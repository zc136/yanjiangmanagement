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

//设计类
//提供菜单界面与用户交互  对演讲比赛进行控制  与文件的读写交互
class SpeechManager
{
public:

	SpeechManager();

	~SpeechManager();


	void show_Menu();//菜单
	void exitSystem();//退出系统
	void initSpeech();//初始化操作

	void creatSpeaker();//初始化创建12个选手

	vector<int> v1;//第一轮选手编号

	vector<int> v2;//第二轮选手编号
	vector<int> vVictory;//胜出选手编号
	map<int, Speaker>m_Speaker;//存放编号以及选手
	int m_Index;//分数

	//开始比赛 创建比赛流程
	void startSpeech();
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	void showScore();//显示分数
	void saveRecord();//保存分数
	//读取记录
	void loadRecord();
	bool fileIsEmpty;//判断是否为空
	map<int, vector<string>>m_Record;
	void showRecord();//显示往届记录
	//清空记录
	void clearRecord();

};