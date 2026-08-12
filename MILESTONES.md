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

---

## 2026-08-12T13:25Z — M4: three PRs green this session — #1155 d_a_magma kiosk adoption (upstream/main + single-commit rebuild), #1157 d_a_npc_co1 100% Matching (Equivalent weak-data, 109/109), #1158 d_a_ship OK (Equivalent regalloc, 189/189 ≥99.9%). All six org PRs (#1152/#1153/#1154/#1155/#1157/#1158) open+mergeable+CI-green x4. Open-claim pool corrected: ship was flip-only; buoyflag enqueued; 1.3.2r family fully characterized (mozo only positive, aj1 negative-definitive).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-12T13:54Z — M5: flip batch complete — #1161 d_a_kb, #1162 d_a_bridge, #1163 d_a_bmdfoot all Equivalent regalloc flips CI-green x4 (single configure.py each from upstream/main). Eleven org PRs open+mergeable (#1152/#1153/#1154/#1155/#1157/#1158/#1159/#1160/#1161/#1162/#1163). Flip-pool exhausted (exactly 6 flips, all in-flight). Free-flip pattern proven: kb/bridge/bmdfoot/kt/ship were all hidden flips found by the outside-queue sweep.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-12T20:00Z — M6: isolated-mode flip batch complete — 17 Equivalent flips ALL locally gated; flip pool exhausted; gate re-verified at HEAD b96f8029e

**State (2026-08-12 22:55 EEST)**: ISOLATED MODE FOREVER (zero GitHub outbound — no PRs/CI/upstream; local flip+gates only). Main HEAD `b96f8029e`, verify worktree reset to it, forced explicit gate `build-lock.sh build/GZLE01/ok` → **416 files OK** (authoritative ok stamp 22:54:34 after configure regen; earlier 22:52/22:53 stamps were 0-byte placeholders — always force + confirm mtime moved after regen). 87 `ActorRel(NonMatching)` rows remain in configure.py; 120 verdicts in `.org/actor-data/`.

**Delivered**
- **17 Equivalent flips all locally gated** (bridge, lod_bg, obj_ikada, obj_tide, himo3, kamome, kt, obj_swflat, ship, bmdfoot, kb, klft, mant, npc_co1, npc_ji1, movie_player, msdan MatchingFor 3-retail) — every flip commit accounted for in flip-gate-audit; 0 unverified flips (mozo premature flip reverted).
- **Flip pool EXHAUSTED**: 0 free-flip candidates; every near-100 actor has ≥1 real (non-regalloc) holdout per the preverify bench. Near-flip targets each need real fixes: kantera (switch-pivot, do-not-retest), ac1 (setBtp getIDRes), gk1 (createInit structural), kddoor (3 stragglers), bpw (action_bunri_dousa API diffs), tribox (holdouts + onPushPullKeep landed).
- **mwcc 1.3.2r family fully characterized**: mozo is the ONLY real 1.3.2r override; 9/10 pair-detect "primes" disproven by .o-swap + stub-check (near-zero scores were empty `/* Nonmatching */` stubs, not compiler-version).
- **Org-wide anti-slop sweep**: Nonmatching marker gaps closed in multiple actors; stale markers on 100% fns removed (mozo 9, ob1 6); s32→bool fix landed for sv (QACop-flagged regression 100→88.889 → 100).
- **One-liners landed this session**: de1 demo() u8->bool + setMtx mAnmNum + CreateHeap priority 1, ob1 get_attPos path-inline, kddoor calcMtx m19A + nodeCB revert, tribox onPushPullKeep + L_attr, ac1 setMtx, ss useHeapInit 0x8, mn 0x78C mItemId.
- **Quota recovery**: full 30-agent wave died to provider 429 (weekly/monthly/5h limits); lesser-scale Pro wave + Main-as-Pro surgical lane carried the flip/gate work; roster trimmed; orgctl queue absorbed mass death with zero loss.

See .org/log.md + .org/lessons.md for details.

---

## 2026-08-12T19:56Z — M6: 17 Equivalent flips all locally gated (416-OK x each); flip pool exhausted (0 free candidates — every near-100 actor has a real fix in flight); 1.3.2r family fully characterized (mozo only override; pw/kg2/bj1/9 others disproven as stub-tier); quota recovered post-429; 87 NonMatching rows remaining, punch list active (ac1 review, kg1 onEventFlag, kddoor drawSet, ss frames, gp1 _draw, mozo stubs, ftree, mn pool)

See .org/log.md + .org/lessons.md for details. (auto-pushed)
