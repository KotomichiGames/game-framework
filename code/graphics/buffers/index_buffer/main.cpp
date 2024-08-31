#include <core/window_manager.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/vertex_array.hpp>

#include <math/vec3.hpp>

int32_t main()
{
    engine::core::WindowManager::instance().create({ .title = "Index Buffer" });
    engine::core::WindowManager::instance().open();

    engine::gl::Functions::load_core();
    engine::gl::Functions::load_extended();

    #pragma region buffers

    const std::vector<engine::math::vec3> vertices
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

    engine::gl::Buffer vertex_buffer;
    vertex_buffer.create();
    vertex_buffer.data(engine::core::buffer_data::create_from(vertices));

    engine::gl::Buffer indices_buffer;
    indices_buffer.create();
    indices_buffer.data(engine::core::buffer_data::create_from(indices));

    engine::gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.attach_vertex_buffer(vertex_buffer, sizeof(engine::math::vec3));
    vertex_array.attach_indices_buffer(indices_buffer);
    vertex_array.attribute({ 0, 3, engine::gl::type_float });

    #pragma endregion

    engine::gl::Commands::clear(engine::core::color::gray);

    while (engine::core::WindowManager::instance().is_active())
    {
        engine::gl::Commands::clear(engine::gl::color_buffer_bit);

        vertex_array.bind();
        engine::gl::Commands::draw_elements(engine::gl::triangles, indices.size());

        engine::core::WindowManager::instance().update();
    }

    #pragma region cleanup

    vertex_buffer.destroy();
    indices_buffer.destroy();
    vertex_array.destroy();

    #pragma endregion

    engine::core::WindowManager::instance().destroy();
    return 0;
}