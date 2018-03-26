'''
trip.py
Created on: Mar 25, 2018
Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
I pledge my honor that I have abided by the Stevens Honor System.
Description: Given 2 strings of lower case letters find all the longest common subsequences
http://www.spoj.com/problems/TRIP/
'''
#!/usr/bin/env python3
import sys
from itertools import groupby

def lcs_dp(s1, s2):
    """ Uses bottom-up dynamic programming and memorization to improve performance.
        Note that T[i][j] contains length of LCS of s1[0..i-1] and s2[0..j-1].
    """
    m = len(s1)
    n = len(s2)
    T = [[0] * (n + 1) for _ in range(m + 1)]
    # Compute the length of LCS for s1[0..m-1], s2[0..n-1]
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i-1] == s2[j-1]:
                T[i][j] = T[i - 1][j - 1] + 1
            else:
                T[i][j] = max(T[i-1][j],T[i][j-1])


    def find_all_lcs(r, c):
        '''Traverse the 2D array starting from T[m][n]'''
         # Use memoization
        if (''.join(reversed(lcs)),r, c) in memo:
            return
        if r == 0 or c == 0:
            # Add to results
            all_lcs.append(''.join(reversed(lcs)))
            return
        if s1[r-1] == s2[c-1]:
            # If characters corresponding to T[r][c] are the same, then include the character as part of LCS
            lcs.append(s1[r - 1])
            find_all_lcs(r-1, c-1)
            lcs.pop()
        # If they are not equal, then the longer of the two sequences is retained
        if T[r - 1][c] == T[r][c]:
            find_all_lcs(r-1, c)
        if T[r][c - 1] == T[r][c]:
            find_all_lcs(r, c-1)
        memo.add((''.join(reversed(lcs)),r, c))

    all_lcs = []
    lcs = []
    memo = set()
    find_all_lcs(m,n)
    return all_lcs

if __name__=='__main__':
    # Read in number of operations to perform
    N = int(input())
    while N:
        N -= 1
        s1 = input()
        s2 = input()
        # print all unique sequences
        for x, _ in groupby(sorted(lcs_dp(s1,s2))):
            print(x)
