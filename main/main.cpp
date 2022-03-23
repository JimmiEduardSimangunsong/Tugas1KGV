// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Util.h"

using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();

    // Vertices and indexArr P
    float vertices[] = {
        -0.5,  0.8,
        -0.3,  0.8,
        -0.5, -0.8,
        -0.3, -0.8,

         0.3,  0.8,
        -0.3,  0.6,
         0.2,  0.6,

        -0.3,  0.2,
         0.2,  0.2,
        -0.3,  0.0,
         0.3,  0.0,

         0.3,  0.5,
         0.5,  0.6,
         0.3,  0.3,
         0.5,  0.2

    };

    unsigned int indexArr[] = {
        0, 1, 3,
        0, 2, 3,

        1, 4, 6,
        1, 5, 6,

        7, 8, 10,
        7, 9, 10,

        4, 11, 6,
        4, 11, 12,

        13, 10, 8,
        13, 10, 14,

        11, 12, 14,
        11, 13, 14
    };

    /*
    // Vertices and indexArr J
    float vertices[] = {
        -1, 1,
        -1, 0.8,
        0.8, 0.8,
        0.8, 1,
        1, 1,
        1, -1,
        0.8, -1,
        0.8, -0.8,
        -1, -0.8,
        -1, -1
    };

    unsigned int indexArr[] = {
        0, 1, 2,
        0, 2, 3,
        3, 6, 5,
        3, 5, 4,
        8, 6, 7,
        8, 9, 6
    };
    */

    /*
    // Vertices and indexArr Square
    float vertices[] = {
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f
    };

    unsigned int indexArr[] = {
        0, 1, 2,
        0, 2, 3
    };
    */
    //pengiriman data ke gpu dengan buffer

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer); //pointer variabel,mengalokasikan sebuah buffer sebanyak 1 buah

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 30, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


    //informasikan kepada gpu bahwa kita akan menggunakan buffer ini
    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, indexArr, GL_STATIC_DRAW);



    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        // Draw P using IndexBuffer
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        
        // Draw J using IndexBuffer
        // glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

        // Draw Square using IndexBuffer
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        // Draw Triangle using GLEW
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        /*
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.5f);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.5f, -0.5f);
        glEnd();
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file