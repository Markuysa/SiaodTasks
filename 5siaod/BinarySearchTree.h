#pragma once
#include "ControlFIleModule.h"
#include <vector>

struct TreeNode {
	string key;
	int filePosition;
	TreeNode* right;
	TreeNode* left;
	TreeNode(string key, TreeNode* right, TreeNode* left,int filePosition) {
		this->key = key;
		this->right = right;
		this->left = left;
		this->filePosition = filePosition;
	}
	TreeNode();
};

class binarySearchTree {
	TreeNode* root = nullptr;
	int count_elements = 0;
public:
	TreeNode* addItem(TreeNode* &root, company_struct* insertObject,int position);
	void buildFromFile(TreeNode* root, string& nameOfFile);
	TreeNode* getRoot() { return root; };
	void setRoot(TreeNode* root) { this->root = root; };
	TreeNode* createRoot(string& license,int position) {
		this->root = new TreeNode(license,nullptr,nullptr,position);
		return this->root;
	}
	TreeNode* searchElement(TreeNode* root, string& key);
	int getCountOfELements() { return this->count_elements; }
	TreeNode* DeleteNode(TreeNode* node, string key);

};

bool isExist(TreeNode* root, string& keyValue) {

	if (root == nullptr) return false;
	if (root->key == keyValue) return true;
	if (root->key < keyValue) return isExist(root->left, keyValue);
	return isExist(root->right, keyValue);
}

void binarySearchTree::buildFromFile(TreeNode* root ,string& nameOfFile){
	ifstream binaryFile(nameOfFile, ios::binary);
	company_struct companyObject;
	root = this->root;
	while (binaryFile.read((char*)&companyObject, sizeof(company_struct))) {
		addItem(root, &companyObject,count_elements);
	}	
	this->root = root;
}
TreeNode* binarySearchTree::addItem(TreeNode* &root, company_struct* insertObject,int position) {
	
	string key(insertObject->license);
	if (isExist(root, key)) return root;
	if (root == nullptr) {
		root = createRoot(key,position);
		return root;
	}

	if (root->key < insertObject->license) root->left = addItem(root->left, insertObject, position++);
	if (root->key > insertObject->license) root->right = addItem(root->right, insertObject, position++);
	this->root = root;
	this->count_elements = position;
	return root;
}
TreeNode* binarySearchTree::searchElement(TreeNode* root, string& key) {
	//fix this (doesn't work if)
	if (root == nullptr) return nullptr;
	if (root->key == key)
		return root;
	if (root->key < key) 
		return searchElement(root->left, key);
	if (root->key > key)
		return searchElement(root->right, key);
	return root;
}
void printTreeObject(TreeNode* object) {
	
	cout << "Position in file: " << object->filePosition << '\n'
		<< "Key: " << object->key << endl;
}

void outputTree(TreeNode* p, int level)
{
	if (p)
	{
		outputTree(p->left, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		/*if (p->key!="ob8")*/
			cout << p->key << endl;
		outputTree(p->right, level + 1);
	}
}

TreeNode* binarySearchTree::DeleteNode(TreeNode* node, string key) {
	if (node == nullptr)
		return node;

	if (key == node->key) {

		TreeNode* tmp;
		if (node->right == nullptr)
			tmp = node->left;
		else {

			TreeNode* ptr = node->right;
			if (ptr->left == nullptr) {
				ptr->left = node->left;
				tmp = ptr;
			}
			else {

				TreeNode* pmin = ptr->left;
				while (pmin->left != nullptr) {
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = node->left;
				pmin->right = node->right;
				tmp = pmin;
			}
		}

		delete node;
		return tmp;
	}
	else if (key > node->key)
		node->left = DeleteNode(node->left, key);
	else
		node->right = DeleteNode(node->right, key);
	return node;
}