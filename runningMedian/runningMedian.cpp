/*
 *  runningMedian.cpp
 *
 *  Created on: Apr 5, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 *  Problem: https://www.hackerrank.com/challenges/find-the-running-median/problem
 */


#include <iostream>     // std::cout, std::fixed
#include <queue>
#include <iomanip>      // std::setprecision
using namespace std;
class MedianFinder {
	public:
		// Adds a number into the data structure
		void insertHeap(int x) {
			// case 1: both heaps are balanced
			if (max_heap.empty() || x <= max_heap.top()) {
				max_heap.push(x);
			}
			else {
				min_heap.push(x);
			}
			// Makes heaps balanced and and their sizes differ by at most 1
			// case 2:  max heap has more elements
			if (max_heap.size() - 2 == min_heap.size()) {
				min_heap.push(max_heap.top());
				max_heap.pop();
			}
			// case 3: min heap has more elements
			else if (min_heap.size() > max_heap.size()) {
				max_heap.push(min_heap.top());
				min_heap.pop();
			}
		}

		// Returns the median of current data stream
		double getMedian() {
			if (min_heap.size() == max_heap.size()) {
				// Returns the average of two middle numbers when both heaps are balanced
				return 0.5*(min_heap.top() + max_heap.top());
			}
			else {
				// Returns the top element of max heap
				return max_heap.top();
			}
		}
	private:
        // in a min heap parent node is always smaller or equal to its child node
	    priority_queue<int, vector<int>, greater<int> > min_heap; // min_heap stores the larger half seen so far.
        // in a max heap parent node is always greater or equal to its child node
	    priority_queue<int, vector<int>, less<int> > max_heap; // max_heap_ stores the smaller half seen so far.
};


int main() {
    // Quick and dirty solution using some IO tricks.
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, val;
    double median;
    MedianFinder mf;
    // Reads inthe number of integers in the data stream
    cin >> n;
    while (n--) {
    		cin >> val;
    		mf.insertHeap(val);
    		median = mf.getMedian();
        cout << setprecision(1) << fixed << median << endl;
    }
}
