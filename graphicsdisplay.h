//
// Created by User on 2020-03-28.
//

#ifndef Q4_GRAPHICSDISPLAY_H
#define Q4_GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include <cstddef>
#include "subject.h"
#include <string>
#include "window.h"

class Cell;

class GraphicsDisplay : public Observer<Info, State> {
    Xwindow xw;
    int cellSize;
    int gridSize;
public:
    GraphicsDisplay(int gridSize, int cellSize = 20);
    void notify(Subject<Info, State> &whoFrom) override;
};


#endif
