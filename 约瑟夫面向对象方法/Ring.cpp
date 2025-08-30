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
	//��С��
	while (pCurrent != pCurrent->next())
	 {
		countUpTo(m); //������m��С����������С���뿪
	}
	 //���ػ�ʤ��
	 Boy win(*pCurrent);
	 //���ⴴ��(����)һ��Boy����
	 delete pCurrent;
	 return win;
}
void Ring::countUpTo(int m)
{
	//������m��С��
	Boy* pLast = 0;
	for (int i = m; i > 1; i--)
	{
		pLast = pCurrent;
		pCurrent = pCurrent->next();
	}
	//������С���뿪
	pCurrent->leave(pLast);//��ǰ��ԲȦ���뿪, pLastָ��ǰ���С��
	delete pCurrent;//ɾ����ǰС��
	pCurrent = pLast->next();//��ǰС������һ��С������һ��
}
Ring::~Ring(){}