/*
 * puzzlesolver.cpp
 *
 *  Created on: Feb 236, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// Class representing puzzle pieces
class Puzzle{
	public:
	int number;
	string top;
	string right;
	string bottom;
	string left;
	Puzzle(){}
	// Initialize the piece with input values
	void InitializePiece(int n, string t, string r, string b, string l) {
		number = n;
		top = t;
		right = r;
		bottom = b;
		left = l;
	}

	// Rotates the piece clockwise
	void turnAround() {
		string temp = top;
		top = left;
		left = bottom;
		bottom = right;
		right = temp;
	}
	// Stores values in an array
	vector<string> toArray() {
		vector<string> vec;
		vec.push_back(to_string(number));
		vec.push_back(top);
		vec.push_back(right);
		vec.push_back(bottom);
		vec.push_back(left);
		return vec;
	}
};

// Checks values of North and West sides of pieces
// Returns true if adding the piece to the current board is valid, otherwise returns false
bool checkValue(int pos, Puzzle **board) {
	string temp;
	// Check North
	if (pos/3 > 0) {
		temp = board[pos-3]->bottom;
		temp[1]-'0' == 1 ? temp.replace(1,1,"0") :  temp.replace(1,1,"1");
		if (board[pos]->top != temp) {
			return false;
		}
	}
	// Check West
	if(pos%3 > 0) {
		temp = board[pos-1]->right;
		temp[1]-'0' == 1 ? temp.replace(1,1,"0") :  temp.replace(1,1,"1");
	    if (board[pos]->left != temp) {
	    	return false;
	    }
	}
	return true;
}


// Solves the puzzle, ensuring all neighboring pieces fit together properly
void SolvePuzzle(int pos, Puzzle *pieces, Puzzle **board, bool *pieceAvailable, vector< vector< vector<string> > > *res) {
	// If a solution is found, we add it to our solution set
	if (pos == 9) {
		if ((board[0]->number < board[2]->number) && (board[0]->number < board[6]->number)
				&& (board[0]->number < board[8]->number)) {

			vector< vector<string> > vec_DataArray;
			for (int i = 0;i<9;i++) {
				vec_DataArray.push_back((*(board[i])).toArray());
			}
			(*res).push_back(vec_DataArray);
		}
		return;
	}
	for(int i = 0; i < 9; ++i) {
		// Checks if the piece is available
		if(pieceAvailable[i] == false) {
			continue;
		}
		// Places the piece on the board
		// Removes the last piece and back track if there is no solution with the current board
		board[pos] = &pieces[i];
		pieceAvailable[i] = false;
		for(unsigned j = 0; j < 4; ++j) {
			if (checkValue(pos, board)) {
				SolvePuzzle(pos+1, pieces, board, pieceAvailable,res);
			}
			pieces[i].turnAround();
		}
		pieceAvailable[i] = true;
	}
	board[pos] = NULL;
}



// Print all unique boards with the proper syntax
void printUniqueBoards(vector<vector<vector<string> > > res) {
	if ((res).size() == 0) {
		cout << "No solution found." << endl;
	} else if ((res).size() == 1) {
		cout << (res).size() << " unique solution found:";
	} else {
		cout << (res).size() << " unique solutions found:" << endl;
	}

	for (unsigned i = 0; i != res.size(); i++) {
		for (unsigned row = 0; row < 13; ++row) {
			if (row % 4 == 0) {
				cout << "+--------+--------+--------+" << endl;
			} else {
				for (unsigned col = 0; col < 28; ++col) {
					if (col % 9 == 0 && col != 27) {
						cout << "|";
					} else if (col == 27) {
						cout << "|" << endl;
					} else {
						if (row % 4 == 1) {
							if (col % 9 == 1) {
								cout << res[i][3 * (row / 4) + col / 9][0];
							} else if (col % 9 == 4) {
								cout << res[i][3 * (row / 4) + col / 9][1];
								++col;
							} else {
								cout << " ";
							}
						}

						if (row % 4 == 2) {
							if (col % 9 == 1) {
								cout << res[i][3 * (row / 4) + col / 9][4];
								++col;
							} else if (col % 9 == 7) {
								cout << res[i][3 * (row / 4) + col / 9][2];
								++col;
							} else {
								cout << " ";
							}
						}

						if (row % 4 == 3) {
							if (col % 9 == 4) {
								cout << res[i][3 * (row / 4) + col / 9][3];
								++col;
							} else {
								cout << " ";
							}
						}

					}
				}

			}
		}
		if (i != res.size() - 1) {
			cout << endl;
		}
	}
}



int main(int argc, const char *argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    //Create an ifstream object.
    ifstream input_file(argv[1]);
    // Read a single number as a string
	string line;
	if (!input_file) {
	    cerr << "Unable to open file arrows.txt";
	    exit(1);   // call system to stop
	}
	Puzzle *pieces = new Puzzle[9];
	Puzzle **board = new Puzzle*[9];
	bool *pieceAvailable = new bool[9];
	vector< vector< vector<string> > > res;
	int i = 0;
	cout << "Input tiles:"  << endl;
	// read in input from txt file
	while (getline(input_file, line)) {
	    		    stringstream linestream(line);
	    		    string value;
	    		    vector<string> container;
	    		    while(getline(linestream,value,','))
	    		    {
	    		    	container.push_back(value);
	    		    }
	    		    pieces[i].InitializePiece(i+1,container[0],container[1],container[2],container[3]);

	    			cout << i+1 << ". <" + container[0] + ", " + container[1] + ", "
	    					+ container[2] + ", " + container[3] + ">" << endl;

	    			board[i] = NULL;
	    			pieceAvailable[i] = true;
	    			i++;
	    		}
	cout << endl;
 	input_file.close();
	clock_t start = clock();
	SolvePuzzle(0, pieces, board, pieceAvailable, &res);
	printUniqueBoards(res);

	clock_t timeElapsed = clock() - start;
	unsigned msElapsed = timeElapsed / (CLOCKS_PER_SEC / 1000);
  cout << 	"Elapsed time: " << msElapsed <<" ms";

	// free memory
	delete[] pieces;
	pieces = NULL;

	for (int i=0; i<9; i++) {
		delete[] board[i];
	}
	delete[] board; //delete the array of pointers
	board = NULL;

	delete[] pieceAvailable;
	pieceAvailable = NULL;

	return 0;
  }
