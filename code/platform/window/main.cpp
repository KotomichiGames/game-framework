#include <glfw/factory.hpp>

#include <glad/glad.h>

int main()
{
    constexpr int width  = 800;
    constexpr int height = 600;

    engine::glfw::Factory platform_factory;

    const auto window = platform_factory.create_window();
    window->create("Window", width, height);

    gladLoadGL();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    while (!window->is_closed())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        window->update();
    }

    window->destroy();

    return 0;
}