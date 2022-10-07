#include "BinaryWithHash.h"


void insertObjectFromBinary(string& nameOfFile,string& license,HashItem* table, HashTable* table2 ) {
	
	HashItem item;

	item.companyItem = *findByKey(nameOfFile, license,&item);

	insert(item, license, table2->tablesize, table,table2);
}
void deleteObjectFromHashAndBinary(string& nameOfFile, string& license, HashItem* &table, HashTable* table2) {

	delItem(license,table2->tablesize,table,table2);


	replaceObject(nameOfFile, license);
}

companyStruct getObjectFromFIle(string& nameOfFile, string& license, HashItem* table, HashTable* table2) {

	ifstream file(nameOfFile, ios::in | ios::out, ios::binary);

	HashItem* obj = findKey(license,table2->tablesize,table);
	int index = obj->indexInFile;
	companyStruct company;
	file.seekg(index * sizeof(companyStruct), ios::beg);
	companyStruct object;
	file.read((char*)&object, sizeof(companyStruct));
	return object;
}
char gen_random(const int len) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(len);

	return alphanum[rand() % (sizeof(alphanum) - 1)];
	

}

void fillwithmillion(HashItem* item,int tablesize,HashItem* table,HashTable* table2) {
	string lic = convertChar(item->companyItem.license);
	insert(*item, lic, tablesize, table, table2);
	char a[10];
	for (int i = 0; i < 10; i++) {
		a[i] = gen_random(1);
	}
	for (int i = 0; i < pow(10, 6); i++) {
		

		insert(*item, lic, tablesize, table, table2);
	}
		
}
void fillFromBinary(string& nameOfFile, int tablesize, HashItem* table, HashTable* table2) {
	ifstream binaryFile(nameOfFile, ios::binary);
	companyStruct companyObject;
	HashItem* temp = new HashItem;
	int index;
	int counter = -1;
	while (binaryFile.read((char*)&companyObject, sizeof(companyStruct))) {
		counter++;
		temp->companyItem = companyObject;
		string lic = convertChar(companyObject.license);
		temp->indexInFile = counter;
		insert(*temp, lic, tablesize, table, table2);
	}

}