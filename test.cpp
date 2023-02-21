#include <stdio.h>
#include "particle.hpp"
#include "vecteur.hpp"
#include "box.hpp"

int main(){
    /*
    particle p = particle();

    vector<double> position_vector = vector<double>(3,1);
    vector<double> speed_vector = vector<double>(3,2);
    vector<double> force_vector = vector<double>(3,3);

    particle q = particle(position_vector, speed_vector, force_vector);

    cout << p << endl << q << endl;


    vector<vector<int>> vec = vector<vector<int>>(3, vector<int> (4, 0));
    vec[0][0] = 1;

     for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout << vec[i][j] << " ";
        }
        cout<< endl;
    }


    cout << endl<< endl;

    vector<double> vec1 = {1, 2, 3};
    vector<double> vec2 = vector<double>(vec1);
    vec1 = 5*vec1;

    vec2[0] = 0;


    for(int i = 0; i < 4; i++)
    {
        cout << vec1[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < 4; i++)
    {
        cout << vec2[i] << " ";
    }
    */
    vecteur<double> v(3, 1);
    vecteur<double> u(3, 2);
    cout << v << endl;
    particle p1 = particle(v, v, v);
    particle p2 = particle(u,u,u);

    particle* p_p1 = &p1;
    p_p1->force = u;

    cout << "p1" << endl << p1 << endl;
    cout << "p2" << endl << p2 << endl;

    box b = box();

    cout << "p1 is in box : " << is_in_box(p1, b) << endl;
    cout << "p2 is in box : " << is_in_box(p2, b) << endl;

    cout << "level " << b.level << endl;

    b.append_particle(p1);
    cout << *(b.p_particle) << endl << endl;

    b.append_particle(p2);
    
    if (b.p_particle==nullptr){
        cout << "NO PARTICLE" << endl;
    }

    if (b.p_sub_box==nullptr){
        cout << "NO SUB BOX" << endl;
    }

    if (b.p_sub_box->p_particle==nullptr){
        cout << "NO SUB PARTICLE" << endl;
    }
    else{
        cout << "SUB PARTICLE" << endl;
        cout << b.p_sub_box->p_particle << endl;
        cout << b.p_sub_box->p_particle->position << endl;
        cout << *(b.p_sub_box->p_particle) << endl;
    }

    //cout << *(b.p_sub_box->p_particle) << endl;

    box* ptr = b.p_sub_box;

    vecteur<vecteur<double>> box_centers = b.sub_box_centers();
    cout << box_centers << endl;
    
    for (int j = 0; j <= 6; j++){
        cout << j << endl;
        j++;
        cout << ptr->p_particle << endl;
        ptr = ptr->p_sister_box;
    }

    
    cout << b.p_particle << endl;
}