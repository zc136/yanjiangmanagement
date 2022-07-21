/*学校举行演讲比赛 12人参加 第一轮淘汰赛  第二轮决赛
每名选手编号10001---10012
分组比赛 每组两人
第一轮为两个小组 整体按照选手进行抽签顺序演讲
十个评委打分  去除最高分最低分  求平均值
淘汰组内排名最后的三个选手  前三名晋级决赛  
第二轮比赛 前三名胜利
每轮比赛要显示晋级选手的信息*/
#include<iostream>
using namespace std;
#include"speechManager.h"


int main()
{
	SpeechManager sm;

////测试代码
//	for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
//	{
//		cout << "选手编号：" << it->first << "姓名：" << it->second.m_Name 
//			<< "分数：" << it->second.m_Score[0] << endl;
//	}
//	
	int choice = 0;
	while (true)
	{
		sm.show_Menu();
		cout << "请输入你的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看记录
			sm.showRecord();
			break;
		case 3://清空记录
			sm.clearRecord();
			break;
		case 0://退出系统
			sm.exitSystem();
			break;
		default:
			system("cls");//清屏
			break;
		}

	}

	system("pause");

	return 0;
}