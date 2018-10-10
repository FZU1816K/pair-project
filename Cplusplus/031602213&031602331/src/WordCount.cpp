
#include "pch.h"
#include <iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<queue>
#include<algorithm>
#include<vector>
#include<stdlib.h>
#include<map>
#include<assert.h>

using namespace std;
int flag;
int mode = -1;//�����ж�0 TITLE ABSTRACT \N
int groupmode = 0;//���ڿ�������ͳ��ģʽ           ��Ӧ-m
int weightmode = 0;//���ڿ���Ȩ��ģʽ                ��Ӧ-w
int outctrmode = 10;//���ڿ��������������ģʽ     ��Ӧ-n
int grouplen;
string file_Inname;
string file_Outname;
map<string, int>wordgroup;
map<string, int>::iterator iter;

struct WGnode
{
	string group;
	int count;
	WGnode() {}
	WGnode(string _group, int _count) :group(_group), count(_count) {}
};

bool cmp(WGnode a, WGnode b)
{
	if (a.count == b.count)
		return (a.group.compare(b.group) <= 0);
	return a.count > b.count;
}

void  groupFreqout(ofstream &fout)
{
	map<string, int>::iterator it;
	vector<WGnode> vec;
	for (it = wordgroup.begin(); it != wordgroup.end(); it++)
	{
		vec.push_back(WGnode(it->first, it->second));
	}
	sort(vec.begin(), vec.end(), cmp);

	int length = vec.size();
	length = min(outctrmode, length);

	for (int i = 0; i < length; i++)
	{
		fout << "<" << vec[i].group << ">: " << vec[i].count << endl;
		//cout << "<" << vec[i].group << ">: " << vec[i].count << endl;
	}
}

struct wordtreeNode //�ֵ����ṹ��
{
	wordtreeNode* next[36];//36ָ���������ָ�룬����0-9a-z//׷��һ����Ԫ���ڷָ����
	int end;//��Ǹý��Ϊ��β��Ƶ��
	string ch;//�洢�ý��Ϊֹ���ַ���
	wordtreeNode() : end(0)//���캯������ֵ
	{
		for (int i = 0; i < 36; i++)
		{
			next[i] = NULL;
		}
	}
};

bool operator < (wordtreeNode a, wordtreeNode b)//��������أ���������
{
	if (a.end == b.end)
		return a.ch > b.ch;//�ֵ���
	else
		return a.end < b.end;//�Ӵ�С
}

priority_queue <wordtreeNode> wordqueue;//���ȶ������ڼ����Ƶ

int charcount(string str, int len)
{
	int CHARnum = 0;
	flag = 0;
	int ibegin = 0;//��������title abstract
	if (mode == 1)
		ibegin = 7;
	if (mode == 2)
		ibegin = 10;
	for (int i = ibegin; i < len; i++)
	{
		if (str[i] == '\t')//tab�� 
		{
			CHARnum++;
			continue;
		}
		if (str[i] >= ' '&&str[i] <= '~')//�ɴ�ӡascii�ַ� 
		{
			CHARnum++;
			if (str[i] != ' ')//ֻҪ�Ƿǿտ����ַ���˵�����ǿհ���
				flag = 1;
		}
	}
	return CHARnum + 1;//getline�����س� 
}

int wordcount(string str, int len)
{
	int WORDnum = 0, isword = 0;
	int ibegin = 0;//��������title abstract
	if (mode == 1)
		ibegin = 7;
	if (mode == 2)
		ibegin = 10;
	for (int i = ibegin; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')//��Сд�л�
			str[i] += 32;
		if (str[i] >= 'a' && str[i] <= 'z')//���ΪСд�����Ϊ��ĸ
		{
			isword++;
		}
		else if (isword < 4)//���������ĸ��ͷǰ4�����γɵ������¼���
		{
			isword = 0;
			continue;
		}
		else if (str[i] >= '0'&&str[i] <= '9')//����Ѿ�����ĸ����Խ�������
		{
			isword++;
		}
		else //˵�������ָ���������һ�ε��ʼ�����ͬʱ�����������
		{
			isword = 0;
			continue;
		}
		if (isword == 4)//˵���Ѿ���Ϊ����
		{
			WORDnum++;
		}
	}
	return WORDnum;
}

void wordinsert(string str, int len, wordtreeNode *root)
{
	int isword = 0, key = 0;
	string lastch = "";
	wordtreeNode *p;
	p = new wordtreeNode;
	p = root;
	int ibegin = 0;//��������title abstract
	if (mode == 1)
		ibegin = 7;
	if (mode == 2)
		ibegin = 10;
	for (int i = ibegin; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			isword++;
		}
		else if (isword < 4)//���Ϸ� 
		{
			isword = 0;
			continue;
		}
		else if (str[i] >= '0'&&str[i] <= '9')//���� 
		{
			isword++;
		}
		else//�ָ��� 
		{
			p->end += (weightmode * 9 + 1);
			p = root;
			isword = 0;
			continue;
		}
		if (isword == 4)
		{
			lastch = "";
			for (int j = i - 3; j <= i; j++)
			{
				if (str[j] <= '9'&&str[j] >= '0')
					key = str[j] - '0';
				else
					key = str[j] - 'a' + 10;
				if (p->next[key] == NULL)
				{
					p->next[key] = new wordtreeNode;
				}
				p = p->next[key];
				p->ch = lastch + str[j];
				lastch = p->ch;
			}
			continue;
		}
		if (isword < 4)
			continue;
		if (str[i] <= '9'&&str[i] >= '0')
			key = str[i] - '0';
		else
			key = str[i] - 'a' + 10;
		if (p->next[key] == NULL)
		{
			p->next[key] = new wordtreeNode;
		}
		p = p->next[key];
		p->ch = lastch + str[i];
		lastch = p->ch;
	}
	if (isword >= 4)//���⴦��ÿ��ĩβ�ĵ��� 
		p->end += (weightmode * 9 + 1);
}

void wordfreq(wordtreeNode *root)//��Ƶͳ��
{
	if (root == NULL)
		return;
	if (root->end != 0)//�����β���ѹ�����
		wordqueue.push(*root);
	for (int i = 0; i <= 35; i++)//��for��if
	{
		wordfreq(root->next[i]);//�ݹ����
	}
}

void wordfreqout(ofstream &fout)//��Ƶ�����
{
	int j = 0;
	wordtreeNode *t = NULL;
	t = new wordtreeNode;
	while (!wordqueue.empty())//popʮ�Σ�������ʮ�����м���pop����
	{
		if (j == outctrmode)
			break;
		*t = wordqueue.top();
		fout << "<" << t->ch << ">: " << t->end << endl;
		cout << "<" << t->ch << ">: " << t->end << endl;
		wordqueue.pop();
		j++;
	}
}

void groupinsert(string str, int len)
{
	int GL = groupmode;
	string insertstr, tmpstr;
	int isgroup = 0, isword = 0;
	queue<string>preword;//���û��嵥��beg=queue<int>(); ��� 
	queue<string>temp;
	int ibegin = 0;//��������title abstract
	if (mode == 1)
		ibegin = 7;
	if (mode == 2)
		ibegin = 10;
	for (int i = ibegin; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;

		if (str[i] >= 'a'&&str[i] <= 'z')
		{
			if (tmpstr != ""&&isword == 0)//���ǰ����һ��������ȫ���� 
			{
				isgroup++;
				preword.push(tmpstr);
				tmpstr = "";
			}
			tmpstr += str[i];
			isword++;
		}
		else if (isword < 4)//�Ƿ����ʻ�ָ��� 
		{
			if (isgroup)//֮ǰ�кϷ����� 
			{
				if (tmpstr != ""&&isword == 0)//�ںϷ������п������ַ� 
				{
					if (str[i] >= '0'&&str[i] <= '9')
					{
						tmpstr = "";
						isgroup = 0;
						preword = queue<string>();
					}
					else
						tmpstr += str[i];
				}
				else//�ڷǷ������в����� 
				{
					tmpstr = "";
					isgroup = 0;
					preword = queue<string>();
				}
			}
			else
				tmpstr = "";
			isword = 0;
		}
		else if (str[i] >= '0'&&str[i] <= '9')//�Ϸ����ʼ����������� 
		{
			tmpstr += str[i];
			isword++;
		}
		else//�ָ��� �Ϸ�����ǡ�ý���tmpstr���ܴ˷ָ���ͬʱ����һ�ζ���
		{
			if (isgroup == (GL - 1))//֮ǰ�ĵ�����GL-1���ټ���Ŀǰ�������ѹ����
			{
				temp = preword;
				insertstr = "";
				for (int j = 1; j < GL; j++)//���볤��ΪGL-1���� 
				{
					insertstr += temp.front();
					temp.pop();
				}
				insertstr += tmpstr;//����ĿǰΪֹ�����һ������
				iter = wordgroup.find(insertstr);
				if (iter != wordgroup.end())
					//iter->second++;
					wordgroup[insertstr]++;
				else
					wordgroup.insert(map<string, int>::value_type(insertstr, 1));
				isgroup--;
				preword.pop();
			}
			tmpstr += str[i];
			isword = 0;
		}
	}
	if (isword >= 4)//���⴦�����һ������ 
	{
		if (isgroup == (GL - 1))//֮ǰ�ĵ�����GL-1���ټ���Ŀǰ�������ѹ����
		{
			temp = preword;
			temp.push(tmpstr);
			insertstr = "";
			for (int j = 1; j <= GL; j++)//���볤��Ϊ���� 
			{
				insertstr += temp.front();
				temp.pop();
			}
			iter = wordgroup.find(insertstr);
			if (iter != wordgroup.end())
				//iter->second++;  
				wordgroup[insertstr]++;
			else
				wordgroup.insert(map<string, int>::value_type(insertstr, 1));
		}
	}
}

int main(int argc, char * argv[])
{
	int CHARnum = 0, LINEnum = 0, WORDnum = 0;
	//int grouplen;
	string readtxt;
	wordtreeNode *root = NULL;



	int i = 1;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			if (argv[i + 1] == NULL)
			{
				printf("error: no input file name!\n");
				return -1;
			}

			file_Inname = argv[i + 1];
			i += 2;
			//cout << file_Inname << endl;
		}

		else  if (strcmp(argv[i], "-o") == 0)
		{
			if (argv[i + 1] == NULL)
			{
				printf("error: no output file name!\n");
				return -1;
			}

			file_Outname = argv[i + 1];
			//cout << file_Outname << endl;
			i += 2;
		}

		else if (strcmp(argv[i], "-w") == 0)
		{
			if (argv[i + 1] == NULL)
			{
				return -1;
			}

			int num = atoi(argv[i + 1]);
			weightmode = num;
			//cout << "weightmode: " << weightmode << endl;
			i += 2;
		}

		else if (strcmp(argv[i], "-m")==0)
		{
			if (argv[i + 1] == NULL)
			{
				printf("error: -m must >= 0!\n");
				return -1;
			}

			groupmode = atoi(argv[i + 1]);
			if (groupmode < 2) {
				printf("error: -m must >= 2!\n");
				return -1;
			}
			i += 2;
		}

		else if (strcmp(argv[i], "-n")==0)
		{
			if (argv[i + 1] == NULL)
			{
				printf("error: -n must >= 0!\n");
				return -1;
			}

			outctrmode = atoi(argv[i + 1]);
			if (outctrmode == -1)
			{
				printf("error: -n must >= 0!\n");
				return -1;
			}
			i += 2;
			cout << "-n:" << outctrmode << endl;
		}

	}

	//cout << " *** " << file_Inname << endl;
	ifstream infile(file_Inname);

	//assert(infile.is_open());
	ofstream outfile(file_Outname);


	root = new wordtreeNode;//��ʼ���� 
	while (getline(infile, readtxt))
	{
		if (readtxt[0] >= '0'&&readtxt[0] <= '9')
			continue;
		if (readtxt[0] == 'T')
			mode = 1;
		if (readtxt[0] == 'A')
			mode = 2;
		if (readtxt[0] == '\0')
			continue;
		CHARnum += charcount(readtxt, readtxt.length());
		WORDnum += wordcount(readtxt, readtxt.length());
		LINEnum += flag;//��Ч�� 

		if (groupmode == 0)//����������ͳ��ģʽ
			wordinsert(readtxt, readtxt.length(), root);
		else
			groupinsert(readtxt, readtxt.length());
		mode = -1;
	}

	if (readtxt[0] != '\0')//������һ�зǿ�Ҫ���һ�� 
		CHARnum--;

	outfile << "characters: " << CHARnum << endl << "words: " << WORDnum << endl << "lines: " << LINEnum << endl;
	//cout << "characters1: " << CHARnum << endl << "words: " << WORDnum << endl << "lines: " << LINEnum << endl;
	if (groupmode == 0)
	{
		wordfreq(root);
		wordfreqout(outfile);
	}
	else
		groupFreqout(outfile);
	outfile.close();
	system("pause");
	return 0;

}

