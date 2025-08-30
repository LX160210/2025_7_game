#include<iostream>
#include<conio.h>
#include<windows.h>
#include <cstdlib>  // �ṩ rand() �� srand()
#include <ctime>    // �ṩ time()
using namespace std;

int height = 20, width = 30;     //   ��Ϸ����ߴ�
int fighter_x, fighter_y;        // �ɻ�λ��
int bullet_x, bullet_y;          // �ӵ�λ��
int enemy_x, enemy_y;            // �л�λ��
int score = 0;                   //����
int fighter_lives = 3;           //������

// �������ع��
void HideCursor() 
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };    // �ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//��ʼ������
void init() {
	fighter_x = height / 2 + 3;
	fighter_y = width / 2;
	enemy_x = 1;
	enemy_y = rand() % (width - 5) + 2;
	HideCursor();
}

void zeroXy(int x, int y)    //����ƶ���(x,y)λ��,������windows. Hͷ�ļ�
{
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos;pos.X = x;
pos.Y = y;
SetConsoleCursorPosition(handle, pos);
}

//�������
void drawPicture() {
	zeroXy(0, 0);
	//system("cls");

	for (int y = 0; y < width; y++) {
		zeroXy(y, 0); cout << "#";          // �ϱ߽�
		zeroXy(y, height - 1); cout << "#";   // �±߽�
	}
	for (int x = 1; x < height - 1; x++) {
		zeroXy(0, x); cout << "#";          // ��߽�
		zeroXy(width - 1, x); cout << "#";    // �ұ߽�
	}

	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			zeroXy(y, x);
			if (x == 0 || x == height - 1 || y == 0 || y == width - 1) {
				cout << "#";
			}
			if ((x == fighter_x && y >= fighter_y - 2 && y <= fighter_y + 2) || (x == fighter_x - 1 && y == fighter_y)
				|| (x == fighter_x + 1 && y == fighter_y - 1) || (x == fighter_x + 1 && y == fighter_y + 1)) //�����ɻ�
			{
				cout << "*";
			}
			else if ((x == bullet_x) && (y == bullet_y))//�����ӵ�
			{
				cout << "!";
			}
			else if ((x == enemy_x && y >= enemy_y - 1 && y <= enemy_y + 1) || (x == enemy_x + 1 && y == enemy_y))//�����л�
			{
				cout << ".";
			}
			else
				cout << " ";                            //����ո�
		}
		cout << endl;
	}
	cout << "����:" << score << "|����:" << fighter_lives << endl;//��ʾ��Ϣ
}

//��������
void operateFighter() {
		if (_kbhit()) {
			char input = _getch(); // �����û��Ĳ�ͬ�������ƶ�
			if (input == 'a' && fighter_y > 3)
				fighter_y--;       // λ������
			if (input == 'd' && fighter_y < width - 4)
				fighter_y++;       //λ������
			if (input == 'w' && fighter_x > 2)
				fighter_x--;      //λ������
			if (input == 's' && fighter_x < height - 3)
				fighter_x++;      //λ������
			if (input == ' ')
			{
				bullet_x = fighter_x - 1;    // �����ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
				bullet_y = fighter_y;
			}
		}
}

void pcOperate() {

	if (bullet_x >= 0)//�ӵ��ƶ�
		bullet_x--;

	static int speed = 0;
	if (speed < 15)
		speed++;
	if (speed == 15)
	{
		enemy_x++; 
		speed = 0;
	}

	if (bullet_x == enemy_x && bullet_y >= enemy_y - 1 && bullet_y <= enemy_y + 1)// �ӵ����ел�
	{
		score++;                          // ������1
		enemy_x = 0;                      // �����µķɻ�
		enemy_y = rand() % (width - 5) + 2;
		bullet_x = -1;                    // �ӵ���Ч
	}

	if ((enemy_x + 1 == fighter_x && enemy_y >= fighter_y - 2 && enemy_y <= fighter_y + 2)
		|| (enemy_x + 1 == fighter_x - 1 && enemy_y == fighter_y)
		|| (enemy_x == fighter_x - 1 && enemy_y + 1 >= fighter_y - 2 && enemy_y - 1 <= fighter_y - 2)
		|| (enemy_x == fighter_x && enemy_y + 1 >= fighter_y - 2 && enemy_y - 1 <= fighter_y - 2)
		|| (enemy_x == fighter_x + 1 && enemy_y + 1 >= fighter_y - 2 && enemy_y - 1 <= fighter_y + 2)
		)//�ɻ�ײ�ϵл�
	{
		fighter_lives--;                  //������1
		if (fighter_lives <= 0)           //�����ľ�
		{
			cout << "��Ϸ����|���շ���:" << score << endl;
			exit(0);                      //��Ϸ����
		}
		init();                           //��ʼ������
	}

	if (enemy_x >= height) {
		enemy_x = 0;
		enemy_y = rand() % (width - 5) + 2;
	}

}