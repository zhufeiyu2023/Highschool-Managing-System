#include"����ѧУ����ϵͳ.h"
#include"password.h"

typedef void(scoreanalysis::* scorefunc)();
int main() {
	srand(time(0));
	myhash_map<string, scorefunc> funcmap = {
		{"���ѧ����Ϣ",        &scoreanalysis::addstudentsinfo},
		{"��ӽ�ʦ��Ϣ",        &scoreanalysis::addteachersinfo},
		{"�޸�ѧ����Ϣ",        &scoreanalysis::changestudent},
		{"�޸Ľ�ʦ��Ϣ",        &scoreanalysis::changeteacher},
		{"ɾ��ѧ����Ϣ",        &scoreanalysis::deletestudent},
		{"ɾ����ʦ��Ϣ",        &scoreanalysis::deleteteacher},
		{"�鿴ѧ����Ϣ",        &scoreanalysis::findstudent},
		{"�鿴��ʦ��Ϣ",        &scoreanalysis::findteacher},
		{"�鿴�ɼ�",            &scoreanalysis::searchandcalculate},
		{"���ļ�����ɼ�",       &scoreanalysis::getscorefromdoc},
		{"���ļ��������ڷ����ĳɼ�", &scoreanalysis::inputscorefromdoc},
		{"¼��ɼ�",            &scoreanalysis::inputscore},
		{"�鿴����ѧ����Ϣ",     &scoreanalysis::showallstudentinfo},
		{"�鿴����ѧ���ɼ�",     &scoreanalysis::showallstuscore},
		{"�鿴���н�ʦ��Ϣ",     &scoreanalysis::showallteacherinfo},
		{"�Գɼ����з���",      &scoreanalysis::getanalysis}
	};
	myhash_map<char, myhash_map<int, string>> map = {
		{'A',
		{{1,"�鿴ѧ����Ϣ"},{2,"�޸�ѧ����Ϣ"},{3,"�鿴�ɼ�"}}
		},
		{'B',
		{{1,"�鿴��ʦ��Ϣ"},{2,"�޸Ľ�ʦ��Ϣ"},{3,"�鿴�ɼ�"} ,
		{4,"���ļ��������ڷ����ĳɼ�"}, {5,"���ļ�����ɼ�"},{6,"¼��ɼ�"},{7,"�Գɼ����з���"}}
	    },
		{'C',{
		{1,"���ѧ����Ϣ"},{2,"��ӽ�ʦ��Ϣ"},
		{3,"�޸�ѧ����Ϣ"},{4,"�޸Ľ�ʦ��Ϣ"},
		{5,"�鿴�ɼ�"},{6,"ɾ��ѧ����Ϣ"},
		{7,"ɾ����ʦ��Ϣ"},{8,"�鿴ѧ����Ϣ"},
		{9,"�鿴��ʦ��Ϣ"},{10,"���ļ��������ڷ����ĳɼ�"},
		{11,"���ļ�����ɼ�"},{12,"¼��ɼ�"},
		{13,"�鿴����ѧ����Ϣ"},{14,"�鿴����ѧ���ɼ�"},
		{15,"�鿴���н�ʦ��Ϣ"} ,{16,"�Գɼ����з���"}
	    }
	    }
	};
	scoreanalysis A; string identity; int num; pw pwsystem; 
	do{
		cout << "���롰1��ע���˺�����" << '\n';
		cout << "���롰2����¼�˺�" << '\n';
		cout << "���롰3���޸�����" << '\n';
		cin >> num;
		if (num == 1) { pwsystem.Register(); system("pause"); }
		else if (num == 2) { identity = to_string(pwsystem.Login()); system("pause"); break; }
		else if (num == 3) { pwsystem.ChangePassword(); system("pause");}
		else { cerr << "δָ֪��,���������룡\n"; cin.clear(); cin.ignore(0, '\n'); }
		system("cls");
	} while (1);
	int Choice;
    {
		if (identity == to_string(pw::Role::Student)) {
			do {
				system("cls");
				cout << "��ӭ����ѧ��ģʽ��\n";
				cout << "1.�鿴������Ϣ;\n2.�޸ĸ�����Ϣ;\n3.�鿴�ɼ�;\n4.�˳�ѧ��ģʽ\n";
				cin >> Choice; if (Choice == 4)break;
				if (!map['A'].find(Choice))
				{
					cerr << "δָ֪�\n"; cin.clear(); cin.ignore(0, '\n');  continue;
				}
				else (A.*funcmap[map['A'][Choice]])();
			} while (1);
		}
		
		else if (identity == to_string(pw::Role::Teacher)) {
			do
			{
				system("cls");
				cout << "��ӭ�����ʦģʽ��\n";
				cout << "1.�鿴��ʦ������Ϣ;\n2.�޸���ʦ������Ϣ;\n3.�鿴ѧ���ɼ�;\n4.���ļ��������ڷ����ĳɼ�;\n5.���ļ�����ɼ�;\n6.��ѧ��¼��ɼ�;\n7.�Գɼ����з���\n8.�˳���ʦģʽ\n";
				cin >> Choice; if (Choice == 8)break;
				if (!map['B'].find(Choice)) { cerr << "δָ֪�\n"; cin.clear(); cin.ignore(0, '\n'); continue; }
				else (A.*funcmap[map['B'][Choice]])();
			} while (1);
		}
		else if (identity == to_string(pw::Role::Admin) ) {
			//����Ա���,ӵ������Ȩ��
			do
			{system("cls");
				cout << "��ӭ�������Աģʽ��\n";
				cout << "1.¼��ѧ����Ϣ;\n2.¼���ʦ��Ϣ;\n3.�޸�ѧ����Ϣ;\n4.�޸Ľ�ʦ��Ϣ;\n5.�鿴�ɼ�;\n6.ɾ��ѧ����Ϣ;\n7.ɾ����ʦ��Ϣ;\n8.��ѯѧ����Ϣ;\n9.��ѯ��ʦ��Ϣ;\n10.���ļ��������ڷ����ĳɼ�;\n11.���ļ�����ɼ�;\n12.¼��ɼ�;\n13.�鿴����ѧ����Ϣ;\n14.�鿴����ѧ���ɼ�;\n15.�鿴���н�ʦ��Ϣ;\n16.�Գɼ����з���\n17.�˳�����Աģʽ\n" << endl;
				cin >> Choice; if (Choice == 17)break; 
				if (!map['C'].find(Choice)) { cerr << "δָ֪�\n"; cin.clear(); cin.ignore(0, '\n'); continue; }
				else (A.*funcmap[map['C'][Choice]])();
			} while (1);
		}
		
		system("cls");
	} 

	return 0;
}