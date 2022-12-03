#pragma once
#include "LZ78.h"
#include <algorithm> 
struct HuffmanNode {
	int frequency = 0;
	char character = ' ';
	char HuffmansIndex = '0';
	HuffmanNode(int frequency, char character) {

		this->character = character;
		this->frequency = frequency;
	}
	HuffmanNode() {};
};

struct HuffmanTreeNode {
	int data;
	char character = ' ';
	HuffmanTreeNode* right = nullptr;
	HuffmanTreeNode* left = nullptr;
	char HuffmanCoeff = '0';
	HuffmanTreeNode(int data, HuffmanTreeNode* left, HuffmanTreeNode* right) {
		this->data = data;
		this->left = left;
		this->right = right;
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
	map<char, string> encodedCharacters;
	map<char, int> HuffmanDict;
	vector<encodeStruuct> encodedText;
public:
	void buildHuffmansTree(string& uncompressedLine);
	map <char, string> formDictionary();
	string findByCharacter(char character, map<char, int> HuffmanDict, HuffmanTreeNode* root);
	void formHuffmanList(string& uncompressedString);
	vector<HuffmanNode> convertMap(map<char, int> HuffmanMap);
	void formEncodedDict(HuffmanTreeNode* node, string resultString);
	string encode(string& uncompressedString);
	HuffmanTreeNode* getRoot() { return this->root; };
	void createEncodedDict();
	string getCode(char character, HuffmanTreeNode* root, string result);
	string decode(string& compressedLine);
};
string HuffmanTree::getCode(char character, HuffmanTreeNode* root, string result) {

	if (root == nullptr) return "";
	if (root->character == character) return result;

	if (root->right != nullptr) {
		result += '1';
		return getCode(character, root->right, result);
	}
	if (root->left != nullptr) {
		result += '0';
		return getCode(character, root->left, result);
	}
	return result;

}
void HuffmanTree::createEncodedDict() {
	HuffmanTreeNode* root = this->getRoot();
	for (auto i : this->huffmanTree) {
		this->encodedCharacters[i->character] = getCode(i->character, root, "");
	}

}
void HuffmanTree::formEncodedDict(HuffmanTreeNode* node, string resultString) {
	if (node == NULL) {
		return;
	}
	if (node->left == NULL && node->right == NULL) {
		this->encodedCharacters[node->character] = resultString;

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
		result+=this->encodedCharacters[i];
		encodeStruuct obj;
		obj.encodeLine = this->encodedCharacters[i];
		obj.letter = i;
		this->encodedText.push_back(obj);
	}

	return result;
}

bool compareStructs(HuffmanNode& first, HuffmanNode& second) {

	return first.frequency < second.frequency;
}
vector<HuffmanNode> HuffmanTree::convertMap(map<char, int> HuffmanMap) {
	vector<HuffmanNode> result;
	for (auto i : HuffmanMap) {
		HuffmanNode node(i.second, i.first);
		result.push_back(node);
	}
	sort(result.begin(), result.end(), compareStructs);
	return result;
}
void HuffmanTree::formHuffmanList(string& uncompressedString) {
	int index = 0;
	while (index < uncompressedString.size()) {

		this->HuffmanDict[uncompressedString[index++]]++;
	}
}

void HuffmanTree::buildHuffmansTree(string& uncompressedLine) {
	formHuffmanList(uncompressedLine);
	map<char, int> result = this->HuffmanDict;
	vector<HuffmanNode> HuffmanVector = this->convertMap(result);
	for (int i = 0; i < HuffmanVector.size() - 1; i++) {
		int data;
		HuffmanTreeNode* right;
		HuffmanTreeNode* left;
		HuffmanTreeNode* temp1 = new HuffmanTreeNode;
		HuffmanTreeNode* temp2 = new HuffmanTreeNode;
		bool isNode;
		if (this->huffmanTree.size() == 0) {
			temp1->character = HuffmanVector.at(i).character;
			temp1->data = HuffmanVector.at(i).frequency;
			temp2->character = HuffmanVector.at(i + 1).character;
			temp2->data = HuffmanVector.at(i + 1).frequency;
			data = HuffmanVector.at(i).frequency + HuffmanVector.at(i + 1).frequency;
			right = HuffmanVector.at(i).frequency > HuffmanVector.at(i + 1).frequency ? temp1 : temp2;
			left = HuffmanVector.at(i).frequency <= HuffmanVector.at(i + 1).frequency ? temp1 : temp2;

		}
		else {
			temp1->character = HuffmanVector.at(i + 1).character;
			temp1->data = HuffmanVector.at(i + 1).frequency;
			data = this->huffmanTree.at(i - 1)->data + HuffmanVector.at(i + 1).frequency;
			right = this->huffmanTree.at(i - 1)->data > HuffmanVector.at(i + 1).frequency ? this->huffmanTree.at(i - 1) : temp1;
			left = this->huffmanTree.at(i - 1)->data <= HuffmanVector.at(i + 1).frequency ? this->huffmanTree.at(i - 1) : temp1;
		}
		right->HuffmanCoeff = '1';
		HuffmanTreeNode* huffmanTreeNode = new HuffmanTreeNode;
		huffmanTreeNode->data = data;
		huffmanTreeNode->left = left;
		huffmanTreeNode->right = right;
		this->huffmanTree.push_back(huffmanTreeNode);
	}
	this->root = huffmanTree.back();
}

string HuffmanTree::findByCharacter(char character, map<char, int> HuffmanDict, HuffmanTreeNode* root) {

	string result = "";
	int size = this->huffmanTree.size();
	HuffmanTreeNode* next = this->huffmanTree.at(size - 1);
	for (size_t i = size - 2; i >= 0; i--) {
		if (next == nullptr) return result;
		if (next->right != nullptr && HuffmanDict[character] >= next->right->data) {
			result += '1';
			if (next->right->data == HuffmanDict[character]) return result;
			next = next->right;
		}
		else {
			result += '0';
			if (next->left != nullptr && next->left->data == HuffmanDict[character]) return result;
			next = next->left;
		}


	}
}
map <char, string> HuffmanTree::formDictionary() {

	map<char, string> result;
	string resultString;
	for (auto i : this->HuffmanDict) {
		resultString = this->findByCharacter(i.first, this->HuffmanDict, this->root);
		result[i.first] = resultString;
	}
	return result;
}

string HuffmanTree::decode(string& compressedLine) {
	string result = "";
	for (auto i : this->encodedText) {
		result += i.letter;
	}
	return result;
}


