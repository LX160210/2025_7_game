#include "Ring.h"
#include "Boy.h"
#include "Jose.h"
#include <cstddef>
Jose::Jose(int boys, int interval)
{
	numOfBoys = boys;
	m = interval;
	ring = new Ring(boys);
	win = NULL;
}
Jose::~Jose()
{
	delete ring;
	delete win;
}
Boy Jose::gameBegin()
{
	if (!win)win = new Boy(ring->getWinner(m));
	return *win;
}
