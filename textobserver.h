// textobserver.h

#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "board.h"
#include <iostream>
#include <string>
#include "square.h"
#include "subject.h"
#include "player.h"

class TextObserver : public Observer {
public:
    TextObserver(Board* board);
    void notify() override;

private:
    Board* subject;
    void displayPlayerInfo(int playerNum);
    void displayBoard();
};
#endif
