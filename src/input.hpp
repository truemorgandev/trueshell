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
    } else if(strcmp(command, "createD") == 0) {
        handleMkDir();
    } else if(strcmp(command,"exit") == 0){
        handleExit();
    } else if(strcmp(command, "listF") == 0){
        handleList();
    } else if(strcmp(command, "help") == 0){
        handleHelp();
    } else if(strcmp(command, "clear") == 0){
        handleClear();
    } else if(strcmp(command, "createF") == 0){
        handleFIleCreation();
    } else {
        printw("No such command!\n");
        printPrompt();
    } 
}

    private:

        void handleCheckD()
        {
            printw("Current directory is %s ", dir.getCurrentPath().c_str());
            refresh();
            printPrompt();
        }

        void handleChangeD()
        {
            printw("What directory you wanna change to?\n");
            refresh();
            char wantedDir[PATH_MAX];
            getstr(wantedDir);

            if(dir.changeDirectory(wantedDir)){
                printw("Directory succsesfully changed to %s ", dir.getCurrentPath().c_str());
                printPrompt();
            } else {
                printw("Failed changing directory to %s ", dir.getCurrentPath().c_str());
                printPrompt();
            }
            
        }
        void handleMkDir(){
            printw("Creating a directory, enter name:  \n");
            refresh();
            char dirName[PATH_MAX];
            getstr(dirName);

            if(dir.createDirectory(dirName))
            {
                printw("Directory %s", dirName);
                printw(" succesfully created");
                printPrompt();
            } else {
                printw("Error while creation directory");
                printPrompt();
            }
            
        }
        void handleExit()
        {
            endwin();
            exit(0);
        }
        void handleList()
        {
            auto files = dir.listFiles();
            if(files.empty()){
                printw("There are no files or cannot open directory %s", dir.getCurrentPath().c_str());
                refresh();
            } else {
                for(auto f : files){
                    printw("%s\n", f.c_str());
                    
                }
            }
            printPrompt();
            
        }
        void handleHelp(){
            printw("Commands:\n ");
            refresh();
            printw("changeD *changes directory*\n");
            refresh();
            printw("createD *creates directory*\n");
            refresh();
            printw("listF *lists files in directory*\n");
            refresh();
            printw("clear *clears terminal*\n");
            refresh();
            printw("checkD *shows directory you currently in*\n");
            refresh();
            printw("createF *creates a file" );
            printPrompt();
        }
        void handleClear()
        {
            clear();
            printPrompt();
        }
        void printPrompt() {
            printw("\n>>> ");
            refresh();
        }
        void handleFIleCreation()
        {
            printw("Enter file name: \n");
            refresh();
            char fileName[PATH_MAX];
            getstr(fileName);

            if(dir.createFile(fileName)){
                printw("File %s succsesfully created", fileName);
                refresh();
            } else {
                printw("Failed creating file %s", fileName);
            }
            printPrompt();
        }

};



#endif