#include<iostream>
#include<conio.h>
#include<windows.h>
#include <cstdlib>  // 提供 rand() 和 srand()
#include <ctime>    // 提供 time()
using namespace std;

int height = 20, width = 30;     //   游戏画面尺寸
int fighter_x, fighter_y;        // 飞机位置
int bullet_x, bullet_y;          // 子弹位置
int enemy_x, enemy_y;            // 敌机位置
int score = 0;                   //分数
int fighter_lives = 3;           //生命数

// 用于隐藏光标
void HideCursor() 
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };    // 第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//初始化画面
void init() {
	fighter_x = height / 2 + 3;
	fighter_y = width / 2;
	enemy_x = 1;
	enemy_y = rand() % (width - 5) + 2;
	HideCursor();
}

void zeroXy(int x, int y)    //光标移动到(x,y)位置,需引入windows. H头文件
{
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;pos.X = x;
pos.Y = y;
SetConsoleCursorPosition(handle, pos);
}

//输出画面
void drawPicture() {
	zeroXy(0, 0);
	//system("cls");

	for (int y = 0; y < width; y++) {
		zeroXy(y, 0); cout << "#";          // 上边界
		zeroXy(y, height - 1); cout << "#";   // 下边界
	}
	for (int x = 1; x < height - 1; x++) {
		zeroXy(0, x); cout << "#";          // 左边界
		zeroXy(width - 1, x); cout << "#";    // 右边界
	}

	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			zeroXy(y, x);
			if (x == 0 || x == height - 1 || y == 0 || y == width - 1) {
				cout << "#";
			}
			if ((x == fighter_x && y >= fighter_y - 2 && y <= fighter_y + 2) || (x == fighter_x - 1 && y == fighter_y)
				|| (x == fighter_x + 1 && y == fighter_y - 1) || (x == fighter_x + 1 && y == fighter_y + 1)) //画出飞机
			{
				cout << "*";
			}
			else if ((x == bullet_x) && (y == bullet_y))//画出子弹
			{
				cout << "!";
			}
			else if ((x == enemy_x && y >= enemy_y - 1 && y <= enemy_y + 1) || (x == enemy_x + 1 && y == enemy_y))//画出敌机
			{
				cout << ".";
			}
			else
				cout << " ";                            //输出空格
		}
		cout << endl;
	}
	cout << "分数:" << score << "|生命:" << fighter_lives << endl;//显示信息
}

//操作函数
void operateFighter() {
		if (_kbhit()) {
			char input = _getch(); // 根据用户的不同输入来移动
			if (input == 'a' && fighter_y > 3)
				fighter_y--;       // 位置左移
			if (input == 'd' && fighter_y < width - 4)
				fighter_y++;       //位置右移
			if (input == 'w' && fighter_x > 2)
				fighter_x--;      //位置上移
			if (input == 's' && fighter_x < height - 3)
				fighter_x++;      //位置下移
			if (input == ' ')
			{
				bullet_x = fighter_x - 1;    // 发射子弹的初始位置在飞机的正上方
				bullet_y = fighter_y;
			}
		}
}

void pcOperate() {

	if (bullet_x >= 0)//子弹移动
		bullet_x--;

	static int speed = 0;
	if (speed < 15)
		speed++;
	if (speed == 15)
	{
		enemy_x++; 
		speed = 0;
	}

	if (bullet_x == enemy_x && bullet_y >= enemy_y - 1 && bullet_y <= enemy_y + 1)// 子弹击中敌机
	{
		score++;                          // 分数加1
		enemy_x = 0;                      // 产生新的飞机
		enemy_y = rand() % (width - 5) + 2;
		bullet_x = -1;                    // 子弹无效
	}

	if ((enemy_x + 1 == fighter_x && enemy_y >= fighter_y - 2 && enemy_y <= fighter_y + 2)
		|| (enemy_x + 1 == fighter_x - 1 && enemy_y == fighter_y)
		|| (enemy_x == fighter_x - 1 && enemy_y + 1 >= fighter_y - 2 && enemy_y - 1 <= fighter_y - 2)
		|| (enemy_x == fighter_x && enemy_y + 1 >= fighter_y - 2 && enemy_y - 1 <= fighter_y - 2)
		|| (enemy_x == fighter_x + 1 && enemy_y + 1 >= fighter_y - 2 && enemy_y - 1 <= fighter_y + 2)
		)//飞机撞上敌机
	{
		fighter_lives--;                  //生命减1
		if (fighter_lives <= 0)           //生命耗尽
		{
			cout << "游戏结束|最终分数:" << score << endl;
			exit(0);                      //游戏结束
		}
		init();                           //初始化界面
	}

	if (enemy_x >= height) {
		enemy_x = 0;
		enemy_y = rand() % (width - 5) + 2;
	}

}