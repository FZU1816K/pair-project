// stdafx.cpp : source file that includes just the standard includes
// wordcount.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
//�ָ����жϲ��и��ַ���
vector<string> splitt(const string &s) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//�ҵ��ַ������׸������ڷָ�������ĸ��
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			if (isalnum(s[i]) == 0) {
				++i;
				flag = 0;
				break;
			}
		}

		//�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			if (isalnum(s[j]) == 0) {//isalnum()�ж���������Ƿ�Ϊ��ĸ��������
				flag = 1;
				break;
			}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}
//�Ƚ�
int cmp(const pair<string, int>& x, const pair<string, int>& y)
{
	if (x.second != y.second)
		return x.second > y.second;
	else {
		return x.first < y.first;//�ֵ���ǰ
	}
}
//�ַ���תСд
string mytolower(string s) {
	int len = s.size();
	//cout << len<<endl;
	for (int i = 0; i<len; i++) {
		if (s[i] >= 'A'&&s[i] <= 'Z') {
			s[i] = tolower(s[i]);
			//s[i]+=32;//+32ת��ΪСд
			//s[i]=s[i]-'A'+'a';
		}
	}
	return s;
}
//�ж��ַ����Ƿ����Ҫ��
int isstring(string c) {
	if (isdigit(c[0]) != NULL || isdigit(c[1]) != NULL || isdigit(c[2]) != NULL || isdigit(c[3]) != NULL)
		return 0;
	else
		return 1;
}

//ͳ���ַ���
int character(char* path) {
	ifstream infile;
	infile.open(path);   //���ļ����������ļ��������� 
	char c;
	int j = 0;
	int i = 0;
	int count = 0;
	string ff = ".";
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		if (c == '\n') {
			c = ' ';
		}
		ff += c;
		count++;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	count--;
	ff = mytolower(ff);
	//cout << ff;
	//cout << count << endl;
	map <string, int> m1;
	map <string, int>::iterator m1_Iter;
	vector<string> split = splitt(ff);
	for (vector<string>::size_type i = 0; i != split.size(); ++i) {
		string key = split[i];
		//cout << "before:" << key << endl;
		if (i+2<=split.size()&&split[i + 1] == "title"&&key.size() <= 3) {
			count = count - key.size()-1;
			//cout << count << endl;
		}
			
		if (m1.count(key) == 0)
		{
			m1.insert(pair <string, int>(key, 1));
		}
		else
		{
			m1[key]++;
		}
	}
	//cout << count << endl;
	count = count - m1["title"] * 17;
	//cout << count << endl;
	return count;
}
//ͳ�ƴ���/������
int word(char* path) {
	ifstream infile;
	infile.open(path);   //���ļ����������ļ��������� 
	char c;
	int i = 0;
	string ff = ".";
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		if (c == '\n') {
			c = ' ';
		}
		ff += c;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	ff = mytolower(ff);
	//cout << ff;
	int count = 0;
	int tcount = 0;
	map <string, int> m1;
	map <string, int>::iterator m1_Iter;
	vector<string> split = splitt(ff);
	for (vector<string>::size_type i = 0; i != split.size(); ++i) {
		string key = split[i];
		//cout << "before:"<<key << endl;
		if (key == "title") {
			tcount++;
		}
		if (key.size() >= 4 && isstring(key) == 1) {
			count++;
		}
	}
	count = count - 2 * tcount;
	return count;
}
//ͳ������
int line(char* path) {
	int lines = 0;
	int count = 0;
	string ff = ".";
	char c;
	int i = 0;
	int flag = 0;
	ifstream infile;
	infile.open(path);   //���ļ����������ļ��������� 
	infile >> noskipws;
	while (!infile.eof())
	{
		infile >> c;
		if (c!=' '&&c!='\0'&&c!='\n')
			flag = 1;
		if (c == '\n'&& isdigit(ff[i])==NULL) {
			if (flag==1) {
				lines++;
			}
			flag = 0;
			c = ' ';
		}
		ff += c;
		count++;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	count--;
	if (count != 0 && flag !=0) {
		lines++;
	}
	return lines;
}
//ͳ�ƴ�Ƶ�����
vector<pair<string, int>> WordsFrequency(char* path, int w, int m, int n) {
	ifstream infile;
	infile.open(path); //���ļ����������ļ��������� 
	infile >> noskipws;
	char c;
	int i = 0;
	string ff = ".";
	while (!infile.eof())
	{
		infile >> c;
		if (c == '\n') {
			c = ' ';
		}
		ff += c;
		i++;
	}
	ff[i] = '\0';
	infile.close();
	ff = mytolower(ff);
	vector<string> split = splitt(ff);
	map <string, int> m1;
	map <string, int>::iterator m1_Iter;
	vector<pair<string, int>> tVector;
	for (vector<string>::size_type i = 0; i != split.size(); ++i) {
		//cout << split[i] << endl;
		string key = split[i];
		if (key.size() >= 4 && isstring(key) == 1) {
			//cout << "�����������ַ����ǣ�" << key << endl;
			if (m1.count(key) == 0)
			{
				m1.insert(pair <string, int>(key, 1));
			}
			else
			{
				m1[key]++;
			}
		}
	}
	//map <string, int>::iterator m1_temp;
	for (map<string, int>::iterator curr = m1.begin(); curr != m1.end(); curr++)
		tVector.push_back(make_pair(curr->first, curr->second));
	sort(tVector.begin(), tVector.end(), cmp);
	return tVector;
}