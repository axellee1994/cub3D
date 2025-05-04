# Cub3D

## Description
Cub3D is a graphical 3D game project built as part of the 42 Cursus. It implements a simple raycasting engine similar to early first-person shooters (e.g., Wolfenstein 3D). The project demonstrates foundational graphics programming, player movement, collision detection, and rendering techniques using the MinilibX library.

### Main Features
- Real-time 3D rendering with raycasting
- Player movement and rotation
- Wall, floor, and ceiling textures
- Map parsing and validation
- Basic collision detection
- Simple UI elements

## Installation Instructions

### Prerequisites
- GCC (GNU Compiler Collection)
- Make
- X11 libraries (Linux) or XQuartz (macOS)
- MinilibX (included as a submodule)

### Steps
```bash
git clone https://github.com/axellee1994/42Cursus.git
cd 42Cursus/cub3d
make
```

If you are on Linux, ensure the following dependencies are installed:
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```
For macOS, install XQuartz:
```bash
brew install --cask xquartz
reboot
```

## Usage Instructions

Run the Cub3D executable with a valid map file:
```bash
./cub3d maps/example.cub
```

- Use `W`, `A`, `S`, `D` to move.
- Use left/right arrows to rotate the player.
- Press `ESC` to exit the game.

## Contribution Guidelines

We welcome contributions! To contribute:
- Fork this repository.
- Create a new branch for your feature or bugfix.
- Follow the code style used in the project (norminette for C code).
- Write clear commit messages.
- Submit a pull request with a description of your changes.

Please ensure your code passes all existing tests and does not break the build.

## License Information

This project is licensed under the BSD 2-Clause License. See the `mlx/LICENSE` file for full details.

## Contact Information

For questions or support, please contact:
*   **Author(s):** axellee1994 - [https://github.com/axellee1994](https://github.com/axellee1994)
*   **Project Link:** [https://github.com/axellee1994/cub3D](https://github.com/axellee1994/cub3D)
---

Thank you for your interest in Cub3D! Contributions, feedback, and suggestions are always welcome.
