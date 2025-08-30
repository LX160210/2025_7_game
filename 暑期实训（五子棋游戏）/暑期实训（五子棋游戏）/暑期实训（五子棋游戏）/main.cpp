#include "ChessGame.h"  // 包含游戏控制类定义
#include "Chess.h"      // 包含棋盘类定义
#include "Man.h"        // 包含玩家类定义
#include "AI.h"         // 包含AI类定义
#include <graphics.h>   // 包含EasyX图形库

/**
 * 主函数 - 程序入口点
 * 初始化游戏对象并启动五子棋游戏
 * @return 程序退出状态码
 */
int main() {
    // 创建棋盘对象(13x13棋盘，边距和棋子大小)
    Chess chess(13, 44, 43, 67.3);

    // 创建玩家和AI对象
    Man man(&chess);   // 创建玩家对象，关联棋盘
    AI ai(&chess);     // 创建AI对象，关联棋盘

    // 创建游戏对象并开始游戏
    ChessGame game(&man, &ai, &chess);  // 创建游戏控制器
    game.play();       // 启动游戏主循环

    // 关闭图形窗口
    closegraph();      // 清理图形资源
    return 0;          // 程序正常退出
}