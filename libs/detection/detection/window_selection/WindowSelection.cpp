//
// Created by vincent on 25-2-16.
//

#include "WindowSelection.h"

WindowSelection::WindowSelection(int frameHeight, int frameWidth, float horizon, float winHeight0, float winHeight1,
                                 float winWidth0, float winWidth1, int stepX, int stepY):
    frameHeight(frameHeight), frameWidth(frameWidth),
    winHeight0(winHeight0), winWidth0(winWidth0),
    winHeight1(winHeight1), winWidth1(winWidth1),
    stepX(stepX), stepY(stepY), horizon(horizon){}
