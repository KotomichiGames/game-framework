#include <window_manager.hpp>
#include <window_factory.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>

using namespace engine;

int main()
{
    const auto factory = WindowFactory::create_factory();

    WindowManager::instance().create(factory, { "Context" });
    WindowManager::instance().open();

    gl::Functions::load();

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        WindowManager::instance().update();
    }

    WindowManager::instance().destroy();
    return 0;
}