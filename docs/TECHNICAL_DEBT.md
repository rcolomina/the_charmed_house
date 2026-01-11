# Technical Debt Tracker

This document tracks known issues, workarounds, and areas needing improvement.

---

## Critical (Causes Bugs/Crashes)

### RESOLVED ✅

#### 1. Segmentation Fault in Movement Commands
- **Status:** RESOLVED (2025-01-11)
- **Impact:** Game crashed on any movement command
- **Root Cause:** Dangling pointers/references in CommandBuilder
- **Fix:** Changed parameters to pass-by-reference in buildCommands()
- **Files:** src/patterns/command/operaciones.h
- **Tests Added:** command_builder_test.cpp, movement_test.cpp

#### 2. Premature Command Execution
- **Status:** RESOLVED (2025-01-11)
- **Impact:** Commands executing during initialization
- **Root Cause:** execute() calls in CommandBuilder::buildCommands()
- **Fix:** Removed execute() calls from builder
- **Files:** src/patterns/command/operaciones.h:254-256
- **Tests Added:** command_builder_test.cpp

#### 3. Parameter Persistence Bug
- **Status:** RESOLVED (2025-01-11)
- **Impact:** Previous command parameters leaked to next command
- **Root Cause:** GameLoop not clearing parameters between inputs
- **Fix:** Added parameter clearing in processInput()
- **Files:** src/manager/game_loop.cpp:68-70
- **Tests Added:** game_loop_test.cpp

### OPEN 🔴

#### 4. Memory Leaks in Command Objects
- **Impact:** HIGH - Memory grows during gameplay
- **Description:** Commands created with `new` in buildCommands() but never deleted
- **Location:** src/patterns/command/operaciones.h:220-234
- **Reproduction:** Play game for extended period, check memory usage
- **Potential Fix:**
  - Use smart pointers (shared_ptr<ICommand>)
  - Or implement destructor in Manager/GameLoop to clean up
- **Workaround:** None (short gaming sessions don't show issue)
- **Estimated Effort:** 4 hours
- **Priority:** HIGH

```cpp
// Current code (leaks memory):
ICommand *c_norte = new Cardinal(&current_scene,s_norte,primera_entrada);
mapComandos[s_norte] = c_norte;
// Never deleted!

// Proposed fix:
shared_ptr<ICommand> c_norte = make_shared<Cardinal>(...);
mapComandos[s_norte] = c_norte;
```

---

## High Priority (Affects Quality)

### 5. Constructor Initialization Order Warnings
- **Impact:** MEDIUM - Compiler warnings, potential UB
- **Description:** Members initialized before base class in command constructors
- **Location:** All command classes in src/patterns/command/operaciones.h
- **Reproduction:** Compile with `-Wall`
- **Example:**
```cpp
// Current (wrong order):
Exit(bool &continuar_loop):
    continuar_loop(continuar_loop),  // Member first
    ICommand(s_exit){}                // Base class second

// Should be:
Exit(bool &continuar_loop):
    ICommand(s_exit),                 // Base class first
    continuar_loop(continuar_loop){}  // Member second
```
- **Estimated Effort:** 2 hours (fix all command classes)
- **Priority:** MEDIUM

### 6. No CI/CD Pipeline
- **Impact:** HIGH - Manual testing only, regressions possible
- **Description:** No automated testing on commits/PRs
- **Proposed Solution:**
  - GitHub Actions workflow
  - Run `make test-integration` on every push
  - Build check on PRs
- **Estimated Effort:** 4 hours
- **Priority:** HIGH

### 7. Incomplete Internationalization
- **Impact:** MEDIUM - Mixed languages in codebase
- **Description:**
  - Game data has English/Spanish (✓)
  - Code comments mixed English/Spanish
  - Some hardcoded Spanish strings in C++ code
- **Locations:**
  - src/patterns/command/invocador.cpp (Spanish error messages)
  - src/manager/game_loop.cpp (Spanish messages)
- **Proposed Solution:**
  - Move ALL user-facing strings to JSON
  - English-only code comments
- **Estimated Effort:** 8 hours
- **Priority:** MEDIUM

---

## Medium Priority (Code Quality)

### 8. Global State in Parameters
- **Impact:** LOW - Makes testing harder
- **Description:** Command strings defined as static const in parametros.h
- **Location:** src/manager/parametros.h
- **Issue:** Global state, hard to mock in tests
- **Proposed Solution:**
  - Load from configuration
  - Or use enum class with string mapping
- **Estimated Effort:** 6 hours
- **Priority:** LOW

### 9. Inconsistent Naming Conventions
- **Impact:** LOW - Readability issue
- **Description:**
  - Some variables use snake_case: `escena_actual`, `primera_entrada`
  - Some use camelCase: `continuar_loop`, `eventsQueue`
  - Files use snake_case: `game_loop.cpp`
- **Decision Needed:** Pick one standard (recommend snake_case for C++)
- **Estimated Effort:** 2 hours (automated refactor)
- **Priority:** LOW

### 10. No Unit Tests for Individual Commands
- **Impact:** MEDIUM - Integration tests only
- **Description:**
  - Have integration tests (✓)
  - Missing unit tests for individual command logic
  - Hard to test edge cases in isolation
- **Proposed Solution:**
  - Add unit tests for each command class
  - Mock dependencies (Scene, Inventario, etc.)
- **Estimated Effort:** 16 hours
- **Priority:** MEDIUM

### 11. Commented-Out Code
- **Impact:** LOW - Code cleanliness
- **Description:** Many files have old commented code
- **Locations:**
  - src/manager/manager.cpp (old CommandBuilder code)
  - src/patterns/command/invocador.cpp (old bad word checking)
  - Multiple test files
- **Decision:** Remove if not needed, or document why kept
- **Estimated Effort:** 2 hours
- **Priority:** LOW

---

## Low Priority (Nice to Have)

### 12. .gitignore Incomplete
- **Impact:** LOW - Git noise
- **Description:** Missing entries for:
  - `.vscode/`
  - `log.out`
  - `*.o` files (though make clean removes them)
  - Test executables in `src/tests/`
- **Proposed Fix:**
```gitignore
# IDE
.vscode/
.idea/

# Build artifacts
*.o
*.gch
main
log.out

# Tests
src/tests/*_test
!src/tests/*_test.cpp
```
- **Estimated Effort:** 10 minutes
- **Priority:** LOW

### 13. Documentation Language Inconsistency
- **Impact:** LOW - Developer experience
- **Description:**
  - Some docs in Spanish: docs/ArquitecturaEscenas.txt
  - Some in English: src/tests/README.md
  - Comments mixed
- **Decision:** English as primary language for code/docs?
- **Estimated Effort:** Variable (depends on scope)
- **Priority:** LOW

### 14. No Doxygen/API Documentation
- **Impact:** LOW - Onboarding time
- **Description:** No generated API documentation
- **Proposed Solution:**
  - Add Doxygen comments to public APIs
  - Generate HTML documentation
- **Estimated Effort:** 12 hours
- **Priority:** LOW

### 15. Build Warnings
- **Impact:** LOW - Code quality signal
- **Description:** Many -Wreorder warnings during compilation
- **Root Cause:** Constructor initialization order (see #5)
- **Fix:** Same as #5
- **Priority:** LOW (same as #5)

---

## Backlog (Future Considerations)

### 16. Modernize to C++17/20
- **Current:** C++11
- **Benefits:**
  - std::optional for nullable returns
  - std::filesystem for file operations
  - Structured bindings
  - std::string_view
- **Effort:** Large (need to check compatibility)
- **Priority:** FUTURE

### 17. Add Save/Load Game State
- **Description:** No persistence currently
- **Proposed:**
  - Save game state to JSON
  - Load on restart
- **Effort:** Medium-Large
- **Priority:** FEATURE REQUEST

### 18. Add More Game Content
- **Description:** Limited scenes/items currently
- **Proposed:**
  - More scenes in JSON
  - More items and puzzles
  - More complex event system
- **Effort:** Variable (content creation)
- **Priority:** FEATURE REQUEST

### 19. Web/GUI Frontend
- **Description:** CLI only currently
- **Proposed:**
  - Web interface (C++ backend + web frontend)
  - Or native GUI (Qt/GTK)
- **Effort:** Large
- **Priority:** FUTURE

---

## Workarounds Currently in Place

### Scene Pointer Management
- **Issue:** ppScene (pointer to pointer) is confusing
- **Workaround:** Document clearly in PROJECT_CONTEXT.md
- **Proper Fix:** Refactor to use references or smart pointers
- **Status:** Workaround acceptable for now

### Language Selection
- **Issue:** Must select language on every run
- **Workaround:** Default to Spanish if invalid input
- **Proper Fix:** Save preference, environment variable, or CLI flag
- **Status:** Low priority improvement

---

## Recently Added Debt

### GameLoop Function Binding
- **Added:** 2025-01-11
- **Location:** src/manager/manager.cpp:90-95
- **Description:** Uses std::bind for update functions
- **Alternative:** Lambdas might be cleaner
- **Reason:** Quick refactor to extract GameLoop
- **Priority:** LOW (works fine, just not idiomatic)

```cpp
// Current:
auto update_objects_func = std::bind(&Manager::actualizar_objetos, this);

// Could be:
auto update_objects_func = [this]() { actualizar_objetos(); };
```

---

## How to Use This Document

### When Adding Debt
1. Add item with OPEN 🔴 status
2. Describe impact and location
3. Propose fix if known
4. Estimate effort
5. Assign priority

### When Fixing Debt
1. Move item to RESOLVED ✅ section
2. Document fix applied
3. Note files changed
4. Add tests if applicable
5. Update date

### Priority Levels
- **CRITICAL:** Fix immediately (causes crashes/data loss)
- **HIGH:** Fix soon (affects quality/reliability)
- **MEDIUM:** Fix when convenient (code quality issue)
- **LOW:** Fix eventually (nice to have)
- **FUTURE:** Consider for major version

---

**Last Updated:** 2025-01-11
**Last Review:** 2025-01-11
**Items Resolved This Month:** 3
**Items Added This Month:** 15 (initial documentation)
