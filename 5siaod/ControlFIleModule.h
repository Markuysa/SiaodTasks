#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct company_struct {
	char license[30];
	char company_name[30];
	char founder[30];

};
int addObjectToFile(string& nameOfFile,company_struct companyObject) {
	ofstream file(nameOfFile, ios::app,ios::binary);
	if (file.is_open()) {
		file.write((char*)&companyObject, sizeof(company_struct));
	}
	else {
		return 0;
	}
	return 1;
}
company_struct getObjectByIndex(string& nameOfFile, short position) {

	ifstream file(nameOfFile, ios::binary);
	company_struct companyObject;

	file.seekg((position - 1) * sizeof(company_struct), ios::beg);
	file.read((char*)&companyObject, sizeof(company_struct));


	file.close();

	return companyObject;
}
void fromTextToBinary(string& textFile, string& binaryFile) {

	company_struct companyObject;

	ifstream TF(textFile);
	ofstream BF(binaryFile, ios::binary);

	while (TF.getline(companyObject.license, 30), TF.getline(companyObject.company_name, 30),
		TF.getline(companyObject.founder, 30)) {

		BF.write((char*)&companyObject, sizeof(company_struct));
		TF.get();
	}

	TF.close();
	BF.close();

}


company_struct* findByKey(string& nameOfFile,string& key) {

	ifstream file(nameOfFile);
	company_struct companyObject;
	if (file.is_open()) {
		while (file.read((char*)&companyObject, sizeof(company_struct))) {
			if (companyObject.license == key) {
				return &companyObject;
			}
		}
	}
	return nullptr;
}
string convertChar(char* license) {

	string result = "";
	for (int i = 0; i < 30; i++) {
		if (license[i] == -52) return result;
		result += license[i];
	}
	return result;
}


void printObject(company_struct* companyObject) {
	string license = convertChar(companyObject->license);
	string name = convertChar(companyObject->company_name);
	string founder = convertChar(companyObject->founder);

	cout << license << '\n'
		<< name << '\n'
		<< founder << '\n';
}

// Что значит по известному адресу епт

void printBinaryFile(string& nameOfFile) {

	ifstream binaryFile(nameOfFile, ios::binary);
	company_struct companyObject;
	while (binaryFile.read((char*)&companyObject, sizeof(company_struct))) {
		printObject(&companyObject);
	}
	binaryFile.close();
}