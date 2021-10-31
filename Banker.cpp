// Banker.cpp
/*
*
* OS Algorithm
* =============PROJECT============
* Copyright (c) vali ahmad rahmani
* Date Oct,17,2021
* name Banker
*
*/
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

vector<int>allocateA, allocateB, allocateC;
vector<int>MAxA, MAxB, MAxC;
int a, b, c;
int process;
int code = 0;//Show state of program 

void clear() {
	allocateA.clear();
	allocateB.clear();
	allocateC.clear();
	MAxA.clear();
	MAxB.clear();
	MAxC.clear();
}
int sum(vector<int>num) {
	int total = 0;
	for (int i = 0; i < num.size(); i++)
		total = total + num[i];
	return total;
}
void MAX() {
	cout << "\nEnter Number Of Resources Requested By Pi From ( A ): ";
	for (int i = 0; i < process; i++) {
		cout << "\nP" << i << ": ";
		MAxA.push_back(_getche() - 48);
		if (MAxA.back() > a) {
			cout << "\n***ERROR! You Have Requested Too Much!***\n";
			code = 1001;
			return;
		}
	}
	cout << "\nEnter Number Of Resources Requested By Pi From ( B ): ";
	for (int i = 0; i < process; i++) {
		cout << "\nP" << i << ": ";
		MAxB.push_back(_getche() - 48);
		if (MAxB.back() > b) {
			cout << "\n***ERROR! You Have Requested Too Much!***\n";
			code = 1002;
			return;
		}
	}
	cout << "\nEnter Number Of Resources Requested By Pi From ( C ): ";
	for (int i = 0; i < process; i++) {
		cout << "\nP" << i << ": ";
		MAxC.push_back(_getche() - 48);
		if (MAxC.back() > c) {
			cout << "\n***ERROR! You Have Requested Too Much!***\n";
			code = 1003;
			return;
		}
	}
	cout << "\nHave Been Requested." << "\n\n\nA  B  C";
	for (int i = 0; i < process; i++) {
		cout << "\n" << MAxA[i] << "  " << MAxB[i] << "  " << MAxC[i] << "  ";
	}
}
void Allocate() {
	cout << "\nHow Many Resources Do You Have?(A,B,C) : ";
	cin >> a >> b >> c;
	cout << "\nEnter Number Of Processes : ";
	cin >> process;
	MAX();
	if (code) {
		return;
	}
	cout << "\nEnter Number Of Resources Allocated To Pi From ( A ): ";
	for (int i = 0; i < process; i++) {
		cout << "\nP" << i << ": ";
		allocateA.push_back(_getche() - 48);
	}
	if (sum(allocateA) > a) {
		cout << "\n***ERROR! You Have Entered Too Much!***\n";
		code = 2001;
		return;
	}
	cout << "\nEnter Number Of Resources Allocated To Pi From ( B ): ";
	for (int i = 0; i < process; i++) {
		cout << "\nP" << i << ": ";
		allocateB.push_back(_getche() - 48);
	}
	if (sum(allocateB) > b) {
		cout << "\n***ERROR! You Have Entered Too Much!***\n";
		code = 2002;
		return;
	}
	cout << "\nEnter Number Of Resources Allocated To Pi From ( C ): ";
	for (int i = 0; i < process; i++) {
		cout << "\nP" << i << ": ";
		allocateC.push_back(_getche() - 48);
	}
	if (sum(allocateC) > c) {
		cout << "\n***ERROR! You Have Entered Too Much!***\n";
		code = 2003;
		return;
	}
	cout << "\n\n\nA  B  C";
	for (int i = 0; i < process; i++) {
		cout << "\n" << allocateA[i] << "  " << allocateB[i] << "  " << allocateC[i] << "  ";
	}
}
//void ERROR() {
//	int func = code / 1000, part = code % 1000;
//	string ERRORLIST[][2] = {
//		{"MAX()","Requesting Too Much Recourses"},
//		{"Allocate()","Allocating More Than Resourses Exist"}
//	};
//	cout << "\n\n\nError Code  Function Name  Massage";
//	cout << "\n\n\n" << code<<ERRORLIST[func-1][] << 
//
//}

int main()
{

	Allocate();
	/*if (code) {
		ERROR();
	}*/



	cout<<"\nDone!";
	clear();
	return 0;
}