// Conway's Game of Life
#include <iostream>
#include <thread>
#include <chrono>
#include <bits/stdc++.h>

const std::string BLACK_BLOCK = "\033[30m\033[47m  ";
const std::string WHITE_BLOCK = "\033[37m\033[40m  ";
const std::string RESET_BLOCK = "\033[0m";
const std::string CLEAR_SCREEN = "\033[2J";

void moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void clearScreen() {
    std::cout << CLEAR_SCREEN; // clear screen
    moveCursor(1,1); // move cursor to (1, 1)
    return;
}

void renderCell(int x, int y, bool isBlack) {
    if (isBlack) {
        std::cout << BLACK_BLOCK; // Black "block" with white background
    } else {
        std::cout << WHITE_BLOCK; // White "block" with black background
    }
    // std::cout << RESET_BLOCK; // Reset attributes
}

void drawGrid(const std::vector<std::vector<int>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            renderCell(x, y, grid[y][x]);
        }
        std::cout << RESET_BLOCK<< "\n";
    }
}

/*
This function modifies the grid according to the rules of Conway's Game of Life:
Source: Wikipedia
1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
void modifyGrid(std::vector<std::vector<int>> &grid, std::queue<std::pair<int,int>> &activeCells){
    int rows = grid.size();
    int cols = grid[0].size();
    
    int len = activeCells.size();
    for(int i=0;i<len;i++){
        std::pair<int,int> cell = activeCells.front();
        activeCells.pop(); // remove the current active cell from the queue
        // check for the number of active neighbours 
        int activeNeighbours = 0;
        for(int i=-1;i<=1;i++){ 
            for(int j=-1;j<=1;j++){
                if(i==0 && j==0) continue; // skip the current cell
                int x = cell.first + i;
                int y = cell.second + j;
                if(x>=0 && x<rows && y>=0 && y<cols){
                    if(grid[x][y]==1) activeNeighbours++;
                }
            }
        }
        if(activeNeighbours<2 || activeNeighbours>3){ // cell must die
            grid[cell.first][cell.second] = 0;
        }else{ // cell will remain alive - so push it back to the queue
            activeCells.push(cell);
        }

        /*
        -- Check for the dead cells around this current active cell
        -- So basically we go the neighbour dead cell and look for the number of active neighbours around it.
        
        Q: Why are we looking at only the neighbours of the current active cell? - 
        Ans: because for a dead cell to become active it must have some active cell around it(exactly 3 to be precise), 
        so if there is no active cell around a dead cell, there is no point in checking that dead cell's active neighbours. 
        However, if the dead cell has even one active cell as neighbour(which indirectly means that an active cell has a dead cell as neighbour), 
        it is worth checking for more.
        */
        for(int i=-1;i<=1;i++){ 
            for(int j=-1;j<=1;j++){
                if(i==0 && j==0) continue; // skip the current cell
                int x = cell.first + i;
                int y = cell.second + j;
                if(x>=0 && x<rows && y>=0 && y<cols){
                    // grid[x][y] - neighbour cell of current cell
                    if(grid[x][y]==0){ // this checks if the neighbour of current cell is dead
                        activeNeighbours = 0; // for this deadCell check if the active neighbours are 3
                        for(int i=-1;i<=1;i++){ 
                            for(int j=-1;j<=1;j++){
                                if(i==0 && j==0) continue; // skip the current cell
                                int x = cell.first + i;
                                int y = cell.second + j;
                                if(x>=0 && x<rows && y>=0 && y<cols){
                                    if(grid[x][y]==1) activeNeighbours++;
                                }
                            }
                        }
                        if(activeNeighbours==3){
                            grid[x][y] = 1;
                            activeCells.push({x,y});
                        }
                    }
                }
            }
        }
    }

}

void initializeGridWithRandomValues(std::vector<std::vector<int>> &grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            grid[y][x] = rand() % 2; // Randomly set cell to be black or white
        }
    }
}

int main() {
    const int rows = 20, cols = 20;
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0)); // Initialize grid with all 0s - white

    // Clear screen and set up grid
    std::cout << CLEAR_SCREEN;

    initializeGridWithRandomValues(grid);
    std::queue<std::pair<int,int>> activeCells;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(grid[i][j]==1){
                activeCells.push({i,j});
            }
        }
    }

    // Initial rendering of the grid
    for(;;){
        clearScreen(); // Clear screen
        drawGrid(grid); // Draw the current configuration of the grid
        modifyGrid(grid, activeCells); // Modify the grid for drawing the next frame
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}