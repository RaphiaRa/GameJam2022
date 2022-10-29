#include "SdlError.h"

using sdl::ErrorCategory;

const char* ErrorCategory::name() const noexcept
{
    return "SdlError";
}

std::string ErrorCategory::message(int c) const
{
    (void)(c);
    return std::string("Sdl Error");
}

std::error_condition ErrorCategory::default_error_condition(int c) const noexcept
{
    return std::error_condition(c, *this);
}

const std::error_category& sdl::errorCategory()
{
    // The category singleton
    static ErrorCategory instance;
    return instance;
}
