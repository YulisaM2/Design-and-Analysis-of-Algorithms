#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// There is a line up of enemies, each one of them has a strength. We also have a group of balls to throw with a power to shoot down soldiers.
// Each enemy must be shot in order of the line up, when all have been strucked, they all raise again and the game continues. 

// For example if there are 5 enemies
// with the strength of 3 2 5 1 2
// and there are 4 balls with the power of 5 1 10 3
// The first ball will shoot down enemies 1 and 2, the second ball will reduce the strength of the third enemy to 1, and the third BeagleBall will shoot down the soldiers 3, 4, 5
// then the enemies are risen up and the fourth ball shoots down the first enemy.
 
// Your output should be the number of the enemies that remain standing after each throw, 
// In the example above the output must be 3 3 5 4 

void fillCont(vector<int>& line, const int& num){
    int buffer;
    for(int i = 0; i < num; ++i){
        cin >> buffer;
        line.push_back(buffer);
    }
}

void fillQueue(queue<int>& line, const int& num){
    int buffer;
    for(int i = 0; i < num; ++i){
        cin >> buffer;
        line.push(buffer);
    }
}

void fillGameboard(stack<int>& gameboard, const vector<int>& soldiers){
    for(int i = soldiers.size() - 1; i >= 0; --i){
        gameboard.push(soldiers[i]);
    }
}

void refillQueue(queue<int>& refill, const vector<int> filler, const int& n){
    for(int i = 0; i < n; ++i){
        refill.push(filler[i]);
    }
}

void printLine(const vector<int>& line, const int& n){
    for(int i = 0;i < n; ++i){
        cout << line[i] << endl;
    }
}

void printStack(stack<int> line){
    while(!line.empty()){
        cout << line.top() << " ";
        line.pop();
    }
    cout << endl;
}

void printQueue(queue<int> line){
    while(!line.empty()){
        cout << line.front() << " ";
        line.pop();
    }

    cout << endl;
}


void shot(const vector<int> lineSoldiers, queue<int>& balls, const int& numSoldiers, const int& numBalls){
    // create editable line of soldiers
    stack<int> gameboard;
    fillGameboard(gameboard,lineSoldiers);

    vector<int> answers;

    while(!balls.empty()){
        int currSoldier = gameboard.top();
        int currBall = balls.front();

        if(currBall < currSoldier){
            currSoldier -= currBall;
            gameboard.pop();
            gameboard.push(currSoldier);
        }else if(currBall == currSoldier){
            gameboard.pop();
        }else{
            currBall -= currSoldier;
            gameboard.pop();
            while(!gameboard.empty() && currBall > 0){
                currSoldier = gameboard.top();
                if(currBall < currSoldier){
                    currSoldier -= currBall;
                    currBall = 0;
                    gameboard.pop();
                    gameboard.push(currSoldier);
                }else if(currBall == currSoldier){
                    currBall = 0;
                    gameboard.pop();
                }else{
                    currBall -= currSoldier;
                    gameboard.pop();
                }

            }
        }

        if(gameboard.empty()){
            fillGameboard(gameboard,lineSoldiers);
        }

        answers.push_back(gameboard.size());
        balls.pop();

    }

    printLine(answers,numBalls);
}

int main(){

    int numSoldiers, numBalls;
    cin >> numSoldiers >> numBalls;

    vector<int> lineSoldiers;

    fillCont(lineSoldiers,numSoldiers);


    queue<int> balls;
    fillQueue(balls,numBalls);


    shot(lineSoldiers, balls, numSoldiers, numBalls);
    return 0;
}
