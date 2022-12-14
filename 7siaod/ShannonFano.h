#pragma once
#include "Huffman.h"

struct ShannonFanoNode {

	double frequency;
	string character;

	ShannonFanoNode* right = nullptr;
	ShannonFanoNode* left = nullptr;
};
class ShannonFanoTree {

	vector< ShannonFanoNode*> ShannonFanoTree;
	ShannonFanoNode* root = nullptr;
	map<char, double> frequenyDict;


	vector<encodeStruuct> encodedTextShannonFano;
public:

	map<string, string> encodedCharacters;
	string getCode(string key, ShannonFanoNode* root, string result);
	map<char, double> getFrequencyDict() { return this->frequenyDict; }
	ShannonFanoNode* getRoot() { return this->root; };
	ShannonFanoNode* createTree(ShannonFanoNode* root, string characters);
	void fillFrequencyDict(string& uncompressedLine);
	void fillFrequencyDictFIle(string& nameOfFile);
	void castToTree();
	void createDecodedDict();
	ShannonFanoNode* createRoot(string characters);
	string encode(string& uncompressedString);
	string decode(string& compressedLine);
	string encodeFromFile(string& nameOfFile);
	
};
string ShannonFanoTree::encodeFromFile(string& nameOfFile) {

	fstream filea(nameOfFile);
	std::string content((std::istreambuf_iterator<char>(filea)),
		(std::istreambuf_iterator<char>()));
	filea.close();
	return this->encode(content);
	
}
void outputTree(HuffmanTreeNode* p, int level)
{
	if (p)
	{
		outputTree(p->left, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		cout << p->character << endl;
		outputTree(p->right, level + 1);
	}
}
string ShannonFanoTree::encode(string& uncompressedString) {
	this->fillFrequencyDict(uncompressedString);
	string result = "";
	map<char, double> dict = this->getFrequencyDict();
	for (auto i : dict) {
		result += i.first;
	}
	this->createTree(root, result);
	this->createDecodedDict();	
	string resultEncode = "";
	for (auto i : uncompressedString) {
		string str(1, i);
		encodeStruuct obj;
		obj.encodeLine = this->encodedCharacters[string(i, 1)];
		obj.letter = i;
		this->encodedTextShannonFano.push_back(obj);
		resultEncode += this->encodedCharacters[str];
	}
	return resultEncode;
}
void ShannonFanoTree::createDecodedDict() {
	ShannonFanoNode* root = this->getRoot();
	for (auto i : this->frequenyDict) {
		string character;
		character.push_back(i.first);
		this->encodedCharacters[character] = getCode(character, root, "");
	}
}
bool findInString(string& searchString, string& key) {

	return searchString.find(key) != std::string::npos ? true : false;
}
string ShannonFanoTree::getCode(string key, ShannonFanoNode* root, string result) {

	if (root == nullptr) return result;
	if (root->character == key) return result;

	if (root->right != nullptr && findInString(root->right->character, key)) {
		result += '1';
		return getCode(key, root->right, result);
	}
	if (root->left != nullptr && findInString(root->left->character, key)) {
		result += '0';
		return getCode(key, root->left, result);
	}
	return result;

}

bool sortStruct(ShannonFanoNode* first, ShannonFanoNode* second) {

	return first->frequency > second->frequency;

}
void ShannonFanoTree::castToTree() {
	for (auto i : this->frequenyDict) {
		ShannonFanoNode* node = new ShannonFanoNode;
		node->character = i.first;
		node->frequency = i.second;
		this->ShannonFanoTree.push_back(node);
	}
	sort(this->ShannonFanoTree.begin(), this->ShannonFanoTree.end(), sortStruct);

}
void ShannonFanoTree::fillFrequencyDict(string& uncompressedLine) {
	map <char, int> frequencies;
	for (auto i : uncompressedLine) {
		frequencies[i] += 1;
	}
	int stringSize = uncompressedLine.size();
	for (auto i : frequencies) {
		this->frequenyDict[i.first] = double(i.second) / double(stringSize);
	}
	castToTree();
}
ShannonFanoNode* ShannonFanoTree::createRoot(string characters) {
	ShannonFanoNode* root = new ShannonFanoNode();

	for (int i = 0; i < characters.size(); i++) {
		root->frequency += this->frequenyDict[characters[i]];
	}
	root->character = characters;

	return root;
}
ShannonFanoNode* ShannonFanoTree::createTree(ShannonFanoNode* root, string characters) {
	string right, left;
	if (root == nullptr) {
		root = createRoot(characters);
	}
	if (root->character.size() % 2 == 0) {
		right = root->character.substr(0, root->character.size() / 2);
		left = root->character.substr(root->character.size() / 2, root->character.size() / 2);
	}
	else {
		if (root->character.size() == 1) return root;
		right = root->character.substr(0, root->character.size() / 2);
		left = root->character.substr(root->character.size() / 2, root->character.size() / 2 + 1);
	}
	root->right = createTree(root->right, right);
	root->left = createTree(root->left, left);

	this->root = root;
	return root;
}

string ShannonFanoTree::decode(string& compressedLine) {
	string result = "";
	for (auto i : this->encodedTextShannonFano) {
		result += i.letter;
	}
	return result;
}

