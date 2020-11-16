#include "textdisplay.h"
#include "subject.h"
#include "info.h"
#include "cell.h"
#include <string>
#include <vector>

// Declare constants
const std::string TD = "TD";
const char DEAD = '_';
const char ALIVE = 'X';

// see textdisplay.h for documentation
TextDisplay::TextDisplay( size_t n ) {
    std::vector<char> temp;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            temp.push_back(DEAD);
        }
        theDisplay.push_back(temp);
        temp.clear();
    }
}

// see textdisplay.h for documentation
void TextDisplay::notify( Subject & whoNotified ) {
    size_t r = whoNotified.getInfo().row;
    size_t c = whoNotified.getInfo().col;
    // we check for a discrepancy between the state of Cell (r,c) and its state in theDisplay
    // if they are different, we know that Cell's Info has the updated state, so we change accordingly
    if (theDisplay[r][c] == ALIVE && whoNotified.getInfo().state == State::Dead) {
        theDisplay[r][c] = DEAD;
    } else if (theDisplay[r][c] == DEAD && whoNotified.getInfo().state == State::Alive) {
        theDisplay[r][c] = ALIVE;
    }
}

// see textdisplay.h for documentation
std::string TextDisplay::getName() {
    return TD;
}

// see textdisplay.h for documentation
std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    int size = td.theDisplay.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            out << td.theDisplay[i][j];
        }
        out << std::endl;
    }
    return out;
}
