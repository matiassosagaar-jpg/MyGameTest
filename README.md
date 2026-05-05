# Enemy Slayer

Simple wave-based top-down shooter built in C++.

## Controls

* **WASD** → Movement
* **Left Click** → Attack (direction based on mouse position)

> The player is represented by the larger black square.

## Gameplay

* Enemies spawn in waves
* Each wave increases the number of enemies
* Each enemy killed adds **+1 score**
* Game over when player HP reaches 0

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/MyGame
```

## Tech

* C++17
* raylib
* CMake

## Demo
https://youtu.be/VJe6SeDyxxo
