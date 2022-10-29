#ifndef SDL_ERROR_H
#define SDL_ERROR_H
#include <system_error>

namespace sdl
{
class ErrorCategory : public std::error_category {
  public:
    virtual const char* name() const noexcept override final;

    virtual std::string message(int c) const override final;

    virtual std::error_condition default_error_condition(int c) const noexcept override final;
};

const std::error_category& errorCategory();
} // namespace sdl
#endif
