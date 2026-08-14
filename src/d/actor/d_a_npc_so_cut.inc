// The original name of this file is unknown, but it must exist because d_a_npc_so's "cut" functions
// are in a separate .text section from the rest of its functions.

#include "d/actor/d_a_npc_so.h"

/* 00004CE8-000051E8       .text cutProc__10daNpc_So_cFv */
void daNpc_So_c::cutProc() {
    /* Nonmatching */
    field_0xB6C = dComIfGp_evmng_getMyStaffId("NpcSo", NULL, 0);
    if (field_0xB6C != -1) {
        static char* cut_name_tbl[] = {
            "SWIM",
            "JUMP",
            "APPEAR",
            "DIVE",
            "DISAPPEAR",
            "SET_ANM",
            "EFFECT",
            "EQUIP",
            "UNEQUIP",
            "EATESA",
            "EATESA1ST",
            "JUMP_MAPOPEN",
            "MINIGAME",
            "TURN",
            "MINIGAME_WARP",
            "MINIGAME_RETURN",
            "PARTNER_SHIP",
            "MINIGAME_WAIT",
            "MINIGAME_END",
            "MINIGAME_PL_TURN",
            "MINIGAME_PL_UP",
        };
        static void (daNpc_So_c::*cut_tbl[][2])() = {
            {&daNpc_So_c::cutSwimStart, &daNpc_So_c::cutSwimProc},
            {&daNpc_So_c::cutJumpStart, &daNpc_So_c::cutJumpProc},
            {&daNpc_So_c::cutAppearStart, &daNpc_So_c::cutAppearProc},
            {&daNpc_So_c::cutDiveStart, &daNpc_So_c::cutDiveProc},
            {&daNpc_So_c::cutDisappearStart, &daNpc_So_c::cutDisappearProc},
            {&daNpc_So_c::cutSetAnmStart, &daNpc_So_c::cutSetAnmProc},
            {&daNpc_So_c::cutEffectStart, &daNpc_So_c::cutEffectProc},
            {&daNpc_So_c::cutEquipStart, &daNpc_So_c::cutEquipProc},
            {&daNpc_So_c::cutUnequipStart, &daNpc_So_c::cutUnequipProc},
            {&daNpc_So_c::cutEatesaStart, &daNpc_So_c::cutEatesaProc},
            {&daNpc_So_c::cutEatesaFirstStart, &daNpc_So_c::cutEatesaFirstProc},
            {&daNpc_So_c::cutJumpMapopenStart, &daNpc_So_c::cutJumpMapopenProc},
            {&daNpc_So_c::cutMiniGameStart, &daNpc_So_c::cutMiniGameProc},
            {&daNpc_So_c::cutTurnStart, &daNpc_So_c::cutTurnProc},
            {&daNpc_So_c::cutMiniGameWarpStart, &daNpc_So_c::cutMiniGameWarpProc},
            {&daNpc_So_c::cutMiniGameReturnStart, &daNpc_So_c::cutMiniGameReturnProc},
            {&daNpc_So_c::cutPartnerShipStart, &daNpc_So_c::cutPartnerShipProc},
            {&daNpc_So_c::cutMiniGameWaitStart, &daNpc_So_c::cutMiniGameWaitProc},
            {&daNpc_So_c::cutMiniGameEndStart, &daNpc_So_c::cutMiniGameEndProc},
            {&daNpc_So_c::cutMiniGamePlTurnStart, &daNpc_So_c::cutMiniGamePlTurnProc},
            {&daNpc_So_c::cutMiniGamePlUpStart, &daNpc_So_c::cutMiniGamePlUpProc},
        };

        int actIdx = dComIfGp_evmng_getMyActIdx(field_0xB6C, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
        if (actIdx == -1) {
            dComIfGp_evmng_cutEnd(field_0xB6C);
        } else {
            if (dComIfGp_evmng_getIsAddvance(field_0xB6C)) {
                (this->*cut_tbl[actIdx][0])();
            }
            (this->*cut_tbl[actIdx][1])();
        }
    }
}

/* 000051E8-000051EC       .text cutSwimStart__10daNpc_So_cFv */
void daNpc_So_c::cutSwimStart() {
    
}

/* 000051EC-00005364       .text cutSwimProc__10daNpc_So_cFv */
void daNpc_So_c::cutSwimProc() {
    /* Nonmatching */
    cXyz pos = mEventCut.getAttnPos();
    field_0xAFC = 7.0f + REG12_F(10);
    const cXyz& diff = current.pos - pos;
    f32 sq = PSVECSquareMag(&cXyz(diff.x, 600.0f, diff.z));
    f32 dist = sq > 600.0f ? std::sqrtf(sq) : sq;
    cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &pos), 8, 0x400);
    if (dist < 150.0f + REG12_F(7)) {
        field_0xAFC = 600.0f;
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 00005364-000054A4       .text cutJumpStart__10daNpc_So_cFv */
void daNpc_So_c::cutJumpStart() {
    /* Nonmatching */
    field_0xA9C = 15;
    current.pos.y = dLib_getWaterY(current.pos, mObjAcch);

    f32* jumpSpeed = dComIfGp_evmng_getMyFloatP(field_0xB6C, "Speed_y");
    f32* swimSpeed = dComIfGp_evmng_getMyFloatP(field_0xB6C, "SpeedF");
    shape_angle.x = l_HIO.field_0x68;
    speed.y = jumpSpeed != NULL ? *jumpSpeed : 40.0f;
    field_0xAFC = swimSpeed != NULL ? *swimSpeed : 5.0f;

    offsetSwim();
    speedF = field_0xAFC;
    setAnm(4, 0);
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x5938, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 000054A4-00005598       .text cutJumpProc__10daNpc_So_cFv */
void daNpc_So_c::cutJumpProc() {
    /* Nonmatching */
    f32 waterY = dLib_getWaterY(current.pos, mObjAcch);
    if (cLib_calcTimer(&field_0xA9C) == 0) {
        if (current.pos.y <= waterY) {
            s8 reverb = dComIfGp_getReverb(current.roomNo);
            JAIZelBasic::getInterface()->seStart(0x5939, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            fopKyM_createWpillar(&current.pos, 1.4f * scale.x, 1.4f, 0);
            field_0xAFC = 600.0f;
            speedF = field_0xAFC;
            dComIfGp_evmng_cutEnd(field_0xB6C);
        }
    }
}

/* 00005598-00005610       .text cutAppearStart__10daNpc_So_cFv */
void daNpc_So_c::cutAppearStart() {
    /* Nonmatching */
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x593A, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    offsetAppear();
}

/* 00005610-00005668       .text cutAppearProc__10daNpc_So_cFv */
void daNpc_So_c::cutAppearProc() {
    if (std::fabsf(field_0xB34 - field_0xB38.x) < 10.0f) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 00005668-00005688       .text cutDiveStart__10daNpc_So_cFv */
void daNpc_So_c::cutDiveStart() {
    offsetDive();
}

/* 00005688-000056E0       .text cutDiveProc__10daNpc_So_cFv */
void daNpc_So_c::cutDiveProc() {
    if (std::fabsf(field_0xB34 - field_0xB38.x) < 10.0f) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 000056E0-00005778       .text cutDisappearStart__10daNpc_So_cFv */
void daNpc_So_c::cutDisappearStart() {
    /* Nonmatching */
    offsetDive();
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x593B, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    fopKyM_createWpillar(&current.pos, 1.2f * scale.x, 1.4f, 0);
}

/* 00005778-000057D0       .text cutDisappearProc__10daNpc_So_cFv */
void daNpc_So_c::cutDisappearProc() {
    if (std::fabsf(field_0xB34 - field_0xB38.x) < 10.0f) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 000057D0-000058D0       .text cutSetAnmStart__10daNpc_So_cFv */
void daNpc_So_c::cutSetAnmStart() {
    /* Nonmatching */
    char* name = dComIfGp_evmng_getMyStringP(field_0xB6C, "Name");
    if (name != NULL) {
        if (strcmp(name, "WAIT") == 0) {
            field_0x6D3 = 1;
        } else if (strcmp(name, "TALK") == 0) {
            field_0x6D3 = 3;
        } else if (strcmp(name, "JUMP") == 0) {
            field_0x6D3 = 4;
        } else if (strcmp(name, "SWIM") == 0) {
            field_0x6D3 = 2;
        }
    } else {
        field_0x6D3 = 1;
    }
}

/* 000058D0-0000599C       .text cutSetAnmProc__10daNpc_So_cFv */
void daNpc_So_c::cutSetAnmProc() {
    /* Nonmatching */
    dComIfGp_evmng_getMyStringP(field_0xB6C, "Name");
    if (field_0x6D3 == 1 || field_0x6D3 == 4 || field_0x6D3 == 3 || field_0x6D3 == 2) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
    if (mpMorf->isStop()) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 0000599C-00005AA8       .text cutEffectStart__10daNpc_So_cFv */
void daNpc_So_c::cutEffectStart() {
    /* Nonmatching */
    cXyz pos(current.pos);
    pos.y -= 80.0f;
    cXyz scale(1.0f, 1.0f, 1.0f);
    JPABaseEmitter* emitter = dComIfGp_particle_set(0x8152, &pos, NULL, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
    emitter->mGlobalParticleScale.set(0.62f, 0.6f, 1.0f);
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(0x58BD, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 00005AA8-00005ADC       .text cutEffectProc__10daNpc_So_cFv */
void daNpc_So_c::cutEffectProc() {
    dComIfGp_evmng_cutEnd(field_0xB6C);
}

/* 00005ADC-00005AE0       .text cutEquipStart__10daNpc_So_cFv */
void daNpc_So_c::cutEquipStart() {
    
}

/* 00005AE0-00005B1C       .text cutEquipProc__10daNpc_So_cFv */
void daNpc_So_c::cutEquipProc() {
    field_0xA78 = 1;
    dComIfGp_evmng_cutEnd(field_0xB6C);
}

/* 00005B1C-00005B20       .text cutUnequipStart__10daNpc_So_cFv */
void daNpc_So_c::cutUnequipStart() {
    
}

/* 00005B20-00005B5C       .text cutUnequipProc__10daNpc_So_cFv */
void daNpc_So_c::cutUnequipProc() {
    field_0xA78 = 0;
    dComIfGp_evmng_cutEnd(field_0xB6C);
}

/* 00005B5C-00005B98       .text cutEatesaStart__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaStart() {
    offsetZero();
    field_0xAFC = 0.0f;
    speedF = 0.0f;
}

/* 00005B98-00005BF8       .text cutEatesaProc__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaProc() {
    fopAc_ac_c* esa = (fopAc_ac_c*)fopAcIt_Judge(searchEsa_CB, this);
    if (esa != NULL) {
        static_cast<esa_class*>(esa)->field_0x298 = 1;
    } else {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 00005BF8-00005C6C       .text cutEatesaFirstStart__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstStart() {
    /* Nonmatching */
    offsetZero();
    fopAc_ac_c* player = g_dComIfG_gameInfo.play.getPlayerPtr(2);
    mCirclePath.mRadius = 650.0f + REG8_F(11);
    mCirclePath.mAngle = player->shape_angle.y;
    field_0xBDA = 1;
    field_0xAFC = 0.0f;
    speedF = 0.0f;
}

/* 00005C6C-000060FC       .text cutEatesaFirstProc__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstProc() {
    /* Nonmatching */
    fopAc_ac_c* player = g_dComIfG_gameInfo.play.getPlayerPtr(0);
    fopAc_ac_c* ship = g_dComIfG_gameInfo.play.getPlayerPtr(2);
    cXyz pos = player->current.pos;
    if (ship != NULL) {
        s16 angle = ship->shape_angle.y + REG12_S(6) - 0x4000;
        pos = ship->current.pos;
        pos.x += 260.0f * cM_ssin(angle);
        pos.z += 260.0f * cM_scos(angle);
    }

    cXyz diff = current.pos - pos;
    f32 sq = PSVECSquareMag(&cXyz(diff.x, 0.0f, diff.z));
    f32 dist = sq > 0.0f ? std::sqrtf(sq) : sq;

    if (dist < 700.0f + REG8_F(11)) {
        cLib_addCalc2(&mCirclePath.mRadius, 30.0f, 0.05f, 8.0f + REG8_F(10));
    }

    mCirclePath.mAngleSpeed = 0x300;
    mCirclePath.mTranslation = pos;
    mCirclePath.mTranslation.y = dLib_getWaterY(mCirclePath.mTranslation, mObjAcch);
    dLib_setCirclePath(&mCirclePath);

    mCirclePath.mPos.y = dLib_getWaterY(mCirclePath.mPos, mObjAcch);
    cXyz target = mCirclePath.mPos;
    target.y -= 100.0f;

    cXyz diff2 = current.pos - target;
    f32 sq2 = PSVECSquareMag(&cXyz(diff2.x, 0.0f, diff2.z));
    f32 dist2 = sq2 > 0.0f ? std::sqrtf(sq2) : sq2;

    mEventCut.setAttnPos(target);
    mEventCut.setAttnFlag(0);
    field_0xB44 = target;

    f32 speed = 2.0f;
    if (dist2 < 100.0f + REG12_F(7)) {
        if (dist2 <= 50.0f) {
            speed = 0.0f;
            fopAc_ac_c* esa = (fopAc_ac_c*)fopAcIt_Judge(searchEsa_CB, this);
            if (esa != NULL) {
                static_cast<esa_class*>(esa)->field_0x298 = 1;
            } else {
                dComIfGp_evmng_cutEnd(field_0xB6C);
                field_0xBDA = 0;
                field_0xB04 = speed;
            }
        }
    } else if (dist2 < 200.0f + REG12_F(7)) {
        speed = 12.0f;
    } else {
        speed = 20.0f + REG12_F(10);
    }

    if (speed != 0.0f) {
        cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&field_0xB54, &target), 3, 0x1200);
    }
    cLib_addCalcPos2(&current.pos, target, 0.1f, speed);
    current.pos.y = dLib_getWaterY(current.pos, mObjAcch) - 100.0f;
}

/* 000060FC-00006148       .text cutJumpMapopenStart__10daNpc_So_cFv */
void daNpc_So_c::cutJumpMapopenStart() {
    field_0xBBC = 0;
    offsetZero();
    setAnm(2, 0);
    field_0xBDA = 1;
}

/* 00006148-000064B8       .text cutJumpMapopenProc__10daNpc_So_cFv */
void daNpc_So_c::cutJumpMapopenProc() {
    /* Nonmatching */
}

/* 000064B8-00006710       .text cutMiniGameStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameStart() {
    /* Nonmatching */
    field_0xB74 = 0;
    mB78 = 0;
    field_0xB7C = 0;
    field_0xB80 = 0;
    offsetDive();
    dComIfGp_startMiniGame(8);
    JAIZelBasic::getInterface()->seStart(0x8F0, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);

    daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (REG8_S(1) == 0) {
        field_0xBCC = player->current.pos;
        field_0xBCC.x += 100.0f * cM_ssin(player->shape_angle.y);
        field_0xBCC.z += 100.0f * cM_scos(player->shape_angle.y);
        field_0xBCC.y += 50.0f;

        field_0xBC0 = player->current.pos;
        field_0xBC0.x += -200.0f * cM_ssin(player->shape_angle.y);
        field_0xBC0.z += -200.0f * cM_scos(player->shape_angle.y);
        field_0xBC0.y += 100.0f;

        cam->mCamera.Reset(field_0xBCC, field_0xBC0);
        cam->mCamera.Start();
    }

    player->mDemo.mDemoType = 3;
    player->mDemo.mParam0 = 0;
    player->mDemo.mDemoMode = 0x44;
    field_0xBDB = 0;
    field_0xBDE = 0;
}

/* 00006710-00006FE4       .text cutMiniGameProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameProc() {
    /* Nonmatching */
}

/* 00006FE4-00006FF0       .text cutTurnStart__10daNpc_So_cFv */
void daNpc_So_c::cutTurnStart() {
    field_0xA9C = 30;
}

/* 00006FF0-00007114       .text cutTurnProc__10daNpc_So_cFv */
void daNpc_So_c::cutTurnProc() {
    /* Nonmatching */
    fopAc_ac_c* player = g_dComIfG_gameInfo.play.getPlayerPtr(0);
    if (player == NULL) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
        return;
    }

    s16 angle = player->shape_angle.y + 0x4000;
    cXyz pos = player->current.pos;
    pos.x += -300.0f * cM_ssin(angle);
    pos.z += -300.0f * cM_scos(angle);

    s16 target = cLib_targetAngleY(&current.pos, &pos);
    cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);
    s32 dist = cLib_distanceAngleS(shape_angle.y, target);
    if (cLib_calcTimer(&field_0xA9C) == 0 || dist <= 0x400) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 00007114-00007324       .text cutMiniGameWarpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpStart() {
    /* Nonmatching */
}

/* 00007324-00007438       .text cutMiniGameWarpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpProc() {
    /* Nonmatching */
}

/* 00007438-00007524       .text cutMiniGameReturnStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnStart() {
    /* Nonmatching */
}

/* 00007524-0000781C       .text cutMiniGameReturnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnProc() {
    /* Nonmatching */
}

/* 0000781C-00007820       .text cutPartnerShipStart__10daNpc_So_cFv */
void daNpc_So_c::cutPartnerShipStart() {
    
}

/* 00007820-00007878       .text cutPartnerShipProc__10daNpc_So_cFv */
void daNpc_So_c::cutPartnerShipProc() {
    fopAc_ac_c* player = g_dComIfG_gameInfo.play.getPlayerPtr(2);
    dEvt_control_c* evt = g_dComIfG_gameInfo.play.getEvent();
    evt->mPtTalk = evt->getPId(player);
    dComIfGp_evmng_cutEnd(field_0xB6C);
}

/* 00007878-000078E0       .text cutMiniGameWaitStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitStart() {
    /* Nonmatching */
}

/* 000078E0-00007914       .text cutMiniGameWaitProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitProc() {
    dComIfGp_evmng_cutEnd(field_0xB6C);
}

/* 00007914-00007934       .text cutMiniGameEndStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameEndStart() {
    field_0xA9C = REG12_S(0) + 0x2D;
    field_0xBDE = 0;
}

/* 00007934-0000798C       .text cutMiniGameEndProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameEndProc() {
    initCam();
    moveCam();
    if (cLib_calcTimer(&field_0xA9C) == 0) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 0000798C-000079AC       .text cutMiniGamePlTurnStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlTurnStart() {
    field_0xA9C = REG12_S(2) + 0xA;
    field_0xBDE = 0;
}

/* 000079AC-00007AC0       .text cutMiniGamePlTurnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlTurnProc() {
    /* Nonmatching */
}

/* 00007AC0-00007B1C       .text cutMiniGamePlUpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpStart() {
    /* Nonmatching */
}

/* 00007B1C-00007CBC       .text cutMiniGamePlUpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpProc() {
    /* Nonmatching */
}

/* 00007CBC-00007E74       .text initCam__10daNpc_So_cFv */
void daNpc_So_c::initCam() {
    /* Nonmatching */
    if (field_0xBDE == 1) {
        return;
    }
    field_0xBDE = 1;

    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (REG8_S(1) != 0) {
        return;
    }

    cam->mCamera.Stop();
    cam->mCamera.SetTrimSize(1);

    fopAc_ac_c* player = g_dComIfG_gameInfo.play.getPlayerPtr(0);
    field_0xBCC = player->current.pos;
    field_0xBCC.x += 100.0f * cM_ssin(player->shape_angle.y);
    field_0xBCC.z += 100.0f * cM_scos(player->shape_angle.y);
    field_0xBCC.y += 50.0f;

    field_0xBC0 = player->current.pos;
    field_0xBC0.x += -200.0f * cM_ssin(player->shape_angle.y);
    field_0xBC0.z += -200.0f * cM_scos(player->shape_angle.y);
    field_0xBC0.y += 100.0f;
}

/* 00007E74-00008010       .text moveCam__10daNpc_So_cFv */
void daNpc_So_c::moveCam() {
    /* Nonmatching */
    if (REG8_S(1) != 0) {
        return;
    }

    fopAc_ac_c* player = g_dComIfG_gameInfo.play.getPlayerPtr(0);
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

    cXyz pos = player->current.pos;
    pos.x += 150.0f * cM_ssin(player->shape_angle.y);
    pos.z += 150.0f * cM_scos(player->shape_angle.y);
    pos.y += 100.0f;

    cXyz pos2 = player->current.pos;
    pos2.x += -400.0f * cM_ssin(player->shape_angle.y);
    pos2.z += -400.0f * cM_scos(player->shape_angle.y);
    pos2.y += 300.0f;

    cLib_addCalcPos2(&field_0xBC0, pos2, 0.05f, 5.0f);
    cLib_addCalcPos2(&field_0xBCC, pos, 0.05f, 5.0f);

    cam->mCamera.Set(field_0xBCC, field_0xBC0);
}
