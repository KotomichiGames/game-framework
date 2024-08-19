#include <glfw/factory.hpp>
#include <window_instance.hpp>

#include <glad/glad.h>

int main()
{
    const auto platform_factory = std::make_shared<engine::glfw::Factory>();

    auto& window = engine::WindowInstance::instance();
    window.create(platform_factory, { "Index Buffer" });

    gladLoadGL();

    const float vertices[] =
    {
        -0.5f, 0.5f, 0.0f,
         0.5f, 0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    unsigned int indices[] =
    {
        0, 1 ,2,
        2, 3, 0
    };

    unsigned int vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices_buffer;
    glGenBuffers(1, &indices_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    while (window.is_active())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vertex_array);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.update();
    }

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &indices_buffer);
    glDeleteVertexArrays(1, &vertex_array);

    window.destroy();
    return 0;
}