#ifndef TUDDBS_HOH_INCLUDE_HASHMAP_HASHMAP_SCALAR_H
#define TUDDBS_HOH_INCLUDE_HASHMAP_HASHMAP_SCALAR_H

#include <cstdint>
#include <cstddef>
#include <cmath>
#include <tuple>
#include <string>

namespace tuddbs {
   template< typename KeyType = uint64_t >
   struct build_stats_t {
      
      struct stat_entry_t {
         KeyType key;
         std::size_t hash;
         std::size_t step;
         
         [[nodiscard]] std::string describe() const {
            return "key\thash\tsteps";
         }
         [[nodiscard]] std::string to_string() const {
            return std::to_string( key ) + "\t" + std::to_string( hash) + "\t" + std::to_string( step );
         }
      };
      
      std::size_t const _element_count;
      std::size_t _idx;
      stat_entry_t * const _stats;
      
      explicit build_stats_t( std::size_t element_count ) :
         _element_count{ element_count },
         _idx{ 0 },
         _stats{ reinterpret_cast< stat_entry_t* >( malloc( element_count * sizeof( stat_entry_t ) ) ) }
         { }
      ~build_stats_t() {
         free( _stats );
      }
      void add_stat( KeyType key, std::size_t hash, std::size_t steps ) {
         _stats[ _idx++ ] = { key, hash, steps };
      }
      
      friend std::ostream & operator<<( std::ostream &os, build_stats_t const & s ) {
         os << s._stats[ 0 ].describe() << "\n";
         for( std::size_t i = 0; i < s._idx; ++i ) {
            os << s._stats[ i ].to_string() << "\n";
         }
         return os;
      }
   };
   
   template<
      template< typename > class HashFn, class CRS, typename KeyType = uint64_t, typename ValueType = std::size_t >
   class hashmap_scalar_t {

      private:
         KeyType normalize_key( KeyType key ) {
            // avoid conflicts when keys are 0, since 0 is used to indicate emptyness
            return key + 1;
         }
         
      public:
         
         void insert( KeyType key, ValueType value ) {
            auto        k     = normalize_key( key );
            auto const  inith = HashFunction::apply( k ) & _mod;
            auto        hash  = inith;
            std::size_t steps = 0;
            
            while( _keys[ hash ] != 0 ) {
               hash = CRS::get_next( hash, _mod );
               ++steps;
            }
            _keys[ hash ]     = key;
            _values[ hash ]   = value;
            if (steps != 0){
                ++collisions;
            }
            stats.add_stat( key, inith, steps );
         }
         
         std::tuple< bool, ValueType > lookup( KeyType key ) {
            auto k    = normalize_key( key );
            auto hash = HashFunction::apply( k ) & _mod;
            auto khm  = _keys[ hash ];
            while( khm != 0 ) {
               if( khm == key ) {
                  return std::make_tuple( true, _values[ hash ] );
               }
               hash = CRS::get_next( hash, _mod );
               khm  = _keys[ hash ];
            }
            return std::make_tuple( false, 0 );
         }
      
      public:
         build_stats_t< KeyType > const & get_stats( ) const {
            return stats;
         }

       public:
           std::size_t const & get_collisions( ) const {
               return collisions;
           }
         
      private:
         std::size_t const _element_count;
         std::size_t const _element_count_hm;
         std::size_t const _mod;
         KeyType   * const _keys;
         ValueType * const _values;
         build_stats_t< KeyType > stats;
         std::size_t collisions = 0;
      
      public:
         using HashFunction = HashFn< KeyType >;
      public:
         explicit hashmap_scalar_t( std::size_t number_of_elements ) :
            _element_count{ number_of_elements },
            _element_count_hm(
               std::size_t(
                  1 << std::size_t( 64 - __builtin_clzll( ( std::size_t ) std::ceil( number_of_elements * 1.6 ) ) )
               )
            ),
            _mod{ _element_count_hm - 1 },
            _keys( reinterpret_cast< KeyType * >( malloc( _element_count_hm * sizeof( KeyType ) ) ) ),
            _values( reinterpret_cast< KeyType * >( malloc( _element_count_hm * sizeof( ValueType ) ) ) ),
            stats( number_of_elements )
         {
            std::fill( _keys, _keys + _element_count_hm, 0 );
            std::cout << "element count: " << _element_count_hm << "\n";
         }
         
         ~hashmap_scalar_t( ) {
            free( _values );
            free( _keys );
         }
   };
}

#endif //TUDDBS_HOH_INCLUDE_HASHMAP_HASHMAP_SCALAR_H
