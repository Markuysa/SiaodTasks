#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;
string RLE(string line) {

	char firstLetter = line[0];
	int counter = 0;
	string resultString = "";

	for (char i : line) {
		if (firstLetter == i) {
			counter++;
		}
		else {
			resultString += to_string(counter) + firstLetter;
			counter = 1;
		}

		firstLetter = i;
	}
	resultString += to_string(counter) + line.back();
	return resultString;
}



