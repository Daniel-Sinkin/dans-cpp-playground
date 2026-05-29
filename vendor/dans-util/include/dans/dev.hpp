// include/dans/dev.hpp
#pragma once
// Externals
#include <dans/development_markers.hpp>
// StdLib
#include <concepts>  // IWYU pragma: keep
#include <string_view>
#include <utility>
//

#ifndef DANS_DEV_HPP
#    define DANS_DEV_HPP

namespace dans::dev
{

#    if defined(DANS_DEV_DEFERABLE_CAN_THROW)
template <typename F>
concept Deferable = std::invocable<F>;
#    else
template <typename F>
concept Deferable = std::is_nothrow_invocable_v<F>;
#    endif

[[noreturn]] def panic_impl(std::string_view msg, std::string_view file, int line) -> void;

template <Deferable F>
class Defer
{
  public:
    explicit Defer(F func) : func_{std::move(func)}
    {
    }
#    if defined(DANS_DEV_DEFERABLE_CAN_THROW)
    ~Defer() noexcept(false)
#    else
    ~Defer() noexcept(true)
#    endif
    {
        func_();
    }
    Defer(const Defer&) = delete;
    Defer(Defer&&) = delete;
    def operator=(const Defer&)->Defer& = delete;
    def operator=(Defer&&)->Defer& = delete;

  private:
    F func_;
};

template <Deferable F>
Defer(F) -> Defer<F>;

}  // namespace dans::dev

#    define DANS_PANIC(msg) ::dans::dev::panic_impl((msg), __FILE__, __LINE__)

#endif  // DANS_DEV_HPP
