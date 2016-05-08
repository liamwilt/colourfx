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
static GLboolean track_cursor = GL_FALSE;
static GLFWcursor* standard_cursors[6];

static void error(int error, const char *desc)
{
        fputs(desc, stderr);
}

static void cursor_position_callback(GLFWwindow* w, double x, double y)
{
    FILE *f = fopen("data.txt", "a");
    if (f==NULL)
    {
        printf("Error opening file!\n");
    }
    
    fprintf(f,"%0.3f: Cursor position: %f %f (%+f %+f)\n",
           glfwGetTime(),
           x, y, x - cursor_x, y - cursor_y);

    cursor_x = x;
    cursor_y = y;
    fclose(f);
}

static void key_callback(GLFWwindow *w, int key, int scancode, int action, int mods)
{
        if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS)
                glfwSetWindowShouldClose(w, GL_TRUE);
}

int main(void)
{
        int i;
        GLFWwindow *w;
                
        glfwSetErrorCallback(error);

        if (!glfwInit())
            exit(EXIT_FAILURE);
            
        for (i = 0;  i < sizeof(standard_cursors) / sizeof(standard_cursors[0]);  i++)
        {
            const int shapes[] = {
                GLFW_ARROW_CURSOR,
                GLFW_IBEAM_CURSOR,
                GLFW_CROSSHAIR_CURSOR,
                GLFW_HAND_CURSOR,
                GLFW_HRESIZE_CURSOR,
                GLFW_VRESIZE_CURSOR
            };
            standard_cursors[i] = glfwCreateStandardCursor(shapes[i]);
            if (!standard_cursors[i])
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
        }

        w = glfwCreateWindow(1024, 768, "CirclePrint", NULL, NULL);
        if (!w)
        {
                glfwTerminate();
                exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(w);
        glfwGetCursorPos(w, &cursor_x, &cursor_y);
        glfwSetCursorPosCallback(w, cursor_position_callback);
        glfwSetCursor(w, standard_cursors[3]);
        glfwSetKeyCallback(w, key_callback);

        while (!glfwWindowShouldClose(w))
        {
                int wnd_width, wnd_height, fb_width, fb_height;
                glfwGetFramebufferSize(w, &fb_width, &fb_height);
                

                if (track_cursor)
                {
                    float scale;

                    glfwGetWindowSize(w, &wnd_width, &wnd_height);
                    glfwGetFramebufferSize(w, &fb_width, &fb_height);

                    scale = (float) fb_width / (float) wnd_width;

                    glViewport(0, 0, fb_width, fb_height);

                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    glOrtho(0.f, fb_width, 0.f, fb_height, 0.f, 1.f);

                    glBegin(GL_LINES);
                    glVertex2f(0.f, (GLfloat) (fb_height - cursor_y * scale));
                    glVertex2f((GLfloat) fb_width, (GLfloat) (fb_height - cursor_y * scale));
                    glVertex2f((GLfloat) cursor_x * scale, 0.f);
                    glVertex2f((GLfloat) cursor_x * scale, (GLfloat) fb_height);
                    glEnd();
                }

                glClear(GL_COLOR_BUFFER_BIT);
                glDisable(GL_DEPTH_TEST);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glOrtho(0, fb_width, fb_height, 0, 0, 1);
                glMatrixMode(GL_MODELVIEW);

                glBegin(GL_TRIANGLE_FAN);

                        glColor3f(1, 0, 0);

                        static double iteration = 0;
                        
                        static const float radius = 100;
                        
                        int xoffset = radius - (2 * radius);
                        int yoffset = 384;

                        double x1 = xoffset + radius;
                        double y1 = yoffset + radius * (sin(iteration));
                        
                        static double a = 256;
                        
                        for (double i = 0; i < 2 * M_PI; i = i + ((2 * M_PI) / a))
                        {

                                glVertex2f(x1 + radius * cos(i), y1 + radius * sin(i));

                        }

                        iteration += 0.03;

                glEnd();
                glTranslatef(1.0f,0.0f,0.0f);
                


                glfwSwapBuffers(w);
                glfwPollEvents();

        }

        glfwDestroyWindow(w);
        
        for (i = 0;  i < sizeof(standard_cursors) / sizeof(standard_cursors[0]);  i++)
            glfwDestroyCursor(standard_cursors[i]);
        
        glfwTerminate();
        exit(EXIT_SUCCESS);

        return 0;
}
