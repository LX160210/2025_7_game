#include <iostream>
#include <iomanip>
using namespace std;
struct Boy//小孩结点
{
	int code;
	Boy* pNext;
};
//定义指针
Boy* pFirt = 0; //第一个小孩指针
Boy* pCurrent = 0; //当前小孩指针
Boy* pivot = 0;//前一个小孩指针
int numOfBoys, m;
void add() {
	//****************n 个小孩围成圆圈****************
	//游戏的初值
	cout << "please input the number of boys，\n"//小孩数
		<< " m of counting:\n"; //数小孩个数
	cin >> numOfBoys >> m;
	//在圆圈中增加第 1 个小孩
	pFirt = new Boy;
	pFirt->code = 1;
	pFirt->pNext = NULL;//后面没有小孩,
	pCurrent = pFirt;
	//依次增加其他小孩
	for (int i = 1; i < numOfBoys; i++) {
		pivot = pCurrent;//当前小孩变成前小孩
		pCurrent = new Boy;
		pCurrent->code = i + 1; //小孩编号
		pivot->pNext = pCurrent; //接到前一个小孩后面
	}
	pCurrent->pNext = pFirt;//最后一个小孩指向第一个小孩
	//输出圆圈中所有小孩
	cout << setw(4) << pFirt->code; //输出当前小孩
	pCurrent = pFirt->pNext;
	while (pCurrent != pFirt) {
		cout << setw(4) << pCurrent->code; //输出当前小孩
		pCurrent = pCurrent->pNext;
	}
	cout << endl;
}
void count() {
	//****************小孩依次离开****************
	//****当前位置设置为第一个小孩****
	pCurrent = pFirt;
	int j;
	while (pCurrent->pNext != pCurrent) { //只有一个小孩时，退出循环
		//****数到第 m 个小孩离开****
		//需要数的小孩数 j=m
		j = m;
		do {
			//当前位置调整到下一个小孩
			pivot = pCurrent; //当前小孩变成前一个小孩
			pCurrent = pCurrent->pNext;//后小孩变成当前小孩
			j--;
		} while (j > 1);//当前小孩数 1，再往后数 m-1 个
		//第 m 个小孩离开
		cout << setw(4) << pCurrent->code;
		pivot->pNext = pCurrent->pNext; //当前小孩的下一个小孩跟在他前一个的后面
		delete pCurrent; //脱离圆圈后删除
		pCurrent = pivot->pNext; //离开小孩的下一个小孩变为当前小孩
	}
}
void print() {
	//****************宣布得胜者****************
	cout << "\n\nthe winner is "
		<< pCurrent->code << endl; //获胜者
	delete pCurrent;
}
void main() {
	add();
	count();
	print();
	system("pause");
}