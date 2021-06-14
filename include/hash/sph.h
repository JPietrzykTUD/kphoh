#ifndef TUDDBS_HOH_INCLUDE_HASH_SPH_H
#define TUDDBS_HOH_INCLUDE_HASH_SPH_H

#include <cstddef>
#include <cstdint>

namespace tuddbs{

   template< typename KeyType >
   struct static_perfect_hashing_t {
      static std::size_t apply( KeyType key ) {
         return ( std::size_t ) key;
      }
   };
   
}
#endif //TUDDBS_HOH_INCLUDE_HASH_SPH_H
