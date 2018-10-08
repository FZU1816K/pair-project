#include "stdafx.h"
#include "Statistics.h"
using namespace std;

int main(int argc, char *argv[])
{
	int i=-1, m=-1, n=-1, w=-1, o=-1;
	for (int j = 0; j <= argc-1; j++)//��ȡ�����в���
	{
		//cout << argv[j] << endl;
		if (strcmp(argv[j], "-i") == 0)
		{
			i = j + 1;
			//cout << "i=" << i << "   " << endl;
			//cout << argv[i] << endl;
		}
		if (strcmp(argv[j], "-o") == 0)
		{
			o = j + 1;
			//cout << "o=" << o << "   " << endl;
			//cout << argv[o] << endl;
		}
		if (strcmp(argv[j], "-w") == 0)
		{
			w = atoi(argv[j + 1]);;
			//cout << "w=" << w << "   " << endl;
		}
		if (strcmp(argv[j], "-m") == 0)
		{
			m = atoi(argv[j + 1]);;
			//cout << "m=" << m << "   " << endl;
		}
		if (strcmp(argv[j], "-n") == 0)
		{
			n = atoi(argv[j + 1]);;
			//cout << "n=" << n << "   " << endl;
		}
	}
	if (o==-1||i==-1||w==-1)//�������������в����Ƿ���ȷ
	{
		cout << "�����������" << endl;
		exit(1);
	}
	ifstream infile;
	ofstream outfile;
	infile.open(argv[i], ios::in);
	if (infile.fail())
	{
		cout << "�����ļ���ʧ�ܣ�" << endl;
		exit(1);
	}
	outfile.open(argv[o], ios::out);
	if (outfile.fail())
	{
		cout << "����ļ���ʧ�ܣ�" << endl;
		exit(1);
	}
	Statistics	s;
	s.set(infile,w,m);
	s.display(outfile,n);
	infile.close();
	outfile.close();
	//system("pause");
	return 0;
}