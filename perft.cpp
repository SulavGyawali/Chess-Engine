#include<iostream>
#include"def.h"

long perftLeafNodes;

void Perft(int depth, S_BOARD *pos) {

    ASSERT(CheckBoard(pos));

    if(depth == 0) {
        perftLeafNodes++;
        return;
    }

    S_MOVELIST list[1];
    GenerateAllMoves(pos,list);

    int MoveNum = 0;
    for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {

        if(!MakeMove(pos,list->moves[MoveNum].move)) {
            continue;
        }

        Perft(depth-1,pos);
        TakeMove(pos);
    }

    return;
}

void PerftTest(int depth, S_BOARD *pos){
    
        ASSERT(CheckBoard(pos));
    
        PrintBoard(pos);
    
        perftLeafNodes = 0;

        int start = GetTimeMs(); 
    
        S_MOVELIST list[1];
        GenerateAllMoves(pos,list);
    
        int move;
        int MoveNum = 0;
        for(MoveNum = 0; MoveNum < list->count; ++MoveNum) {
            move = list->moves[MoveNum].move;
            if(!MakeMove(pos,move)) {
                continue;
            }
            long cumnodes = perftLeafNodes;
            Perft(depth-1,pos);
            TakeMove(pos);
            long oldnodes = perftLeafNodes - cumnodes;
        }
    
        std::cout << "\nTest Complete : " << perftLeafNodes << " leaf nodes visited\n";
        std::cout << "Time : " << GetTimeMs() - start << "ms\n";
    
        return;
}