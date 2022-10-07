#pragma once
#include "testHashT.h"
void testHashB(int menu, HashTable* table) {
	switch (menu) {
	case 10: {
		string textFile, binaryFile;
		cout << "Enter the name of your text file: ";
		cin >> textFile;
		cout << "Enter the name of your binary file: ";
		cin >> binaryFile;

		fromTextToBinary(textFile, binaryFile);
		break;
	}
	case 11: {
		string textFile, binaryFile;
		cout << "Enter the name of your text file: ";
		cin >> textFile;
		cout << "Enter the name of your binary file: ";
		cin >> binaryFile;

		fromBinaryToText(textFile, binaryFile);
		break;
	}
	case 12: {
		string binaryFile;
		cout << "Enter the name of your binary file: ";
		cin >> binaryFile;

		printBinaryFile(binaryFile);
		break;
	}
	case 13: {
		string binaryFile;
		cout << "Enter the name of your binary file: ";
		cin >> binaryFile;

		short index;
		cout << "Enter the index: ";
		cin >> index;

		companyStruct companyObject = getObjectByIndex(binaryFile, index);
		if (companyObject.license_condition != -13108)
			printObject(companyObject);
		else
			cout << "No object with that index :(" << endl;

		break;
	}
	case 14: {
		string binaryFile;
		cout << "Enter the name of your binary file: ";
		cin >> binaryFile;
		cout << "Enter the key (license number): ";
		string license;
		cin >> license;;

		replaceObject(binaryFile, license);

		break;
	}
	case 15: {
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
	case 16: {
		string textFile;
		cout << "Input the name of your file: ";
		cin >> textFile;

		string textFile2;
		cout << "Input the name of your file with indexes: ";
		cin >> textFile2;

		devalidateLicenses(textFile, textFile2);
		break;
	}
	case 17: {
		string textFile;
		cout << "Input the name of your file: ";
		cin >> textFile;
		companyStruct companyObject;
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
}