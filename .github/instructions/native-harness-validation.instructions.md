---
description: "Use when validating native C++ harnesses, interpreting exit-code failures, or tracing a legacy assert/autoabort to faults.log."
---
# Native Harness Validation Instructions

## Purpose

This repository uses small native harnesses to validate backend behavior before trusting the full runtime flow. The harnesses exercise the same compatibility seam used by the application: direct DB contract calls, backend table access, and persisted data validation.

The validation flow is:

- run the repo-native test wrapper or the harness executable under its relevant test folder
- let the harness initialize the DLLs and test data
- read the process result
- treat a non-zero exit code as a real failure signal, not as a successful run

## Harness behavior

The harness is intended to fail loudly when the backend violates the expected runtime contract. The harness is not a silent “pass if nothing exploded” check; it depends on actual read-back validation and persistence checks.

A valid harness run should produce console output such as:

- `[script] PASS`
- `[resource] PASS`
- `[dict] PASS`
- `[restart] PASS`
- `harness succeeded.`

If the process exits unexpectedly or returns status 1, the run must be treated as failed.

## Exit code semantics

This project’s legacy assert machinery can trigger a fatal abort path in the runtime.

- A process exit code of `0` means success from the OS perspective.
- A process exit code of `1` means the runtime hit a fatal condition, including the autoabort path.
- In this codebase, the assert window reads `[ErrorHandling] -> AutoAbortTime` from the active INI and can abort the process automatically after the configured timeout.
- The fatal path is implemented in [../../V200/V200.SRC/ddsmem/GLOBMEM.CPP](../../V200/V200.SRC/ddsmem/GLOBMEM.CPP), and the autoabort logic may call `FatalExit(1)`.

This is intentional: a failed in-process assert must be visible to automation as an error, not as a clean success.

## What to do on exit code 1

When the harness or app exits with code 1:

1. Treat the run as failed.
2. Check whether a new entry was written to [../../V200/V200.TEST/DDSSEQ/faults.log](../../V200/V200.TEST/DDSSEQ/faults.log).
3. If a new faults.log entry exists, inspect it first.
4. Use the fault entry to identify the module, function/method, and assert path that triggered the fatal condition.
5. Follow the stack, source line, and module reported in the log to the runtime source that produced the failure.
6. Only after that, inspect the runtime state, the active INI, the test data, and the DLL version you just built.

The rule is: if the process returned exit code 1 and the faults log has a new entry, the log is the first source of truth for the exact failure site.

## Log investigation workflow

The expected workflow is:

- build the changed module with the repo-native build flow
- run the harness or app under the correct INI and test-data path
- if exit code is 1, look in faults.log
- compare the new timestamped entry to the code path
- trace the error back to the actual source line in the runtime code
- fix the root cause, rebuild, and rerun

## Important caveat

A harness that prints `succeeded` after a fatal runtime exit is not considered valid for this project. If the process returned 1, the run is a failure even if some console output still looks normal.

The exit code is the authoritative signal; the faults log is the investigative trail that explains why the process failed.

## Repository build flow

Always prefer the repo-native build flow defined in [../../build.bat](../../build.bat) and the related instruction files under [.github/instructions](../). Do not rely on ad hoc compiler invocations for the validation routine.

This keeps the environment, the selected modules, and the DLL load path consistent with the repo’s supported Windows toolchain.
