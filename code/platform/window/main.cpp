#include <window_manager.hpp>
#include <window_factory.hpp>

using namespace engine;

int main()
{
    const auto factory = WindowFactory::create_factory();

    WindowManager::instance().create(factory, { "Window" });
    WindowManager::instance().open();

    while (WindowManager::instance().is_active())
    {
        WindowManager::instance().update();
    }

    WindowManager::instance().destroy();
    return 0;
}