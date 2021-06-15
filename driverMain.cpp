#include <Windows.h>
#include <iostream>
using namespace std;

#include "hospital.h"

int main(void) {
	Console* client = new Console();
	client->execute_prog();//프로그램 시작 
	delete client;
	system("pause");
	return 0;
}