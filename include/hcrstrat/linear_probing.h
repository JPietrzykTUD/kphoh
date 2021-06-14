#ifndef TUDDBS_HOH_INCLUDE_CRSTRAT_LINEAR_PROBING_H
#define TUDDBS_HOH_INCLUDE_CRSTRAT_LINEAR_PROBING_H

#include <cstddef>

namespace tuddbs{
   
   struct linear_probing_t {
      static std::size_t get_next( std::size_t hash, std::size_t mod ) {
         return ( hash + 1 ) & mod;
      }
   };
}

#endif //TUDDBS_HOH_INCLUDE_CRSTRAT_LINEAR_PROBING_H
