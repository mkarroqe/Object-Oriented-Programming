/*	Mary Karroqe
	1/26/18
	CS-2124, rec01: Conway's Game of Life
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// change return type?
// creates 1D array with border
void initialBoard(ifstream& inFile, vector<string>& rows) {
	string row;
	char dead = '`';
	string deadRow = "";
	int counter = 0;

	while (getline(inFile, row)) {
		// so we're not repeating each time in loop
		if (counter == 0) {
			int length = row.length();
			for (int i = 0; i < length + 2; ++i) {
				deadRow += dead;
			}
			rows.push_back(deadRow);
		}

		row = dead + row + dead;
		rows.push_back(row);
		counter += 1;
	}
	// border at bottom
	rows.push_back(deadRow);
}

// turns '-' to ' '
void printBoard(const vector<string>& rows) {
	for (string r : rows) {
		for (char c : r) {
			if (c == '-') {
				cout << ' ';
			}
			else {
				cout << c;
			}
		}
		cout << endl;
	}
}

bool alive(char cell) {
	return cell == '*';
}

void game(vector<string>& rows) {
	vector<string> nextGen = rows;

	for (size_t r = 1; r < rows.size() - 1; ++r) {
		for (int c = 1; c < rows[r].length() - 1; ++c) {
			int neighbors = 0;
			char cell = rows[r][c];

			// counting living neighbors:
			if (alive(rows[r-1][c-1])) {
				neighbors += 1;
			}
			if (alive(rows[r-1][c])) {
				neighbors += 1;
			}
			if (alive(rows[r-1][c+1])) {
				neighbors += 1;
			}
			if (alive(rows[r][c-1])) {
				neighbors += 1;
			}
			if (alive(rows[r][c+1])) {
				neighbors += 1;
			}
			if (alive(rows[r+1][c-1])) {
				neighbors += 1;
			}
			if (alive(rows[r+1][c])) {
				neighbors += 1;
			}
			if (alive(rows[r+1][c+1])) {
				neighbors += 1;
			}			

			// cell dead: does it ressurect?
			if (!alive(cell)) {
				if (neighbors == 3) {
					nextGen[r][c] = '*';
				}
			}
			// cell alive: does it die?
			else {
				// cout << "neighbors: " << neighbors << endl;
				if (neighbors < 2 || neighbors > 3) {
					nextGen[r][c] = '-';
				}
			}
		}
	}

	rows = nextGen;
	printBoard(rows);
}

int main() {
	// string path = "";
	// cout << "Please enter encypted file path: \n";
	// cin >> path;

	string path = "life.txt";

	ifstream inFile(path);
	// check if file opens
	if (!inFile) {
		cerr << "Could not open file. \n";
		exit(1);
	}

	vector<string> rows;
	initialBoard(inFile, rows);

	for (int i = 0; i < 11; ++i) {
		if (i == 0) {
			cout << "Initial World: " << endl;
			printBoard(rows);
		}
		else {
			cout << "Generation " << i << ":" << endl;
			game(rows);
		}
	}

	inFile.close();
}










