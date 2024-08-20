#include <windows/factory.hpp>
#include <window_instance.hpp>

#include <glfw/factory.hpp>
#include <glad/glad.h>

using namespace engine;

int main()
{
    const auto glfw_factory = std::make_shared<glfw::Factory>();
    //const auto win32_factory = std::make_shared<engine::win32::Factory>();

    WindowInstance::instance().create(glfw_factory, { "Window" });

    const auto platform = glfw_factory->create_platform();
    const auto context  = glfw_factory->create_context();

    context->create(WindowInstance::instance().handle());

    gladLoadGL();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    while (WindowInstance::instance().is_active())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        context->update();
        platform->update();
    }

    context->destroy();

    WindowInstance::instance().destroy();
    return 0;
}