#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Node {
    Node *next;
    string val;

    Node(string val) : next{nullptr}, val{val} {} 
};

class LinkedList {
private:
    Node *head = nullptr;
public:
    LinkedList(Node *node): head{node} {}
    LinkedList(vector<string> input) {
        for (int i = input.size() - 1; i >= 0; --i) {
            pushFront(new Node{input[i]});
        }
    }
    ~LinkedList() { delete head; }

    Node* front() {
        return head;
    }

    void pushFront(Node *newNode) {
        newNode->next = head;
        head = newNode;
    }

    void popFront() {
        Node *prev = head;
        head = head->next;
        prev->next = nullptr;
        delete prev;
    }

    void print() {
        Node *cur = head;
        while (cur != nullptr) {
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

Node* deleteDupsWithBuffers(Node* head) {
    unordered_set<string> uniqueNodes;
    Node* prev = nullptr;
    Node* cur = head;

    while (cur != nullptr) {
        if (uniqueNodes.count(cur->val) > 0) {
            prev->next = cur->next;
        } else {
            uniqueNodes.insert(cur->val);
            prev = cur;
        }
        cur = cur->next;
    }

    return head;
}

Node* findKFromLast(Node* head, int k, int &i) {
    if (head == nullptr) return head;
    Node *nd = findKFromLast(head->next, k, i);
    if (++i == k) {
        return head;
    }
    return nd;
}

Node* deleteMiddleNode(Node *head) {
    if (head == nullptr || head->next == nullptr) return head; 
    Node *slow = head, *fast = head->next, *prev = nullptr; 

    while (fast != nullptr && fast->next != nullptr) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = slow->next;
    return slow;
}

Node* partition(Node* node, string val) {
    Node *head = node;
    Node *tail = node;

    while (node != nullptr) {
        Node* next = node->next;
        if (stoi(node->val) < stoi(val)) {
            node->next = head;
            head = node;
        } else {
            tail->next = node;
            tail = node;
        }
        node = next;
    }
    tail->next = nullptr;

    return head;
}

// driver code
int main() {
    // deleteDups test
    cout << endl << "deleteDups test:" << endl;
    vector<string> input1 = {"1", "1", "2", "2", "1", "3", "4", "5"};
    LinkedList list1(input1);
    cout << "before: "; 
    list1.print();
    deleteDupsWithBuffers(list1.front());
    cout << "after: ";
    list1.print();

    // findKFromLast test
    cout << endl << "findKFromLast test:" << endl;
    int i = 0, k = 2;
    Node *kElem = findKFromLast(list1.front(), k, i);
    cout << k << " elems from last is: " << kElem->val << endl;

    // deleteMiddleNode test
    cout << endl << "deleteMiddleNode test:" << endl;
    Node *deletedNode = deleteMiddleNode(list1.front());
    cout << "Deleted Node: " << deletedNode->val << endl;
    list1.print();
    
    // partition test
    cout << endl << "partition test:" << endl;
    Node *newListHead = partition(list1.front(), "4");
    LinkedList list2(newListHead);
    list2.print();

    return 0;
}
