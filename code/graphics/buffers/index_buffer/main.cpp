#include <core/window_factory.hpp>
#include <core/window_manager.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>
#include <opengl/vertex_array.hpp>

#include <math/vec3.hpp>

#include <glad/glad.h>

using namespace engine;

int32_t main()
{
    const auto factory = core::WindowFactory::create_factory();

    core::WindowManager::instance().create(factory, { .title = "Index Buffer" });
    core::WindowManager::instance().open();

    gl::Functions::load_core();
    gl::Functions::load_extended();

    gladLoadGL();

    const std::vector<math::vec3> vertices
    {
        { -0.5f,  0.5f, 0.0f },
        {  0.5f,  0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        { -0.5f, -0.5f, 0.0f }
    };

    const std::vector<uint32_t> indices
    {
        0, 1 ,2,
        2, 3, 0
    };

    gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    unsigned int vertex_buffer;
    glCreateBuffers(1, &vertex_buffer);
    glBindBuffer(gl::array_buffer, vertex_buffer);
    glNamedBufferData(gl::array_buffer, vertices.size() * sizeof(math::vec3), vertices.data(), gl::static_draw);

    unsigned int indices_buffer;
    glCreateBuffers(1, &indices_buffer);
    glBindBuffer(gl::element_array_buffer, indices_buffer);
    glNamedBufferData(gl::element_array_buffer, indices.size() * sizeof(uint32_t), indices.data(), gl::static_draw);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, gl::type_float, 0, 3 * sizeof(float), static_cast<void*>(nullptr));

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (core::WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        vertex_array.bind();
        gl::Commands::draw_elements(gl::triangles, indices.size());

        core::WindowManager::instance().update();
    }

    glDeleteBuffers(1, &vertex_buffer);
    glDeleteBuffers(1, &indices_buffer);
    vertex_array.destroy();

    core::WindowManager::instance().destroy();
    return 0;
}