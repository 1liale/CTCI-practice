#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int insertion(int N, int M, int i, int j) {
    M <<= i;
    for (int k = i; k <= j; ++k) {
        N &= ~(1 << k);
    }
    return N |= M;
}

string binToStr(double num) {
    if (num >= 1 || num <= 0) return "ERROR";

    string output = "0.";
    while (num > 0) {
        if (output.length() >= 33) {
            return "ERROR";
        }
        double m = num * 2;
        if (m  >= 1) {
            output += "1";
            num = m - 1;
        }
        else {
            output += "0";
            num = m;
        }
    } 

    return output;
}

int flipBitToWin(unsigned int num) {
    if (~num == 0) return __builtin_popcount(num);
    int bitCount = 1;
    int prev = 0, current = 0;
    while (num > 0) {
        if ((num & 1) == 0) {
            prev = (num & 2) == 0 ? 0 : current;
            current = 0;
        } else {
            ++current;
        }
        bitCount = max(prev + 1 + current, bitCount);
        num >>= 1;
    }
    return bitCount;
}

void nextNumber(unsigned int num) {
    cout << "start: " << num << ", " << bitset<16>(num) << endl;

    // set first non-trailing zero bit
    int i = 0;
    while (i < 32) {
        if ((num & (1 << i)) && (num & (2 << i)) == 0) {
            num |= (2 << i);
            break;
        }
        i++;
    }

    int onesCount = 0;
    // remove all ones after it
    while (i >= 0) {
        if (num & (1 << i)) {
            onesCount++;
            num &= ~(1 << i);
        }
        i--;
    }
    i = 0;
    // set the ones in order for min nextNumber
    while (i < onesCount - 1) {
        num |= (1 << i);
        i++;
    }

    cout << "end: " << num << ", " << bitset<16>(num) << endl;
}

int main() {
    cout << endl << "bits insertion test:"<< endl;
    cout << std::bitset<16>(insertion(stoi("10000001101", nullptr, 2), stoi("10011", nullptr, 2), 2, 6)) << endl;

    cout << endl << "binary to string test:" << endl;
    double num = 0.75;
    cout << num << " in binary string form is: " << binToStr(num) << endl;

    cout << endl << "flipBitToWin test:" <<  endl;
    cout << "11011101111 (1775) has longest 1s sequence of " << flipBitToWin(1775) << " after flipping a bit" << endl;  

    cout << endl << "nextNumber test:" << endl;
    nextNumber(1775);
}

