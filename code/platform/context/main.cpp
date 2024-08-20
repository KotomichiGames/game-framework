#include <platform_factory.hpp>

#include <window_instance.hpp>

#include <opengl/functions.hpp>
#include <opengl/commands.hpp>
#include <opengl/macros.hpp>

using namespace engine;

int main()
{
    const auto factory = PlatformFactory::create_factory();

    WindowInstance::instance().create(factory, { "Context" });

    const auto platform = factory->create_platform();
    const auto context  = factory->create_context();

    context->create(WindowInstance::instance().handle());

    gl::Functions::load();

    gl::Commands::clear(0.5f, 0.5f, 0.5f);

    while (WindowInstance::instance().is_active())
    {
        gl::Commands::clear(gl::color_buffer_bit);

        context->update();
        platform->update();
    }

    context->destroy();

    WindowInstance::instance().destroy();
    return 0;
}