#include <iostream>
#include <vector>

using namespace std;

struct Elem {
    int val;
    int curMin;
    Elem(int v, int m): val{v}, curMin{m} {} 
};

class MinStack {
    vector<Elem> minStack;
public:
    void pop() {
        minStack.pop_back();
    }
    Elem peek() {
        return minStack.back();
    }
    void push(int val) {
        int newMin = min(val, getMin());
        minStack.push_back({val, newMin});
    }
    int getMin() {
        return minStack.empty() ? INT_MAX : peek().curMin;
    }
};

class StackOfPlates {
    vector<vector<int>> stacks;
    int threshold;
    int stackPtr = 0;
public:
    StackOfPlates(int threshold): stacks(1, vector<int>()), threshold{threshold} {}
    void push(int val) {
        if (stacks[stackPtr].size() >= threshold) {
            stacks.push_back(vector<int>());
            stackPtr++;
        } else {
            stacks[stackPtr].push_back(val);
        }
    }

    int peek() {
        return stacks[stackPtr].back();
    }

    void pop() {
        if (stacks[stackPtr].empty()) {
            stacks.resize(stackPtr);
            stackPtr--;
        } else {
            stacks[stackPtr].pop_back();
        }
    }

    int getSize() {
        return stacks.size();
    }
};

class QueueViaClass {
    vector<int> youngStack;
    vector<int> oldStack;
    void transferStack () {
        while (!youngStack.empty()) {
            oldStack.push_back(youngStack.back());
            youngStack.pop_back();
        }
    }
public:
    QueueViaClass() {}
    void queueBack(int val) {
        youngStack.push_back(val);
    }
    void dequeFront() {
        if (oldStack.empty()) {
            transferStack();
        }
        oldStack.pop_back();
    }
    int front() {
        if (oldStack.empty()) {
            transferStack();
        }

        return oldStack.back();
    }
};

int main() {
    cout << endl << "Min Stack test:" << endl;  
    MinStack minStack{};
    minStack.push(5);
    minStack.push(2);
    minStack.push(4);
    cout << "min val on the stack: " << minStack.getMin() << endl;
    
    cout << endl << "Stack of plates test:" << endl;
    StackOfPlates stacks{5};
    stacks.push(1);
    stacks.push(2);
    stacks.push(3);
    stacks.push(4);
    stacks.push(5);
    stacks.push(6);
    cout << "# of stacks: " << stacks.getSize() << endl;
    
    cout << endl << "Queue via stacks test:" << endl;
    QueueViaClass qvc{};
    qvc.queueBack(5);
    qvc.queueBack(4);
    qvc.dequeFront();
    cout << "front of queue: " << qvc.front() << endl;
}
