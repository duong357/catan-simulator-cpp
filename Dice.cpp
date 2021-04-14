//
// Created by heinz on 9/24/20.
//
using namespace std;

#include <cstdlib>
#include "Dice.h"

unsigned int Dice::roll(unsigned int maxValue)
{
    return (rand() % maxValue) + 1;
}
