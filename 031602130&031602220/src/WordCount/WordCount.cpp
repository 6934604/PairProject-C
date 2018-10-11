#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>
#include<cassert>
#include <algorithm>
#include "Dll1.h"
#pragma comment(lib, "Dll1.lib")
#include "CountChars.h"
#include "CountLines.h"
#include "CountWF.h"
#include "CountWords.h"
#include <stdlib.h>
using namespace std;
int main(int agc, char **agv)
{
	int inflag = 0, outflag = 0;														//��������ļ���ʶ
	int quanzhong=0;																		//Ȩ�ر�ʶ��
	int lengths = 1;
	int i = 1;
	int tnum = 10;
	string a = "-i", b = "-o", c = "-w",d = "-m",e = "-n";
	while (agv[i])
	{
		if (agv[i] == a) inflag = i + 1;												//���������ļ�����
		if (agv[i] == b) outflag = i + 1;												//��������ļ�����
		if (agv[i] == c)                                                                               
		{ 
			string a = agv[i + 1]; 
			quanzhong = a[0] - '0'; 
		}
		if(agv[i] == d)lengths = atoi(agv[i + 1]);									//�������Ȳ���
		if (agv[i] == e)tnum = atoi(agv[i + 1]);
		i++;
	}
	ifstream in(agv[inflag]);	//  ���ļ�
	if (!in)
	{
		cerr << "���ļ�ʧ��" << endl;
		return -1;
	}
	ofstream fout(agv[outflag]);
	int LineNum = CountLines(agv[inflag]);
	int CharNum = CountChars(agv[inflag]);
	int WordNum = CountWords(agv[inflag]);
	fout << "characters: " << CharNum << endl << "words: " << WordNum << endl << "lines: " << LineNum << endl;
	fout.close();
	CountWF(agv[inflag],fout,agv[outflag],tnum,lengths,quanzhong);
	return 0;
}