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
	cout << endl << "请输出小孩数和间隔数......" << endl; 
	cin >> n >> m;
	Jose js2(n, m); 
	js2.gameBegin().print();
	cout << endl << "现在宣布" << endl << "第一场获胜者是：" << endl;
	js1.gameBegin().print(); 
	cout << endl << "第二场获胜者是：" << endl;
	js2.gameBegin().print();
	return 0;
	system("pause");
}