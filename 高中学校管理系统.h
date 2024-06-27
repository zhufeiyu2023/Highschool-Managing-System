#pragma once

#include"myvector.h"

#include"柱状图.h"

#include<iostream>

#include<string>

#include<fstream>

#include<algorithm>

#include<sstream>

#include<iomanip>

#include<stdexcept>

using namespace std;
using namespace mystl;
using cstrref = const string&;
//按选科分类学生并将其打印到文件
inline bool choice() {
	cout << "不修改请按0,修改请按其他\n";
	string choice = "0"; cin >> choice;
	if (choice == "0")return 0;
	return 1;
}
//person类，所有人员的基类;
//teacher类，教师类，继承自person类;
//student类，学生类，继承自person类;
//school类，学校类，包含学生和老师等，用myvector和myhash_map实现的聚合类;
//stuwithscore类，用于存放学生信息和成绩的结构体;
//studentscore类，用于存放学生的成绩的类;
//scoreanalysis类，用于分析学生的成绩的类;
struct person{
	string name , sex , id ; 
	person(string n="0", string s="男", string i="0") :name(n), sex(s), id(i) {}
	virtual string putinfointodoc()const = 0;
};
const myarray<string,3> grade = { "高一","高二","高三" };//常量数组，用于存放各个年级的名称
const myarray<string, 12> Subjects = { "物化生", "物化政", "物化地", "物生政", "物生地", "物政地", "历化生", "历化政", "历化地", "历生政", "历生地", "历政地" };
const myarray<string,12> subjects= { "语文", "数学", "英语", "物理", "化学", "生物", "历史", "政治", "地理"," 信息", "体育", "艺术" };
struct teacher:public person {
	string subject; double salary;
	teacher(cstrref n = "0", cstrref s = "男", cstrref i = "0", cstrref sub = "0", double sal = rand()%5000) :
		person(n, s, i), subject(sub), salary(sal) {}
	//任教科目
	void show(bool x = 0) const;//展示老师信息
	void input(); //输入老师信息
	string putinfointodoc()const override;//将老师信息以字符串的形式写入文件
};
struct student:public person{//学生结构体，其中的元素和函数对单个学生起作用
	string grade, choice; int stuclass;
	student(cstrref n = "0", cstrref s = "男", cstrref i = "0", cstrref g = "0", cstrref c = "0", int sc = 0) :
		person(n, s, i), grade(g), choice(c), stuclass(sc) {}
	//年级，选科，班级
	void show(bool x = 0) const;//展示学生信息
	void input(bool flag = 0);//输入学生信息
	string putinfointodoc()const override;//将学生信息以字符串的形式写入文件
};
void showheadtea();//展示所有老师信息的表头
void showheadstu();//展示所有学生信息的表头
class school{
public:
private:myvector<teacher> T; myhash_map<string, myhash_map<string, myvector<student>>> students;//键值对
	   void documentreadstu();//读取学生信息
	   void documentreadtea();//读取老师信息
	   void documentwritstu();//写入学生信息
	   void documentwrittea(); //写入老师信息
	   bool ifexistgraorsub(cstrref ss, string& G, string& S, string& I);//判断年级和科目是否存在
public:
	school(size_t tea_num = 400);
	~school();
	void showallstudentinfo();//展示所有学生信息
	void showallteacherinfo();//展示所有老师信息
	void addstudentsinfo();//添加学生信息
	void addteachersinfo();//添加老师信息
	void findstudent();//查找学生信息
	void findteacher();//查找老师信息
	void deleteteacher();//删除老师信息
	void deletestudent();//删除学生信息
	void changestudent();//修改学生信息
	void changeteacher();//修改老师信息
};


struct stuwithscore {
	string name, choice, id, stuclass;
	myarray<double, 9> score; double total;
	stuwithscore (cstrref n = "0", cstrref c = "0", cstrref i = "0", cstrref sc = "0",double total=0) :
		name(n), choice(c), id(i), stuclass(sc), total(total) {
	}
	void calculatetotal() {
		total = 0;for (auto& i : score) {total += i;}
	}
	void scoreinputB();//输入选科后成绩
	void scoreinputA();//输入选科前成绩
	void print(bool k = 0)const;//打印学生信息
	string putinfointodoc()const;//将学生成绩信息以字符串的形式写入文件
	static string showhead(bool t = true) {//打印学生信息表头
		stringstream ss;
		if (t)//打印表头,t为true时打印表头，否则打印数据
		{ss << "姓名\t" << "学号\t"  << "选科\t" << "班级\t";
		for (int i = 0; i < 9; i++) { ss << subjects[i]<<'\t'; }ss  << "总分\t\n"; }
		else {ss << "姓名" << "," << "选科" << "," << "学号" << "," << "班级";
		for (int i = 0; i < 9; i++) { ss << "," << subjects[i]; }ss << "," << "总分\n";}
		return move(ss.str());
	}
};

//void print(stuwithscore& A);//打印学生信息

inline void writscoredoc(myvector<stuwithscore>& A,myarray<double,10>&average,myarray<double,10>&variance, bool T = true){
		string filename; cout << "请输入文件名与文件路径(全名):\n"; 
		cin >> filename;//将一个学生vector写到文件里
		cout << "想要便于系统读取的文件还是便于公众展示\n";
		cout << "的文件, 输入y展示，输入其他读取\n";
		string cho; cin >> cho;

		ofstream of(filename);// string name, choice, id, stuclass; double score[9] = { 0 }; int total = 0;
		if (cho == "y") { of << stuwithscore::showhead(false); }
		for (auto& stu : A) { of << stu.putinfointodoc() << endl; }

		if (T && cho == "y")
		{
			of << "平均分" << ','; for (int i = 0; i < 3; i++) { of << "  " << ","; }
			for (auto& i : average) { of << scientific << setprecision(3) << i << ","; }
			of << endl << "方差" << ','; for (int i = 0; i < 3; i++) { of << "  " << ","; }
			for (auto& i : variance) { of << scientific << setprecision(3) << i << ","; }
		}
		of.close(); system("pause");
}
//写入学生信息到文件，T为true时写入表头，否则写入数据；average和variance为平均值和方差
//average_size和variance_size为平均值和方差数组的长度
inline void calculate(myvector<stuwithscore>& temp, myarray<double, 10>& expectation, myarray<double, 10>& variance) {
	size_t n = temp.getsize(); size_t e_size = expectation.getsize(), v_size = variance.getsize();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < e_size; j++) {
			if (j < e_size - 1) { expectation[j] += temp[i].score[j]; }
			else { expectation[j] += temp[i].total; }
		}
	}
	for (auto& i : expectation) { i /= n; }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < v_size; j++) {
			double diff = 0.0;
			if (j < e_size - 1) { diff = temp[i].score[j] - expectation[j]; }
			else { diff = temp[i].total - expectation[static_cast<size_t>(e_size) - 1]; }
			variance[j] += diff * diff;
		}
	}
	for (auto& i : variance)i /= n;cout  << left << "平均分\t\n";
	for (int i = 0; i < 9; i++)cout << subjects[i] << '\t'; cout << "总分\t\n";
	for (auto& i : expectation)cout << i<<'\t';
	cout << endl << left << "方差\t\n";
	for (int i = 0; i < 9; i++)cout << subjects[i] << '\t'; cout << "总分\t\n";
	cout << '\n';
	for (auto& i : variance)cout << i<<'\t';cout << endl;
}
//计算平均值和方差;


inline int choiceensure() {
	string i = "0"; cin >> i;
	while (i != "1" && i != "2" && i != "3") { cout << "输入错误,请重试\n"; cin >> i; }
	return stoi(i);
}
//确定选择；
inline bool compareequal(string finder, stuwithscore& A) {//判断单个stuwithscore是否满足条件
	return (A.name == finder || A.id == finder || A.choice == finder || A.choice + A.stuclass == finder);
}
//判断单个stuwithscore是否满足输入的谓词
inline bool ifgreater(const stuwithscore& A,const stuwithscore& B) {//比较学生分数，降序；
	if (A.total != B.total)  return A.total > B.total;
	size_t n = A.score.getsize();
	for (size_t i = 0; i < n-1; i++) {//先比较总分，再比较各科分数；
		if (A.score[i] != B.score[i])  return A.score[i] > B.score[i];
	}return A.score[n-1] > B.score[n-1];
}
//比较学生分数，降序；
inline void changestuscore(stuwithscore& A, bool t) {
	cout << "请为此学生输入（或修改）分数：\n"; A.print(1);
	if (!t) { A.scoreinputB(); }//有选科版，
	else { A.scoreinputA(); }//无选科版，
	cout << "此学生修改后的成绩为:\n"; A.print(); system("pause"); system("cls");
}
//修改学生分数；










class studentscore {//用于大型考试；
private:
	myhash_map<int, string> grade_map; 
	//myvector<myhash_map<string, stuwithscore>> studatalist;//学生信息列表
	myhash_map<string,myhash_map<string,stuwithscore>> studatalist;
	void getinfofromschool();//从school类中留下的文件中获取学生信息，
	//和school类中的读取师生信息类似；
public:
	studentscore():grade_map({ {1, "高一"}, {2, "高二"}, {3, "高三"} }) {
	getinfofromschool(); randomget(); }//构造函数，从school类中留下的文件中获取学生信息
	void inputscore();//根据查找条件输入学生分数,和school::changestudent类似；
	void getscorefromdoc();//从含学生分数的文件中读取学生信息
	void searchandcalculate(); //根据查找条件查找学生信息并计算平均值和方差
	//查找部分与school::findstudent类似；
	void showallstuscore();//展示所有学生分数
	void randomget() {
		
		for (auto& i : studatalist) {
			for (auto& j : i.second) {
				if (j.second.total == 0) {
					for (int k = 0; k < 3; k++) {
						j.second.score[k] = rand() % 150;
					}
					for (int i = 3; i < 6; i++) {
						j.second.score[i] = rand() % 100;
					}
					j.second.calculatetotal();
				}
			}
		}
	}
};


class scoreanalysis :public school,public studentscore{//根据导入的多张成绩单，对成绩进行分析；S
	myhash_map<string, myvector<stuwithscore>> studatalist;//通过键值对存放（含学生分数的）学生信息
public:
	 void inputscorefromdoc();//从文件中读取（含学生分数的）多张成绩单并分析
	 void getanalysis();//获取分析结果并输出到控制台中
};

