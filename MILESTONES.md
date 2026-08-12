# TWW Decomp Org — Milestones

Automatic checkpoint log pushed to the fork's `milestones` branch at every
milestone (never merged into main or PR branches). Append + push via
`bash /home/amr/ZeldaDecompile/scripts/push-milestone.sh "<one-line summary>"`.

---

## M1 — 2026-08-12: Org launched; first PR green on all 4 versions

**State**: 30-agent org running; fork AH64-dll/tww; goal 73.42% → 100% matched on zeldaret/tww.

**Delivered**
- **PR #1152 `d_a_obj_ikada 100% Matching` — CI GREEN on all 4 versions (GZLE01/GZLP01/GZLJ01/D44J01), OPEN + MERGEABLE.** 109/109 functions decompiled (setWave finish); configure.py flip; verified in a dedicated worktree; flipped to `Equivalent` + `# weak func order` after diagnosing extra weak inlines (CrossAtTg/CrossCo/dBgS) vs the original weak set (per-function 100% ≠ rel match). Supersedes partial upstream PR #1091.
- **Full org cycle proven**: claim audit → decompile → anti-slop review (msdan rejected for convention fixes; gate enforced) → flip → worktree-verified → PR → CI green.
- **D44J01 debug maps installed**: 784 .map files (frameworkD.map + 367 per-actor) at orig/D44J01/files/maps/, parser-validated end-to-end; inline hunting (the #1 match-killer) is now local. D44J01 build gate open (main.dol sha1 matches).
- **Knowledge system**: 65+ lessons distilled into 6 skills + 14 pattern docs; inline index D.map-grounded; retail-regalloc cases catalogued (item, bmdfoot, kt).
- **Infrastructure**: build-lock.sh (flock-serialized ninja — kills objdiff/PCH races), verify worktree, PR-branch worktrees (branch isolation), parking policy (compiling WIP sacred), respawn-on-settle loop for budget-limited agents.
- **External value**: 8 convention-review comments posted on upstream PRs (#1060, #1118, #1133, #1150, #1061, #1149 + follow-ups), all Main-approved and verified.

**Actors in flight**: mant, klft, kantera, mozo, movie_player, ship, bpw, bmdfoot, npc_de1, ss(sss), msdan (fix unit), obj_try (prep), npc_ji1/gk1 (handoff requeues), lod_bg/himo2 (fresh-eyes regalloc).

**Hard cases handled honestly**: lod_bg loadModelData (99.94%, 720 decl orders tried), himo2 new_himo2_move (pure regalloc, register-normalized diff = 0), item itemActionForSword (retail-only regalloc, upstream-stuck since 2023), bmdfoot attack_1 (retail-only, upstream merged at 99%) — all released blocked with handoffs or done-as-upstream.

**Progress**: 73.42% → 73.42% matched (baseline; first PR pending merge), 0 regressions across 1683 units (baseline holds), 30/30 agents healthy.

---

## 2026-08-12T11:15Z — M2: First fully-Matching actor PR + three-PR pipeline

**PR #1154 `d_a_obj_msdan 100% Matching` — OPEN, MERGEABLE, CI GREEN on all 4 versions** (GZLE01/GZLJ01/GZLP01/D44J01). The org's first fully-Matching actor. 9/9 functions (6d604e26), convention fixes applied through the review gate (JA_SE_READ_RIDDLE_1 + checkCommandDemoAccrpt, 228cded8), flip committed (d6afce07). Flip scope decided on CLEAN-build evidence: `MatchingFor("GZLJ01","GZLE01","GZLP01")` — the kiosk demo's msdan rel genuinely differs (rm -rf build + configure --version D44J01 proof; same precedent as upstream msdan2 #1092 / msdan_sub2 #1094).

**Three-PR pipeline (all OPEN + MERGEABLE, CI green x4)**: #1152 ikada (Equivalent, weak func order), #1153 movie_player (improvement: mpSetPercentMovieVol header type fix), #1154 msdan (first fully-Matching). All awaiting maintainer merge.

**Closed gates**: D44J01 build green locally (417 files OK) + debug_map_diff.py validated end-to-end; 100% D.map inline-sheet coverage (83/83 unmerged NonMatching actors, 93 sheets).

**Org value delivered**: 13 upstream PRs pre-reviewed with verified convention findings + cross-PR coordination catches (dSnap enum conflict, Vds subsumption); 10+ actors classified done-as-upstream with register-normalized-diff == 0 proof (ikada, ji1, bridge, bmdfoot, bpw, ship, himo3, item, klft-prep); hard cases catalogued. Post-crash recovery complete (416 files OK, two real issues found+fixed: ikada-on-main flip, monsSeStart regression revert); 34-agent concurrency cap in force; 80+ lessons distilled into 6 skills + 16 patterns.

---

## 2026-08-12T14:30Z — M3: mwcc 1.3.2r compiler-version discovery (family-level unlock)

**Discovery (D2W1-3, d_a_mozo)**: the recurring "constant-pooling blocker" (3+ distinct float constants pooled into a ...rodata.0 base register while the original emits per-constant lis/lfs) is a **mwcc compiler-VERSION mismatch**, not a source-structure problem. Some original TUs were built with GC/1.3.2r, not the project default 1.3.2. Verified: swapping a 1.3.2r-built .o into objdiff gives anime_proc 1.01%→100%, towait_proc_init 3.12%→100%, HIO ctor 86.4%→100%, all inits 100%.

**Enabled**: `ActorRel` gained an `mw_version` passthrough (committed on main) — per-actor compiler override at flip time: `ActorRel(Matching, "d_a_mozo", mw_version="GC/1.3.2r")`.

**Candidate family**: mant (n_calc/v_calc/joint_control — its entire remaining delta family shows the signature), bms1 (bs1-family, to test), flame (pool-layout differences), mozo (primary). Review gate now checks for the 1.3.2r signature before rejecting pooling-symptom functions. The org's pooled-actor blockers may be a compiler-version family, not 30 independent regalloc cases.

**Pipeline**: PRs #1152/#1153/#1154 still open+mergeable (CI green x4) awaiting maintainers; co1 (109/109, Equivalent) + magma adoption (#969, noskap release) in Integrator's PR queue; ~15 actors in active decompile; 105 D.map sheets + 53-actor crib map = full tooling coverage; ~225 lessons; 4+ patterns added today (weak-bss verification, 1.3.2r signature, base-class evidence rules).
