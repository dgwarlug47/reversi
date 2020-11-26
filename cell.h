#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include <string>
using namespace std;

class Cell : public Subject<Info, State>, public Observer<Info, State> {
  const size_t r, c;
  Colour colour = Colour::NoColour;

  // Add other private members if necessary
  Direction getDirection(Subject<Info, State> &) const;
  string getError(Subject<Info, State> &) const;
  Direction getOppositeDirection(Direction direction);

 public:
  Cell(size_t r, size_t c);

  void setPiece(Colour colour);    // Place a piece of given colour here.
  void toggle();         // Toggles my colour.

  void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
                                                // when they've changed state
  Info getInfo() const override;
};

#endif
