/* ProyG - LGSubsequence
 * Mariano García Alipi
 * A00822247
 */

#include <iostream>
#include <vector>

using namespace std;

int main() {
	
	/*
	 * str1:	the first string
	 * str2:	the second string
	 * result:	the resulting string (the longest subsequence)
	 * n1:		the length of str1
	 * n2:		the length of str2
	 * k:		the index in the resulting string
	 * cases:	the number of test cases
	 * maxLen:	the length of the resulting string
	 */
	string str1, str2, result;
	int cases, n1, n2, k, maxLen;
	
	cin >> cases;
	
	for (int testCase = 1; testCase <= cases; testCase++) {	
	
		// Read both strings.
		cin >> str1 >> str2;
		
		// Get the length of both strings.
		n1 = str1.length();
		n2 = str2.length();
		
		// A matrix with the longest subsequence from str1[0] to str1[i] and from str2[0] to str2[j].
		// Size + 1 because the second value is not included in the range. That was my mistake...
		int longestMat[n1 + 1][n2 + 1];
		
		
		// Fill the first column with 0.
		for (int it = 0; it < n1 + 1; it++) {
			longestMat[it][0] = 0;
		}
		
		// Fill the first row with 0.
		for (int it = 0; it < n2 + 1; it++) {
			longestMat[0][it] = 0;
		}
		
		
		// Keep the longest subsequence length from str1[0] to str1[i] and from str2[0] to str2[j].
		// Dynamic Programming. Recursive/backtracking is too inefficient.
		for (int i = 1; i < n1 + 1; i++) {
			
			for (int j = 1; j < n2 + 1; j++) {
				
				// If it's the same character in both strings...
				if (str1[i - 1] == str2[j - 1]) {
					
					// If it's in one of the borders (there is no previous subsequence)... 
					if (i == 0 || j == 0) {
						
						longestMat[i][j] = 1;
						
					} else {
						
						// The longest subsequence up to this point (i, j) is the previous point (i - 1, j - 1) plus one.
						longestMat[i][j] = longestMat[i - 1][j - 1] + 1;
						
					}
					
				} else {
						
					// If it's not the same character, keep the previous longest (i - 1 or j - 1).
					if (longestMat[i - 1][j] > longestMat[i][j - 1]) {

						longestMat[i][j] = longestMat[i - 1][j];

					} else {

						longestMat[i][j] = longestMat[i][j - 1];

					}
				}
			}
		}
		
		
		// The longest subsequence's length is at longestMat[n1 - 1][n2 - 1].
		maxLen = longestMat[n1][n2];
		
		// Print result.
		cout << "Case " << testCase << ": " << maxLen << endl;
		
	}
	
	return 0;
}