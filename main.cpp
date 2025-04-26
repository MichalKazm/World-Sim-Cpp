#include "Human.h"
#include "DeadlyNightshade.h"
#include "Hogweed.h"
#include "Dandelion.h"
#include "Grass.h"
#include "Guarana.h"
#include "Antelope.h"
#include "Fox.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"
#include "World.h"

#include <iostream>
#include <ncurses.h>

#define ROWS        20
#define COLS        80
#define LOG_ROWS    10
#define LOG_COLS    100

void InitDisplay() {
    srand(time(nullptr));

    initscr();
    raw();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
}

void InitColor() {
    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);

    bkgd(COLOR_PAIR(0));

    clear();
    refresh();
}

int main() {
    InitDisplay();
    InitColor();

    int maxX = getmaxx(stdscr);
    int maxY = getmaxy(stdscr);

    if ((ROWS + 2 + 3 + LOG_ROWS + 2 > maxY) || (COLS + 2 > maxX) || (LOG_COLS + 2 > maxX)) {
        endwin();

        std::cout << "\nERROR: You're trying to create game bigger than your screen!\n\n";

        return 1;
    }

    WINDOW* gameWindow = newwin(ROWS + 2, COLS + 2, 0, 0);
    WINDOW* logWindow = newwin(LOG_ROWS + 2, LOG_COLS + 2, ROWS + 2 + 3, 0);

    World* world = new World(ROWS,COLS, LOG_ROWS, LOG_COLS, gameWindow, logWindow);
    // world->addOrganism(new Human(1, 1));
    world->addOrganism(new Wolf(15, 15));
    // world->addOrganism(new Wolf(4, 4));
    world->addOrganism(new Sheep(2,2));
    world->addOrganism(new Sheep(1,4));
    world->addOrganism(new Fox(5, 10));
    world->addOrganism(new Turtle(1,12));
    // world->addOrganism(new Sheep(1,0));
    // world->addOrganism(new Sheep(0,1));
    world->addOrganism(new Antelope(0,0));
    world->addOrganism(new Grass(10, 50));
    world->addOrganism(new Dandelion(19, 39));
    world->addOrganism(new Guarana(0,40));
    world->addOrganism(new DeadlyNightshade(19, 20));
    world->addOrganism(new Hogweed(19, 25));


    world->run();

    delete world;

    endwin();

    return 0;
}
