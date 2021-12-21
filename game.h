#ifndef __GAME_H__
#define __GAME_H__

#include "subject.h"
#include <memory>
#include <vector>

class Card;
class Rules;
class Player;
class Head;

class Game : public Subject {
    private:
        int seedNum;
        int numPlayers;
        int curPlayerNum = 1;
        int numVal;
        int numCardsInDeck;
        long unsigned int numMovesMade = 0;
        bool setUpComplete = false;
        bool needCardValue = false;
        int firstHeadNum = 1;
        std::string ruleApplied;
        std::vector<std::shared_ptr<Head>> heads;
        std::vector<std::shared_ptr<Player>> players;
        std::vector<std::shared_ptr<Rules>> rules;
        void addDeck(std::vector<std::shared_ptr<Card>> & wholeDeck);    
        void nextPlayer();
        void notify(SubscriptionType t) const override;
        void notifyAll() const;
    public:
        Game(int seedNum, int numVal = 13); 
        bool getSetUpComplete() const;
        bool getNeedCardValue() const;
        int getCurPlayerNum() const; 
        int getNumDrawsRemaining() const; 
        int getFirstHeadNum() const;
        std::string getRuleApplied() const;
        const std::vector<std::shared_ptr<Head>> & getHeads() const; 
        const std::shared_ptr<Player> getCurPlayer() const; 
        const std::vector<std::shared_ptr<Player>> & getPlayers() const;
        void init(int numPlayers);
        void move(int headNum); 
        bool won();
        void drawCard();      
};

#endif
