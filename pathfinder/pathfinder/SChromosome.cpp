#include "stdafx.h"
#include "SChromosome.h"

SChromosome::SChromosome(int chromlength)
{
	for (int i=0;i<chromlength;i++)
	{
		m_vecGenBit.push_back(RandInt(0,1));
	}
	m_dFitness=0;

}