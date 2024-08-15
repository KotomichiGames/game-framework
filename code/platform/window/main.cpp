#include <glfw/factory.hpp>

int main()
{
    constexpr int width  = 800;
    constexpr int height = 600;

    engine::glfw::Factory platform_factory;

    const auto window = platform_factory.create_window();
    window->create("Window", width, height);

    // drawing initialization

    while (!window->is_closed())
    {
        // drawing

        window->update();
    }

    // drawing cleanup

    window->destroy();

    return 0;
}