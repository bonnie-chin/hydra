#include "game.h"
#include "controller.h"
#include "cmdline_view.h"
#include "test_view.h"
#include <iostream>
#include <string>
#include <memory>

void createNormalGame(const int & seedNum) {
    std::shared_ptr<Game> game = std::make_shared<Game>(seedNum);
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(game);
    CmdLineView{controller, game};
}

void createTestGame(const int & seedNum) {
    std::shared_ptr<Game> game = std::make_shared<Game>(seedNum);
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(game);
    TestView{controller, game};
}

void createTestGameWin(const int & seedNum, const int & cardsInSuit) {
    std::shared_ptr<Game> game = std::make_shared<Game>(seedNum, cardsInSuit);
    std::shared_ptr<Controller> controller = std::make_shared<Controller>(game);
    TestView{controller, game};
}

int main(int argc, char** argv) {
    int seedNum;
    try {
        if (argc > 4) {
            std::cout << "Incorrect number of arguments" << std:: endl;
        } else if (argc == 1) { // Normal Game
            seedNum = rand();
            createNormalGame(seedNum);
        } else if (argc == 2) { // Normal specific seed # or testing
            std::string argTwo(argv[1]);
            if (argTwo == "-testing") {
                seedNum = rand();
                createTestGame(seedNum);
            } else {
                seedNum = std::stoi(argv[1]);
                createNormalGame(seedNum);
            }
        } else if (argc == 3) { // Testing mode with specific seed #
            seedNum = std::stoi(argv[2]);
            createTestGame(seedNum);
        } else {
            seedNum = std::stoi(argv[2]);
            int cardsInSuit = std::stoi(argv[3]);
            createTestGameWin(seedNum, cardsInSuit);
        }
        return 0;
    } catch (std::exception const &) {
        std::cout << "Invalid arguments" << std::endl;
        return 1;
    }
}
