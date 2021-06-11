#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>

using namespace std;

#include "hospital.h"

/*===Console 클래스 구현부===*/
int Console::select_menu() {//메뉴 선택
	int inputMenu = 0;
	try {
		Console::gotoxy(28, 6);  cout << "=======원하시는 서비스를 선택하세요!=======" << endl;
		Console::gotoxy(40, 8);  cout << "(1)진료 예약" << endl;
		Console::gotoxy(40, 10);  cout << "(2)예약 취소" << endl;
		Console::gotoxy(40, 12);  cout << "(3)예약 조회" << endl;
		Console::gotoxy(40, 14);  cout << "(4)서비스 종료하기" << endl;
		inputMenu = _getch();//getch()-->버퍼저장X 키를 누름과 동시에 값 입력(반환값:ASCII코드값)
		system("cls");//입력 후 입력받은 화면 지움 -->API적용
		//cin.ignore(INT_MAX, '\n');//버퍼비우기

		if (inputMenu > 53 ) {
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
		cout << "원하시는 진료부서를 선택해주세요~!\n";
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

void Console::gotoxy(int x, int y) {//윈도우 API사용-->콘솔화면 좌표 조작
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/*=====Department 클래스 구현부=====*/
Department::Department() {
	fstream read_file("depart.txt");//텍스트파일 불러오기
	string readLine;//텍스트파일에서 읽은 한줄의 텍스트 저장

	if (!read_file) {//파일 읽기 오류처리
		cout << "시스템 상에 오류가 있습니다.\n";
		exit(100);
	}
	while (1) {//파일 끝 만나면 루프 종료
		if (read_file.eof())break;
		getline(read_file, readLine);
		vec_deptName.push_back(readLine);
	}
}
void Department::setDept(int selectDept) {
	ifstream read_file;
	string readLine;//텍스트파일에서 읽은 한줄의 텍스트 저장
	string subStr;//부분 문자열 저장
	int chkIdx = 0;

	if (!read_file) {//파일 읽기 오류처리
		cout << "시스템 상에 오류가 있습니다.\n";
		exit(100);
	}
	read_file.open("depart.txt");//텍스트파일 불러오기
	while (1) {//파일 끝 만나면 루프 종료
		if (read_file.eof())break;
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
	for (int i = 0; i < str.size(); i++) {//읽은 문자열의 길이만큼 루프 수행
		if (str[i] == ' ') {//공백 문자 만나면 그 이전 문자에 대한 토크나이징 수행 및 해당 데이터 반환
			result = str.substr(i + 1);
		}
	}
	return result;
}

void Department::display_dept_list() {
	for (int i = 0; i < vec_deptName.size(); i++){
		//Console::gotoxy(10, 10);
		cout << vec_deptName[i]<<endl;
	}
}
/*=====Hospital 클래스 구현부=====*/
void Hospital::execute_prog() {
	selectMenu = Console::select_menu();//메뉴 입력(1. 예약, 2.조회, 3.취소, 4.종료)
	switch (selectMenu){
	case 49: //예약 선택
		dc->display_dept_list();//선택 가능한 진료 부서 출력
		selectDept = Console::select_dept();//부서 입력(1~9)
		activation_reserv(selectDept);//예약 활성화
		break;
	}
}
void Hospital::activation_reserv(int param) {
	dc->setDept(param);//입력된 부서에 해당되는 객체 초기화
	dc->show_select_dept();

}
