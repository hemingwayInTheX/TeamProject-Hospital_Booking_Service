#include <iostream>
using namespace std;

#include "hospital.h"
int main(void) {
	Hospital* client = new Hospital();
	cout << "****Start System****" << endl;
	client->execute_prog();
	delete client;

	system("pause");
	return 0;
}