#include "BinarySearchTree.h"
void printMenu(bool condition)
{
	if (condition) {
		std::cout << "\t\nPractical work #4 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Expression tree.\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	std::cout << "/------------------------FIRST-TASK-------------------------/\n";
	std::cout << "Enter [1] to create a binary file from text file\n"
		<< "Enter [2] to start linear search by the key.\n"
		<< "Enter [3] to print an object from the file by index(pointer).\n"
		<< "Enter [4] to add an object to the file.\n";
	std::cout << "/------------------------Second-TASK-------------------------/\n";
	std::cout << "Enter [5] to build a tree from file.\n"
		<< "Enter [6] to add an object to the tree.\n"
		<< "Enter [7] to search an object by the key.\n"
		<< "Enter [8] to delete an object from the tree\n"
		<< "Enter [9] to print the tree\n";
	std::cout << "/------------------------THIRD-TASK-------------------------/\n";
	std::cout << "Enter [1] to input an expression in infix notation.\n"
		<< "Enter [2] to input an expression in postfix notation.\n"
		<< "Enter [3] to build a tree.\n"
		<< "Enter [4] to print the tree.\n"
		"Enter [0] to exit\n";
	std::cout << "Your choice: ";
}
int main() {
	
	short menu;
	bool flag = true;
	printMenu(true);
	binarySearchTree* tree = new binarySearchTree;
	while (flag) {

		std::cin >> menu;

		switch (menu) {
		case 1: {
			//
			break;
		}
		}
	}
}


