#include "Chess.h"     // 包含棋盘类定义
#include <mmsystem.h>   // 包含多媒体系统函数
#include <conio.h>      // 包含控制台输入输出函数
#include <cmath>        // 包含数学函数
#include <tchar.h>      // 包含字符处理函数
#pragma comment(lib, "winmm.lib")  // 链接多媒体库

/**
 * 透明图片绘制函数
 * 用于绘制带透明度的PNG图片
 * @param x 绘制位置的x坐标
 * @param y 绘制位置的y坐标
 * @param picture 要绘制的图片指针
 */
void putimagePNG(int x, int y, IMAGE* picture) {
    DWORD* dst = GetImageBuffer();           // 获取目标缓冲区
    DWORD* draw = GetImageBuffer();          // 获取绘制缓冲区
    DWORD* src = GetImageBuffer(picture);    // 获取源图片缓冲区
    int picture_width = picture->getwidth(); // 获取图片宽度
    int picture_height = picture->getheight(); // 获取图片高度
    int graphWidth = getwidth();             // 获取画布宽度
    int graphHeight = getheight();           // 获取画布高度
    int dstX = 0;                           // 目标位置x坐标

    // 遍历图片的每个像素
    for (int iy = 0; iy < picture_height; iy++) {
        for (int ix = 0; ix < picture_width; ix++) {
            int srcX = ix + iy * picture_width;  // 计算源像素位置
            // 提取ARGB颜色分量
            int sa = ((src[srcX] & 0xff000000) >> 24);  // Alpha透明度
            int sr = ((src[srcX] & 0xff0000) >> 16);    // Red红色分量
            int sg = ((src[srcX] & 0xff00) >> 8);       // Green绿色分量
            int sb = src[srcX] & 0xff;                  // Blue蓝色分量

            // 检查像素是否在有效范围内
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight) {
                dstX = (ix + x) + (iy + y) * graphWidth;  // 计算目标像素位置
                // 提取目标像素的RGB分量
                int dr = ((dst[dstX] & 0xff0000) >> 16);  // 目标红色分量
                int dg = ((dst[dstX] & 0xff00) >> 8);     // 目标绿色分量
                int db = dst[dstX] & 0xff;                // 目标蓝色分量

                // Alpha混合计算，实现透明效果
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16) |
                    ((sg * sa / 255 + dg * (255 - sa) / 255) << 8) |
                    (sb * sa / 255 + db * (255 - sa) / 255);
            }
        }
    }
}

/**
 * Chess类构造函数
 * 初始化棋盘的基本参数和棋盘数据结构
 */
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize) {
    this->gradeSize = gradeSize;  // 设置棋盘大小（格子数）
    this->margin_x = marginX;     // 设置棋盘左边距
    this->margin_y = marginY;     // 设置棋盘上边距
    this->chessSize = chessSize;  // 设置棋子大小
    playerFlag = true;            // 初始为玩家回合

    // 初始化棋盘数据结构
    for (int i = 0; i < gradeSize; i++) {
        std::vector<int> row;  // 创建一行
        for (int j = 0; j < gradeSize; j++) {
            row.push_back(0);  // 0表示空位
        }
        chessMap.push_back(row);  // 将行添加到棋盘中
    }
}

/**
 * 初始化棋盘函数
 * 创建游戏窗口，绘制棋盘背景和网格线，清空棋盘数据
 */
void Chess::init() {
    // 创建游戏窗口（宽897像素，高895像素）
    initgraph(897, 895);

    // 绘制棋盘背景
    setbkcolor(RGB(218, 165, 32)); // 设置背景为木色
    cleardevice();                 // 清空设备并填充背景色
    
    // 绘制棋盘网格线
    setlinecolor(BLACK);           // 设置线条颜色为黑色
    setlinestyle(PS_SOLID, 2);     // 设置线条样式为实线，宽度为2
    
    // 绘制横线（水平线）
    for (int i = 0; i < gradeSize; i++) {
        line(margin_x, margin_y + i * chessSize, 
             margin_x + (gradeSize - 1) * chessSize, margin_y + i * chessSize);
    }
    
    // 绘制竖线（垂直线）
    for (int i = 0; i < gradeSize; i++) {
        line(margin_x + i * chessSize, margin_y, 
             margin_x + i * chessSize, margin_y + (gradeSize - 1) * chessSize);
    }
    
    // 绘制天元点（棋盘中心点）
    setfillcolor(BLACK);           // 设置填充颜色为黑色
    int center = gradeSize / 2;    // 计算棋盘中心位置
    solidcircle(margin_x + center * chessSize, margin_y + center * chessSize, 4);
    
    // 棋盘数据清零
    for (int i = 0; i < gradeSize; i++) {
        for (int j = 0; j < gradeSize; j++) {
            chessMap[i][j] = 0;        // 0表示空位
        }
    }
    playerFlag = true;             // 设置玩家先手
}

/**
 * 点击棋盘检测函数
 * 检测鼠标点击位置是否在有效的棋盘交叉点附近
 * @param x 鼠标点击的x坐标
 * @param y 鼠标点击的y坐标
 * @param pos 输出参数，返回点击的棋盘位置
 * @return 是否点击在有效位置
 */
bool Chess::clickBoard(int x, int y, ChessPos* pos) {
    int col = (x - margin_x) / chessSize;        // 计算点击的列
    int row = (y - margin_y) / chessSize;        // 计算点击的行
    int leftTopPosX = margin_x + chessSize * col; // 计算网格左上角x坐标
    int leftTopPosY = margin_y + chessSize * row; // 计算网格左上角y坐标
    int offset = chessSize * 0.4;               // 设置有效点击范围
    int len;                                    // 距离变量
    bool ret = false;                           // 返回值

    do {
        // 检查左上角交叉点
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < offset) {
            pos->row = row;
            pos->col = col;
            // 检查位置是否在棋盘范围内且为空位
            if (pos->row >= 0 && pos->row < gradeSize && pos->col >= 0 && pos->col < gradeSize && chessMap[pos->row][pos->col] == 0) {
                ret = true;
                break;
            }
        }
        // 检查右上角交叉点
        int x2 = leftTopPosX + chessSize;
        int y2 = leftTopPosY;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset) {
            pos->row = row;
            pos->col = col + 1;
            // 检查位置是否在棋盘范围内且为空位
            if (pos->row >= 0 && pos->row < gradeSize && pos->col >= 0 && pos->col < gradeSize && chessMap[pos->row][pos->col] == 0) {
                ret = true;
                break;
            }
        }
        // 检查左下角交叉点
        x2 = leftTopPosX;
        y2 = leftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset) {
            pos->row = row + 1;
            pos->col = col;
            // 检查位置是否在棋盘范围内且为空位
            if (pos->row >= 0 && pos->row < gradeSize && pos->col >= 0 && pos->col < gradeSize && chessMap[pos->row][pos->col] == 0) {
                ret = true;
                break;
            }
        }
        // 检查右下角交叉点
        x2 = leftTopPosX + chessSize;
        y2 = leftTopPosY + chessSize;
        len = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
        if (len < offset) {
            pos->row = row + 1;
            pos->col = col + 1;
            // 检查位置是否在棋盘范围内且为空位
            if (pos->row >= 0 && pos->row < gradeSize && pos->col >= 0 && pos->col < gradeSize && chessMap[pos->row][pos->col] == 0) {
                ret = true;
                break;
            }
        }
    } while (0);

    return ret;
}

/**
 * 下棋函数
 * 在指定位置绘制棋子并更新棋盘数据
 * @param pos 下棋位置
 * @param kind 棋子类型（黑棋或白棋）
 */
void Chess::chessDown(ChessPos* pos, chess_kind_t kind) {
    int x = margin_x + chessSize * pos->col;  // 计算棋子绘制的x坐标
    int y = margin_y + chessSize * pos->row;  // 计算棋子绘制的y坐标
    int radius = chessSize / 2 - 2;           // 计算棋子半径

    if (kind == CHESS_WHITE) {
        // 绘制白棋
        setfillcolor(WHITE);    // 设置填充颜色为白色
        setlinecolor(BLACK);    // 设置边框颜色为黑色
        fillcircle(x, y, radius);  // 绘制填充圆
        circle(x, y, radius);      // 绘制圆形边框
    }
    else {
        // 绘制黑棋
        setfillcolor(BLACK);    // 设置填充颜色为黑色
        setlinecolor(BLACK);    // 设置边框颜色为黑色
        fillcircle(x, y, radius);  // 绘制填充圆
    }

    updateGameMap(pos);  // 更新棋盘数据
}

/**
 * 获取棋盘大小
 * @return 棋盘格子数
 */
int Chess::getGradeSize() {
    return gradeSize;
}

/**
 * 获取指定位置的棋子数据
 * @param pos 棋盘位置
 * @return 棋子类型（0=空，1=黑棋，-1=白棋）
 */
int Chess::getChessData(ChessPos* pos) {
    return chessMap[pos->row][pos->col];
}

/**
 * 获取指定坐标的棋子数据
 * @param row 行坐标
 * @param col 列坐标
 * @return 棋子类型（0=空，1=黑棋，-1=白棋）
 */
int Chess::getChessData(int row, int col) {
    return chessMap[row][col];
}

/**
 * 更新游戏地图
 * 在棋盘数据中记录新下的棋子，并切换回合
 * @param pos 新下棋的位置
 */
void Chess::updateGameMap(ChessPos* pos) {
    lastPos = *pos;  // 记录最后一步位置
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;  // 根据当前回合设置棋子类型
    playerFlag = !playerFlag;  // 切换回合（黑白方交替）
}

/**
 * 检查是否有玩家获胜
 * 检查最后一步棋子周围是否形成五子连珠
 * @return 是否有玩家获胜
 */
bool Chess::checkWin() {
    int row = lastPos.row;        // 获取最后一步的行坐标
    int col = lastPos.col;        // 获取最后一步的列坐标
    int kind = chessMap[row][col]; // 获取最后一步的棋子类型

    // 检查水平方向（横向）五子连珠
    for (int i = 0; i < 5; i++) {
        if (col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row][col - i] == kind &&
            chessMap[row][col - i + 1] == kind &&
            chessMap[row][col - i + 2] == kind &&
            chessMap[row][col - i + 3] == kind &&
            chessMap[row][col - i + 4] == kind) {
            return true;
        }
    }

    // 检查垂直方向（纵向）五子连珠
    for (int i = 0; i < 5; i++) {
        if (row - i >= 0 && row - i + 4 < gradeSize &&
            chessMap[row - i][col] == kind &&
            chessMap[row - i + 1][col] == kind &&
            chessMap[row - i + 2][col] == kind &&
            chessMap[row - i + 3][col] == kind &&
            chessMap[row - i + 4][col] == kind) {
            return true;
        }
    }

    // 检查左上到右下对角线方向五子连珠
    for (int i = 0; i < 5; i++) {
        if (row + i < gradeSize && row + i - 4 >= 0 &&
            col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row + i][col - i] == kind &&
            chessMap[row + i - 1][col - i + 1] == kind &&
            chessMap[row + i - 2][col - i + 2] == kind &&
            chessMap[row + i - 3][col - i + 3] == kind &&
            chessMap[row + i - 4][col - i + 4] == kind) {
            return true;
        }
    }

    // 检查左上到右下对角线方向五子连珠（另一个方向）
    for (int i = 0; i < 5; i++) {
        if (row - i >= 0 && row - i + 4 < gradeSize &&
            col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row - i][col - i] == kind &&
            chessMap[row - i + 1][col - i + 1] == kind &&
            chessMap[row - i + 2][col - i + 2] == kind &&
            chessMap[row - i + 3][col - i + 3] == kind &&
            chessMap[row - i + 4][col - i + 4] == kind) {
            return true;
        }
    }

    return false;  // 没有找到五子连珠
}

/**
 * 检查游戏是否结束
 * 如果有玩家获胜，显示胜利信息并等待重新开始
 * @return 游戏是否结束
 */
bool Chess::checkOver() {
    if (checkWin()) {  // 如果有玩家获胜
        Sleep(1500);   // 暂停1.5秒让玩家看到最后一步
        
        // 设置胜利文字样式
        settextcolor(RED);                    // 设置文字颜色为红色
        settextstyle(60, 0, _T("SimSun"));    // 设置字体大小和类型
        setbkmode(TRANSPARENT);               // 设置文字背景为透明
        
        if (playerFlag == false) {
            // 玩家胜利（因为playerFlag已经切换，所以false表示上一步是玩家）
            outtextxy(350, 400, _T("Player Wins!"));
        }
        else {
            // AI胜利（因为playerFlag已经切换，所以true表示上一步是AI）
            outtextxy(350, 400, _T("AI Wins!"));
        }
        
        // 显示重新开始提示
        settextcolor(BLUE);                   // 设置提示文字颜色为蓝色
        settextstyle(30, 0, _T("SimSun"));    // 设置较小的字体
        outtextxy(300, 500, _T("Press any key to restart"));  // 显示重新开始提示
        
        _getch();      // 等待用户按键
        return true;   // 返回游戏结束
    }
    return false;      // 游戏继续
}