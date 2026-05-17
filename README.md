 Indian Flag & JS Logo
 
This is a C++ computer graphics project built using OpenGL and GLUT (OpenGL Utility Toolkit). The application renders the Indian National Flag alongside a stylized JavaScript (JS) logo. It also features interactive 2D transformations, allowing the user to translate, rotate, and scale the rendered graphics in real-time using keyboard inputs.

Features
2D Rendering: Accurately draws the Indian Flag (including the 24-spoke Ashoka Chakra) and the JS logo using basic OpenGL primitives (Quads, Triangles, Lines, Polygons).

Interactive Transformations: Real-time manipulation of the graphics:

Translation (Moving up, down, left, right)
Rotation (Clockwise and Counter-Clockwise)
Scaling (Zooming in and out)

Responsive Window: The viewport automatically recenters and adjusts when the window is resized.

Controls
You can control the graphics using the following keyboard inputs:

 Key/Letters            Action
W / Up Arrow           Move Up
S / Down Arrow         Move Down
A / Left Arrow         Move Left
D / Right Arrow        Move Right
Q                      Rotate Counter-Clockwise
E                      Rotate Clockwise
R                      Zoom In (Scale Up)
F                      Zoom Out (Scale Down)
0                      Reset all transformations to default
ESC                    Exit the application


Prerequisites:

To compile and run this project, you need a C++ compiler and the OpenGL/GLUT libraries installed on your system.
1. Linux (Ubuntu/Debian)
Install the required tools and FreeGLUT development packages using the terminal:

sudo apt-get update
sudo apt-get install build-essential freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev

2. Windows
Using MinGW (GCC): You need to download and install FreeGLUT for MinGW. Place the include, lib, and bin (freeglut.dll) files in your MinGW installation folders.

Using Visual Studio: You can set up a C++ Empty Project and install FreeGLUT via the NuGet Package Manager (Project > Manage NuGet Packages... -> search for freeglut).

3. macOS
macOS comes with OpenGL and GLUT frameworks pre-installed, though they are deprecated in newer versions. You will need Xcode command-line tools:
xcode-select --install

Compilation & Execution
Save the provided C++ code into a file named main.cpp. Then, use your terminal or command prompt to compile and run the project based on your operating system.

Linux
Compile the code:
g++ main.cpp -lGL -lGLU -lglut -o graphics_app

Run the executable:
./graphics_app

Windows (MinGW)
Compile the code:

g++ main.cpp -o graphics_app.exe -lfreeglut -lglu32 -lopengl32

Run the executable:

graphics_app.exe

macOS:
Compile the code using Apple's frameworks:

g++ main.cpp -framework OpenGL -framework GLUT -Wno-deprecated -o graphics_app

Run the executable:

./graphics_app

Technical Details
Coordinate System: The application uses a custom Orthographic 2D projection gluOrtho2D(-1000, 1000, -1000, 1000).

Transformations Order: The matrix operations are applied in the order of Translation -> Rotation -> Scaling to ensure the objects rotate and scale around their center points.
