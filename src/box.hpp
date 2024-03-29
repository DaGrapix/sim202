#ifndef BOX_HPP
#define BOX_HPP


#include "constants.hpp"
#include "particle.hpp"
#include "vecteur.hpp"

class box{
    public:
        int level;
        vecteur<double> center;
        vecteur<double> mass_center;
        double mass;
        particle* p_particle;
        box* p_sub_box;
        box* p_sister_box;

        void initialize_box();

        //function returning the centers of all sub boxes
        vecteur<vecteur<double>> sub_box_centers();

        //constructors
        box();
        box(int level, vecteur<double> center, vecteur<double> mass_center, double mass, particle* p_particle, box* p_sub_box, box* p_sister_box );
        
        //destructor
        ~box();

        //approximate calculation of the force exerted by the box on a given particle
        void force(particle& part);

        //append a particle to a box, possibly subdividing it if it already contains a particle
        void append_particle(particle& part);

        //print option
        void print(ostream& out=cout);
};

//function returning true if a particle is contained in a box
bool is_in_box(particle& p, box& b);

//operator override
ostream& operator <<(ostream& out, box& box_){
    box_.print(out);
    return out;
}


///////////////////////////////////////////////////////////////
//////////////////    Implémentation      /////////////////////
///////////////////////////////////////////////////////////////

//box initializer
void box::initialize_box(){
    if(center.empty()==false){
        center.clear();
    }
    if(mass_center.empty()==false){
        mass_center.clear();
    }
    p_particle = nullptr;
    p_sub_box = nullptr;
    p_sister_box = nullptr;
    mass = 0.;
    level = 0;
}

//constructors
box::box(){
    initialize_box();
    level = 0;
    center = vecteur<double>(3,0.);
    mass_center = vecteur<double>(3,0.);
}

box::box(int level_, vecteur<double> center_, vecteur<double> mass_center_, double mass_, particle* p_particle_, box* p_sub_box_, box* p_sister_box_){
    level = level_;
    center = center_;
    mass_center = mass_center_;
    mass = mass_;
    p_particle = p_particle_;
    p_sub_box = p_sub_box_;
    p_sister_box = p_sister_box_;
}

//destructor
box::~box(){
    if (p_sub_box != nullptr){
        delete p_sub_box;
    }
    if (p_sister_box != nullptr){
        delete p_sister_box;
    }
}

//checks if a given particle is in a given box
bool is_in_box(particle& p, box& b){
    double half_side = (0.5)*(LENGTH/(pow(2,b.level)));
    if ((p.position[0] < b.center[0] - half_side) || (p.position[0] > b.center[0] + half_side)){
        return false;
    }
    if ((p.position[1] < b.center[1] - half_side) || (p.position[1] > b.center[1] + half_side)){
        return false;
    }
    if ((p.position[2] < b.center[2] - half_side) || (p.position[2] > b.center[2] + half_side)){
        return false;
    }
    return true;
}

//returns a matrix with each line being the position of the center of a sub box
vecteur<vecteur<double>> box::sub_box_centers(){
    double quarter_box_length = (0.25)*(LENGTH/(pow(2,level)));
    double x = center[0], y = center[1], z = center[2];
    vecteur<vecteur<double>> centers_matrix = vecteur<vecteur<double>>(8, vecteur<double>(3,0));
    centers_matrix[0][0] = x - quarter_box_length;
    centers_matrix[0][1] = y + quarter_box_length;
    centers_matrix[0][2] = z - quarter_box_length;

    centers_matrix[1][0] = x + quarter_box_length;
    centers_matrix[1][1] = y + quarter_box_length;
    centers_matrix[1][2] = z - quarter_box_length;

    centers_matrix[2][0] = x - quarter_box_length;
    centers_matrix[2][1] = y - quarter_box_length;
    centers_matrix[2][2] = z - quarter_box_length;

    centers_matrix[3][0] = x + quarter_box_length;
    centers_matrix[3][1] = y - quarter_box_length;
    centers_matrix[3][2] = z - quarter_box_length;

    centers_matrix[4][0] = x - quarter_box_length;
    centers_matrix[4][1] = y + quarter_box_length;
    centers_matrix[4][2] = z + quarter_box_length;

    centers_matrix[5][0] = x + quarter_box_length;
    centers_matrix[5][1] = y + quarter_box_length;
    centers_matrix[5][2] = z + quarter_box_length;

    centers_matrix[6][0] = x - quarter_box_length;
    centers_matrix[6][1] = y - quarter_box_length;
    centers_matrix[6][2] = z + quarter_box_length;

    centers_matrix[7][0] = x + quarter_box_length;
    centers_matrix[7][1] = y - quarter_box_length;
    centers_matrix[7][2] = z + quarter_box_length;

    return centers_matrix;
}

//append a particle to a box
void box::append_particle(particle& part){
    //if there is no sub_box and no prior particle in the box, we append the particle to it
    if ((p_sub_box==nullptr) && (p_particle==nullptr)){
        p_particle = &part;
        mass = part.mass;
        mass_center = part.position;
        return;
    }

    //if the box has sub_boxes, we find the one that contains the particle and call our function back on that box, we then adjust the center of mass of the current box
    else if (p_sub_box != nullptr){
        box* ptr = p_sub_box;
        while ((ptr != nullptr) && not(is_in_box(part, *(ptr)))){
            ptr = ptr->p_sister_box;
        }
        if (ptr != nullptr){
            ptr->append_particle(part);
            mass_center = (1.0/(mass + part.mass))*(mass*mass_center + part.mass*part.position);
            mass = mass + part.mass;
        }
    }

    //in the other case, if the box doesn't have sub_boxes, but already has a particle in it, we create the sub_boxes and append the two particles to their respective sub_boxes
    else if (p_sub_box == nullptr){
        vecteur<vecteur<double>> box_centers = sub_box_centers();

        //creating the last box
        int sub_level = level + 1;
        vecteur<double> sub_box_center = box_centers[7];
        vecteur<double> sub_box_mass_center = box_centers[7];
        int sub_box_mass = 0;
        particle* sub_box_p_particle = nullptr;
        box* sub_box_p_sub_box = nullptr;
        box* sub_box_p_sister_box = nullptr;
    
        box* p_last_box = new box(sub_level, sub_box_center, sub_box_mass_center, sub_box_mass, sub_box_p_particle, sub_box_p_sub_box, sub_box_p_sister_box);
        box* ptr = p_last_box;

        //creating the other boxes
        for (int i = 6; i >= 0; i--){
            vecteur<double> sub_box_center = box_centers[i];
            vecteur<double> sub_box_mass_center = box_centers[i];
            int sub_box_mass = 0.;
            particle* sub_box_p_particle = nullptr;
            box* sub_box_p_sub_box = nullptr;
            box* sub_box_p_sister_box = ptr;
            box* p_current_box = new box(sub_level, sub_box_center, sub_box_mass_center, sub_box_mass, sub_box_p_particle, sub_box_p_sub_box, sub_box_p_sister_box);
            ptr = p_current_box;
        }

        //the first box is the sub_box
        p_sub_box = ptr;

        //we remove the particle that was in the box and the function on the two particles
        particle* tmp = p_particle;
        mass_center = center;
        mass = 0.0;
        p_particle = nullptr;
        append_particle(part);
        append_particle(*tmp);
    }
}

// Approximate calculation of the force of a box on a given particle
void box::force(particle& part){
    if (this==nullptr){
        return;
    }
    //we initialise the force to 0 at the beginning
    if (level==0){
        part.force = vecteur<double>(3, 0.0);
    }
    if (p_particle != nullptr){
        //we split the cases on the particle to avoid singularities
        if (p_particle != &part){
            //classic force calculation, with the addition of an EPSILON to avoid singularities due to particle collisions
            vecteur<double> force_particle = (G*part.mass*p_particle->mass*(1/(pow(norm(p_particle->position - part.position), 3) + EPSILON)))*(p_particle->position - part.position);
            part.force = part.force + force_particle;
        }
    }
    //if the particle is in the sub-boxes, we call back the function on the sub_boxes
    else if (is_in_box(part, *this)){
        p_sub_box->force(part);
    }
    else{
        double box_size = LENGTH/pow(2, level);
        double distance = norm(part.position - mass_center);
        double ratio = box_size/distance;
        
        //If the following criterion is fulfilled, we assume that the box is far enough to the particle to consider approximating the resulting force
        //of the center of mass of the box, rather than the individual forces of each particle containned in the box
        if (ratio < THETA){
            vecteur<double> force_box = (G*part.mass*mass*(1/(pow(norm(mass_center - part.position), 3) + EPSILON)))*(mass_center - part.position);
            part.force = part.force + force_box;
        }
        //in the other case, we recursively call our function on the sub_boxes
        else{
            p_sub_box->force(part);
        }
    }
    //we finish by calculating the resulting force exerted by the sister boxes
    p_sister_box->force(part);
}


//print function
void box::print(ostream & out){
    cout << "level : " << level << endl;
    cout << "center : " << center << endl;
    cout << "mass_center : " << mass_center << endl;
    cout << "mass : " << mass << endl;
    if (p_particle != nullptr){
        cout << "####### particle #######" << endl;
        cout << *p_particle;
        cout << "########################" << endl;
    }
    else{
        cout << "no particle" << endl;
    }
    if (p_sub_box != nullptr){
        cout << "there is a sub box" << endl;
    }
    else{
        cout << "no sub box" << endl;
    }
    if (p_sister_box != nullptr){
        cout << "there is sister box" << endl;
    }
    else{
        cout << "no sister box" << endl;
    }
}


#endif