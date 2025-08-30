#pragma once
class Boy
{
public:
	Boy(Boy* pPosition, int id);
	void leave(Boy* pPosition);
	void print();
	Boy* next();
protected:
	int code;
	Boy* pNext;
};