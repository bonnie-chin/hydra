#ifndef __RULE3_H__
#define __RULE3_H__

#include "rules.h"

class Rule3 : public Rules {
    public:
        Rule3();
        bool check(const std::shared_ptr<Player> p, 
                   const int headNum,
                   const std::vector<std::shared_ptr<Head>> & heads) const override;
        void apply(std::shared_ptr<Player> p, 
                   const int headNum,
                   std::vector<std::shared_ptr<Head>> & heads) override;
};

#endif