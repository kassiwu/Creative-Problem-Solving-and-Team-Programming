/*
 * PathSumThreeWays.cpp
 *
 *  Created on: Mar 31, 2018
 *  Authors: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
const int INF= 1e9;

// Method to handle printing with proper formating, used for testing
// void print_table(int** dp, int size) {
// 	for (int i = 0;i<size;i++) {
// 		for (int j = 0;j<size;j++) {
// 			cout << dp[i][j] << " ";
// 		}
// 		cout << endl;
// 	}
// }

// Method to enable backtracking through the matrix
void backtrack(int** dp, vector<vector<int> > data, int size) {

	int ans=INF;
	int row_idx;
	vector<int> minRoute;
	// Find the starting position for backtrack
	for(int i=0; i<size; i++) {
		if(ans>dp[i][size-1]) {
			row_idx = i;
			ans=dp[i][size-1];
		}
	}
	// Print out the sum of shortest route
	cout << "Min sum: " << ans << endl;
	int row = row_idx;
	int col = size - 1;
	while (col > 0) {
		// Stop whenever we reach any cell of the right-most column
		minRoute.push_back(data[row][col]);
		if (row == 0) {
			// At the top row
			// Compare with two directions and add the smallest value to the vector
			if (dp[row][col-1] <= dp[row+1][col]) {
				col -= 1;
			}
			else {
				row += 1;
			}
		}
		else if (row == size -1) {
			// At the bottom row
			// Compare with two directions and add the smallest value to the vector
			if (dp[row][col-1] <= dp[row-1][col]) {
				col -= 1;
			}
			else {
				row -= 1;
			}
		}
		else {
			// At the middle of the table
			// Compare costs from three directions and add the smallest value to the vector
//			cout << "hello" << endl;
			if (dp[row][col-1] <= dp[row-1][col] &&
					dp[row][col-1] <= dp[row+1][col]) {
				col -= 1;
			}
			else if (dp[row-1][col] <= dp[row][col-1] &&
					dp[row-1][col] <= dp[row+1][col]) {
				row -= 1;
			}
			else {
				row += 1;
			}
		}
	}
	minRoute.push_back(data[row][0]);

	 cout << "Values: [";
	 for(int i = minRoute.size()-1; i > 0; i--){
		 cout << minRoute[i] << ", ";
	 }
	 cout << minRoute[0] << "]" << endl;
}


// The main logic of our solution
void solve(vector<vector<int> > data) {
	int size = data.size();
	// allocate table
	int** dp = new int*[size];
	for (int i=0; i<size; ++i) {
		dp[i] = new int[size];
	}
	int** dpp = new int*[size];
	for (int i=0; i<size; ++i) {
		dpp[i] = new int[size];
	}
	int i,j;
	// the first column of table dp and table dpp will always be the same as the left-most column of the data
	for (i = 0;i<size;i++) {
		dp[i][0] = dpp[i][0] = data[i][0];
	}
	for(j=1; j<size; j++) {
		for(i=0; i<size; i++) {
			// Traverse right
			// Calculate the price for going to the right
			dp[i][j] = dpp[i][j] = dp[i][j-1]+data[i][j];
		}
		for(i=1; i<size; i++) {
			// Traverse down
			// Check if it would be cheaper to go down rather than the previously found solution
			dp[i][j] = min(dp[i-1][j]+data[i][j],dp[i][j]);
		}
		for (i = size-2;i>=0;i--) {
			// Traverse up
			// Check if it would be cheaper to go up rather than the previously found solution
			dpp[i][j] = min(dpp[i+1][j]+data[i][j],dpp[i][j]);
		}
		for(i=0; i<size; i++) {
			// Combine
			dp[i][j] = dpp[i][j] = min(dp[i][j],dpp[i][j]);
		}
	}
	// Backtracks to find the minimal path
	backtrack(dp, data, size);


	// Free the memory
	for (int i=0; i<size; ++i) {
		delete [] dp[i];
		delete [] dpp[i];
	}
	delete [] dp;
	delete [] dpp;
}




int main() {
	// Dr. B's C++ stdin speed trick
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// Create an ifstream object
    ifstream input_file("matrix2.txt");
    // If the file does not exist, print an error message and exit the program.
    if (!input_file) {
        cerr << "Error: Cannot read file 'matrix.txt'." << endl;
        return 1;
    }

	// Get lines from matrix.txt
	vector< vector<int> > data;
	string line;
	while (getline(input_file, line)) {
		stringstream linestream(line);
		string line;
		string value;
		vector<int> container;
		while(getline(linestream,value,',')) {
			container.push_back(stoi(value));
		}
		data.push_back(container);
	}
 	input_file.close();
    

	if (data.size() == 1) {
		cout << "Min sum: " << data[0][0] << endl;
		cout << "Values: [" << data[0][0] << ']' << endl;
	}
	else {
		solve(data);
	}
	return 0;
}
