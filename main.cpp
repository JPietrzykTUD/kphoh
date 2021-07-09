#include <iostream>
#include <string>
#include <filesystem>

#include "include/hcrstrat/linear_probing.h"
#include "include/hash/sph.h"
#include "include/hashmap/hashmap_scalar.h"
//#include "include/umash/umash.h"
#include "include/CSVParser/CSVParser.h"
#include "include/hash/loadHash.h"

#define XXH_INLINE_ALL
#include "xxhash.h"

namespace fs = std::filesystem;

int main( ) {

    string filename(fs::current_path().parent_path().string() + "/data/mc.csv");

   string file_contents;
   file_contents = readFileIntoString(filename);
   std::map<int, std::vector<string>> csv_contents;
    //csv_contents is a map which consists of an index and a vector
    //the vector contains the corresponding line of the csv
    //first element of the vector is the id
   csv_contents = contentMap(file_contents, ',');
    /*for(auto elem : csv_contents)
    {
        std::cout << elem.first << " " << elem.second.at(0) << "\n";
    }*/


    std::cout << "Hello, World!" << std::endl;

    tuddbs::hashmap_scalar_t< tuddbs::hsh, tuddbs::linear_probing_t > hm( csv_contents.size() );

    /*for( uint64_t i = 0; i < 50; ++i ) {
        hm.insert( 7*i, i );
    }*/
    for(auto elem : csv_contents)
    {
        std::string input = elem.second.at(0);
        const void* inputPointer = input.c_str();
        XXH64_hash_t hash = XXH64(inputPointer, elem.second.at(0).size(), 0);
        hm.insert(hash, elem.first);
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
