#include <window_factory.hpp>
#include <window_manager.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>

using namespace engine;

int32_t main()
{
    const auto factory = WindowFactory::create_factory();

    WindowManager::instance().create(factory, { .title = "Context" });
    WindowManager::instance().open();

    gl::Functions::load_core();

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        WindowManager::instance().update();
    }

    WindowManager::instance().destroy();
    return 0;
}