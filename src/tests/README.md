# Integration Tests

This directory contains integration tests for The Charmed House game. These tests are designed to catch critical bugs before they make it into production.

## Test Suite

### 1. CommandBuilder Test (`command_builder_test.cpp`)
Tests that would have caught the segmentation fault bugs from the recent refactoring:

**What it tests:**
- Commands can be built without premature execution (bug: commands executing during construction)
- References are properly maintained (bug: dangling references in `continuar_loop`)
- Pointers are properly maintained (bug: dangling pointers in `current_scene`)
- Commands can be executed after building
- Exit command properly modifies the `continuar_loop` reference
- Commands work correctly with cleared parameters

**Covers bugs:**
- Premature command execution in `CommandBuilder::buildCommands()`
- Dangling reference in `continuar_loop` parameter
- Dangling pointer in `current_scene` parameter

### 2. Movement Test (`movement_test.cpp`)
Tests Cardinal movement commands to prevent segmentation faults:

**What it tests:**
- Cardinal commands can be created without crashing
- Movement commands execute without segmentation faults
- Scene transitions work correctly
- Invalid movements are handled gracefully
- The `primera_entrada` flag is set correctly after movement
- Multiple consecutive movements work correctly
- Commands remain functional after scene transitions

**Covers bugs:**
- Segmentation faults when executing movement commands
- Scene pointer invalidation
- State corruption during movement

### 3. GameLoop Test (`game_loop_test.cpp`)
Tests the game loop and command processing:

**What it tests:**
- Input processing clears previous parameters between commands
- Commands execute correctly in loop context
- Game state is maintained across iterations
- Parameter clearing works as expected
- Commands with and without parameters work correctly
- State persists correctly across commands
- Exit command works correctly
- Rapid consecutive command execution (stress test)

**Covers bugs:**
- Parameter clearing bug (parameters persisting between commands)
- State corruption in game loop
- Memory issues with rapid command execution

## Running Tests

### Run all integration tests:
```bash
make test-integration
```

### Run individual tests:
```bash
make command_builder_test
./src/tests/command_builder_test

make movement_test
./src/tests/movement_test

make game_loop_test
./src/tests/game_loop_test
```

### Run all tests (unit + integration):
```bash
make test-all
```

## Test Output

Tests use a simple assertion-based framework with clear output:
- `[PASS]` - Test passed successfully
- `[FAIL]` - Test failed
- `[TEST]` - Currently running test
- `[INFO]` - Informational message

## Adding New Tests

When adding new features or fixing bugs, add corresponding integration tests:

1. Create a new `*_test.cpp` file in `src/tests/`
2. Include necessary headers and test the full integration of components
3. Add a target in the Makefile following the existing pattern
4. Add the test to the `test-integration` target
5. Document the test in this README

## Continuous Integration

These tests should be run:
- Before committing code changes
- Before merging pull requests
- As part of CI/CD pipeline

## Test Philosophy

Integration tests focus on:
- **Real-world scenarios**: Testing how components work together
- **Bug prevention**: Tests are written to prevent specific bugs from recurring
- **Fast feedback**: Tests run quickly to encourage frequent execution
- **Clear failures**: When tests fail, it's clear what went wrong

## Recent Bugs Prevented

The current test suite would have prevented the following bugs:
1. **Premature Command Execution** - Commands executing during `CommandBuilder` construction
2. **Dangling References** - Invalid references in `continuar_loop` parameter
3. **Dangling Pointers** - Invalid pointers in `current_scene` parameter
4. **Parameter Persistence** - Command parameters not clearing between inputs

## Maintenance

- Update tests when refactoring code
- Add new tests for new features
- Keep tests fast and focused
- Document what each test prevents
