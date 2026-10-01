---
name: ddsseq-dev
description: "DDSSEQ development and migration workflow for ipos_kernel. Use when debugging ddsseq linker errors, DataRes symbol issues, dbbtrv replacement work, sequence resource CRUD behavior, and Win11 vs XP validation flow."
user-invocable: true
---

# DDSSEQ Development Workflow

Use this skill for repeatable DDSSEQ troubleshooting and validation during dbbtrv-to-ddsseq migration work.

## When to Use

- `LNK2001`/`LNK1120` in `ddsseq.dll` builds
- `DataRes_*` export/signature mismatches
- Resource table CRUD compatibility checks
- Questions about `_CONVERTTO`, SEQ file reuse, or XP-only re-creation

## Procedure

1. Establish build scope
- Prefer module-level verification first in `V200/V200_32.DBG/DDSSEQ`.
- Rebuild only the changed source/object before full build.

2. Separate compile from link failures
- If link errors mention missing symbols from `ddsseq.exp`, verify the source object was regenerated.
- Do not assume DEF changes are sufficient when object build failed.

3. Verify symbol compatibility
- Compare expected decorated names from linker output with object symbol table.
- Ensure function prototypes and calling conventions match exactly (`WINAPI`/`__stdcall` where required).

4. Resolve dependency assumptions
- If unresolved globals are referenced (for example table pointers), prefer stable exported helper APIs over hidden globals.
- Keep compatibility surface in `ddsseq` and avoid broad changes in `restool`/`dbhelp` unless explicitly requested.

5. Validate runtime path
- Run Win11-first functional checks on copied SEQ data:
  - read existing entries
  - update entry
  - create entry
  - delete entry
- Use XP only when dbbtrv is required to recreate source data.

## Quick Decisions

- Existing SEQ files present:
  - Start without `_CONVERTTO`.
- Runtime anomalies with existing data:
  - Recreate on XP with dbbtrv source, then retest on Win11.
- Mixed-shell command instability:
  - Switch to PowerShell for MSVC toolchain commands.

## Guardrails

- Keep changes minimal and ABI-focused.
- Preserve current public contracts used by `restool` and `dbhelp`.
- Prefer deterministic, stepwise triage over large backports.

## References

- Win11 build and linker commands: [win11-command-snippets](./references/win11-command-snippets.md)
