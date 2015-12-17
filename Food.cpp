//
// Created by Nick on 12/15/2015.
//
#include <iostream>
#include <string>

#include "Food.h"

using namespace std;
namespace Gaming
{
    const char Food::FOOD_ID = 'F';
    Food::Food(const Game &g, const Position &p, double capactity) : Resource(g, p, capactity)
    {

    }
    void Food::print(ostream & os) const
    {
        os << FOOD_ID <<__id;
    }


    Food::~Food() {

    }
}

