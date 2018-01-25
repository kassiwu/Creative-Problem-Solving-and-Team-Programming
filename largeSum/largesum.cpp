/*
 * largeSum.cpp
 *
 *  Created on: Jan 23, 2018
 *  Author: Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;


int main(int argc, const char *argv[]) {
	clock_t time = clock();
	// Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // Read a single number as a string
	string line;

    if (input_file) {
    	    // highest digits might overflow
    		const unsigned int digitLength  = 50 + 3;
    		// all digits are initially zero, least significant digit has index 0
    		vector<unsigned long> fullSum(digitLength);

    		// Use getline to read in a line.
    		while (getline(input_file, line)) {
    			// process string in reverse, least significant digit has index 0
    			vector<unsigned int> temp;
    			for (int i = line.length()-1; i >=0; i--){
    				temp.push_back(line[i] - '0');
    			}
    			// inserting zeros at the end as many elements as needed to reach a size of fullSum.
    			temp.resize(fullSum.size(), 0);
    			// add to fullSum
    		    for (unsigned int i = 0; i < temp.size(); i++){
    		    		fullSum[i] += temp[i];
    		    		if (fullSum[i] >= 10) {
    		    			fullSum[i] -= 10;
    		    			fullSum[i+1] += 1;
    		    		}
    		    }
    	 }

    	 string result;
    	 // iterating over a vector in reverse direction	, most significant digit comes before least significant digit
    	 vector<unsigned long>::reverse_iterator i = fullSum.rbegin();
    	 for (; i!= fullSum.rend(); ++i) {
    		 result += to_string(*i);
    	  }

    	 size_t found = result.find_first_not_of("0");
    	 string FullSumStr = result.substr(found, digitLength-found);
    	 cout << "Full sum: " << FullSumStr << endl;
    	 if (FullSumStr.length() > 10) {
        	 cout << "First 10 digits: " << FullSumStr.substr(0,10) << endl;
    	 }
    	 else {
    		 cout << "Full sum: " << FullSumStr << endl;
    	 }

    	input_file.close();

    	time = clock() - time;
    	cout << 	"Elapsed time: " << time <<" ms";
    	return 0;



    }
    // If it does not exist, print an error message.
    else {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
}
