//
// Created by Nick on 12/15/2015.
//
#include <iostream>
#include <string>

#include "Resource.h"
#include "Agent.h"
#include "Piece.h"
using namespace std;
namespace Gaming {
    unsigned int Piece::__idGen = 0;
    Piece::Piece(const Game &g, const Position &p) : __game(g)
    {
        __position = p;
        __id = __idGen++;
        __finished = false;
    }
    std::ostream &operator<<(ostream &os, const Piece &piece)
    {
        piece.print(os);
        return os;
    }
    Piece::~Piece()
    {

    }


}