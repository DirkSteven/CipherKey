#ifndef LOGIN_SYSTEM_H
#define LOGIN_SYSTEM_H

#include <string>

using namespace std;

class User {
public:
    string username;
    string password;
    
};

class LoginSystem {
private:
    bool loggedIn;
    User currentUser;
    string filename;
    

public:
    LoginSystem(const string& file);

    bool addUser(const User& user);
    User getUser(const string& username);

    bool registerUser(const string& username, const string& password);
    bool userExists(const string& username);

    bool login(const string& username, const string& password);
    void logout();
};

#endif  // LOGIN_SYSTEM_H