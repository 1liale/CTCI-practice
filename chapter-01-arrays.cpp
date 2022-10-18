#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

using namespace std;

bool isUnique(string s) {
    unordered_set<char> visited;
    for (int i = 0; i < s.length(); ++i) {
        if (visited.count(s[i]) > 0) return false;
        visited.insert(s[i]);
    }
    return true;
}

bool checkPermutation(string s1, string s2) {
    int n = s1.length(), m = s2.length();
    if (n != m) return false;
    unordered_map<char, int> charDict;

    for (char c : s1) {
        ++charDict[c];
    }

    for (char c : s2) {
        if (charDict.count(c) < 1 || charDict[c] < 1) return false;
        --charDict[c];
    }

    return true;
}

string URLify(string s) {
    const char SPACE = ' ';
    string compressedURL = "";

    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != SPACE) { 
            compressedURL += s[i];
            continue;
        }
        int j = i;
        while(s[j] == SPACE) {
            ++j;
        }
        i = j - 1;
        if (j < s.length() - 1) compressedURL += "%20";
    }

    return compressedURL;
}

bool checkPalindromePerm(string s) {
    unordered_map<char, int> charDict;

    for (char c : s) {
        if (c != ' ') ++charDict[tolower(c)];
    }

    int oddCount = 0;

    for (auto it : charDict) {
        if (oddCount > 1) return false;
        if (it.second % 2 == 1) oddCount++;
    }

    return true;
}

bool isOneAway(string s1, string s2) {
    int n = s1.length(), m = s2.length();
    if (abs(n - m) > 2) return false;

    string s = n < m ? s1 : s2;
    string l = n < m ? s2 : s1;

    bool changeFound = false;

    int i = 0, j = 0;
    while (i < s.length() && j < l.length()) {
        if (s[i] != l[j]) {
            if (changeFound) return false;
            changeFound = true;

            if (s.length() == l.length()) {
                i++;
            }
        } else {
            i++;
        }
        j++;
    }

    return true;
}

string stringCompression(string compressStr) {
    string output;
    for (int i = 0; i < compressStr.length(); ++i) {
        char curChar = compressStr[i];
        int j = i, repeat = 0;
        while (compressStr[j] == curChar) {
            j++;
            repeat++;
        }
        i = j - 1;
        output += curChar + to_string(repeat);
    }

    return output.length() < compressStr.length() ? output : compressStr;
}

void rotateMatrix90(vector<vector<int>>& matrix) {
   int m = matrix.size();
   if (m == 0 || m != matrix[0].size()) return;

   for (int layer = 0; layer < m / 2; ++layer) {
        int first = layer;
        int last = m - layer - 1;

        for (int i = first; i < last; ++i) {
            int offset = i - first;
            int top = matrix[first][i];

            // left -> top
            matrix[first][i] = matrix[last - offset][first];

            // bottom -> left
            matrix[last - offset][first] = matrix[last][last - offset];

            // right -> bottom
            matrix[last][last - offset] = matrix[i][last];

            // top -> right
            matrix[i][last] = top;
        }
   }
}

void zeroMatrix(vector<vector<int>>& matrix) {
    bool fillFirstRow = false, fillFirstCol = false;

    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i][0] == 0) {
            fillFirstCol = true;
            break;
        }
    }

    for (int i = 0; i < matrix[0].size(); ++i) {
        if (matrix[0][i] == 0) {
            fillFirstRow = true;
        }
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }         
        }
    }

    for (int i = 1; i < matrix.size(); ++i) {
        if (matrix[i][0] == 0) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    for (int i = 1; i < matrix[0].size(); ++i) {
        if (matrix[0][i] == 0) {
            for (int j = 0; j < matrix.size(); ++j) {
                matrix[j][i] = 0;
            }
        }
    }

    if (fillFirstRow)
        for (int i = 0; i < matrix[0].size(); ++i) {
            matrix[0][i] = 0;
        }
    if (fillFirstCol) 
        for (int i = 0; i < matrix.size(); ++i) {
            matrix[i][0] = 0;
        }
}

bool isStringRotation(string s1, string s2) {
    if (s1.length() == s2.length() && s1.length() > 0) {
        string comb = s1 + s1;
        return comb.find(s2) != string::npos;
    }
    return false;
}

int main() {
	// isUnique test
    cout << endl << "isUnique test:" << endl;
    string s = "you";
    cout << s << " is unique: " << boolalpha << isUnique(s) << endl;

    // checkPermutation test
    cout << endl << "checkPermutation test:" << endl;
    string s1 = "apple";
    string s2 = "plaep";

    assert(checkPermutation(s1, s2) == true);
    cout << "permutation found: " << s1 << ", " << s2 << endl;

    // URLify test
    cout << endl << "URLify test:" << endl;
    string url = "Mr John Smith    ";
    cout << URLify(url) << endl;
    
    // checkPalindromePerm test
    cout << endl << "checkPalindromePerm test:" << endl;
    string palinPermStr = "Tact Coa";
    cout << palinPermStr << " has a palindrome permutation: " << boolalpha << checkPalindromePerm(palinPermStr) << endl;

    // isOneAway test
    cout << endl << "isOneAway test:" << endl;
    string oneAwayStr1 = "test";
    string oneAwayStr2 = "tes";
    assert(isOneAway(oneAwayStr1, oneAwayStr2));
    cout << oneAwayStr1 << " is one away from " << oneAwayStr2 << endl; 
    
    // stringCompression test
    cout << endl << "stringCompression test:" << endl;
    string compressStr = "abc";
    cout << compressStr << " becomes " << stringCompression(compressStr) << endl;
       
    // rotateMatrix test
    cout << endl << "rotateMatrix test:" << endl;
    vector<vector<int>> matrix {{1, 2}, {3, 4}};
    
    rotateMatrix90(matrix);
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // zeroMatrix test
    cout << endl << "zeroMatrix test:" << endl;
    vector<vector<int>> matrix1 {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    
    zeroMatrix(matrix1);
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix1[0].size(); ++j) {
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }

    // isStringRotation test
    cout << endl << "isStringRotation test:" << endl;
    string notRotated = "waterbottle";
    string rotated = "erbottlewat";

    cout << "is string rotated: "<< boolalpha << isStringRotation(notRotated, rotated) << endl; 

    return 0;
}
