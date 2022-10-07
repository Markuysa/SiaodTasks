#include "BinarFileWithHash.h"
void test(int menu,HashTable* table){
switch (menu) {
		case 1: {
			companyStruct companyObject;
			cout << "Input license: ";
			cin >> companyObject.license;
			cout << "Input name: ";
			cin >> companyObject.company_name;
			cout << "Input founder: ";
			cin >> companyObject.founder;
			cout << "Input license condition: ";
			cin >> companyObject.license_condition;
			cin.clear();
			HashItem item;
			item.companyItem = companyObject;
			string lic = convertChar(companyObject.license);
			//fillwithmillion(&item,table->tablesize,table->table,table);
			insert(item, lic, table->tablesize, table->table, table);
			break;
		}
		case 2: {
			string nameOFFIle;
			cout << "Input the name of your file: ";
			cin >> nameOFFIle;
			fillFromBinary(nameOFFIle, table->tablesize, table->table, table);
			break;
		}
		case 3: {
			outputTable(table->tablesize, table->table);
			break;
		}
		case 4: {
			string key;
			cout << "Input the key: ";
			cin >> key;
			HashItem* result = findKey(key, table->tablesize, table->table);
			if (result == nullptr)
				cout << "Your object doesn't exist" << endl;
			else {
				cout << "The result object is: " << endl
					/*<< "Id: " << result->id << endl*/
					<< "License: " << result->companyItem.license << endl
					<< "Company name " << result->companyItem.company_name << endl
					<< "Founder name: " << result->companyItem.founder << endl
					<< "License condition: " << result->companyItem.license_condition << endl;

			}
			break;

		}
		case 5: {
			string key;
			cout << "Input the key: ";
			cin >> key;
			delItem(key, table->tablesize, table->table, table);
			table->tablesize--;
			break;
		}
		case 6: {
			rehash(table->tablesize, table->table, table);
			break;
		}
		case 7: {
			string nameOfFile, license;
			cout << "Input the name of file: ";
			cin >> nameOfFile;

			cout << "Input the key: ";
			cin >> license;

			insertObjectFromBinary(nameOfFile, license, table->table, table);
			break;
		}
		case 8: {
			string nameOfFile, license;
			cout << "Input the name of file: ";
			cin >> nameOfFile;

			cout << "Input the key: ";
			cin >> license;
			deleteObjectFromHashAndBinary(nameOfFile, license, table->table, table);
			break;
		}
		case 9: {
			string nameOfFile, license;
			cout << "Input the name of file: ";
			cin >> nameOfFile;

			cout << "Input the key: ";
			cin >> license;
			companyStruct obj = getObjectFromFIle(nameOfFile, license, table->table, table);
			printObject(obj);
			break;
		}
	}
}