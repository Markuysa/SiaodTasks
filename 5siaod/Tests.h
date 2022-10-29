#pragma once
#include "AVLTree.h"
#include <cassert>
void TestAVLSearch() {


}
bool testOrder(TreeNode* root) {
	if (root == nullptr) return false;
	if (root->left > root->right) {
		testOrder(root->right);
		testOrder(root->left);
	}
	else return false;
	return true;
}
bool testTree(TreeNode* root) {
	
	if (abs(height(root->right)-height(root->left))<=1 and testOrder(root)) return true;
	return false;
}


void TEST_BuildTree_ByDeafult_ReturnsTrue(AVLTree* root,string &filename) {
	assert(testTree(root->buildFromFile(root->getRoot(), filename, 0)) && root->heightTree!= 0 == true);
	cout << "The tree builded succesfully\n";
}
