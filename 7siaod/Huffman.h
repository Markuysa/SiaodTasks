#pragma once
#include "LZ78.h"
#include <algorithm> 
struct HuffmanNode {
	int frequency=0;
	char character=' ';
	char HuffmansIndex = '0';
	HuffmanNode(int frequency, char character) {

		this->character = character;
		this->frequency = frequency;
	}
	HuffmanNode() {};
};

struct HuffmanTreeNode{
	int data;
	char character = ' ';
	HuffmanTreeNode* right=nullptr;
	HuffmanTreeNode* left=nullptr;
	char HuffmanCoeff = '0';
	HuffmanTreeNode(int data, HuffmanTreeNode* left, HuffmanTreeNode* right) {
		this->data = data;
		this->left = left;
		this->right = right;
	}
	HuffmanTreeNode() {};
};


class HuffmanTree {
	vector<HuffmanTreeNode*> huffmanTree;
	HuffmanTreeNode* root;
public:
	void buildHuffmansTree(string& uncompressedLine);
	map <char, string> formDictionary(map<char, int> HuffmanDict);
	string findByCharacter(char character, map<char, int> HuffmanDict, HuffmanTreeNode* root);
	map<char, int> formHuffmanList(string& uncompressedString);
	vector<HuffmanNode> convertMap(map<char, int> HuffmanMap);
	string encode(string& uncompressedString);
};

string HuffmanTree::encode(string& uncompressedString) {

	this->buildHuffmansTree(uncompressedString);



}


bool compareStructs(HuffmanNode& first, HuffmanNode& second) {

	return first.frequency < second.frequency;
}
vector<HuffmanNode> HuffmanTree::convertMap(map<char, int> HuffmanMap) {
	vector<HuffmanNode> result;
	for (auto i : HuffmanMap) {
		HuffmanNode node( i.second, i.first );
		result.push_back(node);
	}
	sort(result.begin(), result.end(),compareStructs);
	return result;
}
map<char,int> HuffmanTree::formHuffmanList(string& uncompressedString){
	map<char, int> result;
	int index = 0;
	while (index<uncompressedString.size()) {
		
		result[uncompressedString[index++]]++;
	}
	return result;
}

void HuffmanTree::buildHuffmansTree(string& uncompressedLine) {
	map<char, int> result = this->formHuffmanList(uncompressedLine);
	vector<HuffmanNode> HuffmanVector = this->convertMap(result);
	for (int i = 0; i < HuffmanVector.size()-1;i++) {
		int data;
		HuffmanTreeNode* right;
		HuffmanTreeNode* left;
		HuffmanTreeNode* temp1 = new HuffmanTreeNode;
		HuffmanTreeNode* temp2 = new HuffmanTreeNode;
		bool isNode;
		if (this->huffmanTree.size() == 0) {
			temp1->character = HuffmanVector.at(i).character;
			temp1->data = HuffmanVector.at(i).frequency;
			temp2->character = HuffmanVector.at(i+1).character;
			temp2->data = HuffmanVector.at(i+1).frequency;
			data = HuffmanVector.at(i).frequency + HuffmanVector.at(i + 1).frequency;
			right = HuffmanVector.at(i).frequency > HuffmanVector.at(i + 1).frequency ? temp1 : temp2;
			left = HuffmanVector.at(i).frequency < HuffmanVector.at(i + 1).frequency ? temp1 : temp2;
			
		}
		else {
			temp1->character = HuffmanVector.at(i + 1).character;
			temp1->data = HuffmanVector.at(i + 1).frequency;
			data = this->huffmanTree.at(i - 1)->data + HuffmanVector.at(i + 1).frequency;
			right = this->huffmanTree.at(i - 1)->data > HuffmanVector.at(i + 1).frequency? this->huffmanTree.at(i - 1):temp1;
			left = this->huffmanTree.at(i - 1)->data < HuffmanVector.at(i + 1).frequency ? this->huffmanTree.at(i - 1) : temp1;
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
	HuffmanTreeNode* next = this->huffmanTree.at(size-1);
	for (size_t i = size - 2; i >= 0; i--) {
		if (next == nullptr) return result;
		if (next->right!=nullptr && HuffmanDict[character]>=next->right->data) {
			result += '1';
			if (next->right->data == HuffmanDict[character]) return result;
			next = next->right;
		}
		else {
			result += '0';
			if (next->left!= nullptr && next->left->data == HuffmanDict[character]) return result;
			next = next->left;
		}


	}
}
map <char, string> HuffmanTree::formDictionary(map<char, int> HuffmanDict) {

	map<char, string> result;
	string resultString;
	for (auto i : HuffmanDict) {
		resultString = this->findByCharacter(i.first, HuffmanDict, this->root);
		result[i.first] = resultString;
	}
	return result;
}

