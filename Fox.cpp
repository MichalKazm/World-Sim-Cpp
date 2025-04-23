#include "Fox.h"

#include <cstdlib>

#include "World.h"

Fox::Fox(int y, int x)
    : Animal(3, 7, y, x, 'f') {}
Organism *Fox::createNew(int y, int x) {
    return new Fox(y, x);
}
void Fox::action() {
    int newX = x;
    int newY = y;

    Organism* other = nullptr;

    // Count available directions
    int available = 0;

    if (y > 0) {
        other = world->getOrganism(y - 1, x);
        if ((other == nullptr) || (strength >= other->getStrength())) {
            available++;
        }
        other = nullptr;
    }
    if (y < world->getRows() - 1) {
        other = world->getOrganism(y + 1, x);
        if ((other == nullptr) || (strength >= other->getStrength())) {
            available++;
        }
        other = nullptr;
    }
    if (x > 0) {
        other = world->getOrganism(y, x - 1);
        if ((other == nullptr) || (strength >= other->getStrength())) {
            available++;
        }
        other = nullptr;
    }
    if (x < world->getCols() - 1) {
        other = world->getOrganism(y, x + 1);
        if ((other == nullptr) || (strength >= other->getStrength())) {
            available++;
        }
        other = nullptr;
    }

    // Move in a random available direction
    int chosenMove = 4;

    if (available != 0) {
        chosenMove = rand() % available;
    }

    // Move up
    if (y > 0) {
        other = world->getOrganism(y - 1, x);

        if ((other == nullptr) || (strength >= other->getStrength())) {
            if (chosenMove == 0) {
                newY = y - 1;
            }

            chosenMove--;
        }
        other = nullptr;
    }
    // Move down
    if (y < world->getRows() - 1) {
        other = world->getOrganism(y + 1, x);

        if ((other == nullptr) || (strength >= other->getStrength())) {
            if (chosenMove == 0) {
                newY = y + 1;
            }

            chosenMove--;
        }
        other = nullptr;
    }
    // Move left
    if (x > 0) {
        other = world->getOrganism(y, x - 1);

        if ((other == nullptr) || (strength >= other->getStrength())) {
            if (chosenMove == 0) {
                newX = x -1;
            }

            chosenMove--;
        }
        other = nullptr;
    }
    // Move right
    if (x < world->getCols() - 1) {
        other = world->getOrganism(y, x + 1);

        if ((other == nullptr) || (strength >= other->getStrength())) {
            if (chosenMove == 0) {
                newX = x + 1;
            }

            chosenMove--;
        }
        other = nullptr;
    }

    if (chosenMove < 0) {
        other = world->getOrganism(newY, newX);

        if (other == nullptr) {
            y = newY;
            x = newX;
        }
        else {
            collision(other);
        }
    }

    age++;
}