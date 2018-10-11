#pragma once
#pragma once

#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include<iostream>
#include<fstream>
#include<queue>
#include<map>
#include<unordered_map>
#include<string>
#include<functional>
#include<algorithm>
#include<string>
#include<queue>
#include <regex>

using namespace std;
struct node {
	int num;
	string s;
};
node result[105];
node tem_result[105];

bool cmp(node a, node b) {
	return a.num>b.num;
}
bool cmp1(node a, node b) {
	return a.s < b.s;
}

void charCount(const char* file, const char* file1);
void frequency(int w_flag,int times, const char* file, const char* file1);
void lineCount(const char* file, const char* file1);
void p_frequency(int w_flag,int times, int m, const char* file, const char* file1);
void wordCount(const char* file, const char* file1);


void frequency(int w_flag,int times, const char* file, const char* file1) {
	int number = 0;
	ifstream fin;
	ofstream fout;
	fout.open(file1, ios::out | ios::app);
	fin.open(file);
	if (!fout) {
		cout << "The File cannot open.1111" << endl;
	}
	if (!fin) {
		cout << "The File cannot open." << endl;
	}
	string s = "";
	unordered_map<string, int> wordList;
	int num = 0;//状态转换标识
	int flag = 1;
	while (1) {

		char c;
		fin.get(c);
		if (fin.eof()) {
			break;
		}


		
		if ('A' <= c && c <= 'Z') c = c + 32;
		
		if (num == 0) {
			if ('a' <= c && c <= 'z') {
				s += c;
				num++;
			}
		}
		else if (num == 1) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
			}
		}
		else if (num == 2) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
			}
		}
		else if (num == 3) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
			}
		}
		else if (num == 4) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num = 4;
			}
			else {
				string s1 = s + c;
				if (s1 == "title:"&&w_flag==1 ) {
					flag = 10;
				}
				else if (s1 == "abstract:"&&w_flag==1) {
					flag = 1;
				}
				else wordList[s]+=flag;
				s = "";
				num = 0;
			}
		}
	}
	if (num == 4) {
		wordList[s]+=flag;
	}
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> maxList;

	//遍历hash_map，加入优先队列
	for (unordered_map<string, int>::const_iterator i = wordList.begin(); i != wordList.end(); i++) {
		maxList.push(make_pair(i->second, i->first));
		if (maxList.size() > (unsigned)times) {
			maxList.pop();
		}
	}
	int i = 0;
	//取出队列里面的值，放入result结构数组中
	while (!maxList.empty()) {
		result[i].num = maxList.top().first;
		result[i].s = maxList.top().second;
		maxList.pop();
		i++;
	}

	//排序输出
	sort(result, result + i, cmp);
	int num_count = 0;//记录同频率的
	for (int j = 0; j < i; j++) {
		if (result[j].num == result[j + 1].num) {
			num_count++;
		}
		else {
			if (num_count == 0) {
				fout << "<" << result[j].s << ">" << "：" << result[j].num << endl;

			}
			else {
				int temp = 0;
				for (int k = j - num_count; k <= j; k++) {
					tem_result[temp] = result[k];
					temp++;
				}
				sort(tem_result, tem_result + num_count, cmp1);
				for (int k = 0; k <= num_count; k++) {
					fout << "<" << tem_result[k].s << ">" << "：" << tem_result[k].num << endl;
				}
				num_count = 0;
			}
		}

	}

	fin.close();
	fout.close();
}

/*
*算法是统计有效行数，并统计每一行的字符数量，如果是有效行，则加进count。同时统计‘:’的个数，减去相应的字符数量。
*
*/
void charCount(const char* file, const char* file1) {
	ifstream fin;
	ofstream fout;
	fout.open(file1, ios::trunc);
	fin.open(file);
	if (!fin) {
		cout << "The File cannot open." << endl;
	}
	char c;
	int count = 0;//记录有效字符数
	int flag = 0;//记录是否为有效行
	int line_count=0;//记录每行的字符
	int m_number = 0;//记录":"的个数
	while (true) {
		fin.get(c);
		if ('A' <= c && c <= 'Z') c += 32;
		if (fin.eof()) {
			break;
		}
		line_count++;
		if (c > 32 && !('0' <= c && c <= '9')) {
			flag = 1;
		}
		if (c == ':') {
			m_number++;
		}
		if (c == '\n' || c == '\t' || c == 10) {
			if (flag == 1) {
				count += line_count;
			}
			line_count = 0;
			flag = 0;
		}
	}
	if (flag == 1) {
		count += line_count;
	}
	if (m_number % 2 == 0) {
		count = count - m_number / 2 * 17;
	}
	else {
		count = count - m_number / 2 * 17-7;
	}
	fout << "characters：" << count << endl;
	fin.close();
	fout.close();
}



void lineCount(const char* file, const char* file1) {
	ifstream fin;
	ofstream fout;
	fout.open(file1, ios::app);
	int count = 0;
	int flag = 0;
	fin.open(file);
	if (!fin) {
		cout << "The File cannot open." << endl;
	}
	char c;
	while (true) {
		fin.get(c);
		if (fin.eof()) {
			break;
		}
		if (c > 32 && !('0' <= c && c <= '9')) {
			flag = 1;
		}
		if (c == '\n' || c == '\t' || c == 10) {
			if (flag == 1) {
				count++;
			}
			flag = 0;
		}
	}
	if (flag == 1) {
		count++;
	}

	fout << "lines：" << count << endl;

	fin.close();
	fout.close();
}

void  p_frequency(int w_flag,int times, int m, const char* file, const char* file1) {
	queue<string>que;
	queue<string>que_temp;
	int number = 0;
	string tem[11];
	ifstream fin;
	ofstream fout;
	fout.open(file1, ios::out | ios::app);
	fin.open(file);
	if (!fout) {
		cout << "The File cannot open.1111" << endl;
	}
	if (!fin) {
		cout << "The File cannot open." << endl;
	}
	string s = "";
	unordered_map<string, int> wordList;

	int num = 0;//状态转换标识
	int flag = 1;
	int more_flag = 0;
	while (1) {

		char c;
		if (!more_flag) {
			fin.get(c);
			if (fin.eof()) {
				break;
			}
		}
		else {
			more_flag = 0;
		}


		if ('A' <= c && c <= 'Z') c = c + 32;

		if (num == 0) {
			if ('a' <= c && c <= 'z') {
				s += c;
				num++;
			}
			else {
				while (!que.empty()) {
					que.pop();
				}
			}
		}
		else if (num == 1) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
				while (!que.empty()) {
					que.pop();
				}
			}
		}
		else if (num == 2) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
				while (!que.empty()) {
					que.pop();
				}
			}
		}
		else if (num == 3) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
				while (!que.empty()) {
					que.pop();
				}
			}
		}
		else if (num == 4) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num = 4;
			}
			else {
				string s1 = s + c;
				if (s1 == "title:"&&w_flag==1) {
					flag = 10;
				}
				else if (s1 == "abstract:"&&w_flag==1) {
					flag = 1;
				}
				else {
					que.push(s);
					string s2;
					s2 += c;
					while (1) {
						fin.get(c);
						if (fin.eof()) {
							break;
						}
						if ('A' <= c && c <= 'Z') c = c + 32;
						if (!(('a' <= c && c <= 'z')||('0'<=c&&c<='9'))&&c>=32) {
							s2 += c;
						}
						else {
							que.push(s2);
							more_flag = 1;
							break;
						}
						
					}
				}
				if (que.size() >= (unsigned)(2 * m - 1)) {
					que_temp = que;
					string s3;
					for (int i = 0; i < 2 * m - 1; i++) {
						s3 += que_temp.front();
						que_temp.pop();
					}
					wordList[s3] += flag;
					if (que.size() >= 2) {
						que.pop();
						que.pop();
					}
				}
				s = "";
				num = 0;
			}
		}
	}
	if (num == 4) {
		string s3;
		if (que.size() >=(unsigned) (2 * m - 2)) {
			while (!que.empty()) {
				s3 += que.front();
				que.pop();
			}
			s3 += s;
			wordList[s3] += flag;
		}

	}
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> maxList;

	//遍历hash_map，加入优先队列
	for (unordered_map<string, int>::const_iterator i = wordList.begin(); i != wordList.end(); i++) {
		maxList.push(make_pair(i->second, i->first));
		if (maxList.size() > (unsigned)times) {
			maxList.pop();
		}
	}
	int i = 0;
	//取出队列里面的值，放入result结构数组中
	while (!maxList.empty()) {
		result[i].num = maxList.top().first;
		result[i].s = maxList.top().second;
		maxList.pop();
		i++;
	}

	//排序输出
	sort(result, result + i, cmp);
	int num_count = 0;//记录同频率的
	for (int j = 0; j < i; j++) {
		if (result[j].num == result[j + 1].num) {
			num_count++;
		}
		else {
			if (num_count == 0) {
				fout << "<" << result[j].s << ">" << "：" << result[j].num << endl;

			}
			else {
				int temp = 0;
				for (int k = j - num_count; k <= j; k++) {
					tem_result[temp] = result[k];
					temp++;
				}
				sort(tem_result, tem_result + num_count, cmp1);
				for (int k = 0; k <= num_count; k++) {
					fout << "<" << tem_result[k].s << ">" << "：" << tem_result[k].num << endl;
				}
				num_count = 0;
			}
		}

	}

	fin.close();
	fout.close();

}

void wordCount(const char* file, const char* file1) {
	int number = 0;
	ifstream fin;
	ofstream fout;
	fout.open(file1, ios::app);
	fin.open(file);
	if (!fin) {
		cout << "The File cannot open." << endl;
	}
	string s = "";
	unordered_map<string, int> wordList;
	int num = 0;//状态转换标识
	while (true) {
		char c;
		fin.get(c);
		if (fin.eof()) {
			break;
		}

		if ('A' <= c && c <= 'Z') c = c + 32;
		if (num == 0) {
			if ('a' <= c && c <= 'z') {
				s += c;
				num++;
			}
			else {
				while (1) {
					fin.get(c);
					if (!(('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) || fin.eof())
						break;
				}

			}
		}
		else if (num == 1) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
			}
		}
		else if (num == 2) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
			}
		}
		else if (num == 3) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num++;
			}
			else {
				num = 0;
				s = "";
			}
		}
		else if (num == 4) {
			if (('a' <= c && c <= 'z') || ('0' <= c && c <= '9')) {
				s += c;
				num = 4;
			}
			else {
				string s1 = s + c;
				if(!(s1=="title:"||s1=="abstract:"))
					number++;
				s = "";
				num = 0;
			}
		}
	}
	if (num == 4) {
		number++;
	}

	fout << "words: " << number << endl;
	fin.close();
	fout.close();

}
