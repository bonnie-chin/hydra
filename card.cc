#include "card.h"
#include <string>
#include "exceptions.h"

Card::Card(std::string suit, std::string value) : suit{suit}, value{value} {
        if (value == "A") numVal = 1;
        else if (value == "10") numVal = 10;
        else if (value == "J") numVal = 11;
        else if (value == "Q") numVal = 12;
        else if (value == "K") numVal = 13;
        else if (value == "Joker") numVal = 0;
        else numVal = std::stoi(value);
}

std::string Card::getName() const {
    if (value != "Joker") return value + suit;
    else return value;
}

std::string Card::getVal() const {
    return value;
}

std::string Card::getSuit() const {
    return suit;
}

int Card::getNumVal() const {
    return numVal;
}

void Card::setSuit(std::string s) {
    if (s == "S" || s == "C" || s == "D" || s == "H" || s == "J") {
        suit = s;
    } else {
        throw InvalidValueException();
    }
}

void Card::setValue(std::string v) {
    if (v == "A") numVal = 1;
    else if (v == "2") numVal = 2;
    else if (v == "3") numVal = 3;
    else if (v == "4") numVal = 4;
    else if (v == "5") numVal = 5;
    else if (v == "6") numVal = 6;
    else if (v == "7") numVal = 7;
    else if (v == "8") numVal = 8;
    else if (v == "9") numVal = 9;
    else if (v == "10") numVal = 10;
    else if (v == "J") numVal = 11;
    else if (v == "Q") numVal = 12;
    else if (v == "K") numVal = 13;
    else if (v == "Joker") {
        numVal = 0;
        setSuit("J");
    } else {
        throw InvalidValueException();
    }
    value = v;
}

bool Card::equal(std::shared_ptr<Card> card) const {
    if (numVal == card->getNumVal()) return true; 
    else return false;
}

bool Card::lessThan(std::shared_ptr<Card> card) const {
    if (numVal < card->getNumVal()) return true;
    else return false;
}
