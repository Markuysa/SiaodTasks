#include "RLE.h"

struct LZNODE {
	int offset;
	int length;
	char next;
	LZNODE(int offset, int length, char next) {
		this->length = length;
		this->offset = offset;
		this->next = next;

	}
};

bool findInLAB(string& searchString, string& SB) {

	if (SB.find(searchString) != std::string::npos) {
		return true;
	}
	return false;
}
string encodeLZ77(vector<LZNODE> result) {
	string resString = "";
	for (auto i : result) {
		resString+= "<"+ to_string(i.offset) + ";" + to_string(i.length) + ';' + i.next+">";
	}
	return resString;
}
string LZ77Compress(string& uncompressedString) {
	vector<LZNODE> resultVector;
	int WINDOW_SIZE = 50;
	int sbSize, labSize;
	int length = 0, offset = 0, findPos;
	char next;
	//setting sizes of buffers
	WINDOW_SIZE % 2 == 0 ? sbSize = WINDOW_SIZE / 2, labSize = WINDOW_SIZE / 2 : sbSize = WINDOW_SIZE / 2 + 1, labSize = WINDOW_SIZE / 2;
	// SB - search buffer, LAB - look ahead buffer;
	string SB = "", LAB = "", searchString = "";
	int position = 0, labPosition = 1;

	while (position < uncompressedString.length()) {
		LAB = uncompressedString.substr(position, labSize);
		searchString = LAB[0];
		while (findInLAB(searchString, SB)) {
			searchString += LAB[labPosition];
			labPosition++;
		}
		next = searchString[searchString.size() - 1];
		length = searchString.size() - 1;
		offset = length == 0 ? 0 : SB.size() - SB.rfind(searchString.substr(0, searchString.size() - 1));
		SB += searchString;
		if (SB.size() > sbSize)
			SB = SB.substr(SB.size() - sbSize, sbSize);
		LZNODE node(offset, length, next);
		resultVector.push_back(node);
		position += labPosition;
		labPosition = 1;
	}
	return encodeLZ77(resultVector);
}
