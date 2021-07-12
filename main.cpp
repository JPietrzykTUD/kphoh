#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

#include "include/hcrstrat/linear_probing.h"
#include "include/hash/sph.h"
#include "include/hashmap/hashmap_scalar.h"
#include "include/umash/umash.h"
#include "include/CSVParser/CSVParser.h"
#include "include/hash/loadHash.h"
#include "include/hash/loadMum.h"
#include "include/hash/loadSpooky.h"

namespace fs = std::filesystem;


//Current Join: ct.id = mc.company_type_id
std::string first_table = "ct.csv";
int join_predicate_idx1 = 0;
std::string second_table = "mc.csv";
int join_predicate_idx2 = 3;
//Current Hash: XXH64

int main( ) {

    std::string filename1(fs::current_path().parent_path().string() + "/data/" + first_table);
   std::string file_contents1;
   file_contents1 = readFileIntoString(filename1);
   std::map<int, std::vector<std::string>> first_table_map;
    //first_table is a map which consists of an index and a vector
    //the vector contains the corresponding line of the csv
    //first element of the vector is the id
   first_table_map = contentMap(file_contents1, ',');

    std::string filename2(fs::current_path().parent_path().string() + "/data/" + second_table);
    std::string file_contents2;
    file_contents2 = readFileIntoString(filename2);
    std::map<int, std::vector<std::string>> second_table_map;
    second_table_map = contentMap(file_contents2, ',');

    std::cout << "Hello, World!" << std::endl;

    tuddbs::hashmap_scalar_t< tuddbs::spooky_hash, tuddbs::linear_probing_t > hm( first_table_map.size() );

    /*for( uint64_t i = 0; i < 50; ++i ) {
        hm.insert( 7*i, i );
    }*/
    for(int i =1; i < first_table_map.size(); i++)
    {
        std::string inputString = first_table_map.at(i).at(join_predicate_idx1);
        int input = std::stoi(inputString);
        hm.insert( input, i);
    }


    for( uint64_t i = 1; i < second_table_map.size(); ++i) {
        std::string inputString = second_table_map.at(i).at(join_predicate_idx2);
        int input = std::stoi(inputString);
        auto [ contains, value_left ] = hm.lookup( input );
        if( contains ) {
            std::cout << "Left: " << value_left << ". Right: " << i << "\n";
        }
    }

    std::cout << hm.get_stats() << "\n";
    return 0;
}
