#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include "../include/particle.hh"
#include "../include/globalVar.hh"
#include "../include/globalFunc.hh"


#include "../include/interaction.hh"

std::ofstream outFile1("output.txt");

void ElasticCol1d(Particle *_p1, Particle *_p2){
    double distance = abs(_p1->getPosX() - _p2->getPosX()) + 
                        _p1->getRadius()/2 - _p2->getRadius()/2 ;
    double R = _p1->getRadius()/2 + _p2->getRadius()/2;
    if(distance <= R){
        double m = _p1->getMass();
        double M = _p2->getMass();
        _p1->stepBack();
        _p2->stepBack();
        double ux_0 = _p1->getMomX();
        double vx_0 = _p2->getMomX();
        double uy_0 = _p1->getMomY();
        double vy_0 = _p2->getMomY();
        outFile1 << " momX1, momY1 before: " << ux_0 << ", " << uy_0 << std::endl;
        outFile1 << " momX2, momY2 before: " << vx_0 << ", " << vy_0 << std::endl;
        double rel_m = m/M;
        // double ux = ux_0*(1-rel_m)/(1+rel_m);
        // double vx = ux_0*2*rel_m/(1+rel_m);
        double ux = (m-M)*ux_0/(m+M) + 2*m*vx_0/(m+M);
        double vx = 2*M*ux_0/(m+M)-(m-M)*vx_0/(m+M);
        double uy = uy_0*(1-rel_m)/(1+rel_m);
        double vy = uy_0*2*rel_m/(1+rel_m);
        _p1->updateMom(ux);
        _p2->updateMom(vx);
        outFile1 << " momX1, momY1 after: " << ux << ", " << uy << std::endl;
        outFile1 << " momX2, momY2 after: " << vx << ", " << vy << std::endl;
        outFile1 << " tot mom after: " << ux+vx << std::endl;
    }           
}
