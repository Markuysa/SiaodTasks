#include "LZ77.h"
#include <map>
struct LZ78Node {
	int index;
	string codeword;
	LZ78Node(int index, string codeword) {
		this->codeword = codeword;
		this->index = index;
	}

};
string encode(vector <LZ78Node> encoded) {
	string resultString = "";
	for (auto i : encoded) {

		resultString += "<" + to_string(i.index) + ";" + i.codeword.back() + ">";
	}
	return resultString;
}
string LZ78Compress(string& uncompressedString) {
	vector <LZ78Node> encoded;
	map<string, int> entries;

	int position = 0;

	string currentEntry;
	int index=0;
	int counter = 1;
	char codeword;
	string prefix;
	while (position < uncompressedString.size()) {
		currentEntry = uncompressedString[position];
		codeword = uncompressedString[position];
		while (entries.find(currentEntry) != entries.end()) {
			currentEntry += uncompressedString[++position];
			prefix = currentEntry.substr(0, currentEntry.size() - 1);
			index = entries[prefix];
			codeword = currentEntry[currentEntry.size()-1];
		}
		entries.insert(make_pair(currentEntry, counter));
		LZ78Node node(index, currentEntry);
		encoded.push_back(node);
		position++;
		counter++;
	}
	return encode(encoded);
}
