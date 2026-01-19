# Explaination

- created a window, with paramters 1280x1000 and set the title to "hello world"

```c++
glfwCreateWindow(1280,1000,"hello world");

```

- set the colour of the triangle using glColor3f, I picked a random colour and inserted the values into the function

```c++
    // Bright green
    glColor3f(65.0/255.0,252.0/255.0,3.0/255.0);

```

- made the triangle using immediate mode. I put the vertices between the glBegin and glEnd using the GL_TRIANGLES mode, and put my vertices in between the two functions

```c++
    glBegin(GL_TRIANGLES);
    glVertex2f(0,0.5);
    glVertex2f(0.5,-0.25);
    glVertex2f(-0.5,-0.25);
    glEnd();

```
