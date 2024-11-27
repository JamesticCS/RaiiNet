export module textobserver;

import observer;
import board;
import <iostream>;
import <string>;
import square;
import subject;
import player;

export class TextObserver : public Observer {
public:
    TextObserver(Board* board);
    void notify() override;

private:
    Board* subject;
    void displayPlayerInfo(int playerNum);
    void displayBoard();
};