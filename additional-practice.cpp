#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// DP implementation
int minRefuelStops1(int target, int startFuel, vector<vector<int>> &stations) {
    int size = stations.size();
    vector<long> dp(size + 1, 0);
    dp[0] = startFuel;

    for (int stop = 0; stop < size; ++stop) {
        for (int t = stop; t >= 0; --t) {
            if (dp[t] >= stations[stop][0]) {
               dp[t + 1] = max(dp[t + 1], dp[t] + (long)stations[stop][1]); 
            }
        }
    }

    for (int i = 0; i <= size; ++i) {
        if (dp[i] >= target) return i;
    }
    return -1;
}

int minRefuelStops2(int target, int startFuel, vector<vector<int>> &stations) {
    priority_queue<int> maxHeap;
    int ans = 0;
    int prev = 0;
    for (vector<int>& station : stations) {
        int location = station[0];
        int amount = station[1];
        startFuel -= location - prev;
        while (!maxHeap.empty() && startFuel < 0) {
            startFuel += maxHeap.top();
            maxHeap.pop();
            ++ans;
        }

        if (startFuel < 0) return -1;
        maxHeap.push(amount);
        prev = location;
    }

    startFuel -= target - prev;
    while (!maxHeap.empty() && startFuel < 0) {
        startFuel += maxHeap.top();
        maxHeap.pop();
        ++ans;
    }
    if (startFuel < 0) return -1;
    
    return ans;
}

int main() {
    cout << endl << "minRefuelStops test:" << endl;
    int target = 100;
    int start = 10;
    vector<vector<int>> stations = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
    cout << "dp implementation: " << minRefuelStops1(target, start, stations) << endl; 
    cout << "pq implementation: " << minRefuelStops2(target, start, stations) << endl; 

}
