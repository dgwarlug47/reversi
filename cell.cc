//
// Created by User on 2020-03-25.
//

#include "cell.h"
#include <string>
using namespace std;

Cell::Cell(size_t r, size_t c): r{r}, c{c} {}
void Cell::setPiece(Colour colour){this->colour = colour;}
void Cell::toggle(){
    if(Colour::NoColour == colour){
        throw "Can't toggle a NoColour cell";
    }
    else{
        if(Colour::Black == colour){
            this->colour = Colour::White;
        }
        else{
            this->colour = Colour ::Black;
        }
    }
}
void Cell::notify(Subject<Info, State> &whoFrom) {
    State helpperState;
    // the first case is when the cell that sent the notification is the same as the cell that received it, this is
    // case is treated in the first if statement, I just did this case as a tool to start he notifications
    // the second case is the usual one the notifier is a neighbour of the notified
    if(whoFrom.getInfo().row == getInfo().row && whoFrom.getInfo().col == getInfo().col){
        helpperState = {StateType::NewPiece, colour};
        setState(helpperState);
        return notifyObservers();
    }
    if(getInfo().colour == Colour::NoColour){return;}
    State whoFromState = whoFrom.getState();
    if(whoFromState.type == StateType::NewPiece){
        if(whoFromState.colour == getInfo().colour){
            return;
        }
        whoFromState.type = StateType::Relay;
        whoFromState.direction = getDirection(whoFrom);
        setState(whoFromState);
        return notifyObservers();
    }
    if(getDirection(whoFrom) != whoFromState.direction){
        return;
    }
    if(whoFromState.type == StateType::Relay){
        if(whoFromState.colour == getInfo().colour){
            helpperState.type = StateType::Reply;
            helpperState.direction = getOppositeDirection(whoFromState.direction);
            helpperState.colour = whoFromState.colour;
            setState(helpperState);
            return notifyObservers();
        }
        else{
            setState(whoFromState);
            return notifyObservers();
        }
    }
    if(whoFromState.type == StateType::Reply){
        if(getInfo().colour == whoFromState.colour){ return;}
        toggle();
        setState(whoFromState);
        return notifyObservers();
    }

}
// this method returns the direction from whoFrom to this
Direction Cell::getDirection(Subject<Info, State> & whoFrom) const {
    int row_diff = getInfo().row - whoFrom.getInfo().row;
    int col_diff = getInfo().col - whoFrom.getInfo().col;
    switch (row_diff) {
        case 0:
            switch (col_diff) {
                case 0:
                    break;
                case 1:
                    return Direction::S;
                    break;
                case -1:
                    return Direction::N;
                    break;
                default:
                    throw getError(whoFrom);
            }
            break;
        case 1:
            switch (col_diff) {
                case 0:
                    return Direction::E;
                    break;
                case 1:
                    return Direction::SE;
                    break;
                case -1:
                    return Direction::NE;
                    break;
                default:
                    throw getError(whoFrom);
            }
        case -1:
            switch (col_diff) {
                case 0:
                    return Direction::W;
                    break;
                case 1:
                    return Direction::SW;
                    break;
                case -1:
                    return Direction::NW;
                    break;
                default:
                    throw getError(whoFrom);
            }
        default:
            throw getError(whoFrom);
    }
}

string Cell::getError(Subject<Info, State> &whoFrom) const {
    string error = "Cell with position: ";
    error+= getInfo().row;
    error+= " ";
    error+= getInfo().col;
    error+= "is not a neighbour of ";
    error+= whoFrom.getInfo().row;
    error+= " ";
    error+= whoFrom.getInfo().col;
    return error;
}

Info Cell::getInfo() const {
    return Info{r,c,colour};
}

Direction Cell::getOppositeDirection(Direction direction) {
    switch (direction){
        case Direction::E:
            return Direction::W;
        case Direction ::NE:
            return Direction::SW;
        case Direction ::SE:
            return Direction::NW;
        case Direction ::N:
            return Direction :: S;
        case Direction ::W:
            return Direction::E;
        case Direction :: S:
            return Direction :: N;
        case Direction :: NW:
            return Direction :: SE;
        case Direction :: SW:
            return Direction ::NE;
    }

}
