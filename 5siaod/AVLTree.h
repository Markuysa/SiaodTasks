#pragma once
#include "BalancedSearchTree.h"
class AVLTree {

	TreeNode* root = nullptr;
public:
	int countOfRotates = 0;
	int heightTree = 0;
	TreeNode* addItem(TreeNode*& root, company_struct* insertObject,int position);
	TreeNode* buildFromFile(TreeNode* root, string& nameOfFile, int position);

	TreeNode* getRoot() { return root; };
	void setRoot(TreeNode* root) { this->root = root; };
	TreeNode* createRoot(string& license,int position) {
		this->root = new TreeNode(license, nullptr, nullptr, position);
		return this->root;
	}
	TreeNode* searchElement(TreeNode* root, string& key);
	TreeNode* deleteElement(TreeNode* root, string& key);

	int heightAVL(TreeNode* root);
	int balanseDifference(TreeNode* root);
	TreeNode* smallLeftRotate(TreeNode*&root);
	TreeNode* smallRightRotate(TreeNode*& root);
	TreeNode* leftRightRotate(TreeNode*& root);
	TreeNode* rightLeftRotate(TreeNode*& root);

	void correctHeight();
	TreeNode* balanseTree(TreeNode* &root);
	TreeNode* deleteMin(TreeNode* root);
};

int AVLTree::balanseDifference(TreeNode* root) {
	if (root->left && root->right) {
		return heightAVL(root->left) - heightAVL(root->right);
	}
	else if (root->left && root->right == NULL) {
		return heightAVL(root->left);
	}
	else if (root->left == NULL && root->right) {
		return -1 * heightAVL(root->right);
	}
}
TreeNode* AVLTree::searchElement(TreeNode* root, string& key)
{
	if (root==nullptr) return nullptr;
	if (root->key < key)
		return searchElement(root->left, key);
	if (root->key > key)
		return searchElement(root->right, key);
	if (root->key.compare(key)==0)
		return root;
}
void deleteElements(TreeNode* root) {
	if (root == nullptr) return;
	deleteElements(root->left);
	deleteElements(root->right);
	delete root;
}
TreeNode* getMin(TreeNode* root,string& key) {
	if (root == nullptr) return nullptr;
	string key2 = root->key;
	TreeNode* result=nullptr;
	if (key < key2) {
		key2 = key;
		result = root;
	}
	getMin(root->right,key);
	getMin(root->left,key);
	return result;
}
TreeNode* AVLTree::deleteMin(TreeNode* root) {
	if (root->left == nullptr)
		return root->right;
	root->left = deleteMin(root->left);
	return balanseTree(root);
}
TreeNode* AVLTree::deleteElement(TreeNode* root, string& key)
{
	if (root == nullptr) return nullptr;
	if (root->key < key)
		root->left = deleteElement(root->left, key);
	if (root->key > key)
		root->right = deleteElement(root->right, key);
	else {
		TreeNode* left = root->left;
		TreeNode* right = root->right;

		delete root;

		if (right == nullptr)
			return left;
		else {
			TreeNode* minNode = getMin(root->right,root->key);
			minNode->right = deleteMin(root->right);
			minNode->left = left;
			return balanseTree(minNode);
		}

	}
	return balanseTree(root);
}
int AVLTree::heightAVL(TreeNode* root){
	if (root->left && root->right == NULL) {
		return height(root->left) + 1;
	}
	else if (root->left == NULL && root->right) {
		return height(root->right) + 1;
	}
	else if (root->left && root->right) {
	int left = height(root->left);
	int right = height(root->right);
	if (left < right)
		return right + 1;
	else return  left + 1;
	}
	return 1;
}
TreeNode* AVLTree::rightLeftRotate(TreeNode*& root) {

	TreeNode* temp;
	TreeNode* temp2;
	TreeNode* temp3;

	temp = root;
	temp2 = root->right;
	temp3 = temp2->left;

	temp->right = temp3->left;
	temp2->left = temp3->right;
	temp3->left = temp;
	temp3->right = temp2;

	root = temp3;
	return root;
	
}
TreeNode* AVLTree::leftRightRotate(TreeNode*& root) {

	TreeNode* temp;
	TreeNode* temp2;
	TreeNode* temp3;

	temp = root;
	temp2 = root->right;
	temp3 = temp2->left;

	temp->left = temp3->right;
	temp2->right = temp3->left;
	temp3->right = temp;
	temp3->left = temp2;

	root = temp3;
	return root;

}
TreeNode* AVLTree::balanseTree(TreeNode* &root) {
	cout << sizeof(root);
	if (balanseDifference(root)== 2) {
		if (balanseDifference(root->left) == 1) {
			root= smallLeftRotate(root);
			this->countOfRotates++;
		}
		else {
			if (balanseDifference(root->left) == -1) {
				root = leftRightRotate(root);
				this->countOfRotates++;
			}
		}
	}
	if (balanseDifference(root) == -2) {
		if (balanseDifference(root->right)==-1) {
			root = smallRightRotate(root);
			this->countOfRotates++;
		}
		else {
			if (balanseDifference(root->right) == 1) {
				root = rightLeftRotate(root);
				this->countOfRotates++;
			}
		}
	}
	return root;
}

TreeNode* AVLTree::buildFromFile(TreeNode* root, string& nameOfFile, int position) {
	company_struct companyObject;
	ifstream binaryFile(nameOfFile, ios::binary);

	while (binaryFile.read((char*)&companyObject, sizeof(company_struct))) {

		addItem(root, &companyObject,++position);
		root=this->root;
		this->heightTree++;
	}
	return root;
}
	
TreeNode* AVLTree::addItem(TreeNode*& root, company_struct* insertObject, int position) {

	string key(insertObject->license);
	if (isExist(root, key)) return root;
	if (root == nullptr) {
		root = createRoot(key, position);
	}
	else {
		if (root->key < insertObject->license) root->left = addItem(root->left, insertObject, position++);
		if (root->key > insertObject->license) root->right = addItem(root->right, insertObject, position++);
	}
	this->root = root;
	balanseTree(this->root);
	return this->root;
}

TreeNode* AVLTree::smallRightRotate(TreeNode* &root){
	
	TreeNode* newRoot = root->right;
	TreeNode* temp = root;
	if (!newRoot)
		return root;
	temp->right = newRoot->left;
	newRoot->left = temp;
	root = newRoot;

	return root;

}
TreeNode* AVLTree::smallLeftRotate(TreeNode*& root) {

	TreeNode* newRoot = root->left;
	TreeNode* temp = root;
	if (!newRoot)
		return root;
	temp->left = newRoot->right;
	newRoot->right = temp;

	root = newRoot;

	return root;
}

void AVLTree::correctHeight() {
	this->heightTree = max(height(this->root->left), height(this->root->right));
}

