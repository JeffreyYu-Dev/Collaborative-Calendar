# CS3388 — Computer Graphics

Coursework for CS3388 (Computer Graphics) at Western University. Each
assignment is a self-contained OpenGL program written in C++ against
[GLFW](https://www.glfw.org/), built with CMake.

## 📺 Demo

**[Watch the demo on YouTube →](https://www.youtube.com/watch?v=7qWtB-uOwBQ)**

[![Watch the demo](https://img.youtube.com/vi/7qWtB-uOwBQ/hqdefault.jpg)](https://www.youtube.com/watch?v=7qWtB-uOwBQ)

---

## What's in here

| | Program | What it does |
|---|---|---|
| **Assignment 1** | `first.cpp` | A window with a single flat-shaded triangle — the "hello world" of OpenGL. Covers window creation, the render loop, and immediate-mode geometry. |
| **Assignment 2 · Exercise 1** | `exercise-one.cpp` | Loads a dog outline from a coordinate file and draws eight copies of it arranged around a circle, each spinning in place. Covers file-driven geometry and the matrix stack. |
| **Assignment 2 · Exercise 2** | `exercise-two.cpp` | A restricted chaos game on a square — plots N random points under a rule that forbids jumping to a diagonally opposite corner, which turns noise into a fractal. |

---

## The programs in more detail

### Assignment 1 — first triangle

A 1280×1000 window with one bright green triangle, drawn in immediate mode
between `glBegin(GL_TRIANGLES)` and `glEnd()`. Three vertices, one colour set
with `glColor3f`. The point is the scaffolding around it: initializing GLFW,
making a context current, and the poll → clear → draw → swap loop that every
later program reuses.

### Assignment 2, Exercise 1 — dogs on a circle

The dog's outline lives in `dog.txt` as whitespace-separated `x y` pairs.
`parseFile` reads them into a vector of points, and `drawDog` renders them as a
`GL_LINE_STRIP`.

The interesting part is placement. Rather than baking eight sets of
coordinates, one dog is drawn eight times at 45° intervals around a circle of
radius 25, positioned with `glTranslatef` and spun with `glRotatef` inside a
`glPushMatrix` / `glPopMatrix` pair. The push/pop is what keeps each
transformation local — without it every dog would inherit the previous one's
matrix and the whole arrangement would drift off screen.

The world is set up with `glOrtho(0, 60, 0, 60, -1, 1)`, so coordinates are in
a flat 60×60 space rather than OpenGL's default −1…1.

### Assignment 2, Exercise 2 — restricted chaos game

Start at a random point in a square. Repeatedly pick a corner at random, move
halfway to it, and plot where you land.

Done with no constraints this fills the square. The twist here is the
restriction: the next corner may not be the one diagonally opposite the corner
picked previously. That single rule removes enough of the square that the
remaining points settle into a self-similar fractal.

Takes its parameters on the command line:

```bash
./exercise-two <N> <width> <height>

# 100,000 points in a 1000x1000 window
./exercise-two 100000 1000 1000
```

The scene is drawn once into the back buffer, swapped, and then the window is
simply held open — there's no animation, so there's no reason to redraw every
frame.

---

## Building

You'll need **CMake 3.10+**, a C++11 compiler, and **GLFW3**.

```bash
# macOS
brew install cmake glfw

# Debian / Ubuntu
sudo apt install cmake libglfw3-dev

# Arch
sudo pacman -S cmake glfw
```

### Assignment 2 (CMake)

```bash
cd assignment-2/exercise-1
mkdir -p build && cd build
cmake ..
make
./exercise-one
```

```bash
cd assignment-2/exercise-2
mkdir -p build && cd build
cmake ..
make
./exercise-two 100000 1000 1000
```

Exercise 1's `CMakeLists.txt` copies `dog.txt` into the build directory, so run
the binary from `build/` — it looks for the file in the working directory.

### Assignment 1 (single file)

Assignment 1 predates the CMake setup and compiles directly:

```bash
cd assignment-1

# macOS
c++ first.cpp -o first -lglfw -framework OpenGL && ./first

# Linux
c++ first.cpp -o first -lglfw -lGL && ./first
```

---

## A note on the build setup

Assignment 1 was written on Arch Linux, where the compiler found GLFW and
OpenGL without being told where to look. Assignment 2 onward was written on
macOS, where OpenGL has to be linked as a framework:

```cmake
find_package(glfw3 REQUIRED)
target_link_libraries(exercise-one
    glfw
    "-framework OpenGL"
)
```

That's why the later assignments carry a `CMakeLists.txt` and the first one
doesn't.

These programs use OpenGL's fixed-function immediate mode (`glBegin`/`glEnd`,
`glOrtho`, the matrix stack), which macOS marks as deprecated. It still runs,
but the compiler will say so.
