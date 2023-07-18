
#include <iostream>
#include <string>

#include "includes/LoginSystem.h"
#include "includes/PasswordTracker.h"
#include "includes/EncryptDecryptLib.h"

#include "includes/LoginSystem.cpp"
#include "includes/PasswordTracker.cpp"
#include "includes/EncryptDecryptLib.cpp"



using namespace std;

int main() {
    LoginSystem loginSystem("db/users.csv");
    EncryptDecryptLib edl;
    string currentUser, label, item, accountName;
    string ans = "y";
    PasswordManager passwordManager;

    string choice;
    do {
        cout << "\n";
        cout << "\t=================================================================\n";
        cout << "\t\t\tCipherKey | Encrypted Password Manager\n";
        cout << "\t=================================================================\n";
        cout << "\t\t\"Fortify Your Passwords with Advanced Encryption\"\n"
            << endl;
        cout << "\t>> Please select an option: \n";
        if (currentUser.empty()) {
            cout << "\t1. Register\n";
            cout << "\t2. Login\n";
            cout << "\t3. Exit\n\n";
        } else {
            cout << "\t1. Record new Password\n";
            cout << "\t2. Update Passwords\n";
            cout << "\t3. Delete Passwords\n";
            cout << "\t4. View Passwords\n";
            cout << "\t5. Reset Passwords\n";
            cout << "\t6. Logout\n\n";
        }
        cout << "\t>> Choice: ";
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
                if(!loginSystem.userExists(username))
                loginSystem.registerUser(username, password);
                else cerr << "\t\t\t| User already exist. Try another username. |\n";
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

                    cout << "\t\t\t| Logged in successfully! |\n";
                }
                break;
            case '3':
                cout << "\t\t\t\t >> Exiting... <<\n";
                return 0;
            default:
                cout << "\t\t\t| Invalid choice. Please try again. |\n";
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
                        //cin.ignore();
                        passwordManager.updatePassword(edl.encrypt_text(item), label, new_password);
                    }
                } else {
                    passwordManager.addPassword(item);
                    passwordManager.addPassword(label);
                    cout << "\tPassword for " << label << " to be saved: ";
                    getline(cin, password);
                    passwordManager.addPassword(password);
                    passwordManager.savePasswords();
                    cout << "\n\t\t\t| New Password: Saved! |\n";
                }
                passwordManager.clearTempPasswords();
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
                cout << "\n\t\t\t|Item deleted successfully! |\n";
                choice = "777";

                break;
            case '4':
                cout << "\t\t========= Passwords in your Vault ==========\n";
                passwordManager.printPasswords();
                cout << "\t\t============================================\n";
                break;
            case '5':
                cout << "\tDo you want to delete all the passwords in this account? [Y|N] ";
                getline(cin, ans);
                if (ans == "Y" || ans == "y") {
                    item = currentUser + "-" + label;
                    item = edl.encrypt_text(item);
                    passwordManager.resetPasswords();
                } else if (ans == "N" || ans == "n") {
                    cout << "\n\t\t\t| Password deletion canceled. |\n";
                } else {
                    cout << "\n\t\t\t| Invalid input. Password deletion canceled. |\n";
                }
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
