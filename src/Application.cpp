#include <iostream>
#include "../Dependencies/include/glad/glad.h"
#include <GLFW/glfw3.h>

// Prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// (TEMP) vertex shader src
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// (TEMP) fragment shader src
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

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
    GLFWwindow* window = glfwCreateWindow(600, 800, "MLDC", NULL, NULL);
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

    glViewport(0, 0, 600, 800); // setting the viewport for lower left corner

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Creating vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // creates a shader unique id
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attaches the shader src to vertex shader
    glCompileShader(vertexShader); // compiles the shader

    // Checking if shader compiles successfully
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //  returns if successful or not
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Creating fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Creating shader program
    unsigned int shaderProgram = glCreateProgram(); // creates a unique id for the program and assigns it
        // Attaching vertex and fragment shaders to the shader program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
        // Links the program
    glLinkProgram(shaderProgram);

    // Checking if failed
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    // Deletes the shaders since there's no longer a use for them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // vertices in a 3d space so leave z 0.0 so it can look 2d
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO; // VBO = vertex buffer object
    glGenBuffers(1, &VBO); // generates unique buffer object id to VBO var

    // creating a VAO = Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // binding the array buffer to VBO var

    // copies vertices into the buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // While loop to keep the window up
    while (!glfwWindowShouldClose(window)) {

        // Processing inputs ya know
        processInput(window);

        // Render shit go here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


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
