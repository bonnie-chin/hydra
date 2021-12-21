#include "rule1.h"
#include "rules.h"
#include "player.h"
#include "head.h"
#include "card.h"

Rule1::Rule1() : Rules{"1"} {}

bool Rule1::check(const std::shared_ptr<Player> p, 
                const int headNum,
                const std::vector<std::shared_ptr<Head>> & heads) const {
    if (headNum == 0) return false;
    std::shared_ptr<Card> headCard = heads.at(headNum - 1)->peek();
    std::shared_ptr<Card> inHand = p->getInHand();
    return inHand->lessThan(headCard);
}

void Rule1::apply(std::shared_ptr<Player> p, 
                const int headNum,
                std::vector<std::shared_ptr<Head>> & heads) {
    std::shared_ptr<Card> inHand = p->getInHand();
    heads.at(headNum - 1)->push(inHand);
    p->clearHand();
}
