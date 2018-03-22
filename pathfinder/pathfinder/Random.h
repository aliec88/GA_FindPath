#pragma once
#include <time.h>
#include <stdlib.h>

inline int RandInt(int i,int j)
{
	//srand((unsigned)time(NULL));
	return rand()%(j-i+1)+i;
}
inline double RandDouble()
{
	//srand((unsigned)time(NULL));
	return rand()/(double)(RAND_MAX);
}
	 