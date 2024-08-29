#include <core/window_manager.hpp>

int32_t main()
{
    engine::core::WindowManager::instance().create({ .title = "Window" });
    engine::core::WindowManager::instance().open();

    while (engine::core::WindowManager::instance().is_active())
    {
        engine::core::WindowManager::instance().update();
    }

    engine::core::WindowManager::instance().destroy();
    return 0;
}