#include <iostream>
#include <ncurses.h>

#include "Animal.h"
#include "World.h"

#define ROWS    20
#define COLS    20

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
    world->addOrganism(new Animal(1,1,0,0,'w',world));
    world->addOrganism(new Animal(1,1,19,19,'e',world));
    world->addOrganism(new Animal(1,1,7,10,'t',world));

    world->run();

    delete world;

    endwin();

    return 0;
}
