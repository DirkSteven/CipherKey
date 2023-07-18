#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
#include <fstream>

using namespace std;

class PasswordItem {
    string label;
    string data;

    PasswordItem(string label, string data) {
        this->label = label;
        this->data = data;
    }
};

class PasswordNode {
public:
    string password;
    PasswordNode* next;

    PasswordNode(const string& pass) : password(pass), next(nullptr) {}
};



class PasswordManager {
private:
    PasswordNode* passwordList;
    PasswordNode* tempList;
    PasswordNode* labelList;

    string currentUser;
    string db_data = "db/data.csv";
    
    ofstream database;

public:
    PasswordManager();
    ~PasswordManager();

    void setCurrentUser(const string& username) {
        this->currentUser = username;
    };

    void addPassword(const string& password);
    void updatePassword(const string& item, const string& label, string new_password);
    void loadPassword();
    void savePasswords();
    void printPasswords();

    void deleteItem(const string& itemToDelete);
    bool itemExist(const string& item);

    void clearTempPasswords();
    void clearMainPasswords();
    void resetPasswords();

};

#endif  // PASSWORD_MANAGER_H
