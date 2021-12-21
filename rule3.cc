#include "rule3.h"
#include "player.h"
#include "head.h"
#include "card.h"

Rule3::Rule3() : Rules{"3"} {}

bool Rule3::check(const std::shared_ptr<Player> p, 
                const int headNum,
                const std::vector<std::shared_ptr<Head>> & heads) const {
    if (headNum == 0) return false;
    std::shared_ptr<Card> inHand = p->getInHand();
    if (inHand->getVal() == "A") return false;
    std::shared_ptr<Card> headCard = heads.at(headNum - 1)->peek();
    if (headCard->getVal() == "A") {
        return true;
    }
    return false;
}

void Rule3::apply(std::shared_ptr<Player> p, 
                const int headNum,
                std::vector<std::shared_ptr<Head>> & heads) {
    std::shared_ptr<Card> inHand = p->getInHand();
    heads.at(headNum - 1)->push(inHand);
    p->clearHand();
}
