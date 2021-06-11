#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#ifndef __HOSPITAL__H
#define __HOPITAL__H
/*===Console 클래스====
  >> 사용자 입력값을 받고 반환하는 메서드 정의 --> static 선언*/
class Console {
public:
	static int select_menu();//메뉴 선택
	static int select_dept();//진료부서 선택
	static int select_method();//예약 방식 선택
};

class Department {
public:
	/*Constructor*/
	Department(int selectDept);//선택한 부서에 대한 입력값을 기반으로 객체 초기화
	/*Function*/
	string extract_line(string str);//파일에서 읽은 텍스트의 일부만 추출해 반환
	void show_select_dept() { cout << deptName << "해당부서를 선택하셨습니다.\n"; }//선택한 부서에 대한 초기화 결과 출력(TEST)
private:
	string deptName;//진료부서 이름 정보 저장
};

class Doctor :public Department {
public:
	/*Constructor*/
	Doctor(int param) :Department(param) {};//멤버 이니셜라이져를 활용해 base클래스 생성자 호출
};
/*===Hospital 클래스===
 >> 프로그램 실행 및 활성화 메서드 정의
 >> 진료부서에 대한 객체 동적 할당*/
class Hospital {
public:
	/*Function*/
	void execute_prog();//전체 프로그램 제어 및 실행
	void activation_reserv(int param);//예약 활성화(예약 기능 준비단계)
private:
	Doctor* dc;
	int selectMenu;
	int selectDept;
};
#endif // !__HOSPITAL__H
