#include "player.h"
#include "card.h"
#include "exceptions.h"
#include <algorithm>
#include <random>

Player::Player(int playerNum, int seedNum) : playerNum{playerNum}, 
    seedNum{seedNum}, inHand{nullptr}, reserve{nullptr}  {}

int Player::getPlayerNum() const {
    return playerNum;
}

int Player::getNumInDraw() const {
    return drawPile.size();
}

int Player::getNumInDiscard() const {
    return discardPile.size();
}

std::shared_ptr<Card> Player::getInHand() const {
    return inHand;
}

void Player::drawCard() {
    if (!drawPile.empty()) {
        inHand = drawPile.back();
        drawPile.pop_back();
    } else if (!discardPile.empty()) {
        std::shuffle(discardPile.begin(), discardPile.end(), std::default_random_engine(seedNum));
        while (!discardPile.empty()) {
            addToDraw(discardPile.back());
            discardPile.pop_back();
        }
        inHand = drawPile.back();
        drawPile.pop_back();
    } else if (reserve != nullptr) {
        addReserveToDraw();
        throw OnlyReserveLeft();
    } else {
        throw NoCardsToDraw();
    }
}

void Player::clearHand() {
    inHand = nullptr;
}

void Player::addToDraw(std::shared_ptr<Card> c) {
    drawPile.push_back(c);
}

void Player::addToReserve(std::shared_ptr<Card> c) {
    reserve = c;
}

void Player::addReserveToDraw() {
    if (reserve == nullptr) return;
    drawPile.push_back(reserve);
    reserve = nullptr;
}

void Player::swapHandAndReserve() {
    std::swap(inHand, reserve);
}

void Player::addToDiscard(std::shared_ptr<Card> c) {
    discardPile.push_back(c);
}

bool Player::decksEmpty() const {
    bool drawIsEmpty = drawPile.empty();
    bool discardIsEmpty = discardPile.empty();
    bool reserveIsEmpty = reserveEmpty();
    bool inHandIsEmpty = inHand == nullptr? true : false;
    return (drawIsEmpty && discardIsEmpty && reserveIsEmpty && inHandIsEmpty);
}

bool Player::reserveEmpty() const {
    return (reserve == nullptr);
}

