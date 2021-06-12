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
	static void gotoxy(int x, int y);//콘솔화면 좌표 조작
	static string select_doctorName();//의사 이름 입력
};

class Department {
public:
	/*Constructor*/
	Department();//파일에서 읽은 텍스트 벡터에 저장--> 출력용
	/*Function*/
	void setDept(int selectDept);//입력값을 통해 텍스트파일과 일치하는 부서를 탐색 후 객체 초기화
	string getDept() { return deptName; }//부서명 반환
	string tokenizing_line(const string str);//파일에서 읽은 텍스트의 일부만 추출해 반환
	void show_select_dept() { cout << deptName << "해당부서를 선택하셨습니다.\n"; }//선택한 부서에 대한 초기화 결과 출력(TEST)
	void display_dept_list();//부서명 출력
private:
	string deptName;//진료부서 이름 정보 저장
	vector <string>vec_deptName;//출력용
};

class Doctor :public Department {
public:
	/*Constructor*/
	Doctor(){}
	/*Function*/
	void setDoctor(const string dp);//각 부서에 해당되는 의사 정보 초기화
	string getDoctor() { return dcName; }//의사 정보 반환
	virtual string tokenizing_line(const string str);//가상함수를 이용한 메서드 오버라이딩 활용
	string extract_line(string const& str);
	vector<string>tokenizing_doctor(string const &str);
	void display_doctorList();//선택한 진료부서에 해당되는 의료진 목록 출력
	void doctorName_reserv();//의사선택 예약 진행
private:
	vector <string>vec_dcName;
	string dcName;//의사 정보 저장
};
/*===Hospital 클래스===
 >> 프로그램 실행 및 활성화 메서드 정의
 >> 진료부서에 대한 객체 동적 할당*/
class Hospital {
public:
	/*Constructor*/
	Hospital() { dc = new Doctor(); }//객체 동적할당 초기화
	/*Function*/
	void execute_prog();//전체 프로그램 제어 및 실행
	void activation_reserv(int param);//예약 활성화(예약 기능 준비단계)
private:
	Doctor* dc;
	int selectMenu;//메뉴선택
	int selectDept;//진료부서 선택
	int selectMethod;//예약방식 선택
};
#endif // !__HOSPITAL__H
