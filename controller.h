#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "game.h"
#include <memory>

class Game;

class Controller {
    private:
        std::shared_ptr<Game> game;
    public:
        Controller(std::shared_ptr<Game> game);
        ~Controller() = default;
        void init(int numPlayers);
        void move(int moveHead);
};

#endif
