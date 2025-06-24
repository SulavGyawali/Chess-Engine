#include "def.h"
#include<iostream>
#include<cstdio>

char *PrSq(const int sq){

    static char sqStr[3];

    int file = FilesBrd[sq];
    int rank = RanksBrd[sq];

    snprintf(sqStr, sizeof(sqStr), "%c%c", ('a' + file), ('1' + rank));

    return sqStr;
}

char *PrMove(const int move){

    static char MvStr[6];

    int ff = FilesBrd[FROMSQ(move)];
    int rf = RanksBrd[FROMSQ(move)];
    int ft = FilesBrd[TOSQ(move)];
    int rt = RanksBrd[TOSQ(move)];

    int promoted = PROMOTED(move);

    if(promoted){
        char pchar = 'q';
        if(IsKn(promoted)){
            pchar = 'n';
        }else if(IsRQ(promoted) && !IsBQ(promoted)){
            pchar = 'r';
        }else if(!IsRQ(promoted) && IsBQ(promoted)){
            pchar = 'b';
        }
        snprintf(MvStr, sizeof(MvStr), "%c%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt), pchar);
    }else{
        snprintf(MvStr, sizeof(MvStr), "%c%c%c%c", ('a' + ff), ('1' + rf), ('a' + ft), ('1' + rt));
    }

    return MvStr;
}

int ParseMove(char *ptrCHar, S_BOARD *pos){
    if(ptrCHar[1] > '8' || ptrCHar[1] < '1') return NOMOVE;
    if(ptrCHar[3] > '8' || ptrCHar[3] < '1') return NOMOVE;
    if(ptrCHar[0] > 'h' || ptrCHar[0] < 'a') return NOMOVE;
    if(ptrCHar[2] > 'h' || ptrCHar[2] < 'a') return NOMOVE;

    int from = FR2SQ(ptrCHar[0] - 'a', ptrCHar[1] - '1');
    int to = FR2SQ(ptrCHar[2] - 'a', ptrCHar[3] - '1');

    ASSERT(SqOnBoard(from) && SqOnBoard(to));

    S_MOVELIST list[1];
    GenerateAllMoves(pos, list);
    int MoveNum = 0;
    int Move = NOMOVE;
    int PromPce = EMPTY;

    for(MoveNum = 0; MoveNum < list->count; ++MoveNum){
        Move = list->moves[MoveNum].move;
        if(FROMSQ(Move) == from && TOSQ(Move) == to){
            PromPce = PROMOTED(Move);
            if(PromPce != EMPTY){
                if(IsRQ(PromPce) && !IsBQ(PromPce) && ptrCHar[4] == 'r'){
                    return Move;
                }else if(!IsRQ(PromPce) && IsBQ(PromPce) && ptrCHar[4] == 'b'){
                    return Move;
                }else if(IsRQ(PromPce) && IsBQ(PromPce) && ptrCHar[4] == 'q'){
                    return Move;
                }else if(IsKn(PromPce) && ptrCHar[4] == 'n'){
                    return Move;
                }
                continue;
            }
            return Move;
        }
    }

    return NOMOVE;
}

void PrintMoveList(const S_MOVELIST *list){
    int index = 0;
    int score = 0;
    std::cout<<"MoveList:\n";
    for(index = 0; index < list->count; ++index){
        score = list->moves[index].score;
        std::cout<<"Move:"<<index+1<<"("<<score<<"):"<<PrMove(list->moves[index].move)<<"\n";
    }
    std::cout<<"MoveList Total "<<list->count<<" Moves:\n\n";
}