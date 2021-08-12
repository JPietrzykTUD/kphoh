#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <chrono>
#include <ctime>

#include "include/hcrstrat/linear_probing.h"
#include "include/hash/sph.h"
#include "include/hashmap/hashmap_scalar.h"
#include "include/umash/umash.h"
#include "include/CSVParser/CSVParser.h"
#include "include/hash/loadHash.h"
#include "include/hash/loadMum.h"
#include "include/hash/loadSpooky.h"

namespace fs = std::filesystem;


//Current Join: mc.movie_id = mi_idx.movie_id
std::string first_table = "mc.csv";
int join_predicate_idx1 = 1;
std::string second_table = "mi_idx.csv";
int join_predicate_idx2 = 1;
//Current Hash: MumHash

int main( ) {

    std::string filename1(fs::current_path().parent_path().string() + "/data/" + first_table);
   std::string file_contents1;
   file_contents1 = readFileIntoString(filename1);
   std::map<int, std::vector<std::string>> first_table_map;
    //first_table_map is a map which consists of an index and a vector
    //the vector contains the corresponding line of the csv
    //first element of the vector is the id
   first_table_map = contentMap(file_contents1, ',');

    std::string filename2(fs::current_path().parent_path().string() + "/data/" + second_table);
    std::string file_contents2;
    file_contents2 = readFileIntoString(filename2);
    std::map<int, std::vector<std::string>> second_table_map;
    second_table_map = contentMap(file_contents2, ',');

    std::cout << "Hello, World!" << std::endl;

    tuddbs::hashmap_scalar_t< tuddbs::mum_hash, tuddbs::linear_probing_t > hm( first_table_map.size() );

    /*for( uint64_t i = 0; i < 50; ++i ) {
        hm.insert( 7*i, i );
    }*/

    //Build HashMap
    auto start_building = std::chrono::system_clock::now();
    for(int i =1; i < first_table_map.size(); i++)
    {
        std::string inputString = first_table_map.at(i).at(join_predicate_idx1);
        int input = std::stoi(inputString);
        hm.insert( input, i);
    }
    auto end_building = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_build_secs = end_building-start_building;
    std::cout << "build time in sec: "<< elapsed_build_secs.count() << "\n";

    //Lookup HashMap
    int matches = 0;
    auto start_lookup = std::chrono::system_clock::now();
    for( uint64_t i = 1; i < second_table_map.size(); ++i) {
        std::string inputString = second_table_map.at(i).at(join_predicate_idx2);
        int input = std::stoi(inputString);
        auto [ contains, value_left ] = hm.lookup( input );
        if( contains ) {
            ++matches;
            //std::cout << "Left: " << value_left << ". Right: " << i << "\n";
        }
    }
    auto end_lookup = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_lookup_secs = end_lookup-start_lookup;
    std::cout << "lookup time in sec: "<< elapsed_lookup_secs.count() << "\n";

    //std::cout << hm.get_stats() << "\n";
    std::cout << "collision count: " << hm.get_collisions() << "\n";
    std::cout << "macthes: " << matches << "\n";
    return 0;
}
