#include <core/window_factory.hpp>
#include <core/window_manager.hpp>

using namespace engine;

int32_t main()
{
    const auto factory = core::WindowFactory::create_factory();

    core::WindowManager::instance().create(factory, { .title = "Window" });
    core::WindowManager::instance().open();

    while (core::WindowManager::instance().is_active())
    {
        core::WindowManager::instance().update();
    }

    core::WindowManager::instance().destroy();
    return 0;
}