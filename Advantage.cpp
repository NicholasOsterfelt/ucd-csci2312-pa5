//
// Created by Nick on 12/15/2015.
//
#include <iostream>
#include <string>

#include "Advantage.h"

using namespace std;
namespace Gaming
{
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
    const char Advantage::ADVANTAGE_ID = 'D';
    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    {
    }
    void Advantage::print(ostream & os) const
    {
        os << ADVANTAGE_ID << __id;
    }
    Advantage::~Advantage()
    {

    }

    double Advantage::getCapacity() const {
        return __capacity * ADVANTAGE_MULT_FACTOR;
    }

    double Advantage::consume() {
        return __capacity * ADVANTAGE_MULT_FACTOR;
    }
}

