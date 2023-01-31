#ifndef CLASSES_HPP
#define CLASSES_HPP
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <vector>
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
        //print
        void print();
        //constructors
        particle();
        particle(vector<double> position_vector, vector<double> speed_vector, vector<double> force_vector);
        //reinitialisation of the particle
        void erase_particle();
        //destructor
        ~particle();
};

#endif