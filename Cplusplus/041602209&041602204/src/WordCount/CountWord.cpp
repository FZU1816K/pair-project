#include"CountWord.h"


int CountWord(string filename_in)
{


	int cnt1 = 0, n = 0;
	string temp11;
	int flag = 0;
	fstream fin(filename_in, ios::in);//输入文件
	if (!fin) {
		cout << "Can't open file" << endl;
		return -1;
	}
	int wordvalue = 0;
	int cnt = 0;
	char temp;
	string temp1;
	for (; ; )
	{
		flag = 0;
		while (temp = (fin.get() != '\n'))
		{
			if (temp == EOF)flag = -1;
		}//读完论文标号行 
		if (flag == -1)break;
		while (fin.get() != ':');// 读完Title：              
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
				if (temp != ' ') { temp1 = temp1 + temp; }
				else {
					 cnt++;
					temp1 = "";
					wordvalue = 0;
				}
				break;
			}
			}
		}
		if (wordvalue == 4) {
			cnt++;
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
				if (temp != ' ') { temp1 = temp1 + temp; }
				else {
					cnt++;
					temp1 = "";
					wordvalue = 0;
				}
				break;
			}
			}
		}
		if (wordvalue == 4) {
			 cnt++;
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
	fin.close();
	return cnt;
}
