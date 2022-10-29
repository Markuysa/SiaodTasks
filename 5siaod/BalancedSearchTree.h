#pragma once
#include "BinarySearchTree.h"

int height(TreeNode* currentNode) {
	int leftHeight, rightHeight, heightTree = 0;
	if (currentNode == nullptr) return heightTree;
	leftHeight = height(currentNode->left);
	rightHeight = height(currentNode->right);
	heightTree = max(leftHeight, rightHeight) + 1;
	return heightTree;
}

class balansedSearchTree {
	
	TreeNode* root = nullptr;
	int count_elements = 0;
public:
	TreeNode* addItem(TreeNode*& root, company_struct* insertObject);
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

TreeNode* balansedSearchTree::addItem(TreeNode*& root, company_struct* insertObject) {
	string key = convertChar(insertObject->license);
	if (isExist(root, key)) return root;
	if (root == nullptr) {
		root = createRoot(key);
		this->count_elements++;
		return root;
	}
	int left = height(root->left),right= height(root->right);
	if (left - right == 1) root->right = addItem(root->right, insertObject);
	if (right - left == 1) root->left = addItem(root->left, insertObject);
	if (right - left == 0) root->left = addItem(root->left, insertObject);
	this->root = root;
	this->count_elements++;
	return root;
}


TreeNode* balansedSearchTree::searchElement(TreeNode* root, string& key) {
	// implement BFS 
	return nullptr;
}

