// main.cc
#include "gamecontroller.h"
#include <string>

int main(int argc, char* argv[]) {
    std::string link1File = "";
    std::string link2File = "";
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-link1" && i + 1 < argc) {
            link1File = argv[++i];
        }
        else if (arg == "-link2" && i + 1 < argc) {
            link2File = argv[++i];
        }
    }
    
    // Create game with specified files or random links
    GameController game{2, link1File, link2File};
    game.runGame();
    
    return 0;
}