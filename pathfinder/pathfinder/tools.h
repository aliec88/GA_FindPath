#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;
inline int BinToInte(const vector<int>&bit)
{
	int val=0;
	int mul=1;
	for(int i=bit.size();i>0;i--)
	{
		val+=bit[i-1]*mul;
		mul*=2;
	}
	return val;
}
inline vector<int>Decode(const vector<int>& bit,int codelength)
{
	vector<int>temp;
	vector<int>code;
	for (int i=0;i<bit.size();i+=codelength)
	{
		for (int j=i;j<codelength+i;j++)
		{
			temp.push_back(bit[j]);
		}
		code.push_back(BinToInte(temp));
		temp.clear();
	}
	return code;
}
inline wstring itos(int i)
{
	wostringstream s;
	s<<i;
	return s.str();
}