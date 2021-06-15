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

/*===Doctor Ŭ����====*/
//���� ����� ���� �Է¹��� ����� ������ 6X6Matrix�� ������ �ð��� ���Ͽ� �ش�Ǵ� �ε����� �Ҵ�
//����ڰ� �Է��� ���������� ���������� ����Ǵ� Ŭ����
//���� ��� �� �ش� �ε����� null������ ����
class Doctor{
public:
	/*Constructor & Destructor*/
	Doctor();
	/*Function*/
	void setDc(string dcName) { this->dcName = dcName; }//�ǻ� ���� �ʱ�ȭ
	void setSchedule(string s, int i, int j);//���� �� ��� �ǻ��� ������ �ʱ�ȭ --> '-----' : NULL(���� ����) // 'XXXXXXXX' : ����
	string getSchedule(string s);//���� ���� ��ȸ �� ���õ� ���� �ð� ��¥ ���
	string getDc() { return dcName; }//������ �ǻ� ���� �ʱ�ȭ
	void cancel_sche(string s);//���� ��� �� �ش� �ε��� '-----'�� ����
	bool search_Schedule(int num);//������ �����ٷ� ������ �Ƿ��� Ž��
	void display_Schedule_dayver(int num);//���õ� ���Ͽ� �ش�Ǵ� �Ƿ��� �� ���
	void display_Schedule();//������ ���
private:
	string dcName;
	string schedule[6][6];
};

/*===Department Ŭ����====*/
//�� �μ��� ���� �Ƿ��� �� ��� �Ƿ����� ������ �ʱ�ȭ �۾� 
//Ŭ���� �̸���� �μ����� �����ϴ� ���� ����,��ȸ,��ҿ� ���� ���α׷� �ٽ� �޼��� ����
//����� ���� �Է� �� ��¥/�ð� �Է��� ���� �������� ���� ����
class Department {
public:
	/*Constructor & Destructor*/
	Department() {}
	~Department() { delete doctor; }
	/*Function*/
	void loadDcList(string filename);//Hospital�����ڿ��� ȣ��޾� �μ��� �ش��ϴ� ��� �Ƿ����� �Ƿ��� �������� ������ �ʱ�ȭ
	vector<string> tokenizing_sc(const string str);//�ؽ�Ʈ ������ ������ matrix NULL ǥ�ñ�ȣ "----" ��ũ����¡ �۾� ���� ���� ����--> �ǻ� ������ �ʱ�ȭ�� �ʿ��� �۾�
	void setDept(string deptName) { this->deptName = deptName; }//�μ� �̸� �ʱ�ȭ
	string getDept() { return deptName; }//�μ� �̸� ���
	void set_reservation();//���� ����_1��° ���� ���(�ǻ��߽�)
	void set_reservation_sc();//���� ����_2��° ���� ���(������ �߽�)
	void chk_reservation();//���� ��ȸ
	void cancel_reservation();//���� ���
	int inputDc();//��� �Ƿ��� �Է�
	int reinputDc(int num);
	int inputDay();//��¥ �Է�
	int inputTime();//�ð��� �Է�
	string inputInfo();//����� ���� �Է�
	void display_dcList();//������ �μ��� ���� �Ƿ��� ���
private:
	vector<Doctor*>v;
	Doctor* doctor;
	string deptName;
};

/*===Hospital Ŭ����====*/
//���α׷� �ٽ� ��� Ȱ��ȭ �޼��� ���� --> �� ��� �غ� �ܰ�(�ش� ���α׷� Ư���� �Է°��� ���� �߰� �ܰ輳��)
//Ŭ���� �̸���� �������� �μ��� �����ϰ� �ش� �μ� ����ó���� �ǻ縦 ������ �� �ִ� Ŭ����
//�ʿ��� tokenizing �޼��� ���� --> txt���Ͽ��� ���ǿ� �°� �ʿ��� �κ� ���ڿ� ����
//�⺻ �����ڿ��� ����μ� �ʱ�ȭ ���� ��� �μ��� ���� �Ƿ��� �ʱ�ȭ
class Hospital{
public:
	/*Constructor & Destructor*/
	Hospital();//���α׷��� �ʿ��� ��� �ؽ�Ʈ ������ �ε�
	~Hospital() { delete[]dept; }
	/*Function*/
	string tokenizing_dept(string const& str);//�μ� �̸� ����
	string tokenizing_file(string const& str);//���� �̸� ����
	void activation_booking(int num);//���� ��� Ȱ��ȭ
	void activation_booking2(int num);
	void activation_chk(int num);//��ȸ ��� Ȱ��ȭ
	void activation_cancel(int num);//��� ��� Ȱ��ȭ
	void display_deptList();//���� �� ��ü ����μ� ���
private:
	Department* dept;//ũ�� 9�� ��ü�迭 ���� ����
	vector<string>vec_dept;//����� ���� ��׳���¡ ������ ���� ����
};

/*===Console Ŭ����====*/
//��ü ���α׷� ���� �޼��� ���� --> �ý��� ���� �Լ�
//����� �Է� �޼��� ���� --> �޴�, ����μ�, ������ ����
//window api �ܼ� ��ǥ ���� �޼��� ���� --> gotoxy�� static���� ������ �ʿ��� �κп���
//�ܼ� ����
class Console {
public:
	/*Constructor & Destructor*/
	Console() { hp = new Hospital(); }
	~Console() { delete hp; }
	/*Function*/
	void execute_prog();//�ý��� ����
	static int select_menu();//�޴� ����
	static int select_dept();//����μ� ����
	static int select_method();//���� ��� ����
	static void gotoxy(int x, int y);//�ܼ�ȭ�� ��ǥ ����
private:
	Hospital* hp;
};
#endif // !__HOSPITAL__H