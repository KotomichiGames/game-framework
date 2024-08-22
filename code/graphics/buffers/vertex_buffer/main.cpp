#include <window_manager.hpp>
#include <window_factory.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>

#include <glad/glad.h>

using namespace engine;

int main()
{
    const auto factory = WindowFactory::create_factory();

    WindowManager::instance().create(factory, { "Vertex Buffer" });
    WindowManager::instance().open();

    gl::Functions::load();
    gladLoadGL();

    constexpr float vertices[] =
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

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        glBindVertexArray(vertex_array);
        gl::Commands::draw_arrays(gl::triangles, 3);

        WindowManager::instance().update();
    }

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);

    WindowManager::instance().destroy();
    return 0;
}