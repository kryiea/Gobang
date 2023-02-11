#include <iostream>
#include "../h/Chess.h"
#include "../h/Man.h"
#include "../h/AI.h"
#include "../h/ChessGame.h"


int main() {
  Chess chess(13,44,43,67.4);
  Man man;
  AI ai;
  ChessGame game(&man,&ai,&chess);

  game.play();

  return 0;
}
