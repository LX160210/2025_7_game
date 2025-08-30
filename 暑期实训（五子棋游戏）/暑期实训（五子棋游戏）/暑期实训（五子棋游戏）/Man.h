#ifndef MAN_H
#define MAN_H

// 前向声明Chess类
class Chess;

/**
 * Man类 - 玩家类
 * 负责处理玩家的下棋操作，包括鼠标点击检测和棋子放置
 */
class Man {
public:
    /**
     * 构造函数
     * @param chess 棋盘对象指针
     */
    Man(Chess* chess);
    
    /**
     * 玩家下棋函数
     * 等待玩家鼠标点击，检测点击位置并下棋
     */
    void go();
    
private:
    Chess* chess;  // 棋盘对象指针
};

#endif // MAN_H