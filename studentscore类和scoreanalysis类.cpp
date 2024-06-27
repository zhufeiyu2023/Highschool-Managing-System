#include"����ѧУ����ϵͳ.h"
using namespace std;
void studentscore::getinfofromschool() {
	cout << "���ڴ��ļ��л�ȡѧ����Ϣ...\n";
	ifstream document("student.csv");
	if (!document.is_open()) { throw invalid_argument("student.csv�ļ��޷���"); }
	string line;//���ж�ȡ�ļ���
	while (getline(document, line)) {
		stringstream ss(line);
		myarray<string, 6> temp;
		for (auto& elem : temp) {
			getline(ss >> ws, elem, ',');
		}
		studatalist[temp[2]].insert((temp[0] + temp[4] + temp[1] + temp[3]), stuwithscore(temp[0], temp[4], temp[1], temp[3]));
	}
	document.close();
	cout << "ѧ����Ϣ��ȡ�ɹ���\n";system("pause");
}
void studentscore::inputscore() {
	cout << "������Ҫ����ɼ����꼶��1��2��3��\n";
	bool t = 0; int temp = choiceensure();
	if (temp == 1) { cout << "ѡ��ǰ����ѡ�ƺ�ѡ��ǰ��1��ѡ�κ�0;\n"; cin >> t; }
	cout << "������ɸѡ����:����,ѧ��,ѡ�ƻ�ѡ��+�༶"; string finder; cin >> finder; 
	myvector<stuwithscore*> tempvec;
	for(auto& elem:studatalist[grade_map[temp]]){
		if (compareequal(finder, elem.second))tempvec.push_back(&elem.second);
	}
	cout<<"�ҵ�"<<tempvec.getsize()<<"��ѧ��\n";
	cout << "����Ϊ���ٸ�ѧ������/�޸ĳɼ���\n"; cin >> temp;int j = 0;
	if(j>=tempvec.getsize())cout<<"������������ѧ�����������Զ�����Ϊ���ֵ\n";
	for (auto elem : tempvec) { if(j>=temp)break; cout << "����Ҫ�޸ĵĵ�"<<++j<<"��ѧ������Ϣ\n"; changestuscore(*elem, t); }
	system("pause");
}
void studentscore::getscorefromdoc() {
	cout << "�������ļ���ѧ���ɼ����꼶(1��2��3)\n";
	bool t = 0; int temp = choiceensure(); int j = temp - 1;
	cout << "�������ļ������ļ�·��(ȫ����\n"; string filename; cin >> filename;
	ifstream A(filename); if (!A.is_open()) { cerr << "�ļ�" << filename << "�޷���\n"; }

	string line;//���ж�ȡ�ļ���
	while (getline(A, line)) {
		stringstream ss(line); 
		
		myarray<string, 14> tempinfo;
		for (auto& i:tempinfo) {
			getline(ss >> ws, i, ',');
		}
		stuwithscore stu(tempinfo[0],tempinfo[1],tempinfo[2],tempinfo[3]);
		for (int i = 0; i < 9; i++) { stu.score[i] = stoi(tempinfo[4 + i]); }
		stu.calculatetotal(); 
		if(studatalist.find(grade_map[j])&&studatalist[grade_map[j]].find(stu.name+stu.choice+stu.id+stu.stuclass))
		studatalist[grade_map[j]][stu.name + stu.choice + stu.id + stu.stuclass] = move(stu);
	}
	cout<<"ѧ����Ϣ��ȡ�ɹ���\n"; system("pause");
}

void studentscore::searchandcalculate() {
	cout << "������Ҫ����ѧ�����꼶��1��2��3��";
	//����������ܳɼ������뷽��ܳɼ�Ϊ�����������һ��
	myarray<double,10> expectation, variance;
	int tempnum = choiceensure();
	cout << "������ɸѡ����:����,ѧ��,ѡ�ƻ�ѡ��+�༶(���ﻯ��11)\n";
	string finder; cin >> finder; 
	stuwithscore::showhead(); cout << '\n'; myvector<stuwithscore>temp;
	for (auto& elem : studatalist[grade_map[tempnum]]) {
		if (compareequal(finder, elem.second))
			temp.push_back(elem.second);
	}
	if (temp.empty()) { cout << "���޴���\n"; return; }
	cout << "�ҵ�" << temp.getsize() << "��ѧ��\n";
	temp.sort(ifgreater);//һԪν�ʣ���������
	temp.traverse([](const stuwithscore& A) {A.print(); });
	cout << "�Ƿ����ƽ�����뷽���������y��������������\n"; string y = "y"; cin >> y; bool p = (y == "y");
	if (p) { calculate(temp, expectation, variance); }
	cout << "�Ƿ��ӡ�ɼ�����������y��������������\n"; string z = "y"; cin >> z; bool q = (z == "y");
	if (q) { writscoredoc(temp, expectation, variance,p); }
	system("pause");
}

void studentscore::showallstuscore() {
	stuwithscore::showhead();
	for (auto& stus : studatalist) {
		for (auto& elem : stus.second) {
			elem.second.print();
		}
	}
	system("pause");
}



//scoreanalysis��
void scoreanalysis::inputscorefromdoc() {
	string t = "1"; int i = 0;
	while (t != "0") {
		cout << "�������" << ++i << "��ѧ���ɼ��ļ����ļ������ļ�·��\n"; string filename; cin >> filename;
		ifstream A(filename); if (!A.is_open()) { cout << "�ļ�" << filename << "�޷���\n"; i--; continue; }
		string line;//���ж�ȡ�ļ���
		while (getline(A, line)) {
			stringstream ss(line); stuwithscore stu;string tempinfo[14];
			for (int i = 0; i < 14; i++) 
				getline(ss >> ws, tempinfo[i], ',');
			stu.name = tempinfo[0]; stu.choice = tempinfo[1]; stu.id = tempinfo[2]; stu.stuclass = tempinfo[3];
			for (int i = 0; i < 9; i++) { stu.score[i] = stoi(tempinfo[4 + i]); }
			stu.calculatetotal(); studatalist[stu.id].push_back(move(stu));
		}cout << "��" << i << "���ļ�" << filename << "��ȡ���\n";
		cout << "�Ƿ��ȡ��" << i + 1 << "���ļ�����������0,������������\n"; cin >> t;
	}system("pause");
}
void scoreanalysis::getanalysis() {
	string temp; cout << "������ѧ��ѧ��\n"; cin >> temp; if (studatalist[temp].empty()) { cout << "���޴���\n"; return; }
	auto p = studatalist[temp].begin();
	cout << "����:" << p->name << "\tѡ��:" << p->choice << "\tid:" << p->id << "\t�༶:" << p->stuclass << "\t\n";
	for (int i = 0; i < 9; i++) { cout << '\t' << subjects[i]; }cout << endl;
	for (auto& studata : studatalist[temp]) {
		for (auto& fensu : studata.score) cout << '\t' << fensu;
		cout << '\t' << studata.total << endl;
	}
	cout << "���������ĸ���Ŀ�ɼ��仯��\n";
	myarray<wstring, 9> Lsubjects = { L"����", L"��ѧ", L"Ӣ��", L"����", L"��ѧ", L"����", L"��ʷ", L"����", L"����"};
	wstring temp2;
	myvector<double> tempvec; int j;
	cout << "���������(1-9)\n";
	cout << "ӳ���ϵ��1.���� 2.��ѧ 3.Ӣ�� 4.���� 5.��ѧ 6.���� 7.��ʷ 8.���� 9.���� 10.�ܷ�\n";
	do {
		cin >> j;
	} while (j < 1 || j>10);
	for (const auto& studata : studatalist[temp]) {
		if (j == 10) { tempvec.push_back(studata.total); continue; }
		tempvec.push_back(studata.score[j-1]);
	}
	if(j!=10)
	    analysis(tempvec.begin(), tempvec.end(),(Lsubjects[j-1]+L"�ɼ��仯").c_str());
	else
		analysis(tempvec.begin(), tempvec.end(), L"�ֳܷɼ��仯");
	system("pause"); 
}

