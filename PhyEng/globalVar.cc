#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "globalVar.hh"

GlobVar::GlobVar(){
    // delta time
    TIME = 0.05;
    // The Window hight
    WIN_H = 1000;
    // The Window wide
    WIN_W = 1400;
}

float GlobVar::getTime(){return TIME;}
float GlobVar::getWinH(){return WIN_H;}
float GlobVar::getWinW(){return WIN_W;}
