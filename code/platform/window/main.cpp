#include <windows/factory.hpp>
#include <window_instance.hpp>

#include <glfw/factory.hpp>
#include <glad/glad.h>

int main()
{
    const auto glfw_factory  = std::make_shared<engine::glfw::Factory>();
    const auto win32_factory = std::make_shared<engine::win32::Factory>();

    auto& window = engine::WindowInstance::instance();
    window.create(glfw_factory, { "Window" });

    const auto platform = glfw_factory->create_platform();
    const auto context  = win32_factory->create_context();
    context->create(window.handle());

    gladLoadGL();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    while (window.is_active())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        window.update();

        context->update();
        platform->update();
    }

    context->destroy();

    window.destroy();
    return 0;
}