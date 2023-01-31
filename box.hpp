#ifndef BOX_HPP
#define BOX_HPP
#include "particle.hpp"

double LENGTH = 10;

class box{
    public:
        int level;
        vector<double> center;
        vector<double> mass_center;
        double mass;
        particle* p_particle;
        box* p_sub_box;
        box* p_sister_box;


        void erase_box();
        vector<vector<double>> sub_box_centers();
        // constructors
        box();
        box(int level, vector<double> center, vector<double> mass_center, double mass, particle* p_particle, box* p_sub_box, box* p_sister_box );
        //destructor
        ~box();

        double* force();
        void append_particle(particle& part);
        void pop_particle(particle& part);
        void mass_center_calculation()
};

bool is_in_box(particle& p, box& b);

#endif