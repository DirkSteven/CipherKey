#include "LoginSystem.h"
#include <iostream>
#include <fstream>

using namespace std;

LoginSystem::LoginSystem(const string& file_path) : loggedIn(false), currentUser(), filename(file_path) {}

bool LoginSystem::addUser(const User& user) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "\t\t\t| Error: Failed to open database file. |\n";
        return false;
    }

    file << user.username << "," << user.password << "\n";
    file.close();
    return true;
}

bool LoginSystem::userExists(const string& username) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        size_t pos = line.find(",");
        string savedUsername = line.substr(0, pos);

        if (savedUsername == username) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;  // User not found
}

User LoginSystem::getUser(const string& username) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        size_t pos = line.find(",");
        string savedUsername = line.substr(0, pos);
        string password = line.substr(pos + 1);

        if (savedUsername == username) {
            file.close();
            return { savedUsername, password };
        }
    }

    file.close();
    return { "", "" };  // User not found
}


bool LoginSystem::registerUser(const string& username, const string& password) {
    if (username.empty() || password.empty()) {
        cout << "\t\t\t| Error: Invalid username or password. |\n";
        return false;
    }

    User user;
    user.username = username;
    user.password = password;

    if (!addUser(user)) {
        cout << "\t\t\t| Error: Failed to register user. |\n";
        return false;
    }
    cout << "\t\t\t| Registration successful! |\n";
    return true;
}

bool LoginSystem::login(const string& username, const string& password) {
    if (loggedIn) {
        cout << "\t\t\t| Error: Already logged in. |\n";
        return false;
    }

    User user = getUser(username);
    if (user.username.empty()) {
        cout << "\t\t\t| Error: User not found.|\n";
        return false;
    }

    if (user.password != password) {
        cout << "\t\t\t| Error: Incorrect password. |\n";
        return false;
    }

    loggedIn = true;
    currentUser = user;

    return true;
};

void LoginSystem::logout() {
    if (!loggedIn) {
        cout << "\t\t\t| Error: Not logged in. |\n";
        return;
    }

    loggedIn = false;
    currentUser = User();

    cout << "\t\t\t| Logged out successfully. |\n";
} 