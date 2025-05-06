#include <iostream>
#include <string>
using namespace std;

// Node for Dictionary BST
class DictionaryNode {
public:
    string word;
    string meaning;
    DictionaryNode* left;
    DictionaryNode* right;

    DictionaryNode(string w = "", string m = "") {
        word = w;
        meaning = m;
        left = right = nullptr;
    }

    // Insert word and meaning
    DictionaryNode* insert(DictionaryNode* root, string w, string m) {
        if (root == nullptr)
            return new DictionaryNode(w, m);

        if (w < root->word)
            root->left = insert(root->left, w, m);
        else if (w > root->word)
            root->right = insert(root->right, w, m);
        else
            cout << "Duplicate word ignored: " << w << endl;

        return root;
    }

    // In-order display (ascending)
    void displayAscending(DictionaryNode* root) {
        if (root != nullptr) {
            displayAscending(root->left);
            cout << root->word << " - " << root->meaning << endl;
            displayAscending(root->right);
        }
    }

    // Reverse in-order display (descending)
    void displayDescending(DictionaryNode* root) {
        if (root != nullptr) {
            displayDescending(root->right);
            cout << root->word << " - " << root->meaning << endl;
            displayDescending(root->left);
        }
    }

    // Search with comparison count
    bool searchWord(DictionaryNode* root, string key) {
        int comparisons = 0;
        while (root != nullptr) {
            comparisons++;
            if (key == root->word) {
                cout << "\nWord found in " << comparisons << " comparisons.\n";
                return true;
            }
            root = (key < root->word) ? root->left : root->right;
        }
        cout << "\nWord not found.\n";
        return false;
    }

    // Update meaning of existing word
    void updateMeaning(DictionaryNode* root, string key) {
        while (root != nullptr) {
            if (key == root->word) {
                cout << "Enter new meaning for \"" << key << "\": ";
                cin >> root->meaning;
                return;
            }
            root = (key < root->word) ? root->left : root->right;
        }
        cout << "Word not found.\n";
    }

    // Delete a word from BST
    DictionaryNode* deleteWord(DictionaryNode* root, string key) {
        if (root == nullptr) return nullptr;

        if (key < root->word)
            root->left = deleteWord(root->left, key);
        else if (key > root->word)
            root->right = deleteWord(root->right, key);
        else {
            // Node with 0 or 1 child
            if (root->left == nullptr) {
                DictionaryNode* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                DictionaryNode* temp = root->left;
                delete root;
                return temp;
            }

            // Node with 2 children: find inorder successor
            DictionaryNode* successor = findMin(root->right);
            root->word = successor->word;
            root->meaning = successor->meaning;
            root->right = deleteWord(root->right, successor->word);
        }
        return root;
    }

    // Find node with minimum word (used for deletion)
    DictionaryNode* findMin(DictionaryNode* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }
};

// --- Example usage ---
int main() {
    DictionaryNode dict;
    DictionaryNode* root = nullptr;

    // Add sample entries
    root = dict.insert(root, "banana", "a yellow fruit");
    root = dict.insert(root, "apple", "a red or green fruit");
    root = dict.insert(root, "grape", "a small purple fruit");
    root = dict.insert(root, "orange", "a citrus fruit");

    cout << "\nAscending Order (A-Z):\n";
    dict.displayAscending(root);

    cout << "\nDescending Order (Z-A):\n";
    dict.displayDescending(root);

    cout << "\nSearching for 'grape':\n";
    dict.searchWord(root, "grape");

    cout << "\nUpdating meaning of 'apple':\n";
    dict.updateMeaning(root, "apple");

    cout << "\nAfter Deleting 'banana':\n";
    root = dict.deleteWord(root, "banana");
    dict.displayAscending(root);

    return 0;
}
