#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "particle.hh"
#include "globalVar.hh"

GlobVar GV;
float TIME = GV.getTime();
float WIN_W = GV.getWinW();
float WIN_H = GV.getWinH();

Particle::Particle(){
    mass = 1;
    radius = 1;
    pos_x = WIN_H/2;
    pos_y = WIN_W/2;
    vel_x = 0;
    vel_y = 0;
    accel_x = 0;
    accel_y = 0;
}

Particle::Particle(float _mass, float _radius, 
                    float _pos_x, float _pos_y,
                    float _vel_x, float _vel_y,
                    float _accel_x, float _accel_y){
    mass = _mass;
    radius = _radius;
    pos_x = _pos_x;
    pos_y = _pos_y;
    vel_x = _vel_x;
    vel_y = _vel_y;
    accel_x = _accel_x;
    accel_y = _accel_y;
}

// get methods
float Particle::getMass(){return mass;}
float Particle::getRadius(){return radius;}
float Particle::getPosX(){return pos_x;}
float Particle::getPosY(){return pos_y;}
float Particle::getVelX(){return vel_x;}
float Particle::getVelY(){return vel_y;}
float Particle::getAccelX(){return accel_x;}
float Particle::getAccelY(){return accel_y;}

// set methods
void Particle::setMass(float m){mass = m;}
void Particle::setRadius(float r){radius = r;}
void Particle::setPos(float x, float y){
    pos_x = x;
    pos_y = y;
}

void Particle::setVel(float vx, float vy){
    vel_x = vx;
    vel_y = vy;
}

void Particle::setAccel(float ax, float ay){
    accel_x = ax;
    accel_y = ay;
}


// Move methods
void Particle::periodicVolume(){
    if (pos_x+radius >= WIN_W){pos_x = 0;}
    if (pos_y+radius >= WIN_H){pos_y = 0;}
    if (pos_x+radius <= 0){pos_x = WIN_W;}
    if (pos_y+radius <= 0){pos_y = WIN_H;}
}

void Particle::wallsVolume(){
    if (pos_x+radius >= WIN_W || pos_x <= 0){vel_x *= -1;}
    if (pos_y+radius >= WIN_H || pos_y <= 0){vel_y *= -1;}
}

void Particle::updatePos(){
    pos_x -= vel_x*TIME;            
    pos_y -= vel_y*TIME;
    wallsVolume();
}

void Particle::updateVel(){
    vel_x += accel_x*TIME;            
    vel_y += accel_y*TIME;            
}

void Particle::moveRight(){
    pos_x -= abs(vel_x)*TIME; 
}
void Particle::moveLeft(){
    pos_x += abs(vel_x)*TIME; 
}
void Particle::moveUp(){
    pos_y -= abs(vel_y)*TIME; 
}
void Particle::moveDown(){
    pos_y += abs(vel_y)*TIME; 
}
void Particle::stepBack(){
    accel_x *= -1;
    accel_y *= -1;
    updateVel();
    updatePos();
    accel_x *= -1;
    accel_y *= -1;
    updateVel();
}


// accelartion methods
void Particle::accelRight(){
    vel_x -= abs(accel_x)*TIME; 
}
void Particle::accelLeft(){
    vel_x += abs(accel_x)*TIME; 
}
void Particle::accelUp(){
    vel_y -= abs(accel_y)*TIME; 
}
void Particle::accelDown(){
    vel_y += abs(accel_y)*TIME; 
}

//Collison method
void Particle::flipDirection(){
    vel_x *=-1;
    vel_y *=-1;
}

void Particle::flipDirectionX(){
    vel_x *=-1;
}

void Particle::flipDirectionY(){
    vel_y *=-1;
}

// Apllied Forces
void Particle::setAirFriction(float _fric_par){
    air_fric_x = -_fric_par*vel_x; 
    air_fric_y = -_fric_par*vel_y; 
}

void Particle::setGravity(float _g){
    gravity = -mass*_g; 
}


void Particle::updateForces(){
    ext_F_x = air_fric_x;
    ext_F_y = air_fric_y + gravity;
}

void Particle::updateAccel(){
    accel_x = ext_F_x/mass;
    accel_y = ext_F_y/mass;
}