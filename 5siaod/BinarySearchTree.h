#pragma once
#include "ControlFIleModule.h"
#include <vector>
struct binaryTreeNode {
	std::string key;
	int filePosition;
	binaryTreeNode* right;
	binaryTreeNode* left;
	binaryTreeNode(std::string key, binaryTreeNode* right, binaryTreeNode* left) {
		this->key = key;
		this->right = right;
		this->left = left;
	}
};
struct Trunk
{
	Trunk* prev;
	std::string str;

	Trunk(Trunk* prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

// Вспомогательная функция для печати ветвей бинарного дерева
void showTrunks(Trunk* p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	std::cout << p->str;
}


void printTree(binaryTreeNode* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr) {
		return;
	}

	std::string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true);
	printTree(root->left, trunk, true);

	if (!prev) {
		trunk->str = "———";
	}
	else if (isLeft)
	{
		trunk->str = ".———";
		prev_str = "   |";
	}
	else {
		trunk->str = "`———";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	std::cout << " " << root->key << std::endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

}

std::string convertChar(char* license) {

	std::string result = "";
	for (int i = 0; i < 30; i++) {
		if (license[i] == -52) return result;
		result += license[i];
	}
	return result;
}

bool isExist(binaryTreeNode* root, std::string& keyValue) {

	if (root == nullptr) return false;
	if (root->key == keyValue) return true;
	if (root->key < keyValue) return isExist(root->left, keyValue);
	return isExist(root->right, keyValue);
}
class binarySearchTree {

	std::vector <binaryTreeNode*> tree;
public:
	binaryTreeNode* addItem(binaryTreeNode* root, company_struct* insertObject);
};

binaryTreeNode* binarySearchTree::addItem(binaryTreeNode* root, company_struct* insertObject) {
	std::string key = convertChar(insertObject->license);
	if (isExist(root, key)) return root;
	if (root == nullptr) return new binaryTreeNode(root->key,nullptr,nullptr);
	if (root->key < key) return addItem(root->left, insertObject);
	if (root->key > key) return addItem(root->right, insertObject);
	return root;
}