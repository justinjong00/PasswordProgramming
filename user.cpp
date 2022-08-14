#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <openssl/sha.h>

using namespace std;


string sha256(const string password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);
    stringstream output;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        output << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return output.str();
}


int main() {

    ifstream secretFile;
    ifstream configFile;
    ofstream logFile;
    string password = "";
    string secretName = "/home/user0055952/user.txt";
    string logName = "/home/user0055952/user.log";
    string configName = "/home/user0055952/user.cfg";
    string line = "";
    string userLogged = "";
    string correctPassword = "";
    string digest = "";
    bool success = false;


    cout << "Please enter password" << endl;
    cin >> password;
    cout << "Input was : " << password << endl;
    digest = sha256(password);
    cout << "Digest was : " << digest << endl;


    configFile.open(configName.c_str());
    logFile.open(logName.c_str(), ofstream::app);
    if (configFile.is_open()) {
        while (configFile >> userLogged >> correctPassword) {
            if (digest == correctPassword) {
                success = true;
                if (logFile.is_open()) {
                    logFile << "Successful login by " << userLogged << endl;
                }
            }
        }
        configFile.close();
    }


    if (success) {
        secretFile.open(secretName.c_str());
        if (secretFile.is_open()) {
            while (getline(secretFile, line)) {
                cout << line << endl;
            }
            secretFile.close();
        }
        else {
            cout << "Unable to open secret file." << endl;
        }
    }
    else {
        cout << "Wrong password entered" << endl;
        logFile << "Unsuccessful login attempt with password: " << password << endl;
    }

    logFile.close();

    return 0;
}
