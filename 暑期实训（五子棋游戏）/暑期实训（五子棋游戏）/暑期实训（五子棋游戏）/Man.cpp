#include "Man.h"      // 包含玩家类定义
#include "Chess.h"    // 包含棋盘类定义
#include "ChessPos.h" // 包含棋子位置类定义
#include <graphics.h> // 包含EasyX图形库

/**
 * Man类构造函数
 * 初始化玩家对象，关联棋盘
 * @param chess 棋盘对象指针
 */
Man::Man(Chess* chess) {
    this->chess = chess;  // 保存棋盘对象指针
}

/**
 * 玩家下棋函数
 * 等待玩家鼠标点击，检测点击位置并下棋
 */
void Man::go() {
    MOUSEMSG msg;  // 鼠标消息结构体
    ChessPos pos;  // 棋子位置

    // 等待玩家的有效点击
    while (1) {
        msg = GetMouseMsg();  // 获取鼠标消息
        // 检查是否为左键点击且点击位置有效
        if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
            break;  // 找到有效点击位置，退出循环
        }
    }

    // 在有效位置下黑棋（玩家棋子）
    chess->chessDown(&pos, CHESS_BLACK);
}
