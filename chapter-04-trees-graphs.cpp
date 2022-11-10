#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Chapter Questions 4.1 - 4.5 completed on Leetcode

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
    int val;
    TreeNode(int val): left{nullptr}, right{nullptr}, parent{nullptr}, val{val} {}
};

TreeNode *findLeftMost(TreeNode *node) {
    if (!node) return node;
    while (node->left) {
        node = node->left; 
    }
    return node;
}

TreeNode *findSuccessor(TreeNode* curNode) {
    if (!curNode) return curNode;        
    if (curNode->right != nullptr) {
        return findLeftMost(curNode->right);
    } else {
        TreeNode *node = curNode;
        TreeNode *parentNode = node->parent;
        while (parentNode && parentNode->left != node) {
            node = parentNode;
            parentNode = parentNode->parent;
        }
        return parentNode;
    }
}

vector<char> buildOrder(vector<char> projects, vector<pair<char, char>> dependencies) {
    vector<char> output;
    queue<char> q;
    unordered_set<char> visited;

    // build adjList
    unordered_map<char, vector<char>> adjList; 
    unordered_map<char, vector<char>> parentsList;
    for (auto dep : dependencies) {
        adjList[dep.first].push_back(dep.second);
        parentsList[dep.second].push_back(dep.first);
    }

    for (char c : projects) {
        if (visited.count(c) > 0) continue;
        if (adjList.count(c) == 0 && parentsList.count(c) == 0) {
           output.push_back(c); 
        } else if(parentsList[c].size() == 0) {
            q.push(c);
                
            while (!q.empty()) {
                char top = q.front();
                q.pop();
                if (visited.count(top) == 0) {
                    for (char dest : adjList[top]) {
                        q.push(dest);
                    }
                    visited.insert(top);
                    output.push_back(top);
                }
            }
        }
    }

    return output;
}

bool isNodeFound(TreeNode* node, TreeNode* target) {
    if (!node) return false;
    if (node == target) return true;
    bool left = isNodeFound(node->left, target);
    bool right = isNodeFound(node->right, target);
    return left || right;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || p == root || q == root) return root;
    bool pInLeft = isNodeFound(root->left, p);
    bool qInLeft = isNodeFound(root->left, q);
    if (pInLeft == qInLeft) {
        if (pInLeft)
            return lowestCommonAncestor(root->left, p, q); 
        return lowestCommonAncestor(root->right, p, q);
    }
    return root;
}

int main() {
    cout << endl << "Successor test:" << endl;
    TreeNode *root = new TreeNode{1};
    root->left = new TreeNode{2};
    root->left->parent = root;
    root->right = new TreeNode{3};
    root->right->parent = root;
    cout << "the in-order successor of 2 is " << findSuccessor(root->left)->val << endl;
    TreeNode *successor = findSuccessor(root->right);
    cout << "the in-order successor of 3 is " << (successor ? successor->val : -1) << endl;

    cout << endl << "Build Order test:" << endl;
    vector<char> projects = {'a', 'b', 'c', 'd', 'e', 'f'};
    vector<pair<char, char>> dependencies = {{'a', 'd'}, {'f', 'b'}, {'b', 'd'}, {'f', 'a'}, {'d', 'c'}};
    vector<char> orderedList = buildOrder(projects, dependencies);
    for (int i = 0; i < orderedList.size(); ++i) {
        cout << orderedList[i] << " ";
    }
    cout << endl;

    cout << endl << "Lowest Common Ancestor test:" << endl;
    
}
