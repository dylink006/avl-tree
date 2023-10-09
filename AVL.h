#pragma once
#include <iostream>
using namespace std;

struct Node {
    string name;
    string ufid;
    int height;
    Node* left;
    Node* right;
    Node(string n, string u) : name(n), ufid(u), left(nullptr), right(nullptr) , height(1) {}
};

class AVLTree {
private:
    void updateHeight(Node* node) {
        if (node == nullptr) {
            return;
        }

        int LH = 0;
        int RH = 0;

        if (node->left != nullptr) {
            LH = node->left->height;
        }
        if (node->right != nullptr) {
            RH = node->right->height;
        }

        node->height = 1 + max(LH, RH);
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int LH = 0;
        int RH = 0;

        if (node->left != nullptr) {
            LH = node->left->height;
        }
        if (node->right != nullptr) {
            RH = node->right->height;
        }

        return LH - RH;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* z = x->right;

        x->right = y;
        y->left = z;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* y) {
        Node* x = y->right;
        Node* z = x->left;

        x->left = y;
        y->right = z;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* insertHelper(Node* node, string name, string ufid) {
        if (node == nullptr) {
            return new Node(name, ufid);
        }

        if (stoi(ufid) < stoi(node->ufid)) {
            node->left = insertHelper(node->left, name, ufid);
        }
        else {
            node->right = insertHelper(node->right, name, ufid);
        }

        updateHeight(node);

        int bf = balanceFactor(node);

        if (bf > 1) {
            if (stoi(ufid) < stoi(node->left->ufid)) {
                return rotateRight(node);
            }
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (bf < -1) {
            if (stoi(ufid) > stoi(node->right->ufid)) {
                return rotateRight(node);
            }
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    bool isInTreeHelper(Node* node, string& ID) {
        if (node == nullptr) {
            return false;
        }
        if (ID == node->ufid) {
            return true;
        }
        else if (stoi(ID) < stoi(node->ufid)) {
            return isInTreeHelper(node->left, ID);
        }
        else {
            return isInTreeHelper(node->right, ID);
        }
    }

    void printInOrderHelper(Node* node, Node* lastNode) {
        if (node == nullptr) {
            return;
        }

        printInOrderHelper(node->left, lastNode);
        cout << node->name;
        if (node != lastNode) {
            cout << ", ";
        }

        printInOrderHelper(node->right, lastNode);
    }

    void printPostOrderHelper(Node* node) {
        if (node == nullptr) {
            return;
        }

        printPostOrderHelper(node->left);
        printPostOrderHelper(node->right);

        cout << node->name;
        if (node != root) {
            cout << ", ";
        }
    }

    void printPreOrderHelper(Node* node, Node* lastN) {
        if (node == nullptr) {
            return;
        }

        cout << node->name;
        if (node != lastN) {
            cout << ", ";
        }

        printPreOrderHelper(node->left, lastN);
        printPreOrderHelper(node->right, lastN);
    }

    Node* inorderSuccessor(Node* node) {
        Node* current = node;
        while (current ->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* RemoveHelper(Node* node, string ID) {
        if (node == nullptr) {
            return node;
        }
        if (stoi(ID) < stoi(node->ufid)) {
            node->left = RemoveHelper(node->left, ID);
        }
        else if (stoi(ID) > stoi(node->ufid)) {
            node->right = RemoveHelper(node->right, ID);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp;
                if (node->left != nullptr) {
                    temp = node->left;
                }
                else {
                    temp = node->right;
                }

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                    delete temp;
                }
            }
            else {
                Node* temp = inorderSuccessor(node->right);
                node->ufid = temp->ufid;
                node->name = temp->name;
                node->right = RemoveHelper(node->right, temp->ufid);
            }
        }

        updateHeight(node);
        int bf = balanceFactor(node);

        if (bf > 1 && balanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        if (bf < -1 && balanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    int numNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + numNodes(node->left) + numNodes(node->right);
    }


     string getNthIDHelper(Node* node, int& n) {
        if (node == nullptr) {
            return "";
        }
        string nthID = getNthIDHelper(node->left, n);
        if (!nthID.empty()) {
            return nthID;
        }

        if (n-- == 0) {
            return node->ufid;
        }

        return getNthIDHelper(node->right, n);
    }

    string getNthID(int n) {
        int numOfNodes = numNodes(root);
        if (n < 0 || n > numOfNodes) {
            return "";
        }
        return getNthIDHelper(root, n);
    }

    Node* getLastInorder(Node* node) {
        if (node == nullptr) {
           return nullptr;
        }
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    Node* getLastPreorder(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->right != nullptr) {
            node = node->right;
        }
        if (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    string searchIDHelper(Node* node, string& ID) {
        if (node == nullptr) {
            return "";
        }
        if (ID < node->ufid) {
            return searchIDHelper(node->left, ID);
        }
        else if (ID > node->ufid) {
            return searchIDHelper(node->right, ID);
        }
        else {
            return node->name;
        }
    }

    void searchNameHelper(Node* node, string& name, vector<string>& IDs) {
        if (node == nullptr) {
            return;
        }
        if (node->name == name) {
            IDs.push_back(node->ufid);
        }
        searchNameHelper(node->left, name, IDs);
        searchNameHelper(node->right, name, IDs);
    }
public:
    Node* root;
    void Insert(string name, string ufid) {
        root = insertHelper(root, name, ufid);
    };

    void printPreOrder() {
        Node* lastN = getLastPreorder(root);
        printPreOrderHelper(root, lastN);
        cout << endl;
    }

    void printInOrder() {
        Node* lastN = getLastInorder(root);
        printInOrderHelper(root, lastN);
        cout << endl;
    }

    void printPostOrder() {
        printPostOrderHelper(root);
        cout << endl;
    }

    bool isInTree(string& ID) {
        return isInTreeHelper(root, ID);
    }

    void Remove(string& ID) {
        if (isInTree(ID)) {
            root =  RemoveHelper(root, ID);
        }
    }

    void removeInorder(int& n) {
        string nID = getNthID(n);
        if (nID == "") {
            cout << "unsuccessful" << endl;
        }
        else {
            Remove(nID);
            cout << "successful" << endl;
        }
    }

    void searchID(string& ID) {
        string name = searchIDHelper(root, ID);
        cout << name << endl;
    }

    void searchName(string& name) {
        vector<string> IDs;
        searchNameHelper(root, name, IDs);
        for (int i = 0; i < IDs.size(); i++) {
            cout << IDs.at(i) << endl;
        }
    }

    void printLevels() {
        if (root == nullptr) {
            cout << "0" << endl;
        }
        else {
            cout << root->height << endl;
        }
    }

    AVLTree() {
        this->root = nullptr;
    }
};