#include "ExpressionTree.h"
void printMenu(bool condition)
{
	if (condition) {
		cout << "\t\nPractical work #4 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Expression tree.\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	cout << "/------------------------FIRST-TASK-------------------------/\n";
	cout << "Enter [1] to input an expression in infix notation.\n"
		 << "Enter [2] to input an expression in postfix notation.\n"
		 << "Enter [3] to build a tree.\n"
		 << "Enter [4] to print the tree.\n"
			"Enter [0] to exit\n";
	cout << "Your choice: ";
}

int main() {
	int menu;
	bool flag = true;
	string expression;
	ExpressionTree expressionTree;

	printMenu(true);
	while (flag) {
		cin >> menu;
		switch (menu)
		{
		case 1: {
			cout << "Enter the expression: ";
			cin >> expression;
			expression = infixToPostfix(expression);
			break;
		}
		case 2: {
			cout << "Enter the expression: ";
			cin >> expression;
			break;
		}
		case 3: {
			expressionTree.createTree(expression);
			break;
		}
		case 4: {
			/*printTree(&expressionTree.tree.top(), nullptr, false);*/
			outputTree(&expressionTree.tree.top(),9);
			break;
		}
		default:
			break;
		}
		printMenu(false);
	}

	
	return 0;
}