# Treasure Maze (C++ Console Game)

## Overview

**Treasure Maze** is a console-based adventure game developed in **C++**. The player navigates through a randomly generated maze, collects treasures to increase score, avoids walls to preserve lives, and reaches the exit to complete levels. The game supports multiple difficulty levels, colored console output, and emoji-based rendering for an engaging text-mode experience.

This project demonstrates practical application of **Data Structures & Algorithms (DFS)**, **dynamic memory management**, and **console handling in Windows**.

---

## Key Features

* Random maze generation using **Depth First Search (DFS)**
* Three difficulty levels: Easy, Medium, Hard
* Multi-level gameplay
* Scoring system with different treasure values
* Life system (wall collision penalty)
* ANSI color codes and UTF-8 emojis for visual clarity
* Replay option without restarting the program

---

## Game Symbols

| Symbol | Meaning | Description               |
| ------ | ------- | ------------------------- |
| 🧍     | Player  | User-controlled character |
| 🟦     | Wall    | Collision reduces life    |
| 💰     | Gold    | +10 score                 |
| 🪙     | Silver  | +5 score                  |
| 💎     | Diamond | +20 score                 |
| 🚪     | Exit    | Completes the level       |
| ⬜      | Path    | Free space                |

---

## Controls

| Key | Action     |
| --- | ---------- |
| W   | Move Up    |
| S   | Move Down  |
| A   | Move Left  |
| D   | Move Right |

---

## Difficulty Levels

| Difficulty | Maze Size | Levels |
| ---------- | --------- | ------ |
| Easy       | 15 x 15   | 1      |
| Medium     | 20 x 20   | 2      |
| Hard       | 25 x 25   | 3      |

---

## Game Rules

* Player starts with **3 lives**
* Hitting a wall reduces **1 life**
* Collect treasures to increase score
* Reach the exit 🚪 to finish the level
* Game ends when lives reach **0**

---

## Technical Details

* **Language:** C++
* **Platform:** Windows (uses `windows.h`)
* **Concepts Used:**

  * Depth First Search (DFS)
  * Dynamic 2D arrays
  * Random number generation
  * Console encoding (UTF-8)
  * ANSI escape sequences for colors

---

## How Maze Generation Works

* The maze is initialized with walls
* DFS algorithm carves random paths
* Entry point is `(1,1)`
* Exit is placed at bottom-right
* Treasures are randomly distributed on valid paths

---

## How to Compile and Run

```bash
g++ main.cpp -o TreasureMaze
TreasureMaze
```

> Ensure your terminal supports **UTF-8** and **ANSI colors**.

---

## Learning Outcomes

* Understanding DFS in real-world applications
* Handling dynamic memory safely in C++
* Designing game logic and state management
* Improving console UI without graphics libraries

---


## Author

**Rafia Fayyaz**
Department of Computer Science
Govt. Graduate College for Women, Gulberg, Lahore

---


