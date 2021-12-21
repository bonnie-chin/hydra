#ifndef __RULE5_H__
#define __RULE5_H__

#include "rules.h"

class Rule5 : public Rules {
    public:
        Rule5();
        bool check(const std::shared_ptr<Player> p, 
                   const int headNum,
                   const std::vector<std::shared_ptr<Head>> & heads) const override;
        void apply(std::shared_ptr<Player> p, 
                   const int headNum,
                   std::vector<std::shared_ptr<Head>> & heads) override;
};

#endif