#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class GlobVar{
    public:
        GlobVar();

        double getTime();
        double getWinH();
        double getWinW();

    private:
        // delta time
        double TIME;
        // The Window hight
        double WIN_H;
        // The Window wide
        double WIN_W;
};
