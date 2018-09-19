#include "stdafx.h"
#include <sstream>
#include <iomanip>
#include <ctime>

HMODULE Utility::GetActiveModule() {
    HMODULE hModule = nullptr;

    GetModuleHandleEx( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCSTR>( &GetActiveModule ),
                       &hModule );

    return hModule;
}

std::string Utility::GetModuleName( HMODULE hModule ) {
    TCHAR inBuf[MAX_PATH];

    if ( !hModule )
        hModule = GetActiveModule();

    GetModuleFileName( hModule, inBuf, MAX_PATH );

    auto str = std::string( inBuf );

    auto seperator = str.find_last_of( "\\" );

    if ( seperator != std::string::npos )
        seperator += 1;

    return str.substr( seperator, str.find_last_of( "." ) - seperator );
}

std::string Utility::GetWorkingDirectory() {
    const auto hModule = GetActiveModule();

    TCHAR inBuf[MAX_PATH];

    GetModuleFileName( hModule, inBuf, MAX_PATH );

    auto str = std::string( inBuf );

    auto seperator = str.find_last_of( "\\" );

    if ( seperator != std::string::npos )
        seperator += 1;

    return str.substr( 0, seperator );
}

std::string Utility::GetShortTimeString() {

    time_t t = time( nullptr );

    struct tm timeinfo;

    localtime_s( &timeinfo, &t );

    return va( "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec );
}


std::string Utility::HexString( BYTE * data, int len ) {
    std::stringstream ss;

    for ( int i = 0; i < len; ++i ) {
        ss << "\\x" <<
           std::uppercase <<
           std::setfill( '0' ) <<
           std::setw( 2 ) <<
           std::hex << static_cast<int>( data[i] );
    }
    return ss.str();
}

bool Utility::FileExists( const std::string & fileName ) {
    std::ifstream infile( fileName );
    return infile.good();
}

int Utility::ctol( const char c ) {
    if ( c >= '0' && c <= '9' )
        return c - '0';
    if ( c >= 'A' && c <= 'F' )
        return c - 'A' + 10;
    if ( c >= 'a' && c <= 'f' )
        return c - 'a' + 10;
    throw std::invalid_argument( "Invalid input string" );
}
