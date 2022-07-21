#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<functional>
#include<numeric>
#include<ctime>
#include<deque>
#include<fstream>

//�����
//�ṩ�˵��������û�����  ���ݽ��������п���  ���ļ��Ķ�д����
class SpeechManager
{
public:

	SpeechManager();

	~SpeechManager();


	void show_Menu();//�˵�
	void exitSystem();//�˳�ϵͳ
	void initSpeech();//��ʼ������

	void creatSpeaker();//��ʼ������12��ѡ��

	vector<int> v1;//��һ��ѡ�ֱ��

	vector<int> v2;//�ڶ���ѡ�ֱ��
	vector<int> vVictory;//ʤ��ѡ�ֱ��
	map<int, Speaker>m_Speaker;//��ű���Լ�ѡ��
	int m_Index;//����

	//��ʼ���� ������������
	void startSpeech();
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	void showScore();//��ʾ����
	void saveRecord();//�������
	//��ȡ��¼
	void loadRecord();
	bool fileIsEmpty;//�ж��Ƿ�Ϊ��
	map<int, vector<string>>m_Record;
	void showRecord();//��ʾ�����¼
	//��ռ�¼
	void clearRecord();

};