#include <string>
#include <vector>
#include <iostream>
#include <fstream>
struct companyStruct {
	char license[30];
	char company_name[30];
	char founder[30];
	short license_condition;

};
struct HashItem {
	int id;
	int numberWithKey = 1;
	companyStruct companyItem;
	HashItem* nextItem = nullptr;
	int flag = 0;
	int indexInFile = 0;
};
using namespace std;


int fillObjectStructInfo(string& nameOfFile, companyStruct& companyObject) {

	ofstream file(nameOfFile, ios::app);
	if (file.is_open()) {
		file << companyObject.license;
		file << endl;
		file << companyObject.company_name;
		file << endl;
		file << companyObject.founder;
		file << endl;
		file << companyObject.license_condition;
		file << endl;
		file.clear();
		file.close();
	}
	else {
		return 0;
	}
	return 1;
}

void fromTextToBinary(string& textFile, string& binaryFile) {

	companyStruct companyObject;

	ifstream TF(textFile);
	ofstream BF(binaryFile, ios::binary);

	while (TF.getline(companyObject.license, 30), TF.getline(companyObject.company_name, 30),
		TF.getline(companyObject.founder, 30), TF >> companyObject.license_condition) {

		BF.write((char*)&companyObject, sizeof(companyStruct));
		TF.get();
	}

	TF.close();
	BF.close();

}

void fromBinaryToText(string& textFile, string& binaryFile) {

	ofstream TF(textFile);
	ifstream BF(binaryFile, ios::binary);
	companyStruct companyObject;


	while (BF.read((char*)&companyObject, sizeof(companyStruct))) {

		TF << companyObject.license;
		TF << endl;
		TF << companyObject.company_name;
		TF << endl;
		TF << companyObject.founder;
		TF << endl;
		TF << companyObject.license_condition;
		TF << endl;
	}

	TF.close();
	BF.close();

}

void printObject(companyStruct companyObject) {

	cout << companyObject.license << '\t'
		<< companyObject.company_name << '\t'
		<< companyObject.founder << '\t'
		<< companyObject.license_condition << '\t';
}

void printBinaryFile(string& nameOfFile) {

	ifstream binaryFile(nameOfFile, ios::binary);
	companyStruct companyObject;
	while (binaryFile.read((char*)&companyObject, sizeof(companyStruct))) {
		cout << companyObject.license << '\n'
			<< companyObject.company_name << '\n'
			<< companyObject.founder << '\n'
			<< companyObject.license_condition << '\n';
	}
	binaryFile.close();
}

companyStruct getObjectByIndex(string& nameOfFile, short position) {

	ifstream file(nameOfFile, ios::binary);
	companyStruct companyObject;

	file.seekg((position - 1) * sizeof(companyStruct), ios::beg);
	file.read((char*)&companyObject, sizeof(companyStruct));


	file.close();

	return companyObject;
}

companyStruct* findByKey(string& nameOfFile, string& license, HashItem* hashitem) {
	
	int counter = 0;
	ifstream binaryFile(nameOfFile, ios::binary);
	companyStruct companyObject;

	while (binaryFile.read((char*)&companyObject, sizeof(companyStruct))) {
		if (companyObject.license == license) {
			if (hashitem != nullptr)
				hashitem->indexInFile = counter;

			return &companyObject;
			
		}
	}
	return nullptr;

}
short replaceObject(string& nameOfFile, string key) {

	fstream file(nameOfFile, ios::binary | ios::out | ios::in);
	companyStruct companyObject;
	bool flag = false;
	short index = 0;
	while (file.read((char*)&companyObject, sizeof(companyStruct))) {
		if (companyObject.license == key) {
			flag = true;
			break;
		}
		index++;
	}
	if (!flag) {
		return 0;
	}
	companyStruct companyObjectLast;

	file.seekg(3 * sizeof(companyStruct), ios::beg);
	file.read((char*)&companyObjectLast, sizeof(companyStruct));

	file.seekp(3 * sizeof(companyStruct), ios::beg);
	file.write((char*)&companyObject, sizeof(companyStruct));


	file.seekp(index * sizeof(companyStruct), ios::beg);
	file.write((char*)&companyObjectLast, sizeof(companyStruct));


	file.close();
	return 1;
}

void formLicenseList(string& nameOfFile, string& founderName, string& nameOfSecondFile) {

	ifstream file(nameOfFile, ios::binary);
	ofstream file2(nameOfSecondFile);
	companyStruct companyObject;
	while (file.read((char*)&companyObject, sizeof(companyStruct))) {
		if (companyObject.founder == founderName) {
			file2 << companyObject.license;
			file2 << endl;
		}
	}
	file.close();
	file2.close();

}
void devalidateLicenses(string& nameOfFile, string& nameOfFileWithIndexes) {


	fstream file(nameOfFile, ios::binary | ios::in | ios::out);
	string index;
	int temp;
	companyStruct companyObject;
	short counter = 0;
	ifstream fileWithIndexes(nameOfFileWithIndexes);
	while (getline(fileWithIndexes, index)) {

		temp = stoi(index);
		file.seekg(temp * sizeof(companyStruct), ios::beg);

		file.read((char*)&companyObject, sizeof(companyStruct));

		companyObject.license_condition = 0;
		file.seekp((temp) * sizeof(companyStruct), ios::beg);
		file.write((char*)&companyObject, sizeof(companyStruct));

	}
	file.close();
	fileWithIndexes.close();
}