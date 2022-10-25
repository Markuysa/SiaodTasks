#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int createFile(string& nameOfFile) {
	ofstream file(nameOfFile);
	if (file.is_open()) {
		file << 213 << ' ' << 124 << ' ' << 112 << endl;
		file << 213 << ' ' << 124 << endl;
		file << 112 << endl;
		file << 213 << ' ' << 124 << ' ' << 112 << endl;
		file.close();
	}
	else {
		return 0;
	}
	return 1;
}

int readFile(string& nameOfFile) {
	string line;
	ifstream file(nameOfFile,ios::_Nocreate);
	if (file) {
		cout << "Your file:\n";
		while (!file.eof()) {
			getline(file, line);
			cout << line << endl;
		}
		file.close();
	}
	else {
		return 0;
	}
	return 1;
}

int inputStringFile(string& nameOfFile, string& line) {

	ofstream file(nameOfFile, ios::_Nocreate|ios::app);
	if (file) {
		file << line;
		file.close();
		return 1;
	}
	else {
		return 0;
	}
}

unsigned countOfNumbers(string& nameOfFile) {
	ifstream file(nameOfFile);
	string line;
	bool flag = true;
	unsigned counter = 0;
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			for (size_t i = 0; i < line.size(); i++) {
				if (line[i] >= '0' && line[i] <= '9') {
					flag = true;
					if (i > 0)
						if (line[i - 1] < '0' || line[i - 1]>'9') flag = false;
						else flag = true;

				}
				else {
					if ((line[i] == ' ') && flag)
						counter++;
					else flag = false;
				}
				if (i == line.size() - 1 && flag) counter++;
			}

		}

	}
	else { cout << "Error of opening the " << nameOfFile << endl; }
	file.close();
	return counter;
}

int findFirstEven(string& fileName) {
	ifstream file(fileName);
	string num = "", line;

	int counter = 0, result;
	if (file.is_open()) {
		getline(file, line);

		for (size_t i = 0; i < line.size(); i++) {
			if (line[i] >= '0' && line[i] <= '9')
				num += line[i];
			else
				if (line[i] == ' ' && stoi(num) % 2 == 0)
					return stoi(num);
				else
					num = "";
		}
	}
	file.close();
	return 0;
}

string findNumber(string& nameOfFile, int numberIndex) {
	fstream file(nameOfFile);
	string num = "";
	size_t counter = 0;
	string line;
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, line);
			for (size_t i = 0; i < line.size(); i++) {
				if (line[i] <= '9' && line[i] >= '0')
					num += line[i];
				else {
					if (line[i] == ' ') {
						counter++;
						if (counter == numberIndex) {
							return num;
						}
						num = " ";
					}
				}
				if (i == line.size() - 1) {
					counter++;
					num = " ";
				}
			}
		}
	}
	file.close();
}

void newFile1Variant(string& firstFile, string& secondFile) {
	ifstream file1(firstFile);
	ofstream file2(secondFile);
	int firstEven = findFirstEven(firstFile), result;
	string num = "";
	string line;
	if (file1.is_open()) {
		while (!file1.eof()) {

			getline(file1, line);
			for (size_t i = 0; i < line.size(); i++) {
				if (line[i] >= '0' && line[i] <= '9')
					num += line[i];
				else {
					if (line[i] == ' ') {
						result = stoi(num) + firstEven;
						file2 << result;
						file2 << " ";
						num = "";
					}
				}
				if (i == line.size() - 1) {
					if (line[i] > '9' || line[i] < '0') {
						file2 << line;
						return;
					}
				
					result = stoi(num) + firstEven;
					file2 << result;
					file2 << " ";
					num = "";
				}

			}
			file2 << endl;
		}
	}
	file1.close();
	file2.close();
}
