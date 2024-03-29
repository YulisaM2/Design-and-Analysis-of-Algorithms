// cuttingWood_MultiplicacionMatrices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int minEffort(const int &i, const int &j, int D[50][50],const vector<int>&d) {
	int minVal = INT_MAX;
	for (int k = i; k <= j - 1; ++k) {
		if ((D[i][k] + D[k + 1][j] + (d[j] - d[i-1])) < minVal) {
			minVal = D[i][k] + D[k + 1][j] + (d[j] - d[i - 1]);
		}
	}

	return minVal;
}

int matrixMinimumCut(const int& length, const int &amountCuts) {
	// We need an array that includes the edges of the wood to simulate a matrix
	// e.g. cutAt = 2,4,7		length = 10
	// d = {0 , 2 , 4 , 7 , 10)
	vector<int> d(amountCuts + 2);

	// Fill vector with expected cuts (ranges of matrices)
	int cutAt;
	d[0] = 0;
	for (int i = 1; i <= amountCuts; ++i) {
		cin >> cutAt;
		d[i] = cutAt;
	}
	
	d[amountCuts + 1] = length;

	// Initialize matrix with a 0 diagonal because you cant cut in the same place (where i == j)
	int D[50][50];
	for (int i = 1; i <= amountCuts + 1; ++i) {
		D[i][i] = 0;
	}

	int j;
	for (int diag = 1; diag <= amountCuts + 1; ++diag) {
		for (int i = 1; i <= amountCuts + 1 - diag; ++i) {
			j = i + diag;
			D[i][j] = minEffort(i, j, D, d);
		}
	}
	// Answer located at D[1][amountCuts + 1] (out of the matrix of operations)
	return D[1][amountCuts + 1];
}

int main(){
	int length = -1, amountCuts;

	while (length != 0) {
		cin >> length;
		if (length == 0) {
			break;
		}
		
		cin >> amountCuts;
	
		int minCut = matrixMinimumCut(length, amountCuts);
		
		cout << "The minimum cutting is " << minCut << "." << endl;
	}

	cout << "END REACHED" << endl;
	char op;
	cin >> op;

    return 0;
}

