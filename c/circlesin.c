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

#if defined(_MSC_VER)
 #define _USE_MATH_DEFINES
#endif

#define CURSOR_FRAME_COUNT 60

static double cursor_x;
static double cursor_y;
static int swap_interval = 1;
static GLboolean wait_events = GL_FALSE;
static GLboolean animate_cursor = GL_FALSE;
static GLboolean track_cursor = GL_FALSE;
static GLFWcursor* standard_cursors[6];

static void error(int error, const char *desc)
{
        fputs(desc, stderr);
}

static void key_callback(GLFWwindow *w, int key, int scancode, int action, int mods)
{
        if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
                glfwSetWindowShouldClose(w, GL_TRUE);
}

int main(void)
{
        GLFWwindow *w;
        glfwSetErrorCallback(error);

        if (!glfwInit())
                return 1;

        w = glfwCreateWindow(1024, 768, "CirlceSin", NULL, NULL);
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

                        static double iteration1 = 0;
                        
                        static const int xoffset1 = 0;
                        static const int yoffset1 = 384;
                        
                        static const float radius1 = 100;

                        double x1 = xoffset1 + radius1;
                        double y1 = yoffset1 + radius1 * (2 * cos(iteration1));
                        
                        static double a1 = 256;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / a1))
                        {

                                glVertex2f(x1 + radius1 * cos(i), y1 + radius1 * sin(i));

                        }

                        iteration1 += 0.03;

                glEnd();
                
                glBegin(GL_TRIANGLE_FAN);

                        glColor3f(0, 1, 0);

                        static double iteration2 = 0;
                        
                        static const int xoffset2 = -512;
                        static const int yoffset2 = 384;
                      
                        static const float radius2 = 60;
                        
                        double x2 = xoffset2 + radius2;
                        double y2 = yoffset2 + radius2 * (4 * sin(iteration2));
                        
                        static double a2 = 256;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / a2))
                        {

                                glVertex2f(x2 + radius2 * cos(i), y2 + radius2 * sin(i));
                                

                        }

                        iteration2 += 0.03;
                        

                glEnd();
                
                glBegin(GL_TRIANGLE_FAN);

                        glColor3f(0, 0, 1);

                        static double iteration3 = 0;
                        
                        static const int xoffset3 = -1024;
                        static const int yoffset3 = 384;
                      
                        static const float radius3 = 30;
                        
                        double x3 = xoffset3 + radius3;
                        double y3 = yoffset3 + radius3 * (10 * cos(iteration3));
                        
                        static double a3 = 256;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / a3))
                        {

                                glVertex2f(x3 + radius3 * cos(i), y3 + radius3 * sin(i));
                                

                        }

                        iteration3 += 0.04;
                        

                glEnd();
                glTranslatef(1.0f,0.0f,0.0f);
                


                glfwSwapBuffers(w);
                glfwPollEvents();

        }

        glfwDestroyWindow(w);
        glfwTerminate();

        return 0;
}
