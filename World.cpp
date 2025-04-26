#include "World.h"
#include "Human.h"

#include <curses.h>
#include <vector>
#include <string>

World::World(int rows, int cols, int logRows, WINDOW* gameWindow, WINDOW* logWindow)
    : rows(rows), cols(cols), logRows(logRows), turn(1), gameWindow(gameWindow), logWindow(logWindow), human(nullptr) {
    logs.push_back("-- Turn 0 --");
}
int World::getRows() const {
    return rows;
}
int World::getCols() const {
    return cols;
}
WINDOW *World::getGameWindow() const {
    return gameWindow;
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
        addLog(organism->getName() + ": Was created");
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
void World::addLog(std::string message) {
    logs.push_back(message);
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
void World::printGame() const {
    werase(gameWindow);

    box(gameWindow, 0, 0);

    for (Organism* organism : order) {
        if (!organism->isDead()) {
            if (dynamic_cast<Human*>(organism)) {
                if (human->getAbilityTimer() > 0) {
                    wattron(gameWindow, COLOR_PAIR(4));
                }
                else {
                    wattron(gameWindow, COLOR_PAIR(3));
                }
            }
            else if (dynamic_cast<Animal*>(organism)) {
                wattron(gameWindow, COLOR_PAIR(1));
            }
            else {
                wattron(gameWindow, COLOR_PAIR(2));
            }

            organism->print();

            wattroff(gameWindow, COLOR_PAIR(1));
            wattroff(gameWindow, COLOR_PAIR(2));
            wattroff(gameWindow, COLOR_PAIR(3));
            wattroff(gameWindow, COLOR_PAIR(4));
        }
    }

    wrefresh(gameWindow);
}
void World::printLogs(size_t offset) const {
    werase(logWindow);

    box(logWindow, 0, 0);

    int printRow = 1;

    if (logs.size() < logRows) {
        for (std::string log : logs) {
            mvwprintw(logWindow, printRow, 1, "%s", log.c_str());
            printRow++;
        }
    }
    else {
        for (size_t i = logs.size() - offset - logRows; printRow <= logRows; i++, printRow++) {
            mvwprintw(logWindow, printRow, 1, "%s", logs[i].c_str());
        }
    }

    wrefresh(logWindow);
}
void World::takeTurn() {
    sortOrder();

    // Number of organisms before the turn
    size_t n = order.size();

    addLog("-- Turn " + std::to_string(turn) + " --");

    // Only organisms that are alive and created before the turn will take action
    for (size_t i = 0; i < n; i++) {
        if (!order[i]->isDead()) {
            order[i]->action();
        }
    }
    removeDead();
    printGame();
    turn++;
}
void World::run() {
    printGame();
    printLogs(0);

    int offset = 0;

    int key;
    while (key = getch()) {
        if (human != nullptr) {
            human->setNextMove(' ');
        }
        switch (key) {
            case ' ':
                takeTurn();
                offset = 0;
                break;
            case KEY_UP:
                if (human != nullptr) {
                    human->setNextMove(KEY_UP);
                    takeTurn();
                    offset = 0;
                }
                break;
            case KEY_DOWN:
                if (human != nullptr) {
                    human->setNextMove(KEY_DOWN);
                    takeTurn();
                    offset = 0;
                }
                break;
            case KEY_LEFT:
                if (human != nullptr) {
                    human->setNextMove(KEY_LEFT);
                    takeTurn();
                    offset = 0;
                }
                break;
            case KEY_RIGHT:
                if (human != nullptr) {
                    human->setNextMove(KEY_RIGHT);
                    takeTurn();
                    offset = 0;
                }
                break;
            case 'f':
                if ((human != nullptr) && (human->getAbilityTimer() == - 5)) {
                    human->setAbilityTimer(5);

                    wattron(gameWindow, COLOR_PAIR(4));
                    human->print();
                    wattroff(gameWindow, COLOR_PAIR(4));

                    wrefresh(gameWindow);
                }
                break;
            case 'w':
                if (offset < logs.size() - logRows - 1) {
                    offset++;
                }
                break;
            case 's':
                if (offset > 0) {
                    offset--;
                }
                break;
            case 'q':
                return;
        }

        printLogs(offset);
    }
}
World::~World() {
    for (Organism* organism : order) {
        delete organism;
    }

    if (gameWindow != nullptr) {
        delwin(gameWindow);
        gameWindow = nullptr;
    }
    if (logWindow != nullptr) {
        delwin(logWindow);
        logWindow = nullptr;
    }
}



