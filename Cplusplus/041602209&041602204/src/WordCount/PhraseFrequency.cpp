#include"PhraseFrequency.h"

int PhraseFrequency(string filename_in, string filename_out, int phraseLength, int judgeValue,int sortLength)
{
	//int phraseLength;//词组长读
	//int judgeValue;//权重 0时都为1 1时Title为10 Abstract为1
	//int sortLength; //前TOP N
	//cin >> phraseLength;
	//cin >> judgeValue;
	//cin >> sortLength;
	int i, j;
	ifstream fin(filename_in, ios::in);
	ofstream fout(filename_out, ios::app);
	if (!fin) {
		cout << "Can't open file" << endl;
		return -1;
	}
	map<string, int> phrase;
	map<string, int>::iterator iter;
	char temp;//临时存放读入的字符
	string temp1 = "";//临时存放可能成为合法单词的串
	string temp2 = "";//临时存放分隔符
	string str[400];//存放合法单词与非法单词
	string dvi[400];//存放分隔符
	int phraseValue = 0;//判定str连续的n个字符串是否满足成为词组条件
	int wordValue = 0;//判定连续的字符是否可以成为合法单词
	int unwordValue = 0;//判断分隔符
	int lineWord = 0;//用于计数每篇论文的Title/Abstract的合法单词与非法单词数量，遇到换行符清零
	int lineUnword = 0;//用于计数每篇论文的Title/Abstract的分隔符数量，遇到换行符清零
	int flag = 0;//文件读入结束判定

	while (true)//读入文件
	{
		flag = 0;
		while (temp = (fin.get() != '\n'))
		{
			if (temp == EOF)flag = -1;
		}
		if (flag == -1)
		{
			break;
		}//读完论文标号行 
		while (fin.get() != ':');//读完Title： 
		while (fin.get() != ' ');//读完:后的空格
		for (i = 0; i <= lineWord; i++)//初始化有效单词数组 
		{
			str[i] = "";
		}
		for (i = 0; i <= lineUnword; i++)//初始化分隔符数组 
		{

			dvi[i] = "";
		}
		lineWord = 0;		//初始化各项参数
		lineUnword = 0;
		unwordValue = 0;
		while ((temp = fin.get()) != '\n')//读完Title:后的内容 
		{
			if (!((temp <= 'z'&&temp >= 'a') || (temp >= '0'&&temp <= '9') || (temp >= 'A'&&temp <= 'Z')))//判断是否为分隔符
			{
				temp2 = temp2 + temp;
				unwordValue++;
			}
			else if (unwordValue > 0)
			{
				dvi[lineUnword++] = temp2;
				temp2 = "";
				unwordValue = 0;
			}
			if ('A' <= temp && temp <= 'Z')//判断是否为合法单词
				temp = temp + 32;

			switch (wordValue) {
			case 0: {
				if (temp >= 'a'&&temp <= 'z') {
					temp1 = temp1 + temp;
					wordValue = 1;
				}
				break;
			}
			case 1: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordValue = 2;
				}
				else { wordValue = 0; temp1 = ""; str[lineWord] = "00"; lineWord++; }
				break;
			}
			case 2: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordValue = 3;
				}
				else { wordValue = 0; temp1 = ""; str[lineWord] = "00"; lineWord++; }
				break;
			}
			case 3: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordValue = 4;
				}
				else { wordValue = 0; temp1 = ""; str[lineWord] = "00";	lineWord++; }
				break;
			}
			case 4: {
				if (temp >= 'a'&&temp <= 'z' || (temp >= '0'&&temp <= '9')) { temp1 = temp1 + temp; }
				else {
					str[lineWord] = temp1;
					lineWord++;
					temp1 = "";
					wordValue = 0;
				}
				break;
			}
			}
		}
		if (wordValue == 4) {
			str[lineWord] = temp1;
			lineWord++;
			wordValue = 0;
			temp1 = "";
		}
		for (i = 0; i <= lineWord - phraseLength; i++)//词组匹配
		{
			for (j = 0; j < phraseLength; j++)
			{
				if (str[i + j] != "00")
				{
					phraseValue++;
				}
			}
			if (phraseValue == phraseLength)
			{
				for (j = 0; j < phraseLength - 1; j++)
				{
					temp1 = temp1 + str[i + j];
					temp1 = temp1 + dvi[i + j];
				}
				temp1 = temp1 + str[i + phraseLength - 1];
				phrase[temp1] +=1+judgeValue*9;

				temp1 = "";
			}
			phraseValue = 0;
		}
		for (i = 0; i < lineWord; i++)//初始化有效单词数组 
		{
			str[i] = "";
		}
		for (i = 0; i < lineUnword; i++)//初始化分隔符数组 
		{
			dvi[i] = "";
		}
		lineWord = 0;										//初始化各项参数
		lineUnword = 0;
		unwordValue = 0;
		temp1 = "";
		temp2 = "";
		while (fin.get() != ':');//读完Abstract： 
		while (fin.get() != ' ');//读完:后的空格
		while ((temp = fin.get()) != '\n')//读完Abstract:的内容 
		{
			if (temp == EOF)
			{
				break;
			}
			if (!((temp <= 'z'&&temp >= 'a') || (temp >= '0'&&temp <= '9') || (temp >= 'A'&&temp <= 'Z')))
			{
				temp2 = temp2 + temp;
				unwordValue++;
			}
			else
			{
				if (unwordValue > 0)
				{
					dvi[lineUnword++] = temp2;
					temp2 = "";
					unwordValue = 0;
				}
			}
			if ('A' <= temp && temp <= 'Z')
				temp = temp + 32;

			switch (wordValue) {
			case 0: {
				if (temp >= 'a'&&temp <= 'z') {
					temp1 = temp1 + temp;
					wordValue = 1;
				}
				break;
			}
			case 1: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordValue = 2;
				}
				else { wordValue = 0; temp1 = ""; str[lineWord] = "00"; lineWord++; }
				break;
			}
			case 2: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordValue = 3;
				}
				else { wordValue = 0; temp1 = ""; str[lineWord] = "00"; lineWord++; }
				break;
			}
			case 3: {
				if (temp >= 'a'&&temp <= 'z')
				{
					temp1 = temp1 + temp;
					wordValue = 4;
				}
				else { wordValue = 0; temp1 = ""; str[lineWord] = "00";	lineWord++; }
				break;
			}
			case 4: {
				if (temp >= 'a'&&temp <= 'z' || (temp >= '0'&&temp <= '9')) { temp1 = temp1 + temp; }
				else {
					str[lineWord] = temp1;
					lineWord++;
					temp1 = "";
					wordValue = 0;
				}
				break;
			}
			}
		}
		if (wordValue == 4) {
			str[lineWord] = temp1;
			lineWord++;
			wordValue = 0;
			temp1 = "";
		}
		for (i = 0; i <= lineWord - phraseLength; i++)
		{
			for (j = 0; j < phraseLength; j++)
			{
				if (str[i + j] != "00")
				{
					phraseValue++;
				}
			}
			if (phraseValue == phraseLength)
			{
				for (j = 0; j < phraseLength - 1; j++)
				{
					temp1 = temp1 + str[i + j];
					temp1 = temp1 + dvi[i + j];
				}
				temp1 = temp1 + str[i + phraseLength - 1];
				phrase[temp1]++;
				//cout << temp1 << endl;
				temp1 = "";
			}
			phraseValue = 0;
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
	int max2;
	string max1;
	int test;
	int max = 0;
	for (j = 0; j < sortLength; j++)//输出TOP n
	{
		max2 = 0;
		for (iter = phrase.begin(); iter != phrase.end(); iter++)
		{
			if (max2 < iter->second)
			{
				max2 = iter->second;
				max1 = iter->first;
			}
		}
		if (max2 != 0)
			fout << '<' << max1 << '>' << ": " << max2 << endl;
		if (j == 0)
		{
			test = max2;
		}
		if (max < max2)max = max2;
		phrase[max1] = -1;
	}
	fin.close();
	fout.close();
	return test;
}