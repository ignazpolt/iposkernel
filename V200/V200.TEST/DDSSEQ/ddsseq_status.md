# DDSSEQ Status and Next Steps

## Current status

The DDSSEQ backend has been validated with a native harness for the three primary RESTOOL tables:
- ScriptDB
- ResDB
- DataDict

The harness is located here:
- [V200/V200.TEST/DDSSEQ/ddsseq_harness.cpp](C:/ipos_kernel/V200/V200.TEST/DDSSEQ/ddsseq_harness.cpp)

The runtime test runner is here:
- [V200/V200.TEST/DDSSEQ/run_test.bat](C:/ipos_kernel/V200/V200.TEST/DDSSEQ/run_test.bat)

The environment/setup helper is here:
- [V200/V200.TEST/test_env.bat](C:/ipos_kernel/V200/V200.TEST/test_env.bat)
- [init_vc.bat](C:/ipos_kernel/init_vc.bat)

The backend files that were fixed are:
- [V200/V200.SRC/ddsseq/OPSEQ.CPP](C:/ipos_kernel/V200/V200.SRC/ddsseq/OPSEQ.CPP)
- [V200/V200.SRC/dbhelp/RESSQL.CPP](C:/ipos_kernel/V200/V200.SRC/dbhelp/RESSQL.CPP)
- [V200/V200.SRC/ddsmem/GLOBMEM.CPP](C:/ipos_kernel/V200/V200.SRC/ddsmem/GLOBMEM.CPP)

## What has already been validated

The harness is successfully validating the following CRUD flows:
- create
- read
- update
- delete

for the following table types:
- ScriptDB
- ResDB
- DataDict

The relevant validation flow is the batch command:
- run_test.bat all

The current known result:
- script: PASS
- resource: PASS
- dict: PASS

## Core architectural decision

The replacement strategy is targeted and correct:
- keep the RESTOOL-facing DB contract stable
- implement the missing database behavior in DDSSEQ / SEQ backend
- do not rewrite the whole application or replace unrelated DB layers

This is the compatibility seam that matters:
- DBCall / DBCALLTYPE_* helper API layer
- not direct dbbtrv usage
- not UI-level behavior as the primary validation target

## Why this is the right place to work

The legacy dbbtrv backend is not available on Windows 11, while the SEQ-backed DDSSEQ backend is already the natural storage backend for these tables.

The job is therefore not to replace the whole app stack, but to make DDSSEQ cover the CRUD and record metadata behaviors that RESTOOL requires for its primary tables.

## Important technical findings already covered

### 1. File and path handling
The harness and runtime needed the correct runtime INI and a copied data directory. The test runner prepares this automatically and avoids modifying production SEQ files.

### 2. SEQ metadata integrity matters
The key problems were not mostly “UI” issues, but the actual SEQ mutation logic:
- key metadata initialization
- file-open behavior during create/update
- invalid ownership / stale reference handling
- insert ID assignment
- delete path handling for DataDict

### 3. Update semantics in SEQ files
A key safety rule:
- overwriting bytes in place is only safe when the payload length stays the same
- if a row grows, the backend must safely relocate or append the new record and update metadata

This is the major class of logic required for real CRUD correctness.

### 4. Diagnostics
The missing INI path and runtime setup problems were identified and improved in the assert/logging path.
The relevant file is:
- [V200/V200.SRC/ddsmem/GLOBMEM.CPP](C:/ipos_kernel/V200/V200.SRC/ddsmem/GLOBMEM.CPP)

## Current repo state

The project already contains the working build/test scaffolding:
- build helper: [init_vc.bat](C:/ipos_kernel/init_vc.bat)
- test env: [V200/V200.TEST/test_env.bat](C:/ipos_kernel/V200/V200.TEST/test_env.bat)
- harness: [V200/V200.TEST/DDSSEQ/ddsseq_harness.cpp](C:/ipos_kernel/V200/V200.TEST/DDSSEQ/ddsseq_harness.cpp)
- runner: [V200/V200.TEST/DDSSEQ/run_test.bat](C:/ipos_kernel/V200/V200.TEST/DDSSEQ/run_test.bat)

The key code under development remains concentrated in:
- [V200/V200.SRC/ddsseq/OPSEQ.CPP](C:/ipos_kernel/V200/V200.SRC/ddsseq/OPSEQ.CPP)
- [V200/V200.SRC/dbhelp/RESSQL.CPP](C:/ipos_kernel/V200/V200.SRC/dbhelp/RESSQL.CPP)

## What is next

The next work is not a large rewrite. It is the “real-world hardening” step after the minimal CRUD harness is green.

### Next concrete task group

1. Validate against more realistic RESTOOL table scenarios
   - larger fields
   - realistic record sizes
   - actual key patterns used by the live data
   - repeated create/update/delete loops

2. Add remaining edge cases if not already covered
   - update with larger payload
   - update with smaller payload
   - delete missing key
   - recreate deleted key
   - repeated cycles on the same table
   - long strings / boundary lengths

3. Prepare the next module-level improvement
   - focus on the next small backend hardening change in DDSSEQ or DBHELP
   - not broad refactoring
   - not unrelated modules

## Suggested continuation when we resume tomorrow

The next session should begin by:
1. re-running the harness via run_test.bat all
2. then adding one realistic edge case that stresses a mutation path
3. then applying the next targeted fix in OPSEQ / RESSQL if required

## Working principle

We are not trying to “finish the whole migration” in one go.
We are working in small, defensible steps:
- prove minimal CRUD works
- stress the real data patterns
- harden the metadata/mutation logic
- continue only within the same backend boundary

## Short handoff summary for tomorrow

Status:
- DDSSEQ CRUD harness is passing for the three primary table types
- the backend is working in the validation environment
- the next goal is realistic edge-case and backend hardening work

Focus:
- realistic RESTOOL data patterns
- mutation edge cases
- the next small module improvement in DDSSEQ / DBHELP

## Final note

The repository is already in a good checkpoint state for continuation. If tomorrow we continue from this note, we do not need to re-discover the architecture from scratch. We can continue from the validated harness baseline and push the backend toward the next real-world scenario.
