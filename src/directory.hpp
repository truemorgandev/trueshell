#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>
#include <fstream>
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
    bool createFile(std::string name)
    {
        std::string fullPath = currentPath + '/' + name;
        FILE* file = fopen(fullPath.c_str(), "w");
        if(file != nullptr){
            return true;
        } else {
            fclose(file);
            return false;
        }
    }
    std::vector<std::string> listFiles()
    {
        std::vector<std::string> files;
        DIR* dir = opendir(currentPath.c_str());
        if(dir == nullptr)
        {
            return files;
        }

        struct dirent* entry;
        while((entry = readdir(dir)) != nullptr)
        {
            std::string name = entry->d_name;
            if(name == "." || name == "..")
            {
                continue;
            } 
            files.push_back(name);
        }
        closedir(dir);
        return files;
    }

      void editFile(const std::string& filename) {
        
        std::vector<std::string> buffer;

        
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            std::string line;
            while (std::getline(inFile, line)) {
                buffer.push_back(line);
            }
            inFile.close();
        }

        clear();
        printw("///            onwf editor             ///");
        refresh();
        int curRow = 0, curCol = 0;
        bool running = true;

        while (running) {
            
            clear();
            for (size_t i = 0; i < buffer.size(); ++i) {
                mvprintw(i, 0, "%s", buffer[i].c_str());
            }
            move(curRow, curCol);
            refresh();

            int ch = getch();
            switch (ch) {
                case 17: 
                    running = false;
                    break;
                case 14: 
                {
                    
                    std::ofstream outFile(filename);
                    for (auto& line : buffer) {
                        outFile << line << "\n";
                    }
                    outFile.close();
                    running = false;
                    break;
                }
                case KEY_BACKSPACE:
                case 127:
                    if (curCol > 0) {
                        buffer[curRow].erase(curCol - 1, 1);
                        --curCol;
                    }
                    break;
                case 10: 
                    buffer.insert(buffer.begin() + curRow + 1, "");
                    ++curRow;
                    curCol = 0;
                    break;
                default:
                    if (ch >= 32 && ch <= 126) { 
                        if (buffer.size() <= curRow) buffer.push_back("");
                        buffer[curRow].insert(curCol, 1, ch);
                        ++curCol;
                    }
                    break;
            }
        }

        clear();
        printw("\n>>> ");
        refresh();
    }

};




#endif