#include "vecteur.hpp"
#include "particle.hpp"
#include "box.hpp"
#include "plummer.hpp"

double N = 10;
double M = 1;
double E = 10;

int main(){
    vecteur<vecteur<vecteur<double>>> position_speed = plummer_initialisation(N, M, E);
    particle last_particle = particle(position_speed[N-1][0], position_speed[N-1][1], vecteur<double>(3, 0.0));
    particle current_particle = last_particle;

    for (int i = N-2; i >= 1; i--){
        particle previous_particle = current_particle;
        particle current_particle = particle(position_speed[i][0], position_speed[i][1], vecteur<double>(3, 0.0));
        current_particle.p_next_particle = &previous_particle;

        cout << current_particle << endl;
    }
}