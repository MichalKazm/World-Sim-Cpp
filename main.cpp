#include <iostream>
#include <ncurses.h>

#include "Animal.h"
#include "Sheep.h"
#include "Wolf.h"
#include "World.h"

#define ROWS    30
#define COLS    30

using namespace std;

void Init() {
    srand(time(nullptr));

    initscr();
    raw();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    refresh();
}

int main() {

    Init();

    WINDOW* window = newwin(ROWS + 2, COLS + 2, 0, 0);

    World* world = new World(ROWS,COLS, window);
    world->addOrganism(new Wolf(15, 15));
    // world->addOrganism(new Wolf(4, 4));
    // world->addOrganism(new Sheep(2,2));
    // world->addOrganism(new Sheep(1,4));

    world->run();

    delete world;

    endwin();

    return 0;
}
