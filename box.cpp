#include "box.hpp"

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
    mass = 0;
    level = 0;
}

//Constructors
box::box(){
    erase_box();
    level = 0;
    center = vector<double>(3,0);
    mass_center = vector<double>(3,0);
}

box::box(int level_, vector<double> center_, vector<double> mass_center_, double mass_, particle* p_particle_, box* p_sub_box_, box* p_sister_box_){
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
    erase_box();
}

//checks if the particle is in the box
bool is_in_box(particle& p, box& b){
    double half_side = (1/2)*(LENGTH/(pow(2,b.level)));
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
vector<vector<double>> box::sub_box_centers(){
    double quarter_box_length = (1/4)*(LENGTH/(pow(2,level)));
    double x = center[0], y = center[1], z = center[2];
    vector<vector<double>> centers_matrix = vector<vector<double>>(8, vector<double>(3,0));
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
    //If there us no prior particle in the box, we append the particle to it
    if (p_particle==nullptr){
        p_particle = &part;
        return;
    }
    //If the box has sub_boxes, we check which one can contain the particle and recall our function
    if (p_sub_box != nullptr){
        box* ptr = p_sub_box;
        while ((not is_in_box(part, *(ptr))) && ptr != nullptr){
            ptr = (*ptr).p_sister_box;
        }
        if (ptr != nullptr){
            (*ptr).append_particle(part);
        }
    }
    //In the other case, we create the sub_boxes
    else{
        vector<vector<double>> box_centers = sub_box_centers();

        //creating the last box
        int sub_level = level + 1;
        vector<double> sub_box_center = box_centers[7];
        vector<double> sub_box_mass_center = box_centers[7];
        int sub_box_mass = 0;
        particle* sub_box_p_particle = nullptr;
        box* sub_box_p_sub_box = nullptr;
        box* sub_box_p_sister_box = nullptr;

        box last_box = box(sub_level, sub_box_center, sub_box_mass_center, sub_box_mass, sub_box_p_particle, sub_box_p_sub_box, sub_box_p_sister_box);

        box* ptr = &last_box;

        for (int i = 6; i <= 0; i--){
            vector<double> sub_box_center = box_centers[i];
            vector<double> sub_box_mass_center = box_centers[i];
            int sub_box_mass = 0;
            particle* sub_box_p_particle = nullptr;
            box* sub_box_p_sub_box = nullptr;
            box* sub_box_p_sister_box = ptr;
            box current_box = box(sub_level, sub_box_center, sub_box_mass_center, sub_box_mass, sub_box_p_particle, sub_box_p_sub_box, sub_box_p_sister_box);
            ptr = &current_box;
        }

        p_sub_box = ptr;

        append_particle(part);
    }
}