#include <window_factory.hpp>
#include <window_manager.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>
#include <opengl/vertex_array.hpp>

#include <glad/glad.h>

using namespace engine;

int32_t main()
{
    const auto factory = WindowFactory::create_factory();

    WindowManager::instance().create(factory, { .title = "Vertex Buffer" });
    WindowManager::instance().open();

    gl::Functions::load_core();
    gl::Functions::load_extended();

    gladLoadGL();

    constexpr float vertices[]
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    unsigned int vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        vertex_array.bind();
        gl::Commands::draw_arrays(gl::triangles, 3);

        WindowManager::instance().update();
    }

    glDeleteBuffers(1, &vertex_buffer);
    vertex_array.destroy();

    WindowManager::instance().destroy();
    return 0;
}