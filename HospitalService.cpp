#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <conio.h>
#include <regex>//정규표현식

using namespace std;

#include "hospital.h"

/*===Console 클래스 구현부===*/
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

string Console::select_doctorName() {
	string sent;
	Console::gotoxy(34, 15); cout << "====Please enter the desired Doctor!!====\n"; 
	Console::gotoxy(37, 17); cout << ">>";
	cin >> sent;
	system("cls");//입력 후 입력받은 화면 지움 -->API적용
	return sent;
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
	read_file.close();
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
			subStr = tokenizing_line(readLine);
			deptName = subStr;
			break;
		}
	}
	read_file.close();
}
string Department::tokenizing_line(const string str) {
	string result;
	for (int i = 0; i < str.size(); i++) {//읽은 문자열의 길이만큼 루프 수행
		if (str[i] == ' ') {//공백 문자 만나면 그 이전 문자에 대한 토크나이징 수행 및 해당 데이터 반환
			result = str.substr(i + 1);
		}
	}
	return result;
}

void Department::display_dept_list() {
	Console::gotoxy(41, 1); cout << "◎◎ MEDICAL DEPARTMENT ◎◎" << endl;
	for (int i = 0; i < vec_deptName.size(); i++){
		Console::gotoxy(45, (i*2)+4);
		cout << vec_deptName[i]<<endl;
	}
}

/*=====Doctor 클래스 구현부=====*/
void Doctor::setDoctor(const string dp) {
	ifstream read_fileDoctor;
	string readLine;//텍스트파일에서 읽은 한줄의 텍스트 저장
	string subStrDept;//부분 문자열 저장
	string subStrDc;
	string dcList;

	if (!read_fileDoctor) {//파일 읽기 오류처리
		cout << "시스템 상에 오류가 있습니다.\n";
		exit(100);
	}
	read_fileDoctor.open("doctor.txt");//텍스트파일 불러오기
	while (1) {
		if (read_fileDoctor.eof())break;//파일끝 만나면 루프 탈출
		getline(read_fileDoctor, readLine);
		subStrDept=tokenizing_line(readLine);//부서명 추출	
		subStrDc = extract_line(readLine);//'='이후 토크나이징된 문자열 저장

		if (dp.compare(subStrDept)== 0) {//선택한 부서명과 해당 의료진이 속한 부서명의 동일하면            
			vec_dcName = tokenizing_doctor(subStrDc);//벡터 저장
		}
	}
}
string Doctor::tokenizing_line( const string str) {
	string result;
	for (int i = 0; i < str.size(); i++) {//읽은 문자열의 길이만큼 루프 수행
		if (str[i] == '=') {//공백 문자 만나면 그 이전 문자에 대한 토크나이징 수행 및 해당 데이터 반환
			result = str.substr(0, i);//0번째 인덱스 부터 '='만난 지점까지 문자열 토크나이징
			break;
		}
	}
	return result;
}
string Doctor::extract_line(string const& str) {
	string result;
	for (int i = 0; i < str.size(); i++){
		if (str[i] == '=') {//공백 문자 만나면 그 이전 문자에 대한 토크나이징 수행 및 해당 데이터 반환
			result = str.substr(i + 1);//0번째 인덱스 부터 '='만난 지점까지 문자열 토크나이징
			break;
		}
	}
	return result;
}

vector <string> Doctor::tokenizing_doctor(string const& str) {
	vector <string>temp_dc_name;
	string doctor;
	int chkComma = 0;
	int idx = 0;
	for (int i = 0; i < str.size(); i++) {//쉼표 만나면 이전 문자열 저장 후 벡터에 저장
		if (str[i] == ',') {
			doctor = str.substr(idx, i - idx);//쉼표 이전까지 체크
			idx = i + 1;//인덱스 갱신
			temp_dc_name.push_back(doctor);//추출된 문자열 벡터에 저장
		}
	}
	doctor = str.substr(idx);//마지막 의사 이름 추출--> 마지막 쉼표 이후 문자열은 루프 밖에서 별도 작업 수행
	temp_dc_name.push_back(doctor);

	return temp_dc_name;
}
void Doctor::display_doctorList() {
	for (int i = 0; i < vec_dcName.size(); i++){
		Console::gotoxy(48, (i*2)+6);
		cout << vec_dcName[i] << endl;
	}
}
void Doctor::doctorName_reserv(){
	string temp = Console::select_doctorName();//희망 의료진 입력
	for (int i = 0; i < vec_dcName.size(); i++){
		if (vec_dcName[i].compare(temp) == 0) {
			dcName = temp;
		}
	}
}

/*=====Hospital 클래스 구현부=====*/
void Hospital::execute_prog() {
	selectMenu = Console::select_menu();//메뉴 입력(1. 예약, 2.조회, 3.취소, 4.종료)
	switch (selectMenu){
	case 49: //예약 선택
		dc->display_dept_list();//선택 가능한 진료 부서 출력
		selectDept = Console::select_dept();//부서 입력(1~9)
		dc->setDept(selectDept);//입력된 부서에 해당되는 객체 초기화
		
		selectMethod = Console::select_method();//예약 방식 선택
		activation_reserv(selectMethod);//예약 활성화
		break;
	}
}
void Hospital::activation_reserv(int param) {//예약 준비단계

	if (selectMethod == 1) {//의사 중심 예약 방식 선택
		string department = dc->getDept();//선택한 부서 저장

		dc->setDoctor(department);//선택한 부서에 해당하는 의료진 초기화
		Console::gotoxy(36, 4); cout <<"◎◎◎"<< dc->getDept() << "의료진입니다!◎◎◎" << endl;
		dc->display_doctorList();//의료진 목록 출력
		
		dc->doctorName_reserv();//예약 실행
		cout << dc->getDoctor() << "선택하셨습니다!";
	}
	else if (selectMethod == 2) {

	}
}
