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

    int GetRows() const;
    int GetCols() const;

    void AddOrganism(Organism* organism);
    void SortOrder();
    void Print();

    ~World();
};

#endif
