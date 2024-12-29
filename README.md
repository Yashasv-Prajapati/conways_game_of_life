# Conway's Game of Life
This repository is about conway's game of life, implemented in C++. The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

## Demo
https://github.com/user-attachments/assets/787b6627-4530-4b1e-9944-0657487da001

## Rules
1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
Source: Wikipedia

## How to run
1. Clone the repository
2. Run the following commands:
```bash
g++ -o main main.cpp
./main
```

The changing output will be visible in the console window.

## Future Work
1. Change the initial configuration of the game.
2. Code structure improvement.
3. Potential improvement in the logic of identifying the dead cells and keeping track of their live neighbours.
