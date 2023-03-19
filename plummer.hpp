#ifndef PLUMMER_HPP
#define PLUMMER__HPP


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include <cmath>
#include <random>
#include "vecteur.hpp"
#include "constants.hpp"

#define _USE_MATH_DEFINES

using namespace std;

double g(double x){
    return(pow(1-x*x ,3.5));
}

//initializes N particles so they respect the plummer auto-graviting distribution. Returns a pointer to the first particle.
particle* plummer_initialisation(){
    //random generator initialization
    double lower_bound = 0.0;
    double upper_bound = 1.0;
    std::default_random_engine re(SEED);
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    
    particle* p_last_particle = new particle();
    particle* p_previous_particle = nullptr;
    particle* p_current_particle = p_last_particle;

    for (int i = 0; i <= N-2; i++){
        p_previous_particle = p_current_particle;
        p_current_particle = new particle();
        p_current_particle->p_next_particle = p_previous_particle;

        //Step 1: calculation of r
        double X1 = unif(re);
        double a = pow(X1,-0.666) - 1.0;
        double r = pow(a,-0.5);

        //Step 2: Calculation of position coordinates
        double X2 = unif(re);
        double X3 = unif(re);

        double z = (1 - 2*X2)*r;
        double x = sqrt((r*r - z*z))*cos(2*M_PI*X3);
        double y = (r*r - z*z)*sin(2*M_PI*X3);

        //Step 3: Calculation of V, Ve and g(q)
        double Ve = sqrt(2.0)*pow(1.0 + r*r, -0.25);

        double X4 = unif(re);
        double X5 = unif(re);

        while(X5 >= 10*g(X4)){
            X4 = unif(re);
            X5 = unif(re);
        }

        double q=X4;

        double V=q*Ve;

        //Step 4: Calculation of speed coordinates
        double X6 = unif(re);
        double X7 = unif(re);

        double w=(1.0 - 2*X6)*V;
        double u=sqrt((V*V - w*w))*cos(2*M_PI*X7);
        double v=sqrt((V*V - w*w))*sin(2*M_PI*X7);

        p_current_particle->position[0] = x;
        p_current_particle->position[1] = y;
        p_current_particle->position[2] = z;

        p_current_particle->speed[0] = u;
        p_current_particle->speed[1] = v;
        p_current_particle->speed[2] = w;

        p_current_particle->position = ((3*M_PI/64.0)*M*M/E)*p_current_particle->position;
        p_current_particle->speed = ((64/(3.0*M_PI))*sqrt(E)/sqrt(M))*p_current_particle->speed;

        p_current_particle->successive_positions[0] = p_current_particle->position;
    }

    return(p_current_particle);
}

void dynamic_iteration(particle* p_particle, int iteration){
    //On each iteration, we destroy the tree and recreate it
    box b = box();

    particle* ptr = p_particle;

    while (ptr != nullptr){
        b.append_particle(*ptr);
        ptr = ptr->p_next_particle;
    }

    ptr = p_particle;
    while (ptr != nullptr){
        //calculate the force on particle *ptr
        b.force(*ptr);

        //update speed;
        ptr->speed = ptr->speed + (DT/ptr->mass)*ptr->force;

        //update position
        ptr->position = ptr->position + DT*ptr->speed;

        //save the new position
        ptr->successive_positions[iteration] = ptr->position;
        ptr = ptr->p_next_particle;
    }
}

#endif