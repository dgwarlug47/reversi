//
// Created by User on 2020-03-28.
//

#include "graphicsdisplay.h"

GraphicsDisplay::GraphicsDisplay(int gridSize, int cellSize): cellSize{cellSize}, gridSize{gridSize}, xw{gridSize*cellSize, gridSize*cellSize}{
    for(int r =0; r < gridSize; r ++){
        for(int c = 0; c < gridSize; c++){
            xw.fillRectangle(r*cellSize, c*cellSize, cellSize, cellSize, 4);
        }
    }
    xw.fillRectangle((gridSize/2 - 1)*cellSize,(gridSize/2 - 1)*cellSize,cellSize,cellSize,1);
    xw.fillRectangle((gridSize/2 - 1)*cellSize,(gridSize/2)*cellSize,cellSize,cellSize,0);
    xw.fillRectangle((gridSize/2)*cellSize,(gridSize/2 - 1)*cellSize,cellSize,cellSize,0);
    xw.fillRectangle((gridSize/2)*cellSize,(gridSize/2)*cellSize,cellSize,cellSize,1);
}

void GraphicsDisplay::notify(Subject<Info, State> &whoFrom){
    int colour;
    switch (whoFrom.getInfo().colour){
        case Colour::NoColour:
            return;
        case Colour::Black:
            colour = 1;
            break;
        case Colour::White:
            colour = 0;
            break;
    }
    xw.fillRectangle(whoFrom.getInfo().row*cellSize, whoFrom.getInfo().col*cellSize, cellSize, cellSize, colour);
}


