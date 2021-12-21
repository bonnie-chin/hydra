#ifndef __JOKER_H__
#define __JOKER_H__

#include "card.h"

class Joker : public Card {
    std::string assignedVal;
    bool valueSet = false;
    public:
        Joker();
        ~Joker() = default;
        std::string getName() const override;
        std::string getVal() const override;
        void setValue(std::string v) override;
        void reset();
};

#endif
