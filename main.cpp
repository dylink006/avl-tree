#include <iostream>
#include <sstream>
#include "AVL.h"
using namespace std;

bool validateName(string name) {
    for (char c : name) {
        if (!(islower(c) || isupper(c) || isspace(c))) {
            return false;
        }
    }
    return true;
}

bool validateID(string ID) {
    if (ID.length() != 8) {
        return false;
    }

    for (char c : ID) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool isNum(string& s) {
    if (s.empty()) {
        return false;
    }
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int main() {
    AVLTree t;

    //read in the number of commands
    //Execute them on t

    string numCommands;
    cin >> numCommands;
    cin.ignore();

    for (int i = 0; i < stoi(numCommands) + 1; i++) {
        string line;
        getline(cin, line);

        istringstream in(line);

        string command;
        in >> command;

        if (command == "insert") {
            string name;
            getline(in, name, '"');
            getline(in, name, '"');

            string ID;
            getline(in, ID, ' ');
            getline(in, ID, '"');

            if (validateName(name) && validateID(ID)) {
                if (!t.isInTree(ID)) {
                    t.Insert(name, ID);
                    cout << "successful" << endl;
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else if (command == "remove") {
            string ID;
            getline(in, ID, ' ');
            getline(in, ID, '"');

            if (validateID) {
                t.Remove(ID);
                cout << "successful" << endl;
            }
        }
        else if (command == "removeInorder") {
            string num;
            getline(in, num, ' ');
            getline(in, num, '"');

            int inum = stoi(num);

            t.removeInorder(inum);
        }
        else if (command == "search") {
            string IDorName;
            getline(in, IDorName, ' ');
            getline(in, IDorName, '"');

            if (isNum(IDorName)) {
                if (validateID(IDorName)) {
                    t.searchID(IDorName);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                if (validateName(IDorName)) {
                    t.searchName(IDorName);
                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
        }
        else if (command == "printInorder") {
            t.printInOrder();
        }
        else if (command == "printPreorder") {
            t.printPreOrder();
        }
        else if (command == "printPostorder") {
            t.printPostOrder();
        }
        else if (command == "printLevelCount") {
            t.printLevels();
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}