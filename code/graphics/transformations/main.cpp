#include <core/window_manager.hpp>
#include <core/file.hpp>
#include <core/time.hpp>

#include <core/primivite_shapes.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/vertex_array.hpp>
#include <opengl/shader.hpp>

#include <glad/glad.h>

int32_t main()
{
    engine::core::WindowManager::instance().create({ .title = "Transformations" });
    engine::core::WindowManager::instance().open();

    engine::gl::Functions::load_core();
    engine::gl::Functions::load_extended();

    gladLoadGL();

    engine::gl::ShaderStage vertex_stage { engine::gl::vertex_stage };
    vertex_stage.create();
    vertex_stage.source(engine::core::File::read("default_shader_spv.vert", std::ios::binary));

    engine::gl::ShaderStage fragment_stage { engine::gl::fragment_stage };
    fragment_stage.create();
    fragment_stage.source(engine::core::File::read("default_shader_spv.frag", std::ios::binary));

    engine::gl::Shader default_shader;
    default_shader.create();
    default_shader.attach(vertex_stage);
    default_shader.attach(fragment_stage);
    default_shader.compile();

    vertex_stage.destroy();
    fragment_stage.destroy();

    const auto [vertices, indices] = editor::core::PrimiviteShapes::create_plane();

    engine::gl::Buffer vertex_buffer;
    vertex_buffer.create();
    vertex_buffer.data(engine::core::buffer_data::create_from(vertices));

    engine::gl::Buffer indices_buffer;
    indices_buffer.create();
    indices_buffer.data(engine::core::buffer_data::create_from(indices));

    engine::gl::VertexArray vertex_array;
    vertex_array.create();
    vertex_array.attach_vertex_buffer(vertex_buffer, sizeof(editor::core::vertex));
    vertex_array.attach_indices_buffer(indices_buffer);
    vertex_array.attribute({ 0, 3, engine::gl::type_float });

    constexpr engine::core::rgb material_color { 1.0f, 0.0f, 0.0f };

    engine::gl::Buffer material_buffer;
    material_buffer.create();
    material_buffer.bind(static_cast<int32_t>(engine::core::buffer_location::material));
    material_buffer.data(engine::core::buffer_data::create_from(&material_color));

    engine::gl::Commands::clear(engine::core::color::gray);

    engine::core::Time time;
    time.init();

    while (engine::core::WindowManager::instance().is_active())
    {
        time.update();

        engine::gl::Commands::clear(engine::gl::color_buffer_bit);

        default_shader.bind();

        vertex_array.bind();
        engine::gl::Commands::draw_elements(engine::gl::triangles, indices.size());

        engine::core::WindowManager::instance().update();
    }

    vertex_buffer.destroy();
    indices_buffer.destroy();
    vertex_array.destroy();

    material_buffer.destroy();
    default_shader.destroy();

    engine::core::WindowManager::instance().destroy();
    return 0;
}