#include <Windows.h>
#include <iostream>
using namespace std;

#include "hospital.h"

int main(void) {
	Console* client = new Console();
	client->execute_prog();//���α׷� ���� 
	delete client;
	system("pause");
	return 0;
}