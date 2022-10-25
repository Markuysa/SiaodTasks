#include "AVLTree.h"
void printMenu(bool condition)
{
	if (condition) {
		cout << "\t\nPractical work #4 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Expression tree.\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	cout << "/------------------------FIRST-TASK-------------------------/\n";
	cout << "Enter [1] to create a binary file from text file\n"
		<< "Enter [2] to start linear search by the key.\n"
		<< "Enter [3] to print an object from the file by index(pointer).\n"
		<< "Enter [4] to add an object to the file.\n"
		<< "Enter [5] to print your binary file.\n";
	cout << "/------------------------Second-TASK-------------------------/\n";
	cout << "Enter [6] to build a tree from file.\n"
		<< "Enter [7] to add an object to the tree.\n"
		<< "Enter [8] to search an object by the key.\n"
		<< "Enter [9] to delete an object from the tree\n"
		<< "Enter [10] to print the tree\n";
	cout << "/------------------------THIRD-TASK-------------------------/\n";
	cout << "Enter [11] to create a balansed tree\n"
		<< "Enter [12] to input an expression in postfix notation.\n"
		<< "Enter [13] to build a tree.\n"
		<< "Enter [14] to print the tree.\n"
		"Enter [0] to exit\n";
	cout << "Your choice: ";
}
int main() {
	binarySearchTree* binaryTree = new binarySearchTree;
	balansedSearchTree* balansedTree = new balansedSearchTree;
	short menu;
	bool flag = true;
	printMenu(true);
	while (flag) {

		cin >> menu;

		switch (menu) {
		case 1: {
			string nameOfFileText, nameOfFileBinary ;
			cout << "Input the name of your text file: ";
			cin >> nameOfFileText;
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;

			fromTextToBinary(nameOfFileText, nameOfFileBinary);

			break;
		}
		case 2: {
			string nameOfFileBinary,key;
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;
			cout << "Input the key: ";
			cin >> key;
			company_struct* object = findByKey(nameOfFileBinary, key);
			printObject(object);
			if (object==nullptr) {
				cout << "Your object was not found" << endl;
				break;
			}
			break;
		}
		case 3: {
			string nameOfFileBinary;
			short index;
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;
			cout << "Input the position: ";
			cin >> index;
			company_struct object = getObjectByIndex(nameOfFileBinary, index);
			printObject(&object);
			break;
		}
		case 4: {
			string nameOfFileBinary;
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;
			addObjectToFile(nameOfFileBinary);
			break;
		}
		case 5: {
			string nameOfFileBinary;
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;
			printBinaryFile(nameOfFileBinary);
			break;
		}
		case 6: {
			string nameOfFileBinary;
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;
			binaryTree->buildFromFile(binaryTree->getRoot(), nameOfFileBinary);
			break;
		}
		case 7:{
			company_struct companyObject;
			cout << "Input license: ";
			cin >> companyObject.license;
			cout << "Input name: ";
			cin >> companyObject.company_name;
			cout << "Input founder: ";
			cin >> companyObject.founder;
			TreeNode* root = binaryTree->getRoot();
			binaryTree->addItem(root, &companyObject);
			break;
		}
		case 8: {
			
			break;
		}
		case 9: {
			//delete
			break;
		}
		case 10: {
			TreeNode* root = binaryTree->getRoot();
			binaryTree->printTree(root, nullptr, false);
			break;
		}
		case 11: {
			int size;
			cout << "Input the size of your tree: ";
			cin >> size;
			string nameOfFileBinary;
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;
			balansedTree->setRoot(balansedTree->buildFromFile(balansedTree->getRoot(),nameOfFileBinary,size,0));
			outputTree(balansedTree->getRoot(), 8);
			break;
		}
		case 14: {
/*			TreeNode* root = balansedTree->getRoot();
			balansedTree->printTree(root, nullptr, false);
			break;*/ 
		}
		}
		printMenu(false);
	}
}


