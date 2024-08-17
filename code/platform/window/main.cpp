#include <glfw/factory.hpp>
#include <window_instance.hpp>

#include <glad/glad.h>

int main()
{
    const auto factory = std::make_shared<engine::glfw::Factory>();

    const auto platform = factory->create_platform();
    const auto context  = factory->create_context();

    auto& window = engine::WindowInstance::instance();
    window.create(factory, { "Window" });

    gladLoadGL();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    while (window.is_active())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        window.update();

        platform->update();
    }

    window.destroy();

    return 0;
}