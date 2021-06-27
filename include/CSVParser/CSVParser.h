#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>

#ifndef CSVPARSER_H_INCLUDED
#define CSVPARSER_H_INCLUDED

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream;
using std::map; using std::vector;

string readFileIntoString(const string& path);
map<int, vector<string>> contentMap(string content, char delimiter);

#endif // CSVPARSER_H_INCLUDED
