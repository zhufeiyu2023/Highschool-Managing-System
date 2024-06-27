#include"高中学校管理系统.h"
school::school(size_t tea_num) {//构造函数，初始化系统，读取学生信息和老师信息
	cout << "系统初始化中......\n";
	T.reserve(tea_num);
	documentreadstu();
	documentreadtea();
	system("cls");
}
school::~school() {//析构函数,保存学生信息和老师信息
	cout << "系统正在保存数据，请稍侯......\n";
	documentwritstu();
	documentwrittea();
	system("cls");
}
//判断年级和科目是否存在
bool school::ifexistgraorsub(cstrref ss, string& G, string& S, string& I) {
	cout << "请分别输入要" << ss << "的学生的年级、选科、和学生的任意其他信息（学号、班级、姓名）:\n";
	cin >> G >> S >> I;
	if (students[G][S].empty()) {//若对应的年级和选科下无学生，则提示；
		cout << "该年级和选科下无此学生！\n";
		return false;
	}return true;
}


void school::documentreadstu() {
	ifstream A("student.csv"); if (!A.is_open()) throw invalid_argument("学生文件打开失败!\n");
	if (A.is_open()) {	
		cout << "学生信息读取中\n";
		string line;//按行读取文件；
		while (getline(A, line)) {//逐行读取文件
			stringstream ss(line);  string temp[6];
			for (auto& s : temp) { getline(ss >> ws, s, ','); }
			students[temp[2]][temp[4]].emplace_back(temp[0], temp[5], temp[1], temp[2], temp[4], stoi(temp[3]));
		}A.close(); system("cls");
	}

}

void school::documentwritstu() {
	cout << "学生信息正在保存中......\n";
	//ofstream grade_subjectdocument[36]; ofstream gradedocument[3]; 
	myarray<ofstream,36> grade_subjectdocument; myarray<ofstream,3> gradedocument; ofstream studentdoc("student.csv");
	for (int i = 0; i < grade.getsize(); i++) {
		string filename = grade[i] + "学生信息.csv"; gradedocument[i].open(filename);
		for (int j = 0; j < Subjects.getsize(); j++) {
			string filename2 = grade[i] + Subjects[j] + "学生信息.csv";
			grade_subjectdocument[i * 12 + j].open(filename2);
			if (students[grade[i]].find(Subjects[j]))
			{
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					gradedocument[i] << stu.putinfointodoc() << endl;
					grade_subjectdocument[static_cast<size_t>(i) * 12 + j] << stu.putinfointodoc() << endl;
					studentdoc << stu.putinfointodoc() << endl;
				}
			}
			//else cerr<<"年级"<<grade[i]<<",科目"<<Subjects[j]<<"下无学生"<<endl;
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
		cout << "年级：" << grade[i] << endl;
		for (int j = 0; j < Subjects.getsize(); j++) {
			if (students[grade[i]].find(Subjects[j])) {
				cout << "选科：" << Subjects[j] << endl;
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					stu.show();
				}
			}
		}
	}system("pause");
}
void school::addstudentsinfo() {
	cout << "你想添加几名学生的信息?" << endl;
	int num; cin >> num;
	for (int i = 0; i < num; i++) {
		student stu; stu.input(); string Grade = stu.grade; string Subject = stu.choice;
	    students[Grade][Subject].push_back(move(stu));
	}
	documentwritstu();
}
void school::deletestudent() {
	string Grade, Subject, ID;
	if (!ifexistgraorsub("删除", Grade, Subject, ID)) return;
	students[Grade][Subject].remove_if([ID](student& s) {
		return (s.id == ID || to_string(s.stuclass) == ID || s.name == ID); });
	documentwritstu(); system("pause");
}
void school::findstudent() {
	string Grade, Subject, ID;
	if (!ifexistgraorsub("查找", Grade, Subject, ID)) return;int count = 0;
	for (const auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == (ID) || stu.name == ID) {
			cout << "找到的第" << ++count << "个学生信息如下：\n";
			stu.show();
		}
	}
	if (count == 0) { cout << "查无此人" << endl; }
	system("pause");
}//查找学生信息
void school::changestudent() {
	string Grade, Subject, ID;
	if (!ifexistgraorsub("修改", Grade, Subject, ID)) return;
	myvector<student*> tempP;
	for (auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == ID || stu.name == ID) {
			tempP.push_back(&stu);
		}
	}
	if (tempP.empty()) { cout << "查无此人" << endl; return; }
	else { cout << "找到" << tempP.getsize() << "个学生的信息;" << endl; }
	cout << "想要修改多少学生的信息？\n"; size_t n; cin >> n; size_t i = 0;
	if (n > tempP.getsize()) { cout << "输入的数量大于查找的数量，将修改全部查找的学生信息！\n";
	n = tempP.getsize(); }
	for (auto stu : tempP) {
		if (i >= n)break;
		cout << "要修改的"<<++i<<"个学生信息如下：\n";stu->show();
		cout << "请输入修改后的学生信息：\n";stu->input();
	}
	documentwritstu(); system("pause");
}
void school::showallteacherinfo() {
	showheadtea();
	for (auto& t : T) { t.show(1); }
	cout << "按任意键即可退出\n"; system("pause"); system("cls");
}
void school::addteachersinfo() {//添加老师个人信息，它会对那个文件D://teacher.txt产生宏观的影响
	int n;//新增的学生个数；
	cout << "你想添加多少老师的个人信息\n"; cin >> n;
	for (int i = 0; i < n; i++)
	{
		teacher A; A.input(); T.push_back(move(A));
	}system("pause"); documentwrittea();
}

void school::findteacher() {
	myvector<teacher>ss; string find = "0";
	string L; cout << "请输入老师的姓名，id或任教科目\n"; cin >> L;
	showheadtea();
	for (const auto& s : T) {
		if (s.name == L || s.id == L || s.subject == L) {
			s.show(1); ss.push_back(s); find = "1";
		}
	}if (find=="0") { cout << "查无此人" << endl; system("pause"); return; }
	cout << "是否将结果打印到文件？\n不打印输入0，打印文件输入其他"; cin >> find;
	if (find=="0") { system("pause"); return; }
	string filename = L; cout << "请输入文件名(全名）\n"; cin >> filename;
	ofstream F(filename); F << "姓名" << ',' << "性别" << ',' << "学号" << ',' << "教学科目"<<','<<"薪水" << endl;
	for (const auto& l : ss) 
		F << l.putinfointodoc() << endl;
	cout << "打印成功\n"; F.close();
	system("pause");
}
void school::deleteteacher() {
	bool find = 0; size_t T1 = 0, T2 = 0;
	string L; cout << "请输入待删除老师的姓名，id或任教科目\n"; cin >> L; T1 = T.getsize();
	T.remove_if([L](teacher& s) {return(s.name == L || s.id == L || s.subject == L); });
	T2 = T.getsize();bool p = (T1 != T2);
	cout << (p ? "删除成功\n" : "查无此人\n") << endl; if (p) { documentwrittea(); }
}


void school::changeteacher() {
	bool find = 0;
	string L; cout << "请输入待修改教师的姓名，id，或任教科目\n"; cin >> L;
	myvector<teacher*> tempP;
	for (auto& s : T) {//auto&s:S可以修改数据；
		if (s.name == L || s.id == L || s.subject == L)
		{
			tempP.push_back(&s); find = 1;
		}
	}if (!find) { cout << "查无此人" << endl; return; }
	size_t m,n=tempP.getsize(),p=0;
	cout << "找到" << n << "个教师的信息;" << endl;
	cout << "想要修改多少教师的信息？\n"; cin >> m;
	if (m > n) { cout << "输入的数量大于查找的数量，将修改全部查找的教师信息！\n"; m = n; }
	for (auto &s : tempP) {
		if (p >= m)break;
		cout << "要修改的" << ++p << "个教师信息如下：\n"; s->show(1);
		cout << "是否修改教师姓名:" << s->name << endl;
		if (choice()) { cout << "请输入改后教师姓名："; cin >> s->name; }
		cout << "是否修改教师id:" << s->id << endl;
		if (choice()) { cout << "请输入改后教师id："; cin >> s->id; }
		cout << "是否修改教师教学科目:" << s->subject << endl;
		if (choice()) { cout << "请输入改后教师教学科目："; cin >> s->subject; }
		cout << "是否修改教师薪水:" << s->salary << endl;
		if (choice()) { cout << "请输入改后教师薪水："; cin >> s->salary; }
	}
	
	documentwrittea();system("pause");
}

void school::documentreadtea() {//逐行读取teacher.txt
	ifstream B("teacher.csv"); if (!B.is_open()) throw invalid_argument("教师文件打开失败!\n");
	if (B.is_open())
	{
		cout << "教师信息读取中\n";
		string line;//按行读取文件；
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


void school::documentwrittea() {//教师信息文件保存
	ofstream B("teacher.csv"); cout << "教师信息文件保存中......\n";
	for (const auto& tea : T) {
		B << tea.putinfointodoc() << endl;
	}B.close(); system("cls");
}