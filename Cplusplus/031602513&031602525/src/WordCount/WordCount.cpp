#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <vector>
using namespace std;

bool isLett(char c);
bool isNum(char c);
bool isAlph(char c);
bool myFunc(const pair<string, int> &x, const pair<string, int> &y);

int main(int argc, char* argv[]) {
	string InputName, OutputName, Weight;
	bool useWordGroup = false , useCustomOutput = false, findFirstSeparator = false;
	int mNum, nNum, paperNum=0;
	int characters = 0, lines = 0, words = 0;
	int tc = 0, twords = 0, linefeedNum = 0, wordGroupNum = 0, ignoreNum = 0;
	int k, pos, length = 0, flag = 0, flag0 = 0;
	string strWords, wordGroup;
	unordered_map<string, int> strMap;
	unordered_map<string, int>::iterator it;
	vector <pair<string, int>> vtMap;

	if (argc < 7) {
		cerr << "命令行程序输入参数错误" << endl;
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
				useWordGroup = true;
			}
			else if ('n' == argv[i][1]) {
				nNum = atoi(argv[i + 1]);
				useCustomOutput = true;
			}
			i++;
		}
	}
	char c;
	ifstream infile;												//打开文件
	infile.open(InputName, ios::in);								//将文件流对象与文件连接起来 														 
	if (!infile) {													//若失败,则输出错误消息,并终止程序运行
		cerr << "open error!" << endl;
		exit(1);
	}
	infile >> noskipws;												//不忽略空白符，也不忽略换行符
	while (!infile.eof()) {
		infile >> c;
		if (infile.fail()) {										
			if (!strWords.empty() && strWords.length() >= 4) {	
				if (!useWordGroup) {								//默认统计单词
					//可能有最后一个单词，Abstract内容
					it = strMap.find(strWords);
					if (it == strMap.end()) {
						strMap[strWords] = 1;
					}
					else {
						strMap[strWords]++;
					}
				}
				else {												//统计词组
					if (wordGroupNum == mNum - 1) {
						//可能有最后一个词组，Abstract内容
						wordGroup = wordGroup + strWords;
						it = strMap.find(wordGroup);
						if (it == strMap.end()) {		//没有该词组记录
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

		if ('\n' == c) {											//读到Title、Abstract最后的一个换行符，考虑最后一个单词或词组
			linefeedNum++;
			if (linefeedNum % 2 == 1) {
				ignoreNum = 10;
			}
			else if (linefeedNum % 2 == 0) {
				ignoreNum = 2;
				flag0 = 0;
			}
			
			if (!strWords.empty() && strWords.length() >= 4) {
				if (!useWordGroup) {								//默认统计单词
					//可能有最后一个单词
					if (linefeedNum % 2 == 0 || (linefeedNum % 1 == 0 && "0" == Weight)) {
						k = 1;					//Abstract内容或者Weight为0时的Title内容
					}
					else {						//Weight为1时的Title内容
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
				else {												//统计词组
					if (wordGroupNum == mNum - 1) {
						//可能有最后一个词组
						if (linefeedNum % 2 == 0 || (linefeedNum % 1 == 0 && "0" == Weight)) {
							k = 1;					//Abstract内容或者Weight为0时的Title内容
						}
						else {						//Weight为1时的Title内容
							k = 10;
						}
						wordGroup = wordGroup + strWords;

						//cout << "WordGroup = " << wordGroup << endl;

						it = strMap.find(wordGroup);
						if (it == strMap.end()) {		//没有该词组记录
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

		if (linefeedNum % 2 == 0 && paperNum == int(c)-48 && 0 == flag0) {		//跳过不需要统计的部分，无用的paperNum可能成为bug
			paperNum++;
			flag0 = 1;
			ignoreNum = 8;
			continue;
		}
		tc++;

		if (!useWordGroup) {												//默认统计单词	
			//判断单词
			if (flag == 0) {
				if (isLett(c)) {
					//大写字母改为小写
					if (c >= 'A' && c <= 'Z')
						c += 32;
					strWords = strWords + c;
					length++;
				}
				else if (isNum(c)) {
					if (length < 4) {					//非单词，strWords清空
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
					if (length < 4) {					//非单词，strWords清空
						strWords.clear();
						length = 0;
					}
					else {								//单词
						if (linefeedNum % 2 == 1 || (linefeedNum % 2 == 0 && "0" == Weight)) {
							k = 1;					//Abstract内容或者Weight为0时的Title内容
						}
						else {						//Weight为1时的Title内容
							k = 10;
						}
						it = strMap.find(strWords);
						if (it == strMap.end()) {		//没有该单词记录
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
		else {																//统计词组
			if (flag == 0) {
				if (isLett(c)) {						//读到字母
					//大写字母改为小写
					if (c >= 'A' && c <= 'Z')
						c += 32;
					strWords = strWords + c;
					length++;
				}
				else if (isNum(c)) {					//读到数字
					if (length < 4) {					//非单词，strWords清空，wordGroup清空
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
				else if (!isAlph(c)) {					//读到分隔符
					if (0 == length && wordGroupNum != 0) {				//词组中单词间的分隔符
						wordGroup = wordGroup + c;
					}
					else if (length < 4) {				//非单词，strWords清空，wordGroup清空
						strWords.clear();
						wordGroup.clear();
						wordGroupNum = 0;
						length = 0;
					}
					else {								//单词
						wordGroupNum++;
						wordGroup = wordGroup + strWords;

						//cout << "WordGroup = " << wordGroup << endl;
						//cout << "wordGroupNum = " << wordGroupNum << endl;

						if (mNum == wordGroupNum) {		//词组
							if (linefeedNum % 2 == 1 || (linefeedNum % 2 == 0 && "0" == Weight)) {
								k = 1;					//Abstract内容或者Weight为0时的Title内容
							}
							else {						//Weight为1时的Title内容
								k = 10;
							}
							it = strMap.find(wordGroup);
							if (it == strMap.end()) {		//没有该单词记录
								strMap[wordGroup] = k;
							}
							else {
								strMap[wordGroup] += k;
							}

							//词组取后m-1个单词
							for (int l = 0; l<wordGroup.length(); l++) {
								if (!isAlph(wordGroup[l])) {		//找到分隔符，即第一个单词末尾
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
	lines = linefeedNum+1;
	words = twords;
	
	//词频排序
	for (auto it = strMap.begin(); it != strMap.end(); it++) {
		vtMap.push_back(make_pair(it->first, it->second));
	}
	int n = 10;
	if (useCustomOutput) {
		n = nNum;
	}
	partial_sort(vtMap.begin(), vtMap.begin() + n, vtMap.end(), myFunc);

	//文件输出
	ofstream outfile(OutputName, ios::out);
	if (!outfile) {
		cerr << "open error!" << endl;
		exit(1);
	}
	int t = 0;
	outfile << "characters: " << characters << endl;
	outfile << "words: " << words << endl;
	outfile << "lines: " << lines << endl;
	for (auto it = vtMap.begin(); t<n && it != vtMap.end(); ++it, t++) {
		outfile << "<" << it->first << ">: " << it->second << endl;
	}
	infile.close();
	outfile.close();
	return 0;
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