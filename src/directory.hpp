#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
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

    bool createDirectory(std::string name)
    {
        if(mkdir(name.c_str(),0755) == 0)
        {
            return true;
        } else {
            return false;
        }
    }

};



#endif