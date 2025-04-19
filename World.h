#ifndef WORLD_H
#define WORLD_H
#include <vector>

#include "Organism.h"

class World {
private:
    int rows, cols;
    std::vector<Organism*> order;
public:
    World(int rows, int cols);

    void AddOrganism(Organism* organism);
    void SortOrder();

    ~World();
};

#endif
