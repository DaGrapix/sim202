#ifndef define CLASSES_HPP
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

class box{
    public:
        int level;
        double center[3];
        double mass_center[3];
        double mass;
        particle* p_particle;
        box* p_sub_box;
        box* p_sister_box;
        double* force();
        void append_particle(particle& part);
        void pop_particle(particle& part);
};

bool is_in_box(particle& p, box& b);

#endif