#include "pch.h"
#include "work_2.h"
int hash_index(string word_str)
{
	int value = 0, i = 0;
	int length = word_str.length();
	for (i = 0; i < 4; i++)
	{
		value = (29 * value + word_str[i]) % HASH_LENGTH;//��ϣɢ��
		//cout << value << endl;
	}
	return value;
}
void hash_insert(Wordnode **l, string word_str,int weight_flag)
{
	int value = hash_index(word_str);					//�����ϣֵ
	Wordnode *p;
	//cout << value;
	for (p = l[value]; p != NULL; p = p->next)			//���ҽڵ㲢����
	{
		if (word_str == p->word)						//���нڵ����(�ظ�����)
		{
			p->count += 1 + weight_flag * 9;
			return;
		}
	}
	p = new Wordnode;									//δ�нڵ����(�µ���)
	p->count = 1 + weight_flag * 9;
	p->word = word_str;
	p->next = l[value];
	l[value] = p;
}



void rank_word(Wordnode **l, Words &nw,File &fl)
{
	int i = 0, j = 0, max = 0;
	Wordnode *p, *max_node = NULL;
	for (j = 1; j <= fl.count_n; j++)							//����ǰn��Ƶ
	{
		for (i = 0; i < HASH_LENGTH; i++)
		{
			for (p = l[i]; p != NULL; p = p->next)		//������ϣ��
			{
				if (p->count > max)
				{
					max = p->count;
					max_node = p;
					nw.count_rank[j] = max;
					nw.word_rank[j] = p->word;
				}
				else if (p->count == max && p->word < nw.word_rank[j])
				{
					max_node = p;
					nw.word_rank[j] = p->word;
				}
			}
		}
		if (max == -1)									//������������ʮ�����
			break;
		if (max_node != NULL)
			max_node->count = -1;
		max = 0;
	}
}