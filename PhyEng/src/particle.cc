#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/particle.hh"
#include "../include/globalVar.hh"
#include "../include/globalFunc.hh"

GlobVar GV;
//GlobFunc GF;
double TIME = GV.getTime();
double WIN_W = GV.getWinW();
double WIN_H = GV.getWinH();

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

Particle::Particle(double _mass, double _radius, 
                    double _pos_x, double _pos_y,
                    double _vel_x, double _vel_y,
                    double _accel_x, double _accel_y){
    mass = _mass;
    radius = _radius;
    pos_x = _pos_x;
    pos_y = _pos_y;
    vel_x = _vel_x;
    vel_y = _vel_y;
    accel_x = _accel_x;
    accel_y = _accel_y;
    mom_x = mass*vel_x;
    mom_y = mass*vel_y;
}

void Particle::Initialize(double _mass, double _radius, 
                    double _pos_x, double _pos_y,
                    double _vel_x, double _vel_y,
                    double _accel_x, double _accel_y){
    mass = _mass;
    radius = _radius;
    pos_x = _pos_x;
    pos_y = _pos_y;
    vel_x = _vel_x;
    vel_y = _vel_y;
    accel_x = _accel_x;
    accel_y = _accel_y;
    mom_x = mass*vel_x;
    mom_y = mass*vel_y;
}

// get methods
double Particle::getMass(){return mass;}
double Particle::getRadius(){return radius;}
double Particle::getPosX(){return pos_x;}
double Particle::getPosY(){return pos_y;}
double Particle::getVelX(){return vel_x;}
double Particle::getVelY(){return vel_y;}
double Particle::getMomX(){return mom_x;}
double Particle::getMomY(){return mom_y;}
double Particle::getEnerg(){return energy;}
double Particle::getEnergK(){return energy_k;}
double Particle::getAccelX(){return accel_x;}
double Particle::getAccelY(){return accel_y;}
double Particle::getTempVelX(int n){return temp_vel_x[n];}
double Particle::getTempVelY(int n){return temp_vel_y[n];}
double Particle::getExtF_x(){return F_ext_x;}
double Particle::getExtF_y(){return F_ext_y;}

// set methods
void Particle::setMass(double m){mass = m;}
void Particle::setRadius(double r){radius = r;}
void Particle::setPos(double x, double y){
    pos_x = x;
    pos_y = y;
}

void Particle::setVel(double vx, double vy){
    vel_x = vx;
    vel_y = vy;
    mom_x = mass*vel_x;
    mom_y = mass*vel_y;
}

void Particle::setAccel(double ax, double ay){
    accel_x = ax;
    accel_y = ay;
}


// Move methods
void Particle::periodicVolume(){
    if (pos_x > WIN_W){pos_x = 0;}
    if (pos_y > WIN_H){pos_y = 0;}
    if (pos_x < 0){pos_x = WIN_W;}
    if (pos_y < 0){pos_y = WIN_H;}
}

void Particle::wallsVolume(){
    if (pos_x+radius >= WIN_W || pos_x <= 0){vel_x *= -1;}
    if (pos_y+radius >= WIN_H || pos_y <= 0){vel_y *= -1;}
}

void Particle::updatePos(){
    prestep_x = pos_x;
    prestep_y = pos_y;
    pos_x -= vel_x*TIME;            
    pos_y -= vel_y*TIME;
    wallsVolume();
    //periodicVolume();
}

void Particle::updateVel(){
    vel_x = mom_x/mass;
    vel_y = mom_y/mass;
    vel_x += accel_x*TIME;            
    vel_y += accel_y*TIME;
    energy_k = 0.5*mass*(vel_x*vel_x + vel_y*vel_y);
    energy = energy_k;
    // An array "recording" the last velocities of the particle.
    cyclicArr(temp_vel_x,vel_x, arr_size);
    cyclicArr(temp_vel_y,vel_y, arr_size);
    // If the last few velocities were smaller then some error "vel_err", then just set the velocity to be zero.
    // if(fabs(mean(temp_vel_x, arr_size))<=vel_err){vel_x = 0;}
    // if(fabs(mean(temp_vel_y, arr_size))<=vel_err){vel_y = 0;}

    /*GF.cyclicArr(temp_vel_x,vel_x, arr_size);
    GF.cyclicArr(temp_vel_y,vel_y, arr_size);
    if(fabs(GF.mean(temp_vel_x, arr_size))<=vel_err){vel_x = 0;}
    if(fabs(GF.mean(temp_vel_y, arr_size))<=vel_err){vel_y = 0;}
    */
}

void Particle::updateMom(double _mom){
    mom_x = _mom;
    //mom_y = _mom;
}

void Particle::moveRight(){
    pos_x -= fabs(vel_x)*TIME;
    prestep_x = pos_x; 
}
void Particle::moveLeft(){
    pos_x += fabs(vel_x)*TIME;
    prestep_x = pos_x;
}
void Particle::moveUp(){
    pos_y -= abs(vel_y)*TIME; 
    prestep_y = pos_y;
}
void Particle::moveDown(){
    pos_y += fabs(vel_y)*TIME;
    prestep_y = pos_y;
}
void Particle::stepBack(){
    pos_x = prestep_x;
    pos_y = prestep_y;
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
void Particle::setAirFriction(double _fric_par){
    air_fric_x = -_fric_par*vel_x; 
    air_fric_y = -_fric_par*vel_y; 
}

void Particle::setGravity(double _g){
    gravity = -mass*_g; 
}

//void Particle::setElasticColision(Particle *_p2){}

void Particle::setGravivtyInteraction(Particle *_p2){
    double G = 1.0;
    auto r_rel_size = this->calc_rel_distance(_p2);
    double f_G = G*(this->mass)*(_p2->mass)/r_rel_size;
    f_G_x = f_G*this->calc_rel_direction_x(_p2);
    f_G_y = f_G*this->calc_rel_direction_y(_p2);
}

void Particle::setGSpringInteraction(Particle *_p2, double k_spring, double l_relaxed){
    auto r_rel_size = this->calc_rel_distance(_p2);
    double f_spr = -k_spring*(l_relaxed - r_rel_size);
    f_spr_x = f_spr*this->calc_rel_direction_x(_p2);
    f_spr_y = f_spr*this->calc_rel_direction_y(_p2);
}

void Particle::updateForces(){
    F_ext_x = air_fric_x + f_G_x + f_spr_x;
    F_ext_y = air_fric_y + gravity + f_G_y + f_spr_y;
}

void Particle::updateAccel(){
    accel_x = F_ext_x/mass;
    accel_y = F_ext_y/mass;
}

double Particle::calc_rel_distance(Particle *_p2){
    auto x_rel = this->pos_x - _p2->pos_x;
    auto y_rel = this->pos_y - _p2->pos_y;
    auto r_rel = sqrt(pow(x_rel,2) + pow(y_rel,2));
    return r_rel;
}

double Particle::calc_rel_direction_x(Particle *_p2){
    auto x_rel = this->pos_x - _p2->pos_x;
    auto y_rel = this->pos_y - _p2->pos_y;
    auto r_rel = sqrt(pow(x_rel,2) + pow(y_rel,2));
    return x_rel/r_rel;
}

double Particle::calc_rel_direction_y(Particle *_p2){
    auto x_rel = this->pos_x - _p2->pos_x;
    auto y_rel = this->pos_y - _p2->pos_y;
    auto r_rel = sqrt(pow(x_rel,2) + pow(y_rel,2));
    return y_rel/r_rel;
}

