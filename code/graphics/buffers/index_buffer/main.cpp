#include <core/window_factory.hpp>
#include <core/window_manager.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>
#include <opengl/vertex_array.hpp>

#include <math/vec3.hpp>

using namespace engine;

int32_t main()
{
    const auto factory = core::WindowFactory::create_factory();

    core::WindowManager::instance().create(factory, { .title = "Index Buffer" });
    core::WindowManager::instance().open();

    gl::Functions::load_core();
    gl::Functions::load_extended();

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

    gl::Buffer vertex_buffer;
    vertex_buffer.create();
    vertex_buffer.data(base::buffer_data::create_from(vertices), gl::static_draw);

    gl::Buffer indices_buffer;
    indices_buffer.create();
    indices_buffer.data(base::buffer_data::create_from(indices), gl::static_draw);

    gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.attach_vertex_buffer(vertex_buffer, sizeof(math::vec3 ));
    vertex_array.attach_indices_buffer(indices_buffer);
    vertex_array.attribute({ 0, 3, gl::type_float, 0 });

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (core::WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        vertex_array.bind();
        gl::Commands::draw_elements(gl::triangles, indices.size());

        core::WindowManager::instance().update();
    }

    vertex_buffer.destroy();
    indices_buffer.destroy();
    vertex_array.destroy();

    core::WindowManager::instance().destroy();
    return 0;
}