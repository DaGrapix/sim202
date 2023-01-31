#include "box.hpp"

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

void box::append_particle(particle& part){
    if (p_particle==nullptr){
        p_particle = &part;
        return;
    }
    if (p_sub_box != nullptr){
        box* ptr = p_sub_box;
        while ((not is_in_box(part, *(ptr))) && ptr != nullptr){
            ptr = (*ptr).p_sister_box;
        }
        if (ptr != nullptr){
            (*(ptr)).append_particle(part);
        }
    }
    else{
        double quarter_box_length = (1/4)*(LENGTH/(pow(2,b.level)));
        double x,y,z = center[0], center[1], center[2];
        double sub_box_centers[8][3];
        sub_box_centers[0][0] = x - quarter_box_length;
        sub_box_centers[0][1] = y + quarter_box_length;
        sub_box_centers[0][2] = z - quarter_box_length;

        sub_box_centers[1][0] = x + quarter_box_length;
        sub_box_centers[1][1] = y + quarter_box_length;
        sub_box_centers[1][2] = z - quarter_box_length;

        sub_box_centers[2][0] = x - quarter_box_length;
        sub_box_centers[2][1] = y - quarter_box_length;
        sub_box_centers[2][2] = z - quarter_box_length;

        sub_box_centers[3][0] = x + quarter_box_length;
        sub_box_centers[3][1] = y - quarter_box_length;
        sub_box_centers[3][2] = z - quarter_box_length;

        sub_box_centers[4][0] = x - quarter_box_length;
        sub_box_centers[4][1] = y + quarter_box_length;
        sub_box_centers[4][2] = z + quarter_box_length;

        sub_box_centers[5][0] = x + quarter_box_length;
        sub_box_centers[5][1] = y + quarter_box_length;
        sub_box_centers[5][2] = z + quarter_box_length;

        sub_box_centers[6][0] = x - quarter_box_length;
        sub_box_centers[6][1] = y - quarter_box_length;
        sub_box_centers[6][2] = z + quarter_box_length;

        sub_box_centers[7][0] = x + quarter_box_length;
        sub_box_centers[7][1] = y - quarter_box_length;
        sub_box_centers[7][2] = z + quarter_box_length;
    }
    
}