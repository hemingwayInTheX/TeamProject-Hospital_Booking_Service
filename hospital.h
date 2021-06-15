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

class Doctor{
public:
	Doctor();
	void setDc(string dcName) { this->dcName = dcName; }
	void setSchedule(string s, int i, int j);
	string getSchedule(string s);
	string getDc() { return dcName; }
	void cancel_sche(string s);
	void display_Schedule();
private:
	string dcName;
	string schedule[6][6];
};

class Department {
public:
	Department() {}
	~Department() { delete doctor; }
	void loadDcList(string filename);
	vector<string> tokenizing_sc(const string str);
	void setDept(string deptName) { this->deptName = deptName; }
	string getDept() { return deptName; }
	void set_reservation();
	void chk_reservation();
	void cancel_reservation();
	int inputDc();
	int inputDay();
	int inputTime();
	string inputInfo();
	void display_dcList();
private:
	vector<Doctor*>v;
	Doctor* doctor;
	string deptName;
};

class Hospital{
public:
	Hospital();
	~Hospital() { delete[]dept; }
	string tokenizing_dept(string const& str);
	string tokenizing_file(string const& str);
	void activation_booking(int num);
	void activation_chk(int num);
	void activation_cancel(int num);
	void display_deptList();
private:
	Department* dept;
	vector<string>vec_dept;
};

class Console {
public:
	Console() { hp = new Hospital(); }
	~Console() { delete hp; }
	void execute_prog();//시스템 실행
	static int select_menu();//메뉴 선택
	static int select_dept();//진료부서 선택
	static int select_method();//예약 방식 선택
	static void gotoxy(int x, int y);//콘솔화면 좌표 조작
private:
	Hospital* hp;
};
#endif // !__HOSPITAL__H