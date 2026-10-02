---
description: "Guardrail: build and dev automation in this repo must use Windows-native scripting; no bash build scripts."
---
# Build Shell Policy

## Required scripting language

- Use `.bat` files for legacy Windows build flows.
- Use `.ps1` files for modern Windows automation if a script is needed.
- Do not create bash (`.sh`) scripts for build, compile, link, or dev-tool automation in this project.
- Git Bash is acceptable only for local search, file inspection, and non-build shell helpers.

## Why

- The project uses legacy Windows build scripts and environment expectations.
- The build toolchain is Windows-oriented and depends on cmd.exe / batch semantics and Windows path handling.
- Bash scripts add platform conversion issues, quoting problems, and drift from the repo’s native build flow.

## Rule

If a new development or build helper is required, prefer `.bat` first and `.ps1` second. Bash is forbidden for build-related automation in this repository.
