#ifndef PARTICLE_HH
#define PARTICLE_HH

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Particle
{
    public:
        Particle();
        Particle(double _mass, double _radius, 
                double _pos_x, double _pos_y,
                double _vel_x, double _vel_y,
                double _accel_x, double _accel_y);
        
        void Initialize(double _mass, double _radius, 
                double _pos_x, double _pos_y,
                double _vel_x, double _vel_y,
                double _accel_x, double _accel_y);
        
        // get methods
        double getMass();
        double getRadius();
        double getPosX();
        double getPosY();
        double getVelX();
        double getVelY();
        double getMomX();
        double getMomY();
        double getEnerg();
        double getEnergK();
        double getAccelX();
        double getAccelY();
        double getTempVelX(int n);
        double getTempVelY(int n);
        double getExtF_x();
        double getExtF_y();

        // set methods
        void setMass(double _m);
        void setRadius(double _r);
        void setPos(double _x, double _y);
        void setVel(double _vx, double _vy);
        void setAccel(double _ax, double _ay);

        // Move methods
        void periodicVolume();
        void wallsVolume();
        void updatePos();
        void updateVel();
        void updateMom(double mom_ext);
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();
        void stepBack();

        // accelartion methods
        void accelRight();
        void accelLeft();
        void accelUp();
        void accelDown();
                
        //Collison method
        void flipDirection();
        void flipDirectionX();
        void flipDirectionY();
        
        // Apllied Forces
        void setAirFriction(double _fric_par);
        void setGravity(double _g);

        //void setElasticColision(Particle *_p2);
        void setGravivtyInteraction(Particle *_p2);
        void setGSpringInteraction(Particle *_p2, double k_spring, double l_relaxed);

       
        void updateForces();
        void updateAccel();
        
        // Two particles functions
        double calc_rel_distance(Particle *_p2);
        double calc_rel_direction_x(Particle *_p2);
        double calc_rel_direction_y(Particle *_p2);

    private:
        double radius;
        double mass;
        double pos_x;
        double pos_y;
        double prestep_x;
        double prestep_y;
        double vel_x;
        double vel_y;
        double mom_x;
        double mom_y;
        double energy;
        double energy_k;
        double accel_x;
        double accel_y;
        double F_ext_x;
        double F_ext_y;
        double gravity = 0; //Earth gravity
        double f_G_x = 0; // Gravity between masses
        double f_G_y = 0;
        double f_spr_x = 0; // spring between masses
        double f_spr_y = 0;
        double air_fric_x = 0;
        double air_fric_y = 0;
        //changing array of last 5 velocities. Used to check if |v|~0 after some dt.
        int arr_size = 6;
        double temp_vel_x[6] = {1, 1, 1, 1, 1};
        double temp_vel_y[6] = {1, 1, 1, 1, 1};
        double vel_err = 0.001;

};
#endif