//
// Created by 86195 on 2023/2/11.
//

#include "../h/Man.h"

void Man::init(Chess *chess) {
    this->chess = chess;
}

void Man::go() {
    //等待玩家有效落子
    MOUSEMSG msg;
    ChessPos pos;

    while(1){
        msg = GetMouseMsg();
        if(msg.uMsg == WM_LBUTTONDOWN  && chess->clickBoard(msg.x, msg.y, &pos)){
            break;
        }
    }
    //落子
    chess->chessDown(&pos, CHESS_BLACK);
}
