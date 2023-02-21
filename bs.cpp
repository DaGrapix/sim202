#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdbool.h>
#include "vecteur.hpp"
#include <cmath>

using namespace std;

void function(bool a, bool b=true){
    if (a==true){
        cout << "a is true" << endl;
    }
    else{
        cout << "a is false" << endl;
    }

    if (b==true){
        cout << "b is true" << endl;
    }
    else {
        cout << "b is false" << endl;
    }
    return;
}

int main(){
    bool a = true;

    function(a);

    int table[] = ;
    table[0]
}