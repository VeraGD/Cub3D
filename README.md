# 🕹️ Cub3D (with Bonus)

> **Cub3D** is a 3D graphical project inspired by the legendary Wolfenstein 3D, developed as a group project for the 42 School curriculum. Using the MiniLibX graphical library, the goal is to render a realistic 3D perspective using **Raycasting** techniques based on a 2D map layout.

## 🙏 Acknowledgments
A special thank you to my wonderful partner, narrospi, with whom I built and completed this project. Collaboration, pair programming, and shared problem-solving made this achievement possible!

## 🎯 About the Project
Cub3D challenges students to dive into mathematical rendering, computer graphics, and memory management in C. The program reads a custom .cub scene description file containing the map layout, wall texture paths, and floor/ceiling colors, and then opens an interactive window where the player can navigate the maze.

#### Key Features:
- **Raycasting Engine**: Casts rays from the player's viewpoint across the screen, calculating wall distances and eliminating fisheye distortion to project a 3D perspective.

- **Textured Walls**: Renders distinct wall textures depending on the orientation (North, South, East, West) where the ray hits.

- **Smooth Movement & Rotation**: Handles keyboard events for fluid player translation (WASD or arrow keys) and mouse/key rotation.

- **Map Parsing & Validation**: Thoroughly parses configuration files, validates map closure (ensuring players cannot escape the boundaries), and checks for duplicate or invalid elements.

## 🌟 Bonus Features:
- **Mini-map**: Displays a real-time overhead map tracking the player's position and orientation.

- **Mouse Look**: Allows smooth camera rotation by moving the mouse across the screen.

- **Sprite Rendering / Animations**: Adds animated objects or enemies within the 3D world.


## 🛠️ Technologies Used
- **Language**: C

- **Graphics Library**: MLX42 by Codam

- **Mathematical Concepts**: Trigonometry (sine, cosine, tangents), vectors, and DDA (Digital Differential Analysis) algorithm for raycasting.

## 🚀 Getting Started
#### Prerequisites
- A UNIX-based operating system (Linux or macOS)

- gcc compiler

- make

- CMake and GLFW library (required for MLX42)

#### Compilation & Execution
1. Clone the repository:

   ```C
   git clone [https://github.com/VeraGD/Cub3D.git](https://github.com/VeraGD/Cub3D.git)
   cd cub3d
    ```


2. Compile the project using the Makefile (the bonus rule compiles the extended features):

    ```C
    make
    make bonus
    ```

3. Run the executable with a valid map file:

    ```C
    ./cub3d maps/valid_map.cub
    ```

## 🧹 Cleaning Up
To remove compiled object files:

  ```C
  make clean
  ```
To remove object files and the binary executable:
  ```C
  make fclean
  ```
To recompile from scratch:
  ```C
  make re
  ```
