#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<cctype>
#include<algorithm>
#include<vector>

using namespace std;


typedef pair<string, int> PAIR;

struct CmpByValue 
{
	bool operator()(const PAIR& lhs, const PAIR& rhs) 
	{
		return lhs.second > rhs.second;
	}
};

int main()
{
	std::map<std::string, size_t> word_count;

	ifstream fin;
	string finname = "E:/Users/lenovo/Source/repos/university/Authors.txt";
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
	string university;
	char c;
	int flag1 = 0;          //ÓÃÀ´ÅÐ¶ÏÆ¥ÅäµÄÀ¨ºÅÊý
	int flag2 = 0;
	fin >> noskipws;
	while (fin.good())
	{
		fin >> c;
		if (c == '(' && flag1 == 0)
			flag1++;
		else if (c == '(' && flag1 == 1)
		{
			flag2++;
			int t = university.find(", ");
			if (t != string::npos)
			{
				string u1 = university.substr(0, t);
				string u2 = university.substr(t + 2, university.size()-t-2);
				if (u1.size() && u1.find(" ")!= string::npos)
					word_count[u1]++;
				if (u2.size() && u2.find(" ") != string::npos)
					word_count[u2]++;
			}
			else if(university.size() && university.find(" ") != string::npos)
				word_count[university]++;
			university = "";
		}
		else if (c == ')' && flag2 != 0)
		{
			flag2--;
			university = "";
		}
		else if (c == ')' && flag1 != 0)
		{
			flag1--;
			int t = university.find(", ");
			if (t != string::npos)
			{
				string u1 = university.substr(0, t);
				string u2 = university.substr(t + 2);
				if (u1.size() && u1.find(" ") != string::npos)
					word_count[u1]++;
				if (u2.size() && u2.find(" ") != string::npos)
					word_count[u2]++;
			}
			else if(university.size() && university.find(" ") != string::npos)
				word_count[university]++;
			university = "";
		}
		else
		{
			if (flag1 != 0)
				university.push_back(c);
		}
	}
	if (fin.eof())
		printf("End of the file.\n");
	else if (fin.fail())
		printf("Input terminated by data mismatch.\n");
	else
		printf("Input terminated for unknown reason.\n");
	fin.close();


	//*********ÅÅÐò**********//
	vector<PAIR> word_v;

	vector<pair<string, int>>word_v1(word_count.begin(), word_count.end());
	sort(word_v1.begin(), word_v1.end(), CmpByValue());
	word_v = word_v1;


	////*********Ð´Èë**********//
	ofstream fout;
	string foutname = "2018University_rank2.txt";
	fout.open(foutname, ios::out | ios::app); //×·¼Ó
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < word_v.size() && i < 10; i++)
		fout << "<" << word_v.at(i).first << ">: " << word_v.at(i).second << endl;
	fout.close();


	return 0;
}