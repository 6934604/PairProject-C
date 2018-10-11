#pragma once
#include <string>
#include <iostream>
#include<fstream>
using namespace std;
int  CountLines(char *filename)
{
	int num = 0;
	ifstream in(filename);
	char word[100000];
	string a;
	while (in.getline(word, 100000))
	{   
		a = word;
		if (a.length() < 6)continue;
		num++;
	}
	return num;
}