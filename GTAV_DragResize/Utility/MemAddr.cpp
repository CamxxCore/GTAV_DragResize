#include "stdafx.h"

namespace Utility {

uintptr_t MemAddr::operator+( const uintptr_t x ) {

    return addr + x;
}

MemAddr::operator void*() const {

    return reinterpret_cast<void*>( addr );
}

MemAddr::operator uintptr_t() const {

    return addr;
}
}
