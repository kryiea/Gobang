//
// Created by 86195 on 2023/2/11.
//

#ifndef GOBANG_CHESS_H
#define GOBANG_CHESS_H

#include <graphics.h>
#include <vector>

using namespace std;

typedef enum{
    CHESS_WHITE = -1, // 白色
    CHESS_BLACK = 1 //黑色
}chess_kind_t;

struct  ChessPos{
    int row;
    int col;
};

class Chess {
public:

    //构造函数
    Chess(int gradeSize, int marginX, int marginY, float chessSize);

    //棋盘的初始化：加载棋盘的图片资源，初始化棋盘的相关数据
    void init();

    //判断指定坐标x(x,y), 是否有效点击
    //判断是有效点击，把有效点击的位置（行列）保存在参数pos中
    bool clickBoard(int x, int y, ChessPos* pos);

    //在棋盘的知指定位置（pos），落子（kind）
    void chessDown(ChessPos* pos, chess_kind_t);

    //棋盘的大小（13线，15线，19线）
    int getGradeSize();

    //获取指定位置是黑棋，还是白棋，还是空白
    int getChessData(ChessPos* pos);
    int getChessData(int row, int col);

    //判断棋局是否结束
    bool checkOver();

private:
    //棋盘尺寸
    int gradeSize;
    int margin_x; // 49
    int margin_y;//49
    float chessSize; // 棋子大小（棋盘方格大小）

    IMAGE chessBlackImg;
    IMAGE chessWhiteImg;

    //存储当前游戏棋盘和棋子的情况 空白为 0，黑子为 1，白子 -1
    vector<vector<int>> chessMap;

    //标示下棋方， true：黑棋方   false：AI（Ai方）
    bool playerFlag;

    void updateGameMap(ChessPos *pos);
};


#endif //GOBANG_CHESS_H
