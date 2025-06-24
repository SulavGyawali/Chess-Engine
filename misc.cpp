#include<iostream>
#include"def.h"
#include<sys/time.h>
#include<unistd.h>

int GetTimeMs(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}

int InputWaiting(){
    fd_set readfds;
    FD_ZERO(&readfds);
    struct timeval tv;

    FD_SET(fileno(stdin), &readfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    select(16, &readfds, NULL, NULL, &tv);

    return (FD_ISSET(fileno(stdin), &readfds));

}

void ReadInput(S_SEARCHINFO *info){
    int bytes;
    char input[256] = "", *endc;

    if(InputWaiting()){
        info->stopped = TRUE;
        do{
            bytes = read(fileno(stdin), input, 256);
        }while(bytes < 0);
        endc = strchr(input, '\n');
        if(endc){
            *endc = 0;
        }

        if(strlen(input) > 0){
            if(!strncmp(input, "quit", 4)){
                info->quit = TRUE;
            }
        }
        return;
    }
}

