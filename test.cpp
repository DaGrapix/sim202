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

int main(){
    /*
    int entier[3] = {1, 2, 3};
    for (int i = 0; i <= 10; i++){
        cout << entier[i] << endl;
    }
    */

    particle p = particle();

    vector<double> position_vector = vector<double>(3,1);
    vector<double> speed_vector = vector<double>(3,2);
    vector<double> force_vector = vector<double>(3,3);

    particle q = particle(position_vector, speed_vector, force_vector);

    cout << p.position[1] << endl << q.position[1] << endl;

}