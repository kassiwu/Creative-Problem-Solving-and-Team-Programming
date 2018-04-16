/*
 *  arrayAndSimpleQueries.cpp
 *
 *  Created on: Apr 12, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 *  Problem: https://www.hackerrank.com/challenges/array-and-simple-queries/problem
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main()
{
    // Dr. B's io speed trick
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    /*
     * Take in user input
     * Line 1: Size n of array, number m of queries
     * Line 2: int array A[]
     * Remaining lines: Queries
     * Query format: 1 i j (remove from i to j and move to front) 
     * or 2 i j (remove from i to j and move to back) 
     */

    int n, m;
    int A[n];
    int query, i, j;
    int count = 1;

    cin >> n;
    cin >> m;

    for (int x = 0; x < n; x++)
    {
        cin >> A[x];
    }

    while (m > 0)
    {
        cin >> query;
        if (query == 1)
        {
            // Execute query type 1
            cin >> i;
            cin >> j;
            int takeOut[j - i];
            int preceding[i];
            int succeeding[n - j];
            // int finished[n];
            int y = i;
            for (int x = i; x <= j; x++)
            {
                // Get elements i to j and place them in a new array
                takeOut[x] = A[y];
                y++;
                // Need to fill remaining and concat temp and remaining
            }
            for (int x = 0; x < i; x++)
            {
                // Get elements preceding i to j
                preceding[x] = A[x];
            }
            for (int x = j + 1; x <= n; x++)
            {
                // Get elements succeeding i to j
                int temp = 0;
                succeeding[temp] = A[x];
                temp++;
            }
            // Append takeOut + preceding + succeeding and overwrite A

            ++count;
        }
        else if (query == 2)
        {
            // Execute query type 2
            cin >> i;
            cin >> j;
            int takeOut[j - i];
            int preceding[i];
            int succeeding[n - j];
            // int finished[n];
            int y = i;
            for (int x = i; x <= j; x++)
            {
                // Get elements i to j and place them in a new array
                takeOut[x] = A[y];
                y++;
                // Need to fill remaining and concat temp and remaining
            }
            for (int x = 0; x < i; x++)
            {
                // Get elements preceding i to j
                preceding[x] = A[x];
            }
            for (int x = j + 1; x <= n; x++)
            {
                // Get elements succeeding i to j
                int temp = 0;
                succeeding[temp] = A[x];
                temp++;
            }
            // Append preceding + succeeding + takeOut and overwrite A
            ++count;
        }
        else
        {
            cerr << "Error: query " << count << " is invalid" << endl;
            return 1;
        }
        m--;
    }

    // Get absolute value
    int abso = abs(A[0] - A[n]);
    
    // Print abs 
    cout << abso << endl;

    // Print last array 
    
}
