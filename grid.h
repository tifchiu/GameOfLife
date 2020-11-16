#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <stdexcept> // defines std::invalid_argument
#include "cell.h"

class TextDisplay;
class Observer;

// Grid is initially empty. Sets up a TextDisplay observer when init() is called
// and the grid is initialized with cell objects.
class Grid {
    std::vector<std::vector<Cell>> theGrid;  // The actual grid.
    TextDisplay *td = nullptr;               // The text display is an observer on each cell.
 
    // Add private members, if necessary.
  protected:
    bool isValid( int x, int y, int n);
    void setNeighbours(int n);
 
  public:
    // Default ctor not needed, but may be added if you feel it is necessary.
    ~Grid();
  
    // Outputs the name of each cell, followed by its list of neighbours, to stdout.
    // Format for part a) is:
    // (0,0): (0,1) (1,0) (1,1) \n
    // (0,1): (0,0) (1,0) (0,2) (1,1) (1,2) \n
    // ...
    //
    // Format for part b) is:
    // (0,0): (0,1) (1,0) (1,1) TD \n
    // (0,1): (0,0) (1,0) (0,2) (1,1) (1,2) TD \n
    // ...
    void printCellNeighbours();

    // Sets up an n x n grid, and adds each cell's neighbour and the text display as observers. 
    // Clears old grid, if necessary. If n < 1, raises std::invalid_argument with the message:
    // "ERROR: grid size < 1".
    void init( int n );       

    // Marks cell at row r, col c as alive by calling Cell::setLiving().
    // If either r or c are not in the range 0 to N-1 (where N is the size of the grid), raises
    // std::invalid_argument with the message: 
    //     "ERROR: coordinates (r,c) are not in the range 0 to N-1" where r, c, and N-1 are the
    // appropriate numeric values.
    void turnOn( int r, int c );  

    // Next tick of the simulation.
    void tick();
    
    friend std::ostream & operator<<( std::ostream & out, const Grid & g );
};

// Uses the TextDisplay to output the grid information.
std::ostream & operator<<( std::ostream & out, const Grid & g );

#endif
