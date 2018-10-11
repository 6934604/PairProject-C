#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<cassert>
#include <algorithm>
#include <list>
using namespace std;
int K;
map<string, int> essay;
list<string> b('\0');
list<string>::iterator it1;
bool cmp(int a, int b)
{
	return a>b;
}
void Count(string tline, int maxn, int start,int quanzhong)
{
	for (int i = start; i < tline.length(); i++)
	{
		int count = 0;//计数
		int charcounts = 0;//字符数
		int numflag = 0;//判断是否数字
		for (int k = i;; k++)//判断是否是单词
		{
			if (tline[k] >= 'a'&&tline[k] <= 'z'&&numflag == 0)
			{charcounts++;count++;}//小写字母
			else if (tline[k] >= 'A'&&tline[k] <= 'Z'&&numflag == 0)
			{charcounts++;count++;}//大写字母
			else if (tline[k] >= '0'&&tline[k] <= '9')
			{count++;numflag = 1;}//出现数字
			else break;
		}
		if (charcounts >= 4) //记录
		{	char words[100] = { "\0" };
		//存储单词
			for (int k = i; k < i + count; k++)
			{
				words[k - i] = tline[k];
			}
			string s = words;
			b.push_back(s);  
			s = "\0";
			if (b.size() == maxn)//队列以满
			{
				int nowNum = maxn;
				for (it1 = b.begin(); it1 != b.end(); it1++)
				{
					s.append(*it1);
					nowNum=nowNum-1;
					if (nowNum != 0)s.append(" ");
				}
				if(start==7&&quanzhong==1)essay[s]+=10;//记录
				else essay[s]++;
				b.pop_front();
				s = "\0";
			}
			i += count - 1;
		}
		else if (count > 0 && count < 4)
		{
			b.clear();
			i += count - 1;
		}
		else continue;
	}
	if (start == 7)b.clear();//清空
}
void adjustDown(vector<map<string, int>::iterator> &top, int i)	
{
	int min = i;
	int child = 2 * min + 1;
	while (i < K / 2)
	{
		if ((child + 1 < K) && (top[child]->second > top[child + 1]->second))
			child++;
		if ((child<K) && (top[min]->second>top[child]->second))
		{
			swap(top[min], top[child]);
			min = child;
			child = 2 * min + 1;
		}
		else
			break;
	}
}
void topK(map<string, int> &essay, vector<map<string, int>::iterator> &top, ofstream &fout,char *filename)
{
	auto it = essay.begin();
	for (int i = 0; i < K; i++)
	{
		top[i] = it;
		it++;
	}
	//  建立小根堆
	for (int i = K / 2 - 1; i >= 0; i--)
	{
		adjustDown(top, i);
	}
	//  取topK
	while (it != essay.end())
	{
		if (it->second > top[0]->second)
		{
			top[0] = it;                     //  大于堆顶元素，则入堆；
			adjustDown(top, 0);              //  重新调整为小根堆；

		}
		it++;
	}
	int a[10000];
	string b[10000];
	for (int i = K - 1; i >= 0; i--)
	{
		a[i] = essay[top[0]->first];
		b[i] = top[0]->first;
		top[0]->second = 100000;
		adjustDown(top, 0);              //  重新调整为小根堆；
	}
	sort(a, a + K, cmp);
	fout.open(filename, ios::app);
	for (int i = 0; i < K; i++)
	{
		fout << "<" << b[i] << ">: " << a[i] << endl;
	}
	fout.close();
}
void CountWF(char *filename, ofstream &fout,char* outfile,int tnum,int maxn,int weigth_Pid)
{
	int num = 0;
	K = tnum;
	ifstream in(filename);          //  打开文件
	if (!in)
	{
		cerr << "打开文件失败" << endl;
		exit(0);
	}
	char rLine[10000];
	string tline;

	list<string> listString;
	while (in.getline(rLine, 10000))
	{

		tline = rLine;//存储当前行的字符串
		if (tline.length()<6)
		{
			b.clear();
			continue;
		}
		else if (rLine[0] == 'T'&&rLine[1] == 'i'&&rLine[2] == 't'&&rLine[3] == 'l'&&rLine[4] == 'e')
		{
			Count(tline, maxn, 7,weigth_Pid);
		}
		else if (rLine[0] == 'A'&&rLine[1] == 'b'&&rLine[2] == 's'&&rLine[3] == 't'&&rLine[4] == 'r'&&rLine[5] == 'a'&&rLine[6] == 'c'&&rLine[7] == 't')
		{
			Count(tline, maxn, 10, weigth_Pid);
		}
		else if(rLine)
		{
			Count(tline, maxn, 0,weigth_Pid);
		}
	}
	if (essay.size() < K)K = essay.size();
	vector < map<string, int> ::iterator> top(K, essay.begin());
	topK(essay, top, fout,outfile);

}