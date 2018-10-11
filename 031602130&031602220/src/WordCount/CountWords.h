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
	ifstream in(filename);          //  打开文件
	if (!in)
	{
		cout << "打开文件失败" << endl;
		return -1;
	}
	char word[10000];
	string ss;
	int WordNum=0;
	while (in.getline(word, 10000))    
	{
		ss = word;//这一行所有字符给ss
		for (int i = 0; i < ss.length(); i++)//对每行的操作
		{
			int count = 0;
			int charcounts = 0;
			int numflag = 0;//数字标识符，判断单词前中是否有数字
			for (int k = i;; k++)//判断是否符合需求中单词的样子
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
			if (charcounts >= 4) //若符合要求，则记录
			{
				char words[100] = { '\0' };
				for (int k = i; k < i + count; k++)
				{
					words[k - i] = ss[k];
				}
			
				WordNum++;//统计总单词数
				i += count - 1;
			}
			else if (count>0 && count<4)i += count - 1;
			else continue;
		}
	}
	return WordNum;
}