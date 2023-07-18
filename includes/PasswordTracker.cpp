#include "PasswordTracker.h"
#include "EncryptDecryptLib.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
EncryptDecryptLib edl;


PasswordManager::PasswordManager() : passwordList(nullptr), tempList(nullptr) {}

PasswordManager::~PasswordManager() {
    PasswordNode* current = passwordList;
    while (current) {
        PasswordNode* temp = current;
        current = current->next;
        delete temp;
    }
}

void PasswordManager::addPassword(const string& password) {
    PasswordNode* newNode = new PasswordNode(password);
    if (!passwordList) {
        passwordList = newNode;
    } else {
        PasswordNode* current = passwordList;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    loadPassword();
}

bool PasswordManager::itemExist(const string& item) {
    ifstream file(db_data);
    if (!file) {
        cerr << "\t\t\t| Error: Failed to open database file. |\n";
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        size_t pos = line.find(",");
        string savedUsername = line.substr(0, pos);

        if (item == savedUsername) {
            return true;                                      
        }
    }
    file.close();
    return false;
}

void PasswordManager::deleteItem(const string& itemToDelete) {
    ifstream inFile(db_data);
    if (!inFile) {
        cerr << "\t\t\t|Error: Failed to open file.|\n";
        return;
    }

    vector<string> lines;
    string line;
    bool labelFound = false; 

    while (getline(inFile, line)) {
        size_t pos = line.find(",");
        string savedLabel = line.substr(0, pos);

        if (savedLabel == itemToDelete) {
            labelFound = true;
        } else {
            lines.push_back(line);
        }
    }
    inFile.close();

    if (!labelFound) {
        cout << "\t\t\t|Label does not exist! |\n";
        return;
    }

    ofstream outFile(db_data);
    if (!outFile) {
        cerr << "\t\t\t|Error: Failed to open file for writing.|\n";
        return;
    }

    for (const string& line : lines) {
        outFile << line << '\n';
    }
    outFile.close();

    
    clearMainPasswords();
}

void PasswordManager::resetPasswords() {
    ifstream file(db_data);
    if (!file) {
        cerr << "Error: Failed to open database file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {

        stringstream ss(line);
        size_t pos = line.find(",");

        string savedUsername = line.substr(0, pos);

        string label = line.substr(pos + 1);
        pos = label.find(",");
        label = label.substr(0, pos);

        pos = savedUsername.find("-");

        string n_username = savedUsername.substr(0, pos);
        string n_currentUser = currentUser + '-' + edl.decrypt_text(label);

        if (edl.decrypt_text(n_username) == n_currentUser)
        deleteItem(edl.encrypt_text(n_currentUser));
        

    }
    cout << "\n\t\tPasswords for the account " + currentUser + " successfully deleted.\n";

    file.close();
}

void PasswordManager::savePasswords() {
    
    PasswordNode* newNode;
    if (!passwordList) {
        passwordList = newNode;
    } else {
        PasswordNode* current = passwordList;
        
        ofstream file(db_data, ios::app);
        if (!file) {
            cerr << "\t\t\t| Error: Failed to open database file |\n";
            return;
        }

        while (current) {
            file << edl.encrypt_text(current->password);
            if (current->next != NULL) {
                file << ",";
            }
            current = current->next;
        }

        file << "\n";
        file.close();
    }
    clearMainPasswords();

    
}

void PasswordManager::loadPassword() {
    
    ifstream file(db_data);
    if (!file) {
        cerr << "\t\t\t| Error: Failed to open database file. |\n";
        return;
    }


    string line;
    while (getline(file, line)) {

        // cout << line << endl;
        stringstream ss(line);

        size_t pos = line.find(",");
        string savedUsername = line.substr(0, pos);

        string label = line.substr(pos + 1);
        string tempLabel = label;
        pos = label.find(",");

        label = label.substr(0, pos);
        string passWD = tempLabel.substr(pos + 1);

        string data = "\t\t\t" + edl.decrypt_text(label) + "\t\t   |\t" + edl.decrypt_text(passWD);

        pos = savedUsername.find("-");
        string n_username = savedUsername.substr(0, pos);

        string n_currentUser = currentUser + '-' + edl.decrypt_text(label);

        if (edl.decrypt_text(n_username) == n_currentUser) {
    
            PasswordNode* newNode = new PasswordNode(data);
            if (!tempList) {
                tempList = newNode;
            } else {
                PasswordNode* current = tempList;
                while (current->next) {
                    current = current->next;
                }
                current->next = newNode;
            }     
        }
    }

    file.close();
}

void PasswordManager::printPasswords() {
    loadPassword();
    if (!tempList) {
        cout << "\t\t\t| No passwords found |\n";
        return;
    }
    PasswordNode* current = tempList;
    while (current) {
        cout << current->password << endl; 
        current = current->next;
    }
    clearTempPasswords();
}

void PasswordManager::updatePassword(const string& item, const string& label, string new_password) {
    if(itemExist(item)){
        deleteItem(item);

        cout << "\tWhat is your new " << label << "'s password? "; getline(cin, new_password);
        addPassword(edl.decrypt_text(item));

        edl.encrypt_text(label);
        edl.encrypt_text(new_password);
        addPassword(label);
        addPassword(new_password);

        savePasswords();     
        cout << "\n";
        cout << "\t\t\t | New Password: Saved! |\n";
    }
    else {
        cout << "\t\t\t| Label does not exist! |\n" << endl;
    }
        clearMainPasswords();
        clearTempPasswords();
}

void PasswordManager::clearTempPasswords() {
    PasswordNode* current = tempList;
    while (current) {
        PasswordNode* next = current->next;
        delete current;
        current = next;
    }
    tempList = nullptr;
}

void PasswordManager::clearMainPasswords() {
    PasswordNode* current = passwordList;
    while (current) {
        PasswordNode* next = current->next;
        delete current;
        current = next;
    }
    passwordList = nullptr;
}