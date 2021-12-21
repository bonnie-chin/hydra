#include "rule5.h"
#include "player.h"
#include "head.h"
#include "card.h"

Rule5::Rule5() : Rules{"5"} {}

bool Rule5::check(const std::shared_ptr<Player> p, 
                const int headNum,
                const std::vector<std::shared_ptr<Head>> & heads) const {
    if (headNum != 0) return false;
    return !(p->reserveEmpty());
}

void Rule5::apply(std::shared_ptr<Player> p, 
                const int headNum,
                std::vector<std::shared_ptr<Head>> & heads) {
    p->swapHandAndReserve();
}