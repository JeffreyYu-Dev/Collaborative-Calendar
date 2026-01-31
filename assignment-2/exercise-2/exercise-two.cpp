#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Function to generate random floats in range [-1, 1]
static inline double frand()
{
    double x = ((double)rand()) / (double)RAND_MAX;
    if (rand() % 2)
    {
        x *= -1.0;
    }
    return x;
}

// Class to represent a 2D point
class Point
{
public:
    double x, y;

    Point() : x(0.0), y(0.0) {}
    Point(double x_val, double y_val) : x(x_val), y(y_val) {}

    // Calculate midpoint between this point and another
    Point midpoint(const Point &other) const
    {
        return Point((x + other.x) / 2.0, (y + other.y) / 2.0);
    }
};

// Function to get a random corner of the square
Point getRandomCorner()
{
    int corner = rand() % 4;
    switch (corner)
    {
    case 0:
        return Point(-1.0, -1.0); // Bottom-left
    case 1:
        return Point(1.0, -1.0); // Bottom-right
    case 2:
        return Point(1.0, 1.0); // Top-right
    case 3:
        return Point(-1.0, 1.0); // Top-left
    default:
        return Point(-1.0, -1.0);
    }
}

bool areDiagonallyOpposite(const Point &p1, const Point &p2)
{
    return (p1.x != p2.x) && (p1.y != p2.y);
}

Point getRandomNonDiagonalCorner(const Point &prevCorner)
{
    Point newCorner;
    do
    {
        newCorner = getRandomCorner();
    } while (areDiagonallyOpposite(prevCorner, newCorner));
    return newCorner;
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " N width height" << std::endl;
        std::cerr << "  N: number of points to draw" << std::endl;
        std::cerr << "  width: screen width in pixels" << std::endl;
        std::cerr << "  height: screen height in pixels" << std::endl;
        return 1;
    }

    int N = std::atoi(argv[1]);
    int width = std::atoi(argv[2]);
    int height = std::atoi(argv[3]);

    if (N <= 0 || width <= 0 || height <= 0)
    {
        std::cerr << "Error: N, width, and height must be positive integers" << std::endl;
        return 1;
    }

    std::cout << "Drawing " << N << " points on a " << width << "x" << height << " window" << std::endl;

    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    // Create window
    GLFWwindow *window = glfwCreateWindow(width, height, "Exercise 2 - Dot Plot", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    // Set up OpenGL viewing volume
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.1, 1.1, -1.1, 1.1, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // Set background to white
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set point size and color
    glPointSize(2.0f);
    glColor3f(0.0f, 0.0f, 0.0f); // Black

    // Algorithm implementation
    // Step 2: Choose a random corner c0
    Point currentCorner = getRandomCorner();

    // Step 3: Choose a random starting point p0
    Point currentPoint(frand(), frand());

    // Draw all points using immediate mode
    glBegin(GL_POINTS);

    for (int i = 1; i <= N; i++)
    {
        currentCorner = getRandomNonDiagonalCorner(currentCorner);

        currentPoint = currentPoint.midpoint(currentCorner);

        glVertex2d(currentPoint.x, currentPoint.y);

        if (N >= 100000 && i % 500000 == 0)
        {
            std::cout << "Progress: " << i << " / " << N << " points" << std::endl;
        }
    }

    glEnd();

    // Swap buffers once to display the result
    glfwSwapBuffers(window);

    std::cout << "Drawing complete. Close the window to exit." << std::endl;

    // Keep the window open
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}