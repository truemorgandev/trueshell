#include "directory.hpp"
#include "input.hpp"
#include <ncurses.h>

int main() {
    initscr();
 
    cbreak();

    Directory dir;
    Input input(dir);

    printw("Welcome to trueshell\n");
    printw("\n>>> ");
    refresh();

    while(true) {
        
        input.getCommand();
    }

    endwin();
    return 0;
}

