#include <platform_factory.hpp>

#include <window_instance.hpp>

using namespace engine;

int main()
{
    const auto factory = PlatformFactory::create_factory();

    WindowInstance::instance().create(factory, { "Window" });

    const auto platform = factory->create_platform();

    while (WindowInstance::instance().is_active())
    {
        platform->update();
    }

    WindowInstance::instance().destroy();
    return 0;
}