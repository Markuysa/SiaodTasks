#pragma once
#include "ShannonFano.h"
#include <cassert>
#include <cmath>
HuffmanTree treeHuffman;
ShannonFanoTree treeShannon;
int volume(int length, int i) {
	return length * i;
}


void printEncoded() {

	map<string, string> shannon = treeShannon.encodedCharacters;
	for (auto i : shannon) {

		cout << i.first << " " << i.second << endl;


	}
}
int calculateVolume(string& line,int alphSize) {

	int i = ceil(log2(alphSize));
	return volume(line.size(), i);
	

}
void compressionRatioRLETest(string& uncompressedLine) {
	string compressedLineRepeat = RLE(uncompressedLine);
	double ratioRepeat = double(calculateVolume(compressedLineRepeat,256))/ double(calculateVolume(uncompressedLine, 256));
	cout << "Compressed text: " << compressedLineRepeat << endl;
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratioRepeat << endl;

}
void compressionRatioLZ77Test(string& uncompressedLine) {
	string compressedLine = LZ77Compress(uncompressedLine);
	double ratio = double(calculateVolume(compressedLine,256)) / double(calculateVolume(uncompressedLine,256));
	cout << "Compressed text: " << compressedLine << endl;
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratio << endl;

}
void compressionRatioLZ78Test(string& uncompressedLine) {
	string compressedLine = LZ78Compress(uncompressedLine);
	double ratio = double(calculateVolume(compressedLine, 256)) / double(calculateVolume(uncompressedLine, 256));
	cout << "Compressed text: " << compressedLine << endl;
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratio << endl;
	
}
double calculateMean(string& uncompressedLine) {
	int sum = 0;
	for (auto i : treeHuffman.encodedCharacters) {
		sum += i.second.size() * treeHuffman.HuffmanDict[i.first];
	}
	return double(sum) / double(uncompressedLine.size());
}
double calculateDispersion(string& uncompressedLine) {
	double sum = 0;
	double frequency;
	double sumRes = 0;
	double mean = calculateMean(uncompressedLine);

	for (auto i : treeHuffman.encodedCharacters) {
		sum += pow(mean - i.second.size(), 2);
	}
	return double(sum)/double(treeHuffman.encodedCharacters.size());
}
void compressionRatioHuffmanTest(string& uncompressedLine) {
	string compressedLine = treeHuffman.encode(uncompressedLine);

	double ratio = double(calculateVolume(compressedLine, 2)) / double(calculateVolume(uncompressedLine, 256));
	cout << "Compressed text: " << compressedLine << endl;
	cout << "Compression ratio of <" << uncompressedLine << "> is: " << ratio << endl;
	cout << "Mean length: " << calculateMean(uncompressedLine) << endl;
	cout << "Dispersion: " << calculateDispersion(uncompressedLine) << endl;
}
void compressionRatioShannonFanoTest(string& uncompressedLine) {
	string compressedLine = treeShannon.encode(uncompressedLine);
	double ratio = double(calculateVolume(compressedLine, 2)) / double(calculateVolume(uncompressedLine, 256));
	cout << "Compressed text: " << compressedLine << endl;
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
void testHuffmanFromFile(string& fileName) {
	fstream filea(fileName);
	std::string content((std::istreambuf_iterator<char>(filea)),
		(std::istreambuf_iterator<char>()));
	string compressedLine = treeHuffman.encodeFromFile(fileName);
	double ratio = double(calculateVolume(compressedLine, 2)) / double(calculateVolume(content, 256));
	cout << "Compression ratio of is: " << ratio << endl;
	filea.close();

}
void testShannonFanoFromFile(string& fileName) {
	fstream filea(fileName);
	std::string content((std::istreambuf_iterator<char>(filea)),
		(std::istreambuf_iterator<char>()));
	string compressedLine = treeShannon.encodeFromFile(fileName);
	double ratio = double(calculateVolume(compressedLine, 2)) / double(calculateVolume(content, 256));
	cout << "Compression ratio of is: " << ratio << endl;
	filea.close();
}
