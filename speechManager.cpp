#include"speechManager.h"





SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
}

SpeechManager::~SpeechManager()
{


}


void SpeechManager::show_Menu()
{
	cout << "***************************************" << endl;
	cout << "***********欢迎参加演讲比赛************" << endl;
	cout << "************1.开始演讲比赛*************" << endl;
	cout << "************2.查看往届记录*************" << endl;
	cout << "************3.清空比赛记录*************" << endl;
	cout << "************0.退出演讲比赛*************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech()//初始化操作
{
	//容器为空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Index = 1;
	this->m_Record.clear();

}

void SpeechManager::creatSpeaker()//初始化创建12个选手
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.m_Score[j] = 0;

		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(1 + 10001, sp));
	}
}
void SpeechManager::startSpeech()//比赛流程
{
	//第一轮比赛
	// 1.抽签
	srand((unsigned int)time(NULL));
	this->speechDraw();

	// 2.比赛
	this->speechContest();
	
	// 3.显示晋级信息
	this->showScore();
	// 第二轮比赛
	// 1.抽签
	this->m_Index++;
	srand((unsigned int)time(NULL));
	this->speechDraw();
	// 2.比赛
	this->speechContest();
	
	// 3.显示结果
	this->showScore();
	
	// 4.保存分数
	this-> saveRecord();//保存分数
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
	cout << "本届比赛结束" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw()
{
	cout << "第<<"  << this->m_Index<< ">>轮比赛选手正在抽签" << endl;
	cout << "-----------------------------" << endl;
	cout << "顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());//洗牌
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;

	}
	else
	{
		random_shuffle(v2.begin(), v2.end());//洗牌
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;

	}
	cout << "------------------------" << endl;
	system("pause");
	cout << endl;
}
//比赛
void  SpeechManager::speechContest()
{
	cout << "第<<" << this->m_Index << ">>轮比赛开始" << endl;
	multimap<double, int, greater<double>>groupScore;//临时变量，保存key的分数 value的选手编号
	int  num = 0;//记录人员数  6个为一组
	vector<int>v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f; 
			cout << score << " ";       //600---1000
			d.push_back(score);
		}
		cout << endl;
		sort(d.begin(), d.end(), greater<double>());//排序  大-小
		d.pop_front();//去掉最高分
		d.pop_back();//去掉最低分
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//每个人的平均分
		cout << "编号：" << *it << "选手：" << this->m_Speaker[*it].m_Name
			 << "平均分：" << avg << endl;
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		//6人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
				it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "姓名: " << this->m_Speaker[it->second].m_Name
					<< "成绩：" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//取前三名.
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
				it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();//小组容器清空
			cout << endl;
		}
	}	
	cout << "----------------第" << this->m_Index << "轮比赛完毕-------------------" << endl;
	system("pause");
}
void SpeechManager::showScore()//显示分数
{
	cout << "-------------第" << this->m_Index << "轮晋级选手信息如下：------------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;

	}
	else
	{
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << *it << "姓名：" << this->m_Speaker[*it].m_Name <<
			"得分：" <<this-> m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();

}
void SpeechManager::saveRecord()//保存分数
{

	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//写文件、
	//将每个人数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," <<this-> m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = false;
}
//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//输入对象 读取数据
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//读取  将上面的单个字符 放回来
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;//查到，位置的变量
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)//没有找到情况
			{
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++; 
	}
	ifs.close();
}
void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届" <<
				"冠军编号" << this->m_Record[i][0] << "得分：" << this->m_Record[i][1] << " "
				"亚军编号" << this->m_Record[i][2] << "得分：" << this->m_Record[i][3] << " "
				"季军编号" << this->m_Record[i][4] << "得分：" << this->m_Record[i][5] << endl;
		}
	}	
	system("pause");
	system("cls");
}
//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.返回" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");

}