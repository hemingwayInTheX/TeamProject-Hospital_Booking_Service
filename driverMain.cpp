#include <iostream>
using namespace std;

#include "hospital.h"

int main() {
	cout << "****STRAT SYSTEM****\n";
	Hospital* client = new Hospital();
	client->execute_prog();

	system("pause");
	return 0;
}