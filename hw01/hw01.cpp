/*	Mary Karroqe
	1/24/18
	CS-2124, hw01: Caesar Cypher
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


// resets flags of a file
void resetFlags(ifstream& inFile) {
	inFile.clear();
	inFile.seekg(0);
}

// takes encrypted char and returns decrypted char
char decryptChar(char& encryptedChar, int key) {
	char decryptedChar;

	decryptedChar = int(encryptedChar) + key; // change this

	return decryptedChar;
}

// 	decrypts string ref using helper function decryptChar
void decryptString(string& encryptedString, int key, vector<string>& decryptedLines) {
	string decryptedString = "";
	for (char c : encryptedString) {
		decryptedString += decryptChar(c, key);
	}
	decryptedLines.push_back(decryptedString);
	cout << "decrypted line: " << decryptedString << endl; 
}

void reverseOrder(vector<string>& decryptedLines) {
	vector<string> reversed;
	cout << "i'm here" << endl;
	cout << "decryptedLines.size(): " << decryptedLines.size() << endl;

	// backward loop, using while because when size_t became negative values got weird
	size_t current = decryptedLines.size() - 1;
	while (true) {
		reversed.push_back(decryptedLines[current]);
		if (current == 0) break;
		current--;
	}

	decryptedLines = reversed;
}

// returns key, located in first line of file
int getKey(ifstream& inFile) {
	int key;
	resetFlags(inFile);

	while (inFile >> key) {
		cout << "----------" << endl;
		cout << "key: " << key << endl;
		cout << "----------" << endl;
	}

	// last "int key" found will be returned (and there's only one?)
	return key;
}

int main() {
	// string path = "";
	// cout << "Please enter encypted file path: \n";
	// cin >> path;

	string path = "encrypted.txt";

	ifstream inFile(path);
	// check if file opens
	if (!inFile) {
		cerr << "Could not open file. \n";
		exit(1);
	}

	// reading through file
	int key = getKey(inFile);

	string line;
	string decryptedLine;
	vector<string> decryptedLines;

	inFile.clear(); // so we don't reread the first "key" line
	while (getline(inFile, line)) {
		cout << "encrypted line: " << line << endl;
		decryptString(line, key, decryptedLines);
		cout << "----------" << endl;

	}

	reverseOrder(decryptedLines);

	for (string line : decryptedLines) {
		cout << line << endl;
	}
}











