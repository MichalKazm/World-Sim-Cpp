#include "World.h"
#include "Human.h"

#include <curses.h>
#include <vector>

World::World(int rows, int cols, WINDOW* window)
    : rows(rows), cols(cols), window(window), human(nullptr) {}
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
    bool addedHuman = false;

    // Only one human can be present in the world
    if (dynamic_cast<Human*>(organism)) {
        if (human == nullptr) {
            human = dynamic_cast<Human*>(organism);
            addedHuman = true;
        }
        else {
            delete organism;
            return false;
        }
    }

    if ((organism->getX() < cols) && (organism->getY() < rows) && (organism->getX() >= 0) && (organism->getY() >= 0)) {
        organism->setWorld(this);
        order.push_back(organism);
        return true;
    }
    else {
        if (addedHuman) {
            human = nullptr;
        }
        delete organism;
        return false;
    }
}
Organism *World::getOrganism(int y, int x) const{
    for (Organism* organism : order) {
        if ((!organism->isDead()) && (organism->getY() == y) && (organism->getX() == x)) {
            return organism;
        }
    }

    return nullptr;
}
void World::removeDead() {
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i]->isDead()) {
            if (dynamic_cast<Human*>(order[i])) {
                human = nullptr;
            }
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
            if (dynamic_cast<Human*>(organism)) {
                if (human->getAbilityTimer() > 0) {
                    wattron(window, COLOR_PAIR(4));
                }
                else {
                    wattron(window, COLOR_PAIR(3));
                }
            }
            else if (dynamic_cast<Animal*>(organism)) {
                wattron(window, COLOR_PAIR(1));
            }
            else {
                wattron(window, COLOR_PAIR(2));
            }

            organism->print();

            wattroff(window, COLOR_PAIR(1));
            wattroff(window, COLOR_PAIR(2));
            wattroff(window, COLOR_PAIR(3));
            wattroff(window, COLOR_PAIR(4));
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

    int key;
    while (key = getch()) {
        if (human != nullptr) {
            human->setNextMove(' ');
        }
        switch (key) {
            case ' ':
                takeTurn();
                break;
            case KEY_UP:
                if (human != nullptr) {
                    human->setNextMove(KEY_UP);
                    takeTurn();
                }
                break;
            case KEY_DOWN:
                if (human != nullptr) {
                    human->setNextMove(KEY_DOWN);
                    takeTurn();
                }
                break;
            case KEY_LEFT:
                if (human != nullptr) {
                    human->setNextMove(KEY_LEFT);
                    takeTurn();
                }
                break;
            case KEY_RIGHT:
                if (human != nullptr) {
                    human->setNextMove(KEY_RIGHT);
                    takeTurn();
                }
                break;
            case 'f':
                if ((human != nullptr) && (human->getAbilityTimer() == - 5)) {
                    human->setAbilityTimer(5);

                    wattron(window, COLOR_PAIR(4));
                    human->print();
                    wattroff(window, COLOR_PAIR(4));

                    wrefresh(window);
                }
                break;
            case 'q':
                return;
        }
    }
}
World::~World() {
    for (Organism* organism : order) {
        delete organism;
    }

    delwin(window);
}


