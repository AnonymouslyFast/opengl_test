#include "../Dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>


// Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Magic happens here
int main() {

    // Checks if glfw is properly initialized
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Changing a few glfw settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Creating the window
    GLFWwindow* window = glfwCreateWindow(640, 600, "OpenGL Test", NULL, NULL);
      // Checks if something went wrong creating the window and terminates glfw
    if (window == NULL) {
        std::cout << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
      // opens the window
    glfwMakeContextCurrent(window);


    // Checks if glad has a problem
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 640, 600); // setting the viewport for lower left corner

    // Setting the resize function to the resize event (so it calls the function when triggered)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Creating Shaders (Yes ik I am using full path cuz I didn't wanna spend YEARS on this shader shit)
    Shader shader(R"(C:\Users\caleb\OneDrive\Desktop\c++\opengl_test\assets\shaders\main_vertex.glsl)", R"(C:\Users\caleb\OneDrive\Desktop\c++\opengl_test\assets\shaders\main_fragment.glsl)");


    // Creating a rectangle

    float vertices[] = {    // Colors
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f  // top left
    };


    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };


    unsigned int VBO, VAO, EBO; // VBO = vertex buffer object, VAO = Vertex Array Object, EBO = Element Buffer Object

        // Generating unique buffer object ids for VBO, VAO and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

        // Binding VBO, EBO and VAO to their respective buffers
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // copies vertices and indices into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
        // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);  // can safely unbind



    // While loop to keep the window up
    while (!glfwWindowShouldClose(window)) {

        // Processing inputs ya know
        processInput(window);

        // Render shit go here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

            // Rendering Rectangle
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // other non-important stuff to comment
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate(); // Cleaning the trash
    return 0;
}

// When user resizes window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // resizing the viewport for the new window size to the lower left corner
}

// Put ya inputs in here ya dork
void processInput(GLFWwindow* window) {

    // when user presses ESC the window will close
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

}

