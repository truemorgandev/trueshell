#ifndef INPUT_HPP
#define INPUT_HPP
#include <ncurses.h>
#include "directory.hpp"
#include <sstream>
class Input {

public:
    Directory& dir;

    Input(Directory& directory) : dir(directory){}
    char command[32];

    void getCommand(){
    
    getstr(command);
    std::istringstream iss(command);
    std::string cmd;
    std::string arg;

    iss >> cmd;
    iss >> arg;
    if(cmd == "cdir"){
        handleCheckD();
    } else if(cmd == "adir"){
        handleChangeD(arg);
    } else if (cmd == "clear"){
        handleClear();
    } else if (cmd == "crdir") {
        handleMkDir(arg);    
    } else if(cmd == "lf"){
        handleList();
    } else if(cmd == "exit"){
        handleExit();
    } else if(cmd == "hp"){
        handleHelp();
    } else if(cmd == "cf"){
        handleFIleCreation(arg);
    } else if(cmd == "onwf"){
        dir.editFile(arg);
    } else {
        printw("There is no such command");
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

        void handleChangeD(std::string wantedDir)
        {
        
           
            if(dir.changeDirectory(wantedDir)){
                printw("Directory succsesfully changed to %s ", dir.getCurrentPath().c_str());
                printPrompt();
            } else {
                printw("Failed changing directory to %s ", dir.getCurrentPath().c_str());
                printPrompt();
            }
            
        }
        void handleMkDir(std::string namedir){
            

            if(dir.createDirectory(namedir))
            {
                printw("Directory %s", namedir.c_str());
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
        void handleHelp() {
    printw("Available commands:\n");
    printw("  cdir        - show current directory\n");
    printw("  adir <dir> - change current directory\n");
    printw("  crdir <dir> - create new directory\n");
    printw("  lf         - list files in current directory\n");
    printw("  cf <file> - create new file\n");
    printw("  clear         - clear the screen\n");
    printw("  exit          - quit the shell\n");
    printw("  hp            - show this help message\n");
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
        void handleFIleCreation(std::string fname)
        {
                if (fname.empty()) {
            printw("Error: no filename provided\n");
            printPrompt();
            return;
            }
            if(dir.createFile(fname)){
                printw("File %s succsesfully created", fname.c_str());
                refresh();
            } else {
                printw("Failed creating file %s", fname.c_str());
            }
            printPrompt();
        }

};



#endif