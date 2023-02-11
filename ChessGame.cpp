//
// Created by 86195 on 2023/2/11.
//

#include "ChessGame.h"

void ChessGame::play() {
    chess->init();
    while(1){
        man->go();
        if(chess->checkOver()){
            chess->init();
            continue;
        }

        ai->go();
        if(chess->checkOver()){
            chess->init();
            continue;
        }
    }

}

ChessGame::ChessGame(Man * man, AI * ai, Chess * chess ){
    this->man = man;
    this->ai = ai;
    this->chess = chess;

    ai->init(chess);
    man->init(chess);

}
