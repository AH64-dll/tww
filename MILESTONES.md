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

---

## 2026-08-13T00:59Z — M6b: FLIP #20 — d_a_mozo → Equivalent with `mw_version="GC/1.3.2r"` — the FIRST 1.3.2r-override flip in the tree (commit 2e95469a6, gated 416-OK fresh stamp 00:59:23; setAnm per-case loopMode local was the key — shared call + per-case li r5,0x0). 84 NonMatching rows remain. Confirms the M3 mwcc-version discovery end-to-end: mozo was the one real 1.3.2r family member (10/10 'primes' disproven as stub-tier by .o-swap), and its flip proves the per-actor compiler override path works. R-team marker audit + QA sweep enqueued.

---

## 2026-08-13T00:59Z — M7: ALL FOUR VERSIONS GATED GREEN locally — GZLE01 416 OK (standing), D44J01 417 OK (demo disc), GZLP01 416 OK (PAL ISO, main.dol hash 9395f878 pinned-match), GZLJ01 416 OK (JP RVZ, main.dol 995406d9 pinned-match). 24 Equivalent flips all ancestors of the gated HEAD. 80 NonMatching rows remain (flip pipeline flowing, stub-tier transcription grinding).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T08:15Z — M8: 28 Equivalent flips gated (item #25, uk #26, trap #27, bmcon1 #28) — 416-OK x2 clean gates at fc086df3e/fc045a397 (dual-verified). 77 ActorRel NonMatching remain. TWO shared-header ripple incidents caught by the gate (try.h u8→s8 revert x2 — correct.h Matching rel; so.h inline-ctor weak-emission investigation — clean). Section-scan standard locked: 10+ real value bugs caught (de1/uk×2/ftree×2/magmarock×5/ac1/pw×2/kg2×2). One-sided-insn count = the accept-class discriminator (R4 self-correction). Wave at ~22 agents, D-team fully productive.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T11:34Z — M9: flip #30 d_a_obj_aygr → ActorRel(Matching) — FIRST Matching-class flip this session (18/18 fns 100.0, 4 real fixes: set_mtx arg-eval order, JUT_ASSERT local-name string pool, Draw TEV_TYPE_BG0 lighting bug, CreateHeap assert-string); 416-OK gate at 5153b694a 14:34:11, rel sha1 byte-perfect vs pin. Ledger: 75 ActorRel NonMatching / 28 Equivalent / 312 Matching + 84 DOL Object rows (taxonomy written — JSystem/TRK/dolphin framework tier + 3 actor-adjacent claimable). Bench cycle: 8 preverifies all correct (trap #27 post-flip QA stands; aj1/sarace/bms1/kg2/pw/so/sitem/gy/kantera NOT-flip-ready with fix lists; R2 hidden branch-target catch; R4/R5/R9/R10 value-bug catches — 10+ real bugs pre-blocked). 4-version cycle green at e8aafa15d.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T11:53Z — M10: 3-flip wave — #30 aygr Matching (first Matching-class, byte-perfect rel), #31 kg2 Equivalent (full approval trail), #32 sarace Equivalent (ratified by arbiter R2-7-2, bgt byte-identical proof). Ledger 74 NonMatching / 30 Equivalent / 313 Matching. Flip-discipline codified after 2 stale-incarnation violations (B9-3 stood down): flips only after RLead consensus + Main approval + BLead gate; valid-evidence flips stand gated never reverted. Bench caught 12+ real value bugs pre-flip this session. 4-version cycle green at e8aafa15d.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T12:37Z — M11: flip #33 d_a_tag_ba1 → ActorRel(Matching) — 2nd Matching-class flip, FULL approval trail (D5 fixes b343d9d7b → R9-7 4-step FLIP-READY → RLead-7 concurrence → Main approval → BLead execute+gate 3cd5fae91 15:37:12). Rel re-linked + sha1 byte-perfect vs pin (no Equivalent fallback). Ledger: 73 NonMatching / 30 Equivalent / 314 Matching. Orgctl lock-GC fixed (rmdir logging + status GC pass). Section-scan discipline held: 15+ real value bugs caught today pre-flip.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T12:46Z — M12: flip #34 d_a_obj_hami2 → Matching — stub→Matching in ~40 min (D3 transcription + D6 fixes: nodeCallBack PSMTXCopy arg-order, set_mtx, CreateHeap ret-flag polarity, Mthd_Create ctor-guard; 25/25 fns 100.0; .data extra-weak proven hami3-identical + mwld-GC'd). Triple bench consensus (R4-7/RLead-7/R3-3). Gate 0b764dbe7 15:45:37 sha1 byte-perfect. Ledger: 72 NonMatching / 30 Equivalent / 315 Matching. 2 Matching flips via proper process this wave (#33/#34).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T13:34Z — M13: flip #35 d_a_obj_vtil → Equivalent — 6 flips today (#30-35: aygr/tag_ba1/hami2 Matching, kg2/sarace/vtil Equivalent). Ledger: 71 NonMatching / 31 Equivalent / 315 Matching. vtil: 30/32 fns 100 via full stub transcription (4 real fixes incl HitSeStart &eyePos sound bug); 2 holdouts 0-one-sided (stack-slot trap-precedent + anchor). Gate 12a322c54 16:34:25. Bench pre-blocked flame (real fmuls-chain structural, 13 normdiffs) — discipline holding.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T14:11Z — M14: flip #36 d_a_obj_kanoke → Equivalent — 7 flips today (#30-36: aygr/tag_ba1/hami2 Matching; kg2/sarace/vtil/kanoke Equivalent). Ledger: 69 NonMatching / 32 Equivalent / 314 Matching. kanoke: 3 sub-100 all 0-one-sided (executeNormal norm-diff-0, Tate fns paired single-insn moves, RLead-8 first arbitration); 4 real value bugs fixed during watch. Gate 71fa0ed68 17:10:14. DLead7-2 + RLead-8 shifts wrapped clean; DLead-8/RLead-9 booted.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-13T15:15Z — M15: flip #37 d_a_obj_balancelift → Equivalent — 8 flips this session (#30-37: aygr/tag_ba1/hami2 Matching; kg2/sarace/vtil/kanoke/balancelift Equivalent). Ledger: 68 NonMatching / 33 Equivalent / 314 Matching. Gate doctrine caught a REAL shared-header ripple (d_shop.h m54→mSelectIdx rename missed rsh1.cpp:931 → compile break at committed state; D10 fixed b808825e9, re-gated 5e983f5a7 18:15:08). Bench caught 20+ real bugs today incl 2 gameplay logic inversions (magmarock polarity) + mVelocity 440→2.0.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T00:10Z — M16: flip #39 d_a_npc_ds1 → Equivalent — 10 flips this session (#30-39: 3 Matching + 7 Equivalent). Ledger: 66 NonMatching / 35 Equivalent / 314 Matching. ds1: 46/47 fns 100 via full stub transcription; marker arbitration settled (nonstandard 'demo' marker dropped per msdan precedent; D44J01 _draw divergence 0x30C-vs-0x2AC recorded + gate-enforced). Double gate 03:09:18/03:09:30; 4-version cycle dispatched for rsh1/bs1 rename verification. Wave respawned after 8.5h gap: 33 agents, integrity gate green at 5d4386add.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T00:14Z — M17: 4-version cycle ALL GREEN at 3ba252876 (D44J01 417 / GZLP01 416 / GZLJ01 416 / GZLE01 416) — covers flip #39 ds1 + shared-header renames (d_shop.h/d_snap.h). REAL CATCH: kiosk demo ships DIFFERENT code for aygr/hami2/tag_ba1 (verified hami2 demo cf947424 vs retail de364dda) → converted to MatchingFor(GZLJ01,GZLE01,GZLP01) per agbsw0/andsw0/att precedent, D44J01 re-gated 417 OK. Demo-divergence class now documented + handled. Ledger: 66 NonMatching / 35 Equivalent / 314 Matching + 3 MatchingFor.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T00:51Z — M18: flips #40 Itnak (re-flip after reconciliation — set_mtx norm-diff-0 arg-eval, R7-8 overruled on evidence) + #42 zk1 (8 ARG-only accept holdouts, zero one-sided) → Equivalent, gate 5240492fd 03:50:14. Ledger: 64 NonMatching / 37 Equivalent / 314 Matching + 3 MatchingFor. 13 flips this session (#30-42: aygr/tag_ba1/hami2 Matching; kg2/sarace/vtil/kanoke/balancelift/ashut/ds1/ekskz/Itnak/zk1 Equivalent). Bench caught 25+ real bugs incl ds1 loop-bounds (post-flip), mn speedF 0.0-vs-1.0, Itnak M_cyl_src x3, ekskz seStart 200-vs-1.0, magmarock logic inversions.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T00:53Z — M19: 4-version cycle 2 ALL GREEN at 5240492fd (D44J01 417 with 788-step relink / GZLP01 416 / GZLJ01 416 / GZLE01 416) — zk1 shared-header renames (d_save_event_flag.inc + d_snap.h) verified on all 4 versions, Matching siblings confirmed post-flip. Flips #40 Itnak + #42 zk1 fully gated across the matrix. Ledger: 64 NonMatching / 37 Equivalent / 314 Matching + 3 MatchingFor. Session total: 13 flips, 2 4-version cycles, 3 demo-divergence conversions.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T01:05Z — M20: ALL 5 WAVE-2 FLIPS QA-PASSED — #38 ashut (R8-7), #39 ds1 (R8-8+value-bug-fixed), #40 Itnak (R1-8, reconciliation held), #41 ekskz (R4-8), #42 zk1 (R7-8). 13 flips this session (#30-42). Ledger: 64 NonMatching / 37 Equivalent / 314 Matching + 3 MatchingFor. Bench caught 30+ real bugs org-wide. 2 4-version cycles green. D-team mid-flight: mmrr 5 sub-100, light 15 stubs, firewall transcribing, aj1 lookBack one-liner.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T01:14Z — M21: flip #43 d_a_npc_aj1 → Equivalent — closes the longest actor saga of the session (20+ commits, 4 real value bugs: HIO field-order, msg IDs, wrong-member 0x26D, set_pa_smk GXColor; 3 structural rounds; 21/21 sub-100 0-structural final). Gate 43a1e88e5 04:14:24. Ledger: 63 NonMatching / 38 Equivalent / 314 Matching + 3 MatchingFor. 14 flips this session (#30-43: 3 Matching + 10 Equivalent + 3 MatchingFor conversions).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T01:16Z — M22: flip #44 d_a_obj_magmarock → Equivalent — 15 flips this session (#30-44). Ledger: 62 NonMatching / 39 Equivalent / 314 Matching + 3 MatchingFor. magmarock: 26/32 fns 100, 6 accept-class 0-one-sided (Draw multiset-equal position-shift RLead-11-proven); 8 real bugs fixed en route incl 2 gameplay logic inversions + mVelocity 440→2.0. Gate 6e693b089 04:16:11; 4-version cycle dispatched (Magrock arc D44J01 divergence check, MatchingFor contingency pre-armed).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T01:18Z — M23: 4-version cycle 3 ALL GREEN at 6e693b089 (D44J01 417 / GZLP01 416 / GZLJ01 416 / GZLE01 416). Magmarock demo-divergence CONFIRMED (D44J01 arc 3ecaa539 12100B vs retail 037485a8 12292B) but #44 Equivalent linked=False → D44J01 assembles original sections, pin matches by construction; NO MatchingFor needed (that class is only for Matching/linked=True — the aygr/hami2/ba1 failure was wrongly-flipped-Matching). 3 consecutive 4-version cycles green today. Ledger: 62 NonMatching / 39 Equivalent / 314 Matching + 3 MatchingFor.

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T01:32Z — M24: flip #45 d_a_ss → Equivalent — 16 flips this session (#30-45). Ledger: 61 NonMatching / 40 Equivalent / 314 Matching + 3 MatchingFor. ss: core_move early-return restructure (R3-8 fix direction, 18==18 branches, SVINE fall-through restored), 9 sub-100 0-one-sided. Gate 904caa658 04:31:46. BLead-8 shift: 12 gates (#38-45 + MatchingFor conversion + 3 4-version cycles).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T02:15Z — M25: flip #46 d_a_obj_hcbh → Equivalent — 17 flips this session (#30-46). Ledger: 60 NonMatching / 41 Equivalent / 314 Matching + 3 MatchingFor. hcbh: 15 real bugs fixed (R9-8's 8 + D8-10's 9 incl roomNo member, ClrTgHit-vs-ClrCoHit, X/Y angle swap), 56/64 fns 100, 8 sub-100 all register-strip-equal. Gate 638b767dc 05:15:07. Also this cycle: buoyflag UNBLOCKED (shared-header wall root-caused — m258 layout + mpActor + header-inline static; 5 siblings sha1-verified), ftree held (marker restore + pikupikuS_init).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T03:23Z — M26: 4-version cycle 4 ALL GREEN at 795eacfd5 (D44J01 417 / GZLP01 416 / GZLJ01 416 / GZLE01 416, 06:21:15-35) — flips #45 ss + #46 hcbh + firewall/tntrap/htetu1/light/buoyflag/hsehi1/kf1 transcribes verified on all 4 versions. 4 consecutive cycles green today. OPERATIONS SYSTEMS LIVE: session-compaction (orgctl compact/resume, 500k-token rule, skills updated) + 30-min design heartbeat (heartbeat-main.py: roster roles / 3-team / wave floor / queue health / ledger). Ledger: 59 NonMatching / 42 Equivalent / 314 Matching + 3 MatchingFor. 17 flips this session (#30-46).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T03:35Z — M27: flips #47 msdan2 (MatchingFor, rel re-linked on retail = strongest gate form) + #48 ftree (Equivalent, 9/9 strip-equal after S_init reclassification) → 4-version cycle 5 ALL GREEN at 16961e3bc (D44J01 417 / GZLP01 416 / GZLJ01 416 / GZLE01 416) — 5 consecutive cycles green today. Ledger: 58 NonMatching / 43 Equivalent / 313 Matching + 4 MatchingFor. 18 flips this session (#30-48: 3 Matching + 13 Equivalent + 1 MatchingFor + 1 re-class).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T03:56Z — M28: flip #49 d_a_npc_mn → Equivalent — 20 flips this session (#30-49). Ledger: 57 NonMatching / 44 Equivalent / 313 Matching + 4 MatchingFor. mn: 4 structural cleared byte-exact (executeWait CSE-kill, executeWalk/eventWalk clrlwi, lookBack case-0 pivot NOT kantera), 114/119 fns 100, 5 accept-class. Gate 4a3cc2b2f 06:55:36. Bench: 6 flips concurred this RLead-12-shift (#43-49 cycle: aj1/magmarock/ss/hcbh/msdan2/ftree/mn all QA'd); d_a_sss value-bug catch (pos.y 70-vs-20).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T05:05Z — M29: flip #50 d_a_obj_Vds → Equivalent — 21 flips this session (#30-50). Ledger: 56 NonMatching / 45 Equivalent / 313 Matching + 4 MatchingFor. Vds: FULL stub transcription (34/37 fns 100, 9c5678470), 3 holdouts strip-equal norm-diff-0, .rodata/.data byte-identical. Gate fea7844bc 08:04:58. Wave respawned (D1-11..D10-11). Bench streak: 8 real bugs caught pre-flip this cycle (firewall ChkUsed no-op, sss 70/20, kf1 0.25, ko1 sig, buoyflag constants).

See .org/log.md + .org/lessons.md for details. (auto-pushed)

---

## 2026-08-14T05:29Z — M30: flip #51 d_a_obj_YLzou → MatchingFor(retail-3) — 22 flips this session (#30-51). Ledger: 54 NonMatching / 46 Equivalent / 313 Matching + 5 MatchingFor. YLzou: 49/49 fns + all sections 100.0 (full transcription), demo-only HIO class proven (53 demo refs vs 0 retail). Gate 9301769f4 08:27:30 + cycle 6 ALL GREEN. BLead-9 shift: 6 flips, 10 gap-closes, 3 cycles. MatchingFor-family signature: retail legs relink+pin, demo leg CHECK-only.

See .org/log.md + .org/lessons.md for details. (auto-pushed)
