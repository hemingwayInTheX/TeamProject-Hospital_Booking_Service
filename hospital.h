#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#ifndef __HOSPITAL__H
#define __HOSPITAL__h

/*===Department 클래스===
>> 예약, 취소, 변경 핵심 기능 정의
>> 각 부서에 맞게 의사에 대한 객체 생성*/
class Test {
public:
	Test() { dept = ""; }
	void setName(string name) { dept = name; }
	string getName() { return dept; }
	void display() { cout << dept << endl; }
private:
	string dept;
};
/*===Hospital 클래스===
 >> 프로그램 실행 및 활성화 메서드 정의
 >> 진료부서에 대한 객체 배열 초기화 및 벡터 저장*/
class Hospital {
public:
	/*Constructor & Destructor*/
	Hospital();
	~Hospital() { delete[]test; }
	/*Function*/
	void execute_prog();//프로그램 시작
	void activation_prog(int selection);//기능 활성화
private:
	Test* test;
	vector <Test>vec_storage_Dept;//초기화된 부서객체를 벡터에 저장
	int selectMenu;//메뉴 입력 반환값 저장
	int selectDept;//부서 선택 입력 반환값 저장
};
/*===Console 클래스====
  >> 사용자 입력값을 받고 반환하는 메서드 정의 --> static 선언*/
class Console {
public:
	static int select_menu();//메뉴 선택
	static int select_dept();//진료부서 선택
	static int select_method();//예약 방식 선택
};

#endif // !__HOSPITAL__H

