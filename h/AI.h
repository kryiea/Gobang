//
// Created by 86195 on 2023/2/11.
//

#ifndef GOBANG_AI_H
#define GOBANG_AI_H


#include "Chess.h"

class AI {
public:
    void init(Chess* chess);
    void go();
private:
    Chess* chess;
    //存储个点位的评分情况，作为AI下棋依据
    vector<vector<int>> scoreMap;

    //统计点位得分
    void calculateScore();

    ChessPos think();  //private权限

};


#endif //GOBANG_AI_H
