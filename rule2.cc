#include "rule2.h"
#include "player.h"
#include "head.h"
#include "card.h"

Rule2::Rule2() : Rules{"2"} {}

bool Rule2::check(const std::shared_ptr<Player> p, 
                const int headNum,
                const std::vector<std::shared_ptr<Head>> & heads) const {
    if (headNum == 0) return false;
    std::shared_ptr<Card> headCard = heads.at(headNum - 1)->peek();
    std::shared_ptr<Card> inHand = p->getInHand();
    return inHand->equal(headCard);
}

void Rule2::apply(std::shared_ptr<Player> p, 
                const int headNum,
                std::vector<std::shared_ptr<Head>> & heads) {
    std::shared_ptr<Card> inHand = p->getInHand();
    heads.at(headNum - 1)->push(inHand);
    p->clearHand();
}
