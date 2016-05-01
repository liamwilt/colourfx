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

        w = glfwCreateWindow(1024, 768, "CirlcesThree", NULL, NULL);
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
                
                glBegin(GL_TRIANGLE_FAN);

                        glColor3f(1, 0, 0);

                        // Framerate-based angle. This integer will increment per frame displayed
                        static double iteration3 = 0;
                        // The x, y offset onto the screen
                        static const int xoffset3 = 169;
                        static const int yoffset3 = 384;
                        // The radius of both our circle and the circle it's spinning in.
                        static const float radius3 = 55;

                        // Calculate our x, y coordinates
                        double x3 = xoffset3 + radius3 * cos(iteration3);
                        double y3 = yoffset3 + radius3 * sin(iteration3);
                        static double wobble3 = 0.0;
                        
                        y3 += sin(wobble3) * 200;
                        wobble3 += 0.01;

                        static double a3 = 128;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / a3))
                        {

                                glVertex2f(x3 + radius3 * cos(i), y3 + radius3 * sin(i));

                        }

                        iteration3 += 0.05;

                glEnd();

                glBegin(GL_TRIANGLE_FAN);

                        glColor3f(0, 1, 0);

                        // Framerate-based angle. This integer will increment per frame displayed
                        static double iteration1 = 0;
                        // The x, y offset onto the screen
                        static const int xoffset1 = 512;
                        static const int yoffset1 = 384;
                        // The radius of both our circle and the circle it's spinning in.
                        static const float radius1 = 55;

                        // Calculate our x, y coordinates
                        double x1 = xoffset1 + radius1 * cos(iteration1);
                        double y1 = yoffset1 + radius1 * sin(iteration1);
                        static double wobble1 = 0.0;
                        
                        y1 += sin(wobble1) * 200;
                        wobble1 += 0.05;

                        static double a1 = 128;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / a1))
                        {

                                glVertex2f(x1 + radius1 * cos(i), y1 + radius1 * sin(i));

                        }

                        iteration1 += 0.05;

                glEnd();
                
                
                glBegin(GL_TRIANGLE_FAN);

                        glColor3f(0, 0, 1);

                        // Framerate-based angle. This integer will increment per frame displayed
                        static double iteration2 = 0;
                        // The x, y offset onto the screen
                        static const int xoffset2 = 855;
                        static const int yoffset2 = 384;
                        // The radius of both our circle and the circle it's spinning in.
                        static const float radius2 = 55;

                        // Calculate our x, y coordinates
                        double x2 = xoffset2 + radius2 * cos(iteration2);
                        double y2 = yoffset2 + radius2 * sin(iteration2);
                        static double wobble2 = 0.0;
                        
                        y2 += sin(wobble2) * 200;
                        wobble2 += 0.1;

                        static double a2 = 128;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / a2))
                        {

                                glVertex2f(x2 + radius2 * cos(i), y2 + radius2 * sin(i));

                        }

                        iteration2 += 0.05;

                glEnd();
                


                glfwSwapBuffers(w);
                glfwPollEvents();

        }

        glfwDestroyWindow(w);
        glfwTerminate();

        return 0;
}
