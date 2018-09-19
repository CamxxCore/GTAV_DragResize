#include "stdafx.h"

static WNDPROC oWndProc;

static WindowHook g_WindowHook;

LRESULT CALLBACK MainWndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    // Forward hwnd on because we can get messages (e.g., WM_CREATE)
    // before CreateWindow returns, and thus before mhMainWnd is valid.
    return WindowHook::Instance()->WndProc( hwnd, msg, wParam, lParam );
}

bool WindowHook::Initialize() {

    m_windowHandle = ::FindWindow( TARGET_WINDOW, NULL );

    SetWindowLong( m_windowHandle, GWL_STYLE,
                   GetWindowLong( m_windowHandle, GWL_STYLE ) | WS_SIZEBOX | WS_MINIMIZEBOX | WS_MAXIMIZEBOX );

    oWndProc = ( WNDPROC )SetWindowLongPtr( m_windowHandle, GWLP_WNDPROC, ( LONG_PTR )MainWndProc );

    return true;
}

void WindowHook::Unintialize() {

    SetWindowLongPtr( m_windowHandle, GWLP_WNDPROC, ( LONG_PTR )oWndProc );
}

void WindowHook::OnResize() {

    LOG( "DragResize: Changing window size..." );

    RECT rect;

    GetClientRect( m_windowHandle, &rect );

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    Game::Instance()->UpdateWindowRect( width, height );
}

LRESULT WindowHook::WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {

    switch ( uMsg ) {
    case WM_SIZING:
        return 0;

    case WM_SIZE:
        break;

    case WM_ENTERSIZEMOVE:
        m_bInSizeMove = true;
        break;

    case WM_EXITSIZEMOVE:
        m_bInSizeMove = false;
        OnResize();
        break;

    case WM_GETMINMAXINFO:
        reinterpret_cast<MINMAXINFO*>( lParam )->ptMinTrackSize.x = WINDOW_MIN_WIDTH;
        reinterpret_cast<MINMAXINFO*>( lParam )->ptMinTrackSize.y = WINDOW_MIN_HEIGHT;
        return 0;

    default:
        break;
    }

    return CallWindowProc( oWndProc, hwnd, uMsg, wParam, lParam );
}

HWND WindowHook::MainWnd() const {

    return m_windowHandle;
}

WindowHook * WindowHook::Instance() {

    return &g_WindowHook;
}
