#include "grid.h"
#include "textdisplay.h"
#include <vector>
#include <stdexcept>
#include <iostream>

//see grid.h for documentation
Grid::~Grid() {
    theGrid.clear();
    delete td;
}

//see grid.h for documentation
void Grid::printCellNeighbours() {
    for (std::vector<Cell> i : theGrid) {   
        for (Cell j : i) {
            std::cout << j.getName() << ": " << j.getObserverNames() << std::endl;
        }
    }
}

// helper function for setNeighbours(). isValid(x,y,n) checks if a Cell at position x,y is valid
// in a n by n Grid
bool Grid::isValid( int x, int y, int n) {
    return ((x >= 0) && (x < n) && (y >= 0) && (y < n));
}

// helper function for init(). setNeighbours(n) populates the vector of neighbours for every Cell
// in a n by n Grid. Only called for valid n (enforced by Grid::init)
void Grid::setNeighbours( int n ) {
    // for every Cell, we have 8 possible neighbours
    for (int r = 0; r < n; r++) {
        for (int col = 0; col < n; col++) {
            // for each potential neighbour, we check if it is a valid Cell.
            // if so, we call Subject::attach to make the neighbour an Observer of 
            // the current Cell (r,col)
            // NORTH NEIGHBOUR
            if (isValid(r, col+1, n)) {
                theGrid[r][col].attach(&theGrid[r][col+1]);
            }
            // EAST NEIGHBOUR
            if (isValid(r+1, col, n)) {
                theGrid[r][col].attach(&theGrid[r+1][col]);
            }
            // WEST NEIGHBOUR
            if (isValid(r-1, col, n)) {
                theGrid[r][col].attach(&theGrid[r-1][col]);
            }
            // SOUTH NEIGHBOUR
            if (isValid(r, col-1, n)) {
                theGrid[r][col].attach(&theGrid[r][col-1]);
            }
            // NORTHWEST NEIGHBOUR
            if (isValid(r-1, col+1, n)) {
                theGrid[r][col].attach(&theGrid[r-1][col+1]);
            }
            // SOUTHWEST NEIGHBOUR
            if (isValid(r-1, col-1, n)) {
                theGrid[r][col].attach(&theGrid[r-1][col-1]);
            }
            // NORTHEAST NEIGHBOUR
            if (isValid(r+1, col+1, n)) {
                theGrid[r][col].attach(&theGrid[r+1][col+1]);
            }
            // SOUTHEAST NEIGHBOUR
            if (isValid(r+1, col-1, n)) {
                theGrid[r][col].attach(&theGrid[r+1][col-1]);
            }
            // for each cell, attach textDisplay as an observer
            theGrid[r][col].attach(td);
        } 
    }

}

//see grid.h for documentation
void Grid::init( int n ) {
    if (n >= 1) {
        // if we call `new` in the middle of a simulation we have to clear the TD vector and theGrid
        if (td != nullptr) {
            delete td;
            theGrid.clear();
        }
        // new n x n TextDisplay associated with every new grid
        td = new TextDisplay(n);
        std::vector<Cell> temp;
        for (int rows = 0; rows < n; rows++) {
            for (int columns = 0; columns < n; columns++) {
                temp.emplace_back(rows,columns);        // construct a Cell at (rows,columns) and add it to temp vector representing row
            }
            theGrid.push_back(temp);        // push temp vector (representing a row) to theGrid
            temp.clear();
        }
        // set neighbours for the n x n grid
        setNeighbours(n);
    } else {
        // throw error for n < 1
        // error is caught in main.cc
        throw std::invalid_argument("ERROR: grid size < 1");
    }  
}

//see grid.h for documentation
void Grid::turnOn( int r, int c ) {
    int n = theGrid.size();     //num of rows in theGrid
    if (!isValid(r, c, n)) {
        // if (r,c) is not a valid Cell in a n x n grid, we throw invalid_arg error
        // error is caught in main.cc
        std::string error = "ERROR: coordinates (" + std::to_string(r) + "," + std::to_string(c) + ") are not in the range 0 to " + std::to_string(n-1);
        throw std::invalid_argument(error);
    }
    // set (r,c) to living
    theGrid[r][c].setLiving();
    // notify TextDisplay that a (possible) change has been made
    td->notify(theGrid[r][c]);
}

//see grid.h for documentation
void Grid::tick() {
    // every Cell in theGrid broadcasts to its neighbours if it is alive
    int size = theGrid.size();
    for (std::vector<Cell> i : theGrid) {   
        for (Cell j : i) {
            j.broadcastIfAlive();
        }
    }
    // for every Cell in theGrid, its state for the next iteration is determined
    // td is notified of a (possible) change
    // numAliveNeigbours for the cell is reset to 0 for the next iteration
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            theGrid[r][c].recalculate();
            td->notify(theGrid[r][c]);
            theGrid[r][c].reset();
        }
    }
}

//see grid.h for documentation
std::ostream & operator<<( std::ostream & out, const Grid & g ) {
    if (g.theGrid.size() != 0) {
        out << *g.td;
    }
    return out;
}
