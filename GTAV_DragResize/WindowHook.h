#pragma once
#define TARGET_WINDOW "grcWindow"
#define WINDOW_MIN_WIDTH 100
#define WINDOW_MIN_HEIGHT 100

class WindowHook {
    HWND m_windowHandle;
    bool m_bInSizeMove = false;
  public:
    bool Initialize();
    void Unintialize();
    void OnResize();

    virtual LRESULT WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    HWND      MainWnd() const;

    static WindowHook * Instance();
};

