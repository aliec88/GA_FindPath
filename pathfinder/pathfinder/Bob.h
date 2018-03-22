#pragma once
#include "MazeMap.h"
#include "GA.h"
class CBob
{
private:
	CMazeMap* m_pMazeMap;
	CGA* m_pCGA;
	bool m_bBusy;

public:
	CBob(void);
	~CBob(void);
	void SetBusy(bool busy){m_bBusy=busy;}
	bool GetBusy(){return m_bBusy;}
	CMazeMap* GetMazeMap(){return m_pMazeMap;}
	void Render(int width,int height,HDC surface);
	bool Run(HWND hwnd);
};

