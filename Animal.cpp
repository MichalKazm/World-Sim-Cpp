#include "Animal.h"
#include "World.h"

#include <cstdlib>

Animal::Animal(int strength, int initiative, int y, int x, char symbol, World *world)
    : Organism(strength, initiative, y, x, symbol, world) {}
void Animal::collision(Organism *other) {
    // If two organisms are of the same type, they reproduce
    if (typeid(*this) == typeid(*other)) {
        bool success = false;
        if (world->getOrganism(y - 1, x) == nullptr) {
            success = world->addOrganism(createNew(y - 1, x));
        }
        if ((!success) && (world->getOrganism(y + 1, x) == nullptr)) {
            success = world->addOrganism(createNew(y + 1, x));
        }
        if ((!success) && (world->getOrganism(y, x - 1) == nullptr)) {
            success = world->addOrganism(createNew(y, x - 1));
        }
        if ((!success) && (world->getOrganism(y, x + 1) == nullptr)) {
            success = world->addOrganism(createNew(y, x + 1));
        }
        if ((!success) && (world->getOrganism(other->getY() + 1, other->getX()) == nullptr)) {
            success = world->addOrganism(createNew(other->getY() + 1, other->getX()));
        }
        if ((!success) && (world->getOrganism(other->getY() - 1, other->getX()) == nullptr)) {
            success = world->addOrganism(createNew(other->getY() - 1, other->getX()));
        }
        if ((!success) && (world->getOrganism(other->getY(), other->getX() + 1) == nullptr)) {
            success = world->addOrganism(createNew(other->getY(), other->getX() + 1));
        }
        if ((!success) && (world->getOrganism(other->getY(), other->getX() - 1) == nullptr)) {
            success = world->addOrganism(createNew(other->getY(), other->getX() - 1));
        }

    }
    else {
        if (strength >= other->getStrength()) {
            other->dies();
            y = other->getY();
            x = other->getX();
        }
        else {
            dies();
        }
    }
}
void Animal::action() {
    int direction = -1;
    int newX = x;
    int newY = y;

    // Move in a random available direction
    while (direction < 0) {
        direction = rand() % 4;

        switch (direction) {
            // Move up
            case 0:
                if (y > 0) {
                    newY = y - 1;
                }
                else {
                    direction = -1;
                }
                break;
            // Move down
            case 1:
                if (y < world->getRows() - 1) {
                    newY = y + 1;
                }
                else {
                    direction = -1;
                }
                break;
            // Move left
            case 2:
                if (x > 0) {
                    newX = x - 1;
                }
                else {
                    direction = -1;
                }
                break;
            // Move right
            case 3:
                if (x < world->getCols() - 1) {
                    newX = x + 1;
                }
                else {
                    direction = -1;
                }
                break;
        }
    }

    Organism* other = world->getOrganism(newY, newX);

    if (other == nullptr) {
        y = newY;
        x = newX;
    }
    else {
        collision(other);
    }

    age++;
}

