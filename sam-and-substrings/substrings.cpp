/*
 *  substrings.cpp
 *
 *  Created on: Mar 12, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
using namespace std;
#define mod 1000000007

/*
 Given a number as a string, find the sum of all possible substrings.
 N = 456
 Sum up all possible substrings:
 Sum = 4 + 45 + 456 + 5 + 56 + 6
	 = (4*10^0) + (4*10^1 + 5*10^0) + (4*10^2 + 5*10^1 + 6*10^0) + (5*10^0) + (5*10^1 + 6*10^0) + 6*10^0
     = 1*4*10^0 + 1*4*10^1 + 1*4*10^2 + 2*5*10^0 + 2*5*10^1 + 3*6*10^0
     = (1*4 + 2*5 + 3*6)*10^0 + (1*4 + 2*5)*10^1 + (1*4)*10^2
     = (32)*10^0 + (14)*10^1 + (4)*10^2
     = 32+140+400
     = 572

 In general to find the sum of all possible substrings:
 Sum =  (1*N[0] + 2*N[1] + ... + (n)*N[n-1]) * 10^0
      + (1*N[0] + 2*N[1] + ... + (n-1)*N[n-2]) * 10^1
   	  + ...
   	  + (1*N[0]) * 10^(n-1)
*/




int main() {
    // Quick and dirty solution using some IO tricks.
    ios::sync_with_stdio(false);

    // Read a single number as a string
	string num;
	cin >> num;
	int n = num.size();
	long long total = 0;
	long long  pow = 1;
	int i;

	/*	 Total is calculated by the equation:
		 Sum =  (1*N[0] + 2*N[1] + ... + (n)*N[n-1]) * 10^0
			      + (1*N[0] + 2*N[1] + ... + (n-1)*N[n-2]) * 10^1
			   	  + ...
			   	  + (1*N[0]) * 10^(n-1)*/
	long long arr[n];
	arr[n-1] = num[0]-'0';
	// Calculate binomial factor for each term
	for (i = n-2;i>=0;i--) {
		arr[i] = (((num[n-1-i]-'0')*(n-i)) + arr[i+1])%mod;
	}
	// Multiply each value in the array with its corresponding power
	for (i = 0;i<n;i++) {
		total = (total + ((arr[i]*pow)))%mod;
		pow = (pow*10)%mod;
	}

	cout << total<< endl;
	return 0;
}
