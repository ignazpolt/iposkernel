---
description: "Use when working on ipos_kernel builds, linker errors, shell command execution, ddsseq/dbbtrv migration, or Win11/XP runtime decisions. Prioritize reliable shell usage and fast diagnostics."
---
# ipos_kernel Workflow Instructions

## Shell Strategy (Windows Toolchain)

- Prefer PowerShell for MSVC build tools (`cl.exe`, `link.exe`, `rc.exe`) and response-file linking.
- Use `cmd.exe` for legacy `.bat` flows when environment variables like `ACTVERS` are required.
- Use Git Bash mainly for file search and text operations.
- If linker/tool flags begin with `/` and run in Bash, avoid GNU command collisions and argument conversion issues.

## Build Strategy

- Start with targeted module builds before full build:
  - Example module path: `V200/V200_32.DBG/DDSSEQ`.
- Prioritize DBG profile unless user explicitly requests OPT.
- After compile issues, verify object regeneration before diagnosing link failures.

## DDSSEQ Linker Triage

- For `LNK2001` on exported symbols from `ddsseq.exp`:
  - Confirm source file compiled successfully.
  - Inspect symbols in object files before editing DEF files.
  - Verify calling conventions and mangled names match expectations.
- Prefer fixing root compile/source issues before adding linker workarounds.

## Runtime and Data Policy

- Primary functional testing target: Windows 11.
- XP VM is fallback for dbbtrv-dependent data re-creation workflows.
- If existing SEQ files are available, test on copies first and avoid unnecessary `_CONVERTTO`/re-creation.

## Safety Rules

- Never run destructive git commands unless user explicitly requests them.
- Keep edits minimal and localized; avoid unrelated refactors.
- Preserve user changes in dirty worktrees.
