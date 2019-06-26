#include <iostream>
#include <vector>

using namespace std;

// The two trains each contain some railroad cars. Each railroad car contains a single type of products identified by a positive integer up to 1,000,000. 
// The two trains come in from the right on separate tracks, as in the diagram above. To combine the two trains, we may choose to take the railroad car at the front of either train and attach it to the back of the train being formed on the left.
// Of course, if we have already moved all the railroad cars from one train, then all remaining cars from the other train will be moved to the left one at a time.
// All railroad cars must be moved to the left eventually. Depending on which train on the right is selected at each step, we will obtain different arrangements for the departing train on the left. 
// For example, we may obtain the order 1,1,1,2,2,2 by always choosing the top train until all of its cars have been moved. We may also obtain the order 2,1,2,1,2,1 by alternately choosing railroad cars from the two trains. 
// To facilitate further processing at the other train yards later on in the trip (and also at the destination), the supervisor at the train yard has been given an ordering of the products desired for the departing train. 
// In this problem, you must decide whether it is possible to obtain the desired ordering, given the orders of the products for the two trains arriving at the train yard.  
 


void fillVec(vector<int>& vec, const int& n){
    int buffer;
    for(int i = 0; i < n; ++i){
        cin >> buffer;
        vec.push_back(buffer);
    }
}

void restart(vector<int>& first, vector<int>& second, vector<int>& last){
    first.clear();
    second.clear();
    last.clear();
}

void printVec(const vector<string>& vec){
    for(int i = 0; i < vec.size(); ++i){
        cout << vec[i] << endl;
    }
}


bool verify(const vector<int>& firstRail, const vector<int>& secondRail, const vector<int> check, const int numA, const int numB){
    bool mat[numA + 1][numB + 1];
    mat[0][0] = true;

    for(int i = 1; i <= numA; ++i){
        if(firstRail[i - 1] == check[i - 1] && mat[i - 1][0]){
            mat[i][0] = true;
        }else{
            mat[i][0] = false;
        }
    }

    for(int i = 1; i <= numB; ++i){
        if(secondRail[i - 1] == check[i - 1] && mat[0][i - 1]){
            mat[0][i] = true;
        }else{
            mat[0][i] = false;
        }
    }

    for(int i = 1; i <= numA; ++i){
        for(int j = 1; j <= numB; ++j){
             if(((check[i + j - 1] == firstRail[i - 1]) && mat[i - 1][j]) ||((check[i + j - 1] == secondRail[j - 1]) && mat[i][j - 1])){
                mat[i][j] = true;
            }else{
                mat[i][j] = false;
            }
        }
    }

    return mat[numA][numB];
}

int main(){

    int numA, numB;
    cin >> numA >> numB;

    vector<string> answers;
    while(!(numA == 0 && numB == numA)){
        vector<int> firstRail;
        fillVec(firstRail,numA);

        vector<int> secondRail;
        fillVec(secondRail,numB);

        vector<int> check;
        fillVec(check, numA + numB);

        if(verify(firstRail,secondRail,check,numA,numB)){
            answers.push_back("possible");
        }else{
            answers.push_back("not possible");
        }

        restart(firstRail,secondRail,check);
        cin >> numA >> numB;
    }

    printVec(answers);

    return 0;
}
