#ifndef ASSEMBLAGE_HPP
#define ASSEMBLAGE_HPP


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include "vecteur.hpp"
#include "particle.hpp"
#include "box.hpp"
#include "plummer.hpp"
#include <cmath>
using namespace std;




void replace_part (box& b, box& b_current, particle& part){
    if(not is_in_box(part,b)){
        b_current.pop_particle(part);
        b.append_particle(part);
    }
}


void update_box(box& b){

    box ptr=b;

    if(ptr.p_sub_box!=nullptr){
        update_box(*ptr.p_sub_box);
        while(ptr.p_sister_box!=nullptr){
            ptr=*ptr.p_sister_box;
            update_box(ptr);
        }

    }else{
        if(ptr.p_particle!=nullptr){
            replace_part(b,ptr,*ptr.p_particle);
        }
        while(ptr.p_sister_box!=nullptr){
            ptr=*ptr.p_sister_box;
            if(ptr.p_particle!=nullptr){
                replace_part(b,ptr,*ptr.p_particle);
            }
    }
}
}








void Assemblage(box& b,int niter, vecteur<vecteur<vecteur<double>>> Part_Plummer){


double deltat=0.1;


cout<<"depart Assemblage"<<endl;

//Calculation of Vi1/2
particle* part=b.p_particle;
int i=0;
while(part!=nullptr){

    vecteur<double> force_buffer(3,0);
    cout<<"ok"<<endl;
    part->force=b.force(*part, force_buffer);
    cout<<Part_Plummer[i][1]<<"force"<<part->force<<endl;
    part->speed=Part_Plummer[i][1]+(deltat/(2*(part->mass)))*(part->force);
    part=part->p_next_particle;
    i=i+1;
}

cout<<"Assemblage Calculation of Vi12 ok"<<endl;

//Update of the particles and the boxes
for(int i=0; i<niter; i++ ){

    //Update speed, position and successive position of each particle
    particle* part=b.p_particle;
    while(part!=nullptr){
        part->position=part->position+deltat*(part->speed);
        part->speed=part->speed+(deltat/(2*(part->mass))*(part->force));
        vecteur<double> force_buffer(3,0);
        part->force=b.force(*part, force_buffer);
        part->successive_positions[i+1]=part->position;
        part=part->p_next_particle;
    }


    //Update of the boxes

    box ptr=b;

    if(ptr.p_sub_box!=nullptr){
        update_box(*ptr.p_sub_box);
        while(ptr.p_sister_box!=nullptr){
            ptr=*ptr.p_sister_box;
            update_box(ptr);
        }

    }

}
}










int main(){

    int N=3;  //Number of particles
    int niter=100; //Number of iterations (pour le calcul saute-mouton)

    box b = box();

    vecteur<vecteur<vecteur<double>>> Part_Plummer=Plummer_initialisation(N,1,1);

    vecteur<double> initial_acceleration(3,0);
    for (int i=0;i<N;i++){
        particle part_i=particle(Part_Plummer[i][0],Part_Plummer[i][1],initial_acceleration);
        b.append_particle(part_i);
    }




    vecteur<vecteur<vecteur<double>>> Successive_positions_of_all_particles=vecteur<vecteur<vecteur<double>>> (N,vecteur<vecteur<double>>(niter+1,vecteur<double>(3,0)));
    for(int i=0;i<N;i++){
        Successive_positions_of_all_particles[i][0]=Part_Plummer[i][0];
    }

    cout<<"Successive positions of all particles d�but" << endl<< Successive_positions_of_all_particles<<endl;

    Assemblage(b,niter,Part_Plummer);

    cout<<"Assemblage ok"<<endl;

    particle* part=b.p_particle;
    int i=0;
    while(part!=nullptr){
        for(int j=1;j<niter+1;j++){
            Successive_positions_of_all_particles[i][j]=part->successive_positions[j];
        }
        i=i+1;
        part=part->p_next_particle;
    }


    cout<<"Successive positions of all particles" << endl<< Successive_positions_of_all_particles<<endl;
    return(0);

}


#endif