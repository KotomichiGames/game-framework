#include <core/window_factory.hpp>
#include <core/window_manager.hpp>
#include <core/file.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>
#include <opengl/vertex_array.hpp>
#include <opengl/shader_stage.hpp>

#include <math/vec3.hpp>

#include <glad/glad.h>

#include <iostream>

using namespace engine;

int32_t main()
{
    const auto factory = core::WindowFactory::create_factory();

    core::WindowManager::instance().create(factory, { .title = "Shaders" });
    core::WindowManager::instance().open();

    gl::Functions::load_core();
    gl::Functions::load_extended();

    gladLoadGL();

    const auto vertex_stage_data   = core::File::read("diffuse_vert.glsl");
    const auto fragment_stage_data = core::File::read("diffuse_frag.glsl");

    const char* vertex_stage_temp = vertex_stage_data.data();
    const auto fragment_stage_temp = fragment_stage_data.data();

    gl::ShaderStage vertex_shader { gl::vertex_shader };
    vertex_shader.create();
    glShaderSource(vertex_shader.handle(), 1, &vertex_stage_temp, nullptr);
    glCompileShader(vertex_shader.handle());

    gl::ShaderStage fragment_shader { gl::fragment_shader };
    fragment_shader.create();
    glShaderSource(fragment_shader.handle(), 1, &fragment_stage_temp, nullptr);
    glCompileShader(fragment_shader.handle());

    const uint32_t diffuse_shader = glCreateProgram();
    glAttachShader(diffuse_shader, vertex_shader.handle());
    glAttachShader(diffuse_shader, fragment_shader.handle());
    glLinkProgram(diffuse_shader);

    GLint success;
    glGetProgramiv(diffuse_shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar info_log[512];
        glGetProgramInfoLog(diffuse_shader, 512, nullptr, info_log);
        std::cerr << "Shader program linking failed:\n" << info_log << std::endl;
    }

    vertex_shader.destroy();
    fragment_shader.destroy();

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

        glUseProgram(diffuse_shader);

        vertex_array.bind();
        gl::Commands::draw_elements(gl::triangles, indices.size());

        core::WindowManager::instance().update();
    }

    vertex_buffer.destroy();
    indices_buffer.destroy();
    vertex_array.destroy();

    glDeleteProgram(diffuse_shader);

    core::WindowManager::instance().destroy();
    return 0;
}