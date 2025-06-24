#include <iostream>
#include "def.h"

const int PawnIsolated = -10;
const int PawnPassed[8] = {0, 5, 10, 20, 35, 60, 100, 200};
const int RookOpenFile = 10;
const int RookSemiOpenFile = 5;
const int QueenOpenFile = 5;
const int QueenSemiOpenFile = 3;
const int BishopPair = 30;



const int PawnTable[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    10, 10, 0, -10, -10, 0, 10, 10,
    5, 0, 0, 5, 5, 0, 0, 5,
    0, 0, 10, 20, 20, 10, 0, 0,
    5, 5, 5, 10, 10, 5, 5, 5,
    10, 10, 10, 20, 20, 10, 10, 10,
    20, 20, 20, 30, 30, 20, 20, 20,
    0, 0, 0, 0, 0, 0, 0, 0};

const int KnightTable[64] = {
    0, -10, 0, 0, 0, 0, -10, 0,
    0, 0, 0, 5, 5, 0, 0, 0,
    0, 0, 10, 10, 10, 10, 0, 0,
    0, 0, 10, 20, 20, 10, 5, 0,
    5, 10, 15, 20, 20, 15, 10, 5,
    5, 10, 10, 20, 20, 10, 10, 5,
    0, 0, 5, 10, 10, 5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0};

const int BishopTable[64] = {
    0, 0, -10, 0, 0, -10, 0, 0,
    0, 0, 0, 10, 10, 0, 0, 0,
    0, 0, 10, 15, 15, 10, 0, 0,
    0, 10, 15, 20, 20, 15, 10, 0,
    0, 10, 15, 20, 20, 15, 10, 0,
    0, 0, 10, 15, 15, 10, 0, 0,
    0, 0, 0, 10, 10

};

const int RookTable[64] = {
    0, 0, 5, 10, 10, 5, 0, 0,
    0, 0, 5, 10, 10, 5, 0, 0,
    0, 0, 5, 10, 10, 5, 0, 0,
    0, 0, 5, 10, 10, 5, 0, 0,
    0, 0, 5, 10, 10, 5, 0, 0,
    0, 0, 5, 10, 10, 5, 0, 0,
    25, 25, 25, 25, 25, 25, 25, 25,
    0, 0, 5, 10, 10, 5, 0, 0};

int Mirror64[64] = {
    56, 57, 58, 59, 60, 61, 62, 63,
    48, 49, 50, 51, 52, 53, 54, 55,
    40, 41, 42, 43, 44, 45, 46, 47,
    32, 33, 34, 35, 36, 37, 38, 39,
    24, 25, 26, 27, 28, 29, 30, 31,
    16, 17, 18, 19, 20, 21, 22, 23,
    8, 9, 10, 11, 12, 13, 14, 15,
    0, 1, 2, 3, 4, 5, 6, 7};

const int KingE[64] = {
    -50, -10, 0, 0, 0, 0, -10, -50,
    -10, 0, 10, 10, 10, 10, 0, -10,
    0, 10, 15, 15, 15, 15, 10, 0,
    0, 10, 15, 20, 20, 15, 10, 0,
    0, 10, 15, 20, 20, 15, 10, 0,
    0, 10, 15, 15, 15, 15, 10, 0,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -50, -10, 0, 0, 0, 0, -10, -50};

const int KingO[64] = {
    0, 5, 5, -10, -10, 0, 10, 5,
    -30, -30, -30, -30, -30, -30, -30, -30,
    -50, -50, -50, -50, -50, -50, -50, -50,
    -70, -70, -70, -70, -70, -70, -70, -70,
    -90, -90, -90, -90, -90, -90, -90, -90,
    -110, -110, -110, -110, -110, -110, -110, -110,
    -130, -130, -130, -130, -130, -130, -130, -130,
    -150, -150, -150, -150, -150, -150, -150, -150};

#define MIRROR64(sq) (Mirror64[sq])

int MaterialDraw(const S_BOARD *pos){

    if(!pos->pceNum[wR] && !pos->pceNum[bR] && !pos->pceNum[wQ] && !pos->pceNum[bQ]){
        if(!pos->pceNum[wB] && !pos->pceNum[bB]){
            if(pos->pceNum[wN] < 3 && pos->pceNum[bN] < 3){
                if(pos->pceNum[wP] < 5 && pos->pceNum[bP] < 5){
                    return TRUE;
                }
            }
        }else if(!pos->pceNum[wN] && !pos->pceNum[bN]){
            if(pos->pceNum[wP] < 5 && pos->pceNum[bP] < 5){
                if(pos->pceNum[wB] < 3 && pos->pceNum[bB] < 3){
                    return TRUE;
                }
            }
        }else if(pos->pceNum[wP] < 5 && pos->pceNum[bP] < 5){
            if(pos->pceNum[wB] < 3 && pos->pceNum[bB] < 3){
                if(pos->pceNum[wN] < 3 && pos->pceNum[bN] < 3){
                    return TRUE;
                }
            }
        }
    }else if(!pos->pceNum[wQ] && !pos->pceNum[bQ]){
        if(pos->pceNum[wR] < 2 && pos->pceNum[bR] < 2){
            if(pos->pceNum[wB] < 2 && pos->pceNum[bB] < 2){
                if(pos->pceNum[wN] < 2 && pos->pceNum[bN] < 2){
                    if(pos->pceNum[wP] == 0 && pos->pceNum[bP] == 0){
                        return TRUE;
                    }
                }else if(pos->pceNum[wN] < 3 && pos->pceNum[bN] < 3){
                    if(pos->pceNum[wP] < 6 && pos->pceNum[bP] < 6){
                        return TRUE;
                    }
                }
            }else if(pos->pceNum[wB] < 3 && pos->pceNum[bB] < 3){
                if(pos->pceNum[wN] < 3 && pos->pceNum[bN] < 3){
                    if(pos->pceNum[wP] < 6 && pos->pceNum[bP] < 6){
                        return TRUE;
                    }
                }
            }
        }else if(pos->pceNum[wR] < 3 && pos->pceNum[bR] < 3){
            if(pos->pceNum[wB] < 3 && pos->pceNum[bB] < 3){
                if(pos->pceNum[wN] < 3 && pos->pceNum[bN] < 3){
                    if(pos->pceNum[wP] < 6 && pos->pceNum[bP] < 6){
                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

#define ENDGAME_MAT (1 * PieceVal[wR] + 2 * PieceVal[wN] + 2 * PieceVal[wP] + PieceVal[wK])

int EvalPosition(const S_BOARD *pos)
{
    int pce;
    int sq;
    int pceNum;
    int score = pos->material[WHITE] - pos->material[BLACK];

    if(!pos->pceNum[wP] && !pos->pceNum[bP] && MaterialDraw(pos) == TRUE){
        return 0;
    }

    pce = wP;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score += PawnTable[SQ64(sq)];

        if(!(IsolatedMask[SQ64(sq)] & pos->pawns[WHITE])){
            score += PawnIsolated;
        }

        if((WhitePassedMask[SQ64(sq)] & pos->pawns[BOTH]) == 0){
            score += PawnPassed[RanksBrd[sq]];
        }
    }

    pce = bP;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score -= PawnTable[MIRROR64(SQ64(sq))];

        if(!(IsolatedMask[SQ64(sq)] & pos->pawns[BLACK])){
            score -= PawnIsolated;
        }

        if(BlackPassedMask[SQ64(sq)] & pos->pawns[WHITE]){
            score -= PawnPassed[7 - RanksBrd[sq]];
        }
    }

    pce = wN;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score += KnightTable[SQ64(sq)];
    }

    pce = bN;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score -= KnightTable[MIRROR64(SQ64(sq))];
    }

    pce = wB;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score += BishopTable[SQ64(sq)];
    }

    pce = bB;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score -= BishopTable[MIRROR64(SQ64(sq))];
    }

    pce = wR;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score += RookTable[SQ64(sq)];

        if(!(pos->pawns[BOTH] & FileMask[FilesBrd[sq]])){
            score += RookOpenFile;
        }else if(!(pos->pawns[WHITE] & FileMask[FilesBrd[sq]])){
            score += RookSemiOpenFile;
        }

    }

    pce = bR;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score -= RookTable[MIRROR64(SQ64(sq))];

        if(!(pos->pawns[BOTH] & FileMask[FilesBrd[sq]])){
            score -= RookOpenFile;
        }else if(!(pos->pawns[BLACK] & FileMask[FilesBrd[sq]])){
            score -= RookSemiOpenFile;
        }
    }

    pce = wQ;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score += RookTable[SQ64(sq)];

        if(!(pos->pawns[BOTH] & FileMask[FilesBrd[sq]])){
            score += QueenOpenFile;
        }else if(!(pos->pawns[WHITE] & FileMask[FilesBrd[sq]])){
            score += QueenSemiOpenFile;
        }
    }

    pce = bQ;

    for (pceNum = 0; pceNum < pos->pceNum[pce]; ++pceNum)
    {
        sq = pos->pList[pce][pceNum];
        score -= RookTable[MIRROR64(SQ64(sq))];

        if(!(pos->pawns[BOTH] & FileMask[FilesBrd[sq]])){
            score -= QueenOpenFile;
        }else if(!(pos->pawns[BLACK] & FileMask[FilesBrd[sq]])){
            score -= QueenSemiOpenFile;
        }
    }

    pce = wK;

    sq = pos->pList[pce][0];

    if(pos->material[BLACK] <= ENDGAME_MAT){
        score += KingE[SQ64(sq)];
    }else{
        score += KingO[SQ64(sq)];
    }

    pce = bK;

    sq = pos->pList[pce][0];

    if(pos->material[WHITE] <= ENDGAME_MAT){
        score -= KingE[MIRROR64(SQ64(sq))];
    }else{
        score -= KingO[MIRROR64(SQ64(sq))];
    }

    if(pos->pceNum[wB] >= 2){
        score += BishopPair;
    }

    if(pos->pceNum[bB] >= 2){
        score -= BishopPair;
    }

    if (pos->side == WHITE)
    {
        return score;
    }
    else
    {
        return -score;
    }

    return 0;
}
