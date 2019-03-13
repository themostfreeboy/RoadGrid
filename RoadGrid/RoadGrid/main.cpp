#include <iostream>
#include <string>
//#include <stdbool.h>
#include <vector>
#include <sstream>

using namespace std;

string trim(string s)//ȥ����β����ո�
{
    if(s.empty())
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

vector<string> split(const string s, const string seperator)//����ָ���ָ����ָ��ַ���
{
	vector<string> result;
	int i = 0,k;
	while(i != s.size())
	{
		//�ҵ��ַ������׸������ڷָ�������ĸ
		int flag = 0;
		while(i != s.size() && flag == 0)
		{
			flag = 1;
			for(k=0;k<seperator.size();k++)
			{
				if(s[i] == seperator[k])
				{
					i++;
					flag = 0;
					break;
				}
			}
		}
		//�ҵ���һ���ָ������������ָ���֮����ַ���ȡ��
		flag = 0;
		int j = i;
		while(j != s.size() && flag == 0)
		{
			for(k=0;k<seperator.size();k++)
			{
				if(s[j] == seperator[k])
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0) j++;
		}
		if(i != j)
		{
			result.push_back(s.substr(i,j-i));
			i = j;
		}
	}
	return result;
}

string removeMulSpace(string str)//�ϲ���������Ŀո�Ϊһ���ո�
{
	string result = "";
	int i;
	for(i = 0;i<str.size();i++)
    {
        if(str[i] != ' ')
		{
			result.append(1,str[i]);
		}
        else if(str[i+1] != ' ')
		{
			result.append(1,str[i]);
		}
    }
	return result;
}

class road
{
public:
	road();//���캯��
	~road();//��������
	bool create(string command);//������·
	void printRoad();//��ӡ���
private:
	int m_numOfRow;//����
	int m_numOfCol;//����
	string m_command;//��������
	vector<vector<int>> m_data;//��·����
	void initData();//����������������ʼ����·����
	void changeMode(int cell_1_x,int cell_1_y,int cell_2_x,int cell_2_y);//�޸ĵ�·��ͨ��
	int check();//���������Ч��
};

road::road():m_numOfRow(0),m_numOfCol(0),m_command("")
{
	return;
}

road::~road()
{
	return;
}

void road::initData()//����������������ʼ����·����
{
	int i,j;
	m_data.resize(2*m_numOfRow+1);
	for(i=0;i<2*m_numOfRow+1;i++)
	{
		m_data[i].resize(2*m_numOfCol+1);
	}
	for(i=0;i<2*m_numOfRow+1;i++)
	{
		for(j=0;j<2*m_numOfCol+1;j++)
		{
			if(i%2 && j%2)
			{
				m_data[i][j] = 1;
			}
			else 
			{
				m_data[i][j] = 0;
			}
		}
	}
}

void road::changeMode(int cell_1_x,int cell_1_y,int cell_2_x,int cell_2_y)//�޸ĵ�·��ͨ��
{
	m_data[cell_1_x+cell_2_x+1][cell_1_y+cell_2_y+1] = 1;
}

int road::check()//���������Ч��
{
	int index_line1,index_line2,i,j,cell_1_x,cell_1_y,cell_2_x,cell_2_y;
	index_line1 = m_command.find("\n");
	index_line2 = index_line1 + 1;
	string tempString;
	vector<string> tempVector1,tempVector2,tempVector3;
	stringstream ss;
	if(index_line1==-1)
	{
		return 3;//��ʽ����
	}
	else if(index_line1>0 && m_command[index_line1-1]=='\r')
	{
		index_line1--;
	}
	tempString = m_command.substr(0,index_line1);
	tempString = trim(tempString);
	tempString = removeMulSpace(tempString);
	tempVector1 = split(tempString," ");
	if(tempVector1.size()==2)
	{
		for(i=0;i<tempVector1[0].size();i++)
		{
			if(!isdigit(tempVector1[0][i]))	return 1;//��Ч������
		}
		for(i=0;i<tempVector1[1].size();i++)
		{
			if(!isdigit(tempVector1[1][i]))	return 1;//��Ч������
		}
		ss.clear();
		ss<<tempVector1[0];
		ss>>m_numOfRow;
		ss.clear();
		ss<<tempVector1[1];
		ss>>m_numOfCol;
		if(!((m_numOfRow==0 && m_numOfCol==0) || (m_numOfRow>0 && m_numOfCol>0)))	return 2;//���ֳ���������ķ�Χ
		initData();
	}
	else
	{
		return 3;//��ʽ����
	}
	tempString = m_command.substr(index_line2,m_command.size()-index_line2);
	tempString = trim(tempString);
	tempString = removeMulSpace(tempString);
	tempVector1 = split(tempString,";");
	for(i=0;i<tempVector1.size();i++)
	{
		tempVector2 = split(tempVector1[i]," ");
		if(tempVector2.size()!=2)
		{
			return 3;//��ʽ����
		}
		tempVector3 = split(tempVector2[0],",");
		if(tempVector3.size()!=2)
		{
			return 3;//��ʽ����
		}
		for(j=0;j<tempVector3[0].size();j++)
		{
			if(!isdigit(tempVector3[0][j]))	return 1;//��Ч������
		}
		for(j=0;j<tempVector3[1].size();j++)
		{
			if(!isdigit(tempVector3[1][j]))	return 1;//��Ч������
		}
		ss.clear();
		ss<<tempVector3[0];
		ss>>cell_1_x;
		if(cell_1_x>m_numOfRow || cell_1_x<0)	return 2;//���ֳ���������ķ�Χ
		ss.clear();
		ss<<tempVector3[1];
		ss>>cell_1_y;
		if(cell_1_y>m_numOfCol || cell_1_y<0)	return 2;//���ֳ���������ķ�Χ
		tempVector3 = split(tempVector2[1],",");
		if(tempVector3.size()!=2)
		{
			return 3;//��ʽ����
		}
		for(j=0;j<tempVector3[0].size();j++)
		{
			if(!isdigit(tempVector3[0][j]))	return 1;//��Ч������
		}
		for(j=0;j<tempVector3[1].size();j++)
		{
			if(!isdigit(tempVector3[1][j]))	return 1;//��Ч������
		}
		ss.clear();
		ss<<tempVector3[0];
		ss>>cell_2_x;
		if(cell_2_x>m_numOfRow || cell_2_x<0)	return 2;//���ֳ���������ķ�Χ
		ss.clear();
		ss<<tempVector3[1];
		ss>>cell_2_y;
		if(cell_2_y>m_numOfCol || cell_2_y<0)	return 2;//���ֳ���������ķ�Χ
		if(!((abs(cell_1_x-cell_2_x)==0 && abs(cell_1_y-cell_2_y)==1) || ((abs(cell_1_x-cell_2_x)==1 && abs(cell_1_y-cell_2_y)==0))))	return 4;//��ͨ�Դ���
		changeMode(cell_1_x,cell_1_y,cell_2_x,cell_2_y);
	}
	return 0;
}

bool road::create(string command)//������·
{
	m_command = command;
	m_command = m_command.substr(0,m_command.size());
	m_command = trim(m_command);
	m_command = removeMulSpace(m_command);
	int checkResult = check();
	if(checkResult==1)
	{
		cout<<"Invalid number format."<<endl;
		return false;
	}
	else if(checkResult==2)
	{
		cout<<"Number out of range."<<endl;
		return false;
	}
	else if(checkResult==3)
	{
		cout<<"Incorrect command format."<<endl;
		return false;
	}
	else if(checkResult==4)
	{
		cout<<"Maze format error."<<endl;
		return false;
	}
	return true;
}

void road::printRoad()//��ӡ���
{
	int i,j;
	for(i=0;i<m_data.size();i++)
	{
		if(m_data[i][0]==0)
		{
			cout<<"[W]";
		}
		else if(m_data[i][0]==1)
		{
			cout<<"[R]";
		}
		for(j=1;j<m_data[0].size();j++)
		{
			if(m_data[i][j]==0)
			{
				cout<<" [W]";
			}
			else if(m_data[i][j]==1)
			{
				cout<<" [R]";
			}
		}
		cout<<endl;
	}
	return;
}

void testRoad(string testCommand)//���Ե�����������
{
	road myRoad;
	bool createResult;
	createResult = myRoad.create(testCommand);
	if(createResult)	myRoad.printRoad();
}

void testAllRoad(vector<string>& commands)//�������в�������
{
	int i;
	for(i=0;i<commands.size();i++)
	{
		testRoad(commands[i]);
		cout<<endl;
	}
}

void creatTestCommand(vector<string>& commands)//������������
{
	commands.push_back("3 3\n0,1 0,2;0,0 1,0;0,1 1,1;0,2 1,2;1,0 1,1;1,1 1,2;1,1 2,1;1,2 2,2;2,0 2,1");
	commands.push_back("0 0\n");
	commands.push_back("0 1\n");
	commands.push_back("3 -1\n");
	commands.push_back("3 1.5\n");
	commands.push_back("4 5\n0,1,2,3");
	commands.push_back("4 5\n0,1 2,3");
	commands.push_back("4 5\n0,1 0,2");
	commands.push_back("4 5\n0,1 0,2;0,2 0,3");
	commands.push_back("4 5\n0,1 0,2;0,2 0,2.5");
}

int main()
{
	vector<string> commands;
	creatTestCommand(commands);
	testAllRoad(commands);
	system("pause");
	return 0;
}