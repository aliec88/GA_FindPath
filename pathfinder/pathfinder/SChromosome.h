#pragma once

#include <vector>
using namespace std;

struct SChromosome
{
	vector<int> m_vecGenBit;
	int m_iGenLength;
	double m_dFitness;
	SChromosome(int chromlength);
	SChromosome(){};
	void SetGenLength(int genlen){m_iGenLength=genlen;}
	int GetGenlength(){return m_iGenLength;}
};


