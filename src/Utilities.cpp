#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <sstream> 
#include "Utilities.h"

using std::string, std::vector;

// SPLIT() FUNCTION from https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template<typename Out> 
void split(const string &s, char delim, Out result) {
	std::stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		*(result++) = item;
	}
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}