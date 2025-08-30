#include <graphics.h>  // EasyXͼ�ο�ͷ�ļ�
#include <conio.h>     // ����̨�������ͷ�ļ�
#include <time.h>      // ʱ����غ���ͷ�ļ�
#include <stdio.h>     // ��׼�������ͷ�ļ�
#include <windows.h>   // Windows APIͷ�ļ�

// ��Ϸ��������
const int WIDTH = 600;          // ��Ϸ���ڿ��
const int HEIGHT = 800;         // ��Ϸ���ڸ߶�
const int FIGHTER_SIZE = 40;    // ���ս���ߴ�
const int ENEMY_SIZE = 30;      // �л��ߴ�
const int BULLET_SIZE = 10;     // �ӵ��ߴ�
const int GAME_AREA_TOP = 50;   // ��Ϸ���򶥲��߽�

// ��Ϸ����
int fighterX, fighterY;         // ���ս������
int bulletX, bulletY;           // �ӵ�����
bool bulletActive = false;      // �ӵ��Ƿ񼤻�
int enemyX, enemyY;             // �л�����
int score = 0;                  // ��Ϸ�÷�
int lives = 3;                  // ʣ������
int gameSpeed = 1;              // ��Ϸ�ٶ�
bool gameOver = false;          // ��Ϸ������־

// ͼ����Դ
IMAGE imgBackground;    // ����ͼ��
IMAGE imgFighter;       // ���ս��ͼ��
IMAGE imgEnemy;         // �л�ͼ��
IMAGE imgBullet;        // �ӵ�ͼ��
IMAGE imgExplosion;     // ��ըЧ��ͼ��

// ��ʼ��ͼ����Դ
void initGraphics() {
    // ��������ͼ��
    imgBackground = IMAGE(WIDTH, HEIGHT);
    SetWorkingImage(&imgBackground);  // ���õ�ǰ��ͼĿ��Ϊ����ͼ��
    cleardevice();                   // ���ͼ��
    setbkcolor(BLACK);               // ���ñ���ɫΪ��ɫ
    cleardevice();                   // �ٴ����ȷ������ɫ��Ч

    // �����ǿձ���(����׵�)
    setfillcolor(WHITE);
    for (int i = 0; i < 100; i++) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        int size = rand() % 3 + 1;
        fillrectangle(x, y, x + size, y + size);  // ��������
    }

    // �������ս��ͼ��(��ɫ������)
    imgFighter = IMAGE(FIGHTER_SIZE, FIGHTER_SIZE);
    SetWorkingImage(&imgFighter);
    cleardevice();
    setfillcolor(BLUE);
    POINT fighterShape[] = { {20, 0}, {0, 40}, {40, 40} };  // ���������ζ���
    fillpolygon(fighterShape, 3);  // ���������

    // �����л�ͼ��(��ɫԲ��)
    imgEnemy = IMAGE(ENEMY_SIZE, ENEMY_SIZE);
    SetWorkingImage(&imgEnemy);
    cleardevice();
    setfillcolor(RED);
    fillcircle(15, 15, 15);  // ����Բ�εл�

    // �����ӵ�ͼ��(��ɫ����)
    imgBullet = IMAGE(BULLET_SIZE, BULLET_SIZE);
    SetWorkingImage(&imgBullet);
    cleardevice();
    setfillcolor(YELLOW);
    fillrectangle(0, 0, BULLET_SIZE, BULLET_SIZE);  // ���ƾ����ӵ�

    SetWorkingImage();  // �ָ�Ĭ�ϻ�ͼĿ��
}

// ��ʼ����Ϸ״̬
void initGame() {
    fighterX = WIDTH / 2 - FIGHTER_SIZE / 2;  // ��ҳ�ʼX����(����)
    fighterY = HEIGHT - FIGHTER_SIZE - 20;     // ��ҳ�ʼY����(�ײ�)
    enemyX = rand() % (WIDTH - ENEMY_SIZE);    // �л����X����
    enemyY = GAME_AREA_TOP;                    // �л���ʼY����(����)
    bulletActive = false;                      // �ӵ�δ����
    score = 0;                                 // ���÷���
    lives = 3;                                 // ��������
    gameOver = false;                          // ������Ϸ״̬
}

// ������Ϸ����
void drawGame() {
    // ���Ʊ���
    putimage(0, 0, &imgBackground);

    // �������ս��
    putimage(fighterX, fighterY, &imgFighter);

    // ���Ƶл�
    putimage(enemyX, enemyY, &imgEnemy);

    // �����ӵ�(�������)
    if (bulletActive) {
        putimage(bulletX, bulletY, &imgBullet);
    }

    // ������������
    setbkmode(TRANSPARENT);  // ͸������
    settextcolor(WHITE);     // ��ɫ����
    settextstyle(20, 0, _T("����"));  // ��������

    // ��ʾ����
    TCHAR scoreStr[50];
    _stprintf_s(scoreStr, _T("����: %d"), score);
    outtextxy(20, 10, scoreStr);

    // ��ʾ����
    TCHAR livesStr[50];
    _stprintf_s(livesStr, _T("����: %d"), lives);
    outtextxy(WIDTH - 120, 10, livesStr);

    // ��Ϸ������ʾ
    if (gameOver) {
        settextcolor(RED);
        settextstyle(40, 0, _T("����"));
        outtextxy(WIDTH / 2 - 100, HEIGHT / 2 - 50, _T("��Ϸ����"));

        settextstyle(20, 0, _T("����"));
        TCHAR finalScore[50];
        _stprintf_s(finalScore, _T("���շ���: %d"), score);
        outtextxy(WIDTH / 2 - 70, HEIGHT / 2 + 10, finalScore);

        outtextxy(WIDTH / 2 - 100, HEIGHT / 2 + 50, _T("��R�����¿�ʼ"));
        outtextxy(WIDTH / 2 - 100, HEIGHT / 2 + 80, _T("��ESC���˳�"));
    }
}

// �����û�����
void processInput() {
    // ʹ��GetAsyncKeyState����������״̬

    // A��: ����
    if (GetAsyncKeyState('A') & 0x8000 && fighterX > 0) fighterX -= 5;

    // D��: ����
    if (GetAsyncKeyState('D') & 0x8000 && fighterX < WIDTH - FIGHTER_SIZE) fighterX += 5;

    // W��: ����
    if (GetAsyncKeyState('W') & 0x8000 && fighterY > GAME_AREA_TOP) fighterY -= 5;

    // S��: ����
    if (GetAsyncKeyState('S') & 0x8000 && fighterY < HEIGHT - FIGHTER_SIZE) fighterY += 5;

    // �ո��: �����ӵ�
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && !bulletActive) {
        bulletX = fighterX + FIGHTER_SIZE / 2 - BULLET_SIZE / 2;  // �ӵ�X����(����)
        bulletY = fighterY - BULLET_SIZE;                         // �ӵ�Y����(ս���Ϸ�)
        bulletActive = true;                                      // �����ӵ�
    }

    // ��Ϸ����״̬�µĿ���
    if (gameOver && (GetAsyncKeyState('R') & 0x8000)) initGame();  // R��: ���¿�ʼ
    if (gameOver && (GetAsyncKeyState(VK_ESCAPE) & 0x8000)) exit(0);  // ESC��: �˳�
}

// ������Ϸ״̬
void updateGame() {
    if (gameOver) return;  // ��Ϸ����ʱ������

    // �ӵ��ƶ�
    if (bulletActive) {
        bulletY -= 15;  // �ӵ������ƶ�
        if (bulletY < 0) bulletActive = false;  // �ӵ�������Ļ��ʧЧ
    }

    // �л��ƶ�
    enemyY += 3 + gameSpeed;  // �л������ƶ����ٶ�����Ϸ�Ѷ�����
    if (enemyY > HEIGHT) {    // �л�������Ļ�ײ�
        enemyX = rand() % (WIDTH - ENEMY_SIZE);  // ���X����
        enemyY = GAME_AREA_TOP - ENEMY_SIZE;     // �Ӷ������³���
    }

    // �ӵ���л���ײ���
    if (bulletActive &&
        bulletX + BULLET_SIZE > enemyX &&
        bulletX < enemyX + ENEMY_SIZE &&
        bulletY + BULLET_SIZE > enemyY &&
        bulletY < enemyY + ENEMY_SIZE) {

        // ��ײ�����õл�λ��
        enemyX = rand() % (WIDTH - ENEMY_SIZE);
        enemyY = GAME_AREA_TOP - ENEMY_SIZE;
        bulletActive = false;  // �ӵ�ʧЧ
        score += 10;           // ���ӷ���

        // ÿ100�������Ϸ�Ѷ�
        if (score % 100 == 0) gameSpeed++;
    }

    // �����л���ײ���
    if (fighterX + FIGHTER_SIZE > enemyX &&
        fighterX < enemyX + ENEMY_SIZE &&
        fighterY + FIGHTER_SIZE > enemyY &&
        fighterY < enemyY + ENEMY_SIZE) {

        // ��ײ�����õл�λ��
        enemyX = rand() % (WIDTH - ENEMY_SIZE);
        enemyY = GAME_AREA_TOP - ENEMY_SIZE;
        lives--;  // ��������

        // ����Ϊ0ʱ��Ϸ����
        if (lives <= 0) gameOver = true;
    }
}