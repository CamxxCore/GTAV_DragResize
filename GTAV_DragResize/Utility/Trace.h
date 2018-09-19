#pragma once

static __forceinline void StackTrace( const char * prefix ) {

    PVOID pFrames[USHRT_MAX];

    const auto count = RtlCaptureStackBackTrace( 0, USHRT_MAX, pFrames, NULL );

    FILE * file;

    char buf[MAX_PATH];

    sprintf_s( buf, "stacktrace_%s_%llu.txt", prefix, GetTickCount64() );

    fopen_s( &file, buf, "w" );

    const auto pModuleBase = ( ULONG64 )GetModuleHandleA( nullptr );

    for ( int ndx = 0; ndx < count; ndx++ )
        fprintf( file, "Trace %3d %016llx\n", ndx, ( ULONG64 )pFrames[ndx] );

    fclose( file );
}
