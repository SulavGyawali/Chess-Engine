all:
	clang++ -o MriduEngine main.cpp init.cpp bitboard.cpp hashkeys.cpp board.cpp data.cpp attack.cpp io.cpp movegen.cpp validate.cpp makemove.cpp perft.cpp search.cpp pvtable.cpp misc.cpp evaluate.cpp uci.cpp
