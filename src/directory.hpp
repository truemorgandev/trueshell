#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <limits.h>
#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP
class Directory {
    private: 
        std::string currentPath;
    public:
         Directory(){
            char currentDir[PATH_MAX];
            if(getcwd(currentDir, sizeof(currentDir))!= nullptr){
                currentPath = currentDir;
            } else {
                currentPath = '/';
            }
        }
    std::string getCurrentPath()
    {
        return currentPath;
    }

    bool changeDirectory(std::string wantedDir)
    {
        if(chdir(wantedDir.c_str()) == 0)
        {
            char currentDir[PATH_MAX];
            getcwd(currentDir, sizeof(currentDir));
            currentPath = currentDir;
            return true;
        }
        return false;
    }

};



#endif