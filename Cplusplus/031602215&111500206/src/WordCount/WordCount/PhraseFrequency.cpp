#include "PhraseFrequency.h"

deque<string> q_phrase;
extern int phraseLength;

/*We present a new AI task -- Embodied Question Answering (EmbodiedQA) -- where an agent is spawned at a random location in a 3D environment*/

int TransitionStorePhrase(int state, char input, string & word, int TitleorAbstract)
{
	switch (state)
	{
	case OUTWORD:
		if (Separator(input)) return OUTWORD;
		if (isalpha(input)) { word += input; return P1; }
		if (IsNum(input)) return NotAWord;

	case NotAWord:
		q_phrase.clear();
		if (Separator(input)) return OUTWORD;
		else return NotAWord;

	case P1:
		if (IsNum(input)) { word.clear(); return NotAWord; }
		if (isalpha(input)) { word += input; return  P2; }
		else { word.clear(); q_phrase.clear(); return OUTWORD; }

	case P2:
		if (IsNum(input)) { word.clear(); return NotAWord; }
		if (isalpha(input)) { word += input; return  P3; }
		else { word.clear(); q_phrase.clear(); return OUTWORD; }

	case P3:
		if (IsNum(input)) { word.clear(); return NotAWord; }
		if (isalpha(input)) { word += input; return VALIDWORD; }
		else { word.clear(); q_phrase.clear(); return OUTWORD; }

	case VALIDWORD:
		if (isalnum(input)) { word += input; return VALIDWORD; }
		else {
			string phrase = ConstructPhrase(word); // ���Թ��ɴ��� 
			if (phrase != ""){ // �����Թ��ɴ��飬�ͺ�����һ�������ϣ����
				InsertToHashTable(phrase, TitleorAbstract);
			}
			word.clear();
			return OUTWORD;
		}
	}
	return ERRORSTATE;
}

string ConstructPhrase(string & word) // ���Թ���һ�����飬����Ϊ phraseLength
{
	q_phrase.push_back(word);
	string phrase = "";
	if (q_phrase.size() == phraseLength) // ������������� phraseLength �� word����ȡ��һ������
	{
		string top;
		for (int i = 0; i < phraseLength; i++)
		{
			top = q_phrase.front();
			phrase += top;
			if (i != phraseLength - 1)
				phrase += " "; // todo : �洢�ָ���
			q_phrase.pop_front();
			q_phrase.push_back(top);
		}
		q_phrase.pop_front();
		return phrase;
	}
	else 
		return phrase; // û������һ�����ӣ���ζ�Ų���ȡ��һ��phrase���᷵��һ����string
}

void PhraseFrequency(string line, int TitleorAbstract)
{
	string word;
	char c;
	int state = OUTWORD;
	int i = 0;
	while ((c = line[i]) != '\0' && state != ERRORSTATE) {
		if (!(c >= 1 && c <= 255)) //non - ascii character
		{
			state = OUTWORD;
			i++;
			continue;
		}
		c = tolower(c);
		state = TransitionStorePhrase(state, c, word, TitleorAbstract);
		i++;
	}
	if (state == VALIDWORD) {
		string phrase = ConstructPhrase(word);
		if (phrase != "") {
			InsertToHashTable(phrase, TitleorAbstract);
		}
	}
}
