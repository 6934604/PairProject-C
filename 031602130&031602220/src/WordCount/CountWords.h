#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cassert>
#include <algorithm>

using namespace std;
int CountWords(char *filename)
{
	ifstream in(filename);          //  ���ļ�
	if (!in)
	{
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}
	char word[10000];
	string ss;
	int WordNum=0;
	while (in.getline(word, 10000))    
	{
		ss = word;//��һ�������ַ���ss
		for (int i = 0; i < ss.length(); i++)//��ÿ�еĲ���
		{
			int count = 0;
			int charcounts = 0;
			int numflag = 0;//���ֱ�ʶ�����жϵ���ǰ���Ƿ�������
			for (int k = i;; k++)//�ж��Ƿ���������е��ʵ�����
			{
				if (ss[k] >= 'a'&&ss[k] <= 'z'&&numflag == 0)
				{
					charcounts++;
					count++;
				}
				else if (ss[k] >= 'A'&&ss[k] <= 'Z'&&numflag == 0)
				{
					charcounts++;
					count++;
				}
				else if (ss[k] >= '0'&&ss[k] <= '9')
				{
					count++; 
					numflag = 1;
					charcounts++;
				}
				else if (ss[k] == ':')
				{
					count++;
					charcounts=0;
				}
				else break;
			}
			if (charcounts >= 4) //������Ҫ�����¼
			{
				char words[100] = { '\0' };
				for (int k = i; k < i + count; k++)
				{
					words[k - i] = ss[k];
				}
			
				WordNum++;//ͳ���ܵ�����
				i += count - 1;
			}
			else if (count>0 && count<4)i += count - 1;
			else continue;
		}
	}
	return WordNum;
}