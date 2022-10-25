#include <fstream>
#include <iostream>
#include <string>
#include "SecondTask.h"
using namespace std;

void printMenu(bool condition)
{
	if (condition) {
		cout << "\t\nPractical work #2 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Practice with text and binary files.\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	cout << "/------------------------FIRST-TASK-------------------------/\n";
	cout << "Enter [1] to create the file.\n"
			"Enter [2] to read information from the file\n"
			"Enter [3] to add a string in the end of your file\n"
			"Enter [4] to find the number with selected index\n"
			"Enter [5] to output the count of numbers in your file\n"
			"Enter [6] to add first even number from file2 to each number from file 1\n"
			"/------------------------SECOND-TASK------------------------/\n"
			"Enter [7] to convert text file to binary\n"
			"Enter [8] to convert binary file to text\n"
			"Enter [9] to read all information from the binary file\n"
			"Enter [10] to get an object from a binary file by index\n"
			"Enter [11] to replace an object with inputed index from the binary file by last \n"
			"Enter [12] to get a list of licenses of the entered founder \n"
			"Enter [13] to to revoke a license for objects with specified indexes\n"
			"Enter [14] to fill object info to the text file\n"
			"Enter [0] to exit\n";
	cout << "Your choice: ";
}


void main() {
	short menu;
	printMenu(true);
	cin >> menu;
	while (true) {
		switch (menu) {
			//FIrst task 
		case 1: {
			string nameOfFile;
			cout << "Enter the name of your file: ";
			cin >> nameOfFile;
			int condition = createFile(nameOfFile);
			if (condition)
				cout << "Success!!" << endl;
			else
				cout << "ERROR!" << endl;
			break;
		}
		case 2: {
			string nameOfFile;
			cout << "Enter the name of your file: ";
			cin >> nameOfFile;
			int condition = readFile(nameOfFile);
			if (condition) 
				cout << "The operation was success " << nameOfFile << endl;
			else 
				cout << "Error of opening " << nameOfFile << endl;
			break;
		}
		case 3: {
			string nameOfFile,line;
			cout << "Enter the name of your file: ";
			cin >> nameOfFile;
			cin.clear();
			cin.ignore();
			cout << "Enter the line: ";
			getline(cin, line);


			int condition = inputStringFile(nameOfFile,line);
			if (condition)
				cout << "The inputed stirng added successfully" << endl;
			else
				cout << "Error of adding your string!" << endl;
			break;
		}
		case 4: {
			string nameOfFile;
			int numberOfN;
			cout << "Enter the name of your file: ";
			cin >> nameOfFile;
			cout << "Enter the number of your digit(number): ";
			cin >> numberOfN;
			string str = findNumber(nameOfFile, numberOfN);
			cout << "Your number is: " << findNumber(nameOfFile,numberOfN) << endl;
			break;
			}
		case 5: {
			string nameOfFile;
			cout << "Enter the name of your file: ";
			cin >> nameOfFile;
			cout<<"The count of numbers in your file is: "<<countOfNumbers(nameOfFile)<<endl;
			break;	
		}
		case 6: {
			string nameOfFile1;
			cout << "Enter the name of your file1: ";
			cin >> nameOfFile1;
			string nameOfFile2;
			cout << "Enter the name of your file2: ";
			cin >> nameOfFile2;
			newFile1Variant(nameOfFile1, nameOfFile2);
			cout << "SUccess!!" << endl;
			break;
		}
			//Second task
		case 7: {
			string textFile, binaryFile;
			cout << "Enter the name of your text file: ";
			cin >> textFile;
			cout << "Enter the name of your binary file: ";
			cin >> binaryFile;

			fromTextToBinary(textFile,binaryFile);
			break;
		}
		case 8: {
			string textFile, binaryFile;
			cout << "Enter the name of your text file: ";
			cin >> textFile;
			cout << "Enter the name of your binary file: ";
			cin >> binaryFile;

			fromBinaryToText(textFile, binaryFile);
			break;
		}
		case 9: {
			string binaryFile;
			cout << "Enter the name of your binary file: ";
			cin >> binaryFile;

			printBinaryFile(binaryFile);
			break;
		}
		case 10: {
			string binaryFile;
			cout << "Enter the name of your binary file: ";
			cin >> binaryFile; 

			short index; 
			cout << "Enter the index: ";
			cin >> index;
			
			company_struct companyObject=getObjectByIndex(binaryFile,index);
			if (companyObject.license_condition != -13108)
				printObject(companyObject);
			else
				cout << "No object with that index :(" << endl;

			break;
		}
		case 11: {
			string binaryFile;
			cout << "Enter the name of your binary file: ";
			cin >> binaryFile;
			cout << "Enter the key (license number): ";
			string license;
			cin >> license;;

			replaceObject(binaryFile, license);

			break;
		}
		case 12: {
			string textFile;
			cout << "Input the name of your file: ";
			cin >> textFile;

			string textFile2;
			cout << "Input the name of file to form the result: ";
			cin >> textFile2;

			string founder;
			cout << "Input the founder's name: ";
			cin >> founder;


			formLicenseList(textFile, founder, textFile2);

			break;
		}
		case 13: {
			string textFile;
			cout << "Input the name of your file: ";
			cin >> textFile;

			string textFile2;
			cout << "Input the name of your file with indexes: ";
			cin >> textFile2;

			devalidateLicenses(textFile, textFile2);
			break;
		}
		case 14: {
			string textFile;
			cout << "Input the name of your file: ";
			cin >> textFile;
			company_struct companyObject;
			cout << "Input license: ";
			cin >> companyObject.license;
			cout << "Input name: ";
			cin >> companyObject.company_name;
			cout << "Input founder: ";
			cin >> companyObject.founder;

			cout << "Input license condition: ";
			cin >> companyObject.license_condition;

			short condition = fillObjectStructInfo(textFile, companyObject);
			if (condition) {
				cout << "Success!" << endl;
			}
			else cout << "Failure" << endl;
			break;

		}
		case 0: {
			exit(0);
		}
		default: {
			cout << "Incorrect number of the task! Try again" << endl;
		}
		}
		printMenu(false);
			cin >> menu;
	}
}
