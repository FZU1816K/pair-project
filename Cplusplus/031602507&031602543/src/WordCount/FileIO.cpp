#include "FileIO.h"

//����ַ���ȡ�ļ�
bool FileIO::readChar(int argc, char *argv[],const char* inputFileName,string &charBuf,vector<string> &linesBuf)
{
	string filename = inputFileName;
	ifstream rf(filename);
	if (!rf) {
		return false;
	}
	else
	{
		string tempLine;
		char c;
		while (1)
		{
			c = rf.get();
			if (c >= '0' && c <= '9')
			{
				while (c != '\n')	//�������ı��
				{
					c = rf.get();
				}
				int newLineCount = 0;	//���з�����
				while (1)
				{
					c = rf.get();
					if (c == EOF)	//�ļ�ĩβ
					{
						if (tempLine.size() > 0)
						{
							transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower);
							linesBuf.push_back(tempLine);
							tempLine = "";
						}
						break;
					}
					charBuf += c;
					tempLine += c;
					if (c == '\n')
					{
						transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower);
						linesBuf.push_back(tempLine);
						tempLine = "";
						newLineCount++;
						if (newLineCount == 2)	//һƪ���Ľ���
						{
							break;
						}
					}
				}
			}
			if (c == EOF)	//�ļ�ĩβ
			{
				if (tempLine.size() > 0)
				{
					transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower);
					linesBuf.push_back(tempLine);
				}
				break;
			}
		}
		rf.close();
		return true;
	}
}
//����ļ�
void FileIO::outputToFile(int characterCount, int wordCount,int lineCount, const char* outputFileName,vector<map<string,int>::iterator> &topX)
{
	ofstream wf(outputFileName, ios::out);
	wf << "characters: " << characterCount << endl;
	wf << "words: " << wordCount << endl;
	wf << "lines: " << lineCount << endl;
	for (int i = 0; i < int(topX.size()); i++)
	{
		if (i == 0)
		{
			wf << "<" << topX[i]->first << ">: " << -topX[i]->second;
		}
		else
		{
			wf << endl << "<" << topX[i]->first << ">: " << -topX[i]->second;
		}
	}
	wf.close();
}