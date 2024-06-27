#include"����ѧУ����ϵͳ.h"
school::school(size_t tea_num) {//���캯������ʼ��ϵͳ����ȡѧ����Ϣ����ʦ��Ϣ
	cout << "ϵͳ��ʼ����......\n";
	T.reserve(tea_num);
	documentreadstu();
	documentreadtea();
	system("cls");
}
school::~school() {//��������,����ѧ����Ϣ����ʦ��Ϣ
	cout << "ϵͳ���ڱ������ݣ����Ժ�......\n";
	documentwritstu();
	documentwrittea();
	system("cls");
}
//�ж��꼶�Ϳ�Ŀ�Ƿ����
bool school::ifexistgraorsub(cstrref ss, string& G, string& S, string& I) {
	cout << "��ֱ�����Ҫ" << ss << "��ѧ�����꼶��ѡ�ơ���ѧ��������������Ϣ��ѧ�š��༶��������:\n";
	cin >> G >> S >> I;
	if (students[G][S].empty()) {//����Ӧ���꼶��ѡ������ѧ��������ʾ��
		cout << "���꼶��ѡ�����޴�ѧ����\n";
		return false;
	}return true;
}


void school::documentreadstu() {
	ifstream A("student.csv"); if (!A.is_open()) throw invalid_argument("ѧ���ļ���ʧ��!\n");
	if (A.is_open()) {	
		cout << "ѧ����Ϣ��ȡ��\n";
		string line;//���ж�ȡ�ļ���
		while (getline(A, line)) {//���ж�ȡ�ļ�
			stringstream ss(line);  string temp[6];
			for (auto& s : temp) { getline(ss >> ws, s, ','); }
			students[temp[2]][temp[4]].emplace_back(temp[0], temp[5], temp[1], temp[2], temp[4], stoi(temp[3]));
		}A.close(); system("cls");
	}

}

void school::documentwritstu() {
	cout << "ѧ����Ϣ���ڱ�����......\n";
	//ofstream grade_subjectdocument[36]; ofstream gradedocument[3]; 
	myarray<ofstream,36> grade_subjectdocument; myarray<ofstream,3> gradedocument; ofstream studentdoc("student.csv");
	for (int i = 0; i < grade.getsize(); i++) {
		string filename = grade[i] + "ѧ����Ϣ.csv"; gradedocument[i].open(filename);
		for (int j = 0; j < Subjects.getsize(); j++) {
			string filename2 = grade[i] + Subjects[j] + "ѧ����Ϣ.csv";
			grade_subjectdocument[i * 12 + j].open(filename2);
			if (students[grade[i]].find(Subjects[j]))
			{
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					gradedocument[i] << stu.putinfointodoc() << endl;
					grade_subjectdocument[static_cast<size_t>(i) * 12 + j] << stu.putinfointodoc() << endl;
					studentdoc << stu.putinfointodoc() << endl;
				}
			}
			//else cerr<<"�꼶"<<grade[i]<<",��Ŀ"<<Subjects[j]<<"����ѧ��"<<endl;
			grade_subjectdocument[i * 12 + j].close();
		}
		gradedocument[i].close();
	}
	studentdoc.close();
	system("pause");
	system("cls");//A.close();
}
void school::showallstudentinfo() {
	for (int i = 0; i < grade.getsize(); i++) {
		cout << "�꼶��" << grade[i] << endl;
		for (int j = 0; j < Subjects.getsize(); j++) {
			if (students[grade[i]].find(Subjects[j])) {
				cout << "ѡ�ƣ�" << Subjects[j] << endl;
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					stu.show();
				}
			}
		}
	}system("pause");
}
void school::addstudentsinfo() {
	cout << "������Ӽ���ѧ������Ϣ?" << endl;
	int num; cin >> num;
	for (int i = 0; i < num; i++) {
		student stu; stu.input(); string Grade = stu.grade; string Subject = stu.choice;
	    students[Grade][Subject].push_back(move(stu));
	}
	documentwritstu();
}
void school::deletestudent() {
	string Grade, Subject, ID;
	if (!ifexistgraorsub("ɾ��", Grade, Subject, ID)) return;
	students[Grade][Subject].remove_if([ID](student& s) {
		return (s.id == ID || to_string(s.stuclass) == ID || s.name == ID); });
	documentwritstu(); system("pause");
}
void school::findstudent() {
	string Grade, Subject, ID;
	if (!ifexistgraorsub("����", Grade, Subject, ID)) return;int count = 0;
	for (const auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == (ID) || stu.name == ID) {
			cout << "�ҵ��ĵ�" << ++count << "��ѧ����Ϣ���£�\n";
			stu.show();
		}
	}
	if (count == 0) { cout << "���޴���" << endl; }
	system("pause");
}//����ѧ����Ϣ
void school::changestudent() {
	string Grade, Subject, ID;
	if (!ifexistgraorsub("�޸�", Grade, Subject, ID)) return;
	myvector<student*> tempP;
	for (auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == ID || stu.name == ID) {
			tempP.push_back(&stu);
		}
	}
	if (tempP.empty()) { cout << "���޴���" << endl; return; }
	else { cout << "�ҵ�" << tempP.getsize() << "��ѧ������Ϣ;" << endl; }
	cout << "��Ҫ�޸Ķ���ѧ������Ϣ��\n"; size_t n; cin >> n; size_t i = 0;
	if (n > tempP.getsize()) { cout << "������������ڲ��ҵ����������޸�ȫ�����ҵ�ѧ����Ϣ��\n";
	n = tempP.getsize(); }
	for (auto stu : tempP) {
		if (i >= n)break;
		cout << "Ҫ�޸ĵ�"<<++i<<"��ѧ����Ϣ���£�\n";stu->show();
		cout << "�������޸ĺ��ѧ����Ϣ��\n";stu->input();
	}
	documentwritstu(); system("pause");
}
void school::showallteacherinfo() {
	showheadtea();
	for (auto& t : T) { t.show(1); }
	cout << "������������˳�\n"; system("pause"); system("cls");
}
void school::addteachersinfo() {//�����ʦ������Ϣ��������Ǹ��ļ�D://teacher.txt������۵�Ӱ��
	int n;//������ѧ��������
	cout << "������Ӷ�����ʦ�ĸ�����Ϣ\n"; cin >> n;
	for (int i = 0; i < n; i++)
	{
		teacher A; A.input(); T.push_back(move(A));
	}system("pause"); documentwrittea();
}

void school::findteacher() {
	myvector<teacher>ss; string find = "0";
	string L; cout << "��������ʦ��������id���ν̿�Ŀ\n"; cin >> L;
	showheadtea();
	for (const auto& s : T) {
		if (s.name == L || s.id == L || s.subject == L) {
			s.show(1); ss.push_back(s); find = "1";
		}
	}if (find=="0") { cout << "���޴���" << endl; system("pause"); return; }
	cout << "�Ƿ񽫽����ӡ���ļ���\n����ӡ����0����ӡ�ļ���������"; cin >> find;
	if (find=="0") { system("pause"); return; }
	string filename = L; cout << "�������ļ���(ȫ����\n"; cin >> filename;
	ofstream F(filename); F << "����" << ',' << "�Ա�" << ',' << "ѧ��" << ',' << "��ѧ��Ŀ"<<','<<"нˮ" << endl;
	for (const auto& l : ss) 
		F << l.putinfointodoc() << endl;
	cout << "��ӡ�ɹ�\n"; F.close();
	system("pause");
}
void school::deleteteacher() {
	bool find = 0; size_t T1 = 0, T2 = 0;
	string L; cout << "�������ɾ����ʦ��������id���ν̿�Ŀ\n"; cin >> L; T1 = T.getsize();
	T.remove_if([L](teacher& s) {return(s.name == L || s.id == L || s.subject == L); });
	T2 = T.getsize();bool p = (T1 != T2);
	cout << (p ? "ɾ���ɹ�\n" : "���޴���\n") << endl; if (p) { documentwrittea(); }
}


void school::changeteacher() {
	bool find = 0;
	string L; cout << "��������޸Ľ�ʦ��������id�����ν̿�Ŀ\n"; cin >> L;
	myvector<teacher*> tempP;
	for (auto& s : T) {//auto&s:S�����޸����ݣ�
		if (s.name == L || s.id == L || s.subject == L)
		{
			tempP.push_back(&s); find = 1;
		}
	}if (!find) { cout << "���޴���" << endl; return; }
	size_t m,n=tempP.getsize(),p=0;
	cout << "�ҵ�" << n << "����ʦ����Ϣ;" << endl;
	cout << "��Ҫ�޸Ķ��ٽ�ʦ����Ϣ��\n"; cin >> m;
	if (m > n) { cout << "������������ڲ��ҵ����������޸�ȫ�����ҵĽ�ʦ��Ϣ��\n"; m = n; }
	for (auto &s : tempP) {
		if (p >= m)break;
		cout << "Ҫ�޸ĵ�" << ++p << "����ʦ��Ϣ���£�\n"; s->show(1);
		cout << "�Ƿ��޸Ľ�ʦ����:" << s->name << endl;
		if (choice()) { cout << "������ĺ��ʦ������"; cin >> s->name; }
		cout << "�Ƿ��޸Ľ�ʦid:" << s->id << endl;
		if (choice()) { cout << "������ĺ��ʦid��"; cin >> s->id; }
		cout << "�Ƿ��޸Ľ�ʦ��ѧ��Ŀ:" << s->subject << endl;
		if (choice()) { cout << "������ĺ��ʦ��ѧ��Ŀ��"; cin >> s->subject; }
		cout << "�Ƿ��޸Ľ�ʦнˮ:" << s->salary << endl;
		if (choice()) { cout << "������ĺ��ʦнˮ��"; cin >> s->salary; }
	}
	
	documentwrittea();system("pause");
}

void school::documentreadtea() {//���ж�ȡteacher.txt
	ifstream B("teacher.csv"); if (!B.is_open()) throw invalid_argument("��ʦ�ļ���ʧ��!\n");
	if (B.is_open())
	{
		cout << "��ʦ��Ϣ��ȡ��\n";
		string line;//���ж�ȡ�ļ���
		while (getline(B, line)) {

			stringstream ss(line);
			teacher tea;
			myarray<string, 5> temp;
			for (auto& elem:temp) {
				getline(ss >> ws, elem, ',');
			}
			tea.name = temp[0];  tea.sex = temp[1]; tea.id = temp[2]; tea.subject = temp[3]; tea.salary = stod(temp[4]);
			T.push_back(move(tea));
		}
		B.close(); system("cls");
	}
}


void school::documentwrittea() {//��ʦ��Ϣ�ļ�����
	ofstream B("teacher.csv"); cout << "��ʦ��Ϣ�ļ�������......\n";
	for (const auto& tea : T) {
		B << tea.putinfointodoc() << endl;
	}B.close(); system("cls");
}