/*ѧУ�����ݽ����� 12�˲μ� ��һ����̭��  �ڶ��־���
ÿ��ѡ�ֱ��10001---10012
������� ÿ������
��һ��Ϊ����С�� ���尴��ѡ�ֽ��г�ǩ˳���ݽ�
ʮ����ί���  ȥ����߷���ͷ�  ��ƽ��ֵ
��̭����������������ѡ��  ǰ������������  
�ڶ��ֱ��� ǰ����ʤ��
ÿ�ֱ���Ҫ��ʾ����ѡ�ֵ���Ϣ*/
#include<iostream>
using namespace std;
#include"speechManager.h"


int main()
{
	SpeechManager sm;

////���Դ���
//	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
//	{
//		cout << "ѡ�ֱ�ţ�" << it->first << "������" << it->second.m_Name 
//			<< "������" << it->second.m_Score[0] << endl;
//	}
//	
	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴��¼
			sm.showRecord();
			break;
		case 3://��ռ�¼
			sm.clearRecord();
			break;
		case 0://�˳�ϵͳ
			sm.exitSystem();
			break;
		default:
			system("cls");//����
			break;
		}

	}

	system("pause");

	return 0;
}