/**
Source: https://www.delftstack.com/de/howto/cpp/read-csv-file-in-cpp/
**/
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>


std::string readFileIntoString(const std::string& path) {
    auto ss = std::ostringstream{};
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

std::map<int, std::vector<std::string>> contentMap(std::string content, char delimiter) {

    std::map<int, std::vector<std::string>> csv_contents;
    std::istringstream sstream(content);
    std::vector<std::string> items;
    std::string record;

    int counter = 0;
    while (std::getline(sstream, record)) {
        std::istringstream line(record);
        while (std::getline(line, record, delimiter)) {
            items.push_back(record);
        }

        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }
    return csv_contents;
}
