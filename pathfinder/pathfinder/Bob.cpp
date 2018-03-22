#include "StdAfx.h"
#include "Bob.h"


CBob::CBob(void)
{
	m_pMazeMap=new CMazeMap();
	m_pCGA=new CGA(CHROLENGTH,POPULATION,CROSSOVER_RATE,MUTATION_RATE);
	m_bBusy=false;
}


CBob::~CBob(void)
{
	delete m_pMazeMap;
	delete m_pCGA;
	CGA::EPOCHTIME=0;
}

void CBob::Render(int width,int height,HDC surface)
{
	m_pMazeMap->RenderMap(width,height,surface);
}

bool CBob::Run(HWND hwnd)
{
	bool find=false;
	int k=m_pCGA->GetPopulation().size();
	for (int i=0;i<k;i++)
	{
		SChromosome* p=m_pCGA->GetPopulation().at(i);
		find=m_pMazeMap->TestRoute(p);
		InvalidateRect(hwnd,NULL,TRUE);
		UpdateWindow(hwnd);
		if(find==true)
		{
			break;
		}	
	}
	if (find==true)
	{
		return true;
	}else
	{
		m_pCGA->Epoch();
		return false;
	}
	
}

