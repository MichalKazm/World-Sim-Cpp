#include "World.h"
#include "Human.h"
#include "Antelope.h"
#include "Dandelion.h"
#include "DeadlyNightshade.h"
#include "Fox.h"
#include "Grass.h"
#include "Guarana.h"
#include "Hogweed.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"

#include <curses.h>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>

World::World(int rows, int cols, int logRows, int logCols, WINDOW* gameWindow, WINDOW* logWindow)
    : rows(rows), cols(cols), logRows(logRows), logCols(logCols), turn(1), gameWindow(gameWindow), logWindow(logWindow), human(nullptr) {
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
void World::addLog(const std::string& message) {
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
void World::save() {
    FILE* saveFile = fopen("save.txt", "w");

    if (!saveFile) {
        addLog("ERROR: Cannot save the game!");
        return;
    }

    fprintf(saveFile, "WORLD:\n\n");
    fprintf(saveFile, "Rows: %d\n", rows);
    fprintf(saveFile, "Columns: %d\n", cols);
    fprintf(saveFile, "Log Rows: %d\n", logRows);
    fprintf(saveFile, "Log Columns: %d\n", logCols);
    fprintf(saveFile, "Turn: %d\n", turn);

    fprintf(saveFile, "\nORGANISM:\n\n");
    for (Organism* organism : order) {
        fprintf(saveFile, "%s: Age - %d, Strength - %d\n", organism->getName().c_str(), organism->getAge(), organism->getStrength());
    }

    fprintf(saveFile, "\nLOGS:\n\n");
    for (const std::string& log : logs) {
        fprintf(saveFile, "%s\n", log.c_str());
    }

    if (human != nullptr) {
        fprintf(saveFile, "\nHUMAN:\n\n");
        fprintf(saveFile, "Ability timer: %d\n", human->getAbilityTimer());
    }

    fclose(saveFile);
}
void World::load() {
    FILE* saveFile = fopen("save.txt", "r");

    if (!saveFile) {
        addLog("ERROR: Cannot load the game!");
        return;
    }

    char line[256];

    fgets(line, sizeof(line), saveFile);    // WORLD:\n
    fgets(line, sizeof(line), saveFile);    // \n

    fscanf(saveFile, "Rows: %d\n", &rows);
    fscanf(saveFile, "Columns: %d\n", &cols);
    fscanf(saveFile, "Log Rows: %d\n", &logRows);
    fscanf(saveFile, "Log Columns: %d\n", &logCols);
    fscanf(saveFile, "Turn: %d\n", &turn);

    // Clear windows
    if (gameWindow != nullptr) {
        delwin(gameWindow);
        gameWindow = nullptr;
    }
    if (logWindow != nullptr) {
        delwin(logWindow);
        logWindow = nullptr;
    }

    // Create windows
    gameWindow = newwin(rows + 2, cols + 2, 0, 0);
    logWindow = newwin(logRows + 2, logCols + 2, rows + 2 + 3, 0);
    refresh();

    fgets(line, sizeof(line), saveFile);    // ORGANISM:\n
    fgets(line, sizeof(line), saveFile);    // \n

    // Clear order vector
    for (Organism* organism : order) {
        delete organism;
    }
    order.clear();

    human = nullptr;

    // Read organisms
    while (fgets(line, sizeof(line), saveFile)) {
        if (strcmp(line, "\n") == 0) {
            break;
        }

        char name[30];
        int y, x, age, strength;

        sscanf(line, "%29[^(](%d, %d): Age - %d, Strength - %d)", name, &y, &x, &age, &strength);

        // Remove space from name
        name[strlen(name) - 1] = '\0';

        Organism* newOrganism = nullptr;

        if (strcmp(name, "Antelope") == 0) {
            newOrganism = new Antelope(y, x);
        }
        else if (strcmp(name, "Dandelion") == 0) {
            newOrganism = new Dandelion(y, x);
        }
        else if (strcmp(name, "Deadly Nightshade") == 0) {
            newOrganism = new DeadlyNightshade(y, x);
        }
        else if (strcmp(name, "Fox") == 0) {
            newOrganism = new Fox(y, x);
        }
        else if (strcmp(name, "Grass") == 0) {
            newOrganism = new Grass(y, x);
        }
        else if (strcmp(name, "Guarana") == 0) {
            newOrganism = new Guarana(y, x);
        }
        else if (strcmp(name, "Hogweed") == 0) {
            newOrganism = new Hogweed(y, x);
        }
        else if (strcmp(name, "Human") == 0) {
            newOrganism = new Human(y, x);
        }
        else if (strcmp(name, "Sheep") == 0) {
            newOrganism = new Sheep(y, x);
        }
        else if (strcmp(name, "Turtle") == 0) {
            newOrganism = new Turtle(y, x);
        }
        else if (strcmp(name, "Wolf") == 0) {
            newOrganism = new Wolf(y, x);
        }

        if (newOrganism != nullptr) {
            newOrganism->setAge(age);
            newOrganism->setStrength(strength);

            addOrganism(newOrganism);
        }
    }

    fgets(line, sizeof(line), saveFile);    // LOGS:\n
    fgets(line, sizeof(line), saveFile);    // \n

    logs.clear();

    // Read logs
    while (fgets(line, sizeof(line), saveFile)) {
        if (strcmp(line, "\n") == 0) {
            break;
        }

        // Remove new line character
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }

        addLog(line);
    }

    if (human != nullptr) {
        int abilityTimer;
        fscanf(saveFile, "\nHUMAN:\n\n");
        fscanf(saveFile, "Ability timer: %d\n", &abilityTimer);
        human->setAbilityTimer(abilityTimer);
    }

    fclose(saveFile);

    printGame();
    printLogs(0);
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
                if (offset < logs.size() - logRows) {
                    offset++;
                }
                break;
            case 's':
                if (offset > 0) {
                    offset--;
                }
                break;
            case 'k':
                save();
                break;
            case 'l':
                load();
                offset = 0;
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



