#include "head.h"

Head::Head(int headNum) : headNum{headNum} {}

int Head::getHeadNum() const {
    return headNum;
}

int Head::getNumCards() const {
    return pile.size();
}

bool Head::isEmpty() const {
    if (pile.size() == 0) return true;
    return false;
}

std::shared_ptr<Card> Head::peek() const {
    return pile.back();
}

std::shared_ptr<Card> Head::pop() {
    std::shared_ptr<Card> c = pile.back();
    pile.pop_back();
    return c;
}

void Head::push(std::shared_ptr<Card> c) {
    pile.push_back(c);
}