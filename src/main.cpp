#include "directory.hpp"
#include "input.hpp"
#include <ncurses.h>

int main() {
    initscr();
 
    cbreak();

    Directory dir;
    Input input(dir);

    printw("Welcome to MorganManager\n");
    refresh();

    while(true) {
        printw("\n> "); 
        refresh();
        input.getCommand();
    }

    endwin();
    return 0;
}

