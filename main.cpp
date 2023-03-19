#include "vecteur.hpp"
#include "particle.hpp"
#include "box.hpp"
#include "plummer.hpp"
#include <random>
#include <string>
#include <fstream>

//the exported file is a csv. Each line of the file contains the successive positions x;y;z; of a particle.
//each line representing a given particle
void export_to_csv(string filename, particle* p_particle){
    ofstream myFile(filename + "_N_" + to_string(N) + "_NITER_" + to_string(N_ITER) + ".csv");
    
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

void test(particle* p_first_particle){
    particle* ptr1 = p_first_particle;
    particle* ptr2 = p_first_particle;
    int j = 0;
    vecteur<double> force_j = vecteur<double>(3, 0.0);
    while (ptr1 != nullptr){
        ptr2 = p_first_particle;
        while (ptr2 != nullptr){
            double r = norm(ptr1->position - ptr2->position);
            if (ptr1 != ptr2){
                force_j = force_j + (G*ptr1->mass*ptr2->mass*(1.0/(pow(r, 3))))*(ptr2->position - ptr1->position);
            }
            ptr2 = ptr2->p_next_particle;
        }
        cout << ptr1->force << force_j << endl;
        ptr1 = ptr1->p_next_particle;
        j++;
    }
}

int main(){
    particle* p_first_particle = plummer_initialisation();
    particle* ptr = p_first_particle;

    for (int i = 1; i <= N_ITER - 1; i++){
        dynamic_iteration(p_first_particle, i);
        //cout << p_first_particle->force << endl;

        //test(p_first_particle);
    }
    

    string filename = "successive_positions";
    export_to_csv(filename, p_first_particle);
}