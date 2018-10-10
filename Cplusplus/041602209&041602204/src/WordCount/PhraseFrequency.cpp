#include"PhraseFrequency.h"

int PhraseFrequency(string filename_in, string filename_out, int phraseLength, int judgeValue,int sortLength)
{
	//int phraseLength;//���鳤��
	//int judgeValue;//Ȩ�� 0ʱ��Ϊ1 1ʱTitleΪ10 AbstractΪ1
	//int sortLength; //ǰTOP N
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
	char temp;//��ʱ��Ŷ�����ַ�
	string temp1 = "";//��ʱ��ſ��ܳ�Ϊ�Ϸ����ʵĴ�
	string temp2 = "";//��ʱ��ŷָ���
	string str[400];//��źϷ�������Ƿ�����
	string dvi[400];//��ŷָ���
	int phraseValue = 0;//�ж�str������n���ַ����Ƿ������Ϊ��������
	int wordValue = 0;//�ж��������ַ��Ƿ���Գ�Ϊ�Ϸ�����
	int unwordValue = 0;//�жϷָ���
	int lineWord = 0;//���ڼ���ÿƪ���ĵ�Title/Abstract�ĺϷ�������Ƿ������������������з�����
	int lineUnword = 0;//���ڼ���ÿƪ���ĵ�Title/Abstract�ķָ����������������з�����
	int flag = 0;//�ļ���������ж�

	while (true)//�����ļ�
	{
		flag = 0;
		while (temp = (fin.get() != '\n'))
		{
			if (temp == EOF)flag = -1;
		}
		if (flag == -1)
		{
			break;
		}//�������ı���� 
		while (fin.get() != ':');//����Title�� 
		while (fin.get() != ' ');//����:��Ŀո�
		for (i = 0; i <= lineWord; i++)//��ʼ����Ч�������� 
		{
			str[i] = "";
		}
		for (i = 0; i <= lineUnword; i++)//��ʼ���ָ������� 
		{

			dvi[i] = "";
		}
		lineWord = 0;		//��ʼ���������
		lineUnword = 0;
		unwordValue = 0;
		while ((temp = fin.get()) != '\n')//����Title:������� 
		{
			if (!((temp <= 'z'&&temp >= 'a') || (temp >= '0'&&temp <= '9') || (temp >= 'A'&&temp <= 'Z')))//�ж��Ƿ�Ϊ�ָ���
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
			if ('A' <= temp && temp <= 'Z')//�ж��Ƿ�Ϊ�Ϸ�����
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
		for (i = 0; i <= lineWord - phraseLength; i++)//����ƥ��
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
		for (i = 0; i < lineWord; i++)//��ʼ����Ч�������� 
		{
			str[i] = "";
		}
		for (i = 0; i < lineUnword; i++)//��ʼ���ָ������� 
		{
			dvi[i] = "";
		}
		lineWord = 0;										//��ʼ���������
		lineUnword = 0;
		unwordValue = 0;
		temp1 = "";
		temp2 = "";
		while (fin.get() != ':');//����Abstract�� 
		while (fin.get() != ' ');//����:��Ŀո�
		while ((temp = fin.get()) != '\n')//����Abstract:������ 
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
		while (1)//�������л����ж����� 
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
	for (j = 0; j < sortLength; j++)//���TOP n
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