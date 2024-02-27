// Zoe Dauphinee, recitation 14, recursion

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;

// Node type for the linked list
struct Node {
    int data;
    Node* next = nullptr;
};

// Node type for the binary tree
struct TNode {
    int data;
    TNode *left = nullptr, *mid = nullptr, *right = nullptr;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);

//
// Your functions go here
//
//   Task 1 function:
Node* listSum(const Node* curr1, const Node* curr2) {
    if (curr1 == nullptr && curr2 == nullptr) {
        return nullptr;
    }

    int data1 = 0;
    int data2 = 0;
    const Node* next1 = nullptr;
    const Node* next2 = nullptr;

    if (curr1 != nullptr) {
        data1 = curr1->data;
        next1 = curr1->next;
    }
    if (curr2 != nullptr) {
        data2 = curr2->data;
        next2 = curr2->next;
    }
    Node* new_node = new Node;
    new_node->data = data1 + data2;
    new_node->next = listSum(next1, next2);

    return new_node;
}

//   Task 2 function:
int treeMax(TNode *root) {
    if (root == nullptr) {
        throw invalid_argument("Tree is empty");
    }

    int curr_max = root->data;

    if (root->left != nullptr) {
        curr_max = max(curr_max, treeMax(root->left));
    }
    if (root->mid != nullptr) {
        curr_max = max(curr_max, treeMax(root->mid));
    }
    if (root->right != nullptr) {
        curr_max = max(curr_max, treeMax(root->right));
    }

    return curr_max;
}

//   Task 3 function:
bool palindrome(char* letter, int length) {
    if (length <= 1) {
        return true;
    }
    if (*letter != letter[length - 1]) {
        return false;
    }
    return palindrome(letter + 1, length - 2);
}

//   Task 4 function:
bool parity(int num) {
    if (num == 0) { return true; }
    if (num % 2 == 1) { return !parity(num / 2); }
    else { return parity(num / 2); }
}

//   Task 5 function:
int towers(int num_disks, char start, char target, char spare) {
    if (num_disks == 0) { return 1; }
    return 1 + towers(num_disks - 1, start, spare, target) + towers(num_disks - 1, spare, target, start);
}

//   Task 6
void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; 
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
   } 
   cout << 'c'; 
}


// test code
int main() {
    // We have provided some test code to save you time. Certainly fee
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);
    
    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);

    
    // Task 2:
    TNode a{1}, b{2}, c{4}, d{-8, &a, &b, &c}, e{-16, &c}, f{-32, &d, &e};
    cout << "treeMax(&f): " << treeMax(&f) << endl;

    // How do you keep this from crashing? try/catch! In main!
    try {
        cout << treeMax(nullptr) << endl;
    }
    catch (const invalid_argument& error) {
        cout << "Error: " << error.what() << endl;
    }

    
    // Task 3:
    cout << "\n==============\n"
	 << "#3) Testing palindrome\n";
    cout << boolalpha
	 << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
	 << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
	 << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
	 << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;


    // Task 4:
    cout << "\n==============\n"
	 << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }


    // Task 5:
    cout << "\n==============\n"
	 << "#5) How many moves are required for various sized towers?\n";
    for (int i = 1; i < 30; ++i) {
	cout << "towers(" << i << ", 'a', 'b', 'c'): " 
	     << towers(i, 'a', 'b', 'c') << endl;
    }


    // Task 6:
    for (int i = 0; i < 11; ++i) {
	    mystery(i);
        cout << endl;
    }
}




//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
	result = new Node{vals[index-1], result};
    }
    return result;
}