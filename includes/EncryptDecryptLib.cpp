#include "EncryptDecryptLib.h"
#include <string>
EncryptDecryptLib::EncryptDecryptLib()
{
    //ctor
}

EncryptDecryptLib::~EncryptDecryptLib()
{
    //dtor
}

string EncryptDecryptLib::unFilePath = "username.txt";
string EncryptDecryptLib::pwFilePath = "password.txt";

bool EncryptDecryptLib::has_whitespace(const string& str) {
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
            return true;
        
    }
    return false;
}

void EncryptDecryptLib::saveData(string filePath, string content){
    fstream save;

    save.open(filePath, ios::app);
    save << content << endl;
    save.close();
}

string EncryptDecryptLib::readData(string filePath, string container) {
    fstream read;
    string tmpCont;
    read.open(filePath, ios::in);
    
    while (getline(read, tmpCont)) {
        container.append(tmpCont);
    }
    read.close();
    cout << container;
    return container;
};

string EncryptDecryptLib::encrypt_text(string str){
    string rStr = str;
    int N = str.length();
    for (int i = 0; i < N; i++) {
        int increase = 100;
        rStr[i] += increase;
        increase = 0;
    }
    return rStr;
}

string EncryptDecryptLib::reverse_text(string str)
{
    string tmpStr = str;
    short n = str.length() - 1;
    int j = n;
    int i = 0;

    while (true) {
        tmpStr[j] = str[i];
        cout << j << " " << i << endl;

        j--;
        i++;

        if (n + 1 <= i)
            break;
    }
    return tmpStr;
}

string EncryptDecryptLib::decrypt_text(string str){
   string rStr = str;
    int N = str.length();
    for (int i = 0; i < N; i++) {
        int increase = 100;
        rStr[i] -= increase;
        increase = 0;
    }
    return rStr;
}

bool EncryptDecryptLib::user_exist(string filePath,  string str) {
    fstream read;
    read.open(filePath, ios::in);
    string tmptxt;

    while (getline(read, tmptxt)) {
        cout << "usertmp: " << tmptxt << endl;
        cout << "userorg: " << str << endl;
        if (str == tmptxt)
        {
            read.close();
            return true;
        }
    }
    return false; 
}

bool EncryptDecryptLib::pass_exist(string filePath, string str){
    fstream read;
    read.open(filePath, ios::in);
    string tmptxt;

    string rStr = EncryptDecryptLib::encrypt_text(str);

    while (getline(read, tmptxt)) {
        cout << "passtmp: " << tmptxt << endl;
        cout << "pasorg: " << rStr << endl;
        if (rStr == tmptxt)
        {
            read.close();
            return true;
        }
    }
    return false;
    
}
;

void EncryptDecryptLib::encrpyt_file(string filePath) {
    char holder;
    fstream fileStore, fileEncrpyt;

    fileStore.open("storage.txt", ios::out); // output
    fileEncrpyt.open(filePath, ios::in); // read username.txt

    while (fileEncrpyt >> noskipws >> holder) {
        holder = holder + 100;
        fileStore << holder;
    }
}

void EncryptDecryptLib::decrpyt_file() {
    char holder;
    string storage = "storage.txt";
    fstream fileStore, fileDecrpyt;

    fileDecrpyt.open("decrpyt.txt", ios::out);
    fileStore.open(storage, ios::in);

    while (fileStore >> noskipws >> holder) {
        holder = holder - 100;
        fileDecrpyt << holder;
    }
}