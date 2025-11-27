# Chess Engine

> A custom chess engine written in **C++**, reaching an estimated **~2250 Elo** (tested against a Chess.com bot).

## ♟️ Overview
This project is a fully functional chess engine implemented from scratch in C++. It includes complete move generation, an evaluation function, and a minimax + alpha-beta pruning search algorithm. The goal of the engine is to provide a clean, understandable, and competitive chess engine built without relying on external libraries.

## 🚀 Features

### ✔️ Implemented
- **Complete move generation** for all pieces
- **Legal move validation** (king safety, checks, pins, discoveries)
- **Minimax search**
- **Alpha-Beta pruning** for efficient search
- **Static evaluation function** including:
  - Material balance
  - Piece-square tables
  - Mobility
  - King safety basics
  - Pawn structure evaluation
- **CLI-based gameplay** or engine-vs-engine simulation
- **Basic time control using depth-limited search**
- **Performance-tested to ~2250 Elo** vs Chess.com bot


## 🛠️ Build & Run

### Requirements
- C++ compiler supporting C++17 or above
- Make (optional)

### Build
```bash
make
```
Or manually:
```bash
g++ -std=c++17 -O2 -o chess main.cpp src/*.cpp
```

### Run
```bash
./chess
```

## 🧠 How the Engine Thinks

### Search Algorithm
- Minimax recursive search
- Alpha-Beta pruning to reduce search tree
- Depth-based search (no iterative deepening yet)

### Evaluation
- Material scoring
- Piece-square tables
- Positional bonuses/penalties
- King safety heuristics
- Mobility counts

This combination enables the engine to play at a strong amateur level (~2250 Elo).

