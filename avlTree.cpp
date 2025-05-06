#include<iostream>
#include<string>
using namespace std;

class avlnode {
public:
    string keyword;
    string meaning;
    avlnode *left, *right;
    int bf; // Balance factor (Height of left subtree - Height of right subtree)

    avlnode() {
        keyword = '\0';
        meaning = '\0';
        left = right = NULL;
        bf = 0;
    }

    avlnode(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = NULL;
        bf = 0;
    }

    void LLrotation(avlnode *a, avlnode *b) {
        cout << "LL rotation" << endl;
        a->left = b->right;
        b->right = a;
        a->bf = b->bf = 0;
    }

    void RRrotation(avlnode *a, avlnode *b) {
        cout << "RR rotation" << endl;
        a->right = b->left;
        b->left = a;
        a->bf = b->bf = 0;
    }

    void inorder(avlnode *root) {
        if (root) {
            inorder(root->left);
            cout << root->keyword << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    void descending(avlnode *root) {
        if (root) {
            descending(root->right);
            cout << root->keyword << " : " << root->meaning << endl;
            descending(root->left);
        }
    }

    void update(avlnode *root, string key) {
        while (root != NULL) {
            if (root->keyword == key) {
                cout << "Enter new meaning of the word " << root->keyword << endl;
                cin >> root->meaning;
                return;
            }
            else if (key > root->keyword)
                root = root->right;
            else
                root = root->left;
        }
        cout << "\nWord not found" << endl;
    }

    avlnode* insert(avlnode *root, string key, string mean);
};

avlnode* avlnode::insert(avlnode *root, string key, string mean) {
    if (!root) {
        root = new avlnode(key, mean);
        cout << "ROOT CREATED \n";
        return root;
    }

    avlnode *a, *pa, *p, *pp;
    pa = NULL;
    p = a = root;
    pp = NULL;
    while (p) {
        if (p->bf) {
            a = p;
            pa = pp;
        }
        if (key < p->keyword) {
            pp = p;
            p = p->left;
        } else if (key > p->keyword) {
            pp = p;
            p = p->right;
        } else {
            cout << "Already exists\n";
            return root;
        }
    }

    avlnode *y = new avlnode(key, mean);
    if (key < pp->keyword)
        pp->left = y;
    else
        pp->right = y;
    cout << "KEY INSERTED \n";

    int d;
    avlnode *b, *c;
    b = c = NULL;
    if (key > a->keyword) {
        cout << "KEY > A->KEYWORD \n";
        b = p = a->right;
        d = -1;
        cout << "RIGHT HEAVY \n";
    } else {
        cout << "KEY < A->KEYWORD \n";
        b = p = a->left;
        d = 1;
        cout << "LEFT HEAVY \n";
    }

    while (p != y) {
        if (key > p->keyword) {
            p->bf = -1;
            p = p->right;
        } else {
            p->bf = 1;
            p = p->left;
        }
    }

    cout << "DONE ADJUSTING INTERMEDIATE NODES \n";
    if (!(a->bf) || !(a->bf + d)) {
        a->bf += d;
        return root;
    }

    if (d == 1) {
        if (b->bf == 1)
            LLrotation(a, b);
        else {
            cout << "LR rotation" << endl;
            c = b->right;
            b->right = c->left;
            a->left = c->right;
            c->left = b;
            c->right = a;
            switch (c->bf) {
            case 1:
                a->bf = -1;
                b->bf = 0;
                break;
            case -1:
                a->bf = 0;
                b->bf = 1;
                break;
            case 0:
                a->bf = 0;
                b->bf = 0;
                break;
            }
            c->bf = 0;
            b = c;
        }
    }

    if (d == -1) {
        if (b->bf == -1)
            RRrotation(a, b);
        else {
            c = b->left;
            a->right = c->left;
            b->left = c->right;
            c->left = a;
            c->right = b;
            switch (c->bf) {
            case 1:
                a->bf = 0;
                b->bf = -1;
                break;
            case -1:
                a->bf = 1;
                b->bf = 0;
                break;
            case 0:
                a->bf = 0;
                b->bf = 0;
                break;
            }
            c->bf = 0;
            b = c;
        }
    }

    if (!pa)
        root = b;
    else if (a == pa->left)
        pa->left = b;
    else
        pa->right = b;

    cout << "AVL tree created!! \n";
    return root;
}

int main() {
    string key, mean;
    avlnode *root = NULL, a;

    // Example Insertions
    root = a.insert(root, "hello", "a greeting");
    root = a.insert(root, "world", "the earth, together with all of its countries and peoples");
    root = a.insert(root, "dictionary", "a reference book of words and their meanings");

    // Example Update
    a.update(root, "hello");

    // Display in ascending order
    cout << "\nAscending Order:\n";
    a.inorder(root);

    // Display in descending order
    cout << "\nDescending Order:\n";
    a.descending(root);

    return 0;
}
