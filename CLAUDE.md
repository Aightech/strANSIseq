# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Modular Library Ecosystem

This project is part of a larger ecosystem of reusable C++ library blocks (networking, debugging, etc.). All projects share the same CMakeLists.txt pattern and use git submodules for dependencies.

### Recursive Build Mechanism

The CMake system automatically discovers and builds subprojects:

1. **`cmake/PullingLibs.cmake`** scans `lib/` directory for subdirectories
2. Each subdirectory with a CMakeLists.txt is added via `add_subdirectory()`
3. Subprojects run the same mechanism recursively (unlimited nesting)
4. Library names accumulate in `EXTRA_LIBS` and are linked to the parent

**Key files:**
- `CMakeConfig.cmake` - Project name and version (`EXEC_NAME`, `PROJECT_VERSION`)
- `cmake/PullingLibs.cmake` - Recursive subproject loader
- `cmake/CMakeFunctions.cmake` - Helper macros (`subdirlist`, `subproject_version`)

**Adding a dependency:** Add a git submodule to `lib/` - the build system handles the rest.

## Build Commands

```bash
# First time setup (initializes submodules)
./scripts/setup.sh

# Build the library
cd build
cmake .. && make

# Build with examples (demo CLI app)
cmake .. -DBUILD_EXAMPLES=ON && make

# Run demo app
./strANSIseq -h
```

**Note:** CMake will fail with a clear error if submodules aren't initialized. See `DEPENDENCIES.md` for submodule workflow.

The build produces both shared (`strANSIseq.3.10`) and static (`strANSIseq`) library targets.

## Architecture

This is a C++ library providing ANSI escape sequence utilities for formatted terminal output (colors, styles, cursor movement).

### Core Components (namespace `ESC`)

**Enums** in `include/strANSIseq.hpp`:
- `FORMAT` - ANSI codes for text styling (BOLD, DIM, ITALIC, UNDERLINE, BLINK_SLOW/FAST, REVERSE, HIDDEN, STRIKE) and colors (FG_*/BG_* for foreground/background)

**Free Functions**:
- `fstr(string, {formats...})` - Apply ANSI formatting to a string
- `fstr_n(value, {formats...})` - Format numeric values
- `fstr_link(url, text)` - Create clickable terminal hyperlinks
- `move_up/down/left/right(n)` - Cursor movement
- `move_to(line, col)` - Absolute cursor positioning
- `get_pos(&y, &x)` - Query current cursor position

**CLI Base Class** (`ESC::CLI`):
- Base class for applications needing formatted logging
- Constructor: `CLI(int verbose, std::string id)` - verbose level controls output, id is displayed prefix
- `log(msg)` / `logln(msg)` - Print with optional indentation
- `log_error(msg)` - Print to stderr with red ERROR prefix
- `set_verbose(level)` - Adjust verbosity at runtime
- Color-coded prefix based on verbose level (FG_YELLOW + verbose)

### Usage Pattern

Other libraries inherit from `ESC::CLI` for consistent logging:
```cpp
class MyClass : public ESC::CLI {
public:
    MyClass() : ESC::CLI(1, "MyClass") {}
    void do_something() {
        logln("Starting operation...");
        // ... work ...
        logln(ESC::fstr("Done!", {ESC::FG_GREEN}));
    }
};
```

### Dependencies

None - this is a leaf library with no submodules.

### Platform Support

Windows (via windows.h), Linux (POSIX termios), macOS (POSIX termios).

**Note:** zsh (macOS default) does not fully support all ANSI sequences; use bash for full functionality.

## Code Style

- Allman braces, 4-space indentation
- snake_case for methods, PascalCase for classes, m_ prefix for members
- Strict compilation: `-Wall -Wextra -Wpedantic -Werror`
