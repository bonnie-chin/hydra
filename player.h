#ifndef __PLAYERDECK_H__
#define __PLAYERDECK_H__

#include <memory>
#include <vector>
class Card;

class Player {
    private:
        int playerNum;
        int seedNum;
        std::shared_ptr<Card> inHand;
        std::shared_ptr<Card> reserve;
        std::vector<std::shared_ptr<Card>> drawPile;
        std::vector<std::shared_ptr<Card>> discardPile;
    public:
        Player(int playerNum, int seedNum);
        int getPlayerNum() const;
        int getNumInDraw() const;
        int getNumInDiscard() const;
        std::shared_ptr<Card> getInHand() const;
        void drawCard();
        void clearHand(); 
        void addToDraw(std::shared_ptr<Card> c); 
        void addToReserve(std::shared_ptr<Card> c);
        void addToDiscard(std::shared_ptr<Card> c);
        void addReserveToDraw(); 
        void swapHandAndReserve();
        bool decksEmpty() const;
        bool reserveEmpty() const; 
        ~Player() = default;
};

#endif