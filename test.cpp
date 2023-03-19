#include <stdio.h>
#include "constants.hpp"
#include "particle.hpp"
#include "vecteur.hpp"
#include "box.hpp"
#include "plummer.hpp"

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

    srand(10);
    vecteur<double> v(3, 1.0);
    vecteur<double> u(3, -1.0);
    vecteur<double> w(3, 5.0);
    cout << v << endl;
    particle p1 = particle(v, v, v);
    particle p2 = particle(u, u, u);
    particle p3 = particle(w, w, w);

    particle p4 = particle();
    p4.set_position(vector<double>{9, 9, 9});

    particle p5 = particle();
    p5.set_position(vector<double>{-1, 1, 0});

    vecteur<double> k = p1.position - (1/2.0)*p2.position;
    cout << "diff : " << k << endl;

    cout << "p1" << endl << p1 << endl;
    cout << "p2" << endl << p2 << endl;
    cout << "p4" << endl << p4 << endl;

    box b = box();

    cout << "p1 is in box : " << is_in_box(p1, b) << endl;
    cout << "p2 is in box : " << is_in_box(p2, b) << endl;

    b.append_particle(p1);
    cout << b << endl << endl;

    b.append_particle(p2);
    cout << b << endl << endl;

    b.append_particle(p3);

    b.append_particle(p4);
    b.append_particle(p5);

    particle p6 = particle();
    b.append_particle(p6);

    b.force(p1);
    b.force(p2);
    b.force(p3);
    b.force(p4);
    b.force(p5);
    b.force(p6);

    cout << "force on p1    : " << p1.force << endl;
    cout << "force on p2    : " << p2.force << endl;
    cout << "force on p3    : " << p3.force << endl;
    cout << "force on p4    : " << p4.force << endl;
    cout << "force on p5    : " << p5.force << endl;
    cout << "force on p6    : " << p6.force << endl;


    cout << random_variable() << endl;
    cout << random_variable() << endl;

    /*
    particle* p_first_particle = plummer_initialisation();
    particle* ptr = p_first_particle;
    int counter = 1;
    while (ptr != nullptr){
        cout << counter << *ptr << endl;
        counter++;
        ptr = ptr->p_next_particle;
    }
    */
}