#include "stdafx.h"

#include "GA.h"


CGA::CGA(int ChromLength,int MaxPopulation,double CrossOverRate,double MutationRate)
{
	m_iChromLength=ChromLength;
	m_iMaxPopulation=MaxPopulation;
	m_dCrossoverRate=CrossOverRate;
	m_dMutationRate=MutationRate;
	CreatePopulation(m_iMaxPopulation);
	m_dTotalFitness=0;
}

CGA::~CGA(void)
{
	DeletePopulation();
}

int CGA::EPOCHTIME=0;

void CGA::CreatePopulation(int maxPopulation)
{
	for (int i=0;i<maxPopulation;i++)
	{
		SChromosome* s=new SChromosome(m_iChromLength);
		s->SetGenLength(GENLENGTH);
		m_vecPopulation.push_back(s);
	}
}

void CGA::DeletePopulation()
{
	for (int i=0;i<m_vecPopulation.size();i++)
	{
		delete m_vecPopulation[i];
	}
	m_vecPopulation.clear();
}

void CGA::UpdateAllFitness()
{
	for (int i=0;i<m_vecPopulation.size();i++)
	{
		m_dTotalFitness+=m_vecPopulation.at(i)->m_dFitness;
	}
}

SChromosome* CGA::SelectChromosome()
{
	/*double slice=RandDouble()*m_dTotalFitness;
	int pos1;
	vector<int>pos2;
	pos2.push_back(-1);
	vector<int>::iterator it;
	double total=0;
	for(int i=0;i<m_vecPopulation.size();i++)
	{		
		pos1=RandInt(0,m_vecPopulation.size()-1);
		it=find(pos2.begin(),pos2.end(),pos1);
		if (it==pos2.end())
		{
			pos2.push_back(pos1);		
			total+=m_vecPopulation[pos1]->m_dFitness;
			if (total>slice)
			{
				return m_vecPopulation[pos1];
			}
		}		
	}
	return NULL;*/
	double slice=RandDouble()*m_dTotalFitness;
	double total=0.0;
	for (int i=0;i<m_vecPopulation.size();i++)
	{
		total+=m_vecPopulation[i]->m_dFitness;
		if (total>slice)
		{
			return m_vecPopulation[i];
		}
	}
	return NULL;
}

void CGA::CrossOverAndMutation(SChromosome* pMum,SChromosome* pDad)
{
	SChromosome* pBaby1=new SChromosome();
	SChromosome* pBaby2=new SChromosome();
	pBaby1->m_dFitness=0;
	pBaby2->m_dFitness=0;
	pBaby1->SetGenLength(GENLENGTH);
	pBaby2->SetGenLength(GENLENGTH);

	if (RandDouble()>m_dCrossoverRate || pMum->m_vecGenBit==pDad->m_vecGenBit)
	{
		pBaby1->m_vecGenBit=pMum->m_vecGenBit;
		pBaby2->m_vecGenBit=pDad->m_vecGenBit;
	}else
	{
		int p=RandInt(0,m_iChromLength-1);
		for (int i=0;i<p;i++)
		{
			pBaby1->m_vecGenBit.push_back(pMum->m_vecGenBit[i]) ;
			pBaby2->m_vecGenBit.push_back(pDad->m_vecGenBit[i])  ;
		}
		for (int j=p;j<m_iChromLength;j++)
		{
			pBaby1->m_vecGenBit.push_back(pDad->m_vecGenBit[j]);
			pBaby2->m_vecGenBit.push_back(pMum->m_vecGenBit[j]);
		}
	}
	Mutation(pBaby1);
	Mutation(pBaby2);
	m_vecBaby.push_back(pBaby1);
	m_vecBaby.push_back(pBaby2);
}

void CGA::Mutation(SChromosome*pChrom)
{
	for (int i=0;i<pChrom->m_vecGenBit.size();i++)
	{
		if (RandDouble()<m_dMutationRate)
		{
			pChrom->m_vecGenBit[i]=!pChrom->m_vecGenBit[i];
		}
	}
}

void CGA::Epoch()
{
	UpdateAllFitness();
	SChromosome* pMum;
	SChromosome* pDad;
	while(m_vecBaby.size()<m_vecPopulation.size())
	{
		pMum=SelectChromosome();
		pDad=SelectChromosome();
		if(pDad!=NULL && pMum!=NULL)
		{
			CrossOverAndMutation(pMum,pDad);			
		}
		int k=m_vecBaby.size();

	}
	DeletePopulation();
	m_vecPopulation=m_vecBaby;	
	m_vecBaby.clear();
	EPOCHTIME++;
}
