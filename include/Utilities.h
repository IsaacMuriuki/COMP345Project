#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <sstream> 

using std::string, std::vector;

// For split() function https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template<typename Out>
void split(const std::string &s, char delim, Out result);
vector<string> split(const string &s, char delim);