#include<iostream>
#include <graphics.h>  // EasyXͼ�ο�
#include <windows.h>  
#include"fighter.h"
using namespace std;
int main() 
{
	//initgraph(640, 480);  // ��ʼ��640x480��ͼ�δ���
	//setbkcolor(WHITE);     // ���ñ���ɫΪ��ɫ
	//cleardevice();         // ����
	srand(time(nullptr));
	init();        // ���ݳ�ʼ��
	while (1)     
	{
		drawPicture();            //��ʾ��ҷɻ����л����ӵ���
		pcOperate();              //PC���ɵл��������ӵ�����Ư�Ƶ�
		operateFighter();         //�û��ٿطɻ�
	}
	system("pause");
}