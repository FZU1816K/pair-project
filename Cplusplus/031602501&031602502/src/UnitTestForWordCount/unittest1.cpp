#include "stdafx.h"
#include "CppUnitTest.h"
#include "../WordCount/FileIO.h"
#include "../WordCount/Paper.h"
#include "../WordCount/Statistics.h"
#include "../WordCount/ArgProcessing.h"

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
		TEST_METHOD(TestFor_getTopPhrase)
		{
			const char* inputfile = "TopPhrase(nw)_test.txt";
			vector<Paper> fileContent;
			int phraseLen = 1;
			bool useTitleWeight = false;
			bool showInConsole = false;
			FileIO::readFile(fileContent, inputfile, showInConsole);
			Statistics st(fileContent, useTitleWeight, phraseLen);

			Assert::IsTrue(st.getCharNumber() == 74);
		}

	};
}