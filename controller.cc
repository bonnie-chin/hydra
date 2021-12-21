#include "controller.h"
#include "game.h"
#include "head.h"
#include "player.h"
#include "card.h"
#include <string>
#include <iostream>
#include "exceptions.h"

Controller::Controller(std::shared_ptr<Game> game) : game{game} {}

void Controller::init(int numPlayers) {
    if (numPlayers < 2) throw InvalidValueException();
    game->init(numPlayers);
}

void Controller::move(int moveHead) {
    std::vector<std::shared_ptr<Head>> heads = game->getHeads();
    const int firstHeadNum = game->getFirstHeadNum();
    const int lastHeadNum = heads.size();
    std::shared_ptr<Player> curPlayer = game->getCurPlayer();
    std::shared_ptr<Card> inHand = curPlayer->getInHand();
    if ((moveHead < firstHeadNum && moveHead != 0) || moveHead > lastHeadNum) {
        throw InvalidValueException();
    } else if (inHand->getSuit() == "J") {
        if (inHand->getName() == "Joker") throw JokerValueNotSet();
    }

    try {
        game->move(moveHead);
    } catch (InvalidValueException &) {
        throw InvalidValueException();
    }
}
