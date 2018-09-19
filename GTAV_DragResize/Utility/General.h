#pragma once

namespace Utility {

HMODULE GetActiveModule();

std::string GetModuleName( HMODULE hModule );

std::string GetWorkingDirectory();

std::string GetShortTimeString();

std::string HexString( BYTE * data, int len );

bool FileExists( const std::string& fileName );

/**
* \brief char to long integer
*/
int ctol( char c );

template<typename ... Args>
std::string va( const std::string& format, Args ... args ) {
    const size_t size = ::snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
    std::unique_ptr<char[]> buf( new char[size] );
    snprintf( buf.get(), size, format.c_str(), args... );
    return std::string( buf.get(), buf.get() + size - 1 );
}
}
