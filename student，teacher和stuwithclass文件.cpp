#include"����ѧУ����ϵͳ.h"
using namespace std;
void teacher::show(bool x) const {
	if (x == 0)
		cout << "������" << name << "�Ա�" << sex << "��ʦid:" << id << "ѧ��:" << subject <<"����:"<<salary << endl;
	else cout << name << '\t' << sex << '\t' << id << '\t' << subject << '\t' << salary <<"\t\n" ;
}
void teacher::input() {//������ʦ��Ϣ��
	cout << "����������:\n"; cin >> name;
	cout << "�������Ա�:\n"; cin >> sex;
	cout << "�������ʦid:\n"; cin >> id;
	cout << "��ʾ����ʦ�ν̵�ѧ�ư���:\n";
	cout << "����, ��ѧ, Ӣ��, ����, ��ѧ, ����,\n ����, ��ʷ, ����, ��Ϣ, ����, ����\n";
	cout << "������ѧ��\n"; cin >> subject;
	cout << "�����빤��:\n"; cin >> salary;
}
string teacher::putinfointodoc()const {
	stringstream temp; temp << name << ',' << sex << ',' << id << ',' << subject<<','<<salary; return move(temp.str());
}

void student::show(bool x) const {
	if (!x)
		cout << "������" << name << " �Ա�" << sex << " ѧ��:" << id << " �꼶:" << grade << " �༶" << stuclass << " ѡ��:" << choice << endl;
	else
		cout  << name << '\t' << sex << '\t' << id << '\t' << grade << '\t' << stuclass << '\t' << choice <<"\t\n";
}
void student::input(bool flag) {//����ѧ����Ϣ��
	cout << "������������\n"; cin >> name;
	cout << "�������Ա�(��/Ů):\n"; cin >> sex;
	cout << "������ѧ��:\n"; cin >> id;
	cout << "�������꼶\n";
	cout << "(��ʾ���꼶��������һ���߶�������):\n"; cin >> grade;
	cout << "������༶:\n"; cin >> stuclass;
	cout << "������ѡ��\n";
	cout << "��ʾ:ѡ�ư���:\n�ﻯ��,�ﻯ��,�ﻯ��,������,������,������,\n������,������,������,������,������,������:\n"; cin >> choice;
}
string student::putinfointodoc()const {
	stringstream temp; 
	temp << name << "," << id << "," << grade << "," << stuclass << "," << choice << "," << sex; return temp.str();
}
void showheadtea() {
	cout <<  "����\t" <<"�Ա�\t"  << "��ʦid\t"  << "ѧ��\t" << "����\t\n";

}
void showheadstu() {
	cout << "����\t" << "�Ա�\t" << "ѧ��\t" << "�꼶\t" << "�༶\t" << "ѡ��\t\n" ;
}
void stuwithscore::scoreinputB() {  //ѡ�ƺ�ĳɼ����뺯��������Ӣ��3��4��5��6��7��8
	myhash_map<string, myvector<int>> subject_to_indices = {
	 {"�ﻯ��", {3, 4, 5}},{"�ﻯ��", {3, 4, 7}},{"�ﻯ��", {3, 4, 8}},{"������", {3, 5, 7}},{"������", {3, 5, 8}},{"������", {3, 7, 8}},
	 {"������", {6, 4, 5}},{"������", {6, 4, 7}},{"������", {6, 4, 8}},{"������", {6, 5, 7}},{"������", {6, 5, 8}},{"������", {6, 7, 8}} };
	string i;
	do {
		for (auto& data : score)data = 0;
		cout << "���������ģ���ѧ��Ӣ��ɼ�\n";
		for (int i = 0; i < 3; i++)
			cin >> score[i];
		cout << "������" << choice << "�ɼ�\n";
		// ����ѡ�������Ӧ�ĳɼ�  
		auto it = subject_to_indices.find(choice);
		if (it) {
			for (int index : it->data.second) {
				cout << "������" << subjects[index] << "�ɼ�\n";
				cin >> score[index];
			}
		}
		else {
			cout << "ѡ����Ч\n";
			break;
		}
		cout << "�Ƿ�ȷ����ȷ���밴0����ȷ���밴����\n"; cin >> i;
	} while (i != to_string(0)); calculatetotal();
}
void stuwithscore::scoreinputA() {//cout << "���������ģ���ѧ��Ӣ�������ѧ�������ʷ�����Σ�����ɼ�\n";
	for (size_t i = 0; i < 9; i++) { cout << "������" << subjects[i] << "�ɼ�\n"; cin >> score[i]; }calculatetotal();
}

void stuwithscore::print(bool k )const {
	if (!k) {
		cout  << name << '\t' << id << '\t' << choice << '\t' << stuclass;
	}
	else {
		cout << '\t' << "����:" << '\t' << name << '\t' << "ѧ��:" <<'\t' << id;
	}
	cout << "\n";
	for (int i = 0; i < 9; i++) {
		cout  << score[i]<<'\t';
	}cout << endl;
	cout  << total <<"\t\n";
}
string stuwithscore::putinfointodoc() const{
	stringstream of; of << name << "," << choice << "," << id << "," << stuclass;
	for (int i = 0; i < 9; i++) {
		of << "," << score[i];
	}of << "," << total; return of.str();
}