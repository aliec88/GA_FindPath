#pragma once
#include "stdafx.h"
#include "SChromosome.h"
class CMazeMap
{
private:
	static const int MAZEMAP[MAZEWIDTH][MAZEHEIGHT];
	static const int xStart;
	static const int yStart;
	static const int xEnd;
	static const int yEnd;
	int memory[MAZEWIDTH][MAZEHEIGHT];
public:
	CMazeMap(void);
	~CMazeMap(void);
	void ResetMem();
	void RenderMap(int width,int height,HDC surface);
	bool TestRoute(SChromosome* pChrom);

};

