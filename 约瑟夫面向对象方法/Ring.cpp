#include "Ring.h"
#include "Boy.h"
#include <cstddef> 
Ring::Ring(int n)
{
	pFirst = pCurrent = new Boy(NULL, 1);
	Boy* pB = pFirst;
	for (int i = 2; i <= n; i++)
	{
		pB = new Boy(pB, i);
	}
}
Boy Ring::getWinner(int m)
{
	//数小孩
	while (pCurrent != pCurrent->next())
	 {
		countUpTo(m); //往下数m个小孩，数到的小孩离开
	}
	 //返回获胜者
	 Boy win(*pCurrent);
	 //另外创建(复制)一个Boy对象
	 delete pCurrent;
	 return win;
}
void Ring::countUpTo(int m)
{
	//往下数m个小孩
	Boy* pLast = 0;
	for (int i = m; i > 1; i--)
	{
		pLast = pCurrent;
		pCurrent = pCurrent->next();
	}
	//数到的小孩离开
	pCurrent->leave(pLast);//当前从圆圈中离开, pLast指向前面的小孩
	delete pCurrent;//删除当前小孩
	pCurrent = pLast->next();//当前小孩是上一个小孩的下一个
}
Ring::~Ring(){}