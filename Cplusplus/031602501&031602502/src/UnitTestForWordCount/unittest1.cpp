#include "stdafx.h"
#include "CppUnitTest.h"
#include "../WordCount/FileIO.h"
#include "../WordCount/Paper.h"
#include "../WordCount/Statistics.h"
#include "../WordCount/ArgProcessing.h"
#include<stdio.h>

#include<functional>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForWordCount
{
	TEST_CLASS(UnitTestFor_FileIO)
	{
	public:

		TEST_METHOD(TestFor_readFile)
		{
			auto fun = [this]
			{
				const char* inputfile = "aaa.txt";
				const char* outputfile = "result_test.txt";
				vector<Paper> fileContent;
				bool showInConsole = false;
				FileIO::readFile(fileContent, inputfile, showInConsole);
			};
			Assert::ExpectException<const char*>(fun);
		}
		TEST_METHOD(TestFor_writeFile)
		{
			auto fun = [this]
			{
				const char* inputfile = "empty.txt";
				const char* outputfile = "\\//\\//";
				vector<Paper> fileContent;
				int phraseLen = 1;
				bool useTitleWeight = false;
				bool showInConsole = false;
				int topNum = 10;
				Statistics st(fileContent, useTitleWeight, phraseLen);
				vector<unordered_map<string, int>::iterator> &topPhrase = st.getTopPhrase(topNum);
				FileIO::writeResult(1, 1, 1, topPhrase, outputfile, showInConsole);
			};
			Assert::ExpectException<const char*>(fun);
		}
	};
	TEST_CLASS(UnitTestFor_ArgProcessing)
	{
	public:
		TEST_METHOD(TestFor_ArgProcessingOvermuch)
		{
			auto fun = [this]
			{
				char *argv[4] = { "WordCount.exe","-i","input.txt","-n" };
				int argc = 3;
				ArgProcessing ap(argc, argv);
			};
			Assert::ExpectException<const char*>(fun);
		}
		TEST_METHOD(TestFor_ArgProcessingWrong)
		{
			auto fun = [this]
			{
				char *argv[13] = { "WordCount.exe","-i","input.txt","-m","3","-n","3","-w","1","-o","output.txt","yeah" };
				int argc = 12;
				ArgProcessing ap(argc, argv);
			};
			Assert::ExpectException<const char*>(fun);
		}
	};
	TEST_CLASS(UnitTestFor_Statistics)
	{
	public:
		TEST_METHOD(TestFor_getLineNumber)
		{
			const char* inputfile = "lines(nw)_test.txt";
			vector<Paper> fileContent;
			int phraseLen = 1;
			bool useTitleWeight = false;
			bool showInConsole = false;
			FileIO::readFile(fileContent, inputfile, showInConsole);
			Statistics st(fileContent, useTitleWeight, phraseLen);
			Assert::IsTrue(st.getLineNumber() == 2);
		}
		TEST_METHOD(TestFor_getWordNumber)
		{
			const char* inputfile = "words(nw)_test.txt";
			vector<Paper> fileContent;
			int phraseLen = 1;
			bool useTitleWeight = false;
			bool showInConsole = false;
			FileIO::readFile(fileContent, inputfile, showInConsole);
			Statistics st(fileContent, useTitleWeight, phraseLen);
			Assert::IsTrue(st.getWordNumber() == 9);
		}
		TEST_METHOD(TestFor_getCharNumber)
		{
			const char* inputfile = "char(nw)_test.txt";
			vector<Paper> fileContent;
			int phraseLen = 1;
			bool useTitleWeight = false;
			bool showInConsole = false;
			FileIO::readFile(fileContent, inputfile, showInConsole);
			Statistics st(fileContent, useTitleWeight, phraseLen);
			Assert::IsTrue(st.getCharNumber() == 74);
		}
		TEST_METHOD(TestFor_getTopPhrase_1)
		{
			const char* inputfile = "TopPhrase_3(nw)_test.txt";
			vector<Paper> fileContent;
			int topnum = 10;
			int phraseLen = 3;
			bool useTitleWeight = false;
			bool showInConsole = false;
			FileIO::readFile(fileContent, inputfile, showInConsole);
			Statistics st(fileContent, useTitleWeight, phraseLen);
			string answer[10] ={
			"abcd_abcd_abcd","abcd_abcd.then",
			"else_todo_abcd","then_else_todo","todo_abcd_abcd",
			"abcd.abcd.abcd","abcd.then,else","abcd.then_else",
			"abcd_abcd.abcd","then,else;todo"};
			int frequence[10] = {9,6,6,6,6,3,3,3,3,3};
			vector<unordered_map<string, int>::iterator> &tem = st.getTopPhrase(topnum);
			//FILE *fp = NULL;
			//fopen_s(&fp, "asd.txt", "w");
			for (int i = 0; i < 10; i++)
			{
				/*fprintf(fp, "%d\n", tem[i]->second);*/
				Assert::IsTrue(tem[i]->first == answer[i] && tem[i]->second == frequence[i]);
			}
		}
		TEST_METHOD(TestFor_getTopPhrase_2)
		{
			const char* inputfile = "Top9Phrase_1(w)_test.txt";
			vector<Paper> fileContent;
			int topnum = 10;
			int phraseLen = 1;
			bool useTitleWeight = true;
			bool showInConsole = false;
			FileIO::readFile(fileContent, inputfile, showInConsole);
			Statistics st(fileContent, useTitleWeight, phraseLen);
			string answer[9] = {
			"asdf","csdn",
			"exce","gdfr","onin",
			"prim","scan","thrx",
			"ubyv" };
			int frequence[9] = { 11,1,1,1,1,1,1,1,1};
			vector<unordered_map<string, int>::iterator> &tem = st.getTopPhrase(topnum);
			//FILE *fp = NULL;
			//fopen_s(&fp, "asd.txt", "w");

			for (int i = 0; i < 9; i++)
			{
				/*fprintf(fp, "%d\n", tem[i]->second);*/
				Assert::IsTrue(tem[i]->first == answer[i] && tem[i]->second == frequence[i]);
			}
		}
		TEST_METHOD(TestFor_getTopPhrase_3)
		{
			const char* inputfile = "Top2Phrase_3(nw)_test.txt";
			vector<Paper> fileContent;
			int topnum = 2;
			int phraseLen = 3;
			bool useTitleWeight = false;
			bool showInConsole = false;
			FileIO::readFile(fileContent, inputfile, showInConsole);
			Statistics st(fileContent, useTitleWeight, phraseLen);
			string answer[2] = {
			"abcd_abcd_abcd","abcd_abcd.then" };
			int frequence[2] = {9,6};
			vector<unordered_map<string, int>::iterator> &tem = st.getTopPhrase(topnum);
			//FILE *fp = NULL;
			//fopen_s(&fp, "asd.txt", "w");
			for (int i = 0; i < 2; i++)
			{
				/*fprintf(fp, "%d\n", tem[i]->second);*/
				Assert::IsTrue(tem[i]->first == answer[i] && tem[i]->second == frequence[i]);
			}
			Assert::IsTrue(tem.size() == topnum);
		}
	};
}