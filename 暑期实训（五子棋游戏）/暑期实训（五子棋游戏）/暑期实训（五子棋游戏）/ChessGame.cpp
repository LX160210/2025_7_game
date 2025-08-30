// 包含游戏类的头文件
#include "ChessGame.h"
// 包含棋盘类的头文件
#include "Chess.h"

// ChessGame类的构造函数，初始化游戏所需的三个对象
ChessGame::ChessGame(Man* man, AI* ai, Chess* chess) {
    this->man = man;     // 初始化人类玩家对象
    this->ai = ai;       // 初始化AI对象
    this->chess = chess; // 初始化棋盘对象
}

// 游戏主循环函数，控制整个游戏流程
void ChessGame::play() {
    chess->init(); // 初始化棋盘，清空棋子并设置初始状态

    while (1) { // 无限循环，直到程序退出
        // 人类玩家回合
        man->go(); // 人类玩家下棋
        if (chess->checkOver()) { // 检查游戏是否结束（胜负已分）
            chess->init(); // 重新开始游戏，初始化棋盘
            continue;      // 跳过本次循环的剩余部分，开始新游戏
        }

        // AI玩家回合
        ai->go(); // AI下棋
        if (chess->checkOver()) { // 检查游戏是否结束（胜负已分）
            chess->init(); // 重新开始游戏，初始化棋盘
            continue;      // 跳过本次循环的剩余部分，开始新游戏
        }
    }
}
