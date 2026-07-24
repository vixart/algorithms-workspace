# C++ Algorithms Workspace

A single workspace holding many independent **subprojects** — one folder per
algorithm or mechanism. Each subproject has its own header-only implementation
plus unit tests (using [doctest](https://github.com/doctest/doctest)).

## Layout

```
.
├── Taskfile.yml            # task-based commands (primary)
├── Makefile                # same commands via mingw32-make / make
├── .vscode/
│   └── c_cpp_properties.json  # IntelliSense config (compiler + C++23)
├── common/
│   ├── doctest.h           # vendored single-header test framework
│   └── doctest_main.cpp    # shared main() for all test binaries
├── _template/              # copy this to start a new subproject
│   ├── solution.hpp
│   ├── solution_test.cpp
│   └── main.cpp
├── binary-search/          # example subproject
│   ├── binary_search.hpp
│   ├── binary_search_test.cpp
│   └── main.cpp
└── secret_number/          # another example subproject
    ├── secret_number.hpp
    ├── secret_number_test.cpp
    └── main.cpp
```

## Subproject conventions

Inside a subproject folder `<name>/`:

| File          | Purpose                                                        |
|---------------|----------------------------------------------------------------|
| `*.hpp`       | Header-only implementation of the algorithm/mechanism.         |
| `*_test.cpp`  | Unit tests. Only `#include "doctest.h"` — **no** `main()`.     |
| `main.cpp`    | Optional demo driver (has its own `main()`).                   |

`main()` for the tests comes from `common/doctest_main.cpp`, which is linked in
automatically. That means you can split tests across several `*_test.cpp` files.

## Commands

With [Task](https://taskfile.dev) (recommended):

```
task                      # list all tasks
task projects             # list subprojects
task new  -- quicksort    # scaffold a new subproject from _template
task test -- binary-search
task run  -- binary-search
task test-all             # run tests of every subproject
task clean
```

With Make (`mingw32-make` on Windows):

```
mingw32-make test DIR=binary-search
mingw32-make run  DIR=binary-search
mingw32-make test-all
mingw32-make clean
```

## Adding a new algorithm

1. `task new -- <name>` (copies `_template/` to `<name>/`).
2. Put your implementation in `<name>/solution.hpp` (rename as you like).
3. Write tests in `<name>/*_test.cpp`.
4. `task test -- <name>`.

## Requirements

- A **C++23** compiler in `PATH` (`g++`; the workspace was set up with MinGW-w64 / WinLibs, GCC 16.1.0).
- [Task](https://taskfile.dev) and/or `make` (`mingw32-make` ships with WinLibs).

The C++ standard is set to `-std=c++23` in three places (keep them in sync if you change it):

| Where | Purpose |
|-------|---------|
| `Taskfile.yml` → `vars.CXXFLAGS` | compilation via `task` |
| `Makefile` → `CXXFLAGS` | compilation via `make` |
| `.vscode/c_cpp_properties.json` → `compilerArgs` + `cppStandard` | editor IntelliSense |

The build `CXXFLAGS` also include `-static -static-libgcc -static-libstdc++`, which
make the produced binaries **self-contained** — they don't depend on MinGW's
`libstdc++-6.dll` / `libgcc_s_seh-1.dll` at runtime. Without this, a binary can fail
to launch when `mingw64\bin` isn't on `PATH`, or when an older, ABI-incompatible
`libstdc++-6.dll` from another toolchain is found first (see Troubleshooting). These
flags live in `Taskfile.yml` and `Makefile` (not in the VS Code config, which only
drives IntelliSense and doesn't build).

---

## Environment setup (from scratch, Windows)

These are the exact steps to bring the toolchain up on a fresh Windows machine.
Everything below installs per-user (no admin required) via **winget** (bundled with
Windows 11 / modern Windows 10).

### 1. Install the C++ compiler (MinGW-w64 / WinLibs, GCC 16.1.0)

```powershell
winget install --id BrechtSanders.WinLibs.POSIX.UCRT -e --accept-package-agreements --accept-source-agreements
```

This provides `g++`, `gcc`, `gdb`, `mingw32-make`, `cmake`, `ninja` and more.
winget registers them as command aliases and adds them to `PATH`.

> **Important:** `PATH` changes only take effect in a **new** terminal.
> Close and reopen your terminal (or VS Code) after installing.

Verify (in a new terminal):

```powershell
g++ --version          # -> g++.exe (MinGW-W64 ...) 16.1.0
mingw32-make --version # -> GNU Make ...
```

The compiler binaries live under (path used by `.vscode/c_cpp_properties.json`):

```
C:\Users\<you>\AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin
```

### 2. Install the Task runner

```powershell
winget install --id Task.Task -e --accept-package-agreements --accept-source-agreements
```

Verify (new terminal): `task --version`.

> Task is optional — everything also works with `mingw32-make`. But `task` is the
> primary, cross-platform command runner used by this workspace.

### 3. (Already done) Test framework

`common/doctest.h` is **vendored** (committed into the repo), so there is nothing
to install. If you ever need to update it:

```powershell
curl -L -o common/doctest.h https://raw.githubusercontent.com/doctest/doctest/v2.4.11/doctest/doctest.h
```

### 4. Smoke-test the workspace

From the repo root, in a **new** terminal:

```powershell
task test-all          # builds & runs every subproject's unit tests
```

You should see `Status: SUCCESS!` for each subproject.

### Changing the GCC version later

- Newer/other WinLibs build: `winget install BrechtSanders.WinLibs.POSIX.UCRT --version <ver>`
  (list versions with `winget show BrechtSanders.WinLibs.POSIX.UCRT --versions`).
- A specific version not in winget (e.g. an exact 14.1.0): download the matching
  archive from <https://github.com/brechtsanders/winlibs_mingw/releases>, unzip it,
  and point `.vscode/c_cpp_properties.json` → `compilerPath` at its `bin\g++.exe`.
  Make sure that `bin` folder is the one found first on `PATH`.

---

## VS Code setup

So that IntelliSense (red squiggles, autocomplete, go-to-definition) matches the
actual build.

### 1. Install the C/C++ extension

Extensions view (`Ctrl+Shift+X`) → install **C/C++** (`ms-vscode.cpptools`, by Microsoft).
This extension provides the IntelliSense engine.

### 2. IntelliSense configuration (already in the repo)

`.vscode/c_cpp_properties.json` is committed and points IntelliSense at the WinLibs
compiler:

- `compilerPath` → the WinLibs `g++.exe` (the extension then auto-discovers all system
  headers like `<iostream>`, `<vector>`, …).
- `compilerArgs` / `cppStandard` → `-std=c++23` / `c++23` (matches the build flags).
- `includePath` → `common` (for `doctest.h`) and `${workspaceFolder}/**` (subproject headers).

> If you installed the compiler somewhere else (different user name or a manual
> WinLibs unzip), update `compilerPath` to your `bin\g++.exe`. It's the only line
> that is machine-specific.

### 3. Activate it

`Ctrl+Shift+P` → **C/C++: Select IntelliSense Configuration** → choose **WinLibs-GCC**.
If squiggles linger after edits, run `Ctrl+Shift+P` → **Developer: Reload Window**
(the IntelliSense parser sometimes lags a second or two behind edits).

### 4. Running tasks from within VS Code (optional)

Open a terminal in VS Code (`Ctrl+``) and use the same `task ...` / `mingw32-make ...`
commands. Optionally install the **Task** extension (`task.vscode-task`) to run
tasks from the command palette / a sidebar.

### Troubleshooting

| Symptom | Cause / fix |
|---------|-------------|
| `#include errors detected. Please update your includePath` | `compilerPath` wrong or C/C++ extension not installed. Fix the path, reload window. |
| `namespace "std" has no member "X"` but it compiles fine | Stale IntelliSense. Reload window. Build (`task test`) is the source of truth. |
| `'g++' is not recognized` / `"g++": executable file not found in $PATH` | Your terminal/VS Code was opened **before** the compiler was installed and still holds a stale `PATH`. Fully restart VS Code, or reload `PATH` in the current terminal (see below). |
| `task: command not found` | Task not installed / not on `PATH` — use `mingw32-make` instead, or reopen the terminal. |
| `task run` / `task test` fails with `exit status 57` (or the exe won't start) | The compiled binary loaded a wrong/old `libstdc++-6.dll` from elsewhere on `PATH` (`STATUS_ENTRYPOINT_NOT_FOUND` = `0xC0000139` → 57), or couldn't find it at all (`0xC0000135` → 53). Fixed by the `-static*` flags now in `CXXFLAGS` (binaries no longer depend on that DLL). If it recurs, rebuild: `task clean` then `task run -- <name>`. |

### Quick `PATH` reload (current terminal, no restart)

If a terminal was opened before the toolchain was installed, refresh its `PATH`
without restarting:

**PowerShell** — re-read the persisted `PATH` from the registry:

```powershell
$env:Path = [Environment]::GetEnvironmentVariable('Path','Machine') + ';' + [Environment]::GetEnvironmentVariable('Path','User')
```

**Git Bash** — prepend the WinLibs `bin` directly (adjust the user name if different):

```bash
export PATH="/c/Users/Alex/AppData/Local/Microsoft/WinGet/Packages/BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe/mingw64/bin:$PATH"
```

Then verify in the same terminal: `g++ --version`.
This affects only the current terminal; new terminals pick up the persisted `PATH`
automatically once VS Code has been restarted.
