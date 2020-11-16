#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <string>
#include "info.h"

// DO NOT MODIFY THIS FILE!

class Observer;

class Subject {
    std::vector<Observer*> observers;

  public:
    void attach(Observer *o);  
    void notifyObservers();
    virtual Info getInfo() const = 0;

    // Returns a string consisting of the name of each observer, followed by a single space.
    // If there are no observers, an empty string is returned.
    std::string getObserverNames();
};

#endif
