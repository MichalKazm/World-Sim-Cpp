#include "World.h"

#include <curses.h>
#include <iostream>
#include <vector>

World::World(int rows, int cols, WINDOW* window)
    : rows(rows), cols(cols), window(window) {}
int World::GetCols() const {
    return cols;
}
int World::GetRows() const {
    return rows;
}
void World::AddOrganism(Organism* organism) {
    if ((organism->GetX() < cols) && (organism->GetY() < rows) && (organism->GetX() >= 0) && (organism->GetY() >= 0)) {
        order.push_back(organism);
    }
    else {
        delete organism;
    }
}
void World::SortOrder() {
    for (int i = 0; i < order.size() - 1; i++) {
        for (int j = i + 1; j < order.size(); j++) {
            if (order[j]->GetInitiative() > order[i]->GetInitiative()) {
                std::swap(order[j], order[i]);
            }
            else if ((order[j]->GetInitiative() == order[i]->GetInitiative()) && (order[j]->GetAge() > order[i]->GetAge())) {
                std::swap(order[j], order[i]);
            }
        }
    }
}
void World::Print() {
    werase(window);

    box(window, 0, 0);

    for (Organism* organism : order) {
        mvwprintw( window, organism->GetY() + 1, organism->GetX() + 1, "%c",organism->GetSymbol());
    }

    wrefresh(window);
}

World::~World() {
    for (int i = 0; i < order.size(); i++) {
        delete order[i];
    }

    delwin(window);
}


