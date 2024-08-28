#include <core/window_manager.hpp>

using namespace engine;

int32_t main()
{
    core::WindowManager::instance().create({ .title = "Window" });
    core::WindowManager::instance().open();

    while (core::WindowManager::instance().is_active())
    {
        core::WindowManager::instance().update();
    }

    core::WindowManager::instance().destroy();
    return 0;
}