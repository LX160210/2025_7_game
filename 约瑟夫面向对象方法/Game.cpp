#include "Ring.h"
#include "Boy.h"
#include "Jose.h"
#include <iostream>
using namespace std;
int main()
{
	Jose js1(7, 3);
	js1.gameBegin().print();
	int m, n;
	cout << endl << "�����С�����ͼ����......" << endl; 
	cin >> n >> m;
	Jose js2(n, m); 
	js2.gameBegin().print();
	cout << endl << "��������" << endl << "��һ����ʤ���ǣ�" << endl;
	js1.gameBegin().print(); 
	cout << endl << "�ڶ�����ʤ���ǣ�" << endl;
	js2.gameBegin().print();
	return 0;
	system("pause");
}