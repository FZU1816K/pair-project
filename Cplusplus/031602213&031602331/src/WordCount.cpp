
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
int mode = -1;//用于判断0 TITLE ABSTRACT \N
int groupmode = 0;//用于开启词组统计模式           对应-m
int weightmode = 0;//用于开启权重模式                对应-w
int outctrmode = 10;//用于开启输出个数控制模式     对应-n
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

struct wordtreeNode //字典树结构体
{
	wordtreeNode* next[36];//36指向各子树的指针，包含0-9a-z//追加一个单元用于分割词组
	int end;//标记该结点为结尾的频度
	string ch;//存储该结点为止的字符串
	wordtreeNode() : end(0)//构造函数赋初值
	{
		for (int i = 0; i < 36; i++)
		{
			next[i] = NULL;
		}
	}
};

bool operator < (wordtreeNode a, wordtreeNode b)//运算符重载，用于排序
{
	if (a.end == b.end)
		return a.ch > b.ch;//字典序
	else
		return a.end < b.end;//从大到小
}

priority_queue <wordtreeNode> wordqueue;//优先队列用于计算词频

int charcount(string str, int len)
{
	int CHARnum = 0;
	flag = 0;
	int ibegin = 0;//用于跳判title abstract
	if (mode == 1)
		ibegin = 7;
	if (mode == 2)
		ibegin = 10;
	for (int i = ibegin; i < len; i++)
	{
		if (str[i] == '\t')//tab键 
		{
			CHARnum++;
			continue;
		}
		if (str[i] >= ' '&&str[i] <= '~')//可打印ascii字符 
		{
			CHARnum++;
			if (str[i] != ' ')//只要是非空可视字符就说明不是空白行
				flag = 1;
		}
	}
	return CHARnum + 1;//getline不读回车 
}

int wordcount(string str, int len)
{
	int WORDnum = 0, isword = 0;
	int ibegin = 0;//用于跳判title abstract
	if (mode == 1)
		ibegin = 7;
	if (mode == 2)
		ibegin = 10;
	for (int i = ibegin; i < len; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')//大小写切换
			str[i] += 32;
		if (str[i] >= 'a' && str[i] <= 'z')//如果为小写即如果为字母
		{
			isword++;
		}
		else if (isword < 4)//如果不是字母打头前4个则不形成单词重新计数
		{
			isword = 0;
			continue;
		}
		else if (str[i] >= '0'&&str[i] <= '9')//如果已经是字母则可以接纳数字
		{
			isword++;
		}
		else //说明遇到分隔符开启下一次单词计数，同时进行数组计数
		{
			isword = 0;
			continue;
		}
		if (isword == 4)//说明已经成为单词
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
	int ibegin = 0;//用于跳判title abstract
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
		else if (isword < 4)//不合法 
		{
			isword = 0;
			continue;
		}
		else if (str[i] >= '0'&&str[i] <= '9')//数字 
		{
			isword++;
		}
		else//分隔符 
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
	if (isword >= 4)//特殊处理每行末尾的单词 
		p->end += (weightmode * 9 + 1);
}

void wordfreq(wordtreeNode *root)//词频统计
{
	if (root == NULL)
		return;
	if (root->end != 0)//如果是尾结点压入队列
		wordqueue.push(*root);
	for (int i = 0; i <= 35; i++)//先for后if
	{
		wordfreq(root->next[i]);//递归遍历
	}
}

void wordfreqout(ofstream &fout)//高频词输出
{
	int j = 0;
	wordtreeNode *t = NULL;
	t = new wordtreeNode;
	while (!wordqueue.empty())//pop十次，若不到十次则有几次pop几次
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
	queue<string>preword;//放置缓冲单词beg=queue<int>(); 清空 
	queue<string>temp;
	int ibegin = 0;//用于跳判title abstract
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
			if (tmpstr != ""&&isword == 0)//如果前面是一个单词完全结束 
			{
				isgroup++;
				preword.push(tmpstr);
				tmpstr = "";
			}
			tmpstr += str[i];
			isword++;
		}
		else if (isword < 4)//非法单词或分隔符 
		{
			if (isgroup)//之前有合法单词 
			{
				if (tmpstr != ""&&isword == 0)//在合法单词中可以吞字符 
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
				else//在非法单词中不能吞 
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
		else if (str[i] >= '0'&&str[i] <= '9')//合法单词继续接纳数字 
		{
			tmpstr += str[i];
			isword++;
		}
		else//分隔符 合法单词恰好结束tmpstr接受此分隔符同时开启一次读入
		{
			if (isgroup == (GL - 1))//之前的单词有GL-1个再加上目前这个即可压入树
			{
				temp = preword;
				insertstr = "";
				for (int j = 1; j < GL; j++)//插入长度为GL-1词组 
				{
					insertstr += temp.front();
					temp.pop();
				}
				insertstr += tmpstr;//插入目前为止的最后一个单词
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
	if (isword >= 4)//特殊处理最后一个单词 
	{
		if (isgroup == (GL - 1))//之前的单词有GL-1个再加上目前这个即可压入树
		{
			temp = preword;
			temp.push(tmpstr);
			insertstr = "";
			for (int j = 1; j <= GL; j++)//插入长度为词组 
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


	root = new wordtreeNode;//初始化树 
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
		LINEnum += flag;//有效行 

		if (groupmode == 0)//不开启词组统计模式
			wordinsert(readtxt, readtxt.length(), root);
		else
			groupinsert(readtxt, readtxt.length());
		mode = -1;
	}

	if (readtxt[0] != '\0')//如果最后一行非空要多扣一行 
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

