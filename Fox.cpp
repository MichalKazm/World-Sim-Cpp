#include "World.h"
#include "Fox.h"
#include "Plant.h"

#include <cstdlib>

Fox::Fox(int y, int x)
    : Animal(3, 7, y, x, 'f') {}
std::string Fox::getName() const {
    return "Fox (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
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
        Organism* other = world->getOrganism(newY, newX);

        if (other == nullptr) {
            world->addLog(getName() + ": Moved to (" + std::to_string(newY) + ", " + std::to_string(newX) + ")");
            y = newY;
            x = newX;
        }
        else {
            if (dynamic_cast<Plant*>(other)) {
                world->addLog(getName() + ": Moved to (" + std::to_string(newY) + ", " + std::to_string(newX) + ")");
                y = newY;
                x = newX;
                other->collision(this);
            }
            else {
                collision(other);
            }
        }
    }

    age++;
}