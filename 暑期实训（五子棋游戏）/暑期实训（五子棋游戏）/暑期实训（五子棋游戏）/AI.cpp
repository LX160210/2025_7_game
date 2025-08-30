// 包含AI类头文件
#include "AI.h"
// 包含棋盘类头文件
#include "Chess.h"
// 包含算法库
#include <algorithm>
// 包含时间库，用于随机数种子
#include <ctime>
// 包含Windows API，用于Sleep函数
#include <Windows.h>

/**
 * AI类构造函数
 * 初始化AI对象，设置棋盘引用和评分地图
 */
AI::AI(Chess* chess) {
    this->chess = chess;              // 保存棋盘对象指针
    int size = chess->getGradeSize(); // 获取棋盘大小

    // 初始化评分地图，创建二维数组
    for (int i = 0; i < size; i++) {
        std::vector<int> row;         // 创建一行
        for (int j = 0; j < size; j++) {
            row.push_back(0);         // 初始化每个位置评分为0
        }
        scoreMap.push_back(row);      // 将行添加到评分地图
    }

    srand((unsigned)time(NULL));      // 设置随机数种子
}

/**
 * AI下棋函数
 * 执行AI的一次下棋操作
 */
void AI::go() {
    ChessPos pos = think();           // 通过思考函数获取最佳下棋位置
    Sleep(1000);                      // 暂停一秒，让玩家看到AI在思考
    chess->chessDown(&pos, CHESS_WHITE); // 在选定位置下白棋
}

/**
 * 计算评分函数
 * 为棋盘上每个空位置计算评分值，评分越高表示该位置越重要
 */
void AI::calculateScore() {
    int personNum = 0; // 玩家方(黑棋)在某方向上的连续棋子数
    int aiNum = 0;     // AI方(白棋)在某方向上的连续棋子数
    int emptyNum = 0;  // 空白位置数量
    int size = chess->getGradeSize(); // 获取棋盘大小

    // 清空评分地图，重新计算
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scoreMap[i][j] = 0; // 将所有位置评分重置为0
        }
    }

    // 遍历棋盘上每个空白位置
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (chess->getChessData(row, col) != 0) continue; // 跳过已有棋子的位置

            // 四个方向检查（水平、垂直、两个对角线）
            for (int dir = 0; dir < 4; dir++) {
                int dx = 0, dy = 0;
                // 根据方向设置坐标增量
                switch (dir) {
                case 0: dx = 1; dy = 0; break;   // 水平方向（左右）
                case 1: dx = 0; dy = 1; break;   // 垂直方向（上下）
                case 2: dx = 1; dy = 1; break;   // 主对角线方向（左上到右下）
                case 3: dx = 1; dy = -1; break;  // 副对角线方向（左下到右上）
                }

                personNum = 0; // 重置玩家棋子计数
                aiNum = 0;     // 重置AI棋子计数
                emptyNum = 0;  // 重置空位计数

                // 向正方向检查（根据dx,dy方向）
                for (int i = 1; i <= 4; i++) {
                    int curRow = row + i * dy; // 计算当前检查位置的行坐标
                    int curCol = col + i * dx; // 计算当前检查位置的列坐标
                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) { // 检查边界
                        if (chess->getChessData(curRow, curCol) == CHESS_BLACK) {
                            personNum++; // 发现玩家棋子，计数加1
                        }
                        else if (chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;  // 发现空位，计数加1并停止检查
                            break;
                        }
                        else {
                            break;       // 发现AI棋子，停止检查
                        }
                    }
                    else {
                        break;           // 超出边界，停止检查
                    }
                }

                // 向反方向检查（与上面方向相反）
                for (int i = 1; i <= 4; i++) {
                    int curRow = row - i * dy; // 计算反方向位置的行坐标
                    int curCol = col - i * dx; // 计算反方向位置的列坐标
                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) { // 检查边界
                        if (chess->getChessData(curRow, curCol) == CHESS_BLACK) {
                            personNum++; // 发现玩家棋子，计数加1
                        }
                        else if (chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++;  // 发现空位，计数加1并停止检查
                            break;
                        }
                        else {
                            break;       // 发现AI棋子，停止检查
                        }
                    }
                    else {
                        break;           // 超出边界，停止检查
                    }
                }

                // 根据玩家方棋子数量进行评分（防守评分）
                if (personNum == 1) { // 单子
                    scoreMap[row][col] += 10;  // 基础防守分
                }
                else if (personNum == 2) { // 连二
                    if (emptyNum == 1) {
                        scoreMap[row][col] += 30;  // 死连二
                    }
                    else if (emptyNum == 2) {
                        scoreMap[row][col] += 40;  // 活连二
                    }
                }
                else if (personNum == 3) { // 连三
                    if (emptyNum == 1) {
                        scoreMap[row][col] += 60;  // 死连三
                    }
                    else if (emptyNum == 2) {
                        scoreMap[row][col] += 5000; // 活连三，必须防守
                    }
                }
                else if (personNum == 4) { // 连四
                    scoreMap[row][col] += 20000; // 连四，必须立即防守
                }

                // 重新检查AI方棋子（进攻评分）
                emptyNum = 0; // 重置空位计数
                for (int i = 1; i <= 4; i++) {
                    int curRow = row + i * dy; // 计算正方向位置坐标
                    int curCol = col + i * dx;
                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) { // 检查边界
                        if (chess->getChessData(curRow, curCol) == CHESS_WHITE) {
                            aiNum++; // 发现AI棋子，计数加1
                        }
                        else if (chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++; // 发现空位，计数加1并停止
                            break;
                        }
                        else {
                            break;      // 发现玩家棋子，停止检查
                        }
                    }
                    else {
                        break;          // 超出边界，停止检查
                    }
                }

                // 向反方向检查AI棋子
                for (int i = 1; i <= 4; i++) {
                    int curRow = row - i * dy; // 计算反方向位置坐标
                    int curCol = col - i * dx;
                    if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size) { // 检查边界
                        if (chess->getChessData(curRow, curCol) == CHESS_WHITE) {
                            aiNum++; // 发现AI棋子，计数加1
                        }
                        else if (chess->getChessData(curRow, curCol) == 0) {
                            emptyNum++; // 发现空位，计数加1并停止
                            break;
                        }
                        else {
                            break;      // 发现玩家棋子，停止检查
                        }
                    }
                    else {
                        break;          // 超出边界，停止检查
                    }
                }

                // 根据AI方棋子数量进行评分（进攻评分）
                if (aiNum == 0) {
                    scoreMap[row][col] += 5;   // 空位基础分
                }
                else if (aiNum == 1) { // AI单子
                    scoreMap[row][col] += 10;  // 基础进攻分
                }
                else if (aiNum == 2) { // AI连二
                    if (emptyNum == 1) {
                        scoreMap[row][col] += 25;  // 死连二
                    }
                    else if (emptyNum == 2) {
                        scoreMap[row][col] += 50;  // 活连二
                    }
                }
                else if (aiNum == 3) { // AI连三
                    if (emptyNum == 1) {
                        scoreMap[row][col] += 55;  // 死连三
                    }
                    else if (emptyNum == 2) {
                        scoreMap[row][col] += 10000; // 活连三，优先进攻
                    }
                }
                else if (aiNum >= 4) { // AI连四或更多
                    scoreMap[row][col] += 30000; // 连四或胜利，最高优先级
                }
            }
        }
    }
}

/**
 * AI思考函数
 * 通过评分算法选择最佳下棋位置
 * @return 返回选择的最佳棋子位置
 */
ChessPos AI::think() {
    calculateScore(); // 计算所有空位的评分

    std::vector<ChessPos> maxPoints; // 存储最高评分的位置列表
    int maxScore = 0;                // 当前最高评分
    int size = chess->getGradeSize(); // 获取棋盘大小

    // 寻找最高评分位置
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (chess->getChessData(row, col) == 0) { // 只考虑空位置
                if (scoreMap[row][col] > maxScore) {
                    maxScore = scoreMap[row][col];        // 更新最高评分
                    maxPoints.clear();                    // 清空之前的候选位置
                    maxPoints.push_back(ChessPos(row, col)); // 添加新的最佳位置
                }
                else if (scoreMap[row][col] == maxScore) {
                    maxPoints.push_back(ChessPos(row, col)); // 添加同等评分的位置
                }
            }
        }
    }

    // 随机选择一个最高评分位置(避免每次都下同一个位置)
    int index = rand() % maxPoints.size();
    return maxPoints[index];
}