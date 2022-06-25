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
#include <numeric>
#include <color.hpp>
#include <tabulate/table.hpp>

using namespace tabulate;
using namespace hue;
using namespace dye;
using namespace std;

const string t = "  ";

vector<int>sequences;
vector<int>seqProcess;
vector<int>MaxA, MaxB, MaxC;
vector<int>needA, needB, needC;
vector<int>allocateA, allocateB, allocateC;
vector<int> Aavailable, Bavailable, Cavailable;
int AResource, BResource, CResource;
int process;
int code = 0;//Showing state of program 

void error() {
	int func = code / 1000, type = code % 1000;
	string sp = string(10, ' ');
	string s = string(70, '*');
	string ERRORLIST[][2] = {
		{"  MAX()","\t You Have Requested Too Much!"},
		{"  Allocate()","\t You Have Entered Too Much!"},
		{"  Check","\t These Sequences Are Deadlock!"}
	};
	cout << "\n" << s << "\nError Code | Error Type | Function Name | Massage";
	cout << "\n\n  " << code << sp << (char)(type) << sp <<
		ERRORLIST[func - 1][0] << ERRORLIST[func - 1][1] << "\n" << s << "\n";
	exit(0);
}
string itos(int num) {
	string _num;
	_num = to_string(num);
	return _num;
}
string itos(vector<int>num) {
	stringstream ss;
	copy(num.begin(), num.end(), ostream_iterator<int>(ss, " "));
	string _num = ss.str();
	_num = _num.substr(0, _num.length() - 1);
	return _num;
}
vector<int> permGenerator(int n, int k) {
	vector<int> d(n), num;
	iota(d.begin(), d.end(), 1);
	do {
		for (int i = 0; i < k; i++) {
			num.push_back(d[i]);
		}
		std::reverse(d.begin() + k, d.end());
	} while (next_permutation(d.begin(), d.end()));
	return num;
}
void clear() {
	allocateA.clear();
	allocateB.clear();
	allocateC.clear();
	Aavailable.clear();
	Bavailable.clear();
	Cavailable.clear();
	MaxA.clear();
	MaxB.clear();
	MaxC.clear();
	needA.clear();
	needB.clear();
	needC.clear();
}
int sum(vector<int>num) {
	int total = 0;
	for (int i = 0; i < num.size(); i++)
		total = total + num[i];
	return total;
}
void Available() {
	Aavailable.push_back(AResource - sum(allocateA));
	Bavailable.push_back(BResource - sum(allocateB));
	Cavailable.push_back(CResource - sum(allocateC));
}
int Check(int mode) {
	vector<int>tempA, tempB, tempC;
	tempA = allocateA;
	tempB = allocateB;
	tempC = allocateC;
	for (int i = 0; i < process; i++) {
		int currentProcess = seqProcess[i];
		if (needA[currentProcess] <= Aavailable[i] &&
			needB[currentProcess] <= Bavailable[i] &&
			needC[currentProcess] <= Cavailable[i]) {
			allocateA[currentProcess] = 0;
			allocateB[currentProcess] = 0;
			allocateC[currentProcess] = 0;
			Available();
		}
		else if (mode) {
			system("cls");
			code = 3045;
			error();
		}
		else if (!mode) {
			return 1;
		}
	}
	allocateA = tempA;
	allocateB = tempB;
	allocateC = tempC;
	return 0;
}
void makeSequence() {
	vector<int>temp, seq, correctSeq;

	temp = permGenerator(process, process);
	for (int i = 0; i < temp.size(); i++)
		temp[i] -= 1;

	for (int i = 0; i < (temp.size() / process); i++) {
		Aavailable.clear();
		Bavailable.clear();
		Cavailable.clear();
		Available();
		for (int j = i * process; j < (i * process + process); j++)
			seq.push_back(temp[j]);
		seqProcess = seq;
		if (!Check(0)) {
			correctSeq.reserve(correctSeq.size() + distance(seq.begin(), seq.end()));
			correctSeq.insert(correctSeq.end(), seq.begin(), seq.end());
		}
		seq.clear();
		seqProcess.clear();
	}
	seqProcess = correctSeq;
}
void print() {
	Check(1);
	Table mytable;
	string ABC = 'A' + t + 'B' + t + 'C';
	mytable.add_row({ "Allocated","Max","Available","Need" });
	mytable.add_row({ ABC,ABC,ABC,ABC });
	for (int i = 0; i < process; i++) {
		mytable.add_row({ itos(allocateA[i]) + t + itos(allocateB[i]) + t + itos(allocateC[i]),
			itos(MaxA[i]) + t + itos(MaxB[i]) + t + itos(MaxC[i]),
			itos(Aavailable[i]) + t + itos(Bavailable[i]) + t + itos(Cavailable[i]),
			itos(needA[i]) + t + itos(needB[i]) + t + itos(needC[i])
			});
	}
	int i = process;
	mytable.add_row({ "","",itos(Aavailable[i]) + t + itos(Bavailable[i]) + t + itos(Cavailable[i]),"" });

	mytable.format()
		.font_align(FontAlign::center)
		.border(" ")
		.corner(" ")
		.font_background_color(Color::green);

	mytable[0].format()
		.padding_top(1)
		.padding_bottom(1)
		.font_background_color(Color::cyan);

	mytable[1].format()
		.padding_top(1)
		.padding_bottom(1)
		.font_background_color(Color::yellow);

	system("cls");
	cout << mytable;

}
void Need() {
	for (int i = 0; i < process; i++) {
		needA.push_back(MaxA[i] - allocateA[i]);
		needB.push_back(MaxB[i] - allocateB[i]);
		needC.push_back(MaxC[i] - allocateC[i]);
	}
}
void MAX() {
	cout << "\nHow Many Resources Do You Have?(A,B,C) : ";
	cin >> AResource >> BResource >> CResource;
	cout << "\nEnter Number Of Processes : ";
	cin >> process;

	cout << "\nEnter Number Of Resources Requested By Pi From ( A ): ";
	for (int i = 0; i < process; i++) {
		cout << black_on_yellow << "\nP" << i << ":"
			<< reset << " ";
		MaxA.push_back(_getche() - 48);
		if (MaxA.back() > AResource) {
			code = 1065;
			error();
		}
	}
	cout << "\nEnter Number Of Resources Requested By Pi From ( B ): ";
	for (int i = 0; i < process; i++) {
		cout << black_on_yellow << "\nP" << i << ":"
			<< reset << " ";
		MaxB.push_back(_getche() - 48);
		if (MaxB.back() > BResource) {
			code = 1066;
			error();
		}
	}
	cout << "\nEnter Number Of Resources Requested By Pi From ( C ): ";
	for (int i = 0; i < process; i++) {
		cout << black_on_yellow << "\nP" << i << ":"
			<< reset << " ";
		MaxC.push_back(_getche() - 48);
		if (MaxC.back() > CResource) {
			code = 1067;
			error();
		}
	}
}
void Allocate() {
	MAX();

	cout << "\nEnter Number Of Resources Allocated To Pi From ( A ): ";
	for (int i = 0; i < process; i++) {
		cout << black_on_yellow << "\nP" << i << ":"
			<< reset << " ";
		allocateA.push_back(_getche() - 48);
	}
	if (sum(allocateA) > AResource) {
		code = 2065;
		error();
	}
	cout << "\nEnter Number Of Resources Allocated To Pi From ( B ): ";
	for (int i = 0; i < process; i++) {
		cout << black_on_yellow << "\nP" << i << ":"
			<< reset << " ";
		allocateB.push_back(_getche() - 48);
	}
	if (sum(allocateB) > BResource) {
		code = 2066;
		error();
	}
	cout << "\nEnter Number Of Resources Allocated To Pi From ( C ): ";
	for (int i = 0; i < process; i++) {
		cout << black_on_yellow << "\nP" << i << ":"
			<< reset << " ";
		allocateC.push_back(_getche() - 48);
	}
	if (sum(allocateC) > CResource) {
		code = 2067;
		error();
	}
	cout << "\n\n\nChoose #1 If You Want To Enter A Sequence / #2 If You Want To See All Undeadlock's Sequences :  ";
	int op = _getche() - 48;
	while (op != 1 && op != 2) {
		cout << hue::black_on_light_red << "\nPlease Enter Again :" << reset << " ";
		op = _getche() - 48;
	}
	if (op == 1) {
	loop:
		cout << "\nEnter a Sequence of Processes(Just Index of Process) : ";
		for (int i = 0; i < process; i++) {
			cout << "P";
			seqProcess.push_back(_getche() - 48);
			cout << ", ";
		}
		for (int i = 0; i < process; i++) {
			if (!(seqProcess[i] >= 0 && seqProcess[i] < process)) {
				cout << black_on_light_red << "\nYour Sequence Is Not Valid.\nTry Again.."
					<< reset;
				seqProcess.clear();
				goto loop;
			}
		}
		for (int i = 0; i < process; i++) {
			for (int j = 0; j < process; j++) {
				if (i == j)continue;
				if (seqProcess[i] == seqProcess[j]) {
					cout << black_on_light_red << "\nYour Sequence Is Not Valid.\nTry Again.."
						<< reset;
					seqProcess.clear();
					goto loop;
				}
			}
		}
		Need();
		Available();
		print();
	}
	else {
		Need();
		makeSequence();
		if (!seqProcess.empty()) {
			cout << "\n\nThese Sequences Are Not Deadlock";
			for (int i = 0; i < (seqProcess.size() / process); i++) {
				cout << "\n#" << i + 1 << " [";
				cout << "P" << seqProcess[i] << ", ";
				cout << "P" << seqProcess[i + 1] << ", ";
				cout << "P" << seqProcess[i + 2];
				cout << "]";
			}
			cout << "\n";
		}
		else cout << "\n\nAll Sequences Are Deadlock!";
	}

}




int main()
{
	Allocate();
	clear();


	_getche();
	return 0;
}