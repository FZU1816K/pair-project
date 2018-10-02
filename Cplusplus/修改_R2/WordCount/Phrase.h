/**
 * File name: Phrase.cpp
 * Description: COUNT phrases
 * Function List:
	bool Get_Empty(); //for UnitTest,Judge the word_v is empty or not
	int Get()         //for UnitTest
	void Fwrite();    //Write result into file
	void PS();        //Count file's phrases and SORT frequence
	void Show();      //Show result in screen
 */
#ifndef PHRASE_H_
#define PHRASE_H_
#include<map>
#include<vector>
#include<string>

typedef std::pair<std::string, int> PAIR;

class Psort
{
private:
	std::string finname;
	std::string foutname;
	std::vector<PAIR>phrase_v;  //story phrase(sequenced)
	int len;                    //argument, the length of phrase(how many words)
	int num;                    //TOP n

public:

	Psort(std::string filein, std::string fileout, int length, int number);
	Psort();
	/*************************************************/
	///////////////////FOR UnitTest////////////////////
	bool Get_Empty();
	int Get();
	/*************************************************/
	void Fwrite();
	void PS();
	void Show();
};

#endif
