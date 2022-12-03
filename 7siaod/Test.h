#pragma once
#include "ShannonFano.h"
#include <cassert>
#include <cmath>
HuffmanTree treeHuffman;
ShannonFanoTree treeShannon;
int volume(int length, int i) {
	return length * i;
}
int calculateVolume(string& line,int alphSize) {

	int i = ceil(log2(alphSize));
	return volume(line.size(), i);
	

}
void compressionRatioRLETest(string& uncompressedLine) {
	string compressedLineRepeat = RLE(uncompressedLine);
	double ratioRepeat = double(calculateVolume(compressedLineRepeat,256))/ double(calculateVolume(uncompressedLine, 256));
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratioRepeat << endl;

}
void compressionRatioLZ77Test(string& uncompressedLine) {
	string compressedLine = LZ77Compress(uncompressedLine);
	double ratio = double(calculateVolume(compressedLine,256)) / double(calculateVolume(uncompressedLine,256));
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratio << endl;
}
void compressionRatioLZ78Test(string& uncompressedLine) {
	string compressedLine = LZ78Compress(uncompressedLine);
	double ratio = double(calculateVolume(compressedLine, 256)) / double(calculateVolume(uncompressedLine, 256));
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratio << endl;

}
void compressionRatioHuffmanTest(string& uncompressedLine) {
	string compressedLine = treeHuffman.encode(uncompressedLine);
	double ratio = double(calculateVolume(compressedLine, 2)) / double(calculateVolume(uncompressedLine, 256));
	cout << compressedLine << endl;
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratio << endl;

}
void compressionRatioShannonFanoTest(string& uncompressedLine) {
	string compressedLine = treeShannon.encode(uncompressedLine);
	double ratio = double(calculateVolume(compressedLine, 2)) / double(calculateVolume(uncompressedLine, 256));
	cout << compressedLine << endl;
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratio << endl;
}

void testDecompressHuffman(string& uncompressedLine) {
	string decompressedLine = treeHuffman.decode(uncompressedLine);

	if (uncompressedLine == decompressedLine) {
		cout << "Success decompression: " << decompressedLine << endl;
	}
	else {
		cout << "Failure decompression!" << endl;
	}
}
void testDecompressShannonFano(string& uncompressedLine) {
	string decompressedLine = treeShannon.decode(uncompressedLine);

	if (uncompressedLine == decompressedLine) {
		cout << "Success decompression: " << decompressedLine << endl;
	}
	else {
		cout << "Failure decompression!" << endl;
	}

}