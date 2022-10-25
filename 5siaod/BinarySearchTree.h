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
};
class binarySearchTree {
	TreeNode* root = nullptr;
	int count_elements = 0;
public:
	TreeNode* addItem(TreeNode* &root, company_struct* insertObject,int position);
	void buildFromFile(TreeNode* root, string& nameOfFile);
	TreeNode* getRoot() { return root; };
	TreeNode* createRoot(string& license,int position) {
		this->root = new TreeNode(license,nullptr,nullptr,position);
		return this->root;
	}
	TreeNode* searchElement(TreeNode* root, string& key);

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
	
	string key = convertChar(insertObject->license);
	if (isExist(root, key)) return root;
	if (root == nullptr) {
		root = createRoot(key,position);
		return root;
	}
	count_elements++;
	this->root = root;
	return root;
}

TreeNode* binarySearchTree::searchElement(TreeNode* root, string& key) {
	
	if (root->key < key) 
		searchElement(root->left, key);
	if (root->key > key)
		searchElement(root->right, key);
	if (root->key == key)
		return root;
	return nullptr;

}

//Branch* del_elem(Branch*& aBranch, int aData) {
//
//	if (aBranch == NULL)
//
//		return aBranch;
//
//	if (aData == aBranch->Data) {
//
//		Branch* tmp;
//
//		if (aBranch->RightBranch == NULL)
//
//			tmp = aBranch->LeftBranch;
//
//		else {
//
//			Branch* ptr = aBranch->RightBranch;
//
//			if (ptr->LeftBranch == NULL) {
//
//				ptr->LeftBranch = aBranch->LeftBranch;
//
//				tmp = ptr;
//
//			}
//
//			else {
//
//				Branch* pmin = ptr->LeftBranch;
//
//				while (pmin->LeftBranch != NULL) {
//
//					ptr = pmin;
//
//					pmin = ptr->LeftBranch;
//
//				}
//
//				ptr->LeftBranch = pmin->RightBranch;
//
//				pmin->LeftBranch = aBranch->LeftBranch;
//
//				pmin->RightBranch = aBranch->RightBranch;
//
//				tmp = pmin;
//
//			}
//
//		}
//
//		delete aBranch;
//
//		return tmp;
//
//	}
//
//	else if (aData < aBranch->Data)
//
//		aBranch->LeftBranch = del_elem(aBranch->LeftBranch, aData);
//
//	else
//
//		aBranch->RightBranch = del_elem(aBranch->RightBranch, aData);
//
//	return aBranch;
//
//}