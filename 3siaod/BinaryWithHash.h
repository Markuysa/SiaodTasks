#pragma once
#include <iostream>
#include <vector>
#include "SecondTask.h"
using namespace std;



struct HashTable {
	int countOfElemets = 0;
	int tablesize;
	int sizeofEl;
	HashItem* table;

	HashTable(int size) {
		this->tablesize = size;
		this->sizeofEl = size;
		table = new HashItem[tablesize];
	}
};

int hash_function(string& license,int tablesize) {

	int asciiSum = 0;
	for (size_t i = 0; i < license.size(); i++) {
		asciiSum += license[i];
	}

	return tablesize == 0 ? 0 : asciiSum % tablesize;
}

HashItem* findKey(string& key,int tablesize,HashItem* table) {
	int index = hash_function(key,tablesize);

	HashItem* obj = &table[index];
	if (obj->companyItem.license == key)
		return obj;
	while (obj->nextItem != nullptr) {
		obj = obj->nextItem;
		if (obj->companyItem.license == key)
			return obj;
	}
	return nullptr;
}

void delItem(string& key, int tablesize, HashItem* &table,HashTable* table2) {
	int index = hash_function(key, tablesize);
	
	HashItem* obj = &table[index];

	if (obj->companyItem.license == key) {
		HashItem* newmas = new HashItem[tablesize - 1];

		for (size_t i = index + 1; i < tablesize; i++) {
			newmas[i-1] = table[i];
		}
		if (index != 0) {
			for (size_t i = 0; i < index; i++) {
				newmas[i] = table[i];
			}
		}
		delete[] table;

		table = newmas;
	}
	else {
		HashItem* prev=&table[index];
		HashItem* next = prev->nextItem;
		while (next != nullptr) {
			if (next->companyItem.license == key) {
				prev->nextItem = nullptr;
				delete next;
				break;
			}
			prev = next;
			next = prev == nullptr ?prev->nextItem:nullptr;
		}
	}
}

string convertChar(char* license) {

	string result = "";
	for (int i = 0; i < 30; i++) {
		if (license[i] == -52) return result;
		result += license[i];
	}
	return result;
}

void outputTable(int tablesize, HashItem* table) {
	int size = tablesize;
	string line = "----------------------------------\n";
	cout << "INDEX/LICENSE/COMPANY_NAME/FOUNDER_NAME/LICENSE_CONDITION/PLACE" << endl;
	for (size_t i = 0; i < size; i++) {
		if (table[i].flag!=0) {
			cout << line;
			cout << table[i].id << " ";
			printObject(table[i].companyItem);
			cout << table[i].indexInFile<<"|";
			cout << endl;
			HashItem* obj = &table[i];
			cout << line;
			while (obj->nextItem != nullptr) {
				if (obj->flag == 0 || obj->flag == 1) {
					cout << "\n\t" + line;

					obj = obj->nextItem;
					cout << "\t";
					
					cout <<"|" << obj->id << " ";
					printObject(obj->companyItem);
					cout << obj->indexInFile<<"|";
					cout << "\n\t"+line;
				}
				else {
					break;
				}
				
			}
		}
		else {
			cout << line;
		}

	}

}

void insert(HashItem hashItem, string& key, int& tablesize, HashItem* &table,HashTable* table2) {
	HashItem* temp=new HashItem;
	int index;
	companyStruct companyObject = hashItem.companyItem;
	string license = convertChar(companyObject.license);
	index = hash_function(license,tablesize);
	temp->companyItem = companyObject;
	temp->id = index;
	temp->indexInFile = hashItem.indexInFile;
	if (table[index].flag!=0){
		table[index].numberWithKey = (table[index].numberWithKey + 1);
		HashItem* obj = &table[index];
		while (obj->nextItem != nullptr) {
			obj = obj->nextItem;
		}
		obj->nextItem = temp;
		table2->sizeofEl++;
		
	}
	else {
		temp->flag = 1;
		table[index] = *temp;

	}

}



void rehash(int newtablesize, HashItem* &table,HashTable* table2) {
	int size = table2->tablesize;
	newtablesize = size + size / 2;
	HashItem* newmas = new HashItem[newtablesize];
	int index;
	string license;
	for (size_t i = 0; i < table2->tablesize; i++) {
		license = convertChar(table[i].companyItem.license);
		if (table[i].nextItem == nullptr) {
			insert(table[i], license, newtablesize, newmas,table2);
		}
		else {
			HashItem* obj = &table[i];
			while (obj!= nullptr) {
				insert(*obj, license, newtablesize, newmas,table2);
				obj = obj->nextItem;
			}
		}
	}

	table2->tablesize = newtablesize;
	delete table;
	table = newmas;

}

