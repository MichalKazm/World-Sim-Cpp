#include "World.h"

#include <curses.h>
#include <vector>

World::World(int rows, int cols, WINDOW* window)
    : rows(rows), cols(cols), window(window) {}
int World::getCols() const {
    return cols;
}
int World::getRows() const {
    return rows;
}
WINDOW *World::getWindow() const {
    return window;
}
void World::addOrganism(Organism* organism) {
    if ((organism->getX() < cols) && (organism->getY() < rows) && (organism->getX() >= 0) && (organism->getY() >= 0)) {
        order.push_back(organism);
    }
    else {
        delete organism;
    }
}
void World::sortOrder() {
    for (int i = 0; i < order.size() - 1; i++) {
        for (int j = i + 1; j < order.size(); j++) {
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
        organism->print();
    }

    wrefresh(window);
}
void World::takeTurn() {
    sortOrder();

    for (Organism* organism : order) {
        organism->action();
    }

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


