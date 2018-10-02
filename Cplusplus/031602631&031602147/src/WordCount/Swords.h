/**
 * File name: Swords.cpp
 * Description: COUNT words
 * Function List:
    bool Get_Empty(); //for UnitTest,Judge the word_v is empty or not
	int Get()         //for UnitTest
	void Fwrite();    //Write result into file
	void CS();        //Count file's words and SORT frequence
	void Show();      //Show result in screen
 */
#ifndef SWORDS_H_
#define SWORDS_H_
#include<map>
#include<vector>
#include<string>

typedef std::pair<std::string, int> PAIR;

class Wsort
{
private:
	std::string finname;
	std::string foutname;
	std::vector<PAIR> word_v; //story words(sequenced)
	int weight;               //weight
	int num;                  //TOP n

public:

	Wsort(std::string filein, std::string fileout, int w,int number);
	Wsort();
	/*************************************************/
	///////////////////FOR UnitTest////////////////////
	bool Get_Empty();
	int Get();
	/*************************************************/
	void Fwrite();
	void CS();
	void Show();
};

#endif
