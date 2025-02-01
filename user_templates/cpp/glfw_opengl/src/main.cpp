#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void handle_events(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void on_window_resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {

    if (!glfwInit()) {
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    auto window = glfwCreateWindow(800, 600, "Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Couldn't make window!\n";
        return 1;
    }

    glfwSetWindowSizeCallback(window, on_window_resize);

    glfwMakeContextCurrent(window);
    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.3, 0.6, 0.4, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();
        handle_events(window);
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
