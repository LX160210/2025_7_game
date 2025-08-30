#include <graphics.h>  // EasyX图形库头文件
#include <conio.h>     // 控制台输入输出头文件
#include <time.h>      // 时间相关函数头文件
#include <stdio.h>     // 标准输入输出头文件
#include <windows.h>   // Windows API头文件

// 游戏常量定义
const int WIDTH = 600;          // 游戏窗口宽度
const int HEIGHT = 800;         // 游戏窗口高度
const int FIGHTER_SIZE = 40;    // 玩家战机尺寸
const int ENEMY_SIZE = 30;      // 敌机尺寸
const int BULLET_SIZE = 10;     // 子弹尺寸
const int GAME_AREA_TOP = 50;   // 游戏区域顶部边界

// 游戏变量
int fighterX, fighterY;         // 玩家战机坐标
int bulletX, bulletY;           // 子弹坐标
bool bulletActive = false;      // 子弹是否激活
int enemyX, enemyY;             // 敌机坐标
int score = 0;                  // 游戏得分
int lives = 3;                  // 剩余生命
int gameSpeed = 1;              // 游戏速度
bool gameOver = false;          // 游戏结束标志

// 图形资源
IMAGE imgBackground;    // 背景图像
IMAGE imgFighter;       // 玩家战机图像
IMAGE imgEnemy;         // 敌机图像
IMAGE imgBullet;        // 子弹图像
IMAGE imgExplosion;     // 爆炸效果图像

// 初始化图形资源
void initGraphics() {
    // 创建背景图像
    imgBackground = IMAGE(WIDTH, HEIGHT);
    SetWorkingImage(&imgBackground);  // 设置当前绘图目标为背景图像
    cleardevice();                   // 清空图像
    setbkcolor(BLACK);               // 设置背景色为黑色
    cleardevice();                   // 再次清空确保背景色生效

    // 绘制星空背景(随机白点)
    setfillcolor(WHITE);
    for (int i = 0; i < 100; i++) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        int size = rand() % 3 + 1;
        fillrectangle(x, y, x + size, y + size);  // 绘制星星
    }

    // 创建玩家战机图像(蓝色三角形)
    imgFighter = IMAGE(FIGHTER_SIZE, FIGHTER_SIZE);
    SetWorkingImage(&imgFighter);
    cleardevice();
    setfillcolor(BLUE);
    POINT fighterShape[] = { {20, 0}, {0, 40}, {40, 40} };  // 定义三角形顶点
    fillpolygon(fighterShape, 3);  // 填充三角形

    // 创建敌机图像(红色圆形)
    imgEnemy = IMAGE(ENEMY_SIZE, ENEMY_SIZE);
    SetWorkingImage(&imgEnemy);
    cleardevice();
    setfillcolor(RED);
    fillcircle(15, 15, 15);  // 绘制圆形敌机

    // 创建子弹图像(黄色矩形)
    imgBullet = IMAGE(BULLET_SIZE, BULLET_SIZE);
    SetWorkingImage(&imgBullet);
    cleardevice();
    setfillcolor(YELLOW);
    fillrectangle(0, 0, BULLET_SIZE, BULLET_SIZE);  // 绘制矩形子弹

    SetWorkingImage();  // 恢复默认绘图目标
}

// 初始化游戏状态
void initGame() {
    fighterX = WIDTH / 2 - FIGHTER_SIZE / 2;  // 玩家初始X坐标(居中)
    fighterY = HEIGHT - FIGHTER_SIZE - 20;     // 玩家初始Y坐标(底部)
    enemyX = rand() % (WIDTH - ENEMY_SIZE);    // 敌机随机X坐标
    enemyY = GAME_AREA_TOP;                    // 敌机初始Y坐标(顶部)
    bulletActive = false;                      // 子弹未激活
    score = 0;                                 // 重置分数
    lives = 3;                                 // 重置生命
    gameOver = false;                          // 重置游戏状态
}

// 绘制游戏画面
void drawGame() {
    // 绘制背景
    putimage(0, 0, &imgBackground);

    // 绘制玩家战机
    putimage(fighterX, fighterY, &imgFighter);

    // 绘制敌机
    putimage(enemyX, enemyY, &imgEnemy);

    // 绘制子弹(如果激活)
    if (bulletActive) {
        putimage(bulletX, bulletY, &imgBullet);
    }

    // 设置文字属性
    setbkmode(TRANSPARENT);  // 透明背景
    settextcolor(WHITE);     // 白色文字
    settextstyle(20, 0, _T("宋体"));  // 设置字体

    // 显示分数
    TCHAR scoreStr[50];
    _stprintf_s(scoreStr, _T("分数: %d"), score);
    outtextxy(20, 10, scoreStr);

    // 显示生命
    TCHAR livesStr[50];
    _stprintf_s(livesStr, _T("生命: %d"), lives);
    outtextxy(WIDTH - 120, 10, livesStr);

    // 游戏结束显示
    if (gameOver) {
        settextcolor(RED);
        settextstyle(40, 0, _T("宋体"));
        outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 50, _T("游戏结束"));

        settextstyle(20, 0, _T("宋体"));
        TCHAR finalScore[50];
        _stprintf_s(finalScore, _T("最终分数: %d"), score);
        outtextxy(WIDTH / 2 - 70, HEIGHT / 2 + 10, finalScore);

        outtextxy(WIDTH / 2 - 100, HEIGHT / 2 + 50, _T("按R键重新开始"));
        outtextxy(WIDTH / 2 - 100, HEIGHT / 2 + 80, _T("按ESC键退出"));
    }
}

// 处理用户输入
void processInput() {
    // 使用GetAsyncKeyState检测持续按键状态

    // A键: 左移
    if (GetAsyncKeyState('A') & 0x8000 && fighterX > 0) fighterX -= 5;

    // D键: 右移
    if (GetAsyncKeyState('D') & 0x8000 && fighterX < WIDTH - FIGHTER_SIZE) fighterX += 5;

    // W键: 上移
    if (GetAsyncKeyState('W') & 0x8000 && fighterY > GAME_AREA_TOP) fighterY -= 5;

    // S键: 下移
    if (GetAsyncKeyState('S') & 0x8000 && fighterY < HEIGHT - FIGHTER_SIZE) fighterY += 5;

    // 空格键: 发射子弹
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && !bulletActive) {
        bulletX = fighterX + FIGHTER_SIZE / 2 - BULLET_SIZE / 2;  // 子弹X坐标(居中)
        bulletY = fighterY - BULLET_SIZE;                         // 子弹Y坐标(战机上方)
        bulletActive = true;                                      // 激活子弹
    }

    // 游戏结束状态下的控制
    if (gameOver && (GetAsyncKeyState('R') & 0x8000)) initGame();  // R键: 重新开始
    if (gameOver && (GetAsyncKeyState(VK_ESCAPE) & 0x8000)) exit(0);  // ESC键: 退出
}

// 更新游戏状态
void updateGame() {
    if (gameOver) return;  // 游戏结束时不更新

    // 子弹移动
    if (bulletActive) {
        bulletY -= 15;  // 子弹向上移动
        if (bulletY < 0) bulletActive = false;  // 子弹超出屏幕则失效
    }

    // 敌机移动
    enemyY += 3 + gameSpeed;  // 敌机向下移动，速度随游戏难度增加
    if (enemyY > HEIGHT) {    // 敌机超出屏幕底部
        enemyX = rand() % (WIDTH - ENEMY_SIZE);  // 随机X坐标
        enemyY = GAME_AREA_TOP - ENEMY_SIZE;     // 从顶部重新出现
    }

    // 子弹与敌机碰撞检测
    if (bulletActive &&
        bulletX + BULLET_SIZE > enemyX &&
        bulletX < enemyX + ENEMY_SIZE &&
        bulletY + BULLET_SIZE > enemyY &&
        bulletY < enemyY + ENEMY_SIZE) {

        // 碰撞后重置敌机位置
        enemyX = rand() % (WIDTH - ENEMY_SIZE);
        enemyY = GAME_AREA_TOP - ENEMY_SIZE;
        bulletActive = false;  // 子弹失效
        score += 10;           // 增加分数

        // 每100分提高游戏难度
        if (score % 100 == 0) gameSpeed++;
    }

    // 玩家与敌机碰撞检测
    if (fighterX + FIGHTER_SIZE > enemyX &&
        fighterX < enemyX + ENEMY_SIZE &&
        fighterY + FIGHTER_SIZE > enemyY &&
        fighterY < enemyY + ENEMY_SIZE) {

        // 碰撞后重置敌机位置
        enemyX = rand() % (WIDTH - ENEMY_SIZE);
        enemyY = GAME_AREA_TOP - ENEMY_SIZE;
        lives--;  // 减少生命

        // 生命为0时游戏结束
        if (lives <= 0) gameOver = true;
    }
}