#pragma once

namespace Utility {
class MemAddr {

  public:
    MemAddr() : MemAddr( nullptr ) {}

    MemAddr( const uintptr_t address ) : addr( address ) {}

    MemAddr( LPVOID ptr ) : MemAddr( reinterpret_cast<uintptr_t>( ptr ) ) {}

    uintptr_t addr;

    operator uintptr_t&() {
        return addr;
    }

    uintptr_t operator+( uintptr_t x );

    operator void*() const;

    operator uintptr_t() const;

    MemAddr add( MemAddr m ) const {
        return *this + m;
    }
};
}
