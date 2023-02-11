//
// Created by 86195 on 2023/2/11.
//

#include "Chess.h"
#include <mmsystem.h>
#include <cmath>

#pragma comment(lib, "winmm.lib")


void putimagePNG(int x, int y, IMAGE* picture){//x为载入图片的X坐标，y为Y坐标
    // 变量初始化
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
    int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
    int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
    int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
    int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
    int dstX = 0;    //在显存里像素的角标

    // 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //在显存里像素的角标
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
            int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + x) + (iy + y) * graphWidth; //在显存里像素的角标
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
                             | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
                             | (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
            }
        }
    }
}

void Chess::init() {
    initgraph(897,895);
    loadimage(0,"res/棋盘2,jpg");

    mciSendString("play res/start.wav",0,0,0);//需要修改字符集为多字符集

    loadimage(&chessBlackImg,"res/black.png",chessSize,chessSize,true);
    loadimage(&chessWhiteImg,"res/white.png",chessSize,chessSize,true);

    for (int i = 0; i < chessMap.size(); ++i) {
        for (int j = 0; j < chessMap.size(); ++j) {
            chessMap[i][j] = 0;
        }
    }

    playerFlag = true;
}

bool Chess::clickBoard(int x, int y, ChessPos * pos) {
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;

    int leftTopPosX = margin_x + chessSize * col;
    int leftTopPosY = margin_y + chessSize * row;
    int offset = chessSize * 0.4; // 20 鼠标点击的模拟距离上限（阈值）

    int len;
    int selectPos = false;

    do {
        //距离 左上角 的距离
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < offset) {
            pos->row = row;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0) {
                selectPos = true;
            }
            break;
        }

        //距离 右上角 的距离
        len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < offset) {
            pos->row = row;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0) {
                selectPos = true;
            }
            break;
        }

        // 距离左下角的距离
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
        if (len < offset) {
            pos->row = row + 1;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0) {
                selectPos = true;
            }
            break;
        }

        // 距离右下角的距离
        len = sqrt((x - leftTopPosX - chessSize) * (x - leftTopPosX - chessSize) +(y - leftTopPosY - chessSize) * (y - leftTopPosY - chessSize));
        if (len < offset) {
            pos->row = row + 1;
            pos->col = col + 1;

            if (chessMap[pos->row][pos->col] == 0) {
                selectPos = true;
            }
            break;
        }
    } while (0);

    return selectPos;
}


void Chess::chessDown(ChessPos *pos, chess_kind_t kind) {
    mciSendString("play res/down7.WAV",0,0,0);
    int x = margin_x + pos->row *chessSize - 0.5 * chessSize;
    int y = margin_y + pos->col *chessSize - 0.5 * chessSize;

    if(kind == CHESS_WHITE){
        putimagePNG(x,y,&chessWhiteImg);
    }
    else{
        putimagePNG(x,y,&chessBlackImg);
    }

    updateGameMap(pos);
}

int Chess::getGradeSize() {
    return 0;
}

int Chess::getChessData(ChessPos *pos) {
    return 0;
}

int Chess::getChessData(int row, int col) {
    return 0;
}

bool Chess::checkOver() {
    return false;
}

Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize) {
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;

    playerFlag = CHESS_BLACK;

    for(int i = 0; i<gradeSize; i++){
        vector<int>row;
        for(int j = 0; j<gradeSize; j++){
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}

void Chess::updateGameMap(ChessPos *pos) {
    //lastPos = *pos;
    chessMap[pos->row][pos->col] = playerFlag ? 1 : -1;
    playerFlag = !playerFlag; // 换手
}
