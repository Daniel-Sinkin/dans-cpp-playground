// include/dans/version.hpp

#ifndef DANS_CORE_INCLUDE_DANS_VERSION_HPP
#define DANS_CORE_INCLUDE_DANS_VERSION_HPP
#pragma once

#include <dans/types.hpp>

// Single source of truth for the dans-core version. CMake parses these three
// macros to set the project version, so they travel with vendored headers.
#define DANS_CORE_VERSION_MAJOR 0
#define DANS_CORE_VERSION_MINOR 3
#define DANS_CORE_VERSION_PATCH 0

#define DANS_CORE_VERSION_ENCODE(major, minor, patch) ((major) * 10000 + (minor) * 100 + (patch))

#define DANS_CORE_VERSION \
    DANS_CORE_VERSION_ENCODE(DANS_CORE_VERSION_MAJOR, DANS_CORE_VERSION_MINOR, DANS_CORE_VERSION_PATCH)

#define DANS_CORE_VERSION_STRINGIZE_(x) #x
#define DANS_CORE_VERSION_STRINGIZE(x) DANS_CORE_VERSION_STRINGIZE_(x)

#define DANS_CORE_VERSION_STRING                            \
    DANS_CORE_VERSION_STRINGIZE(DANS_CORE_VERSION_MAJOR)    \
    "." DANS_CORE_VERSION_STRINGIZE(DANS_CORE_VERSION_MINOR) \
    "." DANS_CORE_VERSION_STRINGIZE(DANS_CORE_VERSION_PATCH)

namespace dans {
struct Version {
    u32 major{};
    u32 minor{};
    u32 patch{};
};

inline constexpr Version k_core_version{
    .major = DANS_CORE_VERSION_MAJOR,
    .minor = DANS_CORE_VERSION_MINOR,
    .patch = DANS_CORE_VERSION_PATCH,
};

inline constexpr u32 k_core_version_encoded{DANS_CORE_VERSION};
} // namespace dans

#endif // DANS_CORE_INCLUDE_DANS_VERSION_HPP
