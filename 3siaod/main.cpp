

#include "testHashB.h"

void printMenu(bool condition)
{
	if (condition) {
		cout << "\t\nPractical work #3 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Hash tables.\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	cout << "/------------------------FIRST-TASK-------------------------/\n";
	cout << "Enter [1] to insert an item in your hash-table.\n"
		"Enter [2] to fill the table from binary file\n"
		"Enter [3] to print the table\n"
		"Enter [4] to find the object with selected key\n"
		"Enter [5] to delete the object by the key\n"
		"Enter [6] to rehash the table\n"
		"/------------------------Binary Files with Hash------------------------/\n"
		"Enter [7] to insert an object from binary file to your table by key\n"
		"Enter [8] to delete the object from your file and from the table by the key\n"
		"Enter [9] to get an object from file by key with hash\n"
		"/------------------------Binary Files------------------------/\n"
		"Enter [10] to convert text file to binary\n"
		"Enter [11] to convert binary file to text\n"
		"Enter [12] to read all information from the binary file\n"
		"Enter [13] to get an object from a binary file by index\n"
		"Enter [14] to replace an object with inputed index from the binary file by last \n"
		"Enter [15] to get a list of licenses of the entered founder \n"
		"Enter [16] to to revoke a license for objects with specified indexes\n"
		"Enter [17] to fill object info to the text file\n";
		"Enter [0] to exit\n";
	cout << "Your choice: ";
}

int main() {
	int menu;
	cout << "Input 'START' to run the programm\n";
	string condition;
	cin >> condition;
	if (condition == "START") {
		int size;
		cout << "Enter the size of your hash table: " << endl;
		cin >> size;
		HashTable* table = new HashTable(size);
		printMenu(true);
		while (true) {
			cin >> menu;
			menu< 10 ? test(menu, table): testHashB(menu, table);
			printMenu(false);
		}
	}
	else { cout << "ERROR" << endl; }
}
