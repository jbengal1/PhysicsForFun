#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "particle.hh"


class Interaction
{
    public:
        Interaction();
        Interaction(float _a);
        void ElasticCol(Particle* _p1, Particle* _p2);

    private:
        float a;
};