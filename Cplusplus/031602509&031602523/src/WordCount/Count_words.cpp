#include "pch.h"
#include "work_2.h"
bool isdivide(char d)
{
	if ((d <= '9'&&d >= '0') || (d <= 'Z'&&d >= 'A') || (d <= 'z'&&d >= 'a'))
		return 0;
	else
		return 1;
}
bool isletter(char d)
{
	if ((d <= 'Z'&&d >= 'A') || (d <= 'z'&&d >= 'a'))
		return 1;
	else
		return 0;
}

int C_words(istream &fl, File &fn, Words &wn, Wordnode **l, vector <string> &str_lines)
{
	int len = fn.count_m;
	int fflag = fn.m_flag;
	unsigned int i = 0, j = 0, k = 0;		//���ϴ���string.size()����
	int count_lines = 0, count_words = 0;
	vector <string> wordbuf;
	int istitle = -1;
	int err = 0;
	int cnt = 0;
	int flag = 0;
	string temp_line = "", temp_word = "", temp_comb = "";
	char temp_chr;
	for (i = 0; i < str_lines.size(); i++)	//��Ч�����ж�
	{
		temp_line = str_lines[i];
		int flag_line = 0;
		for (j = 0; j < temp_line.size(); j++)
		{
			if (temp_line[j] >= 33)
			{
				flag_line = 1; break;		//������Ч�ַ�
			}
		}
		if (0 == flag_line)
		{
			continue;				//δ������Ч�ַ�	
		}
		count_lines++;
		k = 0;
		while (k < temp_line.size())	//���е����ж�
		{
			//cout<<temp_line.size();
			temp_chr = temp_line[k];
			if (temp_chr <= '9'&&temp_chr >= '0')
			{
				k++;								//���ֿ�ͷ�ж�
				while (k <= temp_line.size() - 1 && ((temp_line[k] <= '9'&&temp_line[k] >= '0') || (temp_line[k] <= 'z'&&temp_line[k] >= 'a')))
				{
					k++;
				}
				wordbuf.clear();
			}
			else if (temp_chr <= 'z' && temp_chr >= 'a')
			{
				temp_word = "";
				temp_word += temp_chr;		//�ַ�����
				//cout<<temp_word<<endl;
				k += 1;
				if (temp_line.size() - 2 > k)	//�ж�����λ���Ƿ�װ��һ������
				{
					while (k < temp_line.size() && ((temp_line[k] <= 'z' && temp_line[k] >= 'a') || (temp_line[k] <= '9' && temp_line[k] >= '0')))
					{
						temp_word += temp_line[k];
						//cout << temp_word << endl;
						k += 1;
					}
					//wordbuf.clear();
				}
				if (3 < temp_word.size() && (temp_word[0] <= 'z'&&temp_word[0] >= 'a') && (temp_word[1] <= 'z'&&temp_word[1] >= 'a') && (temp_word[2] <= 'z'&&temp_word[2] >= 'a') && (temp_word[3] <= 'z'&&temp_word[3] >= 'a'))
				{
					count_words++;
					if (temp_word == "title"&&temp_line[k] == ':'&&k <= temp_line.size())
					{
						fn.count_chars = fn.count_chars - 7;
						count_words--;
						istitle = 1;
						wordbuf.clear();
						k += 2;
						continue;
					}
					if (temp_word == "abstract"&&temp_line[k] == ':'&&k <= temp_line.size())
					{
						fn.count_chars = fn.count_chars - 10;
						count_words--;
						istitle = 0;
						wordbuf.clear();
						k += 2;
						continue;
					}
					//��⵽�Ϸ�����
					if (fflag == 1)						//ֻͳ�ƴ���
					{
						int thischar = k;
						while (isdivide(temp_line[thischar]) && thischar < temp_line.size())
						{
							temp_word = temp_word + temp_line[thischar];
							thischar++;
						}
						wordbuf.push_back(temp_word);
						//cout << wordbuf.size() << endl;
						if (wordbuf.size() == len)
						{
							for (int i = 0; i < len; i++)
							{
								temp_comb += wordbuf[i];
							}
							wordbuf.erase(wordbuf.begin());
							//cout << wordbuf.size() << endl;
							//cout << temp_comb << endl;
							while (isdivide(temp_comb[temp_comb.length() - 1]))
							{
								temp_comb = temp_comb.substr(0, temp_comb.length() - 1);
							}
							//cout << temp_comb << endl;
							if (istitle == 1 && fn.weight == 1)
							{
								hash_insert(l, temp_comb,1);
							}
							else
							{
								hash_insert(l, temp_comb,0);
							}
							temp_comb = "";
						}
					}
					else				//ֻͳ�Ƶ���
					{
						if (istitle == 1 && fn.weight == 1)
						{
							hash_insert(l, temp_word,1);
						}
						else
						{
							hash_insert(l, temp_word,0);
							//cout << temp_word << endl;
						}
						temp_word = "";
					}
				}
				else
				{
					wordbuf.clear();
				}
			}
			else
				k += 1;	//�����ַ������뵥��
		}				//һ�н���
	}

	fn.count_lines = count_lines;
	return count_words;

}
