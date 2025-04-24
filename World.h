#ifndef WORLD_H
#define WORLD_H
#include "Organism.h"

#include <curses.h>
#include <vector>

class World {
private:
    int rows, cols;
    std::vector<Organism*> order;
    WINDOW* window;
public:
    World(int rows, int cols, WINDOW* window);

    int getRows() const;
    int getCols() const;
    WINDOW* getWindow() const;

    bool addOrganism(Organism* organism);
    Organism* getOrganism(int y, int x) const;

    void removeDead();
    void sortOrder();
    void print() const;
    void takeTurn();
    void run();

    ~World();
};

#endif
