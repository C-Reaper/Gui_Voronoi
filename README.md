# Project README

## Overview
This project is a C-based application that generates Voronoi diagrams in various environments. It includes implementations for Linux, Windows, Wine, and WebAssembly.

## Features
- Generates Voronoi diagrams.
- Supports multiple build environments: Linux, Windows, Wine, and WebAssembly.

## Project Structure
```
Gui_Voronoi/
├── build/              # .exe files produced by Main.c
├── bin/                # .so / .dll produced by *.c in libs (not present)
├── libs/               # *.c for bin (not present)
├── lib/                # librarys for my own languages (not present)
├── code/               # scripts from my custom languages for example .rex, .ll, .omml (not present)
├── data/               # Datafile for example .txt or dumped files (not present)
├── assets/             # images and sound files (not present)
├── src/                # src code
│   ├── Main.c          # Entry point
│   └── *.h             # stand alone Header-based C-files, without *.c files that implement it
├── Makefile.linux      # Linux Build configuration
├── Makefile.windows    # Windows Build configuration
├── Makefile.wine       # Wine Build configuration for Linux cross compile for windows
├── Makefile.web        # Emscripten Build configuration for Webassembly
└── README.md           # This file
└── LICENSE             # License file (not present)
└── .gitignore          # Git ignore rules (not present)
```

## Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools

## Build & Run
### Linux
1. Navigate to the project directory.
2. Build the project:
    ```sh
    make -f Makefile.linux all
    ```
3. Run the executable:
    ```sh
    make -f Makefile.linux exe
    ```

### Windows
1. Navigate to the project directory.
2. Build the project:
    ```sh
    make -f Makefile.windows all
    ```
3. Run the executable:
    ```sh
    make -f Makefile.windows exe
    ```

### Wine
1. Navigate to the project directory.
2. Build the project:
    ```sh
    make -f Makefile.wine all
    ```
3. Run the executable within Wine:
    ```sh
    WINEPREFIX=~/wine64 WINEARCH=win64 wine build/Main.exe
    ```

### WebAssembly (Emscripten)
1. Navigate to the project directory.
2. Build the project:
    ```sh
    make -f Makefile.web all
    ```
3. Serve the generated HTML file in a web browser or using `emrun`:
    ```sh
    emrun --no_browser --port 8080 build/index.html
    ```

These instructions cover building and running the project for different platforms using the provided Makefiles.