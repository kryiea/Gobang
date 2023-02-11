#include <iostream>
#include "Chess.h"
#include "Man.h"
#include "AI.h"
#include "ChessGame.h"

int main() {
  Chess chess(13,44,43,67.4);
  Man man;
  AI ai;
  ChessGame game(&man,&ai,&chess);

  game.play();

  return 0;
}
