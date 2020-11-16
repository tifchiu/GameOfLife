#include <iostream>
#include <string>
#include <stdexcept>
#include "grid.h"
#include "info.h"
using namespace std;

// Do not change.

int main() {
    cin.exceptions(ios::eofbit|ios::failbit);
    string cmd;
    Grid g;

    try {
        while ( std::cin >> cmd ) {
            try {
                if ( cmd == "new" ) {
                    int n;
                    std::cin >> n; 
                    g.init(n);
                } else if ( cmd == "neighbours" ) {
                    g.printCellNeighbours();
                } else if ( cmd == "init" ) {
                    try {
                        int r, c;
                        for ( std::cin >> r >> c; ; std::cin >> r >> c ) {
                            if ( r == -1 && c == -1 ) break;
                            g.turnOn(r,c);
                         } // for

                    } catch (std::invalid_argument & e) {
                        std::cerr << e.what() << std::endl;
                    } // catch
                } else if ( cmd == "step" ) {
                    g.tick();
                } else if ( cmd == "steps" ) {
                    int n;
                    std::cin >> n;
                    for ( int i = 0; i < n; ++i ) g.tick();
                } else if ( cmd == "print" ) {
                    std::cout << g;
                } // if
            } catch (std::invalid_argument & e) {
                std::cerr << e.what() << std::endl;
            }  // catch
        } // while
    } catch (ios::failure &) {}  // Any I/O failure quits
} // main
