#include "World.h"
#include "Antelope.h"

#include <cstdlib>

Antelope::Antelope(int y, int x)
    : Animal(4, 4, y, x, 'a') {}
Organism *Antelope::createNew(int y, int x) {
    return new Antelope(y, x);
}
bool Antelope::didDeflectAttack(Organism *attacker) {
    // 50% chance
    if (rand() % 2 == 0) {
        bool success = false;
        if (y > 0) {
            if (world->getOrganism(y - 1, x) == nullptr) {
                y--;
                success = true;
            }
        }
        if (y < world->getRows() - 1) {
            if ((!success) && (world->getOrganism(y + 1, x) == nullptr)) {
                y++;
                success = true;
            }
        }
        if (x > 0) {
            if ((!success) && (world->getOrganism(y, x - 1) == nullptr)) {
                x--;
                success = true;
            }
        }
        if (x < world->getCols() - 1) {
            if ((!success) && (world->getOrganism(y, x + 1) == nullptr)) {
                x++;
                success = true;
            }
        }

        if (success) {
            return true;
        }
    }

    return false;
}
void Antelope::action() {
    int newX = x;
    int newY = y;

    // Count available directions
    int available = 0;

    if (y > 1) {
        available++;
    }
    if (y < world->getRows() - 2) {
        available++;
    }
    if (x > 1) {
        available++;
    }
    if (x < world->getCols() - 2) {
        available++;
    }

    // Move in a random available direction
    int chosenMove = 4;

    if (available != 0) {
        chosenMove = rand() % available;
    }

    // Move up
    if (y > 1) {
        if (chosenMove == 0) {
            newY = y - 2;
        }

        chosenMove--;
    }
    // Move down
    if (y < world->getRows() - 2) {
        if (chosenMove == 0) {
            newY = y + 2;
        }

        chosenMove--;
    }

    // Move left
    if (x > 1) {
        if (chosenMove == 0) {
            newX = x - 2;
        }

        chosenMove--;
    }
    // Move right
    if (x < world->getCols() - 2) {
        if (chosenMove == 0) {
            newX = x + 2;
        }

        chosenMove--;
    }

    if (chosenMove < 0) {
        Organism *other = world->getOrganism(newY, newX);

        if (other == nullptr) {
            y = newY;
            x = newX;
        } else {
            collision(other);
        }
    }

    age++;
}


