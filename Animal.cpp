#include "Plant.h"
#include "Animal.h"
#include "World.h"
#include "Antelope.h"

#include <cstdlib>
#include <typeinfo>

Animal::Animal(int strength, int initiative, int y, int x, char symbol)
    : Organism(strength, initiative, y, x, symbol) {}
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

        if (success) {
            world->addLog(getName() + ": Reproduce with " + other->getName());
        }
    }
    else {
        world->addLog(getName() + ": Attacked " + other->getName());

        if (dynamic_cast<Antelope*>(other)) {
            y = other->getY();
            x = other->getX();
        }
        if (!other->didDeflectAttack(this)) {
            y = other->getY();
            x = other->getX();

            if (strength >= other->getStrength()) {
                other->dies();
            }
            else {
                dies();
            }
        }
    }
}
void Animal::action() {
     int newX = x;
     int newY = y;

     // Count available directions
     int available = 0;

     if (y > 0) {
         available++;
     }
     if (y < world->getRows() - 1) {
         available++;
     }
     if (x > 0) {
         available++;
     }
     if (x < world->getCols() - 1) {
         available++;
     }

     // Move in a random available direction
     int chosenMove = 4;

     if (available != 0) {
         chosenMove = rand() % available;
     }

     // Move up
     if (y > 0) {
         if (chosenMove == 0) {
             newY = y - 1;
         }

         chosenMove--;
     }
     // Move down
     if (y < world->getRows() - 1) {
         if (chosenMove == 0) {
             newY = y + 1;
         }

         chosenMove--;
     }

     // Move left
     if (x > 0) {
         if (chosenMove == 0) {
             newX = x - 1;
         }

         chosenMove--;
     }
     // Move right
     if (x < world->getCols() - 1) {
         if (chosenMove == 0) {
             newX = x + 1;
         }

         chosenMove--;
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

