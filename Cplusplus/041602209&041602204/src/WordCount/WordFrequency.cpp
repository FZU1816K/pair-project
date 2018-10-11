#include "WordFrequency.h"


int WordFrequency(string filename_in,string filename_out,int judgevalue,int jj)
{	  
	                                                                                //int judgevalue = 0;
	                                                                               //cin >> judgevalue;                                                 ////111111
	                                                                               //int paperCount = 4;//论文数                                               //1111

	int cnt1 = 0, n = 0;
	string temp11;

	

	int flag = 0;
	                                                                             //fstream fin("result.txt", ios::in);//输入文件 
	                                                                             // ofstream fout("result2.txt", ios::app);//输出文件 
	fstream fin(filename_in, ios::in);//输入文件
	ofstream fout(filename_out, ios::app);//输出文件 
	if (!fin) {
		cout << "Can't open file" << endl;
		return -1;
	}
	map<string, int> title;
	int wordvalue = 0;
	char temp;
	string temp1;
	map<string, int>::iterator iter;
	for (; ; )
	{
		
		flag = 0;
		while (temp = (fin.get() != '\n'))
		{
			if (temp == EOF)flag = -1;
		}//读完论文标号行 
		if (flag == -1)break;
		while (fin.get() != ':');// 读完Title：                 //妙啊！！！！！！！
		while ((temp = fin.get()) != '\n')//读完Title：以后的内容 
		{
			if ('A' <= temp && temp <= 'Z')
				temp = temp + 32;                  //转换成小写；
			switch (wordvalue) {
			case 0: {
				if (temp >= 'a'&&temp <= 'z') {
					temp1 = temp1 + temp;
					wordvalue = 1;
				}
				break;
			}
			case 1: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordvalue = 2;
				}
				else { wordvalue = 0; temp1 = ""; }
				break;
			}
			case 2: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordvalue = 3;
				}
				else { wordvalue = 0; temp1 = ""; }
				break;
			}
			case 3: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordvalue = 4;
				}
				else { wordvalue = 0; temp1 = ""; }
				break;
			}
			case 4: {
				if (temp >= 'a'&&temp <= 'z' || (temp >= '0'&&temp <= '9')) { temp1 = temp1 + temp; }
				else {
					title[temp1] += 1 + judgevalue * 9;	
					temp1 = "";
					wordvalue = 0;
				}
				break;
			}
			}
		}
		if (wordvalue == 4) {
			title[temp1] += 1 + judgevalue * 9;
			wordvalue = 0;
			temp1 = "";
		}
		while (fin.get() != ':');//读完Abstract： 
		while ((temp = fin.get()) != '\n')//读完 Abstract：之后的内容 
		{
			if (temp == EOF)
			{
				break;
			}
			if ('A' <= temp && temp <= 'Z')
				temp = temp + 32;
			switch (wordvalue) {

			case 0: {
				if (temp >= 'a'&&temp <= 'z') {
					temp1 = temp1 + temp;
					wordvalue = 1;
				}
				break;
			}
			case 1: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordvalue = 2;
				}
				else { wordvalue = 0; temp1 = ""; }
				break;
			}
			case 2: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordvalue = 3;
				}
				else { wordvalue = 0; temp1 = ""; }
				break;
			}
			case 3: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordvalue = 4;
				}
				else { wordvalue = 0; temp1 = ""; }
				break;
			}
			case 4: {
				if (temp >= 'a'&&temp <= 'z' || (temp >= '0'&&temp <= '9')) { temp1 = temp1 + temp; }
				else {
					title[temp1] ++;
					temp1 = "";
					wordvalue = 0;
				}
				break;
			}
			}
		}
		if (wordvalue == 4) {
			title[temp1] ++;
			temp1 = "";
			wordvalue = 0;
		}
		while (1)//读过空行或者判定结束 
		{
			if ((temp = fin.get()) == EOF)
			{
				flag = -1;
				break;
			}
			if (temp == '\n')
			{
				continue;
			}
			if (temp <= '9'&&temp >= '0')
			{
				break;
			}
		}
		if (flag == -1)break;
	}

	//按词频数输出；
	int max2;
	string max1;
	int j;
	int max = 0;

	for (j = 0; j < jj; j++)
	{
		max2 = 0;
		for (iter = title.begin(); iter != title.end(); iter++)
		{
			if (max2 < iter->second)
			{
				max2 = iter->second;
				max1 = iter->first;
			}
		}
		if (max2 != 0)
			fout << '<' << max1 << '>' << ": " << max2 << endl;
		if (max < max2)max = max2;
		title[max1] = -1;
	}
	fin.close();
	fout.close();
	return 0;
}