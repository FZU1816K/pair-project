#pragma once
/******************����input.txt��������ж��ٸ������ǰʮ��**********************/
#ifndef PHRASE_H_
#define PHRASE_H_
#include<map>
#include<vector>
#include<string>

typedef std::pair<std::string, int> PAIR;

class Psort
{
private:
	std::string finname; //��ȡ���ļ�������Ҫ���ⲿ��ȡ
	std::string foutname;
	std::vector<PAIR>phrase_v;  //�����ģ���ʱ������Ҳ���string
	int len;  //�������Ĳ�������ʾ��������ĵ��ʳ���
	int num;  //����Ĵ�������

public:

	Psort(std::string filein, std::string fileout, int length, int number);
	Psort();
	/*************************************************/
	bool get_empty();  //Ϊ�˲��Զ�����д�ĺ�����ʵ�ʲ�����Ҫ
	int get();
	/*************************************************/
	void fwrite(); //д��reault.txt
	void PS();  //�������Ƶ��������
	void show();  //��ʾ������
};

#endif
