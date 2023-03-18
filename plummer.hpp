#ifndef PLUMMER_HPP
#define PLUMMER__HPP


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include "vecteur.hpp"
#include <cmath>
#define _USE_MATH_DEFINES

using namespace std;


double random_variable(){
    double x=rand()%101; //x in the range 0 to 100, loi uniforme
    x=x/100;
    return(x);
}

double g(double x){
    return(pow(1-x*x,7/2));
}


//this function returns a N-vector, each component being a 2-vector which is the couple (position, speed) of a particle
vecteur<vecteur<vecteur<double>>> plummer_initialisation (double N,double M,double E){
    double R=1;
    double G=1;
    double m=1/N;

    vecteur<vecteur<vecteur<double>>> initial_particles=vecteur<vecteur<vecteur<double>>> (N, vecteur<vecteur<double>> (2,vecteur<double>(3,0.0)));

    for (int i=0;i<N;i++){
        //Step 1: calculation of r
        double X1=random_variable();
        double a=pow(X1,-0.666)-1;
        double r=pow(a,-0.5);
        cout<<"a"<<endl<<a<<endl;

        //Step 2: Calculation of position coordinates
        double X2=random_variable();
        double X3=random_variable();

        double z=(1-2*X2)*r;
        double x=sqrt((r*r-z*z))*cos(2*M_PI*X3);
        double y=(r*r-z*z)*sin(2*M_PI*X3);

        //Step 3: Calculation of V, Ve and g(q)
        double Ve=sqrt(2)*pow(1+r*r,-0.25);

        double X4=random_variable();
        double X5=random_variable();

        while(X5>=10*g(X4)){
        double X4=random_variable();
        double X5=random_variable();
        }

        double q=X4;

        double V=q*Ve;

        //Step 4: Calculation of speed coordinates
        double X6=random_variable();
        double X7=random_variable();

        double w=(1-2*X6)*V;
        double u=sqrt((V*V-w*w))*cos(2*M_PI*X7);
        double v=sqrt((V*V-w*w))*sin(2*M_PI*X7);

        //Update of initial_particles
        initial_particles[i][0][0]=x;
        initial_particles[i][0][1]=y;
        initial_particles[i][0][2]=z;

        initial_particles[i][1][0]=u;
        initial_particles[i][1][1]=v;
        initial_particles[i][1][2]=w;
    }
    return initial_particles;
}

/*
int main(){
vecteur<vecteur<vecteur<double>>> res=Plummer_initialisation(3,1,1);
cout<<"initialisation"<<endl<<res<<endl;
}
*/

#endif