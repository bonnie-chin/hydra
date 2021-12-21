#ifndef __TEST_VIEW_H__
#define __TEST_VIEW_H__

#include "observer.h"
#include <memory>

class Controller;
class Game;
class Card;

class TestView : public Observer {
    public:
        TestView(std::shared_ptr<Controller>, std::shared_ptr<Game>);
        ~TestView() = default;
        void update() override; // Observer Pattern: concrete update() method
        SubscriptionType subType() const override;
    private:
        int curPlayerNum;
        std::shared_ptr<Game> game; // Observer Pattern: to access Model accessors without having to downcast subject
        std::shared_ptr<Controller> controller;
        void won();
        void printHeads();
        void printPlayers(); 
        void printHand(const std::shared_ptr<Card> inHand); 
        void inputMove(const std::shared_ptr<Card> inHand); 
        void inputMoveJoker(const std::shared_ptr<Card> inHand);
        void setCardValue();
};

#endif