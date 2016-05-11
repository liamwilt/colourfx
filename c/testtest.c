#define _BSD_SOURCE 2387423
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stddef.h>
#include <GLFW/glfw3.h>

#ifndef PI
# define PI 3.141592653
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

void drawCircle(GLfloat x, GLfloat y, GLfloat radius){
	int i;
	int triangleAmount = 285;
	
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		        x + (radius * cos(i * twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}

int main(int argc, char **argv)
{
        GLFWwindow *w;
        glfwSetErrorCallback(error);
        float r[5] = {100,90,80,70,60};

        if (!glfwInit())
                return 1;

        w = glfwCreateWindow(1024, 768, "CircleTests", NULL, NULL);
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

                drawCircle(100,100,r[0]);

                glfwSwapBuffers(w);
                glfwPollEvents();

        }

        glfwDestroyWindow(w);
        glfwTerminate();

        return 0;
}
