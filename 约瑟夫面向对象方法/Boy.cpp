#include"Boy.h"
#include <iostream>
using namespace std;
Boy::Boy(Boy* pPosition, int id)
{
	code = id;
	if (!pPosition)
	{
		this->pNext = this;//只有一个小孩时，自己指向自己
	}else
	{
		this->pNext = pPosition->pNext; // 插入到小孩*pPosition的后面
		pPosition->pNext = this; //与上一条不能交换
	}
}
void Boy::leave(Boy* pPosition)
{
	pPosition->pNext = this->pNext;
	cout << "离开：" << code << endl;
}
void Boy::print() 
{
	cout << "Id:" << code; 
}
Boy* Boy::next()
{
	return pNext;
}