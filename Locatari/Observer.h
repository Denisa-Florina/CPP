#pragma once
#include <vector>
#include <algorithm>

using std::vector;

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
    vector<Observer*> observers;
protected:
    void notify() {
        for (auto observer : observers) {
            observer->update();
        }
    }
public:
    void addObserver(Observer* o) {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }
};