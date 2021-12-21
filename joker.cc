#include "joker.h"
#include "exceptions.h"

Joker::Joker() : Card{"J", "Joker"} {}

void Joker::setValue(std::string v) {
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
    assignedVal = v;
    if (v != "Joker") valueSet = true;
}

void Joker::reset() {
    assignedVal = "";
    numVal = 0;
    valueSet = false;
}

std::string Joker::getName() const {
    if (valueSet) {
        return assignedVal + suit;
    } else {
        return value;
    }
}

std::string Joker::getVal() const {
    if (valueSet) {
        return assignedVal + suit;
    } else {
        return value;
    }
}

