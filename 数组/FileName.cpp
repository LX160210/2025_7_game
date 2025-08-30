#include <iostream>
using namespace std;
void main() {
	//n 个小孩围成圆圈
	const int numOfBoy = 7; //小孩总数
	int boy[numOfBoy]; //小孩数组
	int i;
	for (i = 0; i < numOfBoy; i++)//从 1 开始给小孩编号
		boy[i] = i + 1;
	//输入数小孩间隔
	int m; //Josephus 问题中的间隔 m
	cout << "please input the interval: ";
	cin >> m;
	//输出开始时的小孩编号
	for (i = 0; i < numOfBoy; i++)
		cout << boy[i] << "，";
	cout << endl;
	//小孩依次离开
	i = 0; //当前位置 i 设置为第一个小孩
	int n = numOfBoy; //离开小孩的个数
	while (n > 1) {//只剩一个小孩
		//数到第 m 个小孩离开
		int j = m;
		do {
			//当前位置 i 调整到下一个小孩
			i = (i + 1) % numOfBoy;
			while (boy[i] == 0)
				i = (i + 1) % numOfBoy;
			j--; //数一个小孩
		} while (j > 1); //数到第 m 个小孩
		//第 m 个小孩离开
		cout << boy[i] << "，"; //输出离开的小孩之编号
		boy[i] = 0; //标识该小孩已离开
		///当前位置 i 调整到下一个小孩
		i = (i + 1) % numOfBoy;
		while (boy[i] == 0)
			i = (i + 1) % numOfBoy;
		n--; //离开一个小孩
	}
	//宣布得胜者
	for (int i = 0; i < numOfBoy; i++) {
		if (boy[i] != 0) {
			cout << "\nNo." << boy[i] << "获胜.\n"; //输出胜利者
			break;
		}
	}
	system("pause");
}