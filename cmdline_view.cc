#include "cmdline_view.h"
#include "controller.h"
#include "joker.h"
#include "exceptions.h"
#include "head.h"
#include "player.h"
#include <string>
#include <iostream>

CmdLineView::CmdLineView(std::shared_ptr<Controller> c, std::shared_ptr<Game> g) : game{g}, controller{c} {
    std::cin.exceptions(std::ios::eofbit|std::ios::failbit);
    int numPlayers;
    bool numPlayersInvalid = true;
    g->attach(this);
    while (numPlayersInvalid) {
        try {
            std::cout << "How many players?" << std::endl;
            std::cin >> numPlayers;
            controller->init(numPlayers);
            numPlayersInvalid = false;
        } catch (InvalidValueException &) {
        } catch (std::iostream::failure &) {
            exit(0);
        }
    }
}

void CmdLineView::update() {
    if (!game->getSetUpComplete()) {
        std::cout << std::endl;
        printHeads();
        printPlayers();
        return;
    }

    if (game->won()) {
        won();
        exit(0);
    }

    if (curPlayerNum != game->getCurPlayerNum()) {
        curPlayerNum = game->getCurPlayerNum();
        std::cout << std::endl
                  << "Player " << curPlayerNum << ", it is your turn." 
                  << std::endl
                  << std::endl;
    }

    const std::shared_ptr<Player> curPlayer = game->getCurPlayer();
    std::shared_ptr<Card> inHand = curPlayer->getInHand();

    printHeads();
    printPlayers();
    
    if (inHand->getSuit() == "J") { // joker logic
        inputMoveJoker(inHand);
    } else {
        inputMove(inHand);
    }
}

SubscriptionType CmdLineView::subType() const {
    return SubscriptionType::Regular;
}

void CmdLineView::inputMove(const std::shared_ptr<Card> inHand) {
    std::cin.exceptions(std::ios::eofbit|std::ios::failbit);
    const std::vector<std::shared_ptr<Head>> heads = game->getHeads();
    int moveHead;
    bool moveInvalid = true;
    while (moveInvalid) {
        try {
            printHand(inHand);
            std::cin >> moveHead;
            controller->move(moveHead);
            moveInvalid = false;
        } catch (InvalidValueException &) { 
        } catch (std::iostream::failure &) {
            exit(0);
        }
    }
}

void CmdLineView::inputMoveJoker(const std::shared_ptr<Card> inHand) {
    std::cin.exceptions(std::ios::eofbit|std::ios::failbit);
    const std::vector<std::shared_ptr<Head>> heads = game->getHeads();
    int moveHead;
    bool moveInvalid = true;

    while (moveInvalid) { // getting a valid head number to commit move
        try {
            printHand(inHand);
            std::cin >> moveHead;
            controller->move(moveHead);
        } catch (InvalidValueException &) {
        } catch (JokerValueNotSet &) {
            moveInvalid = true;
            while (moveInvalid) {
                try { // getting a valid joker value
                    std::cout << "Joker value?" << std::endl;
                    std::string jokerVal;
                    std::cin >> jokerVal;
                    inHand->setValue(jokerVal);
                    controller->move(moveHead);
                    moveInvalid = false;
                } catch (InvalidValueException &) {}
            }
        } catch (std::iostream::failure &) {
            exit(0);
        }
    }
}

void CmdLineView::won() {
    std::cout << "Player " << curPlayerNum << " wins!" << std::endl;
}

void CmdLineView::printHand(const std::shared_ptr<Card> inHand) {
    std::cout << std::endl;
    std::cout << "Player " << game->getCurPlayerNum() << ", "
              << "You are holding " << inHand->getName() << ". "
              << "Your move?" << std::endl;
}

void CmdLineView::printHeads() {
    const std::vector<std::shared_ptr<Head>> heads = game->getHeads();
    std::cout << std::endl;
    std::cout << "Heads:" << std::endl;
    for (auto head : heads) {
        if (head == nullptr) continue;
        std::string topCard = head->peek()->getName();
        std::cout << head->getHeadNum() << ": "
                  << topCard << " "
                  << "(" << head->getNumCards() << ")"
                  << std::endl;
    }
}

void CmdLineView::printPlayers() {
    std::vector<std::shared_ptr<Player>> players = game->getPlayers();
    std::cout << std::endl;
    std::cout << "Players:" << std::endl;
    for (auto player : players) {
        int totalCards = player->getNumInDiscard() + player->getNumInDraw();
        std::cout << "Player " << player->getPlayerNum() << ": "
                  << totalCards << " "
                  << "(" << player->getNumInDraw()
                  << " draw, "
                  << player->getNumInDiscard() 
                  << " discard"
                  << ")";

        if (player->getPlayerNum() == curPlayerNum) {
            std::cout << " + 1 in hand, "
                      << game->getNumDrawsRemaining()
                      << " remaining, "
                      << (player->reserveEmpty() ? 0 : 1)
                      << " in reserve";

        }
        std::cout << std::endl;
    }
}

