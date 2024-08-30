#include <core/window_manager.hpp>
#include <core/rgb.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>

int32_t main()
{
    engine::core::WindowManager::instance().create({ .title = "Context" });
    engine::core::WindowManager::instance().open();

    engine::gl::Functions::load_core();

    engine::gl::Commands::clear(engine::core::color::gray);

    while (engine::core::WindowManager::instance().is_active())
    {
        engine::gl::Commands::clear(engine::gl::color_buffer_bit);

        engine::core::WindowManager::instance().update();
    }

    engine::core::WindowManager::instance().destroy();
    return 0;
}