#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#ifndef __HOSPITAL__H
#define __HOPITAL__H

#define DAY 6
#define DATE 6

/*===Doctor 클래스====*/
//예약 기능을 통해 입력받은 사용자 정보를 6X6Matrix에 선택한 시간과 요일에 해당되는 인덱스에 할당
//사용자가 입력한 예약정보가 최종적으로 저장되는 클래스
//예약 취소 시 해당 인덱스를 null값으로 갱신
class Doctor{
public:
	/*Constructor & Destructor*/
	Doctor();
	/*Function*/
	void setDc(string dcName) { this->dcName = dcName; }//의사 정보 초기화
	void setSchedule(string s, int i, int j);//병원 내 모든 의사의 스케줄 초기화 --> '-----' : NULL(예약 가능) // 'XXXXXXXX' : 휴진
	string getSchedule(string s);//예약 정보 조회 시 선택된 예약 시간 날짜 출력
	string getDc() { return dcName; }//선택한 의사 정보 초기화
	void cancel_sche(string s);//예약 취소 시 해당 인덱스 '-----'로 갱신
	bool search_Schedule(int num);//휴진인 스케줄로 예정된 의료진 탐색
	void display_Schedule_dayver(int num);//선택된 요일에 해당되는 의료진 목룍 출력
	void display_Schedule();//스케줄 출력
private:
	string dcName;
	string schedule[6][6];
};

/*===Department 클래스====*/
//각 부서에 속한 의료진 및 모든 의료진의 스케줄 초기화 작업 
//클래스 이름대로 부서에서 진행하는 예약 실행,조회,취소와 같이 프로그램 핵심 메서드 정의
//사용자 정보 입력 및 날짜/시간 입력을 통해 본격적인 예약 실행
class Department {
public:
	/*Constructor & Destructor*/
	Department() {}
	~Department() { delete doctor; }
	/*Function*/
	void loadDcList(string filename);//Hospital생성자에서 호출받아 부서에 해당하는 모든 의료진과 의료진 개개인의 스케줄 초기화
	vector<string> tokenizing_sc(const string str);//텍스트 파일의 스케줄 matrix NULL 표시기호 "----" 토크나이징 작업 통해 벡터 저장--> 의사 스케줄 초기화에 필요한 작없
	void setDept(string deptName) { this->deptName = deptName; }//부서 이름 초기화
	string getDept() { return deptName; }//부서 이름 출력
	void set_reservation();//예약 실행_1번째 예약 방식(의사중심)
	void set_reservation_sc();//예약 실행_2번째 예약 방식(스케줄 중심)
	void chk_reservation();//예약 조회
	void cancel_reservation();//예약 취소
	int inputDc();//희망 의료진 입력
	int reinputDc(int num);
	int inputDay();//날짜 입력
	int inputTime();//시간대 입력
	string inputInfo();//사용자 정보 입력
	void display_dcList();//선택한 부서에 대한 의료진 출력
private:
	vector<Doctor*>v;
	Doctor* doctor;
	string deptName;
};

/*===Hospital 클래스====*/
//프로그램 핵심 기능 활성화 메서드 정의 --> 각 기능 준비 단계(해당 프로그램 특성상 입력값이 많아 중간 단계설정)
//클래스 이름대로 병원에서 부서를 선택하고 해당 부서 원무처에서 의사를 선택할 수 있는 클래스
//필요한 tokenizing 메서드 정의 --> txt파일에서 조건에 맞게 필요한 부분 문자열 추출
//기본 생성자에서 진료부서 초기화 부터 모든 부서에 대한 의료진 초기화
class Hospital{
public:
	/*Constructor & Destructor*/
	Hospital();//프로그램에 필요한 모든 텍스트 데이터 로딩
	~Hospital() { delete[]dept; }
	/*Function*/
	string tokenizing_dept(string const& str);//부서 이름 추출
	string tokenizing_file(string const& str);//파일 이름 추출
	void activation_booking(int num);//예약 기능 활성화
	void activation_booking2(int num);
	void activation_chk(int num);//조회 기능 활성화
	void activation_cancel(int num);//취소 기능 활성화
	void display_deptList();//병원 내 전체 진료부서 출력
private:
	Department* dept;//크기 9인 객체배열 동적 생성
	vector<string>vec_dept;//출력을 위해 토그나이징 데이터 벡터 저장
};

/*===Console 클래스====*/
//전체 프로그램 제어 메서드 정의 --> 시스템 실행 함수
//사용자 입력 메서드 정의 --> 메뉴, 진료부서, 예약방식 선택
//window api 콘솔 좌표 제어 메서드 정의 --> gotoxy를 static으로 선언해 필요한 부분에서
//콘솔 조작
class Console {
public:
	/*Constructor & Destructor*/
	Console() { hp = new Hospital(); }
	~Console() { delete hp; }
	/*Function*/
	void execute_prog();//시스템 실행
	static int select_menu();//메뉴 선택
	static int select_dept();//진료부서 선택
	static int select_method();//예약 방식 선택
	static void gotoxy(int x, int y);//콘솔화면 좌표 조작
private:
	Hospital* hp;
};
#endif // !__HOSPITAL__H