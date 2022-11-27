#include <iostream>
#include <vector>

using namespace std;

int tripleStepBrute(int n) {
    if (n == 0) return 1;
    if (n < 0) return 0;

    return tripleStepBrute(n - 1) + tripleStepBrute(n - 2) + tripleStepBrute(n - 3);
}

int countSteps(int n, vector<int>& memo) {
    if (n == 0) return 1;
    if (n < 0) return 0;
    return memo[n] > -1 ? memo[n] : countSteps(n - 1, memo) + countSteps(n - 2, memo) + countSteps(n - 3, memo);
}

int tripleStepWithMemo(int n) {
    vector<int> memo(n + 1, -1);
    return countSteps(n, memo);
}

int main() {
    cout << endl << "tripleStep test:" << endl;
    int steps = 30;
    cout << "There are " << tripleStepWithMemo(steps) << " ways to traverse " << steps << " steps" << endl;  
}
