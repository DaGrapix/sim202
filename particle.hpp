#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include "vecteur.hpp"
#include <cmath>
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

        //reinitialisation of the particle
        void erase_particle();

        //destructor
        ~particle();
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
    position = vecteur<double>(3, 0);
    speed = vecteur<double>(3, 0);
    force = vecteur<double>(3, 0);

    vecteur<double> default_vecteur = vecteur<double>(3,0);
    successive_positions = vecteur<vecteur<double>>(1, default_vecteur);
    p_next_particle = nullptr;
}

particle::particle(vecteur<double> position_vecteur, vecteur<double> speed_vecteur, vecteur<double> force_vecteur){
    erase_particle();
    position = position_vecteur;
    speed = speed_vecteur;
    force = force_vecteur;
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
}

ostream& operator <<(ostream& out, particle& particle_){
    particle_.print(out);
    return out;
}

#endif