#include "vecteur.hpp"
#include "particle.hpp"
#include "box.hpp"
#include "plummer.hpp"
#include <random>
#include <string>
#include <fstream>

void export_to_csv(string filename, particle* p_particle){
    ofstream myFile(filename);
    
    particle* ptr = p_particle;
    while (ptr != nullptr){
        for (int i = 0; i <= N_ITER - 2; i++){
            myFile << ptr->successive_positions[i][0] << ";";
            myFile << ptr->successive_positions[i][1] << ";";
            myFile << ptr->successive_positions[i][2] << ";";
        }
        myFile << ptr->successive_positions[N_ITER - 1][0] << ";";
        myFile << ptr->successive_positions[N_ITER - 1][1] << ";";
        myFile << ptr->successive_positions[N_ITER - 1][2];
        myFile << "\n";
        
        ptr = ptr->p_next_particle;
    }
}

int main(){
    particle* p_first_particle = plummer_initialisation();
    particle* ptr = p_first_particle;

    for (int i = 1; i <= N_ITER - 1; i++){
        dynamic_iteration(p_first_particle, i);
    }
    string filename = "successive_positions.csv";
    export_to_csv(filename, p_first_particle);
}