//
//
// Created by Nick on 12/15/2015.
//
#include <iostream>
#include <string>

#include "Piece.h"
#include "Agent.h"
#include "Resource.h"

using namespace std;
namespace Gaming
{
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;
    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p)
    {
           __capacity = capacity;
    }

    Piece &Resource::operator*(Piece &other) {
        other.interact(this);
        return *this;
    }

    Piece &Resource::interact(Agent *agent) {
        agent->addEnergy(this->getCapacity());
        this->finish();
        return *this;
    }

    Piece &Resource::interact(Resource *resource) {
        return *this;
    }
    Resource::~Resource() {

    }
    void Resource::age()
    {
        __capacity /= RESOURCE_SPOIL_FACTOR;
        if(__capacity < .1)
        {
            __capacity = 0;
        }
    }

    double Resource::consume() {
        this->finish();
        return __capacity;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }
}

