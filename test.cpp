#include <stdio.h>
#include "particle.hpp"

int main(){
    particle p = particle();

    vector<double> position_vector = vector<double>(3,1);
    vector<double> speed_vector = vector<double>(3,2);
    vector<double> force_vector = vector<double>(3,3);

    particle q = particle(position_vector, speed_vector, force_vector);

    cout << p << endl << q << endl;

}