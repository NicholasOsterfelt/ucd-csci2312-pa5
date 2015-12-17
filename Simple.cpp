//
// Created by Nick on 12/15/2015.
//
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Simple.h"

using namespace std;
namespace Gaming
{
    const char Simple::SIMPLE_ID = 'S';
    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy)
    {

    }
    void Simple::print(ostream & os) const
    {
        os << SIMPLE_ID << __id;
    }
    Simple::~Simple()
    {

    }

    ActionType Simple:: takeTurn(const Surroundings &s) const
    {
        bool noMove = true;
        int desiredIndex = 0;
        std::vector<int> resourceIndices;
        std::vector<int> emptyIndices;


        for(int n = 0; n < s.array.size(); n++)
        {
            int temp = n;
            if(s.array[n] == FOOD || s.array[n] == ADVANTAGE)
                resourceIndices.push_back(temp);
            if(s.array[n] == EMPTY)
                emptyIndices.push_back(temp);
        }
        if(resourceIndices.empty() && emptyIndices.empty())
        {
            return STAY;
        }
        if(!resourceIndices.empty())
        {
            desiredIndex = resourceIndices[rand() % resourceIndices.size()];
        }
        else
        {
            if(!emptyIndices.empty())
            {
               desiredIndex = emptyIndices[rand() % emptyIndices.size()];
            }
        }
        if(desiredIndex == 0)
            return NW;
        if(desiredIndex == 1)
            return N;
        if(desiredIndex == 2)
            return NE;
        if(desiredIndex == 3)
            return W;
        if(desiredIndex == 4)
            return STAY;
        if(desiredIndex == 5)
            return E;
        if(desiredIndex == 6)
            return SW;
        if(desiredIndex == 7)
            return S;
        if(desiredIndex == 8)
            return SE;
        return STAY;
    }
}

