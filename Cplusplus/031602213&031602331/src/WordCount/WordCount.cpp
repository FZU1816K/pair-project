#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<queue>
#include<algorithm>
#include<vector>
#include<stdlib.h>
#include<map>
using namespace std;
int flag;//������ 
int mode = -1;//�����ж�0 TITLE ABSTRACT \N
map<string, int>wordgroup;
map<string, int>::iterator iter;


struct Node
{
	string word;
	int count;
	Node() {}
	Node(string _word, int _count) :word(_word), count(_count) {}
};

bool cmp(Node n1, Node n2)
{
	if (n1.count == n2.count)
		return (n1.word.compare(n2.word) <= 0);
	return n1.count > n2.count;
}

void test()
{
	map<string, int>::iterator it;
	vector<Node> vec;
	for (it = wordgroup.begin(); it != wordgroup.end(); it++)
	{
		vec.push_back(Node(it->first, it->second));
	}
	sort(vec.begin(), vec.end(), cmp);

	int length = vec.size();
	length = min(10, length);

	for (int i = 0; i < length; i++)
	{
		cout << vec[i].word << ' ' << vec[i].count << endl;
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
			p->end++;
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
		p->end++;
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
void wordfreqout()//��Ƶ�����
{
	int j = 0;
	wordtreeNode *t = NULL;
	t = new wordtreeNode;
	while (!wordqueue.empty())//popʮ�Σ�������ʮ�����м���pop����
	{
		if (j == 10)
			break;
		*t = wordqueue.top();
		cout << "<" << t->ch << ">: " << t->end << endl;
		wordqueue.pop();
		j++;
	}
}
void groupinsert(string str, int len, int GL)
{
	string insertstr, tmpstr;
	int isgroup = 0, isword = 0, k;
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
int main()
{
	int CHARnum = 0, LINEnum = 0, WORDnum = 0;
	int grouplen;
	string readtxt;
	wordtreeNode *root = NULL;
	ifstream infile("D:/2018software/result.txt");
	cin >> grouplen;//���鳤�� 
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
		wordinsert(readtxt, readtxt.length(), root);
		groupinsert(readtxt, readtxt.length(), grouplen);
		LINEnum += flag;//��Ч�� 
		mode = -1;
	}
	wordfreq(root);
	wordfreqout();
	//groupfreq(Groot);
	//groupfreqout();
	//for (iter=wordgroup.begin(); iter!=wordgroup.end(); iter++)
//	if(iter->second>20)  
		//cout<<iter->first<<' '<<iter->second<<endl;
	if (readtxt[0] != '\0')//������һ�зǿ�Ҫ���һ�� 
		CHARnum--;
	cout << "�ַ�����" << CHARnum << endl << "��Ч������" << LINEnum << endl << "��������" << WORDnum << endl;

	test();

	system("pause");
	return 0;
}
