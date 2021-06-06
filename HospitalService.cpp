#include <iostream>
#include <fstream>
#include <string>
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

/*===Hospital 클래스 구현부===*/
Hospital::Hospital() {
	test = new Test[25];//25개의 진료부서 저장
	ifstream read_file;
	string readLine;//텍스트 파일에서 한 줄씩 읽은 데이터 저장
	string deptName;
	int idx = 0;

	read_file.exceptions(ifstream::failbit | ifstream::badbit);//예외처리
	read_file.open("hospital.txt");//텍스트파일 불러오기

	while (!read_file.eof()) {//파일 끝을 만날때까지 작업 수행
		if (read_file.eof())break;//파일의 끝인지 중복체크
		getline(read_file, readLine);
		deptName = readLine;
		test[idx].setName(deptName);// 1) 객체 배열 초기화
		vec_storage_Dept.push_back(test[idx]);// 2) 초기화된 객체를 벡터에 순서대로 저장
		idx++;
	}
}

void Hospital::execute_prog() {
	int idx = 0;
	selectMenu = Console::select_menu();
	if (selectMenu == 1) {//메뉴 입력
		selectDept = Console::select_dept();//진료 부서 선택
		activation_prog(selectDept);
		cout << "hello";
	}
}

void Hospital::activation_prog(int selection) {
		for (int i = 0; i < 3; i++) {//전체 진료 부서 출력
			vec_storage_Dept[i].display();
		}

}