#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/globalVar.hh"

GlobVar::GlobVar(){
    // delta time
    TIME = 0.05;
    // The Window hight
    WIN_H = 1000;
    // The Window wide
    WIN_W = 1400;
}

double GlobVar::getTime(){return TIME;}
double GlobVar::getWinH(){return WIN_H;}
double GlobVar::getWinW(){return WIN_W;}
