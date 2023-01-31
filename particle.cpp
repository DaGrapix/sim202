#include "particle.hpp"
#include <cmath>
#include <vector>

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

particle::particle(){
    erase_particle();
    position = vector<double>(3, 0);
    speed = vector<double>(3, 0);
    force = vector<double>(3, 0);

    vector<double> default_vector = vector<double>(3,0);
    successive_positions = vector<vector<double>>(1, default_vector);
    p_next_particle = nullptr;
}

particle::particle(vector<double> position_vector, vector<double> speed_vector, vector<double> force_vector){
    erase_particle();
    position = position_vector;
    speed = speed_vector;
    force = force_vector;
}

particle::~particle(){
    erase_particle();
};