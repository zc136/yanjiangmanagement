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
	cout << "***********��ӭ�μ��ݽ�����************" << endl;
	cout << "************1.��ʼ�ݽ�����*************" << endl;
	cout << "************2.�鿴�����¼*************" << endl;
	cout << "************3.��ձ�����¼*************" << endl;
	cout << "************0.�˳��ݽ�����*************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech()//��ʼ������
{
	//����Ϊ��
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Index = 1;
	this->m_Record.clear();

}

void SpeechManager::creatSpeaker()//��ʼ������12��ѡ��
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
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
void SpeechManager::startSpeech()//��������
{
	//��һ�ֱ���
	// 1.��ǩ
	srand((unsigned int)time(NULL));
	this->speechDraw();

	// 2.����
	this->speechContest();
	
	// 3.��ʾ������Ϣ
	this->showScore();
	// �ڶ��ֱ���
	// 1.��ǩ
	this->m_Index++;
	srand((unsigned int)time(NULL));
	this->speechDraw();
	// 2.����
	this->speechContest();
	
	// 3.��ʾ���
	this->showScore();
	
	// 4.�������
	this-> saveRecord();//�������
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
	cout << "�����������" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw()
{
	cout << "��<<"  << this->m_Index<< ">>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-----------------------------" << endl;
	cout << "˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());//ϴ��
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;

	}
	else
	{
		random_shuffle(v2.begin(), v2.end());//ϴ��
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
//����
void  SpeechManager::speechContest()
{
	cout << "��<<" << this->m_Index << ">>�ֱ�����ʼ" << endl;
	multimap<double, int, greater<double>>groupScore;//��ʱ����������key�ķ��� value��ѡ�ֱ��
	int  num = 0;//��¼��Ա��  6��Ϊһ��
	vector<int>v_Src;
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600)/10.f; 
			cout << score << " ";       //600---1000
			d.push_back(score);
		}
		cout << endl;
		sort(d.begin(), d.end(), greater<double>());//����  ��-С
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//ÿ���˵�ƽ����
		cout << "��ţ�" << *it << "ѡ�֣�" << this->m_Speaker[*it].m_Name
			 << "ƽ���֣�" << avg << endl;
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		//6��һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin();
				it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "����: " << this->m_Speaker[it->second].m_Name
					<< "�ɼ���" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			//ȡǰ����.
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
			groupScore.clear();//С���������
			cout << endl;
		}
	}	
	cout << "----------------��" << this->m_Index << "�ֱ������-------------------" << endl;
	system("pause");
}
void SpeechManager::showScore()//��ʾ����
{
	cout << "-------------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�------------" << endl;
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
		cout << "ѡ�ֱ�ţ�" << *it << "������" << this->m_Speaker[*it].m_Name <<
			"�÷֣�" <<this-> m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();

}
void SpeechManager::saveRecord()//�������
{

	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//д�ļ���
	//��ÿ��������д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," <<this-> m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	this->fileIsEmpty = false;
}
//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//������� ��ȡ����
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//��ȡ  ������ĵ����ַ� �Ż���
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;
		int pos = -1;//�鵽��λ�õı���
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)//û���ҵ����
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
		cout << "�ļ������ڣ����¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "��" <<
				"�ھ����" << this->m_Record[i][0] << "�÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ����" << this->m_Record[i][2] << "�÷֣�" << this->m_Record[i][3] << " "
				"�������" << this->m_Record[i][4] << "�÷֣�" << this->m_Record[i][5] << endl;
		}
	}	
	system("pause");
	system("cls");
}
//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");

}