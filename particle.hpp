#ifndef PARTICLE_HPP
#define PARTICLE_HPP
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <vector>
#include <cmath>
using namespace std;


class particle{
    public:
        //position
        vector<double> position;
        //speed
        vector<double> speed;
        //force
        vector<double> force;
        //successive positions taken by the particle
        vector<vector<double>> successive_positions;
        //pointer to the next particle
        particle* p_next_particle;
        //printing options
        void print(ostream& out=cout);
        friend ostream& operator <<(ostream & out, const particle & particle_);
        //constructors
        particle();
        particle(vector<double> position_vector, vector<double> speed_vector, vector<double> force_vector);
        //reinitialisation of the particle
        void erase_particle();
        //destructor
        ~particle();
};

#endif