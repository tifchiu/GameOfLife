#include "cell.h"
#include <string>
#include <vector>

//see cell.h for documentation
Cell::Cell(size_t r, size_t c) : r{r}, c{c}, numAliveNeighbours{0}, state{State::Dead} {}

//see cell.h for documentation
void Cell::setLiving() {
    state = State::Alive;
}

//see cell.h for documentation
void Cell::reset() {
    numAliveNeighbours = 0;
}

//see cell.h for documentation
std::string Cell::getName() {
    std::string s = "(" + std::to_string(r) + "," + std::to_string(c) + ")";
    return s;
}

//see cell.h for documentation
void Cell::broadcastIfAlive() {
    if (state == State::Alive) {
        notifyObservers();
    }
}

//see cell.h for documentation
void Cell::notify( Subject & whoNotified ) {
    numAliveNeighbours++;
}

//see cell.h for documentation
void Cell::recalculate() {
    if (state == State::Alive) {
        if ((numAliveNeighbours < 2) || (numAliveNeighbours > 3)) {
            state = State::Dead;
        }
    } else {
        if (numAliveNeighbours == 3) {
            state = State::Alive;
        }
    }
}

//see cell.h for documentation
Info Cell::getInfo() const {
    Info i{state, r, c};
    return i;
}
