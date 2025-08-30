#include"fighter.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
const int WIDTH = 600;
const int HEIGHT = 800;
int main() {
    initgraph(WIDTH, HEIGHT);  // ��ʼ��ͼ�δ���
    srand((unsigned)time(NULL));  // ��ʼ�����������
    initGraphics();  // ��ʼ��ͼ����Դ
    initGame();      // ��ʼ����Ϸ״̬

    // ��Ϸ��ѭ��(֡�ʿ���)
    DWORD lastTime = GetTickCount();  // ��¼��һ֡ʱ��
    while (true) {
        DWORD currentTime = GetTickCount();  // ��ǰʱ��
        float deltaTime = (currentTime - lastTime) / 1000.0f;  // ����ʱ���(��)
        lastTime = currentTime;  // ������һ֡ʱ��

        processInput();  // ��������
        updateGame();    // ������Ϸ״̬
        drawGame();      // ������Ϸ����
        FlushBatchDraw();  // ˢ�»���

        // ����֡��(Լ60FPS)
        if (deltaTime < 1.0f / 60) {
            Sleep((1.0f / 60 - deltaTime) * 1000);  // ����1/60��ʱ����
        }
    }

    closegraph();  // �ر�ͼ�δ���
    return 0;
}