#ifndef BOX_HPP
#define BOX_HPP
#include "particle.hpp"
#include "vecteur.hpp"

double LENGTH = 10;

class box{
    public:
        int level;
        vecteur<double> center;
        vecteur<double> mass_center;
        double mass;
        particle* p_particle;
        box* p_sub_box;
        box* p_sister_box;


        void erase_box();
        vecteur<vecteur<double>> sub_box_centers();
        // constructors
        box();
        box(int level, vecteur<double> center, vecteur<double> mass_center, double mass, particle* p_particle, box* p_sub_box, box* p_sister_box );
        //destructor
        ~box();

        double* force();
        void append_particle(particle& part);
        void pop_particle(particle& part);
        double mass_calculation();
        vecteur<double> mass_center_calculation();
        void print(ostream& out=cout);
};

bool is_in_box(particle& p, box& b);

ostream& operator <<(ostream& out, box& box_){
    box_.print(out);
    return out;
}

///////////////////////////////////////////////////////////////
//////////////////    Implémentation      /////////////////////
///////////////////////////////////////////////////////////////



//recursively delete a box and all of its sub_boxes and sister boxes
/*
void recursive_delete(box* p_box, box* p_mother_box=nullptr, box* parent_list, int depth){
    if (p_box==nullptr){
        return;
    }
    box* ptr = p_box;
    box* ptr_mother = p_mother_box;
    if (ptr->p_sub_box==nullptr){
        box* ptr_sis = p_box->p_sister_box;
        while (ptr != nullptr){
            delete ptr;
            ptr = ptr_sis;
            ptr_sis = ptr_sis->p_sister_box;
        }
        recursive_delete(p_mother_box, p_mother_mother_box);
    }
    else{
        recursive_delete(ptr->p_sub_box, ptr, p_mother_box);
    }
}
*/

box** remove_parent(box** parent_list, int depth){
    box** array = new box*[depth - 1];
    for (int i = 0; i <= depth - 2; i++){
        array[i] = parent_list[i];
    }
    return array;
}

box** add_parent(box** parent_list, int depth, box* p_parent){
    box** array = new box*[depth + 1];
    for (int i = 0; i <= depth - 1; i++){
        array[i] = parent_list[i];
    }
    array[depth] = p_parent;
    return array;
}

void recursive_delete(box* p_box, box** parent_list, int depth){
    if ((p_box==nullptr) && (depth = 0)){
        return;
    }
    box* ptr = p_box;
    box* ptr_parent = parent_list[depth - 1];
    if (ptr->p_sub_box==nullptr){
        box* ptr_sis = p_box->p_sister_box;
        while (ptr != nullptr){
            delete ptr;
            ptr = ptr_sis;
            ptr_sis = ptr_sis->p_sister_box;
        }
        box** new_parent_list = remove_parent(parent_list, depth);
        recursive_delete(ptr_parent, new_parent_list, depth - 1);
    }
    else{
        box** new_parent_list = add_parent(parent_list, depth, ptr);
        recursive_delete(ptr->p_sub_box, new_parent_list, depth + 1);
    }
}

//box reinitialiser
void box::erase_box(){
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



//Constructors
box::box(){
    erase_box();
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
    recursive_delete(this);
}

//checks if the particle is in the box
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

//append a particle in a box
void box::append_particle(particle& part){
    //If there is no sub_box and no prior particle in the box, we append the particle to it
    if ((p_sub_box==nullptr) && (p_particle==nullptr)){
        p_particle = &part;
        mass = mass + part.mass;
        mass_center = part.position;
        return;
    }

    //If the box has sub_boxes, we check which one can contain the particle and call our function back on that box, we then adjust the center of mass of the current box
    if (p_sub_box != nullptr){
        box* ptr = p_sub_box;
        while ((ptr != nullptr) && not(is_in_box(part, *(ptr)))){
            ptr = ptr->p_sister_box;
        }
        if (ptr != nullptr){
            ptr->append_particle(part);
            mass_center = (1.0/(mass + part.mass))*(mass*mass_center + part.mass*part.position);
        }
    }

    //In the other case, if the box doesn't have sub_boxes, but already has a particle in it, we create the sub_boxes and append the two particles to their respective sub_boxes
    else if (p_sub_box == nullptr){
        vecteur<vecteur<double>> box_centers = sub_box_centers();

        //Creating the last box
        int sub_level = level + 1;
        vecteur<double> sub_box_center = box_centers[7];
        vecteur<double> sub_box_mass_center = box_centers[7];
        int sub_box_mass = 0;
        particle* sub_box_p_particle = nullptr;
        box* sub_box_p_sub_box = nullptr;
        box* sub_box_p_sister_box = nullptr;

        box last_box = box(sub_level, sub_box_center, sub_box_mass_center, sub_box_mass, sub_box_p_particle, sub_box_p_sub_box, sub_box_p_sister_box);

        box* ptr = &last_box;

        //Creating the other boxes
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

        //The first box is the sub_box
        p_sub_box = ptr;

        //We call back our function on our two particles
        append_particle(part);
        append_particle(*p_particle);
        p_particle = nullptr;
    }

    else{
        cout << "problem" << endl;
    }
}


//Pas utile
/*
double box::mass_calculation(){
    // pour la masse d'une particule: ajouter masse dans la d�finition de la classe particle
    double m = 0;
    particle* ptr = p_particle;
    while (ptr != nullptr){
        m = m + ptr->mass;
        ptr = ptr->p_next_particle;
    }
    return m;
}

vecteur<double> box::mass_center_calculation(){
    vecteur<double> m_center = vecteur<double>(3,0);
    double half_box_length = (1/2)*(LENGTH/(pow(2,level)));
    particle* ptr = p_particle;
    while(ptr != nullptr){
        m_center[0] = m_center[0] + ptr->mass*(ptr->position[0]);
        m_center[1] = m_center[1] + ptr->mass*(ptr->position[1]);
        m_center[2] = m_center[2] + ptr->mass*(ptr->position[2]);
        ptr = ptr->p_next_particle;
    }

    m_center[0] = m_center[0]/mass;
    m_center[1] = m_center[1]/mass;
    m_center[2] = m_center[2]/mass;

    box* box_ptr = p_sub_box;
    while(box_ptr != nullptr){
        m_center = m_center + box_ptr->mass_center_calculation();
        box_ptr = box_ptr->p_sister_box;
    }
    return m_center;
}
*/

void box::pop_particle (particle& part){
    //If the box contains a particles (=> it doesn't have sub_boxes), then we check if it is the particle we want to pop
    if (&part == p_particle){
        p_particle = nullptr;
        mass = 0;
        mass_center = vecteur<double>(3,0);
    }

    //suppression de la particule dans la potentielle sous-boite contenant la particule
    else if (p_sub_box != nullptr){
        box* ptr = p_sub_box;
        while ((not is_in_box(part, *(ptr))) && ptr != nullptr){
            ptr = ptr->p_sister_box;
        }
        
        if (ptr == nullptr){
            cout << "Error, particle not found in box" << endl;
        }
        else{
            ptr->pop_particle(part);
            //calcul du nouveau centre de masse de la boite
            mass_center = (mass*mass_center - part.mass*part.position)/(mass - part.mass);
            //calcul de la nouvelle masse de la boite
            mass = mass - part.mass;
        }
    }
}


//print
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