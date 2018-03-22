#include "StdAfx.h"
#include "MazeMap.h"
#include "tools.h"
#include "GA.h"


const int CMazeMap::MAZEMAP[MAZEWIDTH][MAZEHEIGHT]=
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,
	8,0,0,0,1,1,1,0,0,1,1,1,1,1,1,0,1,0,1,1,
	1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,
	1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,0,0,0,1,1,0,1,0,0,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
	1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,1,
	1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,
	1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,
	1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1,
	1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,1,1,
	1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,
	1,1,1,0,0,1,1,1,1,1,1,0,1,0,1,0,0,0,0,1,
	1,0,0,0,1,1,0,1,1,1,1,0,1,0,1,0,0,1,1,1,
	1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,0,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};
//const int CMazeMap::MAZEMAP[MAZEWIDTH][MAZEHEIGHT]=
//{	
//	1,1,1,1,1,1,1,1,1,1,
//	8,0,0,0,0,1,1,0,0,1,
//	1,0,0,0,0,1,1,0,0,1,
//	1,1,1,0,0,0,0,0,0,1,
//	1,1,1,0,0,1,1,1,1,1,
//	1,0,0,0,1,1,0,1,1,1,
//	1,0,1,1,1,1,0,1,0,1,
//	1,0,0,0,0,0,0,0,0,5,
//	1,1,1,1,0,0,1,1,0,1,
//	1,1,1,1,1,1,1,1,1,1
//
//};

const int CMazeMap::xStart=XSTART;

const int CMazeMap::yStart=YSTART;

const int CMazeMap::xEnd=XEND;

const int CMazeMap::yEnd=YEND;

CMazeMap::CMazeMap(void)
{
	ResetMem();
}


CMazeMap::~CMazeMap(void)
{
}

void CMazeMap::ResetMem()
{
	for (int i=0;i<MAZEWIDTH;i++)
	{
		for (int j=0;j<MAZEHEIGHT;j++)
		{
			memory[i][j]=0;
		}
	}
}

void CMazeMap::RenderMap(int width,int height,HDC surface)
{
	HPEN hNullPen=(HPEN)GetStockObject(NULL_PEN);	
	HBRUSH hBlackBrush=(HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH hRedBrush=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	HBRUSH hGrayBrush=(HBRUSH)GetStockObject(GRAY_BRUSH);
	HPEN hOldPen=(HPEN)SelectObject(surface,hNullPen);
	HBRUSH hOldBrush;
	int border=40;
	int blockWidth=(width-2*border)/MAZEWIDTH;
	int blockHeight=(height-2*border)/MAZEHEIGHT;
	for (int i=0;i<MAZEWIDTH;i++)
	{
		for (int j=0;j<MAZEHEIGHT;j++)
		{
			int blockX=border+blockWidth*i;
			int blockY=border+blockHeight*j;
			int blockRight=blockX+blockWidth;
			int blockBottom=blockY+blockHeight;
			if (MAZEMAP[j][i]==1)
			{
				hOldBrush=(HBRUSH)SelectObject(surface,hBlackBrush);
				Rectangle(surface,blockX,blockY,blockRight,blockBottom);
			}
			if (MAZEMAP[j][i]==5 || MAZEMAP[j][i]==8)
			{
				hOldBrush=(HBRUSH)SelectObject(surface,hRedBrush);
				Rectangle(surface,blockX,blockY,blockRight,blockBottom);

			}
			if (memory[j][i]==1)
			{
				hOldBrush=(HBRUSH)SelectObject(surface,hGrayBrush);
				Rectangle(surface,blockX,blockY,blockRight,blockBottom);

			}
		}
	}
	wstring s=TEXT("按回车键重新开始");
	TextOut(surface,width/2-s.size()*10,height-border,s.c_str(),s.size());
	wstring times=TEXT("已经进化了")+itos(CGA::EPOCHTIME)+TEXT("个时代");
	TextOut(surface,border,height-border*2-blockHeight*20,times.c_str(),times.size());
	SelectObject(surface,hOldPen);
	SelectObject(surface,hOldBrush);
	DeleteObject(hNullPen);
	DeleteObject(hBlackBrush);
}

bool CMazeMap::TestRoute(SChromosome* pChrom)
{
	ResetMem();
	int genlength=pChrom->GetGenlength();
	vector<int> path=Decode(pChrom->m_vecGenBit,genlength);
	int Xmem=yStart;
	int Ymem=xStart;
	for (int i=0;i<path.size();i++)
	{
		switch(path[i])
		{
		case 0:
			{
				if ((Ymem-1)<0 || MAZEMAP[Xmem][Ymem-1]==1)
				{
					break;
				}else
				{
					Ymem--;
				}
			}
			break;
		case 1:
			{
				if ((Ymem+1)>=MAZEHEIGHT || MAZEMAP[Xmem][Ymem+1]==1)
				{
					break;
				}else
				{
					Ymem++;
				}
			}
			break;
		case 2:
			{
				if ((Xmem-1)<0 || MAZEMAP[Xmem-1][Ymem]==1)
				{
					break;
				} 
				else
				{
					Xmem--;
				}
			}
			break;
		case 3:
			{
				if ((Xmem+1)>=MAZEWIDTH || MAZEMAP[Xmem+1][Ymem]==1)
				{
					break;
				} 
				else
				{
					Xmem++;
				}
			}
			break;
		}
		memory[Xmem][Ymem]=1;

		if (abs(Xmem-yEnd)==0 && abs(Ymem-xEnd)==0)
		{
			//MessageBox(0,itos(Ymem).c_str(),itos(Xmem).c_str(),0);
			break;
		}
	}
	//MessageBox(0,itos(Ymem).c_str(),itos(Xmem).c_str(),0);

	int DiffX=abs(Xmem-yEnd);
	int Diffy=abs(Ymem-xEnd);
	pChrom->m_dFitness=1/(double)(DiffX+Diffy+1);
	if (pChrom->m_dFitness==1.0)
	{
		//MessageBox(0,itos(Ymem).c_str(),itos(Xmem).c_str(),0);
		return true;
	}else
	{
		return false;
	}
}
