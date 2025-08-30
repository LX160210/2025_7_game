#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "Man.h"  // 包含玩家类定义
#include "AI.h"   // 包含AI类定义

// 前向声明Chess类
class Chess;

/**
 * ChessGame类 - 游戏控制类
 * 负责协调玩家、AI和棋盘之间的交互，控制游戏流程
 */
class ChessGame {
public:
    /**
     * 构造函数
     * @param man 玩家对象指针
     * @param ai AI对象指针
     * @param chess 棋盘对象指针
     */
    ChessGame(Man* man, AI* ai, Chess* chess);
    
    /**
     * 开始游戏
     * 控制游戏主循环，处理玩家和AI的回合交替
     */
    void play();
    
private:
    Man* man;      // 玩家对象指针
    AI* ai;        // AI对象指针
    Chess* chess;  // 棋盘对象指针
};

#endif // CHESSGAME_H
