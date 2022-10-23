#pragma once
#include <iostream>
#include <fstream>
#include <string>
struct company_struct {
	char license[30];
	char company_name[30];
	char founder[30];

};
int addObjectToFile(std::string& nameOfFile, company_struct& companyObject) {

	std::ofstream file(nameOfFile, std::ios::app);
	if (file.is_open()) {
		file << companyObject.license;
		file << std::endl;
		file << companyObject.company_name;
		file << std::endl;
		file << companyObject.founder;
		file << std::endl;
		file.clear();
		file.close();
	}
	else {
		return 0;
	}
	return 1;
}
void fromTextToBinary(std::string& textFile, std::string& binaryFile) {

	company_struct companyObject;

	std::ifstream TF(textFile);
	std::ofstream BF(binaryFile, std::ios::binary);

	while (TF.getline(companyObject.license, 30), TF.getline(companyObject.company_name, 30),
		TF.getline(companyObject.founder, 30)) {

		BF.write((char*)&companyObject, sizeof(company_struct));
		TF.get();
	}

	TF.close();
	BF.close();

}

company_struct* findByKey(std::string& nameOfFile,std::string& key) {

	std::ifstream file(nameOfFile);
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
void printObject(company_struct& companyObject) {

	std::cout << companyObject.license << '\n'
		<< companyObject.company_name << '\n'
		<< companyObject.founder << '\n';
}


// Что значит по известному адресу епт

