#include "Human.h"
#include "World.h"
#include "Plant.h"
#include "Antelope.h"

#include <curses.h>
#include <cstdlib>

Human::Human(int y, int x)
    : Animal(5, 4, y, x, '@') {
    nextMove = ' ';
    abilityTimer = -5;
}
int Human::getAbilityTimer() const {
    return abilityTimer;
}
void Human::setAbilityTimer(int abilityTimer) {
    this->abilityTimer = abilityTimer;
}
void Human::setNextMove(int nextMove) {
    this->nextMove = nextMove;
}
std::string Human::getName() const {
    return "Human (" + std::to_string(y) + ", " + std::to_string(x) + ")";
}
Organism *Human::createNew(int y, int x) {
    return nullptr;
}
void Human::collision(Organism *other) {
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
void Human::action() {
    int newX = x;
    int newY = y;
    bool moved = false;
    bool doubleMove = false;

    // First 3 turns when ability is active
    if (abilityTimer > 2) {
        doubleMove = true;
    }
    else if (abilityTimer > 0) {
        // Last 2 turns when ability is active
        if (rand() % 2 == 0) {
            doubleMove = true;
        }
    }

    if (doubleMove) {
        switch (nextMove) {
            case KEY_UP:
                if (y > 1) {
                    newY = y - 2;
                    moved = true;
                }
                break;
            case KEY_DOWN:
                if (y < world->getRows() - 2) {
                    newY = y + 2;
                    moved = true;
                }
                break;
            case KEY_LEFT:
                if (x > 1) {
                    newX = x - 2;
                    moved = true;
                }
                break;
            case KEY_RIGHT:
                if (x < world->getCols() - 2) {
                    newX = x + 2;
                    moved = true;
                }
                break;
        }
    }
    else {
        switch (nextMove) {
            case KEY_UP:
                if (y > 0) {
                    newY = y - 1;
                    moved = true;
                }
                break;
            case KEY_DOWN:
                if (y < world->getRows() - 1) {
                    newY = y + 1;
                    moved = true;
                }
                break;
            case KEY_LEFT:
                if (x > 0) {
                    newX = x - 1;
                    moved = true;
                }
                break;
            case KEY_RIGHT:
                if (x < world->getCols() - 1) {
                    newX = x + 1;
                    moved = true;
                }
                break;
        }
    }

    if (moved) {
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

    if (abilityTimer > -5) {
        abilityTimer--;
    }
    age++;
}
