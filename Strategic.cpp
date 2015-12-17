//
// Created by Nick on 12/15/2015.
//
#include <iostream>
#include <string>

#include "Strategic.h"

using namespace std;
namespace Gaming
{
    const char Strategic::STRATEGIC_ID = 'T';
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s): Agent(g, p, energy)
    {
        __strategy = s;
    }
    void Strategic::print(ostream & os) const
    {
        os << STRATEGIC_ID << __id;
    }
    Strategic::~Strategic()
    {
        __strategy = nullptr;
    }
    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }
}

