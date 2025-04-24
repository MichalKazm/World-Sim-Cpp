#include "Antelope.h"
#include "Fox.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"
#include "World.h"

#include <iostream>
#include <ncurses.h>

#include "Grass.h"

#define ROWS    20
#define COLS    40

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
    // world->addOrganism(new Wolf(15, 15));
    // world->addOrganism(new Wolf(4, 4));
    // world->addOrganism(new Sheep(2,2));
    // world->addOrganism(new Sheep(1,4));
    // world->addOrganism(new Fox(5, 10));
    // world->addOrganism(new Turtle(1,1));
    // world->addOrganism(new Sheep(1,0));
    // world->addOrganism(new Sheep(0,1));
    // world->addOrganism(new Antelope(0,0));
    world->addOrganism(new Grass(10, 20));

    world->run();

    delete world;

    endwin();

    return 0;
}
