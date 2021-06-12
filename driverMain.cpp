#include <Windows.h>
#include <iostream>
using namespace std;

#include "hospital.h"

int main() {
	Console::gotoxy(28, 3);
	cout << "�ڡڡڡڡ� WELCOME TO SEVERANCE-HEALTHCARE!!! �ڡڡڡڡ�\n";
	Hospital* client = new Hospital();
	client->execute_prog();

	system("pause");
	return 0;
}