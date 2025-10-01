#ifndef PROCESS_HPP
#define PROCESS_HPP
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
class Proccess {

    private: 
        pid_t pID;
        std::string name;
    public:
        bool runProccess(const std::string& pname, char* argv[])
        {
            pID = fork();
            if(pID == -1){
                perror("fork failed");
                return false;
            } else if(pID == 0){
                execvp(pname.c_str(),argv);
                perror("execvp failed");
                exit(1);

            }
            name = pname;
            int status;
            waitpid(pID, &status, 0);
            return(WIFEXITED(status) && WEXITSTATUS(status) == 0);
        }

};












#endif