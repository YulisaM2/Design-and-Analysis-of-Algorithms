#include <iostream>

using namespace std;

// Check how many possible combinations of binary trees can be created depending on the n submitted

// Catalan number; SUM i = 1 a n, C(i) * C(n - i) = C0Cn + C1Cn-1 +... + CnC0
// para n > 0
// base n = 0 , 1
long int calcTrees(int n){
    long int sum[n];

    sum[0] = 1;

    for(int i = 1; i <= n; ++i){
        sum[i] = 0;
        for(int j = 0; j < i; ++j){
            // C0 Cmax + C1 Cmax - 1 + ... + CMax C0
            // Ccurr Cmax - curr
            sum[i] += sum[j] * sum[i - j - 1];
        }
    }

    return sum[n];
}

int main(){
    long int n;
    cin >> n;

    cout << calcTrees(n) << " BTrees" << endl;
    return 0;
}
