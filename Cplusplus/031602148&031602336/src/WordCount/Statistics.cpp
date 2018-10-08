#include "stdafx.h"
#include "Statistics.h"
using namespace std;

bool cmp(int a, int b)
{
	return a > b;
}
int Statistics::w_words(ifstream& in)//统计权重单词
{
	string str;
	string temp;
	string te;
	int flag = 0;
	int sum = 0;
	int star = 0;
	int t = 0;
	int a = 0;
	while (getline(in, str))//逐行读取,记录title和abstract
	{
		te = str;
		te.erase(std::remove(te.begin(), te.end(), ' '), te.end());//删除一行中的空格
		te.erase(std::remove(te.begin(), te.end(), '\t'), te.end());//删除一行中的制表符
		if (te.length() == 0)
		{
			t = 0;
			a = 0;
			continue;
		}
		if (str[0] == 'A'&&str[1] == 'b'&&str[2] == 's'&&str[3] == 't'&&str[4] == 'r' &&str[5] == 'a' &&str[6] == 'c' &&str[7] == 't' && (str[8] == ':' || str[8] == '：'))
		{
			t = 0;
			a = 1;
		}
		if (str[0] == 'T'&&str[1] == 'i'&&str[2] == 't'&&str[3] == 'l'&&str[4] == 'e' && (str[5] == ':' || str[5] == '：'))
		{
			t = 1;
			a = 0;
		}
		flag = 0;
		for (unsigned j = 0; j < str.length(); j++)//提取合法单词并统计 
		{
			if (str[j] == 'A'&&str[j + 1] == 'b'&&str[j + 2] == 's'&&str[j + 3] == 't'&&str[j + 4] == 'r' &&str[j + 5] == 'a' &&str[j + 6] == 'c' &&str[j + 7] == 't' && (str[j + 8] == ':' || str[j + 8] == '：'))
			{
				j = 9;
				continue;
			}
			if (str[j] == 'T'&&str[j + 1] == 'i'&&str[j + 2] == 't'&&str[j + 3] == 'l'&&str[j + 4] == 'e' && (str[j + 5] == ':' || str[j + 5] == '：'))
			{
				j = 6;
				continue;
			}
			if (j == str.length() - 1 && ((str[j] >= 'a'&&str[j] <= 'z') || (str[j] >= 'A'&&str[j] <= 'Z')) && flag >= 3)//特殊处理
			{
				flag++;
				if (star >= 1)//修改部分
				{
					if (str[star - 1] >= '0'&&str[star - 1] <= '9')
					{
						flag = 0;
						continue;
					}
				}
				temp = str.substr(star, flag);//截取合法单词
				for (unsigned i = 0; i < temp.length(); i++)//将大写字母转为小写字母 
				{
					if (temp[i] >= 'A'&&temp[i] <= 'Z')
					{
						temp[i] = temp[i] + 32;
					}
				}
				if (t == 1 && a == 0)
				{
					if (trecord.count(temp))
					{
						trecord[temp]++;
					}
					else
					{
						trecord[temp] = 1;
					}
				}
				if (t == 0 && a == 1)
				{
					if (arecord.count(temp))
					{
						arecord[temp]++;
					}
					else
					{
						arecord[temp] = 1;
					}
				}
			}
			if ((str[j] >= 'a'&&str[j] <= 'z') || (str[j] >= 'A'&&str[j] <= 'Z'))
			{
				if (flag == 0)
				{
					star = j;
				}
				flag++;
			}
			else
			{
				if (flag >= 4)
				{
					if (str[j] >= '0'&&str[j] <= '9')
					{
						if (j == str.length() - 1)
						{
							flag++;
						}
						else
						{
							flag++;
							continue;
						}
					}
					if (star >= 1)//修改部分
					{
						if (str[star - 1] >= '0'&&str[star - 1] <= '9')
						{
							flag = 0;
							continue;
						}
					}
					temp = str.substr(star, flag);//截取合法单词
					for (unsigned i = 0; i < temp.length(); i++)//将大写字母转为小写字母 
					{
						if (temp[i] >= 'A'&&temp[i] <= 'Z')
						{
							temp[i] = temp[i] + 32;
						}
					}
					sum++;
					if (t == 1 && a == 0)
					{
						if (trecord.count(temp))
						{
							trecord[temp]++;
						}
						else
						{
							trecord[temp] = 1;
						}
					}
					if (t == 0 && a == 1)
					{
						if (arecord.count(temp))
						{
							arecord[temp]++;
						}
						else
						{
							arecord[temp] = 1;
						}
					}
				}
				flag = 0;
			}
		}
	}
	map<string, int>::iterator tit;
	map<string, int>::iterator ait;
	for (tit = trecord.begin(); tit != trecord.end(); tit++)
	{
		if (word.count((*tit).first))
		{
			word[(*tit).first] = (*tit).second * 10;//不会运行
		}
		else
		{
			word[(*tit).first] = (*tit).second * 10;
		}
	}
	for (ait = arecord.begin(); ait != arecord.end(); ait++)
	{
		if (word.count((*ait).first))
		{
			word[(*ait).first] = word[(*ait).first]+ (*ait).second;
		}
		else
		{
			word[(*ait).first] = (*ait).second * 1;
		}
	}
	in.clear();//指针重新定位至文件头部 
	in.seekg(0, ios::beg);
	return sum;
}
int Statistics::nw_words(ifstream& in)//统计无权重单词
{
	string str;
	string temp;
	string te;
	int flag = 0;
	int sum = 0;
	int star = 0;
	while (getline(in, str))//逐行读取
	{
		te = str;
		//cout << "te" <<te<< endl;
		te.erase(std::remove(te.begin(), te.end(), ' '), te.end());//删除一行中的空格
		te.erase(std::remove(te.begin(), te.end(), '\t'), te.end());//删除一行中的制表符
		if (te.length() == 0)
		{
			continue;
		}
		flag = 0;
		for (unsigned j = 0; j < str.length(); j++)//提取合法单词并统计 
		{
			if (str[j] == 'A'&&str[j + 1] == 'b'&&str[j + 2] == 's'&&str[j + 3] == 't'&&str[j + 4] == 'r' &&str[j + 5] == 'a' &&str[j + 6] == 'c' &&str[j + 7] == 't' && (str[j + 8] == ':' || str[j + 8] == '：'))
			{
				j = 9;
				continue;
			}
			if (str[j] == 'T'&&str[j + 1] == 'i'&&str[j + 2] == 't'&&str[j + 3] == 'l'&&str[j + 4] == 'e' && (str[j + 5] == ':' || str[j + 5] == '：'))
			{
				j = 6;
				continue;
			}
			if (j == str.length() - 1 &&( (str[j] >= 'a'&&str[j] <= 'z')|| (str[j] >= 'A'&&str[j] <= 'Z'))&&flag >= 3)//特殊处理
			{
				flag++;
				if (star >= 1)//修改部分
				{
					if (str[star - 1] >= '0'&&str[star - 1] <= '9')
					{
						flag = 0;
						continue;
					}
				}
				temp = str.substr(star, flag);//截取合法单词 
				for (unsigned i = 0; i < temp.length(); i++)//将大写字母转为小写字母 
				{
					if (temp[i] >= 'A'&&temp[i] <= 'Z')
					{
						temp[i] = temp[i] + 32;
					}
				}
				if (word.count(temp))
				{
					word[temp]++;
					sum++;//修改部分
				}
				else
				{
					word[temp] = 1;
					sum++;
				}
			}
			if ((str[j] >= 'a'&&str[j] <= 'z') || (str[j] >= 'A'&&str[j] <= 'Z'))
			{
				if (flag == 0)
				{
					star = j;
				}
				flag++;
			}
			else
			{
				if (flag >= 4)
				{
					if (str[j] >= '0'&&str[j] <= '9')
					{
						if (j == str.length() - 1)
						{
							flag++;
						}
						else
						{
							flag++;
							continue;
						}
					}
					if (star >= 1)//修改部分
					{
						if (str[star - 1] >= '0'&&str[star - 1] <= '9')
						{
							flag = 0;
							continue;
						}
					}
					temp = str.substr(star, flag);//截取合法单词 
					for (unsigned i = 0; i < temp.length(); i++)//将大写字母转为小写字母 
					{
						if (temp[i] >= 'A'&&temp[i] <= 'Z')
						{
							temp[i] = temp[i] + 32;
						}
					}
					if (word.count(temp))
					{
						word[temp]++;
						sum++;//修改部分
					}
					else
					{
						word[temp] = 1;
						sum++;
					}
				}
				flag = 0;
			}
		}
	}
	cout << "sum=" << sum << endl;
	in.clear();//指针重新定位至文件头部 
	in.seekg(0, ios::beg);
	return sum;
}
int Statistics::w_phrase(ifstream& in, int m)//统计权重词组
{
	string str = "";
	string temp = "";
	string titl = "";
	string abst = "";
	string te = "";
	int flag = 0;
	int sum = 0;
	int start = 0;
	int t = 0;
	int a = 0;
	int turn = 0;
	int mark = 0;
	int star = 0;
	while (getline(in, str))//逐行读取
	{
		te = str;
		te.erase(std::remove(te.begin(), te.end(), ' '), te.end());//删除一行中的空格
		te.erase(std::remove(te.begin(), te.end(), '\t'), te.end());//删除一行中的制表符
		if (te.length() == 0)
		{
			t = 0;
			a = 0;
			//摘要段处理
			flag = 0;
			start = 0;
			mark = 0;
			//cout << "deal abst" << endl;
			//cout << abst << endl;
			for (unsigned j = 0; j < abst.length(); j++)//提取合法词组并统计 
			{
				if (j == abst.length() - 1 && flag >= 4)
				{
					sum++;
				}
				if (abst[j] == 'A'&&abst[j + 1] == 'b'&&abst[j + 2] == 's'&&abst[j + 3] == 't'&&abst[j + 4] == 'r' &&abst[j + 5] == 'a' &&abst[j + 6] == 'c' &&abst[j + 7] == 't' && (abst[j + 8] == ':' || abst[j + 8] == '：'))
				{
					j = 9;
					continue;
				}
				if ((abst[j] >= 'a'&&abst[j] <= 'z') || (abst[j] >= 'A'&&abst[j] <= 'Z'))
				{
					if (flag == 0)
					{
						star = j;
					}
					flag++;
				}
				else
				{
					if (flag >= 4)
					{
						if (abst[j] >= '0'&&abst[j] <= '9')
						{
							if (j == abst.length() - 1)
							{
								flag++;
							}
							else
							{
								flag++;
								continue;
							}
						}
						if (star >= 1)//修改部分
						{
							if (abst[star - 1] >= '0'&&abst[star - 1] <= '9')
							{
								flag = 0;
								continue;
							}
						}
						//temp = abst.substr(star, flag);//截取合法单词
						sum++;
						flag = 0;
						mark = 1;
						for (unsigned i = j; i < abst.length(); i++)
						{
							if (i == abst.length() - 1 && ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z')) && flag >= 3)//特殊处理
							{
								mark++;
								flag = 0;
								//sum++;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star + 1));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (arecord.count(temp))
										{
											arecord[temp]++;
										}
										else
										{
											arecord[temp] = 1;
										}
									}
								}
								mark = 0;
								flag = 0;
								break;
							}
							if ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z'))
							{
								flag++;
							}
							else
							{
								if (flag == 0 && ((abst[i] < '0') || (abst[i] > '9'&&abst[i] < 'A') || (abst[i] > 'Z'&&abst[i] < 'a') && (abst[i] > 'z')))
								{
									continue;
								}
								if (flag < 4)
								{
									for (unsigned k = i; k < abst.length(); k++)
									{
										if ((abst[k] >= 'a'&&abst[k] <= 'z') || (abst[k] >= 'A'&&abst[k] <= 'Z'))
										{
											j = k - 1;
											break;
										}
									}
									break;
								}
								if (flag >= 4 && (abst[i] >= '0'&&abst[i] <= '9'))
								{
									continue;
								}
								mark++;
								flag = 0;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (arecord.count(temp))
										{
											arecord[temp]++;
											mark = 0;
											flag = 0;
										}
										else
										{
											arecord[temp] = 1;
											mark = 0;
											flag = 0;
										}
									}
									mark = 0;
									flag = 0;
									break;
								}
							}
						}
					}
				}
			}
			turn = 0;
			abst = "";
			continue;
		}
		if (str[0] == 'A'&&str[1] == 'b'&&str[2] == 's'&&str[3] == 't'&&str[4] == 'r' &&str[5] == 'a' &&str[6] == 'c' &&str[7] == 't' && (str[8] == ':' || str[8] == '：'))
		{
			t = 0;
			a = 1;
			turn = 1;
			//标题段处理
			flag = 0;
			start = 0;
			mark = 0;
			//cout << "deal titl" << endl;
			//cout << titl << endl;
			for (unsigned j = 0; j < titl.length(); j++)//提取合法词组并统计 
			{
				if (j == titl.length() - 1 && flag >= 4)
				{
					sum++;
				}
				if (titl[j] == 'T'&&titl[j + 1] == 'i'&&titl[j + 2] == 't'&&titl[j + 3] == 'l'&&titl[j + 4] == 'e' && (titl[j + 5] == ':' || titl[j + 5] == '：'))
				{
					j = 6;
					continue;
				}
				if ((titl[j] >= 'a'&&titl[j] <= 'z') || (titl[j] >= 'A'&&titl[j] <= 'Z'))
				{
					if (flag == 0)
					{
						star = j;
					}
					flag++;
				}
				else
				{
					if (flag >= 4)
					{
						if (titl[j] >= '0'&&titl[j] <= '9')
						{
							if (j == titl.length() - 1)
							{
								flag++;
							}
							else
							{
								flag++;
								continue;
							}
						}
						if (star >= 1)//修改部分
						{
							if (titl[star - 1] >= '0'&&titl[star - 1] <= '9')
							{
								flag = 0;
								continue;
							}
						}
						//temp = titl.substr(star, flag);//截取合法单词
						sum++;
						flag = 0;
						mark = 1;
						for (unsigned i = j; i < titl.length(); i++)
						{
							if (i == titl.length() - 1 && ((titl[i] >= 'a'&&titl[i] <= 'z') || (titl[i] >= 'A'&&titl[i] <= 'Z')) && flag >= 3)//特殊处理
							{
								mark++;
								flag = 0;
								//sum++;
								if (mark - m == 0)
								{
									temp = titl.substr(star, (i - star + 1));//截取合法词组
									//cout << "i2   " << i << endl;
									//cout << "star2    " << star << endl;
									//cout << "i2-star2   " << (i - star) << endl;
									//cout << "length" << titl.length() << endl;
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (trecord.count(temp))
										{
											trecord[temp]++;
										}
										else
										{
											trecord[temp] = 1;
										}
									}
								}
								mark = 0;
								flag = 0;
								break;
							}
							if ((titl[i] >= 'a'&&titl[i] <= 'z') || (titl[i] >= 'A'&&titl[i] <= 'Z'))
							{
								flag++;
							}
							else
							{
								if (flag == 0 && ((titl[i] < '0') || (titl[i] > '9'&&titl[i] < 'A') || (titl[i] > 'Z'&&titl[i] < 'a') && (titl[i] > 'z')))
								{
									continue;
								}
								if (flag < 4)
								{
									for (unsigned k = i; k < titl.length(); k++)
									{
										if ((titl[k] >= 'a'&&titl[k] <= 'z') || (titl[k] >= 'A'&&titl[k] <= 'Z'))
										{
											j = k - 1;
											break;
										}
									}
									break;
								}
								if (flag >= 4 && (titl[i] >= '0'&&titl[i] <= '9'))
								{
									continue;
								}
								mark++;
								flag = 0;
								if (mark - m == 0)
								{
									temp = titl.substr(star, (i - star));//截取合法词组
									//cout <<"i"<< i << endl;
									//cout <<"star"<< star << endl;
									//cout << "i-star" <<(i - star) << endl;
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (trecord.count(temp))
										{
											trecord[temp]++;
											mark = 0;
											flag = 0;
										}
										else
										{
											trecord[temp] = 1;
											mark = 0;
											flag = 0;
										}
									}
									mark = 0;
									flag = 0;
									break;
								}
							}
						}
					}
				}
			}
			titl = "";
		}
		if (str[0] == 'T'&&str[1] == 'i'&&str[2] == 't'&&str[3] == 'l'&&str[4] == 'e' && (str[5] == ':' || str[5] == '：'))
		{
			t = 1;
			a = 0;
		}
		if (t == 1 && a == 0)
		{
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
			titl = titl + str;
		}
		if (t == 0 && a == 1)
		{
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
			abst = abst + str;
		}
		if (turn == 1 && abst != "")
		{
			//摘要段处理
			flag = 0;
			start = 0;
			mark = 0;
			//cout << "deal abst" << endl;
			//cout << abst << endl;
			for (unsigned j = 0; j < abst.length(); j++)//提取合法词组并统计 
			{
				if (j == abst.length() - 1 && flag >= 4)
				{
					sum++;
				}
				if (abst[j] == 'A'&&abst[j + 1] == 'b'&&abst[j + 2] == 's'&&abst[j + 3] == 't'&&abst[j + 4] == 'r' &&abst[j + 5] == 'a' &&abst[j + 6] == 'c' &&abst[j + 7] == 't' && (abst[j + 8] == ':' || abst[j + 8] == '：'))
				{
					j = 9;
					continue;
				}
				if ((abst[j] >= 'a'&&abst[j] <= 'z') || (abst[j] >= 'A'&&abst[j] <= 'Z'))
				{
					if (flag == 0)
					{
						star = j;
					}
					flag++;
				}
				else
				{
					if (flag >= 4)
					{
						if (abst[j] >= '0'&&abst[j] <= '9')
						{
							if (j == abst.length() - 1)
							{
								flag++;
							}
							else
							{
								flag++;
								continue;
							}
						}
						if (star >= 1)//修改部分
						{
							if (abst[star - 1] >= '0'&&abst[star - 1] <= '9')
							{
								flag = 0;
								continue;
							}
						}
						//temp = abst.substr(star, flag);//截取合法单词
						flag = 0;
						mark = 1;
						sum++;
						for (unsigned i = j; i < abst.length(); i++)
						{
							if (i == abst.length() - 1 && ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z')) && flag >= 3)//特殊处理
							{
								mark++;
								flag = 0;
								//sum++;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star + 1));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (arecord.count(temp))
										{
											arecord[temp]++;
										}
										else
										{
											arecord[temp] = 1;
										}
									}
								}
								mark = 0;
								flag = 0;
								break;
							}
							if ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z'))
							{
								flag++;
							}
							else
							{
								if (flag == 0 && ((abst[i] < '0') || (abst[i] > '9'&&abst[i] < 'A') || (abst[i] > 'Z'&&abst[i] < 'a') && (abst[i] > 'z')))
								{
									continue;
								}
								if (flag < 4)
								{
									for (unsigned k = i; k < abst.length(); k++)
									{
										if ((abst[k] >= 'a'&&abst[k] <= 'z') || (abst[k] >= 'A'&&abst[k] <= 'Z'))
										{
											j = k - 1;
											break;
										}
									}
									break;
								}
								if (flag >= 4 && (abst[i] >= '0'&&abst[i] <= '9'))
								{
									continue;
								}
								mark++;
								flag = 0;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (arecord.count(temp))
										{
											arecord[temp]++;
											mark = 0;
											flag = 0;
										}
										else
										{
											arecord[temp] = 1;
											mark = 0;
											flag = 0;
										}
									}
									mark = 0;
									flag = 0;
									break;
								}
							}
						}
					}
				}
			}
			turn = 0;
			abst = "";
		}
	}
	map<string, int>::iterator tit;
	map<string, int>::iterator ait;
	for (tit = trecord.begin(); tit != trecord.end(); tit++)
	{
		if (word.count((*tit).first))
		{
			word[(*tit).first] = (*tit).second * 10;//不会运行
		}
		else
		{
			word[(*tit).first] = (*tit).second * 10;
		}
	}
	for (ait = arecord.begin(); ait != arecord.end(); ait++)
	{
		if (word.count((*ait).first))
		{
			word[(*ait).first] = word[(*ait).first] + (*ait).second;
		}
		else
		{
			word[(*ait).first] = (*ait).second * 1;
		}
	}
	in.clear();//指针重新定位至文件头部 
	in.seekg(0, ios::beg);
	return sum;
}
int Statistics::nw_phrase(ifstream& in,int m)//统计无权重词组
{
	string str="";
	string temp="";
	string titl="";
	string abst="";
	string te="";
	int flag = 0;
	int sum = 0;
	int start = 0;
	int t=0;
	int a=0;
	int turn = 0;
	int mark=0;
	int star=0;
	while (getline(in, str))//逐行读取
	{
		te = str;
		te.erase(std::remove(te.begin(), te.end(), ' '), te.end());//删除一行中的空格
		te.erase(std::remove(te.begin(), te.end(), '\t'), te.end());//删除一行中的制表符
		if (te.length() == 0)
		{
			t = 0;
			a = 0;
			//摘要段处理
			flag = 0;
			start = 0;
			mark = 0;
			//cout << "deal abst" << endl;
			//cout << abst << endl;
			for (unsigned j = 0; j < abst.length(); j++)//提取合法词组并统计 
			{
				if (j == abst.length() - 1 && flag >= 4)
				{
					sum++;
				}
				if (abst[j] == 'A'&&abst[j + 1] == 'b'&&abst[j + 2] == 's'&&abst[j + 3] == 't'&&abst[j + 4] == 'r' &&abst[j + 5] == 'a' &&abst[j + 6] == 'c' &&abst[j + 7] == 't' && (abst[j + 8] == ':' || abst[j + 8] == '：'))
				{
					j = 9;
					continue;
				}
				if ((abst[j] >= 'a'&&abst[j] <= 'z') || (abst[j] >= 'A'&&abst[j] <= 'Z'))
				{
					if (flag == 0)
					{
						star = j;
					}
					flag++;
				}
				else
				{
					if (flag >= 4)
					{
						if (abst[j] >= '0'&&abst[j] <= '9')
						{
							if (j == abst.length() - 1)
							{
								flag++;
							}
							else
							{
								flag++;
								continue;
							}
						}
						if (star >= 1)//修改部分
						{
							if (abst[star - 1] >= '0'&&abst[star - 1] <= '9')
							{
								flag = 0;
								continue;
							}
						}
						//temp = abst.substr(star, flag);//截取合法单词
						flag = 0;
						mark = 1;
						sum++;
						for (unsigned i = j; i < abst.length(); i++)
						{
							if (i == abst.length() - 1 && ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z')) && flag >= 3)//特殊处理
							{
								mark++;
								flag = 0;
								//sum++;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star+1));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (word.count(temp))
										{
											word[temp]++;
										}
										else
										{
											word[temp] = 1;
										}
									}
								}
								mark = 0;
								flag = 0;
								break;
							}
							if ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z'))
							{
								flag++;
							}
							else
							{
								if (flag == 0 && ((abst[i] < '0') || (abst[i] > '9'&&abst[i] < 'A') || (abst[i] > 'Z'&&abst[i] < 'a') && (abst[i] > 'z')))
								{
									continue;
								}
								if (flag < 4)
								{
									for (unsigned k = i; k < abst.length(); k++)
									{
										if ((abst[k] >= 'a'&&abst[k] <= 'z') || (abst[k] >= 'A'&&abst[k] <= 'Z'))
										{
											j = k - 1;
											break;
										}
									}
									break;
								}
								if (flag >= 4 && (abst[i] >= '0'&&abst[i] <= '9'))
								{
									continue;
								}
								mark++;
								flag = 0;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (word.count(temp))
										{
											word[temp]++;
											mark = 0;
											flag = 0;
										}
										else
										{
											word[temp] = 1;
											mark = 0;
											flag = 0;
										}
									}
									mark = 0;
									flag = 0;
									break;
								}
							}
						}
					}
				}
			}
			turn = 0;
			abst = "";
			continue;
		}
		if (str[0] == 'A'&&str[1] == 'b'&&str[2] == 's'&&str[3] == 't'&&str[4] == 'r' &&str[5] == 'a' &&str[6] == 'c' &&str[7] == 't' && (str[8] == ':' || str[8] == '：'))
		{
			t = 0;
			a = 1;
			turn = 1;
			//标题段处理
			flag = 0;
			start = 0;
			mark = 0;
			//cout << "deal titl" << endl;
			//cout << titl << endl;
			for (unsigned j = 0; j < titl.length(); j++)//提取合法词组并统计 
			{
				if (j == titl.length() - 1 && flag >= 4)
				{
					sum++;
				}
				if (titl[j] == 'T'&&titl[j + 1] == 'i'&&titl[j + 2] == 't'&&titl[j + 3] == 'l'&&titl[j + 4] == 'e' && (titl[j + 5] == ':' || titl[j + 5] == '：'))
				{
					j = 6;
					continue;
				}
				if ((titl[j] >= 'a'&&titl[j] <= 'z') || (titl[j] >= 'A'&&titl[j] <= 'Z'))
				{
					if (flag == 0)
					{
						star = j;
					}
					flag++;
				}
				else
				{
					if (flag >= 4)
					{
						if (titl[j] >= '0'&&titl[j] <= '9')
						{
							if (j == titl.length() - 1)
							{
								flag++;
							}
							else
							{
								flag++;
								continue;
							}
						}
						if (star >= 1)//修改部分
						{
							if (titl[star - 1] >= '0'&&titl[star - 1] <= '9')
							{
								flag = 0;
								continue;
							}
						}
						//temp = titl.substr(star, flag);//截取合法单词
						flag = 0;
						mark = 1;
						sum++;
						for (unsigned i = j; i < titl.length(); i++)
						{
							if (i == titl.length() - 1 && ((titl[i] >= 'a'&&titl[i] <= 'z') || (titl[i] >= 'A'&&titl[i] <= 'Z')) && flag >= 3)//特殊处理
							{
								mark++;
								flag = 0;
								//sum++;
								if (mark - m == 0)
								{
									temp = titl.substr(star, (i - star+1));//截取合法词组
									//cout << "i2   " << i << endl;
									//cout << "star2    " << star << endl;
									//cout << "i2-star2   " << (i - star) << endl;
									//cout << "length" << titl.length() << endl;
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (word.count(temp))
										{
											word[temp]++;
										}
										else
										{
											word[temp] = 1;
										}
									}
								}
								mark = 0;
								flag = 0;
								break;
							}
							if ((titl[i] >= 'a'&&titl[i] <= 'z') || (titl[i] >= 'A'&&titl[i] <= 'Z'))
							{
								flag++;
							}
							else
							{
								if (flag==0&&((titl[i] < '0') || (titl[i] > '9'&&titl[i] < 'A') || (titl[i] > 'Z'&&titl[i] < 'a') && (titl[i] > 'z')))
								{
									continue;
								}
								if (flag < 4)
								{
									for (unsigned k = i; k < titl.length(); k++)
									{
										if ((titl[k]>='a'&&titl[k]<='z')||(titl[k]>='A'&&titl[k]<='Z'))
										{
											j = k - 1;
											break;
										}
									}
									break;
								}
								if (flag >= 4 && (titl[i] >= '0'&&titl[i] <= '9'))
								{
									continue;
								}
								mark++;
								flag = 0;
								if (mark - m == 0)
								{
									temp = titl.substr(star, (i - star));//截取合法词组
									//cout <<"i"<< i << endl;
									//cout <<"star"<< star << endl;
									//cout << "i-star" <<(i - star) << endl;
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (word.count(temp))
										{
											word[temp]++;
											mark = 0;
											flag = 0;
										}
										else
										{
											word[temp] = 1;
											mark = 0;
											flag = 0;
										}
									}
									mark = 0;
									flag = 0;
									break;
								}
							}
						}
					}
				}
			}
			titl = "";
		}
		if (str[0] == 'T'&&str[1] == 'i'&&str[2] == 't'&&str[3] == 'l'&&str[4] == 'e' && (str[5] == ':' || str[5] == '：'))
		{
			t = 1;
			a = 0;
		}
		if (t == 1 && a == 0)
		{
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
			titl = titl + str;
		}
		if (t == 0 && a == 1)
		{
			str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
			abst = abst + str;
		}
		if (turn == 1 && abst != "")
		{
			//摘要段处理
			flag = 0;
			start = 0;
			mark = 0;
			//cout << "deal abst" << endl;
			//cout << abst << endl;
			for (unsigned j = 0; j < abst.length(); j++)//提取合法词组并统计 
			{
				if (j == abst.length() - 1 && flag >= 4)
				{
					sum++;
				}
				if (abst[j] == 'A'&&abst[j + 1] == 'b'&&abst[j + 2] == 's'&&abst[j + 3] == 't'&&abst[j + 4] == 'r' &&abst[j + 5] == 'a' &&abst[j + 6] == 'c' &&abst[j + 7] == 't' && (abst[j + 8] == ':' || abst[j + 8] == '：'))
				{
					j = 9;
					continue;
				}
				if ((abst[j] >= 'a'&&abst[j] <= 'z') || (abst[j] >= 'A'&&abst[j] <= 'Z'))
				{
					if (flag == 0)
					{
						star = j;
					}
					flag++;
				}
				else
				{
					if (flag >= 4)
					{
						if (abst[j] >= '0'&&abst[j] <= '9')
						{
							if (j == abst.length() - 1)
							{
								flag++;
							}
							else
							{
								flag++;
								continue;
							}
						}
						if (star >= 1)//修改部分
						{
							if (abst[star - 1] >= '0'&&abst[star - 1] <= '9')
							{
								flag = 0;
								continue;
							}
						}
						//temp = abst.substr(star, flag);//截取合法单词
						flag = 0;
						mark = 1;
						sum++;
						for (unsigned i = j; i < abst.length(); i++)
						{
							if (i == abst.length() - 1 && ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z')) && flag >= 3)//特殊处理
							{
								mark++;
								flag = 0;
								//sum++;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star+1));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (word.count(temp))
										{
											word[temp]++;
										}
										else
										{
											word[temp] = 1;
										}
									}
								}
								mark = 0;
								flag = 0;
								break;
							}
							if ((abst[i] >= 'a'&&abst[i] <= 'z') || (abst[i] >= 'A'&&abst[i] <= 'Z'))
							{
								flag++;
							}
							else
							{
								if (flag == 0 && ((abst[i] < '0') || (abst[i] > '9'&&abst[i] < 'A') || (abst[i] > 'Z'&&abst[i] < 'a') && (abst[i] > 'z')))
								{
									continue;
								}
								if (flag < 4)
								{
									for (unsigned k = i; k < abst.length(); k++)
									{
										if ((abst[k] >= 'a'&&abst[k] <= 'z') || (abst[k] >= 'A'&&abst[k] <= 'Z'))
										{
											j = k - 1;
											break;
										}
									}
									break;
								}
								if (flag >= 4 && (abst[i] >= '0'&&abst[i] <= '9'))
								{
									continue;
								}
								mark++;
								flag = 0;
								if (mark - m == 0)
								{
									temp = abst.substr(star, (i - star));//截取合法词组
									{
										for (unsigned g = 0; g < temp.length(); g++)//将大写字母转为小写字母 
										{
											if (temp[g] >= 'A'&&temp[g] <= 'Z')
											{
												temp[g] = temp[g] + 32;
											}
										}
										if (word.count(temp))
										{
											word[temp]++;
											mark = 0;
											flag = 0;
										}
										else
										{
											word[temp] = 1;
											mark = 0;
											flag = 0;
										}
									}
									mark = 0;
									flag = 0;
									break;
								}
							}
						}
					}
				}
			}
			turn = 0;
			abst = "";
		}
	}
	in.clear();//指针重新定位至文件头部 
	in.seekg(0, ios::beg);
	return sum;
}
int Statistics::characters(ifstream& in)//统计字符数
{
	int num = 0;
	int rnum = 0;
	string str;
	string te;
	while (getline(in, str))
	{
		te = str;
		te.erase(std::remove(te.begin(), te.end(), ' '), te.end());//删除一行中的空格
		te.erase(std::remove(te.begin(), te.end(), '\t'), te.end());//删除一行中的制表符
		te.erase(std::remove(te.begin(), te.end(), '0'), te.end());//删除一行中的0
		te.erase(std::remove(te.begin(), te.end(), '1'), te.end());//删除一行中的1
		te.erase(std::remove(te.begin(), te.end(), '2'), te.end());//删除一行中的2
		te.erase(std::remove(te.begin(), te.end(), '3'), te.end());//删除一行中的3
		te.erase(std::remove(te.begin(), te.end(), '4'), te.end());//删除一行中的4
		te.erase(std::remove(te.begin(), te.end(), '5'), te.end());//删除一行中的5
		te.erase(std::remove(te.begin(), te.end(), '6'), te.end());//删除一行中的6
		te.erase(std::remove(te.begin(), te.end(), '7'), te.end());//删除一行中的7
		te.erase(std::remove(te.begin(), te.end(), '8'), te.end());//删除一行中的8
		te.erase(std::remove(te.begin(), te.end(), '9'), te.end());//删除一行中的9
		if (te.length()== 0) //如果删除制表符和空格之后的一行还有其他字符就算有效行
		{
			rnum--;
			continue;
		}
		else
		{
			num = int(str.length())+num;
			if (str[0] == 'A'&&str[1] == 'b'&&str[2] == 's'&&str[3] == 't'&&str[4] == 'r' &&str[5] == 'a' &&str[6] == 'c' &&str[7] == 't' && (str[8] == ':' || str[8] == '：')&&str[9]==' ')
			{
				num = num - 10;
				continue;
			}
			if (str[0] == 'T'&&str[1] == 'i'&&str[2] == 't'&&str[3] == 'l'&&str[4] == 'e' && (str[5] == ':' || str[5] == '：')&&str[6]==' ')
			{
				num = num - 7;
				continue;
			}
			if (str[0] == 'A'&&str[1] == 'b'&&str[2] == 's'&&str[3] == 't'&&str[4] == 'r' &&str[5] == 'a' &&str[6] == 'c' &&str[7] == 't' && (str[8] == ':' || str[8] == '：'))
			{
				num = num - 9;
				continue;
			}
			if (str[0] == 'T'&&str[1] == 'i'&&str[2] == 't'&&str[3] == 'l'&&str[4] == 'e' && (str[5] == ':' || str[5] == '：'))
			{
				num = num - 6;
				continue;
			}
		}
	}
	in.clear();//指针重新定位至文件头部 
	in.seekg(0, ios::beg);
	char ch;
	//cout << "rnum" << rnum << endl;
	while (in.peek() != EOF)//按字符读取
	{
		in.get(ch);
		if(ch=='\n')
			rnum++;
	}
	//cout << "rnum" << rnum << endl;
	in.clear();//指针重新定位至文件头部 
	in.seekg(0, ios::beg);
	return num+rnum;
}
int Statistics::lines(ifstream& in)	//统计有效行数
{
	int line = 0;
	int mark = 0;
	string str;
	while (getline(in, str))
	{
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());//删除一行中的空格
		str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());//删除一行中的制表符
		str.erase(std::remove(str.begin(), str.end(), '0'), str.end());//删除一行中的0
		str.erase(std::remove(str.begin(), str.end(), '1'), str.end());//删除一行中的1
		str.erase(std::remove(str.begin(), str.end(), '2'), str.end());//删除一行中的2
		str.erase(std::remove(str.begin(), str.end(), '3'), str.end());//删除一行中的3
		str.erase(std::remove(str.begin(), str.end(), '4'), str.end());//删除一行中的4
		str.erase(std::remove(str.begin(), str.end(), '5'), str.end());//删除一行中的5
		str.erase(std::remove(str.begin(), str.end(), '6'), str.end());//删除一行中的6
		str.erase(std::remove(str.begin(), str.end(), '7'), str.end());//删除一行中的7
		str.erase(std::remove(str.begin(), str.end(), '8'), str.end());//删除一行中的8
		str.erase(std::remove(str.begin(), str.end(), '9'), str.end());//删除一行中的9
		if (str.length() > 0) //如果删除制表符和空格(+数字)之后的一行数据还有其他字符就算有效行
		{

			line++;
		}
	}
	in.clear();//指针重新定位至文件头部 
	in.seekg(0, ios::beg);
	return line;
}
void Statistics::set(ifstream& in,int w,int m)//调用统计功能
{
	cnum = 0;
	lnum = 0;
	wnum = 0;
	cnum = characters(in);
	lnum = lines(in);
	//cout << "w=" << w << endl;
	//cout << "m=" << m << endl;
	if (w == 0 && m >= 2)
	{		
		//cout << "nwp" << endl;
		wnum=nw_phrase(in,m);
	}
	if (w == 1 && m >= 2)
	{	
		//cout << "wp" << endl;
		wnum=w_phrase(in,m);
	}
	if (w == 0 && m < 2)
	{		
		//cout << "nww" << endl;
		wnum=nw_words(in);
	}
	if (w == 1 && m < 2)
	{	
		//cout << "ww" << endl;
		wnum=w_words(in);
	}
}
void Statistics::display(ofstream& out,int temp)//将结果(词频)输出至指定文档
{
	int n = 0;
	int t;
	int num = 0;
	if (temp < 0)
	{
		n = 10;
	}
	else
	{
		n = temp;
	}
	//cout << "n=" << n << endl;
	out << "characters: " << cnum << endl;
	//cout << "characters: " << cnum << endl;
	out << "words: " << wnum << endl;
	//cout << "words: " << wnum << endl;
	out << "lines: " << lnum << endl;
	//cout << "lines: " << lnum << endl;
	map<string, int>::iterator it;
	for (it = word.begin(); it != word.end(); it++)
	{
		t = (*it).second;
		a.push_back(t);
		num++;
	}
	sort(a.begin(), a.end(), cmp);
	for (int i = 0; i <num && i < n; i++)//修改部分
	{
		t = a[i];
		for (it = word.begin(); it != word.end(); it++)
		{
			if ((*it).second == t)
			{
				out << "<" << (*it).first << ">: " << t << endl;
				//cout << "<" << (*it).first << ">: " << t << endl;
				(*it).second = 0;
				break;
			}
		}
	}
}