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

    cout << "level " << b.level << endl;

    b.append_particle(p2);
    cout << *(b.p_particle) << endl;

    b.append_particle(p1);
    
    if (b.p_particle==nullptr){
        cout << "NO PARTICLE" << endl;
    }

    if (b.p_sub_box==nullptr){
        cout << "NO SUB BOX" << endl;
    }

    if (b.p_sub_box->p_particle==nullptr){
        cout << "NO SUB PARTICLE" << endl;
    }

    //cout << *(b.p_sub_box->p_particle) << endl;

    box* ptr = b.p_sub_box;
    int i = 1;


    double quarter_box_length = (0.25)*(LENGTH/(pow(2,b.level)));
    cout << "quarter_box_length " << quarter_box_length << endl;

    vecteur<vecteur<double>> the_box = b.sub_box_centers();

    cout << the_box << endl;

    /*
    while (ptr != nullptr){
        cout << i << endl;
        i++;
        if (ptr->p_particle != nullptr){
            cout << *(ptr->p_particle) << endl;
        }
        ptr = ptr->p_sister_box;
    }

    
    b.append_particle(p2);

    cout << b.p_particle << endl;
    */
}