#include <iostream>
#include <string>
#ifdef _WIN32
#include <string>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;


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
	tcgetattr(SRDIN_FILENO, &oldt);
	newt = oldt;
	new.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	while ((ch = getchar()) != '\n') {
		if (ch == 127 || ch == '\b') { // Handle backspace
			if (!password.empty()) {
				password.pop_back();
				cout << "\b \b";
			}
		}
		else {
			password.push_back(ch);
			cout << '*'
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

	cout << endl;
	return password;

}



