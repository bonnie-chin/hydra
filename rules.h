#ifndef __RULES_H__
#define __RULES_H__

#include <string>
#include <memory>
#include <vector>
#include "subscriptions.h"

class Player;
class Head;
class Card;
class Observer;

class Rules {
    private:
        std::string ruleName;
    public:
        Rules(std::string ruleName);
        std::string getRuleName() const;
        virtual bool check(const std::shared_ptr<Player> p, 
                           const int headNum,
                           const std::vector<std::shared_ptr<Head>> & heads) const = 0;
        virtual void apply(std::shared_ptr<Player> p, 
                           const int headNum,
                           std::vector<std::shared_ptr<Head>> & heads) = 0;
        virtual ~Rules() = default;
};

#endif
