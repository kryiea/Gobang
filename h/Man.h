//
// Created by 86195 on 2023/2/11.
//

#ifndef GOBANG_MAN_H
#define GOBANG_MAN_H


#include "Chess.h"

class Man {
public:
    void init(Chess* chess);
    void go();

private:
    Chess* chess;
};


#endif //GOBANG_MAN_H
