#pragma once
#include "BinarySearchTree.h"


class balansedSearchTree {
	
	TreeNode* root = nullptr;
	int count_elements = 0;
public:
	TreeNode* addItem(TreeNode*& root, company_struct* insertObject);
	void printTree(TreeNode* root, Trunk* prev, bool isLeft);
	TreeNode* buildFromFile(TreeNode* root, string& nameOfFile,int size,int position);
	TreeNode* getRoot() { return root; };
	void setRoot(TreeNode* root) { this->root = root; };
	TreeNode* createRoot(string& license) {
		this->root = new TreeNode(license, nullptr, nullptr, 0);
		return this->root;
	}
	TreeNode* searchElement(TreeNode* root, string& key);

};

TreeNode* balansedSearchTree::buildFromFile(TreeNode* root, string& nameOfFile,int size,int position) {
	if (size == 0) return root;
	int right = size / 2;
	int left = size - right - 1;
	company_struct companyObject;
	ifstream binaryFile(nameOfFile, ios::binary);
	binaryFile.seekg(position * sizeof(company_struct), ios::beg);
	binaryFile.read((char*)&companyObject, sizeof(company_struct));
	string license = convertChar(companyObject.license);
	TreeNode* newNode = new TreeNode(license, nullptr, nullptr, position);
	count_elements++;

	newNode->right = buildFromFile(newNode->right, nameOfFile, right, count_elements);

	newNode->left = buildFromFile(newNode->left, nameOfFile, left, count_elements);

	root = newNode;

	return root;
}
void outputTree(TreeNode *p, int level)
{
	if (p)
	{
		outputTree(p->left, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		cout << p->key << endl;
		outputTree(p->right, level + 1);
	}
}
TreeNode* balansedSearchTree::addItem(TreeNode*& root, company_struct* insertObject) {
	string key = convertChar(insertObject->license);
	if (isExist(root, key)) return root;
	if (root == nullptr) {
		root = createRoot(key);
		return root;
	}
	if (root->key < key) root->left = addItem(root->left, insertObject);
	if (root->key > key) root->right = addItem(root->right, insertObject);
	this->root = root;
	return root;
}

