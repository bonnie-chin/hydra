#include "test_view.h"
#include "controller.h"
#include "joker.h"
#include "exceptions.h"
#include "head.h"
#include "player.h"
#include <string>
#include <iostream>

TestView::TestView(std::shared_ptr<Controller> c, std::shared_ptr<Game> g) : game{g}, controller{c} {
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

void TestView::update() {
    if (game->getNeedCardValue() && (game->getRuleApplied() == "cut" || !game->getSetUpComplete())) {
        setCardValue();
        return;
    } else if (!game->getSetUpComplete()) {
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

    setCardValue();
    if (inHand->getSuit() == "J") { // joker logic
        inputMoveJoker(inHand);
    } else {
        inputMove(inHand);
    }
}

SubscriptionType TestView::subType() const {
    return SubscriptionType::Test;
}

void TestView::inputMove(const std::shared_ptr<Card> inHand) {
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

void TestView::inputMoveJoker(const std::shared_ptr<Card> inHand) {
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

void TestView::won() {
    std::cout << "Player " << curPlayerNum << " wins!" << std::endl;
}

void TestView::printHand(const std::shared_ptr<Card> inHand) {
    std::cout << std::endl;
    std::cout << "Player " << game->getCurPlayerNum() << ", "
              << "You are holding " << inHand->getName() << ". "
              << "Your move?" << std::endl;
}

void TestView::printHeads() {
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

void TestView::printPlayers() {
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

void TestView::setCardValue() {
    std::cin.exceptions(std::ios::eofbit|std::ios::failbit);
    std::shared_ptr<Card> inHand = game->getCurPlayer()->getInHand();

    try {
        while (true) { // setting the Card value
            try {
                std::cout << std::endl
                << "Card value?" 
                << std::endl;
                std::string cardVal;
                std::cin >> cardVal;
                inHand->setValue(cardVal);
                break;
            } catch (InvalidValueException &) {}
        }
        if (inHand->getVal() == "Joker") return;
        while (true) { // setting the Card value
            try {
                std::cout << std::endl
                << "Suit?" 
                << std::endl;
                std::string cardSuit;
                std::cin >> cardSuit;
                inHand->setSuit(cardSuit);
                break;
            } catch (InvalidValueException &) {}
        }
    } catch (std::iostream::failure &) {
        exit(0);
    }
}


