#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROW 20
#define COL 20
#define DELAY 500000 
#define VIRUS '+'
#define EMPTY '.'
#define NEIGHBOR 'o'

void initializeGrid(char grid[ROW][COL]);
void printGrid(char grid[ROW][COL]);
void displayWithNeighbors(char grid[ROW][COL]);
void nextGeneration(char grid[ROW][COL], char newGrid[ROW][COL]);
int countNeighbors(char grid[ROW][COL], int row, int col);
void copyGrid(char source[ROW][COL], char destination[ROW][COL]);

int main() {
    char grid[ROW][COL];
    char newGrid[ROW][COL];
    
    srand(time(NULL));
    initializeGrid(grid);
    
    while (1) {
        system("clear"); 
        printf("Virus Simulation: \n");
        printf("Legend:\n");
        printf("Virus = (+)\n");
        printf("Neighbor = (o)\n");
        printf("Empty = (.)\n\n");
        displayWithNeighbors(grid);
        nextGeneration(grid, newGrid);
        copyGrid(newGrid, grid);
        usleep(DELAY);
    }
    return 0;
}
void initializeGrid(char grid[ROW][COL]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            grid[row][col] = (rand() % 5 == 0) ? VIRUS : EMPTY; 
        }
    }
}
void printGrid(char grid[ROW][COL]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            printf("%c ", grid[row][col]);
        }
        printf("\n");
    }
}
void nextGeneration(char grid[ROW][COL], char newGrid[ROW][COL]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            int neighbors = countNeighbors(grid, row, col);
            
            if (grid[row][col] == VIRUS) { 
                
                if (neighbors < 2) {
                    newGrid[row][col] = EMPTY; 
                }
                else if (neighbors == 2 || neighbors == 3) {
                    newGrid[row][col] = VIRUS; 
                }
                else {
                    newGrid[row][col] = EMPTY; 
                }
            } else { 
                
                if (neighbors == 3) {
                    newGrid[row][col] = VIRUS; 
                } else {
                    newGrid[row][col] = EMPTY; 
                }
            }
        }
    }
}
int countNeighbors(char grid[ROW][COL], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newRow = row + i, newCol = col + j;
            if (newRow >= 0 && newRow < ROW && newCol >= 0 && newCol < COL) {
                if (grid[newRow][newCol] == VIRUS) {
                    count++;
                }
            }
        }
    }
    return count;
}
void displayWithNeighbors(char grid[ROW][COL]) {
    char displayGrid[ROW][COL];
    
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            displayGrid[row][col] = grid[row][col];
        }
    }
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (grid[row][col] == EMPTY) {
                int n = countNeighbors(grid, row, col);
                if (n > 0) {
                    displayGrid[row][col] = NEIGHBOR;
                }
            }
        }
    }
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            printf("%c ", displayGrid[row][col]);
        }
        printf("\n");
    }
}
void copyGrid(char source[ROW][COL], char destination[ROW][COL]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            destination[row][col] = source[row][col];
        }
    }
}