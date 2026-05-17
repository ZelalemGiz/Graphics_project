OpenGL Graphics — Indian Flag & JS Logo

Descriptin

This is a small C++ OpenGL project (using GLUT) that renders the Indian National Flag alongside a stylized JavaScript (JS) logo. The program supports interactive 2D transformations so you can translate, rotate, and scale the scene in real time with the keyboard.

Features

- 2D Rendering: Draws the Indian Flag (including the 24-spoke Ashoka Chakra) and a JS logo using basic OpenGL primitives (quads, triangles, lines, polygons).
- Interactive Transformations: Translate, rotate, and scale the scene in real time.
- Responsive Window: The viewport recenters and adjusts when the window is resized.

Controls

Use the keyboard keys below to control the scene:

- `W` or Up Arrow — Move up
- `S` or Down Arrow — Move down
- `A` or Left Arrow — Move left
- `D` or Right Arrow — Move right
- `Q` — Rotate counter-clockwise
- `E` — Rotate clockwise
- `R` — Zoom in (scale up)
- `F` — Zoom out (scale down)
- `0` — Reset all transformations to defaults
- `ESC` — Exit the application

Prerequisites

You need a C++ compiler and OpenGL/GLUT (FreeGLUT) development libraries.

Linux (Ubuntu/Debian)

Run:

```sh
sudo apt-get update
sudo apt-get install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

Windows

- MinGW/GCC: download FreeGLUT for MinGW and place the `include`, `lib`, and `bin` (freeglut.dll) files into your MinGW folders.
- Visual Studio: create a C++ project and add FreeGLUT via NuGet (Project → Manage NuGet Packages… → search for `freeglut`).

macOS

Install Xcode command-line tools (if not already installed):

```sh
xcode-select --install
```

Compilation & Execution

Save the code as `main.cpp` and compile using the commands below for your platform.

Linux

```sh
g++ main.cpp -lGL -lGLU -lglut -o graphics_app
./graphics_app
```

Windows (MinGW)

```sh
g++ main.cpp -o graphics_app.exe -lfreeglut -lglu32 -lopengl32
graphics_app.exe
```

macOS

```sh
g++ main.cpp -framework OpenGL -framework GLUT -Wno-deprecated -o graphics_app
./graphics_app
```

Technical details

- Coordinate system: uses an orthographic 2D projection `gluOrtho2D(-1000, 1000, -1000, 1000)`.
- Transform order: Translation → Rotation → Scaling (so objects rotate/scale about their center).

Notes

- This README only improves wording and formatting; no project structure or file locations were changed.