#include <iostream>
#include <queue>

using namespace std;

// Find the longest subsequence common to all sequences in a set of sequences (often just two sequences that do not need to be consecutive)
// For example, having the strings “AAAAAAABBAAB” and “ABAABBAB”, the Longest Common Subsequence is the string “AAABBAB” with a length of 7. 

int longestSequence(const string& first, const string& second){
    int maxRen = first.size();
    int maxCol = second.size();

    int mat[maxRen][maxCol];

    // Keep track of sequences one row above & one column before
    // + 1 if curr first and second are the same char
    for(int i = 0; i < maxRen; ++i){
        for(int j = 0; j < maxCol; ++j){
            if(first[i] == second[j]){
                // Sequences start at i == 0 and j == 0
                if(i > 0 && j > 0){
                    mat[i][j] = mat[i - 1][j - 1] + 1;
                }else{
                    mat[i][j] = 1;
                }
            }else{
                if(i > 0 && j > 0){
                    if(mat[i - 1][j] >= mat[i][j - 1]){
                        mat[i][j] = mat[i - 1][j];
                    }else{
                        mat[i][j] = mat[i][j - 1];
                    }
                }else{
                    if(i > 0){
                        mat[i][j] = mat[i - 1][j];
                    }else if(j > 0){
                        mat[i][j] = mat[i][j - 1];
                    }else{
                        mat[i][j] = 0;
                    }
                }

            }
        }
    }

//    for(int i = 0; i < maxRen; ++i){
//        for(int j = 0; j < maxCol; ++j){
//            cout << mat[i][j] << " ";
//        }
//        cout << endl;
//    }
    return mat[maxRen - 1][maxCol - 1];
}


int main(){
    int trials;
    cin >> trials;

    for(int i = 0; i < trials; ++i){
        string first, second;
        cin >> first >> second;

        cout << "Case " << i + 1 << ": " << longestSequence(first,second) << endl;
    }

    return 0;
}
