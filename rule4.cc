#include "rule4.h"
#include "player.h"
#include "head.h"
#include "card.h"

Rule4::Rule4() : Rules{"4"} {}

bool Rule4::check(const std::shared_ptr<Player> p, 
                const int headNum,
                const std::vector<std::shared_ptr<Head>> & heads) const {
    if (headNum != 0) return false;
    return p->reserveEmpty();
}

void Rule4::apply(std::shared_ptr<Player> p, 
                const int headNum,
                std::vector<std::shared_ptr<Head>> & heads) {
    std::shared_ptr<Card> inHand = p->getInHand();
    p->addToReserve(inHand);
    p->clearHand();
}
