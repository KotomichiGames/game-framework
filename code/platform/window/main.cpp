#include <glfw/window.hpp>

int main()
{
    engine::Window window;
    window.create("Window", 800, 600);

    // drawing initialization

    while (!window.is_closed())
    {
        // drawing

        window.update();
    }

    // drawing cleanup

    window.destroy();

    return 0;
}