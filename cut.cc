#include "cut.h"
#include "player.h"
#include "card.h"
#include "joker.h"
#include "head.h"
#include "exceptions.h"
#include "game.h"

Cut::Cut(std::vector<std::shared_ptr<Rules>> rules, Game * game) : Rules{"cut"}, rules{rules}, game{game} {}

bool Cut::check(const std::shared_ptr<Player> p, 
                const int headNum,
                const std::vector<std::shared_ptr<Head>> & heads) const {
    
    if (headNum > 1 && heads.at(headNum - 2) != nullptr) return false;

    const std::shared_ptr<Card> inHand = p->getInHand();
    for (auto head : heads) { // checking through all heads...
        if (head == nullptr) continue;
        for (auto rule : rules) { // checking if any of the rules apply
            if (head->getHeadNum() == headNum) continue;
            if (rule->check(p, headNum, heads)) return false;
        }
    }
    return true;
}

void Cut::apply(std::shared_ptr<Player> p, 
                const int headNum,
                std::vector<std::shared_ptr<Head>> & heads) {

    std::shared_ptr<Card> cardToAdd = p->getInHand(); // discarding what's in hand
    p->addToDiscard(cardToAdd);
    p->clearHand();

    if (!p->reserveEmpty()) { // putting back any of the reserve
        p->addReserveToDraw();
    }

    std::shared_ptr<Head> headToCut = heads.at(headNum - 1); // cutting the head
    while (!headToCut->isEmpty()) {
        cardToAdd = headToCut->pop();
        if (cardToAdd->getSuit() == "J") {
            std::shared_ptr<Joker> jokerCard = std::dynamic_pointer_cast<Joker>(cardToAdd);
            jokerCard->reset();
        }
        p->addToDiscard(cardToAdd);
    }
    heads.at(headNum - 1) = nullptr;

    for (int i = 0; i < 2; i++) { // creating new heads
        game->drawCard();
        std::shared_ptr<Card> addAsHead = p->getInHand();
        p->clearHand();
        std::shared_ptr<Head> newHead = std::make_shared<Head>(heads.size() + 1);
        if (addAsHead->getSuit() == "J") {
            addAsHead->setValue("2");
        }
        newHead->push(addAsHead);
        heads.push_back(newHead);
    }
}
