#include "Animal.h"
#include "World.h"

#include <cstdlib>

Animal::Animal(int strength, int initiative, int x, int y, char symbol, World *world)
    : Organism(strength, initiative, x, y, symbol, world) {}
void Animal::Action() {
    int direction = -1;

    // Move in a random available direction
    while (direction < 0) {
        direction = rand() % 4;

        switch (direction) {
            // Move up
            case 0:
                if (y > 0) {
                    y--;
                }
                else {
                    direction = -1;
                }
                break;
            // Move down
            case 1:
                if (y < world->GetRows() - 1) {
                    y++;
                }
                else {
                    direction = -1;
                }
                break;
            // Move left
            case 2:
                if (x > 0) {
                    x--;
                }
                else {
                    direction = -1;
                }
                break;
            // Move right
            case 3:
                if (x < world->GetCols() - 1) {
                    x++;
                }
                else {
                    direction = -1;
                }
                break;
        }
    }

    age++;
}

