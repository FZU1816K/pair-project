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
	vector<int>a;//������
	map<string, int> word;//��¼ͳ�Ƶĵ��ʻ����Ĵ�Ƶ
	map<string, int> trecord;//��¼�����еĴ�Ƶ
	map<string, int> arecord;//��¼ժҪ�еĴ�Ƶ
	void set(ifstream& in, int w, int m);//����ͳ��
	void display(ofstream& out,int temp);//���ͳ�ƽ��
	int characters(ifstream& in);//ͳ���ַ���
	int lines(ifstream& in);//ͳ������
	int	nw_words(ifstream& in);//ͳ����Ȩ�ص���
	int	w_words(ifstream& in);//ͳ��Ȩ�ص���
	int	nw_phrase(ifstream& in,int m);//ͳ����Ȩ�ش���
	int	w_phrase(ifstream& in,int m);//ͳ��Ȩ�ش���
private:
	int cnum;//�ַ���
	int wnum;//������
	int lnum;//����
};
