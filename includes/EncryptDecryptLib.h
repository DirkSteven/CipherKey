#ifndef ENCRYPTDECRYPTLIB_H
#define ENCRYPTDECRYPTLIB_H

#include <fstream>
#include <iostream>

using namespace std;

class EncryptDecryptLib
{
public:
    EncryptDecryptLib();
    virtual ~EncryptDecryptLib();
    static string pwFilePath;
    static string unFilePath;

    bool has_whitespace(const string& str);
    bool user_exist(string filePath, string str);
    bool pass_exist(string filePath,  string str);

    void saveData(string filePath, string content);
    string readData(string filePath, string container);

    string reverse_text(string str);

    string encrypt_text(string str);
    string decrypt_text(string str);

    void encrpyt_file(string fileName);
    void decrpyt_file();

protected:

private:
};

#endif // ENCRYPTDECRYPTLIB_H