#pragma once
#include<iostream>
using namespace std;
#include<map>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

class Statistics
{
public:	
	int cnum;//�ַ���
	int wnum;//������
	int lnum;//����
	map<string, int> word;//��¼ͳ�Ƶĵ��ʻ����Ĵ�Ƶ
	map<string, int> trecord;//��¼�����еĴ�Ƶ
	map<string, int> arecord;//��¼ժҪ�еĴ�Ƶ
	void set(ifstream& in, int w, int m);//����ͳ��
	int characters(ifstream& in);//ͳ���ַ���
	int lines(ifstream& in);//ͳ������
	int	nw_words(ifstream& in);//ͳ����Ȩ�ص���
	int	w_words(ifstream& in);//ͳ��Ȩ�ص���
	int	nw_phrase(ifstream& in,int m);//ͳ����Ȩ�ش���
	int	w_phrase(ifstream& in,int m);//ͳ��Ȩ�ش���
	int get_wnum(ifstream& in);//���д���ͳ��ʱ���㵥����
};
