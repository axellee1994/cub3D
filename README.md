# Cub3D

## Overview
Cub3D is a 3D graphics project inspired by the classic game Wolfenstein 3D. It uses raycasting techniques to create a 3D perspective in a 2D map.

## Features
- 3D perspective rendering using raycasting
- Textured walls with different colors for each direction (North, South, East, West)
- Player movement (forward, backward, strafe left, right)
- Player rotation (look left, right)
- Minimap display
- Floor and ceiling rendering
- Basic collision detection

## Requirements
- gcc compiler
- Make
- MinilibX library

## Compilation
To compile the project, run:
make

To check for leaks, run:
make leaks

## Usage
To run the project, run:
./cub3D [map_file]


### Controls
- W: Move forward
- S: Move backward
- A: Strafe left
- D: Strafe right
- Left Arrow: Rotate camera left
- Right Arrow: Rotate camera right
- ESC: Exit the game

## Map Format
The map file should be a `.cub` file with the following format:
(STILL WORKING ON THIS)

## Optimization
- [ ] minimap/fov_lines.c
- [x] minimap/map_utils.c
- [ ] minimap/minimap.c
- [x] raycasting/angle_utils.c
- [x] raycasting/intersection_utils.c
- [ ] raycasting/intersection.c
- [x] raycasting/raycasting.c
- [x] rendering/drawing_utils.c
- [x] rendering/pixel_utils.c
- [x] rendering/rendering.c
- [x] free_and_exit.c
- [x] help.c
- [x] hooks.c
- [x] initialization.c
- [x] main.c
- [x] player.c
- [x] validation.c 

## Known Issues
- [ ] Texture files still need to be implemented
- [ ] Minimap still needs to be shortened and optimised (Consider taking out the FOV lines)
- [ ] Need to create a .cub file to test the program

## Future Improvements
- [List any planned features or improvements]

## Contributors
- [axlee]
