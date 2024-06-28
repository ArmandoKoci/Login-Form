#include<iostream>
#include<fstream>
#include <string>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;


class temp {
    string userName, Email, password;
    string searchName, searchPass, searchEmail;
    fstream file;
public:
    void login();
    void singUP();
    void forgot();
}obj;


string getPassword() {
    string password;
    char ch;

#ifdef _WIN32 
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    new.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while ((ch = getchar()) != '\n') {
        if (ch == 127 || ch == '\b') { //Handle Backspace
            if (!password.emprty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    cout << endl;
    return password;
}


int main() {
    char choice;
    while (true) {
        cout << "\n1- Login";
        cout << "\n2- Sing-Up";
        cout << "\n3- Forgot Password";
        cout << "\n4- Exit";
        cout << "\nEnter Your Choice :: ";
        cin >> choice;
        cin.ignore();  // To ignore the newline character after the choice input

        switch (choice) {
        case '1':
            obj.login();
            break;
        case '2':
            obj.singUP();
            break;
        case '3':
            obj.forgot();
            break;
        case '4':
            return 0;
        default:
            cout << "Invalid Selection...!";
        }
    }
}

void temp::singUP() {
    cout << "\nEnter Your User Name :: ";
    cin.ignore(); // To ignore the newline character left by previous input
    getline(cin, userName);
    cout << "Enter Your Email Address :: ";
    getline(cin, Email);
    cout << "Enter Your Password :: ";
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    file << userName << "*" << Email << "*" << password << endl;
    file.close();
    cout << "Sign-Up Successful!\n";
}

void temp::login() {

    cout << "--------------LOGIN--------------" << endl;
    cout << "Enter Your User Name :: " << endl;
    cin.ignore(); // To ignore the newline character left by previous input
    getline(cin, searchName);
    cout << "Enter Your User Password :: " << endl;
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);
    if (!file) {
        cout << "No User Data Found.\n";
        return;
    }

    bool found = false;
    while (getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password)) {
        if (userName == searchName && password == searchPass) {
            cout << "\nAccount Login Successful...!";
            cout << "\nUsername :: " << userName << endl;
            cout << "Email :: " << Email << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid Username or Password.\n";
    }

    file.close();
}


void temp::forgot() {
    cout << "\nEnter Your UserName :: ";
    cin.ignore(); // To ignore the newline character left by previous input
    getline(cin, searchName);
    cout << "\nEnter Your Email Address :: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    if (!file) {
        cout << "No User Data Found.\n";
        return;
    }

    bool found = false;
    while (getline(file, userName, '*') && getline(file, Email, '*') && getline(file, password)) {
        if (userName == searchName && Email == searchEmail) {
            cout << "\nAccount Found...!";
            cout << "\nYour Password :: " << password << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not Found.\n";
    }

    file.close();

}
