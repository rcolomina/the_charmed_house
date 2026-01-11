# The Charmed House - Project Context

## Quick Start for Claude

This document provides essential context to avoid re-analyzing the codebase on each session.

---

## Project Overview

**Type:** Text-based adventure game (interactive fiction)
**Language:** C++11
**Build System:** Make
**Architecture:** Command pattern with Factory pattern for scene/item creation

### Key Directories
```
src/
├── core/           # Domain models (Escenario, Objeto, Inventario, etc.)
├── manager/        # Game manager and game loop
├── patterns/       # Design patterns (Command, Factory)
│   ├── command/    # Command pattern implementation
│   └── factory/    # Factory for creating game objects
├── data/           # Data loading (JSON/XML)
├── events/         # Event system
└── tests/          # Unit and integration tests

lib/                # Utility libraries (logger, colormod, etc.)
3rdParty/           # Third-party dependencies (json, tinyxml)
```

---

## Critical Architecture Patterns

### 1. Command Pattern (MOST IMPORTANT!)
- **Location:** `src/patterns/command/`
- **Key Classes:**
  - `ICommand` - Base interface for all commands
  - `Cardinal`, `Ver`, `Examinar`, `Coger`, etc. - Specific commands
  - `Invocador` - Command invoker
  - `CommandBuilder` - Builds and registers all commands

**⚠️ CRITICAL PITFALLS (Caused recent segfaults):**

1. **Pass-by-reference required for:**
   - `continuar_loop` - Controls game loop
   - `current_scene` (pScene) - Pointer to current scene
   - `parametro1`, `parametro2` - Command parameters
   - `primera_entrada` - First entry flag

2. **NEVER execute commands during construction/building**
   - Commands should only execute when explicitly invoked via `Invocador::exec()`

3. **Scene pointer is ppScene (pointer to pointer)**
   - `Cardinal` commands modify `*escena_actual` to change scenes
   - Must use `&current_scene` when building commands

### 2. Factory Pattern
- **Location:** `src/patterns/factory/`
- **Purpose:** Creates game objects (scenes, items) from data files
- **Key Classes:**
  - `FactoryGame` - Main factory
  - `IGameDataLoader` - Interface for data sources
  - `JSONGameDataLoader` - JSON data implementation

### 3. Game Loop
- **Location:** `src/manager/game_loop.{h,cpp}`
- **Responsibilities:**
  - Process user input
  - Parse commands and parameters
  - Execute commands via Invocador
  - Update game state

**⚠️ CRITICAL:** Must clear `comando`, `parametro1`, `parametro2` before each input!

---

## Common Data Types

```cpp
typedef Escenario* pScene;          // Pointer to scene
typedef Escenario** ppScene;        // Pointer to scene pointer (used in commands)
typedef Objeto* pItem;              // Pointer to item
```

---

## Recent Major Changes

### JSON Migration (2025-01)
- Migrated from XML to JSON for game data
- Added `JSONGameDataLoader` class
- Created `gameData_es.json` and `gameData_en.json`
- Language selection menu in main

### Critical Bug Fixes (2025-01)
Fixed 4 segmentation faults:
1. Premature command execution in `CommandBuilder::buildCommands()`
2. Dangling reference in `continuar_loop` (was pass-by-value)
3. Dangling pointer in `current_scene` (was pass-by-value)
4. Parameters not cleared between commands in GameLoop

### GameLoop Refactoring (2025-01)
- Extracted game loop from Manager into GameLoop class
- Better separation of concerns

### Integration Tests Added (2025-01)
- `command_builder_test.cpp`
- `movement_test.cpp`
- `game_loop_test.cpp`
- See `src/tests/README.md` for details

---

## Known Issues & Technical Debt

### High Priority
- [ ] Constructor initialization order warnings (member initialized before base class)
- [ ] No unit tests for individual commands
- [ ] No CI/CD pipeline
- [ ] Memory leaks: Commands allocated with `new` but never deleted
- [ ] Hardcoded strings in Spanish (some i18n work done, not complete)

### Medium Priority
- [ ] Global state in `parametros.h` (command strings as static constants)
- [ ] Mixed English/Spanish in code comments
- [ ] Inconsistent naming conventions (some snake_case, some camelCase)
- [ ] `.vscode/` and `log.out` not in `.gitignore`

### Low Priority
- [ ] Old commented-out code in many files
- [ ] Some TODO comments in codebase
- [ ] Documentation mostly in Spanish

---

## Development Workflow

### Before Making Changes

1. **Read this document first!**
2. Check `docs/TECHNICAL_DEBT.md` for known issues
3. Run existing tests: `make test-integration`
4. Understand the command pattern (avoid recent bugs)

### Making Changes

1. **Follow pass-by-reference rules** for CommandBuilder
2. **Never execute commands during building**
3. **Always clear parameters** in game loop
4. Add integration tests for new commands
5. Run tests before committing

### Before Committing

```bash
# Build
make clean && make

# Run integration tests
make test-integration

# Test the game manually
echo -e "2\nnorte\neste\nsur\noeste\nver\nexit\n" | ./main

# Check for crashes
# If segfault, check:
#   1. CommandBuilder parameters (pass-by-reference?)
#   2. Premature execution in builder?
#   3. Parameter clearing in GameLoop?
```

### Commit Message Format
```
<type>: <short description>

<detailed description>

<bullet points of changes>

Co-Authored-By: Claude Sonnet 4.5 <noreply@anthropic.com>
```

---

## Build System

### Main Targets
```bash
make              # Build main executable
make clean        # Clean objects and executable
make test         # Build all tests
make test-integration  # Run integration tests
make test-all     # Run all tests
```

### Key Variables
- `SOURCES` - All .cpp files except tests
- `OBJECTS` - Compiled .o files
- `OBJECTSTEST` - Objects for tests (excludes main.cpp)

---

## Testing Strategy

### Integration Tests (Required)
Location: `src/tests/`

**When to add tests:**
- Adding new commands → Add to existing movement_test or create new test
- Modifying CommandBuilder → Update command_builder_test
- Modifying GameLoop → Update game_loop_test

**Test naming:** `<feature>_test.cpp`

### Running Tests
```bash
make test-integration     # Fast, runs integration tests only
make test-all            # Comprehensive, runs everything
```

---

## Quick Reference: Common Commands

### Game Commands (for testing)
```
norte, sur, este, oeste  # Movement
ver                      # Look around
examinar <object>        # Examine object
coger <object>          # Pick up object
tirar <object>          # Pull object
inventario              # Show inventory
exit/salir              # Exit game
```

### Available Scenes (from gameData_es.json)
- Front of House (starting location)
- Various rooms (loaded from JSON)

---

## Files That Change Together

When modifying commands:
- `src/patterns/command/operaciones.h` (command definitions)
- `src/patterns/command/operaciones.cpp` (command implementations)
- `src/tests/command_builder_test.cpp` (tests)
- `src/tests/movement_test.cpp` (if movement commands)

When modifying game data:
- `gameData_es.json` and `gameData_en.json` (both languages)
- `src/data/JSONGameDataLoader.cpp` (if schema changes)

When modifying game loop:
- `src/manager/game_loop.{h,cpp}`
- `src/tests/game_loop_test.cpp`

---

## Quick Debugging Tips

### Segmentation Fault in Movement Commands?
1. Check `CommandBuilder::buildCommands()` - are params pass-by-reference?
2. Check if commands execute during building (they shouldn't)
3. Run in gdb: `gdb ./main` → `run` → `bt` for backtrace

### Commands Not Working?
1. Check if command is registered in `CommandBuilder::buildCommands()`
2. Check `Invocador::exec()` is finding the command in map
3. Verify command ID matches string in `parametros.h`

### Parameters Persisting?
1. Check `GameLoop::processInput()` clears `comando`, `parametro1`, `parametro2`
2. Happens at line 68-70 in game_loop.cpp

---

## Contact Points for Deep Dives

If you need to understand a specific area:

- **Command System:** Start at `src/patterns/command/operaciones.h`
- **Factory System:** Start at `src/patterns/factory/factory.h`
- **Data Loading:** Start at `src/data/IGameDataLoader.h`
- **Game Loop:** Start at `src/manager/game_loop.cpp`
- **Scene Graph:** Start at `src/core/escenario.h`

---

## Success Criteria Checklist

Before marking any task complete:

- [ ] Code builds without errors (`make clean && make`)
- [ ] Integration tests pass (`make test-integration`)
- [ ] Manual testing shows no segfaults
- [ ] No new compiler warnings introduced
- [ ] Tests added for new functionality
- [ ] Technical debt documented if not fixed
- [ ] This document updated if architecture changes

---

**Last Updated:** 2025-01-11
**Last Major Change:** Added integration test suite and fixed segmentation faults
