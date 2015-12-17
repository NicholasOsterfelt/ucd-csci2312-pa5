//
// Created by Nick on 12/15/2015.
//
#include <cstdlib>

#include "DefaultAgentStrategy.h"

using namespace std;
namespace Gaming
{
    DefaultAgentStrategy::DefaultAgentStrategy()
    {

    }
    DefaultAgentStrategy::~DefaultAgentStrategy()
    {

    }
    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const
    {
        bool noMove = true;
        int desiredIndex = -1;
        std::vector<int> advantageIndices;
        std::vector<int> foodIndices;
        std::vector<int> simpleIndices;
        std::vector<int> emptyIndices;
        for(int n = 0; n < s.array.size(); n++)
        {
            int temp = n;
            if(s.array[n] == ADVANTAGE)
                advantageIndices.push_back(temp);
            if(s.array[n] == FOOD)
                foodIndices.push_back(temp);
            if(s.array[n] == SIMPLE)
                simpleIndices.push_back(temp);
            if(s.array[n] == EMPTY)
                emptyIndices.push_back(temp);
        }
        if(!emptyIndices.empty())
        {
            desiredIndex = emptyIndices[rand() % emptyIndices.size()];
        }
        if(!simpleIndices.empty())
        {
            desiredIndex = simpleIndices[rand() % simpleIndices.size()];
        }
        if(!foodIndices.empty())
        {
            desiredIndex = foodIndices[rand() % foodIndices.size()];
        }
        if(!advantageIndices.empty())
        {
            desiredIndex = advantageIndices[rand() % advantageIndices.size()];
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