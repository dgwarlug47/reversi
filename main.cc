#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  int turn;
  Colour colour;
  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
        // Add code here
        if(n%2 == 0 && n > 3) {
            turn = 0;
            g.init(n);
        }
        else{
            continue;
        }
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      if(turn == 0){
          colour = Colour::White;
      }
      else{
          colour = Colour::Black;
      }
      try {
          g.setPiece(r, c, colour);
      }
      catch(char const* e){
          continue;
      }
      if(g.isFull()){
          switch (g.whoWon()){
              case Colour::Black:
                  std::cout << "Black Wins!" << std::endl;
                  break;
              case Colour::White:
                  std::cout << "White Wins!";
                  break;
              case Colour::NoColour:
                  std::cout << "Tie!";
                  break;
          }
	  std::cout << g;
          break;
      }
    }
    else{
        continue;
    }
    std::cout << g;
    turn = 1 - turn;
  }
  }
  catch (ios::failure &) {} 



}
