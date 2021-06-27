#ifndef HOH_LOADHASH_H
#define HOH_LOADHASH_H
#include "xxhash.h"
#include "wyhash.h"

#include <cstddef>
#include <cstdint>

namespace tuddbs{

    template< typename KeyType >
    struct hsh {
        static std::size_t apply( KeyType key ) {
            XXH64_hash_t hash = XXH64(&key, sizeof(key), 1); // XXH
            //uint64_t _wyp[4]; // WyHash
            //make_secret(time(NULL),_wyp);
            //std::size_t hash = wyhash(&key, sizeof(key),0,_wyp);
            return ( std::size_t ) hash;
        }
    };

}

#endif //HOH_LOADHASH_H
