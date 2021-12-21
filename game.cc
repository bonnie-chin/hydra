#include "game.h"
#include "joker.h"
#include "card.h"
#include "rule1.h"
#include "rule2.h"
#include "rule3.h"
#include "rule4.h"
#include "rule5.h"
#include "cut.h"
#include "player.h"
#include "head.h"
#include "observer.h"
#include "exceptions.h"
#include <string>
#include <algorithm>
#include <random>
#include <iostream>

Game::Game(int seedNum, int numVal) : seedNum{seedNum}, numVal{numVal}  {
    rules.push_back(std::make_shared<Rule1>());
    rules.push_back(std::make_shared<Rule2>());
    rules.push_back(std::make_shared<Rule3>());
    rules.push_back(std::make_shared<Rule4>());
    rules.push_back(std::make_shared<Rule5>());
    rules.push_back(std::make_shared<Cut>(rules, this));
    numCardsInDeck = (numVal * 4) + 2;
}

void Game::nextPlayer() {
    ruleApplied = "";
    getCurPlayer()->addReserveToDraw();
    if (curPlayerNum == numPlayers) curPlayerNum = 1;
    else curPlayerNum++;
    numMovesMade = 0;
}

int Game::getCurPlayerNum() const { return curPlayerNum; }

bool Game::getSetUpComplete() const { return setUpComplete; }

int Game::getNumDrawsRemaining() const {
    int numCutHeads = firstHeadNum - 1;
    return heads.size() - numMovesMade - numCutHeads;
}

bool Game::getNeedCardValue() const {
    return needCardValue;
}

const std::vector<std::shared_ptr<Head>> & Game::getHeads() const {
    return heads;
}

const std::shared_ptr<Player> Game::getCurPlayer() const {
    return players[curPlayerNum - 1];
}

const std::vector<std::shared_ptr<Player>> & Game::getPlayers() const {
    return players;
}

int Game::getFirstHeadNum() const {
    return firstHeadNum;
}

std::string Game::getRuleApplied() const {
    return ruleApplied;
}

void Game::addDeck(std::vector<std::shared_ptr<Card>> & wholeDeck) {
    const std::string value [] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    const std::string suit [] = {"S", "H", "C", "D"};
    const int numSuit = 4;
    const int numJokersPerDeck = 2;
    
    for (int i = 0; i < numSuit; i++) {
        for (int j = 0; j < numVal; j++) {
            std::shared_ptr<Card> card = std::make_shared<Card>(suit[i], value[j]);
            wholeDeck.push_back(card);
        }
    }
    for (int k = 0; k < numJokersPerDeck; k++) {
        std::shared_ptr<Joker> card = std::make_shared<Joker>();
        wholeDeck.push_back(std::make_shared<Joker>());
    }
}

void Game::init(int numOfPlayers) {
    numPlayers = numOfPlayers;
    std::vector<std::shared_ptr<Card>> wholeDeck;
    
    // Creating and shuffling cards for game
    for (int i = 0; i < numPlayers; i++) {
        addDeck(wholeDeck);
    }
    std::shuffle(wholeDeck.begin(), wholeDeck.end(), std::default_random_engine(seedNum));

    // Distributing cards to players
    for (int i = 0; i < numPlayers; i++) {
        int playerNum = i + 1;
        players.push_back(std::make_shared<Player>(playerNum, seedNum));
        for (int j = 0; j < numCardsInDeck; j++) {
            players[i]->addToDraw(wholeDeck.back());
            wholeDeck.pop_back();
        }
    }

    // Creating the first head
    drawCard();
    std::shared_ptr<Card> firstHead = players[0]->getInHand();
    players[0]->clearHand();
    heads.push_back(std::make_shared<Head>(1));
    if (firstHead->getSuit() == "J") {
        firstHead->setValue("2");
    }
    heads[0]->push(firstHead);
    notifyAll();
    
    nextPlayer();
    setUpComplete = true;
    drawCard();
    notifyAll();
}

void Game::move(int headNum) {
    try {
        std::shared_ptr<Player> curPlayer = getCurPlayer();
        for (auto rule : rules) { // checking and applying applicable rules
            if (rule->check(curPlayer, headNum, heads)) {
                ruleApplied = rule->getRuleName();
                rule->apply(curPlayer, headNum, heads);
                break;
            }
        }
        
        // deciding whether to increase move count
        if (ruleApplied == "") {
            throw InvalidValueException();
        } else if (ruleApplied != "5") { // swap - does not count as a move
            numMovesMade++;
        }
        
        // deciding whether to move onto next player
        long unsigned int numMovesNecessary = heads.size() - firstHeadNum + 1;
        if (numMovesMade == numMovesNecessary || ruleApplied == "2") { // turn terminating moves
            nextPlayer();
        } else if (ruleApplied == "cut") {
            nextPlayer();
            firstHeadNum++;
        }
        
        if (ruleApplied != "5") {
            ruleApplied = "";
            drawCard();
        }
        ruleApplied = "";
        notifyAll();
    } catch (OnlyReserveLeft &) {
        nextPlayer();
        drawCard();
        notifyAll();
    } catch (NoCardsToDraw &) {
        notifyAll();
    } catch (InvalidValueException &) {
        throw InvalidValueException();
    }
}

void Game::drawCard() {
std::shared_ptr<Player> curPlayer = getCurPlayer();
    curPlayer->drawCard();
    needCardValue = true;
    notify(SubscriptionType::Test);
    needCardValue = false;
}

bool Game::won() {
    for (auto player : players) {
        if (player->decksEmpty()) return true;
    }
    return false;
}

void Game::notify(SubscriptionType t) const {
    for (auto o : observers) {
        if (o->subType() == t)  o->update();
    }
}

void Game::notifyAll() const {
    for (auto o : observers) {
        o->update();
    }
}   
