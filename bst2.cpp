#include <iostream>
#include <algorithm> // Required for max() function
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
    Node* root;
    
    Node* insertHelper(Node* node, int val) {
        if(!node) return new Node(val);
        
        if(val < node->data) {
            node->left = insertHelper(node->left, val);
        }
        else {
            node->right = insertHelper(node->right, val);
        }
        return node;
    }

    bool searchHelper(Node* node, int val) {
        if(!node) return false;
        if(val == node->data) return true;
        return val < node->data ? searchHelper(node->left, val) 
                              : searchHelper(node->right, val);
    }
    
    int heightHelper(Node* node) {
        if(!node) return 0;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

    void mirrorHelper(Node* node) {
        if(!node) return;
        swap(node->left, node->right);
        mirrorHelper(node->left);
        mirrorHelper(node->right);
    }

    void displayHelper(Node* node) {
        if(!node) return;
        displayHelper(node->left);
        cout << node->data << " ";
        displayHelper(node->right);
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) {
        root = insertHelper(root, val);
    }

    bool search(int val) {
        return searchHelper(root, val);
    }

    int findMin() {
        if(!root) {
            cerr << "Tree is empty!" << endl;
            return -1;
        }
        Node* current = root;
        while(current->left) {
            current = current->left;
        }
        return current->data;
    }

    int findHeight() {
        return heightHelper(root);
    }

    void mirror() {
        mirrorHelper(root);
    }

    void display() {
        displayHelper(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    
    // Test insertion
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    
    cout << "Original tree: ";
    tree.display();
    
    // Test search
    cout << "Search 40: " << (tree.search(40) ? "Found" : "Not found") << endl;
    cout << "Search 99: " << (tree.search(99) ? "Found" : "Not found") << endl;
    
    // Test min and height
    cout << "Minimum value: " << tree.findMin() << endl;
    cout << "Tree height: " << tree.findHeight() << endl;
    
    // Test mirror
    tree.mirror();
    cout << "Mirrored tree: ";
    tree.display();
    
    return 0;
}