#include <iostream>
#include "def.h"
#include <string>
#include <cstring>

#define INPUTBUFFER 400 * 6
#define AUTHOR "Sujan"

void ParseGo(char *line, S_SEARCHINFO *info, S_BOARD *pos){

    int depth = -1, movestogo = 30, movetime = -1;
    int time = -1, inc = 0;
    char *ptr = NULL;
    info->timeset = FALSE;

    if ((ptr = strstr(line, "infinite")) != NULL)
    {
        ;
    }

    if ((ptr = strstr(line, "binc")) != NULL && pos->side == BLACK)
    {
        inc = atoi(ptr + 5);
    }

    if ((ptr = strstr(line, "winc")) != NULL && pos->side == WHITE)
    {
        inc = atoi(ptr + 5);
    }

    if ((ptr = strstr(line, "wtime")) != NULL && pos->side == WHITE)
    {
        time = atoi(ptr + 6);
    }

    if ((ptr = strstr(line, "btime")) != NULL && pos->side == BLACK)
    {
        time = atoi(ptr + 6);
    }

    if ((ptr = strstr(line, "movestogo")) != NULL)
    {
        movestogo = atoi(ptr + 10);
    }

    if ((ptr = strstr(line, "movetime")) != NULL)
    {
        movetime = atoi(ptr + 9);
    }

    if ((ptr = strstr(line, "depth")) != NULL)
    {
        depth = atoi(ptr + 6);
    }

    if (movetime != -1)
    {
        time = movetime;
        movestogo = 1;
    }

    info->starttime = GetTimeMs();
    info->depth = depth;

    if (time != -1)
    {
        info->timeset = TRUE;
        time /= movestogo;
        time -= 50;
        info->stoptime = info->starttime + time + inc;
    }

    if (depth == -1)
    {
        info->depth = MAXDEPTH;
    }

    std::cout << "time:" << time << " start:" << info->starttime << " stop:" << info->stoptime << " depth:" << info->depth << " timeset:" << info->timeset << std::endl;

    SearchPosition(pos, info);

}

void ParsePosition(char *lineIn, S_BOARD *pos)
{

    lineIn += 9;
    char *ptrChar = lineIn;

    if (strncmp(lineIn, "startpos", 8) == 0)
    {
        ParseFen(START_FEN, pos);
    }
    else
    {
        ptrChar = strstr(lineIn, "fen");
        if (ptrChar == NULL)
        {
            ParseFen(START_FEN, pos);
        }
        else
        {   
            if(strlen(ptrChar) > 4){
                ptrChar += 4;
            }
            ParseFen(ptrChar, pos);
        }
    }

    ptrChar = strstr(lineIn, "moves");
    int move;
    if (ptrChar != NULL)
    {
        ptrChar += 6;
        while (*ptrChar)
        {
            move = ParseMove(ptrChar, pos);
            if (move == NOMOVE)
            {
                break;
            }
            MakeMove(pos, move);
            pos->ply = 0;
            while (*ptrChar && *ptrChar != ' ')
            {
                ptrChar++;
            }
            ptrChar++;
        }
    }

    PrintBoard(pos);
}

void Uci_Loop(S_BOARD *pos, S_SEARCHINFO *info)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    char line[INPUTBUFFER];
    std::cout << "id name " << NAME << "\n";
    std::cout << "id author " << AUTHOR << "\n";
    std::cout << "uciok\n";

   
    InitPvTable(pos->PvTable);

    while (true)
    {
        memset(&line[0], 0, sizeof(line));
        fflush(stdout);
        if (!fgets(line, INPUTBUFFER, stdin))
        {
            continue;
        }

        if (line[0] == '\n')
        {
            continue;
        }

        if (!strncmp(line, "isready", 7))
        {
            std::cout << "readyok\n";
            continue;
        }
        else if (!strncmp(line, "position", 8))
        {
            ParsePosition(line, pos);
        }
        else if (!strncmp(line, "ucinewgame", 10))
        {
            ParsePosition("position startpos\n", pos);
        }
        else if (!strncmp(line, "go", 2))
        {
            ParseGo(line, info, pos);
        }
        else if (!strncmp(line, "quit", 4))
        {
            info->quit = TRUE;
            break;
        }
        else if (!strncmp(line, "uci", 3))
        {
            std::cout << "id name " << NAME << "\n";
            std::cout << "id author " << AUTHOR << "\n";
            std::cout << "uciok\n";
        }
        if (info->quit)
        {
            break;
        }
    }
}