# OpenGL Graphics — 3D Waving Indian Flag & JS Logo

## Description

This is a C++ OpenGL graphics project built using GLUT (FreeGLUT).  
The application renders an animated 3D-style waving Indian National Flag together with a stylized JavaScript (JS) logo.

The project demonstrates:

- OpenGL 2D graphics rendering
- Real-time wave animation using sine functions
- Dynamic 3D lighting/shading effects
- Interactive transformations
- Keyboard event handling
- Custom geometric drawing using OpenGL primitives

---

# Features

## Animated Waving Indian Flag
- Real-time cloth-like waving animation
- Smooth sine-wave motion
- Dynamic shading for a fake 3D lighting effect

## Ashoka Chakra Rendering
- Animated Ashoka Chakra at the center of the flag
- 24 spokes rendered using OpenGL lines
- Dynamic lighting applied to the chakra

## Stylized JS Logo
- Custom JavaScript logo created using:
  - arcs
  - rectangles
  - quads

## Interactive Transformations
The entire scene can be:
- translated
- rotated
- scaled

in real time using the keyboard.

## Responsive Window
- Automatically adjusts viewport on resize
- Maintains centered rendering

---

# Controls

## Translation

| Key | Action |
|---|---|
| `U` | Move Up |
| `D` | Move Down |
| `L` | Move Left |
| `R` | Move Right |

You can also use:

| Key | Action |
|---|---|
| `↑` | Move Up |
| `↓` | Move Down |
| `←` | Move Left |
| `→` | Move Right |

---

## Rotation

| Key | Action |
|---|---|
| `Q` | Rotate Counter-Clockwise |
| `E` | Rotate Clockwise |

---

## Scaling

| Key | Action |
|---|---|
| `H` | Zoom In |
| `F` | Zoom Out |

---

## Reset & Exit

| Key | Action |
|---|---|
| `0` | Reset Transformations |
| `2` | Exit Application |

---

# Technologies Used

- C++
- OpenGL
- GLUT / FreeGLUT
- Mathematical Animation (Sin/Cos Functions)

---

# Graphics Concepts Used

- OpenGL Primitives
  - `GL_QUADS`
  - `GL_TRIANGLES`
  - `GL_LINES`
  - `GL_POLYGON`
  - `GL_QUAD_STRIP`

- 2D Transformations
  - Translation
  - Rotation
  - Scaling

- Procedural Geometry

- Real-Time Animation

- Dynamic Vertex Coloring

- Orthographic Projection

- Event-Driven Programming

---

# Mathematical Concepts

The waving animation is created using sine functions:

```math
wave = amplitude × sin(angle + position)
