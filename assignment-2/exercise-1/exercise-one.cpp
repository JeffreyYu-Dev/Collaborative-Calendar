#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

double dogRotation = 0;

void parseFile(std::string fileName, std::vector<std::tuple<double, double>> *vectors)
{
    std::string x, y;
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        throw std::invalid_argument("Can't open file");
    }

    // this could throw an error if the file contains something that isn't a double i think
    while (std::getline(file, x, ' ') && std::getline(file, y, ' '))
    {
        vectors->push_back(std::make_tuple(std::stod(x), std::stod(y)));
    }

    file.close();
}

void drawDog(const std::vector<std::tuple<double, double>> &vectors, double centerX, double centerY, double angle)
{
    glPushMatrix();

    glTranslatef(centerX, centerY, 0);
    glRotatef(angle, 0, 0, 1);

    glBegin(GL_LINE_STRIP);
    for (const auto &point : vectors)
    {
        double x = std::get<0>(point);
        double y = std::get<1>(point);
        glVertex2d(x, y);
    }
    glEnd();

    glPopMatrix();
}

int paint(const std::vector<std::tuple<double, double>> &vectors)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 60, 0, 60, -1, 1);

    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0);

    double circleRadius = 25.0;
    double circleCenterX = 30.0;
    double circleCenterY = 30.0;

    for (int angle = 0; angle < 360; angle += 45)
    {
        double radians = angle * M_PI / 180.0;
        double x = circleCenterX + circleRadius * cos(radians);
        double y = circleCenterY + circleRadius * sin(radians);

        drawDog(vectors, x, y, dogRotation);
    }
}

int main()
{

    std::vector<std::tuple<double, double>> vectors;

    // read from file and create pairs of vectors
    parseFile("dog.txt", &vectors);

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 1000, "Dogs!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // draw to the screen
        paint(vectors);

        dogRotation += 1.0;
        if (dogRotation >= 360)
        {
            dogRotation = 0;
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}