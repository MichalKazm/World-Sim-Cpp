#include "World.h"

#include <curses.h>
#include <vector>

World::World(int rows, int cols, WINDOW* window)
    : rows(rows), cols(cols), window(window) {}
int World::getRows() const {
    return rows;
}
int World::getCols() const {
    return cols;
}
WINDOW *World::getWindow() const {
    return window;
}
bool World::addOrganism(Organism* organism) {
    if ((organism->getX() < cols) && (organism->getY() < rows) && (organism->getX() >= 0) && (organism->getY() >= 0)) {
        organism->setWorld(this);
        order.push_back(organism);
        return true;
    }
    else {
        delete organism;
        return false;
    }
}
Organism *World::getOrganism(int y, int x) const{
    for (Organism* organism : order) {
        if ((organism->getY() == y) && (organism->getX() == x)) {
            return organism;
        }
    }

    return nullptr;
}
void World::removeDead() {
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i]->isDead()) {
            delete order[i];
            order.erase(order.begin() + i);
            i--;
        }
    }
}
void World::sortOrder() {
    for (size_t i = 0; i < order.size() - 1; i++) {
        for (size_t j = i + 1; j < order.size(); j++) {
            if (order[j]->getInitiative() > order[i]->getInitiative()) {
                std::swap(order[j], order[i]);
            }
            else if ((order[j]->getInitiative() == order[i]->getInitiative()) && (order[j]->getAge() > order[i]->getAge())) {
                std::swap(order[j], order[i]);
            }
        }
    }
}
void World::print() const {
    werase(window);

    box(window, 0, 0);

    for (Organism* organism : order) {
        if (!organism->isDead()) {
            organism->print();
        }
    }

    wrefresh(window);
}
void World::takeTurn() {
    sortOrder();

    // Number of organisms before the turn
    size_t n = order.size();

    // Only organisms that are alive and created before the turn will take action
    for (size_t i = 0; i < n; i++) {
        if (!order[i]->isDead()) {
            order[i]->action();
        }
    }
    removeDead();
    print();
}
void World::run() {
    print();

    char key;
    while (key = wgetch(window)) {
        if (key == ' ') {
            takeTurn();
        }

        if (key == 'q') {
            break;
        }
    }
}
World::~World() {
    for (Organism* organism : order) {
        delete organism;
    }

    delwin(window);
}


