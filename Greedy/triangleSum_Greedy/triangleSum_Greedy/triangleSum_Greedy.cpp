// triangleSum_Greedy.cpp : Defines the entry point for the console application.
// Yulisa Medina 
// A01570056

#include "stdafx.h"
#include <iostream>

using namespace std;

void printMatrix(int m[10][11], int numLines) {
	cout << "PRINT MATRIX" << endl;
	for (int i = 0; i < numLines; ++i) {
		for (int j = 0; j <= numLines; ++j) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void dinamic(const int& numLines) {
	int sums[10][11];

	for (int i = 0; i < numLines; ++i) {
		for (int j = 0; j < numLines; ++j) {
			sums[i][j] = 0;
		}
	}

	// Find bigger between above and above left
	// o
	// |\
	// o o
	// when j == i there is no above so use sums[i-1][j-1]
	// when j == 0 there is no above left so use sums[i-1][j]
	// base case is (0,0) where we have no aboves, so we must save nums

	// Save biggest sum at (0,numLines) which when starting is nums
	int nums;
	cin >> nums;
	sums[0][0] = nums;
	sums[0][numLines] = nums;

	for (int i = 1; i < numLines; ++i) {
		for (int j = 0; j <= i; ++j) {
			cin >> nums;
		    if (j == 0) {
				sums[i][j] = sums[i - 1][j];
			}else {
				sums[i][j] = (sums[i - 1][j - 1] >= sums[i - 1][j]) ? sums[i - 1][j - 1] : sums[i - 1][j];
			}		
			
			sums[i][j] += nums;

			// save biggest
			if (sums[i][j] > sums[0][numLines]) {
				sums[0][numLines] = sums[i][j];
			}

		}
	}

//	 printMatrix(sums, numLines);

	cout << sums[0][numLines] << endl;

}

int main(){
	int amountTrials;
	cin >> amountTrials;

	for (int currTrial = 0; currTrial < amountTrials; ++currTrial) {
		int numLines;
		cin >> numLines;
		dinamic(numLines);
	}


	char op;
	cin >> op;
    
	return 0;
}

