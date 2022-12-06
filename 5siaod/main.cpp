#include "Tests.h"
#include <time.h>
void printMenu(bool condition)
{
	if (condition) {
		cout << "\t\nPractical work #4 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Expression tree.\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	cout << "/------------------------FILES-------------------------/\n";
	cout << "Enter [1] to create a binary file from text file\n"
		<< "Enter [2] to start linear search by the key.\n"
		<< "Enter [3] to print an object from the file by index(pointer).\n"
		<< "Enter [4] to add an object to the file.\n"
		<< "Enter [5] to print your binary file.\n";
	cout << "/------------------------BINARY-TREE-------------------------/\n";
	cout << "Enter [6] to build a tree from binary file.\n"
		<< "Enter [7] to add an object to the tree.\n"
		<< "Enter [8] to search an object by the key.\n"
		<< "Enter [9] to delete an object from the tree\n"
		<< "Enter [10] to print the tree\n";
	cout << "/------------------------AVL-TREE-------------------------/\n";
	cout << "Enter [11] to create an AVL tree from binary file\n"
		<< "Enter [12] to add an object to the tree.\n"
		<< "Enter [13] to search an element by key.\n"
		<< "Enter [14] to delete an object from the tree\n"
		<< "Enter [15] to print the tree\n"
		<< "Enter [16] to output the count of rotates\n"
		"Enter [0] to exit\n"
		"Enter [-1] to clean console\n";
	cout << "Your choice: ";
}
int main() {
	binarySearchTree* binaryTree = new binarySearchTree;
	balansedSearchTree* balansedTree = new balansedSearchTree;
	AVLTree* avlTree = new AVLTree;
	int sizeBalansedTree=0;
	short menu;
	bool flag = true;
	printMenu(true);
	string nameOfFileBinary;
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

			clock_t start = clock();
			company_struct* object = findByKey(nameOfFileBinary, key);
			clock_t end = clock();
			double seconds = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "The worktime: " << seconds << endl;
			//printObject(object);
			if (object==nullptr) {
				cout << "Your object was not found" << endl;
				break;
			}
			break;
		}
		case 3: {
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
			company_struct companyObject;
			cout << "Input license: ";
			cin >> companyObject.license;
			cout << "Input name: ";
			cin >> companyObject.company_name;
			cout << "Input founder: ";
			cin >> companyObject.founder;
			addObjectToFile(nameOfFileBinary,companyObject);
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
			binaryTree->addItem(root, &companyObject,0);
			addObjectToFile(nameOfFileBinary, companyObject);
			break;
		}
		case 8: {
			string key;
			cout << "Input the key: ";
			cin >> key;
			clock_t start = clock();
			TreeNode* result = binaryTree->searchElement(binaryTree->getRoot(), key);
			clock_t end = clock();
			double seconds = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "The worktime: " << seconds << endl;
			//printTreeObject(result);

			break;
		}
		case 9: {
			cout << "Enter the key: " << endl;
			string key;
			cin >> key;
			binaryTree->setRoot(binaryTree->DeleteNode(binaryTree->getRoot(), key));

			break;
		}
		case 10: {
			outputTree(binaryTree->getRoot(), binaryTree->getCountOfELements());
			break;
		}
		case 11: {
			cout << "Input the name of your binary file: ";
			cin >> nameOfFileBinary;
			avlTree->buildFromFile(avlTree->getRoot(),nameOfFileBinary,0);
			break;
		}
		case 12: {
			company_struct companyObject;
			cout << "Input license: ";
			cin >> companyObject.license;
			cout << "Input name: ";
			cin >> companyObject.company_name;
			cout << "Input founder: ";
			cin >> companyObject.founder;
			TreeNode* root = avlTree->getRoot();
			avlTree->addItem(root, &companyObject,0);
			addObjectToFile(nameOfFileBinary, companyObject);
			break;
		}
		case 13: {
			string key;
			cout << "Input the key: ";
			cin >> key;
			clock_t start = clock();
			TreeNode* result = avlTree->searchElement(avlTree->getRoot(), key);
			clock_t end = clock();
			double seconds = (double)(end - start) / CLOCKS_PER_SEC;
			cout << "The worktime: " << seconds << endl;
			if (result == nullptr)
				cout << "The object was not found:<"<<endl;
			else printTreeObject(result);

			break;
		}
		case 14: {
			string key;
			cout << "Input the key: ";
			cin >> key;
			//avlTree->deleteElement(avlTree->getRoot(), key);
			break;
		}
		case 15: {
			outputTree(avlTree->getRoot(), avlTree->heightTree);
			break;

		}
		case 16: {
			nameOfFileBinary = "5.bin";
			TEST_BuildTree_ByDeafult_ReturnsTrue(avlTree, nameOfFileBinary);
			break;
		}
		case 0: exit(0);
		case -1: {
			system("cls");
			break;
		}
		}
		printMenu(false);
	}
}


