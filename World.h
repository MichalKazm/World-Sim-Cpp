#ifndef WORLD_H
#define WORLD_H
#include "Organism.h"
#include "Human.h"

#include <curses.h>
#include <vector>
#include <string>

class World {
private:
    int rows, cols, logRows, logCols, turn;
    std::vector<Organism*> order;
    std::vector<std::string> logs;
    WINDOW* gameWindow;
    WINDOW* logWindow;
    Human* human;
public:
    World(int rows, int cols, int logRows, int logCols, WINDOW* GameWindow, WINDOW* logWindow);

    int getRows() const;
    int getCols() const;
    WINDOW* getGameWindow() const;

    bool addOrganism(Organism* organism);
    Organism* getOrganism(int y, int x) const;

    void addLog(const std::string& message);
    void removeDead();
    void sortOrder();
    void printGame() const;
    void printLogs(size_t start) const;
    void save();
    void load();
    void takeTurn();
    void run();

    ~World();
};

#endif
