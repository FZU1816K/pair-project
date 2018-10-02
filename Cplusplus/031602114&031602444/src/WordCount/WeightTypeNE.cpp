#include"pch.h"
#include"WeightTypeNE.h"
using namespace std;

void WeightTypeNE(char* filem, map<string, int> &m0, int W)
{
	ifstream f;
	f.open(filem, ios::in);
	string s;
	vector<int> ans;				//存分隔符位置
	while (!f.eof())				//一次读取一行
	{
		getline(f, s);
		ans.clear();
		int i;
		int ssize = s.size();
		int start = 0;								//从非title和abstract开始
		int sflag = 0;								//0为abstract，1为title，默认为0
		if (ssize > 7 && ssize < 10)
		{
			string if_Ttl = s.substr(0, 7);
			if (if_Ttl == "Title: ")
			{
				start = 7;
				sflag = 1;
			}
		}
		else if (ssize >= 10)
		{
			string if_Abs = s.substr(0, 10);
			string if_Ttl = s.substr(0, 7);
			if (if_Abs == "Abstract: ")
			{
				start = 10;
			}
			if (if_Ttl == "Title: ")
			{
				start = 7;
				sflag = 1;
			}
		}

		for (i = start; i < ssize; i++)					//从非title和start开始存分隔符
		{
			if (s[i] >= 65 && s[i] <= 90)
			{
				s[i] += 32;
			}
			if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || (s[i] > 90 && s[i] < 97) || s[i]>122)
			{
				ans.push_back(i);
			}
		}

		int sss = ans.size();
		if (sss == 0)				//如果分割符数目等于0，就是只有一个字符串
		{
			//如果从该符号起四个字符都是字母
			if ((s[0] >= 97 && s[0] <= 122) && (s[1] >= 97 && s[1] <= 122) && (s[2] >= 97 && s[2] <= 122) && (s[3] >= 97 && s[3] <= 122))
			{
				if (start == 0)
				{
					if (sflag == 1 && W == 1)			//为title且权值为10
					{
						m0[s] += 10;
					}
					else m0[s]++;
	
				}
			}
			continue;
		}

		//否则就有一个以上的分隔符
		//先判断第一个，因为第一个没有分隔符做开头标记
		if ((s[start] >= 97 && s[start] <= 122) && (s[start + 1] >= 97 && s[start + 1] <= 122) && (s[start + 2] >= 97
			&& s[start + 2] <= 122) && (s[start + 3] >= 97 && s[start + 3] <= 122))
		{
			string temp(s.substr(start, ans[0]));			//满足前四个字符是字母，截取
			if (sflag == 1 && W == 1)
			{
				m0[temp] += 10;
			}
			else m0[temp]++;
		}

		for (i = 0; i < sss; i++)
		{
			//满足分隔符后四个字符是字母
			if ((s[ans[i] + 1] >= 97 && s[ans[i] + 1] <= 122) && (s[ans[i] + 2] >= 97 && s[ans[i] + 2] <= 122) &&
				(s[ans[i] + 3] >= 97 && s[ans[i] + 3] <= 122) && (s[ans[i] + 4] >= 97 && s[ans[i] + 4] <= 122))
			{
				string a;
				if (i == sss - 1)
				{
					string temp(s.substr(ans[i] + 1, s.size() - ans[i] - 1));
					a = temp;
				}
				else
				{
					string temp(s.substr(ans[i] + 1, ans[i + 1] - ans[i] - 1));
					a = temp;
				}
				if (sflag == 1 && W == 1)
				{
					m0[a] += 10;
				}
				else m0[a]++;
			}
		}

	}
}