# Nightingale Engine

Nightingale is a very simple game engine, originally made as a personal project of mine.
It utilizes a simple ECS architecture that is, admittedly, unoptimized. It has many
utilities for managing state, including an Finite State Machine class and a Pushdown Automaton
class. The Pushdown Automaton is utilized for managing game states, such as moving through
menus, levels, world maps, etc.

Nightingale uses SDL2 for its windowing and input management, OpenGL for its graphics API,
and OpenAL for a cross-platform audio backend.

## Dependencies

On Ubuntu 22.04, the following development libraries need to be installed prior to building:

```
libsdl2-dev
libsdl2-image-dev
libalut-dev
libglm-dev
libstdc++-12-dev
```

## Building

Building Nightingale is very simple:

```
mkdir build
cd build
cmake ..
make
```

After building, there is a shared object library for you to link against in your own
project. Alternatively, you can use this project as a submodule in your own project
and add it as a subdirectory in your own CMakeLists.txt

## Running Tests

After building you can run the test executable found at the top level of your build directory:

```
./NightingaleTests
```

This tests the basic utilities of the engine, and does not cover the low-level API implementations, such
as OpenGL, OpenAL, and SDL.
