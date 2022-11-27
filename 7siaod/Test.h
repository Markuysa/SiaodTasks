#pragma once
#include <vector>
#include <string>
#include <list>
#include <iostream>
using namespace std;

double compressionRatioRLE(string& uncompressedLine, string& compressedLine) {

	int uncomp = uncompressedLine.size(), comp = compressedLine.size();
	return uncomp > comp ? uncomp / comp : -1 * comp / uncomp;
}

