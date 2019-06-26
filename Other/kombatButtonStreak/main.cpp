#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// There is a game which has 26 buttons (from ‘a’ to ‘z’), it consist in making the most damage possible clicking buttons but is not possible to push the same button more than consecutive n times.
// Having a hit button sequence and their damage, give the maximum damage possible.

// For example, given that the length of the button sequence is 7
// and that the max times of consecutive hits is 3
// with this damage per button 1 5 16 18 7 2 10 
// and this combination baaaaca 
// the output shall be 54 

void printVect(const vector<int>& vec, const int& n){
    for(int i = 0; i < n; ++i){
        cout << vec[i] << " ";
    }
    cout << endl;
}

int addBest(priority_queue<int>& best, int& sum, const int& maxHits){
    for(int i = 0; i < maxHits; ++i){
        sum += best.top();
        best.pop();
    }
}

int calcMax(const vector<int>& damages, const string& sequence, const int& sizeHits, const int& maxHits){
    int sum = 0;
    priority_queue<int> bestSequence;

    int curr = 0;
    while(curr < sizeHits){
        if(curr < sizeHits - 1){

            if(sequence[curr] == sequence[curr + 1]){
                bestSequence = priority_queue<int>();
                bestSequence.push(damages[curr]);
                bestSequence.push(damages[curr + 1]);

                int same = curr + 2;
                while(sequence[curr] == sequence[same] && same < sizeHits){
                    bestSequence.push(damages[same++]);
                }
                addBest(bestSequence, sum, maxHits);
                curr = same;

            }else{
                sum += damages[curr++];
            }
        }else{
            sum += damages[curr++];
        }
    }

    return sum;
}

int main(){
    int sizeHit, maxHits;
    cin >> sizeHit >> maxHits;

    vector<int> damages(sizeHit);
    for(int i = 0 ; i < sizeHit; ++i){
        cin >> damages[i];
    }

    string sequence;
    cin >> sequence;

    cout << calcMax(damages,sequence, sizeHit, maxHits) << endl;

    return 0;
}
