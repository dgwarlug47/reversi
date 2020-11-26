//
// Created by User on 2020-03-25.
//
#include "grid.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;
Grid::~Grid(){
    delete td;
    delete gd;
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
    if ( colour == Colour::NoColour ){
        throw "Cannot assign Cell to NoColour";
    }
    // this is the case when someone plays a piece that is already occupied
    // it throws an error that it is caught by the main function
    if(r < 0 or r > size - 1 or c < 0 or c > size -1){
        throw "invalid move";
    }
    if(theGrid[r][c].getInfo().colour != Colour::NoColour){
        throw "invalid move";
    }
    numberOfPlays++;
    theGrid[r][c].setPiece(colour);
    theGrid[r][c].notify(theGrid[r][c]);
}

void Grid::setObserver(Observer<Info, State> *ob){
    this->ob = ob;
}
bool Grid::isFull() const {
    if(size*size == numberOfPlays + 4){
        return true;
    }
    return false;
}
Colour Grid::whoWon() const{
    int numberOfBlackPieces = 0;
    int numberOfWhitePieces = 0;
    for (int r = 0; r < size; r++){
        for (int c = 0; c < size; c++){
            if(theGrid[r][c].getInfo().colour == Colour::White){
                numberOfWhitePieces ++;
            }
            else{
                numberOfBlackPieces++;
            }
        }
    }
    if (numberOfBlackPieces > numberOfWhitePieces){
        return Colour::Black;
    }
    else if(numberOfWhitePieces > numberOfBlackPieces){
        return Colour ::White;
    }
    else{
        return Colour ::NoColour;
    }
}

void Grid::init(size_t n) {
    vector<Cell> v;
    size = n;
    numberOfPlays = 0;
    // when you are constructing the Grid for the second time, you have to remove the contents of the first one, this is for that
    theGrid.clear();
    delete td;
    //
    // allocates the space for a new grid
    for (size_t r = 0; r < n; r++){
        for (size_t c = 0; c < n; c++){
            Cell cell = Cell(r ,c);
            v.emplace_back(cell);

        }
        theGrid.emplace_back(v);
        v.clear();
    }
    // add the starting black and white pieces
    theGrid[n/2 - 1][n/2 - 1].setPiece(Colour::Black);
    theGrid[n/2 - 1][n/2].setPiece(Colour::White);
    theGrid[n/2][n/2 - 1].setPiece(Colour::White);
    theGrid[n/2][n/2].setPiece(Colour::Black);

    td = new TextDisplay(size);
    gd = new GraphicsDisplay(size);
    attachCells(n);
    // making new td
}
// this method adds all of the observers of each cell.
void Grid::attachCells(size_t n) {
    for (size_t r = 0; r < n; r++) {
        for (size_t c = 0; c < n; c++) {
            try {
                theGrid[r][c].attach(&theGrid.at(r - 1).at(c - 1));
            }
            catch (out_of_range e) {}
            try {
                theGrid[r][c].attach(&theGrid.at(r - 1).at(c));
            }
            catch (out_of_range e) {}
            try {
                theGrid[r][c].attach(&theGrid.at(r - 1).at(c + 1));
            }
            catch (out_of_range e) {}
            try {
                theGrid[r][c].attach(&theGrid.at(r + 1).at(c - 1));
            }
            catch (out_of_range e) {}
            try {
                theGrid[r][c].attach(&theGrid.at(r + 1).at(c));
            }
            catch(out_of_range e) {}
            try {
                theGrid[r][c].attach(&theGrid.at(r + 1).at(c + 1));
            }
            catch (out_of_range e) {}
            try {
                theGrid[r][c].attach(&theGrid.at(r).at(c - 1));
            }
            catch (out_of_range e) {}
            try {
                theGrid[r][c].attach(&theGrid.at(r).at(c + 1));
            }
            catch (out_of_range e) {}
            theGrid[r][c].attach(td);
            theGrid[r][c].attach(gd);
        }

    }
}


void Grid::toggle(size_t r , size_t c){
    if(Colour::NoColour == theGrid[r][c].getInfo().colour){
        throw "Can't toggle a NoColour cell";
    }
    else{
        if(Colour::Black == theGrid[r][c].getInfo().colour){
            theGrid[r][c].setPiece(Colour::White);
        }
        else{
            theGrid[r][c].setPiece(Colour::White);
        }
    }
}

std::ostream &operator<<(std::ostream &out, const Grid &g){
    out << *g.td;
    return out;
}
