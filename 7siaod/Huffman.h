#pragma once
#include "LZ78.h"
#include <queue>
#include <algorithm> 
struct HuffmanNode {
	int frequency = 0;
	char character = ' ';
	HuffmanNode(int frequency, char character) {

		this->character = character;
		this->frequency = frequency;
	}
	HuffmanNode() {};
};

struct HuffmanTreeNode {
	string character = "";
	int frequency = 0;
	HuffmanTreeNode* right = nullptr;
	HuffmanTreeNode* left = nullptr;
	char HuffmanCoeff = '0';
	HuffmanTreeNode(int frequency, HuffmanTreeNode* left, HuffmanTreeNode* right,string character) {
		this->left = left;
		this->right = right;
		this->frequency = frequency;
		this->character = character;
	}
	HuffmanTreeNode() {};
};
struct encodeStruuct {
	char letter;
	string encodeLine;
};

class HuffmanTree {
	vector<HuffmanTreeNode*> huffmanTree;
	HuffmanTreeNode* root;
	vector<encodeStruuct> encodedText;
public:
	map<string, int> HuffmanDict;
	map<string, string> encodedCharacters;
	void buildHuffmansTree(string& uncompressedLine);
	void formHuffmanList(string& uncompressedString);
	vector<HuffmanTreeNode*> convertMap(map<string, int> HuffmanMap);
	void formEncodedDict(HuffmanTreeNode* node, string resultString);
	string encode(string& uncompressedString);
	HuffmanTreeNode* getRoot() { return this->root; };
	string decode(string& compressedLine);
	string encodeFromFile(string& nameOfFile);
};
string HuffmanTree::encodeFromFile(string& nameOfFile) {

	fstream filea(nameOfFile);
	std::string content((std::istreambuf_iterator<char>(filea)),
		(std::istreambuf_iterator<char>()));
	filea.close();
	return this->encode(content);
}
void HuffmanTree::formEncodedDict(HuffmanTreeNode* node, string resultString) {
	if (node == NULL) {
		return;
	}
	if (node->left == NULL && node->right == NULL) {
		this->encodedCharacters[node->character] = resultString;
		return;
	}
	formEncodedDict(node->left, resultString + "0");
	formEncodedDict(node->right, resultString + "1");
}


string HuffmanTree::encode(string& uncompressedString) {
	string result = "";
	this->buildHuffmansTree(uncompressedString);
	this->formEncodedDict(this->getRoot(), "");
	HuffmanTreeNode* root = this->getRoot();
	int counter = 0;
	for (auto i : uncompressedString) {
		string letter;
		letter = i;
		result+=this->encodedCharacters[letter];
		encodeStruuct obj;
		obj.encodeLine = this->encodedCharacters[letter];
		obj.letter = i;
		this->encodedText.push_back(obj);
	}

	return result;
}

bool compareStructs(HuffmanTreeNode* first, HuffmanTreeNode* second) {
	return first->frequency > second->frequency;
}
vector<HuffmanTreeNode*> HuffmanTree::convertMap(map<string, int> HuffmanMap) {
	vector<HuffmanTreeNode*> result;
	for (auto i : HuffmanMap) {
		HuffmanTreeNode* node = new HuffmanTreeNode(i.second,nullptr,nullptr, i.first);
		result.push_back(node);
	}
	sort(result.begin(), result.end(), compareStructs);
	return result;
}
void HuffmanTree::formHuffmanList(string& uncompressedString) {
	int index = 0;
	string letter;
	while (index < uncompressedString.size()) {
		letter = uncompressedString[index++];
		this->HuffmanDict[letter]++;
	}
}


void HuffmanTree::buildHuffmansTree(string& uncompressedLine) {
	formHuffmanList(uncompressedLine);
	map<string, int> result = this->HuffmanDict;
	this->huffmanTree = this->convertMap(result);
	vector<HuffmanTreeNode*> HuffmanVector = this->huffmanTree;

	while (this->huffmanTree.size() > 1) {

		HuffmanTreeNode* right = new HuffmanTreeNode;
		HuffmanTreeNode* left = new HuffmanTreeNode;
		left = this->huffmanTree.back();
		this->huffmanTree.pop_back();
		right = this->huffmanTree.back();
		this->huffmanTree.pop_back();
		
		HuffmanTreeNode* newNode = new HuffmanTreeNode;

		newNode->right =  right;
		newNode->left = left;
		newNode->frequency = right->frequency + left->frequency;
		newNode->character = right->character + left->character;
		this->huffmanTree.push_back(newNode);
		sort(this->huffmanTree.begin(), this->huffmanTree.end(), compareStructs);
	}

	this->root = this->huffmanTree.back();
}
string HuffmanTree::decode(string& compressedLine) {
	string result = "";
	for (auto i : this->encodedText) {
		result += i.letter;
	}
	return result;
}


