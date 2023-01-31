#include <stdio.h>
#include <stdlib.h>
#include <iostream>
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
        particle(vector<double> position_vector, vector<double> speed_vector, vector<double> force_vector);
        particle();
        void erase_particle();

};

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
}

particle::particle(){
    erase_particle();
    position = vector<double>(3, 0);
    speed = vector<double>(3, 0);
    force = vector<double>(3, 0);

    vector<double> default_vector = vector<double>(3,0);
    successive_positions = vector<vector<double>>(1, default_vector);
}

int main(){
    int entier[3] = {1, 2, 3};
    for (int i = 0; i <= 10; i++){
        cout << entier[i] << endl;
    }
}