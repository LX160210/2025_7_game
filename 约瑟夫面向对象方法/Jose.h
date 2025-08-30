#pragma once
#include "Ring.h"
#include "Boy.h"
class Jose
{
public:
	Jose(int boys, int interval);
	~Jose();
	Boy gameBegin();
private:
	int numOfBoys;
	int m;
	Ring* ring;
	Boy* win;
};