#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include <cmath>
#include "particle.hh"
#include "globalVar.hh"
#include "interaction.hh"

int sign(float x){
    if(x>0) return 1;
    if(x>0) return -1;
}

std::ofstream outFile("output.txt");



int main()
{   
    GlobVar GV;
    float TIME = GV.getTime();
    float WIN_W = GV.getWinW();
    float WIN_H = GV.getWinH();
   
    float g = 1;
    float b = 0.1;
    int N = 10;
    Particle particle1(10, 10, 
                        100, 500,
                        10, 0,
                        0, 0);
    Particle particle2(20, 20, 
                        400, 600,
                        0, 0,
                        0, 0);

    particle1.setGravity(g);
    particle2.setGravity(g);
    

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "SFML works!");
    sf::CircleShape shape1(particle1.getRadius());
    sf::CircleShape shape2(particle2.getRadius());
    
    shape1.setPosition(particle1.getPosX(),particle1.getPosY());
    shape2.setPosition(particle2.getPosX(),particle2.getPosY());
    shape1.setFillColor(sf::Color::Green);
    shape2.setFillColor(sf::Color::Red);
    
    Interaction interaction(1);

    while (window.isOpen())
    {
        //outFile << "";
        outFile << " Velocity is "<< particle2.getVelY() << " and hight is "<< WIN_H - particle2.getPosY() <<"\n";
        //particle1.setAirFriction(b);
        //particle2.setAirFriction(b);
        particle1.updateForces();
        particle2.updateForces();

        particle1.updateVel();
        particle1.updatePos();
        particle1.updateAccel();
        particle2.updateVel();
        particle2.updatePos();
        particle2.updateAccel();

        interaction.ElasticCol(&particle1, &particle2);


        shape1.setPosition(particle1.getPosX(),particle1.getPosY());
        shape2.setPosition(particle2.getPosX(),particle2.getPosY());
        
        sf::Event event;
        while (window.pollEvent(event))
        {    
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape1);
        window.draw(shape2);
        window.display();
    }
    
    return 0;
}