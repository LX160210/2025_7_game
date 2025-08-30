#ifndef CHESSPOS_H
#define CHESSPOS_H

/**
 * ChessPos类 - 棋子位置类
 * 用于表示棋盘上的位置坐标
 */
class ChessPos {
public:
    int row;  // 行坐标
    int col;  // 列坐标
    
    /**
     * 构造函数
     * @param r 行坐标，默认为0
     * @param c 列坐标，默认为0
     */
    ChessPos(int r = 0, int c = 0) : row(r), col(c) {}
};

/**
 * chess_kind_t枚举定义
 * 用于表示棋子的类型
 */
typedef enum {
    CHESS_WHITE = -1,  // 白棋（AI棋子）
    CHESS_BLACK = 1    // 黑棋（玩家棋子）
} chess_kind_t;

#endif // CHESSPOS_H
