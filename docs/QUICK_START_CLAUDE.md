# Quick Start Guide for Claude

**READ THIS FIRST** when starting a new session!

---

## TL;DR - Essential Information

### What is this project?
Text-based adventure game in C++11 using Command Pattern

### Current Branch
`refactor/game-data-to-json` (migrating from XML to JSON)

### Build & Test
```bash
make clean && make              # Build
make test-integration           # Run tests (ALWAYS do this first!)
./main                         # Run game
```

### Most Recent Changes (2025-01-11)
- ✅ Fixed 4 critical segmentation faults
- ✅ Added integration test suite
- ✅ Extracted GameLoop class
- ✅ JSON migration completed

---

## Critical Things to Remember

### 🚨 Command Pattern Rules (PREVENTS SEGFAULTS!)

**CommandBuilder parameters MUST be pass-by-reference:**
```cpp
// ✅ CORRECT:
map<string,ICommand*> buildCommands(bool &continuar_loop,
                                    pScene &current_scene, ...)

// ❌ WRONG (causes segfault):
map<string,ICommand*> buildCommands(bool continuar_loop,
                                    pScene current_scene, ...)
```

**NEVER execute commands during building:**
```cpp
// ❌ WRONG:
mapComandos[s_ver]->execute();  // Don't do this in buildCommands()!
return mapComandos;

// ✅ CORRECT:
return mapComandos;  // Commands execute later via Invocador
```

**GameLoop MUST clear parameters:**
```cpp
// In GameLoop::processInput() at the START:
comando = "";
parametro1 = "";
parametro2 = "";
```

---

## File Locations (Most Important)

```
docs/
├── PROJECT_CONTEXT.md          ← Read this for architecture
├── DEVELOPMENT_WORKFLOW.md     ← Follow this for process
├── TECHNICAL_DEBT.md           ← Known issues to avoid
└── QUICK_START_CLAUDE.md       ← You are here

src/
├── patterns/command/           ← Command pattern (segfault prone!)
│   ├── operaciones.h           ← CommandBuilder is here
│   └── operaciones.cpp         ← Command implementations
├── manager/
│   ├── game_loop.{h,cpp}       ← Game loop (NEW, 2025-01)
│   └── manager.{h,cpp}         ← Main manager
└── tests/
    ├── README.md               ← Testing documentation
    ├── command_builder_test.cpp ← Tests CommandBuilder
    ├── movement_test.cpp        ← Tests movement commands
    └── game_loop_test.cpp       ← Tests game loop
```

---

## First Steps in a New Session

### 1. Context Check (30 seconds)
```bash
# Check current state
git status
git log --oneline -5

# Verify tests pass
make test-integration
```

### 2. Review Docs (2 minutes)
```bash
# If modifying commands:
cat docs/PROJECT_CONTEXT.md | grep -A 20 "Command Pattern"

# If fixing a bug:
cat docs/TECHNICAL_DEBT.md | grep "OPEN"

# If adding a feature:
cat docs/DEVELOPMENT_WORKFLOW.md | grep -A 10 "Adding a New"
```

### 3. Run Game Manually (30 seconds)
```bash
# Quick smoke test
echo -e "2\nnorte\neste\nver\nexit\n" | ./main

# Interactive test
./main
# Type: 2 (Español)
# Type: norte, este, oeste, sur, ver, inventario, exit
```

---

## Common Tasks

### Fix a Segmentation Fault
1. Run in gdb: `echo "input" | gdb -ex run -ex bt ./main`
2. Check backtrace location
3. **Most likely causes (in order):**
   - CommandBuilder params not pass-by-reference
   - Commands executing during building
   - Parameters not cleared in GameLoop
   - Null pointer dereference
4. Check `docs/PROJECT_CONTEXT.md` → "Critical Pitfalls"
5. Write a test that reproduces it
6. Fix, verify test passes

### Add a New Command
1. Define in `src/patterns/command/operaciones.h`
2. Implement in `src/patterns/command/operaciones.cpp`
3. Add to `CommandBuilder::buildCommands()`
4. Add test to `src/tests/command_builder_test.cpp`
5. Run: `make test-integration`

### Modify Game Data
1. Edit `gameData_es.json` AND `gameData_en.json` (keep in sync!)
2. Test: `make json_loader_test`
3. Run game manually to verify

---

## Red Flags (Stop and Think!)

### 🛑 If You See These, Double-Check:

**In Code:**
- `pScene current_scene` (not `pScene &current_scene`) in CommandBuilder
- `execute()` call inside `buildCommands()`
- Missing parameter clearing in `processInput()`
- `new` without corresponding `delete` (memory leak)
- Hardcoded strings (should be in JSON)

**In Testing:**
- Tests passing but game crashes → Integration tests missing coverage
- Segfault in movement commands → CommandBuilder params issue
- Commands not working → Check registration in builder map

**In Git:**
- Large diffs → Probably need to split into multiple commits
- Modified files unrelated to task → Scope creep
- `.vscode/` or `log.out` staged → Need .gitignore

---

## Quick Reference

### Test Commands
```bash
make test-integration           # All integration tests
make command_builder_test       # Specific test
./src/tests/command_builder_test  # Run test directly
```

### Game Commands (for testing)
```
norte, sur, este, oeste  # Movement
ver                      # Look
examinar <obj>          # Examine object
inventario              # Show inventory
exit                    # Quit
```

### Debug Commands
```bash
# Build with debug symbols (already default)
make clean && make

# Run in debugger
gdb ./main
(gdb) run
(gdb) bt          # After crash

# Check memory leaks
valgrind ./main
```

---

## Pitfall Examples (Learn from Recent Bugs)

### Bug 1: Dangling Pointer
```cpp
// ❌ CAUSED SEGFAULT:
map<string,ICommand*> buildCommands(bool &continuar_loop,
                                    pScene current_scene, ...)  // Pass by value!
{
    ICommand *c_norte = new Cardinal(&current_scene, ...);
    // &current_scene points to LOCAL variable
    // After function returns, pointer is DANGLING!
}

// ✅ FIX:
map<string,ICommand*> buildCommands(bool &continuar_loop,
                                    pScene &current_scene, ...)  // Pass by reference!
```

### Bug 2: Premature Execution
```cpp
// ❌ CAUSED SEGFAULT:
map<string,ICommand*> mapComandos = buildCommands(...);
// Inside buildCommands:
mapComandos[s_norte]->execute();  // Executes before game ready!
return mapComandos;

// ✅ FIX:
map<string,ICommand*> mapComandos = buildCommands(...);
// Commands execute ONLY via Invocador::exec() later
```

### Bug 3: Parameter Persistence
```cpp
// ❌ CAUSED BUG:
void processInput() {
    getline(cin, entrada_consola);
    // Parse into comando, parametro1, parametro2
    // But never clear them first!
    // Previous values persist!
}

// ✅ FIX:
void processInput() {
    comando = "";      // Clear first!
    parametro1 = "";
    parametro2 = "";
    getline(cin, entrada_consola);
    // Now parse...
}
```

---

## Success Checklist

Before saying "task complete":

- [ ] `make clean && make` succeeds
- [ ] `make test-integration` passes
- [ ] Manual game test works (no crashes)
- [ ] No new compiler warnings
- [ ] Changes committed with good message
- [ ] Docs updated if architecture changed
- [ ] Tests added for new functionality

---

## When in Doubt

1. **Check docs:** `docs/PROJECT_CONTEXT.md`
2. **Run tests:** `make test-integration`
3. **Test manually:** `./main`
4. **Check recent changes:** `git log --oneline -10`
5. **Review similar code:** Search for existing patterns

---

## Emergency Contacts (Files to Check)

| Problem | Check This File |
|---------|----------------|
| Segfault in movement | `src/patterns/command/operaciones.h` |
| Commands not working | `src/patterns/command/invocador.cpp` |
| Game loop issues | `src/manager/game_loop.cpp` |
| Data loading fails | `src/data/JSONGameDataLoader.cpp` |
| Tests failing | `src/tests/README.md` |
| Build broken | `Makefile` |

---

**Remember:** Tests first, code second. Small commits, frequent pushes. Document as you go.

**Last Updated:** 2025-01-11
