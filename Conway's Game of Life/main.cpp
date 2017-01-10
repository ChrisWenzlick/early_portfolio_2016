// Chris Wenzlick
// 4-8-2014
// Conway's Game of Life
//
// Program accepts a seed state for the matrix, then updates it
// according to the standard rules for Conway's Game of Life

#include <iostream>

#define WIDTH 25
#define HEIGHT 25
#define ALIVE 1
#define DEAD 0

// TableType
// Purpose: stores a matrix of integers, either 1 or 0, representing living and dead cells
typedef int TableType[WIDTH][HEIGHT];


//// BEGIN FUNCTION PROTOTYPES ////

// getSeed
// Purpose: retrieve the initial state of the matrix from the user
// Input:
//      frontTable - the matrix that will be drawn
//      backTable - the matrix on which operations are performed
// Output:
//      No return type. The function, once completed, will have assigned input to the backTable.
void getSeed(TableType frontTable, TableType backTable);

// iterate
// Purpose: update the matrix according to the game rules and display the next cycle
// Input:
//      frontTable - the matrix that will be drawn
//      backTable - the matrix on which operations are performed
// Output:
//      No return type. The function, once completed, will advance the game by one cycle.
void iterate(TableType frontTable, TableType backTable);

// countNeighbors
// Purpose: count the living neighbors surrounding a single cell
// Input:
//      frontTable - the matrix that was drawn last
//      x - the x position of the cell
//      y - the y position of the cell
// Output:
//      Returns an integer containing the total number of living neighbors to the cell.
int countNeighbors(TableType frontTable, int x, int y);

// calculateCell
// Purpose: determine whether a cell is alive or dead, and update it accordingly
// Input:
//      backTable - the matrix on which operations are performed
//      x - the x position of the cell
//      y - the y position of the cell
//      numOfNeighbors - the number of living neighbors to the cell
// Output:
//      No return type. The function, once completed, assigns the updated state of the cell to backTable.
void calculateCell(TableType backTable, int x, int y, int numOfNeighbors);

// printTable
// Purpose: display the matrix with proper formatting to allow easy viewing of results
// Input:
//      frontTable - the matrix that will be drawn
//      backTable - the matrix on which operations are performed
// Output:
//      No return type. The function copies backTable to frontTable and then prints frontTable.
void printTable(TableType frontTable, TableType backTable);

//// END FUNCTION PROTOTYPES ////


int main(int argc, char* argv[]){

    char quitProgram = ' ';
    TableType frontTable; // The table that gets drawn
    TableType backTable; // The table that is altered
    int generation = 0; // The number of the current generation

    getSeed(frontTable, backTable); // Get the seed data from the user

    do{
        generation++;
        iterate(frontTable, backTable); // Update the table by one cycle
        std::cout << "\nGENERATION: " << generation << "\nEnter 'q' to quit or 'c' to continue: ";
        std::cin >> quitProgram;
        std::cout << "\n";
    }while(quitProgram != 'q');

    return 0;
}

void iterate(TableType frontTable, TableType backTable){
    int x; // The column currently being looked at
    int y; // The row currently being looked at
    int numOfNeighbors; // The number of live neighbors to the cell

    for(x=0; x < WIDTH; x++){
        for(y=0; y < HEIGHT; y++){
            numOfNeighbors = countNeighbors(frontTable, x, y);
            calculateCell(backTable, x, y, numOfNeighbors);
        }
    }

    printTable(frontTable, backTable);
}

void getSeed(TableType frontTable, TableType backTable){
    int x; // The column currently being looked at
    int y; // The row currently being looked at
    int input; // The number the user enters

    for(y=0; y < HEIGHT; y++){
        for(x=0; x < WIDTH; x++){
            std::cout << "Please enter data for cell " << x << "," << y << ". (1 = alive, 0 = dead): ";
            std::cin >> input;
            if((input != 1) && (input != 0)){
                std::cout << "\nERROR, unknown data entered.\n";
                std::cout << "Please enter data for cell " << x << "," << y << ". (1 = alive, 0 = dead): ";
                std::cin >> input;
            }
            backTable[x][y] = input;
            std::cout << "\n";
        }
    }
    printTable(frontTable, backTable); // Display the seed table
}

int countNeighbors(TableType frontTable, int x, int y){
    int numOfNeighbors = 0; // The number of live neighbors to the cell

    // For this cell, count all living neighbors in the eight surrounding spaces

    // check top-left cell
    if(x>0 && y>0){
        if(frontTable[x-1][y-1] == ALIVE){
            numOfNeighbors++;
        }
    }
    // check top cell
    if(y>0){
        if(frontTable[x][y-1] == ALIVE){
            numOfNeighbors++;
        }
    }
    // check top-right cell
    if(x<WIDTH-1 && y>0){
        if(frontTable[x+1][y-1] == ALIVE){
            numOfNeighbors++;
        }
    }
    // check left cell
    if(x>0){
        if(frontTable[x-1][y] == ALIVE){
            numOfNeighbors++;
        }
    }
    // check right cell
    if(x<WIDTH-1){
        if(frontTable[x+1][y] == ALIVE){
            numOfNeighbors++;
        }
    }
    // check bottom-left cell
    if(x>0 && y<HEIGHT-1){
        if(frontTable[x-1][y+1] == ALIVE){
            numOfNeighbors++;
        }
    }
    // check bottom cell
    if(y<HEIGHT-1){
        if(frontTable[x][y+1] == ALIVE){
            numOfNeighbors++;
        }
    }
    // check bottom-right cell
    if(x<WIDTH-1 && y<HEIGHT-1){
        if(frontTable[x+1][y+1] == ALIVE){
            numOfNeighbors++;
        }
    }

    return numOfNeighbors;
}

void calculateCell(TableType backTable, int x, int y, int numOfNeighbors){
    if(numOfNeighbors < 2){
        backTable[x][y] = DEAD;
    }
    if(numOfNeighbors > 3){
        backTable[x][y] = DEAD;
    }
    if(numOfNeighbors == 3){
        backTable[x][y] = ALIVE;
    }
}

void printTable(TableType frontTable, TableType backTable){

    int x; // The column currently being looked at
    int y; // The row currently being looked at

    // Update the front table with the information
    for(x=0; x < WIDTH; x++){
        for(y=0; y < HEIGHT; y++){
            frontTable[x][y] = backTable[x][y];
        }
    }

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; // print 30 blank lines to clear display

    for(y=0; y < HEIGHT; y++){
        for(x=0; x < WIDTH; x++){
            if(frontTable[x][y] == ALIVE){
                std::cout << "#";
            }
            else{
                std::cout << "_";
            }
        }
        std::cout << "\n"; // move to next row
    }
}
