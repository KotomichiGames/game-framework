#include <window_factory.hpp>
#include <window_manager.hpp>

using namespace engine;

int32_t main()
{
    const auto factory = WindowFactory::create_factory();

    WindowManager::instance().create(factory, { .title = "Window" });
    WindowManager::instance().open();

    while (WindowManager::instance().is_active())
    {
        WindowManager::instance().update();
    }

    WindowManager::instance().destroy();
    return 0;
}