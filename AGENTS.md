# AGENTS.md - C++ Primer Learning Repository

## Overview
This is a C++ learning/practice repository based on C++ Primer. Code is organized by chapter (e.g., C02/, c03/). Uses C++20 standard with modern features like concepts and constexpr.

## Build Commands

### Compile Single File
```bash
g++ -g -O0 -std=c++20 -I/mnt/f/DevCpp/WGALIB <file.cpp> -o <file.o>
```

### Example
```bash
g++ -g -O0 -std=c++20 -I/mnt/f/DevCpp/WGALIB C02/prog1.cpp -o C02/prog1.o
```

### Run Compiled Program
```bash
./C02/prog1.o
```

### VS Code Build Task (from tasks.json)
- Use Ctrl+Shift+B to build current file
- Output: `${fileDirname}/${fileBasenameNoExtension}.o`

## Code Style Guidelines

### C++ Standard
- Use **C++20** standard
- Leverage modern features: concepts, constexpr, auto, range-based for loops

### Includes & Namespaces
- Place standard headers first, then custom headers
- Custom utility header: `#include "wga.h"` (located in repo root)
- Use `std::` prefix explicitly OR `using namespace std;` at file scope
- Avoid `using namespace` in headers

### Naming Conventions
- **Functions**: PascalCase for exported functions (e.g., `SwapAB`, `PrintInfo`)
- **Variables**: camelCase or snake_case
- **Classes**: PascalCase (e.g., `stringBuilder`)
- **Constants**: UPPER_SNAKE_CASE or PascalCase
- **Templates**: Single capital letter (e.g., `T`)

### Formatting
- Indent: 4 spaces (no tabs)
- Braces: Opening brace on same line for functions, new line for classes
- Line length: ~100 characters
- Comments: Mix of Chinese and English acceptable

### Key Patterns
1. **Prefer references over pointers** for parameter passing
2. **Use `const` correctness** - mark parameters and methods const when possible
3. **Leverage C++20 Concepts** for template constraints (see wga.h for Vector1D/Vector2D concepts)
4. **Error handling**: Use exceptions with try-catch blocks
5. **Memory**: Prefer smart pointers; use RAII principles

### Template Guidelines
- Use `if constexpr` for compile-time type branching
- Apply concepts to constrain template parameters
- Example:
```cpp
template <typename T>
    requires Vector1D<T>
void ProcessVector(T& v) { ... }
```

### Comments
- Use Doxygen-style for function documentation:
```cpp
/**
 * @brief Brief description
 * @details Detailed explanation
 */
```
- Inline comments in Chinese acceptable for learning purposes

## Project Structure
```
/mnt/f/DevCpp/CppPrimer/
├── wga.h              # Custom utility header with templates
├── C02/               # Chapter 2 exercises
├── c03/               # Chapter 3 exercises
├── .vscode/           # VS Code configuration
└── [other chapters]/
```

## External Dependencies
- **WGALIB**: `/mnt/f/DevCpp/WGALIB` - external library include path
- Compiler: g++ with C++20 support

## Testing
No formal test framework. Programs are individual exercises:
1. Compile with g++
2. Run and verify output manually
3. Some programs read from stdin (EOF: Ctrl+D on Linux/macOS, Ctrl+Z on Windows)

## Git
- Use meaningful commit messages in English or Chinese
- Ignore: *.o, *.exe, .vscode/settings.json, .vscode/launch.json

## Notes for AI Agents
- This is a learning repository - code may contain experimental patterns
- Don't refactor for "production quality" unless asked
- Preserve Chinese comments when editing
- wga.h contains shared utilities - update carefully as multiple files depend on it
- When adding new exercises, follow existing chapter folder naming (C02/, c03/, etc.)
