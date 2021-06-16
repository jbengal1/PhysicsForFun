#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class GlobVar{
    public:
        GlobVar();

        float getTime();
        float getWinH();
        float getWinW();

    private:
        // delta time
        float TIME;
        // The Window hight
        float WIN_H;
        // The Window wide
        float WIN_W;
};
