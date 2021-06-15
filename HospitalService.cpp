#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "hospital.h"

/*======Doctor 클래스 구현부======*/

/* doctor 생성자 : 의사 이름과 진료 스케줄 2차원 배열 생성
  기본 값 : 이름="NULL", 스케줄 : 0행-요일 0열-타임 */
Doctor::Doctor() {
	dcName = "NULL";
	schedule[0][0] = "~~~";
	schedule[0][1] = "월";
	schedule[0][2] = "화";
	schedule[0][3] = "수";
	schedule[0][4] = "목";
	schedule[0][5] = "금";

	for (int i = 1; i < 6; i++) {
		schedule[i][0] = to_string(i) + "time";
		for (int i = 1; i < 6; i++) {
			for (int j = 1; j < 6; j++) {

				schedule[i][j] = "NULL";
			}
		}
	}
}
string Doctor::getSchedule(string s) {
	string str;
	int temp = 0;
	for (int i = 1; i < DAY; i++){
		for (int j = 1; j < DATE; j++){
			if (schedule[i][j] == s) {
				temp = i;
				if (j == 1)str = "mon";
				else if (j == 2)str = "tue";
				else if (j == 3)str = "wed";
				else if (j == 4)str = "thu";
				else if (j == 5)str = "fri";
			}
		}
	}
	str = str + '-' + to_string(temp)+"time";
	return str;
}
/*진료 스케줄 초기화 --> 휴진 'x'reading 시 예외처리*/
void Doctor::setSchedule(string s, int i, int j) {
	if (schedule[i][j] == "xxxxxxxxxxxxx") {
		cout << "휴진입니다~!\n";
		return;
	}
	schedule[i][j] = s;
}
/*스케줄 출력*/
void Doctor::display_Schedule() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << schedule[i][j] << "\t";
		}
		cout << endl;
	}
}
/*예약 취소 시 "-" 갱신*/
void Doctor::cancel_sche(string s) {
	string str;
	int temp = 0;
	for (int i = 1; i < DAY; i++) {
		for (int j = 1; j < DATE; j++) {
			if (schedule[i][j] == s) {
				setSchedule("============", i, j);
			}
		}
	}
}
void Doctor::display_Schedule_dayver(int num) {
	for (int i = 0; i < 6; i++) {
		cout << schedule[i][0] << "\t";
		cout << schedule[i][num] << endl;
	}
	cout << endl;
}

bool Doctor::search_Schedule(int num) {
	if (schedule[1][num] != "xxxxxxxxxxxxx") {
		return true;
	}
	return false;
}
/*======Department 클래스 구현부======
진료부서에 대한 초기화 작업 후 바로 각 부서의 
의료진 및 모든 의사 스케줄에 대한 초기화 작업 수행
--> 1) 텍스트파일에서 의사 이름을 탐색 시 객체 초기화 작업 이후 벡터 저장
--> 2) 의사 이름이 아닌 스케줄 널값('-')탐색 시 따로 정의한 추출 메서드를 
통해 '-'5개 추출 후 벡터 저장 및 반환 = 스케줄 Matrix(5X5) 초기화 
        --> 0행 0열은 요일 및 시간대로 사전 초기화*/
void Department::loadDcList(string filename) {
	string getFile = filename;
	string str;
	ifstream read_file;
	Doctor* doc;

	read_file.open(filename);
	if (!read_file) {
		cout << "시스템 상에 오류가 있습니다.\n";
		exit(100);
	}
	int count = 0;   //파일 줄세기
	int i = 0;      //벡터 객체 순서 저장
	int s = 1; //DAY 계산 
	while (getline(read_file, str)) {
		//의사 이름 접근 : 닥터객체 생성하여 벡터 저장 및 의사 이름 저장
		if (count % 7 == 1) {
			doctor = new Doctor;
			doctor->setDc(str);
			v.push_back(doctor);
			i++;
		}
		else {
			//진료 스케줄접근 : 진료 스케줄 받아오기
			//v 벡터 = 의사객체 저장 -> pop -> temp벡터 -> (storage) string tokenizing --> 각 원소 할당
			if (str != "-----") {
				int j = 0;
				doc = v.at(i - 1);
				vector<string> sc = tokenizing_sc(str);
				if (s != DAY) {
					for (int t = 1; t < DATE; t++) {
						if (j != sc.size()) {
							doc->setSchedule(sc.at(j), s, t);
							j++;
						}
					}
				}
				if (s == 5)s = 0;
				s++;
			}
		}
		count++;
	}
	read_file.close();
}
vector<string> Department::tokenizing_sc(const string str) {
	vector <string> result;
	string sc;
	int chkSpace = 0;
	int idx = 0;
	for (int i = 0; i < str.size(); i++) {//읽은 문자열의 길이만큼 루프 수행
		if (str[i] == ' ') {//공백 문자 만나면 그 이전 문자에 대한 토크나이징 수행 및 해당 데이터 반환
			sc = str.substr(idx, i - idx);
			idx = i + 1;
			result.push_back(sc);
		}
	}
	sc = str.substr(idx);
	result.push_back(sc);
	return result;
}

int Department::inputDc() {
	int input;
	Console::gotoxy(34, 18); cout << "※ Please select the Doctor you want~!\n";
	Console::gotoxy(34, 19); cout << ">>";
	cin >> input;
	system("cls");//입력 후 입력받은 화면 지움 -->API적용

	return input;
}
int Department::inputDay() {
	string input;
	int result = 0;
	cout << "※ Please select Day~!\n";
	cout << ">>";
	cin >> input;
	
	if (input.compare("mon")==0) { result = 1;}
	else if (input.compare("tue") == 0) { result = 2;}
	else if (input.compare("wed") == 0) { result = 3;}
	else if (input.compare("thu") == 0) { result = 4;}
	else if (input.compare("fri") == 0) { result = 5;}
	
	return result;
}
/*시간대 입력*/
int Department::inputTime() {
	int inputDept = 0;
	try {
		cout << "※ Please select the Time~!\n";
		cout << ">>";
		cin >> inputDept;
		cin.ignore(INT_MAX, '\n');//버퍼비우기

		if (inputDept > 5) {
			throw inputDept;
		}
	}
	catch (int x) {
		cout << "WARNING! 잘못된 입력입니다!! 다시 입력해주세요~!\n";
		cin >> inputDept;
	}
	return inputDept;
}
/*사용자 정보 입력*/
string Department::inputInfo() {
	string inputName;
	string inputId;
	string result;

	cout << "※ Please input NAME~!\n";
	cout << ">>";
	cin >> inputName;

	cout << "※ Please input ID~!\n";
	cout << ">>";
	cin >> inputId;

	result = inputName + '-'+inputId;
	return result;
}
int Department::reinputDc(int num) {
	int input;
	while (1) {
		input = inputDc();
		if (!v[input - 1]->search_Schedule(num))
			cout << "고유번호에 해당하는 의사가 존재하지 않습니다. 다시 입력해주세요" << endl;
		else
			break;
	}
	return input;
}
/*의료진 목록 출력*/
void Department::display_dcList() {
	for (int i = 0; i < v.size(); i++){
		Console::gotoxy(46, (i * 2) + 10);
		cout <<"("<<i+1<<")"<< v[i]->getDc() << endl;
	}
}
/*  핵심 기능 실행
  --> 예약에 있어 필요한 날짜, 시간대를 입력받고
  최종적으로 사용자 정보를 입력함으로써 예약 완료*/
void Department::set_reservation() {
	display_dcList();//출력
	int day;
	int time;
	string client;

	int inputDoc = inputDc();// 1) 의사입력
	v[inputDoc - 1]->display_Schedule();//의사출력

	day = inputDay();// 2) 날짜 입력 --> Ex) input >> mon, tue, wed
	time = inputTime();// 3) 시간 입력 
	client = inputInfo();// 4) 사용자 정보 입력

	v[inputDoc - 1]->setSchedule(client,time,day);
	v[inputDoc - 1]->display_Schedule();//선택한 의사 스케줄 및 확정된 예약 내역출력
	Console::gotoxy(35, 24);
	cout << v[inputDoc - 1]->getSchedule(client) << "(요일/시간대)를 선택하셨습니다!\n";
	Sleep(6000);//잠깐 멈추고 다음 화면으로 전환
	system("cls");//입력 후 입력받은 화면 지움 -->API적용
}
void Department::set_reservation_sc() {
	cout << "※ Please select day~!\n";
	cout << " mon\ttue\twed\tthu\tfri\n";

	int input;
	int inputDoc;
	int time;
	string client;

	input = inputDay();

	for (int i = 0; i < v.size(); i++) {
		if (v[i]->search_Schedule(input)) {
			cout << "(" << i + 1 << "). " << v[i]->getDc() << endl;
			v[i]->display_Schedule_dayver(input);
		}
	}

	inputDoc = reinputDc(input);
	time = inputTime();
	client = inputInfo();

	v[inputDoc - 1]->setSchedule(client, time, input);//사용자 입력
	v[inputDoc - 1]->display_Schedule();//출력
	Sleep(6000);//잠깐 멈추고 다음 화면으로 전환
	system("cls");//입력 후 입력받은 화면 지움 -->API적용
}
/* 의사 객체의 스케줄에 저장된 사용자 정보를 
    반환받아 null값을 나타내는 '-' 과 비교연산
	수행 후 사용자가 입력한 예약정보 출력*/
void Department::chk_reservation() {
	string client = inputInfo();
	string s;
	for (int i = 0; i < v.size(); i++) {
		s = v[i]->getSchedule(client);
		if (s[0] != '-') {
			cout << s;
			Sleep(6000);//잠깐 멈추고 다음 화면으로 전환
			system("cls");//입력 후 입력받은 화면 지움 -->API적용
			break;
		}
	}
}

void Department::cancel_reservation() {
	string client = inputInfo();
	string s;
	for (int i = 0; i < v.size(); i++) {
		v[i]->cancel_sche(client);
	}
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
	string subFile;
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
		subFile = tokenizing_file(readLine);

		dept[idx].setDept(subDept);
		vec_dept.push_back(subDept);

		dept[idx].loadDcList(subFile);
		idx++;
	}
	read_file.close();
}
/*읽은 문자열의 길이만큼 루프 수행,
	공백 문자 만나면 그 이후 문자열(진료부서 명)을 추출해 반환.
	---> string 헤더파일의 substr라이브러리 활용 */
string Hospital::tokenizing_dept(string const& str) {
	string result;
	int j = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ') {
			j = i;
		}
		if (str[i] == '=') {
			result = str.substr(j+1, i-3 );
		}
	}
	return result;
}
/*'=' 기준 텍스트 파일명 추출 작업 수행
   ---> = 이후 문자열 추출해 반환 */
string Hospital::tokenizing_file(string const& str) {
	string result;
	int cnt = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '=') {
			cnt++;
			if (cnt == 1) {
				result = str.substr(i+1);
			}
		}
	}
	return result;
}
/*핵심 기능 활성화*/
void Hospital::activation_booking(int num) {
	string a = dept[num - 1].getDept();
	Console::gotoxy(32, 8); cout <<"◎◎"<< a << "진료부서를 선택하셨습니다~!◎◎\n";
	dept[num - 1].set_reservation();
}
void Hospital::activation_booking2(int num) {
	dept[num - 1].set_reservation_sc();
}
void Hospital::activation_chk(int num) {dept[num - 1].chk_reservation();}
void Hospital::activation_cancel(int num) {dept[num - 1].cancel_reservation();}
/*병원 내 전체 진료부서 출력*/
void Hospital::display_deptList() {
	Console::gotoxy(34,2); cout << " ♣♣♣♣♣♣SEVERANCE-HEALTHCARE♣♣♣♣♣\n";
	for (int i = 0; i < vec_dept.size(); i++) {
		Console::gotoxy(46, (i * 2) + 4);
		cout << "("<<i+1<<")"<<vec_dept[i] << endl;
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
		Console::gotoxy(32, 16);  cout << "=============================================" << endl;
		
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
	while (1) {
		Console::gotoxy(28, 3);
		cout << " ♣♣♣♣♣♣WELCOME TO SEVERANCE-HEALTHCARE♣♣♣♣♣\n";

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
				hp->activation_booking2(selectDept);
			}
			break;
		}
		case 50: {//예약 취소
			hp->display_deptList();
			int selectDept = Console::select_dept();// 2) 진료부서 선택
			hp->activation_cancel(selectDept);
			break;
		}
		case 51: {//예약 조회
			hp->display_deptList();
			int selectDept = Console::select_dept();// 2) 진료부서 선택
			hp->activation_chk(selectDept);
			break;
		}
		case 52: {
			string chk;
			Console::gotoxy(33, 13); cout << "정말 종료하시겠습니까~~~?!!" << endl;
			Console::gotoxy(33, 14); cout << ">>"; cin >> chk;
			system("cls");//입력 후 입력받은 화면 지움 -->API적용
			if (chk.compare("yes") == 0) {
				exit(100);
			}
		}
		default:
			cout << "잘못 입력하셨습니다!!" << endl;
			break;
		}
	}
}
