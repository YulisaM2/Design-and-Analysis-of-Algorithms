#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>

using namespace std;

// Given a set of 2n integers separated into two arrays of size n, each ordered ascending, and without repeated values, find the median of the set. 

// FLOOR
int midFirstHalf(int top, int bottom){
    return floor((double)(top + bottom)/2);
}

// CEILING
int midSecondHalf(int top, int bottom){
    return ceil((double)(top + bottom)/2);
}
/// O log2 n
void fillVec(vector<int>& vec, const int& n){
    for(int i = 0; i < n; ++i){
        cin >> vec[i];
    }
}

double calcMedian(const vector<int>& firstHalf, const vector<int>& secondHalf, int first, int second){
    return (((double)firstHalf[first] +  secondHalf[second])/ 2);
}

double getMedian(const vector<int>& firstHalf, const vector<int> secondHalf, int limitFirstStart, int limitFristEnd, int limitSecondStart, int limitSecondEnd){
    int midFirst = midFirstHalf(limitFirstStart,limitFristEnd);
    int midSecond = midSecondHalf(limitSecondStart,limitSecondEnd);

    if((midFirst == 0 || midFirst == firstHalf.size() - 1) && (midSecond == 0 || midSecond == firstHalf.size() - 1)){
        return calcMedian(firstHalf,secondHalf,midFirst,midSecond);
    }
    if(firstHalf[midFirst] < secondHalf[midSecond - 1] || secondHalf[midSecond] < firstHalf[midFirst - 1]){
        return getMedian(firstHalf,secondHalf, limitFirstStart + 1, limitFristEnd, limitSecondStart, limitSecondEnd - 1);
    }else if(firstHalf[midFirst] > secondHalf[midSecond + 1] || secondHalf[midSecond] > firstHalf[midFirst + 1]){
        return getMedian(firstHalf,secondHalf,limitFirstStart, limitFristEnd - 1, limitSecondStart + 1, limitSecondEnd);
    }else{
        return calcMedian(firstHalf,secondHalf,midFirst,midSecond);
    }

}

int main(){
    int trials, numSize, curr = 1;;
    cin >> trials;
    for(int i = 0; i < trials; ++i){
        cin >> numSize;
        vector<int> firstHalf(numSize);
        vector<int> secondHalf(numSize);
        fillVec(firstHalf, numSize);
        fillVec(secondHalf, numSize);

        double ans = getMedian(firstHalf,secondHalf,0,numSize - 1,0,numSize - 1);
        cout << "Median case " << curr << ": ";
        cout << fixed << setprecision(2) << ans << endl;
        ++curr;
    }


    return 0;
}
