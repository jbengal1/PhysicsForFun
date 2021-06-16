#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "interaction.hh"
#include "particle.hh"
#include "globalVar.hh"

Interaction::Interaction(){
    a = 1;
};
Interaction::Interaction(float _a){
    a = _a;
};

void Interaction::ElasticCol(Particle &_p1, Particle &_p2){
    float distance = sqrtf(powf(_p1.getPosX() - _p2.getPosX(), 2) + powf(_p1.getPosY() - _p2.getPosY(), 2) ); 
    float R = _p1.getRadius() + _p2.getRadius();
    if(distance <= R){
        _p1.stepBack();
        _p2.stepBack();
        _p1.flipDirection();
        _p2.flipDirection();
    }           
}