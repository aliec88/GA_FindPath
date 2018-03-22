#pragma once
#include "stdafx.h"
#include "SChromosome.h"
class CGA
{
private:
	vector<SChromosome*>m_vecPopulation;
	vector<SChromosome*>m_vecBaby;
	int m_iChromLength;
	int m_iMaxPopulation;
	double m_dTotalFitness;
	double m_dCrossoverRate;
	double m_dMutationRate;
public:
	CGA(int ChromLength,int MaxPopulation,double CrossOverRate,double MutationRate);
	~CGA(void);
	static int EPOCHTIME; 
private:
	void SetChromLength(int length){m_iChromLength=length;}
	void CreatePopulation(int maxPopulation);
	void DeletePopulation();
	void UpdateAllFitness();
	SChromosome* SelectChromosome();
	void CrossOverAndMutation(SChromosome* pMum,SChromosome* pDad);
	void Mutation(SChromosome*pChrom);
	
public:
	void Epoch();
	vector<SChromosome*>GetPopulation(){return m_vecPopulation;}
};

