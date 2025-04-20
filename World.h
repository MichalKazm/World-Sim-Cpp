#ifndef WORLD_H
#define WORLD_H
#include <curses.h>
#include <vector>

#include "Organism.h"

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

    void addOrganism(Organism* organism);
    void sortOrder();
    void print() const;
    void takeTurn();
    void run();

    ~World();
};

#endif
