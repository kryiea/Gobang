//
// Created by 86195 on 2023/2/11.
//

#include "../h/AI.h"

void AI::init(Chess *chess) {
    this->chess = chess;
    int size = chess->getGradeSize();

    for (int i = 0; i < size; ++i) {
        vector<int> row;
        for (int j = 0; j < size; ++j) {
            row.push_back(0);
        }
        scoreMap.push_back(row);
    }
}

void AI::go() {
    ChessPos pos = think();
    Sleep(1000); //假装思考
    chess->chessDown(&pos, CHESS_WHITE);
}

void AI::calculateScore()
{
    // 统计玩家或者电脑连成的子
    int personNum = 0;  // 玩家连成子的个数
    int botNum = 0;     // AI连成子的个数
    int emptyNum = 0;   // 各方向空白位的个数

    // 清空评分数组
    for (int i = 0; i < scoreMap.size(); i++) {
        for (int j = 0; j < scoreMap[i].size(); j++) {
            scoreMap[i][j] = 0;
        }
    }

    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
        {
            // 空白点就算
            if (chess->getChessData(row, col) == 0) {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++) {
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;

                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子
                            // 对黑棋评分（正反两个方向）
                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row + i * y;
                                int curCol = col + i * x;
                                if (curRow >= 0 && curRow < size &&
                                    curCol >= 0 && curCol < size &&
                                    chess->getChessData(curRow, curCol) == 1) // 真人玩家的子
                                {
                                    personNum++;
                                }
                                else if (curRow >= 0 && curRow < size &&
                                         curCol >= 0 && curCol < size &&
                                         chess->getChessData(curRow, curCol) == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row - i * y;
                                int curCol = col - i * x;
                                if (curRow >= 0 && curRow < size &&
                                    curCol >= 0 && curCol < size &&
                                    chess->getChessData(curRow, curCol) == 1) // 真人玩家的子
                                {
                                    personNum++;
                                }
                                else if (curRow >= 0 && curRow < size &&
                                         curCol >= 0 && curCol < size &&
                                         chess->getChessData(curRow, curCol) == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (personNum == 1)                      // 杀二
                                scoreMap[row][col] += 10;
                            else if (personNum == 2)                 // 杀三
                            {
                                if (emptyNum == 1)
                                    scoreMap[row][col] += 30;
                                else if (emptyNum == 2)
                                    scoreMap[row][col] += 40;
                            }
                            else if (personNum == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    scoreMap[row][col] += 60;
                                else if (emptyNum == 2)
                                    scoreMap[row][col] += 200;
                            }
                            else if (personNum == 4)                 // 杀五
                                scoreMap[row][col] += 20000;

                            // 进行一次清空
                            emptyNum = 0;

                            // 对白棋评分
                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row + i * y;
                                int curCol = col + i * x;
                                if (curRow > 0 && curRow < size &&
                                    curCol > 0 && curCol < size &&
                                    chess->getChessData(curRow, curCol) == -1) // 玩家的子
                                {
                                    botNum++;
                                }
                                else if (curRow > 0 && curRow < size &&
                                         curCol > 0 && curCol < size &&
                                         chess->getChessData(curRow, curCol) == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                int curRow = row - i * y;
                                int curCol = col - i * x;
                                if (curRow > 0 && curRow < size &&
                                    curCol > 0 && curCol < size &&
                                    chess->getChessData(curRow, curCol) == -1) // 玩家的子
                                {
                                    botNum++;
                                }
                                else if (curRow > 0 && curRow < size &&
                                         curCol > 0 && curCol < size &&
                                         chess->getChessData(curRow, curCol) == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (botNum == 0)                      // 普通下子
                                scoreMap[row][col] += 5;
                            else if (botNum == 1)                 // 活二
                                scoreMap[row][col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1)                // 死三
                                    scoreMap[row][col] += 25;
                                else if (emptyNum == 2)
                                    scoreMap[row][col] += 50;  // 活三
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1)                // 死四
                                    scoreMap[row][col] += 55;
                                else if (emptyNum == 2)
                                    scoreMap[row][col] += 10000; // 活四
                            }
                            else if (botNum >= 4)
                                scoreMap[row][col] += 30000;   // 活五，应该具有最高优先级
                        }
                    }
                }
            }
        }
}

ChessPos AI::think() {
    // 计算评分
    calculateScore();

    // 从评分中找出最大分数的位置
    int maxScore = 0;
    //std::vector<std::pair<int, int>> maxPoints;
    vector<ChessPos> maxPoints;
    int k = 0;

    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            // 前提是这个坐标是空的
            if (chess->getChessData(row, col) == 0) {
                if (scoreMap[row][col] > maxScore)          // 找最大的数和坐标
                {
                    maxScore = scoreMap[row][col];
                    maxPoints.clear();
                    maxPoints.push_back(ChessPos(row, col));
                } else if (scoreMap[row][col] == maxScore) {   // 如果有多个最大的数，都存起来
                    maxPoints.push_back(ChessPos(row, col));
                }
            }
        }
    }

    // 随机落子，如果有多个点的话
    int index = rand() % maxPoints.size();
    return maxPoints[index];

}