#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <cmath>
#include "vecteur.hpp"
#include "constants.hpp"

using namespace std;

class particle{
    public:
        //mass
        double mass;
        
        //position
        vecteur<double> position;

        //speed
        vecteur<double> speed;

        //force
        vecteur<double> force;

        //successive positions taken by the particle
        vecteur<vecteur<double>> successive_positions;

        //pointer to the next particle
        particle* p_next_particle;

        //printing options
        void print(ostream& out=cout);
        friend ostream& operator <<(ostream & out, particle & particle_);

        //constructors
        particle();
        particle(vecteur<double> position_vecteur, vecteur<double> speed_vecteur, vecteur<double> force_vecteur);
        particle(vecteur<double> position_vecteur, vecteur<double> speed_vecteur, vecteur<double> force_vecteur, double mass_);

        //reinitialisation of the particle
        void erase_particle();

        //destructor
        ~particle();

        //operator override
        bool operator ==(particle& part);

        void set_position(vector<double> pos);
        void set_speed(vector<double> sp);
};



///////////////////////////////////////////////////////////////
//////////////////    Implémentation      /////////////////////
///////////////////////////////////////////////////////////////



//Reinitialising a particle
void particle::erase_particle(){
    if (position.empty()==false){
        position.clear();
    }
    if (speed.empty()==false){
        speed.clear();
    }
    if (force.empty()==false){
        force.clear();
    }
    if (successive_positions.empty()==false){
        successive_positions.clear();
    }
    p_next_particle = nullptr;
}

//Constructors
particle::particle(){
    erase_particle();
    position = vecteur<double>(3, 0.0);
    speed = vecteur<double>(3, 0.0);
    force = vecteur<double>(3, 0.0);
    mass = MASS;

    vecteur<double> default_vecteur = vecteur<double>(3,0);
    successive_positions = vecteur<vecteur<double>>(1, default_vecteur);
    p_next_particle = nullptr;
}

particle::particle(vecteur<double> position_vecteur, vecteur<double> speed_vecteur, vecteur<double> force_vecteur){
    erase_particle();
    position = position_vecteur;
    speed = speed_vecteur;
    force = force_vecteur;
    mass = MASS;
}

particle::particle(vecteur<double> position_vecteur, vecteur<double> speed_vecteur, vecteur<double> force_vecteur, double mass_){
    erase_particle();
    position = position_vecteur;
    speed = speed_vecteur;
    force = force_vecteur;
    mass = mass_;
}

//Destructor
particle::~particle(){
    erase_particle();
};


void particle::print(ostream& out){
    out << "position :     [";
    for (int i = 0; i <= 1; i++){
        out << position[i] << ", ";
    }
    out << position[2] << "]" << endl;

    out << "speed :        [";
    for (int i = 0; i <= 1; i++){
        out << speed[i] << ", ";
    }
    out << speed[2] << "]" << endl;

    out << "force :        [";
    for (int i = 0; i <= 1; i++){
        out << force[i] << ", ";
    }
    out << force[2] << "]" << endl;
    out << "mass :         " << mass << endl;
}

bool particle::operator ==(particle& part){
    if (mass != part.mass){
        return false;
    }
    if (not(position == part.position)){
        return false;
    }
    if (not(speed == part.speed)){
        return false;
    }
    if (not(force == part.force)){
        return false;
    }
    if (not(successive_positions == part.successive_positions)){
        return false;
    }
    if (p_next_particle != part.p_next_particle){
        return false;
    }
    return true;
}

ostream& operator <<(ostream& out, particle& particle_){
    particle_.print(out);
    return out;
}

void particle::set_position(vector<double> pos){
    position[0] = pos[0];
    position[1] = pos[1];
    position[2] = pos[2];
}

void particle::set_speed(vector<double> sp){
    speed[0] = sp[0];
    speed[1] = sp[1];
    speed[2] = sp[2];
}

#endif