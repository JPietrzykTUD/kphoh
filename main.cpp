#include <iostream>
#include <string>
#include <filesystem>

#include "include/hcrstrat/linear_probing.h"
#include "include/hash/sph.h"
#include "include/hashmap/hashmap_scalar.h"
#include "include/umash/umash.h"
#include "include/CSVParser/CSVParser.h"
#include "hash/loadHash.h"

namespace fs = std::filesystem;

int main( ) {

   // string filename(fs::current_path() + "/data/mc.csv");
   // string file_contents;
   // file_contents = readFileIntoString(filename);
   // std::map<int, std::vector<string>> csv_contents;
   // csv_contents = contentMap(file_contents, ',');



    std::cout << "Hello, World!" << std::endl;

    tuddbs::hashmap_scalar_t< tuddbs::hsh, tuddbs::linear_probing_t > hm( 100 );

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