#include"CountLine.h"

int CountLine(string filename)
{
	ifstream File;
	int n = 0;
	string temp;
	File.open(filename, ios::in);//ios::in ��ʾ��ֻ���ķ�ʽ��ȡ�ļ�
	if (File.fail())//�ļ���ʧ��:����0
	{
		return -1;
	}
	else//�ļ�����
	{
		while (getline(File, temp))
		{   //   if(temp[0]!='\n')
		//  ʵ��վ	cout << temp[0] << endl;
			n++;
		}
		return n - ((n+2) / 5) * 3;
	}
	File.close();

}