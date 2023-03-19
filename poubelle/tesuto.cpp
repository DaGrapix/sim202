#include <random>
#include <iostream>
#include <ostream>
#include "constants.hpp"

int main()
{
    srand(10);
    double lower_bound = 0;
    double upper_bound = 10;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;

    std::cout << unif(re) << std::endl;
    std::cout << unif(re) << std::endl;
    return 0;
}