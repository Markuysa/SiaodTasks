#pragma once
#include "ShannonFano.h"
double compressionRatioRLE(string& uncompressedLine, string& compressedLine) {

	int uncomp = uncompressedLine.size(), comp = compressedLine.size();
	return uncomp > comp ? uncomp / comp : -1 * comp / uncomp;
}

