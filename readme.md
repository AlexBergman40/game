# C++ Chess Engine (In Progress)

This project is an **incomplete** C++ chess engine built using SDL2 for rendering. It was coauthored by Justus Jones and Alex Bergman, and serves as a showcase of our combined efforts in game development, memory management, and implementing an algorithm for generating chess moves. The project has helped us gain significant experience, although it is still a work in progress with some planned features yet to be implemented.

## Project Structure

- **assets/**: Contains game assets like images or textures
- **include/**: Header files for the project
- **lib/**: External libraries for SDL2 or other dependencies
- **physicstest/**: Folder for testing the physics engine or movement mechanics
- **boardrep.cpp**: Handles the board representation
- **boardrep.hpp**: Header for board representation
- **game.cpp**: Manages the overall game flow and player turns
- **game.hpp**: Header for game flow
- **gameobject.cpp**: Handles rendering of game objects like chess pieces
- **gameobject.hpp**: Header for game objects
- **generatePossibleMoves.cpp**: Algorithm to calculate all legal chess moves
- **generatePossibleMoves.hpp**: Header for move generation logic
- **main.cpp**: Main entry point of the game, initializes SDL2 and runs the game loop
- **Makefile**: Build configuration for compiling the project
- **map.cpp**: Map or board layout implementation
- **map.hpp**: Header for map or board layout
- **possibleMoves.cpp**: Additional file for move generation or legal move validation
- **texture.cpp**: Handles loading textures for game rendering
- **texture.hpp**: Header for texture loading


## Features

- **Chess Logic**: Implements the core rules of chess, including move legality, turn-based play, and basic game flow management.
- **Move Generation Algorithm**: Includes a custom algorithm that calculates all possible moves for each piece, ensuring only legal moves are allowed.
- **Rendering with SDL2**: Uses SDL2 to render the chessboard, pieces, and game interactions. SDL2 is also used for handling player input and rendering smooth animations.
- **Memory Management**: Implements efficient memory handling for game objects and game state, ensuring smooth performance during gameplay.
- **Extensive Documentation**: The code includes comments and documentation to explain the purpose and functionality of each part, making the project easy to understand and contribute to.

## Technologies

This project leverages the following technologies:

- **C++**: The core programming language used for the chess engine.
- **SDL2**: The library used for rendering the chessboard and handling user input.
- **Makefile**: Automates the build process, allowing easy compilation and linking of project files.
- **Object-Oriented Design**: The project follows OOP principles for code organization, ensuring modularity and maintainability.

## Prerequisites

- A C++ compiler (e.g., GCC, Clang)
- SDL2 development libraries
- Make (for compiling with the provided Makefile)

## Setup and Compilation

1. Clone the repository:
    ```bash
    git clone https://github.com/AlexBergman40/game.git
    ```

2. Install SDL2 development libraries:
    - On Ubuntu:
      ```bash
      sudo apt-get install libsdl2-dev
      ```
    - On macOS:
      ```bash
      brew install sdl2
      ```
    - On Windows, download SDL2 from the [SDL website](https://www.libsdl.org/) and follow their setup instructions.

3. Build the project using the Makefile:
    ```bash
    make
    ```

4. Run the chess engine:
    ```bash
    ./chess-engine
    ```

## Learning Experience

This project has provided valuable learning opportunities in several areas:

- **Game Development**: We gained experience in game architecture, including rendering, input handling, and game state management.
- **Algorithmic Thinking**: The implementation of a move generation algorithm challenged us to think deeply about efficient ways to calculate legal chess moves.
- **Memory Management**: Managing the memory of game objects in a performant manner was crucial for ensuring the engine runs smoothly.
- **Collaboration**: This project improved our teamwork and communication skills, particularly in managing shared code and balancing tasks.

## Is It AI?

Technically, this project does not include a full-fledged AI opponent. However, the **move generation algorithm** can be considered a component of AI in a chess engine, as it determines the possible actions for each piece based on the current game state. We plan to extend this logic in the future by adding decision-making capabilities to simulate an AI opponent.

For now, the project focuses on generating legal moves and validating game logic, without advanced AI features such as move evaluation or minimax search.

## Future Enhancements

- **AI Opponent**: Implementing an AI that can make intelligent decisions based on move evaluations and strategies.
- **Multiplayer**: Adding online multiplayer functionality using network protocols.
- **Improved GUI**: Enhancing the graphical interface to provide better feedback for moves and game state.
- **Game Completion**: Completing additional features, including check/checkmate detection and AI integration.

## Collaborators

- **Justus Jones** and **Alex Bergman** We both contributed equally to the development of this project, sharing responsibility for the game logic, move generation, rendering, and overall functionality.

### License

This project is licensed under the ISC License:

Copyright (c) 2024, Justus Jones and Alex Bergman

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

---

Made by [Justus Jones](https://github.com/Jorstors) and [Alex Bergman](https://github.com/AlexBergman40)
