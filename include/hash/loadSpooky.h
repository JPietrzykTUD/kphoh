//
// Created by Peter Kreysig on 11.07.2021.
//

#ifndef KPHOH_LOADSPOOKY_H
#define KPHOH_LOADSPOOKY_H
#include "spooky.h"

#include <cstddef>
#include <cstdint>

namespace tuddbs{

    template< typename KeyType >
    struct spooky_hash {
        static std::size_t apply( KeyType key ) {
            SpookyHash sh;
            uint64 hash = sh.Hash64(&key, sizeof(key), 1);
            return ( std::size_t ) hash;
        }
    };

}


#endif //KPHOH_LOADSPOOKY_H
