#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream fin1, fin2;
	ofstream fout;
	string f1 = "E:/Users/lenovo/PycharmProjects/PAPER/Eresult.txt";
	string f2 = "E:/Users/lenovo/PycharmProjects/PAPER/Only_Type.txt";
	string f3 = "result.txt";

	fin1.open(f1);
	fin2.open(f2);
	fout.open(f3, ios::out | ios::app);

	if (!fin1.is_open())
	{
		cerr << "Could not open " << f1 << endl;
		fin1.clear();
	}
	if (!fin2.is_open())
	{
		cerr << "Could not open " << f2 << endl;
		fin2.clear();
	}
	if (!fout.is_open())
	{
		cerr << "Can't open result.txt.\n";
		exit(EXIT_FAILURE);
	}


	int count = 0;
	char buffer1[3000];
	char buffer2[50];
	while (fin1.good()&&fin2.good())
	{
		fin1.getline(buffer1, 3000, '\n');
		count++;
		int i = strlen(buffer1);
		if (count % 12 == 2)
		{
			fin2.getline(buffer2, 50, '\n');
			fout <<"Type: "<< buffer2;
			fout << buffer1 << endl;
		}
		else if (count % 12 == 9)
		{
			fout << buffer1 << endl << endl<<endl;
		}
		else
		{
			if (i != 0)
			{
				fout << buffer1 << endl;
			}
		}
	}


	fin1.close();
	fin2.close();
	fout.close();
	return 0;
}