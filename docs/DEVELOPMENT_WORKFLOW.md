# Development Workflow Checklist

This checklist ensures consistent, high-quality contributions and prevents common bugs.

---

## Starting a New Task

### 1. Context Setup (2 minutes)
```bash
[ ] Read docs/PROJECT_CONTEXT.md
[ ] Review docs/TECHNICAL_DEBT.md for known issues
[ ] Check current branch: git branch -vv
[ ] Pull latest: git pull origin <branch>
[ ] Run tests to ensure baseline: make test-integration
```

### 2. Understanding Requirements (5 minutes)
```bash
[ ] What is the goal?
[ ] Which components are affected?
[ ] Are there existing tests I can reference?
[ ] Are there similar features already implemented?
[ ] What could break? (Check PROJECT_CONTEXT.md for pitfalls)
```

### 3. Planning (5 minutes)
```bash
[ ] List files that need to change
[ ] Identify tests that need updating/adding
[ ] Consider backwards compatibility
[ ] Review command pattern rules if touching commands
[ ] Document approach before coding
```

---

## During Development

### Code Quality Checks
```bash
[ ] Follow existing code style and patterns
[ ] Use pass-by-reference for CommandBuilder parameters
[ ] Never execute commands during construction/building
[ ] Clear parameters between command executions
[ ] Add TODO comments for known limitations
[ ] Remove commented-out code (or document why it's kept)
[ ] Use meaningful variable names
```

### Command Pattern Checklist (CRITICAL)
If modifying anything in `src/patterns/command/`:

```bash
[ ] Are all CommandBuilder params pass-by-reference?
    - bool &continuar_loop (NOT bool continuar_loop)
    - pScene &current_scene (NOT pScene current_scene)
    - string &parametro1, &parametro2
    - bool &primera_entrada

[ ] No execute() calls in buildCommands()?
[ ] Commands only execute via Invocador::exec()?
[ ] Cardinal commands use &current_scene (ppScene)?
[ ] New commands added to CommandBuilder map?
[ ] Command IDs match strings in parametros.h?
```

### GameLoop Checklist
If modifying `src/manager/game_loop.cpp`:

```bash
[ ] Parameters cleared in processInput()?
    - comando = ""
    - parametro1 = ""
    - parametro2 = ""
[ ] State updates happen after command execution?
[ ] No infinite loops possible?
```

### Testing During Development
```bash
[ ] Write test FIRST (TDD preferred)
[ ] Run test (should fail): make <test_name>
[ ] Implement feature
[ ] Run test (should pass): make <test_name>
[ ] Run all integration tests: make test-integration
[ ] Manual smoke test: echo "commands" | ./main
```

---

## Before Committing

### Build & Test Verification (5 minutes)
```bash
[ ] Clean build succeeds:
    make clean && make

[ ] No new compiler warnings

[ ] Integration tests pass:
    make test-integration

[ ] Manual testing works:
    echo -e "2\nnorte\neste\nver\nexit\n" | ./main
    (No segfaults, commands work as expected)
```

### Code Review Self-Check (5 minutes)
```bash
[ ] Only relevant files modified?
    git status

[ ] No debug code left in?
    - No cout debug statements
    - No commented test code
    - No hardcoded test data

[ ] New tests added for new functionality?

[ ] Tests cover edge cases?
    - Null/empty inputs
    - Invalid commands
    - Boundary conditions

[ ] Documentation updated?
    - PROJECT_CONTEXT.md if architecture changed
    - TECHNICAL_DEBT.md if debt added
    - src/tests/README.md if tests added
```

### Commit Preparation (3 minutes)
```bash
[ ] Stage only relevant files:
    git add <files>

[ ] Write descriptive commit message:
    - What changed (imperative mood)
    - Why it changed
    - What bugs it fixes
    - Reference issues/PRs

[ ] Run final check:
    git diff --staged  # Review changes
```

---

## Commit Message Template

```
<type>: <short summary in imperative mood>

<Detailed explanation of what and why>

## Changes
- Change 1
- Change 2
- Change 3

## Testing
- Test scenario 1
- Test scenario 2

## Related
- Fixes #<issue_number>
- See also: #<related_pr>

Co-Authored-By: Claude Sonnet 4.5 <noreply@anthropic.com>
```

**Types:** fix, feat, refactor, test, docs, chore

---

## Creating a Pull Request

### Pre-PR Checklist (5 minutes)
```bash
[ ] All commits follow message template?
[ ] Branch up to date with master?
    git fetch origin
    git rebase origin/master  # or merge

[ ] No merge conflicts?
[ ] Tests pass on final commit?
[ ] Clean git log?
    git log --oneline master..HEAD
```

### PR Description Template

```markdown
## Summary
Brief overview of what this PR does

## Changes
- Major change 1
- Major change 2

## Testing
- [ ] Integration tests added/updated
- [ ] Manual testing completed
- [ ] No regressions

## Before/After
Show behavior before and after the change

## Test Plan
How to test this PR

🤖 Generated with [Claude Code](https://claude.com/claude-code)
```

### PR Creation
```bash
[ ] Push to remote:
    git push origin <branch>

[ ] Create PR with template:
    gh pr create --title "..." --body "..." --base master

[ ] Link to relevant issues
[ ] Request review if needed
[ ] Add labels (bug, enhancement, etc.)
```

---

## Common Workflows

### Adding a New Command

```bash
1. [ ] Define command class in src/patterns/command/operaciones.h
2. [ ] Implement execute() in src/patterns/command/operaciones.cpp
3. [ ] Add command ID to src/manager/parametros.h
4. [ ] Register in CommandBuilder::buildCommands()
5. [ ] Add test case to src/tests/command_builder_test.cpp
6. [ ] Test manually: echo -e "2\n<command>\nexit\n" | ./main
7. [ ] Update docs if needed
```

### Fixing a Segmentation Fault

```bash
1. [ ] Reproduce with minimal input
2. [ ] Run in gdb:
    echo "input" | gdb -ex run -ex bt ./main
3. [ ] Check backtrace for:
    - Dangling pointers/references?
    - Null pointer dereference?
    - Out of bounds access?
4. [ ] Review recent changes to affected files
5. [ ] Check CommandBuilder parameters (common cause!)
6. [ ] Write test that reproduces the crash
7. [ ] Fix the issue
8. [ ] Verify test passes
9. [ ] Run all integration tests
```

### Adding a New Scene

```bash
1. [ ] Add scene to gameData_es.json
2. [ ] Add scene to gameData_en.json (keep in sync!)
3. [ ] Define exits to/from other scenes
4. [ ] Add objects to scene if needed
5. [ ] Test scene loading: make json_loader_test
6. [ ] Test scene transitions manually
7. [ ] Update game documentation if needed
```

### Refactoring Code

```bash
1. [ ] Run all tests BEFORE refactoring (baseline)
2. [ ] Make small, incremental changes
3. [ ] Run tests after EACH change
4. [ ] Never refactor and add features simultaneously
5. [ ] Update tests if interfaces change
6. [ ] Document architectural changes in PROJECT_CONTEXT.md
7. [ ] Run full test suite before committing
```

---

## Emergency Procedures

### Build Broken
```bash
1. Revert to last known good commit:
   git log --oneline
   git checkout <last_good_commit>

2. Test if build works:
   make clean && make

3. If yes, check what broke:
   git diff <last_good> <broken_commit>

4. Fix or revert the breaking commit
```

### Tests Failing
```bash
1. Identify which test:
   make test-integration

2. Run specific test:
   make <test_name>
   ./<test_executable>

3. Check recent changes:
   git log --oneline -5
   git diff HEAD~1

4. Revert or fix
```

### Segmentation Fault in Production
```bash
1. Get core dump or run in gdb
2. Check backtrace
3. Review RECENT changes first (likely culprit)
4. Check CommandBuilder parameters (common issue)
5. Check GameLoop parameter clearing
6. Look for premature command execution
7. Write regression test
8. Fix and verify test passes
```

---

## Continuous Improvement

### After Completing a Task
```bash
[ ] Did I encounter any unexpected issues?
    → Document in TECHNICAL_DEBT.md

[ ] Did I discover new patterns/pitfalls?
    → Update PROJECT_CONTEXT.md

[ ] Could this workflow be improved?
    → Update DEVELOPMENT_WORKFLOW.md

[ ] Do we need more tests?
    → Add to backlog
```

---

## Quick Commands Reference

```bash
# Build
make clean && make              # Clean build
make                           # Incremental build

# Testing
make test-integration          # Integration tests only
make test-all                  # All tests
make <test_name>              # Specific test
./<test_executable>           # Run test directly

# Manual Testing
echo -e "2\ncommands\nexit\n" | ./main
./main                        # Interactive mode

# Git
git status                    # Check status
git diff                      # See changes
git log --oneline -10         # Recent commits
git branch -vv                # Current branch info

# Debugging
gdb ./main                    # Start debugger
(gdb) run                     # Run program
(gdb) bt                      # Backtrace after crash
```

---

**Remember:**
- Tests first, code second
- Small commits, frequent pushes
- Document as you go
- Ask for help early
- Update this workflow when you learn something new

**Last Updated:** 2025-01-11
