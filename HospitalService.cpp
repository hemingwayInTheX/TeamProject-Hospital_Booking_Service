#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "hospital.h"

/*======Department 클래스 구현부======*/

void Department::inItDc(int num) {
	ifstream read_file;
	string readLine;
	string sub;
	int idx = 0;

	read_file.open("doctor.txt");
	if (!read_file) {
		cout << "시스템 상에 오류가 있습니다.\n";
		exit(100);
	}

	while (!read_file.eof()) {
		if (read_file.eof()) {
			break;
		}
		getline(read_file, readLine);
		idx = readLine[0] - '0';
		sub = tokenizing_empty(readLine);
		if (idx == num) {
			vec_dc = tokenizing_dcList(sub);
		}
	}
}

string Department::tokenizing_empty(string const& str) {
	string result;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			result = str.substr(i + 1);
		}
	}
	return result;
}

vector<string>Department:: tokenizing_dcList(string const& str) {
	vector<string>v;
	string doctor;
	int chkComma = 0;
	int idx = 0;
	for (int i = 0; i < str.size(); i++){
		if (str[i] == ',') {
			doctor = str.substr(idx, i - idx);//쉼표 이전까지 체크
			idx = i + 1;//인덱스 갱신
			v.push_back(doctor);//추출된 문자열 벡터에 저장
		}
	}
	doctor = str.substr(idx);//마지막 의사 이름 추출--> 마지막 쉼표 이후 문자열은 루프 밖에서 별도 작업 수행
	v.push_back(doctor);
	return v;
}
string Department::select() {
	string input;
    cout << "※ Please select the Doctor you want~!\n";
	cout << ">>";
	cin >> input;
	
	return input;
}
void Department::display_dcList() {
	for (int i = 0; i < vec_dc.size(); i++){
		cout << vec_dc[i] << endl;
	}
}
void Department::selectDc() {//point!
	display_dcList();//출력
	dc = new Doctor();
	string doc = select();
	for (int i = 0; i < vec_dc.size(); i++) {
		if (doc.compare(vec_dc[i])) {
			dc->setDc(doc);
		}
	}
	cout << "선택한 의사" << dc->getDc();
}
/*======Hospital 클래스 구현부======*/

/*9개의 진료부서에 대한 객체 배열 동적 생성.
	부서명을 추출한 후 각각 해당되는 객체 초기화.
	---> 부서명 txt파일(depart.txt)에서 모든 부서를 읽어
	전체 객체에 대한 초기화 작업
	---> 병원 내 전체 진료부서에 대한 출력을 위해 벡터 자료구조 활용*/
Hospital::Hospital() {
	ifstream read_file;
	string readLine;
	string subDept;
	int idx = 0;
	dept = new Department[9];

	read_file.open("depart.txt");
	if (!read_file) {
		cout << "시스템 상에 오류가 있습니다.\n";
		exit(100);
	}
	while (!read_file.eof()) {
		getline(read_file, readLine);
		if (read_file.eof()) {
			break;
		}
		subDept = tokenizing_dept(readLine);
		dept[idx].setDept(subDept);
		vec_dept.push_back(subDept);

		idx++;
	}
	read_file.close();
}
/*읽은 문자열의 길이만큼 루프 수행,
	공백 문자 만나면 그 이후 문자열(진료부서 명)을 추출해 반환.
	---> string 헤더파일의 substr라이브러리 활용 */
string Hospital::tokenizing_dept(string const& str) {
	string result;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			result = str.substr(i + 1);
		}
	}
	return result;
}
void Hospital::activation_booking(int num) {
	string s = dept[num - 1].getDept();
	dept[num - 1].inItDc(num);
	dept[num - 1].selectDc();
}
/*병원 내 전체 진료부서 출력*/
void Hospital::display_deptList() {
	for (int i = 0; i < vec_dept.size(); i++) {
		cout << vec_dept[i] << endl;
	}
}
/*======Console 클래스 구현부======*/
int Console::select_menu() {//메뉴 선택
	int inputMenu = 0;
	try {
		Console::gotoxy(32, 6);  cout << "=====Please select the service you want!=====" << endl;
		Console::gotoxy(46, 8);  cout << "(1)Booking" << endl;
		Console::gotoxy(46, 10);  cout << "(2)Cancel" << endl;
		Console::gotoxy(46, 12);  cout << "(3)Check" << endl;
		Console::gotoxy(46, 14);  cout << "(4)Exit System" << endl;
		inputMenu = _getch();//getch()-->버퍼저장X 키를 누름과 동시에 값 입력(반환값:ASCII코드값)
		system("cls");//입력 후 입력받은 화면 지움 -->API적용

		if (inputMenu > 53) {
			throw inputMenu;
		}
	}
	catch (int x) {
		cout << "WARNING! 잘못된 입력입니다!! 다시 입력해주세요~!\n";
		cin >> inputMenu;
	}
	return inputMenu;
}

int Console::select_dept() {//부서 선택
	int inputDept = 0;
	try {
		Console::gotoxy(34, 23); cout << "※ Please select the Medical Department you want~!\n";
		Console::gotoxy(34, 24); cout << ">>";
		cin >> inputDept;
		system("cls");//입력 후 입력받은 화면 지움 -->API적용
		cin.ignore(INT_MAX, '\n');//버퍼비우기

		if (inputDept > 9) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! 잘못된 입력입니다!! 다시 입력해주세요~!\n";
		cin >> inputDept;
	}
	return inputDept;
}

int Console::select_method() {//부서 선택
	int inputDept = 0;
	try {
		Console::gotoxy(34, 10); cout << "◎◎ Please select a booking method~! ◎◎\n";
		Console::gotoxy(46, 13); cout << "(1)의사 선택\n";
		Console::gotoxy(46, 15); cout << "(2)스케줄 선택\n";
		Console::gotoxy(46, 18); cout << ">>";
		cin >> inputDept;
		system("cls");//입력 후 입력받은 화면 지움 -->API적용
		cin.ignore(INT_MAX, '\n');//버퍼비우기

		if (inputDept > 2) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! 잘못된 입력입니다!! 다시 입력해주세요~!\n";
		cin >> inputDept;
	}
	return inputDept;
}
void Console::gotoxy(int x, int y) {//윈도우 API사용-->콘솔화면 좌표 조작
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void Console::execute_prog() {
	//while (1) {
		int selectMenu = Console::select_menu();//1) 메뉴 입력
		switch (selectMenu) {
		case 49: {// 예약 진행
			hp->display_deptList();//병원 내 전체 진료부서 출력
			int selectDept = Console::select_dept();// 2) 진료부서 선택
			int selectMethod = Console::select_method();//3)예약방식 선택
			if (selectMethod == 1) {// 3-1) 의사 선택 방식
				hp->activation_booking(selectDept);
			}
			else if (selectMethod == 2) {// 3-2) 스케줄 선택 방식
				cout << "현재 이용하실 수 없는 서비스입니다." << endl;
			}
			break;
		}
		}
	//}
}