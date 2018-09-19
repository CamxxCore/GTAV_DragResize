#include "stdafx.h"

namespace Utility {

Thread::Thread() : m_handle( nullptr )
{ }

Thread::Thread( const ThreadCallback callback ) : Thread( callback, nullptr )
{ }

Thread::Thread( const ThreadCallback callback, const LPVOID param ) :
    m_info( ThreadState( param ), callback ), m_handle( nullptr ) { }

DWORD Thread::ThreadStart( const LPVOID pParam ) {

    auto info = reinterpret_cast<ThreadInfo*>( pParam );

    info->m_state.running = 1;

    do {
        if ( info->m_callback ) {
            info->m_callback( &info->m_state );
        }
    } while ( !info->m_state.shouldExit );

    info->m_state.running = 0;

    return 0;
}

Thread::~Thread() {

    Exit();
}
}
