#define _BSD_SOURCE 2387423
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stddef.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>

#ifndef Pi
# define Pi 3.141592653
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

float drawCircle(GLfloat x, GLfloat y, GLfloat radius){
	static double j = 0;
	static double triangles = 360;
	
	glBegin(GL_TRIANGLE_FAN);
	    double a = x;
        double b = y + radius * (sin(j));
		glVertex2f(x, y); // center of circle
		glColor3f(1, 0, 1); // color of circle
		for (double i = 0; i < 2 * Pi; i = i + ((2 * Pi) / triangles))
        {
            glVertex2f(a + radius * cos(i), b + radius * sin(i));
        }
        j += 0.03;
	glEnd();
	glTranslatef(3,0,0);
}

int main()
{
        GLFWwindow* w;
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

        do{
            int width, height;
            glfwGetFramebufferSize(w, &width, &height);

            glClear(GL_COLOR_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, width, height, 0, 0, 1);
            glMatrixMode(GL_MODELVIEW);
                           
            drawCircle(0,768/2,r[0]);

            glfwSwapBuffers(w);
            glfwPollEvents();
        }
        while (!glfwWindowShouldClose(w));
        
        glfwDestroyWindow(w);
        glfwTerminate();

        return 0;
}
