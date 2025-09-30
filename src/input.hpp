#ifndef INPUT_HPP
#define INPUT_HPP
#include <ncurses.h>
#include "directory.hpp"
class Input {

public:
    Directory& dir;

    Input(Directory& directory) : dir(directory){}
    char command[32];

    void getCommand(){
    
    getstr(command);

    if(strcmp(command, "checkD") == 0) {
        handleCheckD();
    } else if(strcmp(command, "changeD") == 0) {
        handleChangeD();
    } else if(strcmp(command, "exit") == 0) {
        handleExit();
    } else {
        printw("No such command!\n");
        refresh();
    }
}

    private:

        void handleCheckD()
        {
            printw("Current directory is %s ", dir.getCurrentPath().c_str());
            refresh();
        }

        void handleChangeD()
        {
            printw("What directory you wanna change to?\n");
            refresh();
            char wantedDir[PATH_MAX];
            getstr(wantedDir);

            if(dir.changeDirectory(wantedDir)){
                printw("Directory succsesfully changed to %s ", dir.getCurrentPath().c_str());
            } else {
                printw("Failed changing directory to %s ", dir.getCurrentPath().c_str());
            }
        }

        void handleExit()
        {
            endwin();
            exit(0);
        }



};



#endif