#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

#include <cmath>
#include "include/particle.hh"
#include "include/globalVar.hh"
#include "include/globalFunc.hh"
#include "include/interaction.hh"


std::ofstream outFile("Energies.txt");

void initialize_particles(std::vector<Particle*> particles, double WIN_W, double WIN_H){ 
    int N = particles.size();
    for (int i = 0; i < N; i++){
        double rad = 20*(i+1);
        int sign = pow(-1, i+1);
        particles[i]->Initialize(rad, rad, 
                        500, 500,
                        // WIN_W/2 - rad, WIN_H/2 + sign*rad*(i+1),
                        0, 0,
                        0, 0);
    }
    particles[0]->setVel(0, -1);
    particles[1]->setVel(0, 1);
    particles[2]->setVel(0, 1);
}


int main(int argc,char** argv)
{   
    GlobVar GV;
    //GlobFunc GF;

    double TIME = GV.getTime();
    double WIN_W = GV.getWinW();
    double WIN_H = GV.getWinH();
   
    //double g = 9.8;
    double g = 0;
    double b = 0.1;
    double k = 0.1;
    double l = 10;
    int N = 3;
    int counter = 0;
    
    std::vector<Particle*> particles;
    for (int i = 0; i < N; i++){ 
        particles.push_back(new Particle());
        particles[i]->setGravity(g);
        particles[i]->setAirFriction(1);
    }
    initialize_particles(particles, WIN_W, WIN_H);
    //std::vector< sf::CircleShape > shapes;
    std::vector< sf::RectangleShape > shapes;
    for (int i = 0; i < N; i++){ 
        //sf::CircleShape shape_i(particles[i]->getRadius());
        sf::RectangleShape shape_i(sf::Vector2f(particles[i]->getRadius(), particles[i]->getRadius()));
        shape_i.setPosition(particles[i]->getPosX(),particles[i]->getPosY());        
        shape_i.setFillColor(sf::Color::Green);
        shapes.push_back(shape_i);
    }
    shapes[1].setFillColor(sf::Color::Red);
    
    double dis = abs(particles[0]->getPosX() - particles[1]->getPosX()) + 
                    particles[0]->getRadius()/2 - particles[1]->getRadius()/2 ;
    sf::RectangleShape line(sf::Vector2f(dis, 5));
    line.setPosition(particles[1]->getPosX() + particles[1]->getRadius(), 620);
    /*
    particles[0]->Initialize(0, 10, 
                        400, 400,
                        0.5, -0.5,
                        0, 0);
    
    particles[1]->Initialize(10, 10, 
                        700, 700,
                        -0.5, 0.5,
                        0, 0);
    */
    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "SFML works!");   
    

    /*
    Particle particle1(10, 10, 
                        400, 400,
                        0.5, -0.5,
                        0, 0);
    Particle particle2(10, 10, 
                        700, 700,
                        -0.5, 0.5,
                        0, 0);
    
    particle1.setGravity(0);
    particle2.setGravity(0);
    

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "SFML works!");
    sf::CircleShape shape1(particle1.getRadius());
    sf::CircleShape shape2(particle2.getRadius());
    
    shape1.setPosition(particle1.getPosX(),particle1.getPosY());
    shape2.setPosition(particle2.getPosX(),particle2.getPosY());
    shape1.setFillColor(sf::Color::Green);
    shape2.setFillColor(sf::Color::Red);
    
    std::vector< sf::CircleShape > shapes;

    shapes.push_back(shape1);
    shapes.push_back(shape2);
    */
    //Interaction interaction(1);
    outFile  << "First pos" << particles[1]->getPosX()<< " " << particles[1]->getPosY() << std::endl;
    int count=0;
    while (window.isOpen())
    {
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                if (j!=i){
                    //particles[i]->setGravivtyInteraction(particles[j]);        
                    //particles[i]->setGSpringInteraction(particles[j], k, l);        
                }
            }
            
            //particles[i].setGravivtyInteraction(particles[i+1]);
            //particle2.setGravivtyInteraction(particle1);
            particles[i]->updateForces();
            particles[i]->updateVel();
            particles[i]->updatePos();
            particles[i]->updateAccel();
            shapes[i].setPosition(particles[i]->getPosX(), particles[i]->getPosY());
        }
        for(int i=0; i<N; ++i){
            for(int j=i+1; j<N; ++j){
                if (i==1){outFile  << count << "pos" << particles[1]->getPosX()<< " " << particles[1]->getPosY() << std::endl;}
                ElasticCol1d(particles[i], particles[j]);
            }
        }
        count+=1;

        // outFile << particles[0]->getEnerg() << " "
        //         << particles[1]->getEnerg() << " "
        //         << particles[0]->getMomX() << " "
        //         << particles[1]->getMomX() 
        //         << std::endl;

        std::vector< sf::CircleShape* > trail;

        for(int i = 0; i < shapes.size(); i++){ 
            window.draw(shapes[i]); 
            trail.push_back(new sf::CircleShape(2));
            }
        
        dis = abs(particles[0]->getPosX() - particles[1]->getPosX()) + 
                    particles[0]->getRadius()/2 - particles[1]->getRadius()/2 ;
        line.setSize(sf::Vector2f(dis, 5));
        line.setPosition(particles[1]->getPosX() + particles[1]->getRadius(), 650);
        // window.draw(line); 

        /*
        sf::CircleShape* c1 = new sf::CircleShape(2);
        sf::CircleShape* c2 = new sf::CircleShape(2);
        
        if(counter%100==0){
            shapes.push_back(*c1);
            shapes.push_back(*c2);
            shapes[shapes.size()-2].setPosition(particles[0]->getPosX(),particles[0]->getPosY());
            shapes[shapes.size()-2].setFillColor(sf::Color::Green);
            shapes[shapes.size()-1].setPosition(particles[1]->getPosX(),particles[1]->getPosY());
            shapes[shapes.size()-1].setFillColor(sf::Color::Red);            
        }
        */
        window.display();
        window.clear();
        
        sf::Event event;
        while (window.pollEvent(event))
        {    
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        /*
        delete c1; 
        delete c2;
        */
        counter++;
    }
    
    return 0;
}