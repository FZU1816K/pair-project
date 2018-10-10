#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <vector>
#include "Core.h"
using namespace std;

bool isLett(char c);
bool isNum(char c);
bool isAlph(char c);
bool myFunc(const pair<string, int> &x, const pair<string, int> &y);

int main(int argc, char* argv[]) {
	string InputName, OutputName, Weight;
	int mNum = -1 , nNum = -1;
	if (argc < 7) {
		cerr << "�����г��������������" << endl;
		exit(1);
	}
	else {
		for (int i = 1; i < argc; i++) {
			if ('i' == argv[i][1]) {
				InputName = argv[i + 1];
			}
			else if ('o' == argv[i][1]) {
				OutputName = argv[i + 1];
			}
			else if ('w' == argv[i][1]) {
				Weight = argv[i + 1];
			}
			else if ('m' == argv[i][1]) {
				mNum = atoi(argv[i + 1]);
			}
			else if ('n' == argv[i][1]) {
				nNum = atoi(argv[i + 1]);
			}
			i++;
		}
	}

	Core core(InputName, OutputName, Weight, mNum, nNum);
	vector <pair<string, int>> vtMap = core.getVector();
	int n = 10;
	if (nNum != -1) {
		n = nNum;
	}
	//�ļ����
	ofstream outfile(OutputName, ios::out);
	if (!outfile) {
		cerr << "open error!" << endl;
		exit(1);
	}
	int t = 0;
	outfile << "characters: " << core.getCrt() << endl;
	outfile << "words: " << core.getWords() << endl;
	outfile << "lines: " << core.getLines() << endl;
	for (auto it = vtMap.begin(); t<n && it != vtMap.end(); ++it, t++) {
		outfile << "<" << it->first << ">: " << it->second << endl;
	}
	outfile.close();
	return 0;
}

Core::Core(string InputNameTemp, string OutputNameTemp, string WeightTemp, int mNumTemp, int nNumTemp) {
	InputName = InputNameTemp;
	OutputName = OutputNameTemp;
	Weight = WeightTemp;
	mNum = mNumTemp;
	nNum = nNumTemp;
	infile.open(InputName, ios::in);								//���ļ����������ļ��������� 														 
	if (!infile) {													//��ʧ��,�����������Ϣ,����ֹ��������
		cerr << "open error!" << endl;
		exit(1);
	}
	if (-1 == mNum) {
		useWordGroup = false;
	}
	else {
		useWordGroup = true;
	}
	if (-1 == nNum) {
		useCustomOutput = false;
	}
	else {
		useCustomOutput = true;
	}
	hasRunKernel = false;
}

Core::~Core(){
	infile.close();
}

int Core::getCrt() {
	if (!hasRunKernel) kernelFunction();
	return characters;
}
int Core::getWords() {
	if (!hasRunKernel) kernelFunction();
	return words;
}
int Core::getLines() {
	if (!hasRunKernel) kernelFunction();
	return lines;
}
vector <pair<string, int>> Core::getVector() {
	if (strMap.empty()) kernelFunction();
	if (vtMap.empty()) sort();
	return vtMap;
}

void Core::kernelFunction() {
	bool findFirstSeparator = false;
	int tc = 0, twords = 0, linefeedNum = 0, wordGroupNum = 0, ignoreNum = 0, paperNum = 0;
	int k, pos, length = 0, flag = 0, flag0 = 0;
	string strWords, wordGroup;

	infile.clear(ios::goodbit);
	infile.seekg(ios::beg);
	char c;
	infile >> noskipws;

	while (!infile.eof()) {
		infile >> c;
		if (infile.fail()) {
			if (!strWords.empty() && strWords.length() >= 4) {
				if (!useWordGroup) {								//Ĭ��ͳ�Ƶ���
																	//���������һ�����ʣ�Abstract����
					it = strMap.find(strWords);
					if (it == strMap.end()) {
						strMap[strWords] = 1;
					}
					else {
						strMap[strWords]++;
					}
				}
				else {												//ͳ�ƴ���
					if (wordGroupNum == mNum - 1) {
						//���������һ�����飬Abstract����
						wordGroup = wordGroup + strWords;
						it = strMap.find(wordGroup);
						if (it == strMap.end()) {		//û�иô����¼
							strMap[wordGroup] = 1;
						}
						else {
							strMap[wordGroup]++;
						}
					}
				}
				twords++;
				strWords.clear();
			}
			break;
		}

		//cout <<"c = "<<c<< "   tc = " <<tc<< endl;
		if (ignoreNum>0) {
			ignoreNum--;
			continue;
		}

		if ('\n' == c) {											//����Title��Abstract����һ�����з����������һ�����ʻ����
			linefeedNum++;
			if (linefeedNum % 2 == 1) {
				ignoreNum = 10;
			}
			else if (linefeedNum % 2 == 0) {
				ignoreNum = 2;
				flag0 = 0;
			}

			if (!strWords.empty() && strWords.length() >= 4) {
				if (!useWordGroup) {								//Ĭ��ͳ�Ƶ���
																	//���������һ������
					if (linefeedNum % 2 == 0 || (linefeedNum % 1 == 0 && "0" == Weight)) {
						k = 1;					//Abstract���ݻ���WeightΪ0ʱ��Title����
					}
					else {						//WeightΪ1ʱ��Title����
						k = 10;
					}
					it = strMap.find(strWords);
					if (it == strMap.end()) {
						strMap[strWords] = k;
					}
					else {
						strMap[strWords] += k;
					}
				}
				else {												//ͳ�ƴ���
					if (wordGroupNum == mNum - 1) {
						//���������һ������
						if (linefeedNum % 2 == 0 || (linefeedNum % 1 == 0 && "0" == Weight)) {
							k = 1;					//Abstract���ݻ���WeightΪ0ʱ��Title����
						}
						else {						//WeightΪ1ʱ��Title����
							k = 10;
						}
						wordGroup = wordGroup + strWords;

						//cout << "WordGroup = " << wordGroup << endl;

						it = strMap.find(wordGroup);
						if (it == strMap.end()) {		//û�иô����¼
							strMap[wordGroup] = k;
						}
						else {
							strMap[wordGroup] += k;
						}
					}
				}
				twords++;
			}

			strWords.clear();
			length = 0;
			flag = 0;
			if (useWordGroup) {
				wordGroup.clear();
				wordGroupNum = 0;
			}
			tc++;
			continue;
		}

		if (linefeedNum % 2 == 0 && paperNum == int(c) - 48 && 0 == flag0) {		//��������Ҫͳ�ƵĲ��֣����õ�paperNum���ܳ�Ϊbug
			paperNum++;
			flag0 = 1;
			ignoreNum = 8;
			continue;
		}
		tc++;

		if (!useWordGroup) {												//Ĭ��ͳ�Ƶ���	
																			//�жϵ���
			if (flag == 0) {
				if (isLett(c)) {
					//��д��ĸ��ΪСд
					if (c >= 'A' && c <= 'Z')
						c += 32;
					strWords = strWords + c;
					length++;
				}
				else if (isNum(c)) {
					if (length < 4) {					//�ǵ��ʣ�strWords���
						strWords.clear();
						length = 0;
						flag = 1;
					}
					else {
						strWords = strWords + c;
						length++;
					}
				}
				else if (!isAlph(c)) {
					if (length < 4) {					//�ǵ��ʣ�strWords���
						strWords.clear();
						length = 0;
					}
					else {								//����
						if (linefeedNum % 2 == 1 || (linefeedNum % 2 == 0 && "0" == Weight)) {
							k = 1;					//Abstract���ݻ���WeightΪ0ʱ��Title����
						}
						else {						//WeightΪ1ʱ��Title����
							k = 10;
						}
						it = strMap.find(strWords);
						if (it == strMap.end()) {		//û�иõ��ʼ�¼
							strMap[strWords] = k;
						}
						else {
							strMap[strWords] += k;
						}
						twords++;
						strWords.clear();
						length = 0;
					}
				}
			}
			else {
				if (!isAlph(c)) {
					flag = 0;
				}
			}
		}
		else {																//ͳ�ƴ���
			if (flag == 0) {
				if (isLett(c)) {						//������ĸ
														//��д��ĸ��ΪСд
					if (c >= 'A' && c <= 'Z')
						c += 32;
					strWords = strWords + c;
					length++;
				}
				else if (isNum(c)) {					//��������
					if (length < 4) {					//�ǵ��ʣ�strWords��գ�wordGroup���
						strWords.clear();
						wordGroup.clear();
						wordGroupNum = 0;
						length = 0;
						flag = 1;
					}
					else {
						strWords = strWords + c;
						length++;
					}
				}
				else if (!isAlph(c)) {					//�����ָ���
					if (0 == length && wordGroupNum != 0) {				//�����е��ʼ�ķָ���
						wordGroup = wordGroup + c;
					}
					else if (length < 4) {				//�ǵ��ʣ�strWords��գ�wordGroup���
						strWords.clear();
						wordGroup.clear();
						wordGroupNum = 0;
						length = 0;
					}
					else {								//����
						wordGroupNum++;
						wordGroup = wordGroup + strWords;

						//cout << "WordGroup = " << wordGroup << endl;
						//cout << "wordGroupNum = " << wordGroupNum << endl;

						if (mNum == wordGroupNum) {		//����
							if (linefeedNum % 2 == 1 || (linefeedNum % 2 == 0 && "0" == Weight)) {
								k = 1;					//Abstract���ݻ���WeightΪ0ʱ��Title����
							}
							else {						//WeightΪ1ʱ��Title����
								k = 10;
							}
							it = strMap.find(wordGroup);
							if (it == strMap.end()) {		//û�иõ��ʼ�¼
								strMap[wordGroup] = k;
							}
							else {
								strMap[wordGroup] += k;
							}

							//����ȡ��m-1������
							for (int l = 0; l<wordGroup.length(); l++) {
								if (!isAlph(wordGroup[l])) {		//�ҵ��ָ���������һ������ĩβ
									findFirstSeparator = true;
								}
								if (findFirstSeparator) {
									if (isLett(wordGroup[l])) {
										pos = l;
										findFirstSeparator = false;
										break;
									}
								}
							}
							wordGroup = wordGroup.substr(pos, wordGroup.length() - pos);
							wordGroupNum--;
						}
						wordGroup = wordGroup + c;

						twords++;
						strWords.clear();
						length = 0;
					}
				}
			}
			else {
				if (!isAlph(c)) {
					flag = 0;
				}
			}
		}
	}
	characters = tc;
	lines = linefeedNum + 1;
	words = twords;
}

void Core::sort() {
	//��Ƶ����
	for (auto it = strMap.begin(); it != strMap.end(); it++) {
		vtMap.push_back(make_pair(it->first, it->second));
	}
	int n = 10;
	if (useCustomOutput) {
		n = nNum;
	}
	partial_sort(vtMap.begin(), vtMap.begin() + n, vtMap.end(), myFunc);
}

bool isLett(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	else
		return false;
}
bool isNum(char c) {
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

bool isAlph(char c) {
	if (isNum(c) || isLett(c))
		return true;
	else
		return false;
}
bool myFunc(const pair<string, int> &x, const pair<string, int> &y) {
	if (x.second > y.second)
		return true;
	else if (x.second == y.second) {
		if (x.first < y.first)
			return true;
		else
			return false;
	}
	else
		return false;
}