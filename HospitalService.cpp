#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#include "hospital.h"

/*===Console 클래스 구현부===*/
int Console::select_menu() {//메뉴 선택
	int inputMenu = 0;
	try {
		cout << "****원하시는 서비스를 선택하세요****" << endl;
		cout << "(1)진료 예약\t\t(2)예약 취소\t\t(3)예약 조회\t\t(4)예약 변경\t\t(5)종료\n";
		cin >> inputMenu;
		cin.ignore(INT_MAX, '\n');//버퍼비우기

		if (inputMenu > 4) {
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
		cout << "(1)내과\t\t(2)외과\t\t(3)피부과\n";
		cin >> inputDept;
		cin.ignore(INT_MAX, '\n');//버퍼비우기

		if (inputDept > 4) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! 잘못된 입력입니다!! 다시 입력해주세요~!\n";
		cin >> inputDept;
	}
	return inputDept;
}

/*=====Department 클래스 구현부=====*/
Department::Department(int selectDept) {
	ifstream read_file;
	string readLine;//텍스트파일에서 읽은 한줄의 텍스트 저장
	string subStr;//부분 문자열 저장
	int chkIdx = 0;

	read_file.exceptions(ifstream::failbit | ifstream::badbit);//예외처리
	read_file.open("depart.txt");//텍스트파일 불러오기

	while (!read_file.eof()) {//파일 끝 만나면 루프 종료
		getline(read_file, readLine);
		chkIdx = readLine[0] - '0';// 한 줄의 첫 번째 인덱스 번호를 정수형으로 변환

		if (chkIdx == selectDept) {
			subStr = extract_line(readLine);
			deptName = subStr;
			break;
		}
	}
}

string Department::extract_line(string str) {
	string result;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			result = str.substr(i + 1);
		}
	}
	return result;
}

/*=====Hospital 클래스 구현부=====*/
void Hospital::execute_prog() {
	selectMenu = Console::select_menu();//메뉴 입력(1. 예약, 2.조회, 3.취소, 4.종료)
	switch (selectMenu){
	case 1: 
		selectDept = Console::select_dept();//부서 입력(1~9)
		activation_reserv(selectDept);//예약 활성화
		break;
	}
}
void Hospital::activation_reserv(int param) {
	dc = new Doctor(param);
	dc->show_select_dept();
}
