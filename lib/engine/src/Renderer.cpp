#include "SdlRenderer.h"

#include <engine/Renderer.h>

using engine::Renderer;

std::unique_ptr<Renderer> Renderer::create(Backend backend, const Area& winArea, std::string_view title, unsigned int flags)
{
    switch (backend) {
        case Backend::sdl:
            return std::make_unique<sdl::Renderer>(winArea, title, flags);
            break;
        default:
            // throw some exception here
            break;
    }
    return nullptr;
}
