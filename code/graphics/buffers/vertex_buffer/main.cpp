#include <core/window_factory.hpp>
#include <core/window_manager.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>
#include <opengl/vertex_array.hpp>

#include <base/buffer_data.hpp>

#include <math/vec3.hpp>

#include <glad/glad.h>

using namespace engine;

int32_t main()
{
    const auto factory = core::WindowFactory::create_factory();

    core::WindowManager::instance().create(factory, { .title = "Vertex Buffer" });
    core::WindowManager::instance().open();

    gl::Functions::load_core();
    gl::Functions::load_extended();

    gladLoadGL();

    const std::vector<math::vec3> vertices
    {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.0f,  0.5f, 0.0f }
    };

    gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.bind();

    const base::buffer_data vertex_buffer_data = base::buffer_data::create_from(vertices);

    uint32_t vertex_buffer;
    gl::glCreateBuffers(1, &vertex_buffer);
    gl::glBindBuffer(gl::array_buffer, vertex_buffer);
    gl::glNamedBufferData(vertex_buffer, vertex_buffer_data.size(), vertex_buffer_data.data(), gl::static_draw);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, gl::type_float, 0, 3 * sizeof(float), static_cast<void*>(nullptr));

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (core::WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        vertex_array.bind();
        gl::Commands::draw_arrays(gl::triangles, vertices.size());

        core::WindowManager::instance().update();
    }

    gl::glDeleteBuffers(1, &vertex_buffer);
    vertex_array.destroy();

    core::WindowManager::instance().destroy();
    return 0;
}