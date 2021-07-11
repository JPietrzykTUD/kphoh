//
// Created by Peter Kreysig on 11.07.2021.
//

#ifndef KPHOH_LOADMUM_H
#define KPHOH_LOADMUM_H
#include "mum.h"

#include <cstddef>
#include <cstdint>

namespace tuddbs{

    template< typename KeyType >
    struct mum_hash {
        static std::size_t apply( KeyType key ) {
            size_t hash = mum_hash64(key, 1);
            return ( std::size_t ) hash;
        }
    };

}
#endif //KPHOH_LOADMUM_H
