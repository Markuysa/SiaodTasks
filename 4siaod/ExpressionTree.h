#include "InfixToPostfix.h"
#include <vector>
#include <iomanip>


struct Trunk
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str)
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
	cout << p->str;
}

bool isNumber(char element) {
	return element >= '0' && element <= '9' || element >='a' && element<='z' ? true : false;
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

void outputTree(Node* p, int level)
{
	if (p)
	{
		outputTree(p->left, level + 1);
		for (int i = 0; i < level; i++) cout << "   ";
		cout << p->data << endl;
		outputTree(p->right, level + 1);
	}
}
class ExpressionTree {
public:
	stack<Node> tree;
	int level = 0;
	Node* createNode(char data, Node* left, Node* right);

	void createTree(string& expression);

	void printTree(Node* top, string table_pr,bool flag,int counter);
};
// Creating node for the tree
Node* ExpressionTree::createNode(char data, Node* left, Node* right) {
	Node newNode(data,left,right);
	return &newNode;
}
// form our tree
void ExpressionTree::createTree(string& expression) {
	for (size_t i = 0; i < expression.size(); i++) {
		//creating a new node for our tree
		Node* newNode = createNode(expression[i], nullptr, nullptr);
		
		// if current element is number ==> create a new node and push it into our stack
		// else ==> create a node with an operatior in a root
		if (!isNumber(expression[i])) {
			//getting first two operands
			Node* right = new Node(tree.top().data, tree.top().left, tree.top().right);
			tree.pop();
			Node* left = new Node(tree.top().data, tree.top().left, tree.top().right);
			tree.pop();

			// set two pointers to our operands
			newNode->data = expression[i];
			newNode->left = left;
			newNode->right = right;

		}
		// push to our form stack
		tree.push(*newNode);
		
	}
}


void printTree(Node* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr) {
		return;
	}

	string prev_str = "    ";
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
	cout << " " << root->data << endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

}

