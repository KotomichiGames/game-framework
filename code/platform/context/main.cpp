#include <core/window_factory.hpp>
#include <core/window_manager.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>

using namespace engine;

int32_t main()
{
    const auto factory = core::WindowFactory::create_factory();

    core::WindowManager::instance().create(factory, { .title = "Context" });
    core::WindowManager::instance().open();

    gl::Functions::load_core();

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (core::WindowManager::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        core::WindowManager::instance().update();
    }

    core::WindowManager::instance().destroy();
    return 0;
}