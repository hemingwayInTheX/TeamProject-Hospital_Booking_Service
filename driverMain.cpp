#include <Windows.h>
#include <iostream>
using namespace std;

#include "hospital.h"

int main() {
	Console::gotoxy(28, 3);
	cout << "****WELCOME TO SEVERANCE-HEALTHCARE!!!****\n";
	Hospital* client = new Hospital();
	client->execute_prog();

	system("pause");
	return 0;
}