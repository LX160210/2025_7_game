#ifndef AI_H
#define AI_H

#include <vector>      // 包含向量容器库
#include "ChessPos.h"  // 包含棋子位置类定义

// 前向声明Chess类，避免循环包含
class Chess;

/**
 * AI类 - 人工智能玩家类
 * 负责AI的决策逻辑和下棋操作
 */
class AI {
public:
    /**
     * 构造函数
     * @param chess 棋盘对象指针
     */
    AI(Chess* chess);
    
    /**
     * AI下棋函数
     * 执行AI的一次下棋操作
     */
    void go();
    
private:
    Chess* chess;                           // 棋盘对象指针
    std::vector<std::vector<int>> scoreMap; // 评分地图，存储每个位置的评分值

    /**
     * 计算评分函数
     * 为棋盘上每个位置计算评分值
     */
    void calculateScore();
    
    /**
     * AI思考函数
     * 根据评分选择最佳下棋位置
     * @return 返回选择的棋子位置
     */
    ChessPos think();
};

#endif // AI_H
