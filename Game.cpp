//
// Created by Nick on 12/15/2015.
//
#include <sstream>
#include <fstream>
#include <cstring>

#include "Gaming.h"
#include "Game.h"
#include "Agent.h"
#include "Strategic.h"
#include "Simple.h"
#include "Resource.h"
#include "Food.h"
#include "Advantage.h"
#include "Piece.h"
#include "Exceptions.h"
#include "AggressiveAgentStrategy.h"
#include "DefaultAgentStrategy.h"

using namespace std;
namespace Gaming {
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    Game::Game() {
        __width = 3;
        __height = 3;
        __numInitAgents = 0;
        __numInitResources = 0;
        __round = 0;
        vector<Piece *> temp(__width * __height, nullptr);
        __grid = temp;
        __status = PLAYING;

    }

    Game::Game(unsigned w, unsigned h, bool manual) {
        if (w < MIN_WIDTH || h < MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, w, h);
        }
        __width = w;
        __height = h;
        if(!manual)
        {
            __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
            __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        }
        else
        {
            __numInitResources =0;
            __numInitAgents = 0;
        }
        __round = 0;
        vector<Piece *> temp(__width * __height, nullptr);
        __grid = temp;
        if (!manual) {
            populate();
        }
    }

    Game::Game(const Game &g) {
        __width = g.__width;
        __height = g.__height;
        __numInitAgents = g.__numInitResources;
        __numInitResources = g.__numInitResources;
        __grid = g.__grid;
        __status = g.__status;
    }

    Game::~Game() {

    }

    ostream &operator<<(ostream &os, const Game &game) {
        Piece *p;
        os << "Round " << game.getRound() + 1 << ":" << endl;
        for (int n = 0; n < game.getHeight(); n++) {
            for (int c = 0; c < game.getWidth(); c++) {
                if (game.__grid[n * game.getWidth() + c] == nullptr) {
                    os << "[     ]";
                }
                else {
                    os << "[";
                    int length = 0;
                    std::ostringstream stream;
                    stream << *game.__grid[n * game.getWidth() + c];
                    string input = stream.str();
                    const char *str = input.c_str();
                    length = strlen(str);
                    if (length > 5) {
                        for (int i = 0; i < 5; i++) {
                            os << input.at(i);
                        }
                    }
                    else {
                        int count = 0;
                        for (int i = 0; i < length; i++) {
                            os << str[i];
                            count++;
                        }
                        while (count < 5) {
                            os << " ";
                            count++;
                        }
                    }

                    os << "]";
                }
            }
            os << endl;
        }
        os << "Status: " << game.getStatus();
        return os;
    }

    bool Game::addSimple(const Position &p) {
        if (p.x >= __height || p.y >= __width) {
            throw OutOfBoundsEx(__width, __height, p.x, p.y);
        }
        if (__grid[p.y + p.x * __width] != nullptr) {
            return false;
        }
        Simple *s = new Simple(*this, p, STARTING_AGENT_ENERGY);
        __grid[p.y + p.x * __width] = s;
        __numInitAgents++;
        return true;
    }

    bool Game::addSimple(unsigned x, unsigned y) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if (__grid[x + y * __width] != nullptr) {
            return false;
        }
        Position p(x, y);
        Simple *s = new Simple(*this, p, STARTING_AGENT_ENERGY);
        __grid[y + x * __width] = s;
        __numInitAgents++;
        return true;
    }

    bool Game::addStrategic(const Position &p, Strategy *s) {
        if (p.x >= __height || p.y >= __width) {
            throw OutOfBoundsEx(__width, __height, p.x, p.y);
        }
        if (__grid[p.y + p.x * __width] != nullptr) {
            return false;
        }
        Strategic *t = new Strategic(*this, p, STARTING_AGENT_ENERGY, s);
        __grid[p.y + p.x * __width] = t;
        __numInitAgents++;
        return true;
    }

    bool Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if (__grid[y + x * __width] != nullptr) {
            return false;
        }
        Position p(x, y);
        Strategic *t = new Strategic(*this, p, STARTING_AGENT_ENERGY, s);
        __grid[y + x * __width] = t;
        __numInitAgents++;
        return true;
    }

    bool Game::addFood(const Position &p) {
        if (p.x >= __height || p.y >= __width) {
            throw OutOfBoundsEx(__width, __height, p.x, p.y);
        }
        if (__grid[p.y + p.x * __width] != nullptr) {
            return false;
        }
        Food *s = new Food(*this, p, STARTING_RESOURCE_CAPACITY);
        __grid[p.x + p.y * __width] = s;
        __numInitResources++;
        return true;
    }

    bool Game::addFood(unsigned x, unsigned y) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if (__grid[y + x * __width] != nullptr) {
            return false;
        }
        Position p(x, y);
        Food *s = new Food(*this, p, STARTING_AGENT_ENERGY);
        __grid[y + x * __width] = s;
        __numInitResources++;
        return true;
    }

    bool Game::addAdvantage(const Position &p) {
        if (p.x >= __height || p.y >= __width) {
            throw OutOfBoundsEx(__width, __height, p.x, p.y);
        }
        if (__grid[p.y + p.x * __width] != nullptr) {
            return false;
        }
        Advantage *s = new Advantage(*this, p, STARTING_RESOURCE_CAPACITY);
        __grid[p.y + p.x * __width] = s;
        __numInitResources++;
        return true;
    }

    bool Game::addAdvantage(unsigned x, unsigned y) {
        if (x >= __height || y >= __width) {
            throw OutOfBoundsEx(__width, __height, x, y);
        }
        if (__grid[y + x * __width] != nullptr) {
            return false;
        }
        Position p(x, y);
        Advantage *s = new Advantage(*this, p, STARTING_RESOURCE_CAPACITY);
        __grid[y + x * __width] = s;
        __numInitResources++;
        return true;
    }

    const Surroundings Game::getSurroundings(const Position &p) const {
        Surroundings *s = new Surroundings();
        s->array[4] = SELF;

        if ((int) (p.x - 1) < 0 || (int) p.y - 1 < 0) {
            s->array[0] = INACCESSIBLE;
        }
        else if (__grid[(p.y - 1) + (p.x - 1) * __width] == nullptr)
            s->array[0] = EMPTY;
        else {
            s->array[0] = __grid[(p.y - 1) + (p.x - 1) * __width]->getType();
        }
        if ((int) p.x - 1 < 0) {
            s->array[1] = INACCESSIBLE;
        }
        else if (__grid[p.y + (p.x - 1) * __width] == nullptr)
            s->array[1] = EMPTY;
        else {
            s->array[1] = __grid[(p.y) + (p.x - 1) * __width]->getType();
        }
        if ((int) p.x - 1 < 0 || p.y + 1 > __width) {
            s->array[2] = INACCESSIBLE;
        }
        else if (__grid[p.y + 1 + (p.x - 1) * __width] == nullptr)
            s->array[2] = EMPTY;
        else {
            s->array[2] = __grid[(p.y + 1) + (p.x - 1) * __width]->getType();
        }
        if ((int) p.y - 1 < 0) {
            s->array[3] = INACCESSIBLE;
        }
        else if (__grid[p.y - 1 + (p.x) * __width] == nullptr)
            s->array[3] = EMPTY;
        else {
            s->array[3] = __grid[(p.y - 1) + (p.x) * __width]->getType();
        }
        if (p.y + 1 >= __width) {
            s->array[5] = INACCESSIBLE;
        }
        else if (__grid[p.y + 1 + (p.x) * __width] == nullptr)
            s->array[5] = EMPTY;
        else {
            s->array[5] = __grid[(p.y + 1) + (p.x) * __width]->getType();
        }
        if ((int) p.y - 1 < 0 || p.x + 1 >= __height) {
            s->array[6] = INACCESSIBLE;
        }
        else if (__grid[p.y - 1 + (p.x + 1) * __width] == nullptr)
            s->array[6] = EMPTY;
        else {
            s->array[6] = __grid[(p.y - 1) + (p.x + 1) * __width]->getType();
        }
        if (p.x + 1 >= __height) {
            s->array[7] = INACCESSIBLE;
        }
        else if (__grid[(p.y) + (p.x + 1) * __width] == nullptr)
            s->array[7] = EMPTY;
        else {
            if(p.y + (p.x+1) * __width > 8)
            {
                s->array[7] = EMPTY;
            }
            else
            s->array[7] = __grid[(p.y) + (p.x + 1) * __width]->getType();
        }
        if (p.y + 1 >= __width || p.x + 1 >= __height) {
            s->array[8] = INACCESSIBLE;
        } else if (__grid[p.y + 1 + (p.x + 1) * __width] == nullptr)
            s->array[8] = EMPTY;
        else {
            s->array[8] = __grid[(p.y + 1) + (p.x + 1) * __width]->getType();
        }
        return *s;
    }

    unsigned int Game::getNumAgents() const {
        unsigned int count = 0;
        return __numInitAgents;
    }

    unsigned int Game::getNumSimple() const {
        unsigned int count = 0;
        for (int n = 0; n < __grid.size(); n++) {
            if (__grid[n] != nullptr && (__grid[n]->getType() == SIMPLE)) {
                count++;
            }
        }
        return count;
    }

    unsigned int Game::getNumStrategic() const {
        unsigned int count = 0;
        for (int n = 0; n < __grid.size(); n++) {
            if (__grid[n] != nullptr && (__grid[n]->getType() == STRATEGIC)) {
                count++;
            }
        }
        return count;
    }

    unsigned int Game::getNumResources() {
        unsigned int count = 0;
        return __numInitResources;
        return count;
    }

    unsigned int Game::getNumPieces() const {
        unsigned int count = 0;
        for (int n = 0; n < __grid.size(); n++) {
            if (__grid[n] != nullptr) {
                count++;
            }
        }
        return count;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        if (ac == N) {
            if ((int) pos.x - 1 < 0) {
                return false;
            }
            return true;
        }
        if (ac == NW) {
            if ((int) pos.x - 1 < 0 || (int) pos.y - 1 < 0) {
                return false;
            }
            return true;

        }
        if (ac == NE) {
            if ((int) pos.x - 1 < 0 || (int) pos.y + 1 > __width) {
                return false;
            }
            return true;

        }
        if (ac == W) {
            if ((int) pos.y - 1 > __width) {
                return false;
            }
            return true;

        }
        if (ac == E) {
            if ((int) pos.y + 1 > __width) {
                return false;
            }
            return true;

        }
        if (ac == S) {
            if ((int) pos.x + 1 > __height) {
                return false;
            }
            return true;

        }
        if (ac == SW) {
            if ((int) pos.x + 1 > __height || (int) pos.y - 1 < 0) {
                return false;
            }
            return true;

        }
        if (ac == SE) {
            if ((int) pos.x + 1 > __height || (int) pos.y + 1 > __width) {
                return false;
            }
            return true;

        }
        if (ac == STAY) {
            return true;
        }
        return true;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const {
        if (isLegal(ac, pos)) {
            Position newPos(pos.x, pos.y);
            if (ac == NW) {
                newPos.x--;
                newPos.y--;
                return newPos;
            }
            if (ac == N) {
                newPos.x--;
                return newPos;
            }
            if (ac == NE) {
                newPos.x--;
                newPos.y++;
                return newPos;
            }
            if (ac == W) {
                newPos.y--;
                return newPos;
            }
            if (ac == E) {
                newPos.y++;
                return newPos;
            }
            if (ac == SW) {
                newPos.x++;
                newPos.y--;
                return newPos;
            }
            if (ac == S) {
                newPos.x++;
                return newPos;
            }
            if (ac == SE) {
                newPos.x++;
                newPos.y++;
                return newPos;
            }

        }
        return pos;
    }

    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        int xDiff = (int) to.x - from.x;
        int yDiff = (int) to.y - from.y;
        if (xDiff == -1 && yDiff == -1) {
            return NW;
        }
        if (xDiff == -1) {
            return N;
        }
        if (xDiff == -1 && yDiff == 1) {
            return NE;
        }
        if (yDiff == -1) {
            return W;
        }
        if (yDiff == 1) {
            return E;
        }
        if (xDiff == 1 && yDiff == -1) {
            return SW;
        }
        if (xDiff == 1) {
            return S;
        }
        if (xDiff == 1 && yDiff == 1) {
            return SE;
        }
        return STAY;
    }

    void Game::populate() {
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        while (numStrategic > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }
        while (numSimple > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }
        while (numAdvantages > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }
        while (numFoods > 0) {
            int i = d(gen); // random index in the grid vector
            if (__grid[i] == nullptr) { // is position empty
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }
    }

    void Game::round() {
        for (int n = 0; n < __grid.size(); n++) {
            if (__grid[n] != nullptr) {
                ActionType act;
                Surroundings s = getSurroundings(__grid[n]->getPosition());
                act = __grid[n]->takeTurn(s);
                if (isLegal(act, __grid[n]->getPosition())) {
                    Position p = move(__grid[n]->getPosition(), act);
                    __grid[n]->setPosition(move(__grid[n]->getPosition(), act));
                    if (__grid[p.y + p.x * __width] != nullptr && __grid[n] != nullptr) {
                        if(p.y + p.x * __width < 8 )
                        (*__grid[n]) * (*__grid[p.y + p.x * __width]);
                    }
                    __grid[n]->setTurned(true);
                    if (!(__grid[n]->isViable())) {
                        __grid[n] = nullptr;
                    }
                    if (__grid[p.y + p.x * __width]!= nullptr && !__grid[p.y + p.x * __width]->isViable()) {
                        __grid[p.y + p.x * __width] = nullptr;
                    }

                }
            }
        }

    }


    void Game::play(bool verbose) {
        while(getNumPieces() > 1 && __round < 7) {
            round();

            for (int i = 0; i < __grid.size(); i++) {
                if(__grid[i] != nullptr)
                {
                    __grid[i]->age();
                    __grid[i]->setTurned(false);
                    if (!__grid[i]->isViable()) {
                        __grid[i] = nullptr;
                    }
                }

            }
            __round++;
            if(!verbose)
            {
                cout <<*this;
            }

        }
        cout << *this;
    }
}