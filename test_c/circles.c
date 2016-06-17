#define _BSD_SOURCE 2387423
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stddef.h>
#include <GLFW/glfw3.h>

#ifndef M_PI
# define M_PI 3.141592653
#endif

static void error(int error, const char *desc)
{
        fputs(desc, stderr);
}

static void key_callback(GLFWwindow *w, int key, int scancode, int action, int mods)
{
        if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
                glfwSetWindowShouldClose(w, GL_TRUE);
}

int main(int argc, char **argv)
{
        GLFWwindow *w;
        glfwSetErrorCallback(error);

        if (!glfwInit())
                return 1;

        w = glfwCreateWindow(1024, 768, "Cirlces", NULL, NULL);
        if (!w)
        {
                glfwTerminate();
                return 1;
        }


        glfwMakeContextCurrent(w);
        glfwSetKeyCallback(w, key_callback);

        while (!glfwWindowShouldClose(w))
        {
                int width, height;
                glfwGetFramebufferSize(w, &width, &height);

                glClear(GL_COLOR_BUFFER_BIT);
                glDisable(GL_DEPTH_TEST);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(0, width, height, 0, 0, 1);
                glMatrixMode(GL_MODELVIEW);

                // Draw our line
                glBegin(GL_LINE_LOOP);

                        glColor3f(1, 0, 1);

                        // Framerate-based angle. As the frames are displayed, this integer will increment
                        // and continue until it hits 360, then it will wrap around and start from 0
                        static double iteration = 0;
                        // The x, y offset onto the screen -- this should later be centered
                        static const int xoffset = 512;
                        static const int yoffset = 384;
                        // The radius of both our circle and the circle it's spinning in.
                        static const float radius = 75;

                        // Calculate our x, y coordinates
                        double x1 = xoffset + radius * cos(iteration);
                        double y1 = yoffset + radius * sin(iteration);
                        static double wobble = 0.0;
                        
                        y1 += sin(wobble) * 200;
                        wobble += 0.01;

                        static double b = 128;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / b))
                        {

                                glVertex2f(x1 + radius * cos(i), y1 + radius * sin(i));

                        }

                        iteration += 0.05;

                glEnd();


                glfwSwapBuffers(w);
                glfwPollEvents();

        }

        glfwDestroyWindow(w);
        glfwTerminate();

        return 0;
}
