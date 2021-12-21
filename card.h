#ifndef __CARD_H__
#define __CARD_H__

#include <string>
#include <memory>

class Card {
    protected:
        std::string suit;
        std::string value;
        int numVal;
    public:
        Card(std::string suit, std::string value);
        virtual ~Card() = default;
        virtual std::string getName() const;
        std::string getSuit() const;
        int getNumVal() const;
        virtual std::string getVal() const;
        void setSuit(std::string s);
        virtual void setValue(std::string v);
        bool equal(std::shared_ptr<Card> card) const;
        bool lessThan(std::shared_ptr<Card> card) const;
};

#endif
