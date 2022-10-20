#include "InfixToPostfix.h"
#include <vector>

bool isNumber(char element) {
	return element >= '0' && element <= '9' ? true : false;
}
//structure of one node in the tree
struct Node {
	char data;
	Node* left;
	Node* right;
	Node(char data, Node* left, Node* right) {
		this->data = data;
		this->left = left;
		this->right = right;
	}
};
class ExpressionTree {

	//stack that is used to form the tree
	stack<Node> treeFormStack;

	//vector of elemets of the exp.tree
	vector<Node> tree;
public:
	Node* createNode(char data, Node* left, Node* right);

	void createTree(string& expression);

	void printTree();
};
// Creating node for the tree
Node* ExpressionTree::createNode(char data, Node* left, Node* right) {
	Node newNode(data,left,right);
	return &newNode;
}
// form our tree
inline void ExpressionTree::createTree(string& expression) {
	for (size_t i = 0; i < expression.size(); i++) {
		//creating a new node for our tree
		Node* newNode = createNode(expression[i], nullptr, nullptr);
		
		// if current element is number ==> create a new node and push it into our stack
		// else ==> create a node with an operatior in a root
		if (!isNumber(expression[i])) {
			//getting first two operands
			Node right = treeFormStack.top();
			treeFormStack.pop();
			Node left = treeFormStack.top();
			treeFormStack.pop();

			// set two pointers to our operands
			newNode->left = &left;
			newNode->right = &right;

		}
		// push to our form stack
		treeFormStack.push(*newNode);
		
	}
}

inline void ExpressionTree::printTree()
{
	while (!treeFormStack.empty()) {
		cout << treeFormStack.top().data;
		treeFormStack.pop();
	}
}
