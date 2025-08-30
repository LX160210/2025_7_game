#include"fighter.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
const int WIDTH = 600;
const int HEIGHT = 800;
int main() {
    initgraph(WIDTH, HEIGHT);  // 初始化图形窗口
    srand((unsigned)time(NULL));  // 初始化随机数种子
    initGraphics();  // 初始化图形资源
    initGame();      // 初始化游戏状态

    // 游戏主循环(帧率控制)
    DWORD lastTime = GetTickCount();  // 记录上一帧时间
    while (true) {
        DWORD currentTime = GetTickCount();  // 当前时间
        float deltaTime = (currentTime - lastTime) / 1000.0f;  // 计算时间差(秒)
        lastTime = currentTime;  // 更新上一帧时间

        processInput();  // 处理输入
        updateGame();    // 更新游戏状态
        drawGame();      // 绘制游戏画面
        FlushBatchDraw();  // 刷新画面

        // 控制帧率(约60FPS)
        if (deltaTime < 1.0f / 60) {
            Sleep((1.0f / 60 - deltaTime) * 1000);  // 不足1/60秒时休眠
        }
    }

    closegraph();  // 关闭图形窗口
    return 0;
}