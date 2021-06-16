#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Particle
{
    public:
        Particle();
        Particle(float _mass, float _radius, 
                float _pos_x, float _pos_y,
                float _vel_x, float _vel_y,
                float _accel_x, float _accel_y);

        // get methods
        float getMass();
        float getRadius();
        float getPosX();
        float getPosY();
        float getVelX();
        float getVelY();
        float getAccelX();
        float getAccelY();

        // set methods
        void setMass(float _m);
        void setRadius(float _r);
        void setPos(float _x, float _y);
        void setVel(float _vx, float _vy);
        void setAccel(float _ax, float _ay);

        // Move methods
        void periodicVolume();
        void wallsVolume();
        void updatePos();
        void updateVel();        
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
        void setAirFriction(float _fric_par);

        void setGravity(float _g);
        
        /*
        void setElasticColision(){

        }
        */
       
        void updateForces();
        void updateAccel();
        

    private:
        float radius;
        float mass;
        float pos_x;
        float pos_y;
        float vel_x;
        float vel_y;
        float accel_x;
        float accel_y;
        float ext_F_x;
        float ext_F_y;
        float gravity;
        float air_fric_x;
        float air_fric_y;

};
