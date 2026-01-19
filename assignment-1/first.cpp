#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280,1000,"Hello World",NULL,NULL);
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
        /* Poll for and process events */
        glfwPollEvents();
        
		/* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        // set the colour of the triangel
        glColor3f(65.0/255.0,252.0/255.0,3.0/255.0);
        

        // create triangle
        glBegin(GL_TRIANGLES);
        glVertex2f(0,0.5);
        glVertex2f(0.5,-0.25);
        glVertex2f(-0.5,-0.25);
        glEnd();

        

		//...
        
		/* Swap front and back buffers */
        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}
