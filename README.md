# World Simulator C++

Simple world simulator operating in terminal. Made in C++ using ncurses library.

# Features

- **Turn system:** The simulation operates in turns. In each turn, every organism performs an action depending on its type. The order of actions is based on the initiative and age of each organism.
- **Animals & plants:** Organisms are divided into two subgroups: animals and plants. Animals can move, fight other organisms, and reproduce with animals of the same kind, creating a new animal on an adjacent cell. Plants don't move or fight but have a 10% chance of spreading to an adjacent empty cell each turn. Other mechanics are specific to each organism.
- **Human player:** The simulation can involve a playable human character. It behaves similarly to an animal but its movement is controlled by arrow keys instead of being random. The human also possesses a special ability that can be activated before a turn.
- **Logs:** To make the simulation easy to follow even with many organisms on the map, every event that happens during a turn is recorded in the logs. Logs can be easily scrolled through, which helps spot what happened during a specific turn.
- **Colors** The simulation uses a color system to help differentiate between various organisms.
- **Saving & Loading:** The game can be easily saved to and loaded from a file.
