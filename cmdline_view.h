#ifndef __CMDLINE_VIEW_H__
#define __CMDLINE_VIEW_H__

#include "observer.h"
#include <memory>

class Controller;
class Game;
class Card;

class CmdLineView : public Observer {
    public:
        CmdLineView(std::shared_ptr<Controller>, std::shared_ptr<Game>);
        ~CmdLineView() = default;
        void update() override; // Observer Pattern: concrete update() method
    private:
        int curPlayerNum = 1;
        std::shared_ptr<Game> game; // Observer Pattern: to access Model accessors without having to downcast subject
        std::shared_ptr<Controller> controller;
        SubscriptionType subType() const override;
        void won();
        void printHeads(); 
        void printPlayers(); 
        void printHand(const std::shared_ptr<Card> inHand); 
        void inputMove(const std::shared_ptr<Card> inHand); 
        void inputMoveJoker(const std::shared_ptr<Card> inHand);
};

#endif
