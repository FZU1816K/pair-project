#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#pragma once

using namespace std;

class InputFile
{
public:
	InputFile(string inputPath, int _phraseLength, int _weight, int _sortNum);
	~InputFile();
	int getCrtNum();									//�����ַ���
	int getLineNum();									//��������
	int getWordNum();									//���ص�������
	int getPhraseNum();
	vector<pair<string, int>> getOrderWord();

private:
	/*�����в���*/
	int weight;											//Title����Ȩ�أ�-w��
	int phraseLength;									//�趨���鳤�ȣ�-m��
	int sortNum;										//�趨�������������-n��

	/*InputFile���Ա��Ϣ*/
	int crtNum;
	int lineNum;
	int wordNum;
	int phraseNum;
	vector<pair<string, int>> orderWord;				//�����Ŵ��������

	/*InputFile���ڲ�����*/
	bool hasSort;
	bool hasCount;										//�ж��Ƿ�ͳ�ƹ�������
	bool hasOpenFile;
	ifstream inputFile;
	unordered_map<string, int> phraseMap;				//����ļ��з���Ҫ��Ĵ���
	unordered_map<string, int>::iterator itor;

	/*InputFile���ڲ��ӿں���*/
	void readFile();									//�����ļ���ͬʱͳ���ַ�������Ч�����������������Ƶ
	void sortPair();									//���ļ��е��ʰ�Ҫ������
};

