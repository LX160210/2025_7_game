#include<iostream>
#include <graphics.h>  // EasyX图形库
#include <windows.h>  
#include"fighter.h"
using namespace std;
int main() 
{
	//initgraph(640, 480);  // 初始化640x480的图形窗口
	//setbkcolor(WHITE);     // 设置背景色为白色
	//cleardevice();         // 清屏
	srand(time(nullptr));
	init();        // 数据初始化
	while (1)     
	{
		drawPicture();            //显示玩家飞机、敌机、子弹等
		pcOperate();              //PC生成敌机、处理子弹向上漂移等
		operateFighter();         //用户操控飞机
	}
	system("pause");
}