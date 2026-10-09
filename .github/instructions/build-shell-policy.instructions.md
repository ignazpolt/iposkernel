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

## Required build entrypoint

- Use the repo-native build wrapper in [build.bat](C:/ipos_kernel/build.bat) as the default entrypoint for project builds.
- For a normal debug rebuild, prefer: `build.bat DBG` or `build.bat DBG <module>`.
- For targeted validation, prefer a module-specific build like: `build.bat DBG DDSSEQ` or `build.bat DBG RESTOOL`.
- Do not bypass the repo build flow with direct `cl.exe`, `link.exe`, or ad hoc compiler commands unless the project explicitly requires a narrow tool invocation for diagnosis.
- The repo expects the VC environment bootstrap via [init_vc.bat](C:/ipos_kernel/init_vc.bat) and the legacy Windows batch flow; this is part of the project’s supported build contract.

## AI/tooling guidance

- Before making build or compile changes, confirm the correct module and profile in the repo build wrapper.
- If the task is debugging a module or a DLL, start from the smallest build using the module name in `build.bat` instead of a full `ALL` rebuild.
- When the task involves Windows-native build behavior, prefer PowerShell or `cmd.exe` semantics over bash, and keep all build-related automation consistent with this repository’s established Windows batch design.
