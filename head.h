#ifndef __HEAD_H__
#define __HEAD_H__
#include <vector>
#include "card.h"
#include <memory>

class Head {
    int headNum;
    std::vector<std::shared_ptr<Card>> pile;
    public:
        Head(int headNum);
        int getHeadNum() const;
        int getNumCards() const;
        std::shared_ptr<Card> peek() const;
        std::shared_ptr<Card> pop();
        void push(std::shared_ptr<Card>);
        bool isEmpty() const;
};

#endif