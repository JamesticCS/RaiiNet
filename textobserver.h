// textobserver.h

#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "board.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "square.h"
#include "subject.h"
#include "player.h"
#include "gamecontroller.h"

class GameController;

class TextObserver : public Observer {
public:
    TextObserver(Board* board, GameController* controller);
    void notify() override;

private:
    Board* subject;
    GameController* controller;
    void displayPlayerInfo(int playerNum);
    void displayPlayerLinks(const Player& player);
    void displayBoard();
};
#endif
