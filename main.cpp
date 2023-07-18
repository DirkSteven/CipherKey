#include "includes/LoginSystem.h"
#include "includes/PasswordTracker.h"
#include "includes/EncryptDecryptLib.h"

#include "includes/LoginSystem.cpp"
#include "includes/PasswordTracker.cpp"
#include "includes/EncryptDecryptLib.cpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
    LoginSystem loginSystem("db/users.csv");
    EncryptDecryptLib edl;
    string currentUser, label, item, accountName;
    string ans = "y";
    PasswordManager passwordManager;

    string choice;
    do {
        system("cls"); // Clear the console screen

        // Center align the main UI
        int consoleWidth = 80;
        int mainUiWidth = 60;
        int leftPadding = (consoleWidth - mainUiWidth) / 2;

        cout << string(leftPadding, ' ') << "=================================================================\n";
        cout << string(leftPadding, ' ') << "        CipherKey | Encrypted Password Manager\n";
        cout << string(leftPadding, ' ') << "=================================================================\n";
        cout << string(leftPadding, ' ') << "        \"Fortify Your Passwords with Advanced Encryption\"\n\n";

        cout << string(leftPadding, ' ') << ">> Please select an option: \n";
        if (currentUser.empty()) {
            cout << string(leftPadding, ' ') << "1. Register\n";
            cout << string(leftPadding, ' ') << "2. Login\n";
            cout << string(leftPadding, ' ') << "3. Exit\n\n";
        } else {
            cout << string(leftPadding, ' ') << "1. Record new Password\n";
            cout << string(leftPadding, ' ') << "2. Update Passwords\n";
            cout << string(leftPadding, ' ') << "3. Delete Passwords\n";
            cout << string(leftPadding, ' ') << "4. View Passwords\n";
            cout << string(leftPadding, ' ') << "5. Reset Passwords\n";
            cout << string(leftPadding, ' ') << "6. Logout\n\n";
        }

        cout << string(leftPadding, ' ') << ">> Choice: ";

        
        cin >> choice;

  
        cout << "\n";

        cin.ignore(); // Ignore remaining characters in input buffer

        string username, password, new_password;

        if (currentUser.empty()) {
            switch (choice[0]) {
                case '1':
                    cout << "\t\t\t\t>> Register <<\n";
                    cout << "\tEnter username: ";
                    getline(cin, username);
                    cout << "\tEnter password: ";
                    getline(cin, password);
                    cout << "\n";

                    password = edl.encrypt_text(password);
                    if (!loginSystem.userExists(username))
                        loginSystem.registerUser(username, password);
                    else
                       
                        cerr << "\t\t\t| User already exists. Try another username. |\n"; 
                        cout <<"\t\t\t | ENTER ANY KEY TO CONTINUE |\n";  
                        
                    cin.ignore();
                    break;
                case '2':
                    cout << "\t\t\t\t>> Log In <<\n";
                    cout << "\tEnter username: ";
                    getline(cin, username);
                    cout << "\tEnter password: ";
                    getline(cin, password);
                    password = edl.encrypt_text(password);
                    cout << "\n";

                    if (loginSystem.login(username, password)) {
                        currentUser = username;
                        passwordManager.setCurrentUser(currentUser);

                        cout << "\t\t\t| Logged in successfully! |\n\n\n";
                        
                        cout <<"\t\t\t| ENTER ANY KEY TO CONTINUE |\n";
                    }
                    cin.ignore();
                    
                    break;
                case '3':
                    cout << "\t\t\t\t >> Exiting... <<\n";
                    return 0;
                default:
                    cout << "\t\t\t| Invalid choice. Please try again. |\n";
                    break;
            }
        } else {
            switch (choice[0]) {
                case '1':
                    cout << "\t\t\t>> Record New Password <<\n";
                    passwordManager.clearMainPasswords();

                    cout << "\tPassword Label: ";
                    getline(cin, label);
                    item = currentUser + "-" + label;

                    if (passwordManager.itemExist(edl.encrypt_text(item))) {
                        cout << "\tLabel already exists. Do you want to update? [Y|N] ";
                        getline(cin, ans);
                        if (ans == "y" || ans == "Y") {
                            passwordManager.updatePassword(edl.encrypt_text(item), label, new_password);
                        }
                    } else {
                        passwordManager.addPassword(item);
                        passwordManager.addPassword(label);
                        cout << "\tPassword for " << label << " to be saved: ";
                        getline(cin, password);
                        passwordManager.addPassword(password);
                        passwordManager.savePasswords();
                        cout << "\n\t\t\t| New Password: Saved! |\n\n\n";
                        cout <<"\t\t\t| ENTER ANY KEY TO CONTINUE |\n";
                    }
                    passwordManager.clearTempPasswords();
                    cin.ignore();
                    break;
                case '2':
                    cout << "\t\t\t>> Update Passwords <<\n";
                    cout << "\t\t========= Passwords in your Vault ==========\n";
                    passwordManager.printPasswords();
                    cout << "\t\t============================================\n";
                    cout << "\tWhich password do you want to update? [LABEL] ";
                    getline(cin, label);
                    item = currentUser + "-" + label;
                    item = edl.encrypt_text(item);
                    passwordManager.updatePassword(item, label, new_password);
                    cout <<"\t\t\t| ENTER ANY KEY TO CONTINUE |\n";
                    cin.ignore();
                    break;
                case '3':
                    cout << "\t\t\t>> Delete Passwords <<\n";
                    cout << "\t\t========= Passwords in your Vault ==========\n";
                    passwordManager.printPasswords();
                    cout << "\t\t============================================\n";
                    cout << "\tWhich password do you want to delete? [LABEL] ";
                    getline(cin, label);
                    item = currentUser + "-" + label;
                    item = edl.encrypt_text(item);
                    passwordManager.deleteItem(item);
                    cout << "\n\t\t\t| Item deleted successfully! |\n";
                    cout <<"\t\t\t| ENTER ANY KEY TO CONTINUE |\n";
                    choice = "777";
                    cin.ignore();
                    break;
                case '4':
                    cout << "\t\t========= Passwords in your Vault ==========\n";
                    passwordManager.printPasswords();
                    cout << "\t\t============================================\n";
                    cin.ignore();
                    break;
                case '5':
                    cout << "\tDo you want to delete all the passwords in this account? [Y|N] ";
                    getline(cin, ans);
                    if (ans == "Y" || ans == "y") {
                        item = currentUser + "-" + label;
                        item = edl.encrypt_text(item);
                        passwordManager.resetPasswords();
                        cout <<"\t\t\t| ENTER ANY KEY TO CONTINUE |\n";
                    } else if (ans == "N" || ans == "n") {
                        cout << "\n\t\t\t| Password deletion canceled. |\n";
                        cout <<"\t\t\t| ENTER ANY KEY TO CONTINUE |\n";
                    } else {
                        cout << "\n\t\t\t| Invalid input. Password deletion canceled. |\n";
                        cout <<"\t\t\t| ENTER ANY KEY TO CONTINUE |\n";
                    }
                    cin.ignore();
                    break;
                case '6':
                    loginSystem.logout();
                    currentUser.clear();
                    break;
                default:
                    cout << "\t\t\t| Invalid choice. Please try again. |\n";
            }
        }
    } while (choice != "3");

    return 0;
}
