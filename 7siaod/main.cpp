#include "Test.h"

void printMenu(bool condition)
{
	if (condition) {
		cout << "\t\nPractical work #7 IKBO-10-21 Kushkhov I.A. V12\n\n"
			"Theme: Compression algorithms\n"
			"~-~-~-~-~-~-~-~-~-~-~-~-~-~-~MENU~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n\n";
	}
	cout << "/------------------------OPTIONS-------------------------/\n";
	cout << "Enter [1] to start test of RLE algo.\n"
		<< "Enter [2] to start test of LZ77 algo.\n"
		<< "Enter [3] to start test of LZ78 algo.\n"
		<< "Enter [4] to start test of Huffman's compression algo.\n"
		<< "Enter [5] to start test of Shannon-Fano compression algo.\n"
		<< "Enter [6] to start Huffman decompression.\n"
		<< "Enter [7] to start Shannon-Fano decompression.\n"
		<< "Enter [8] to start Huffman decompression from file.\n"
		<< "Enter [9] to start Shannon-Fano decompression from file.\n"
		<< "Enter [0] to exit\n"
		<< "Enter [-1] to clean the console\n";
	cout << "Your choice: ";
}
int main() {
	HuffmanTree huffmanTree;
	ShannonFanoTree shannonFanoTree;
	int menu;
	bool flag = true;
	string uncompressedLine = "";
	printMenu(true);
	while (flag) {
		cin >> menu;
		switch (menu){

		case 1: {
			cout << "Input the uncompressed string: ";
			cin.ignore();
			getline(cin,uncompressedLine);
			compressionRatioRLETest(uncompressedLine);
			break;
		}
		case 2: {
			cout << "Input the uncompressed string: ";
			cin.ignore();
			getline(cin, uncompressedLine);
			compressionRatioLZ77Test(uncompressedLine);
			break;
		}
		case 3: {
			cout << "Input the uncompressed string: ";
			cin.ignore();
			getline(cin, uncompressedLine);
			compressionRatioLZ78Test(uncompressedLine);
			break;
		}
		case 4: {
			cout << "Input the uncompressed string: ";
			cin.ignore();
			getline(cin, uncompressedLine);
			compressionRatioHuffmanTest(uncompressedLine);
			break;
		}
		case 5: {
			cout << "Input the uncompressed string: ";
			cin.ignore();
			getline(cin, uncompressedLine);
			compressionRatioShannonFanoTest(uncompressedLine);
			break;
		}
		case 6: {
			string decompressedLine;
			testDecompressHuffman(uncompressedLine);
			break;
		}
		case 7: {
			string decompressedLine;
			testDecompressShannonFano(uncompressedLine);
			break;
		}
		case 8: {
			string nameOfFile;
			cout << "Input the file name: ";
			cin >> nameOfFile;

			testHuffmanFromFile(nameOfFile);
			break;
		}	
		case 9: {
			string nameOfFile;
			cout << "Input the file name: ";
			cin >> nameOfFile;

			testShannonFanoFromFile(nameOfFile);
			break;


		}
		case 0:{
			exit(0);
		}
		case -1: {
			system("cls");
		}
		default:
			cout << "Uncorrect option! Try again)))))))))" << endl;
			break;
		}
		printMenu(false);
	}
    
}