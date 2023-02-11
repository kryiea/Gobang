//
// Created by 86195 on 2023/2/11.
//

#ifndef GOBANG_CHESSGAME_H
#define GOBANG_CHESSGAME_H


#include "Man.h"
#include "AI.h"

class ChessGame {
public:
    ChessGame(Man*, AI*, Chess*);
    void play();

private:
    Man* man;
    AI* ai;
    Chess* chess;
};




#endif //GOBANG_CHESSGAME_H
