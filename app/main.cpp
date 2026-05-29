// app/main.cpp
// Externals
#include <dans/chrono.hpp>
#include <dans/dev.hpp>
#include <dans/development_markers.hpp>
#include <dans/types.hpp>
// StdLib
#include <print>
//

def main() -> int
{
    using namespace dans;
    using namespace dans::dev;

    mut auto* arr = new int[16zu]{};
    std::println("Allocated");
    const Defer _{[&]() noexcept { delete[] arr; }};

    arr[5zu] = 10;
    std::println("The 5th element it {}", arr[5]);
}
