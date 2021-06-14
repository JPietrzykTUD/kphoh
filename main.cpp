#include <iostream>

#include <hcrstrat/linear_probing.h>
#include <hash/sph.h>
#include <hashmap/hashmap_scalar.h>

int main( ) {
   std::cout << "Hello, World!" << std::endl;
   
   tuddbs::hashmap_scalar_t< tuddbs::static_perfect_hashing_t, tuddbs::linear_probing_t > hm( 100 );
   
   for( uint64_t i = 0; i < 50; ++i ) {
      hm.insert( 7*i, i );
   }
   for( uint64_t i = 0; i < 50; ++i ) {
      auto [ contains, value_left ] = hm.lookup( 4*i );
      if( contains ) {
         std::cout << "Left: " << value_left << ". Right: " << i << "\n";
      }
   }
   
   std::cout << hm.get_stats() << "\n";
   return 0;
}
