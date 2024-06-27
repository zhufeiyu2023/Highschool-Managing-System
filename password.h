#pragma once
#include"myvector.h"
#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<utility>
#include<codecvt>
#include<iomanip>
#include<stdexcept>
using namespace std;
class pw 
{public:enum Role { Student, Teacher, Admin };
private:
	using Account = string;
	using Password = string;
	string dataname;
	fstream datafile;
	myhash_map<Account, mypair<Password,Role>> map;
	void Load();
	//�������ݿ�ĺ���
	int getRole(const string& name);
	//��ȡ��ɫ�ĺ���
	void Update();
	//�������ݿ�ĺ���
	void Freeze(const string& name);
	//�����˺ŵĺ���
	bool IsFrozen(const string& name);
	//�ж��˺��Ƿ񱻶���ĺ���
public:
	pw(string dataname1="Password.csv") //���캯�����������뱣��·��
	{
		dataname = dataname1;
		Load();
	}
	void Register();
	//ע�ắ����ǰ���û�ע���˺�����
	int Login();
	//��¼������ǰ���û���½ϵͳ
	void ChangePassword();
	//�޸����뺯��
};
inline void pw::Register()
{
	string zh, mm;
	cout << "�������˺ţ�" << endl;
	cin >> zh;
	while (map.find(zh)) {
		cout << "�����������˺ţ�" << endl;
		cin >> zh;
	}//ϵͳ���Ѿ��и��˺ţ����û����������˺ſ�ʼע��

/*---------------------------------------------------------------
	 �˺Ż�ȡ���ִ������
----------------------------------------------------------------*/

	cout << "���������룺" << endl;
	cin >> mm;
	myhash_map < string, Role > role_map = {{"ѧ��", Student}, {"��ʦ", Teacher}, {"����Ա", Admin}};
	cout << "�������û�����ѧ������ʦ������Ա\n";string Role_str;cin >> Role_str;
	while(!role_map.find(Role_str)){cout<<"�����������û�����ѧ������ʦ������Ա\n";cin>>Role_str;}
	map[zh] = mymake_pair(mm, role_map[Role_str]);//�����˺�--����ӳ��

/*---------------------------------------------------------------
	 �����ȡ���ִ������
----------------------------------------------------------------*/

	Update();

/*---------------------------------------------------------------
	 ���ݱ��沿�ִ������
----------------------------------------------------------------*/
	cout << "ע��ɹ���" << endl;
};

inline int pw::Login()
{   string tempzh, tempmm;//���ڲɼ��û�������˺��������ʱ����
	bool flag1=true,flag2=true;//flag1����˺��Ƿ���ڣ�flag2��������Ƿ����˺Ŷ�Ӧ
	int count = 0;//��������������10�δ����򶳽��˻�
	do {cout << "�˺ţ�";cin >> tempzh;
		cout << "���룺";cin >> tempmm;
		if (!map.find(tempzh)) { flag1 = false; cout << "�˺Ų����ڣ�" << endl; }
		//�˺Ų����ڣ�flag1=false
		else if (IsFrozen(tempzh)) { cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << endl; return -1; }
		//����˺��Ƿ񱻶���
		else if ((map.find(tempzh)->data.second.first) != tempmm) { flag2 = false; count++; cout << "���벻��ȷ��" <<'\t' << endl; }
		//���벻��ȷ��flag2=false,ͬʱ����countֵ���ﵽ���Ƶ�¼����Ч��
		else break;
		//����ѭ���������˺Ŵ��ڲ���������ȷ����ֱ������ѭ��
	} while (((flag1 == false) ||(flag2 == false)) && (count < 10));
	//ѭ������������1.�˺Ų����ڣ�flag1==false��;2.���벻��ȷ��flag2==false��;3.����������С��10			
	if (count >= 10)
	{
		cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << endl;
		Freeze(tempzh);//�����˺�
		return -1;
	}//�������������࣬��½ʧ��
	else 
	{cout << "��½�ɹ������ڽ���ϵͳ..." << endl;//��½�ɹ�
	return getRole(tempzh);}

};

inline void pw::ChangePassword()
{string mm1;string tempzh, tempmm;//���ڲɼ��û�������˺��������ʱ����
	bool flag1 = true, flag2 = true;//flag1����˺��Ƿ���ڣ�flag2��������Ƿ����˺Ŷ�Ӧ
	int count = 0;//��������������10�δ����򶳽��˻�
	do {cout << "�˺ţ�";cin >> tempzh;cout << "���룺";cin >> tempmm;
		if (!map.find(tempzh)) { flag1 = false; cout << "�˺Ų����ڣ�" << endl; }
		//�˺Ų����ڣ�flag1=false
		else if (IsFrozen(tempzh)) { cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << endl; return; }
		//����˺��Ƿ񱻶���
		else if ((map.find(tempzh)->data.second.first) != tempmm) { flag2 = false; count++; cout << "���벻��ȷ��" << '\t' << endl; }
		//���벻��ȷ��flag2=false,ͬʱ����countֵ���ﵽ���Ƶ�¼����Ч��
		else break;
		//����ѭ���������˺Ŵ��ڲ���������ȷ����ֱ������ѭ��
	} while (((flag1 == false) || (flag2 == false)) && (count < 10));
	//ѭ������������1.�˺Ų����ڣ�flag1==false��;2.���벻��ȷ��flag2==false��;3.����������С��10
	if (count >= 10)
	{cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << endl;
		Freeze(tempzh);//�����˺�
	}//�������������࣬��½ʧ��
	else cout << "��½�ɹ������ڽ���ϵͳ..." << endl;//��½�ɹ�
	//���ȵ�½��Ȼ����ܽ��к�������
	cout << "������������" << endl;cin >> mm1;map[tempzh].first = mm1;
	//�����µ������˺�hash_map��ϵ
	Update();
	//�������ݿ�
	cout << "�����޸ĳɹ���" << endl;
};

inline void pw::Load()
{
	datafile.open(dataname, ios::in);
	if (datafile)
	{string zh, mm; int r;
		cout << "���ڼ�������..." << endl; string temp;
		while (getline(datafile, temp))
		{   stringstream ss(temp); getline(ss >> ws, zh, ','); 
			getline(ss >> ws, mm, ','); ss >> r;
			map[zh] = mymake_pair(mm, Role(r));
		}
		datafile.close();
		cout<<"�������ݳɹ���"<<endl;
	}
	else cout << "��������ʧ�ܣ�" << endl;
	datafile.clear(0);

};//�������ݿ�ĺ���

inline void clearfile(string s) 
{
	fstream tempfile;
	tempfile.open(s, ios::trunc, ios::out);
	tempfile.close();

}

inline void copy(const string &s1,const string &s2)//�ļ����ƺ�������s1������s2
{
	string line;
	ifstream ini_file(s1);
	ofstream out_file(s2);
	if (ini_file && out_file) {

		while (getline(ini_file, line)) {
			out_file << line << "\n";
		}
	}
	else cerr << "�ڸ����ļ�ʱ�����˴���" << endl;
	ini_file.close();
	out_file.close();
	
};

inline void pw::Update()
{
	/*˼·��
	1.����Ѵ��ڵĿ����ļ�password_back_up.txt
	2.������ǰpassword.txt�ڵ����ݣ���password_back_up.txt�ļ�����Ϊ����
	3.���password.txt�ļ��ڵ���������
	4.����hash_map������������ݵ�password.txt

	��Ҫ�õ��ĸ���������
	void clearfile(string s)��
	void copy(string s1,string s2);
	*/
	clearfile("password_back_up.csv");
	//����1
	copy(dataname, "password_back_up.csv");
	//����2
	clearfile(dataname);
	//����3
	datafile.open(dataname, ios::out);
	for (const auto& mypair : map) {
		datafile << mypair.first << ',' << mypair.second.first << ',' << mypair.second.second << "\n";
	}
	datafile << endl;
	datafile.close();
	//����4


};


//�������ݿ�ĺ���

inline int pw::getRole(const string& name) {
	if (map.find(name)) return map.find(name)->data.second.second;
	else return -1;
}

inline void pw::Freeze(const string &name)
{
	/*˼·��
	1.�趨txt�ļ� banlist
	2.��name������banlist��
	 */
	datafile.open("banlist.txt", ios::out);
	datafile << name << endl;
	datafile.close();
}

inline bool pw::IsFrozen(const string &name) 
{

	string temp;
	datafile.open("banlist.txt", ios::in);
	if (datafile)
	{
		while (!datafile.eof())
		{
			datafile >> temp;
			if (temp.find(name, 0) != string::npos) return true;
			
		}
		datafile.close(); //�򿪳ɹ����ܹر�
	}

	datafile.clear(0);
	return false;


}


