#include <core/window_manager.hpp>
#include <core/rgb.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>
#include <opengl/vertex_array.hpp>

#include <math/vec3.hpp>

int32_t main()
{
    engine::core::WindowManager::instance().create({ .title = "Vertex Buffer" });
    engine::core::WindowManager::instance().open();

    engine::gl::Functions::load_core();
    engine::gl::Functions::load_extended();

    const std::vector<engine::math::vec3> vertices
    {
        { -0.5f, -0.5f, 0.0f },
        {  0.5f, -0.5f, 0.0f },
        {  0.0f,  0.5f, 0.0f }
    };

    engine::gl::Buffer vertex_buffer;
    vertex_buffer.create();
    vertex_buffer.data(engine::core::buffer_data::create_from(vertices), engine::gl::static_draw);

    engine::gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.attach_vertex_buffer(vertex_buffer, sizeof(engine::math::vec3));
    vertex_array.attribute({ 0, 3, engine::gl::type_float });

    engine::gl::Commands::clear(engine::core::color::gray);

    while (engine::core::WindowManager::instance().is_active())
    {
        engine::gl::Commands::clear(engine::gl::color_buffer_bit);

        vertex_array.bind();
        engine::gl::Commands::draw_arrays(engine::gl::triangles, vertices.size());

        engine::core::WindowManager::instance().update();
    }

    vertex_buffer.destroy();
    vertex_array.destroy();

    engine::core::WindowManager::instance().destroy();
    return 0;
}