#pragma once

namespace Utility {
union ThreadParameter {
    ThreadParameter( const int value ) : integer( value ) {}
    ThreadParameter( void * obj ) : object( obj ) {}
    int integer;
    void * object;
};

struct ThreadState {
    ThreadState() : ThreadState( NULL ) {}
    ThreadState( ThreadParameter param ) : running( false ), parameter( param ) {}
    BOOL running, shouldExit = false;
    ThreadParameter parameter;
};

typedef void( *ThreadCallback )( ThreadState * pState );

struct ThreadInfo {
    ThreadInfo( const ThreadState state, const ThreadCallback callback ) :
        m_state( state ), m_callback( callback ) {}
    ThreadInfo() : ThreadInfo( ThreadState(), nullptr ) {}
    ThreadState m_state;
    ThreadCallback m_callback;
};

class Thread {
    ThreadInfo m_info;
    HANDLE m_handle;
    static DWORD WINAPI ThreadStart( LPVOID pParam );

  public:
    Thread();

    Thread( ThreadCallback callback );

    Thread( ThreadCallback callback, LPVOID param );

    void Run() {
        Run( THREAD_PRIORITY_NORMAL );
    }

    void Run( const int nPriority ) {
        Run( nPriority, NULL );
    }

    void Run( const int nPriority, const ThreadParameter parameter ) {

        m_info.m_state.parameter = parameter;

        m_handle = CreateThread( nullptr, NULL, ThreadStart, &m_info, NULL, nullptr );

        SetThreadPriority( m_handle, nPriority );

        SetThreadPriorityBoost( m_handle, TRUE );
    }

    void Exit() {
        m_info.m_state.shouldExit = true;
    }

    void Kill() {
        if ( m_handle ) {
            TerminateThread( m_handle, 0 );

            m_handle = nullptr;
        }
    }

    bool IsRunning() const {
        return m_info.m_state.running != 0;
    }

    ~Thread();
};
}
