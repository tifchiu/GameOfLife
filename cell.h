#ifndef CELL_H
#define CELL_H
#include <cstddef> // defines size_t i.e. an unsigned int
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "info.h"

class Cell : public Subject, public Observer {
    const size_t r, c;      // coordinates of cell
    int numAliveNeighbours; // current number of neighbours who are alive
    State state;            // dead/alive

    // Add other private members if necessary

  public:
    Cell(size_t r, size_t c); // Cell is at row r and column c of the grid
    void setLiving();         // Marks cell as alive. Called by Grid::turnOn.
    void reset();             // Resets neighbour count to 0.

    // Return a string consisting of "(r,c)" where r and c are the data fields.
    virtual std::string getName() override;

    // Grid calls this to start the process whereby a cell notifies its neighbours if it
    // is alive.
    void broadcastIfAlive();
    
    // My neighbours will call this to let me know if they're alive. Also needs
    // to be called when state is set to be alive so display(s) are notified.
    void notify( Subject & whoNotified ) override;
                                                
    // Reassess my living-or-dead status, based on information from neighbours.
    void recalculate(); 

    // Observer calls this to get information about cell.
    virtual Info getInfo() const override;
};

#endif
