//
// Created by User on 2020-03-25.
//
#include "textdisplay.h"

TextDisplay::TextDisplay(int n): gridSize{n} {
    std::vector<char> c;
    for (int s = 0; s < n; s++){
        c.emplace_back('-');
    }
    for (int s = 0; s < n; s++){
        theDisplay.emplace_back(c);
    }
    theDisplay[n/2 - 1][n/2 - 1] = 'B';
    theDisplay[n/2 - 1][n/2] = 'W';
    theDisplay[n/2][n/2 - 1] = 'W';
    theDisplay[n/2][n/2] = 'B';
}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
    if(whoNotified.getState().type == StateType::Reply || whoNotified.getState().type == StateType::NewPiece) {
        if (Colour::NoColour == whoNotified.getInfo().colour) {}
        else if (whoNotified.getInfo().colour == Colour::Black) {
            theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'B';
        }
        else {
            theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'W';
        }
    }
}
std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for(int r = 0; r < td.gridSize;  r++ ){
        for (int c = 0; c < td.gridSize; c++){
            out << td.theDisplay[r][c];
        }
        out << std::endl;
    }
    return out;
}
