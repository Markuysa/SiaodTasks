#include "FirstTask.h"
#include <vector>
struct company_struct{
	char license[30];
	char company_name[30];
	char founder[30];
	short license_condition;

};

int fillObjectStructInfo(string& nameOfFile, company_struct& companyObject) {

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

void fromTextToBinary(string& textFile,string& binaryFile) {
		
	company_struct companyObject;

	ifstream TF(textFile);
	ofstream BF(binaryFile, ios::binary);
	
	while (TF.getline(companyObject.license,30), TF.getline(companyObject.company_name, 30),
		TF.getline(companyObject.founder, 30), TF >> companyObject.license_condition) {

		BF.write((char*)&companyObject, sizeof(company_struct));
		TF.get();
	}
	
	TF.close();
	BF.close();

}

void fromBinaryToText(string& textFile, string& binaryFile) {

	ofstream TF(textFile);
	ifstream BF(binaryFile, ios::binary);
	company_struct companyObject;
	

	while (BF.read((char*)&companyObject, sizeof(company_struct))) {

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

void printObject(company_struct& companyObject) {

	cout << companyObject.license << '\n'
		<< companyObject.company_name << '\n'
		<< companyObject.founder << '\n'
		<< companyObject.license_condition << '\n';
}

void printBinaryFile(string& nameOfFile) {

	ifstream binaryFile(nameOfFile, ios::binary);
	company_struct companyObject;
	while (binaryFile.read((char*)&companyObject, sizeof(company_struct))) {
		printObject(companyObject);
	}
	binaryFile.close();
}

company_struct getObjectByIndex(string& nameOfFile, short position) {

	ifstream file(nameOfFile,ios::binary);
	company_struct companyObject;

	file.seekg((position-1) * sizeof(company_struct), ios::beg);
	file.read((char*)&companyObject, sizeof(company_struct));


	file.close();
	
	return companyObject;
}


short replaceObject(string& nameOfFile,string key) {
	
	fstream file(nameOfFile, ios::binary|ios::out|ios::in);
	company_struct companyObject;
	bool flag = false;
	short index = 0;
	while (file.read((char*)&companyObject, sizeof(company_struct))) {
		if (companyObject.license == key) {
			flag = true;
			break;
		}
		index++;
	}
	if (!flag) {
		return 0;
	}
	company_struct companyObjectLast;

	file.seekg(3 * sizeof(company_struct),ios::beg);
	file.read((char*)&companyObjectLast, sizeof(company_struct));

	file.seekp(3 * sizeof(company_struct), ios::beg);
	file.write((char*)&companyObject, sizeof(company_struct));


	file.seekp(index * sizeof(company_struct), ios::beg);
	file.write((char*)&companyObjectLast, sizeof(company_struct));


	file.close();
	return 1;
}

 void formLicenseList(string& nameOfFile,string& founderName,string& nameOfSecondFile) {
	
	 ifstream file(nameOfFile, ios::binary);
	 ofstream file2(nameOfSecondFile);
	 company_struct companyObject;
	 while (file.read((char*)&companyObject, sizeof(company_struct))) {
		 if (companyObject.founder == founderName) {
			 file2 << companyObject.license;
			 file2 << endl;
		 }
	 }
	 file.close();
	 file2.close();
	
 }

 void devalidateLicenses(string& nameOfFile,string& nameOfFileWithIndexes) {


	fstream file(nameOfFile, ios::binary|ios::in | ios::out);
	string index;
	int temp;
	company_struct companyObject;
	short counter = 0;
	ifstream fileWithIndexes(nameOfFileWithIndexes);
	while (getline(fileWithIndexes,index)) {

		temp = stoi(index);
		file.seekg(temp*sizeof(company_struct), ios::beg);

		file.read((char*)&companyObject, sizeof(company_struct));

		companyObject.license_condition = 0;		
		file.seekp((temp) * sizeof(company_struct), ios::beg);
		file.write((char*)&companyObject, sizeof(company_struct));

	}
	file.close();
	fileWithIndexes.close();
 }