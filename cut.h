#ifndef __CUT_H__
#define __CUT_H__

#include "rules.h"

class Game;

class Cut : public Rules {
    private:
        std::vector<std::shared_ptr<Rules>> rules;
        Game * game;
    public:
        Cut(std::vector<std::shared_ptr<Rules>> rules, Game * game);
        bool check(const std::shared_ptr<Player> p, 
                   const int headNum,
                   const std::vector<std::shared_ptr<Head>> & heads) const override;
        void apply(std::shared_ptr<Player> p, 
                   const int headNum,
                   std::vector<std::shared_ptr<Head>> & heads) override;
};

#endif
