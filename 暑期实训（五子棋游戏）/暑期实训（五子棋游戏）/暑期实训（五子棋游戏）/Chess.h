#ifndef CHESS_H
#define CHESS_H

#include <graphics.h>  // 包含EasyX图形库
#include <vector>      // 包含向量容器库
#include "ChessPos.h"  // 包含棋子位置类定义

/**
 * Chess类 - 棋盘类
 * 负责棋盘的绘制、棋子管理、胜负判断等核心功能
 */
class Chess {
public:
    /**
     * 构造函数
     * @param gradeSize 棋盘大小（格子数）
     * @param marginX 棋盘左边距
     * @param marginY 棋盘上边距
     * @param chessSize 棋子大小
     */
    Chess(int gradeSize, int marginX, int marginY, float chessSize);
    
    /**
     * 初始化棋盘
     * 绘制棋盘线条和清空棋子数据
     */
    void init();
    
    /**
     * 点击棋盘检测函数
     * @param x 鼠标点击的x坐标
     * @param y 鼠标点击的y坐标
     * @param pos 输出参数，返回点击的棋盘位置
     * @return 是否点击在有效位置
     */
    bool clickBoard(int x, int y, ChessPos* pos);
    
    /**
     * 下棋函数
     * @param pos 下棋位置
     * @param kind 棋子类型（黑棋或白棋）
     */
    void chessDown(ChessPos* pos, chess_kind_t kind);
    
    /**
     * 获取棋盘大小
     * @return 棋盘格子数
     */
    int getGradeSize();
    
    /**
     * 获取指定位置的棋子数据
     * @param pos 棋盘位置
     * @return 棋子类型（0=空，1=黑棋，2=白棋）
     */
    int getChessData(ChessPos* pos);
    
    /**
     * 获取指定坐标的棋子数据
     * @param row 行坐标
     * @param col 列坐标
     * @return 棋子类型（0=空，1=黑棋，2=白棋）
     */
    int getChessData(int row, int col);
    
    /**
     * 检查游戏是否结束
     * @return 游戏是否结束
     */
    bool checkOver();
    
private:
    IMAGE chessBlackImg;                      // 黑棋图片
    IMAGE chessWhiteImg;                      // 白棋图片
    int gradeSize;                            // 棋盘的大小（格子数）
    int margin_x;                             // 棋盘的左部边界
    int margin_y;                             // 棋盘的顶部边界
    float chessSize;                          // 棋子的大小
    std::vector<std::vector<int>> chessMap;   // 存储当前棋盘的棋子分布
    bool playerFlag;                          // true表示玩家回合，false表示AI回合
    ChessPos lastPos;                         // 最后一步位置

    /**
     * 更新游戏地图
     * @param pos 新下棋的位置
     */
    void updateGameMap(ChessPos* pos);
    
    /**
     * 检查是否有玩家获胜
     * @return 是否有玩家获胜
     */
    bool checkWin();
};

#endif // CHESS_H
