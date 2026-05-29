# Vendored dans-util

Plain-file vendored copy of `dans-util` (https://github.com/Daniel-Sinkin/dans-util).

Source commit: 85fdf2a

Only `include/` and `src/` are vendored. dans-util's own bundled `vendor/dans-core`
was intentionally dropped: this project already provides dans-core, and the
`dans_util` target is built against that copy instead (forced via the `dans::core`
link in the top-level CMakeLists.txt). Not a git submodule, not consumed through
its own CMakeLists.txt.
