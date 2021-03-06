#include "stdafx.h"

using namespace Utility;

static Thread initThread = Thread( []( ThreadState* s ) {

    HWND windowHandle = nullptr;

    do {
        Sleep( 0 );
    }

    while ( ( windowHandle = ::FindWindow( TARGET_WINDOW, NULL ) ) == nullptr );

    if ( !Game::Instance()->Initialize() ) {

        LOG( "DragResize: Failed to initialize game." );
    }

    if ( !WindowHook::Instance()->Initialize() ) {

        LOG( "DragResize: Failed to initialize window hook." );
    }

    s->shouldExit = 1;
} );

void uninitialize() {

    WindowHook::Instance()->Unintialize();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     ) {
    switch ( ul_reason_for_call ) {
    case DLL_PROCESS_ATTACH:
        initThread.Run();
        break;
    case DLL_PROCESS_DETACH:
        uninitialize();
        break;
    }
    return TRUE;
}

