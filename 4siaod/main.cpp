#include "ExpressionTree.h"


int main() {
	ExpressionTree expressionTree;
	string infix = "1*3*5+5*3+2";

	string postfix = infixToPostfix(infix);
	cout << postfix << endl;

 	expressionTree.createTree(postfix);

	expressionTree.printTree();
	return 0;
}