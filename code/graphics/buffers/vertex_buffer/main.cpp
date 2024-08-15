#include <glfw/factory.hpp>

#include <glad/glad.h>

int main()
{
    constexpr int width  = 800;
    constexpr int height = 600;

    engine::glfw::Factory platform_factory;

    const auto window = platform_factory.create_window();
    window->create("Vertex Buffer", width, height);

    gladLoadGL();

    float const vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    while (!window->is_closed())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window->update();
    }

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);

    window->destroy();

    return 0;
}