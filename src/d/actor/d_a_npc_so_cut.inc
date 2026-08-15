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
    f32 sq = PSVECSquareMag(&cXyz(diff.x, 0.0f, diff.z));
    f32 dist = std::sqrtf(sq);
    cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &pos), 8, 0x400);
    if (dist < 150.0f + REG12_F(7)) {
        field_0xAFC = 0.0f;
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
    if (jumpSpeed != NULL) {
        speed.y = *jumpSpeed;
    } else {
        speed.y = 40.0f;
    }
    if (swimSpeed != NULL) {
        field_0xAFC = *swimSpeed;
    } else {
        field_0xAFC = 5.0f;
    }

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
        s32 angle = ship->shape_angle.y + REG12_S(6);
        angle -= 0x4000;
        pos = ship->current.pos;
        pos.x += 260.0f * cM_ssin(angle);
        pos.z += 260.0f * cM_scos(angle);
    }

    const cXyz& diff = current.pos - pos;
    f32 sq = PSVECSquareMag(&cXyz(diff.x, 0.0f, diff.z));
    f32 dist = std::sqrtf(sq);

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

    const cXyz& diff2 = current.pos - target;
    f32 sq2 = PSVECSquareMag(&cXyz(diff2.x, 0.0f, diff2.z));
    f32 dist2 = std::sqrtf(sq2);

    const cXyz& diff3 = current.pos - pos;
    f32 sq3 = PSVECSquareMag(&cXyz(diff3.x, 0.0f, diff3.z));
    f32 dist3 = std::sqrtf(sq3);

    mEventCut.setAttnFlag(0);
    mEventCut.setAttnPos(target);
    field_0xB44 = target;

    f32 speed;
    if (dist3 < 100.0f + REG12_F(7)) {
        speed = 2.0f;
        if (dist3 <= 50.0f) {
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
    daShip_c* ship = dComIfGp_getShipActor();
    if (ship == NULL) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
        return;
    }

    if (field_0xBBC == 0) {
        field_0xB34 = field_0xB38.x;
        gravity = l_HIO.field_0x80;
        speed.y = l_HIO.field_0x84;
        field_0xB00 = speed.y;
        speedF = 0.0f;
        field_0xAFC = speedF;
        shape_angle.x = l_HIO.field_0x68;
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::getInterface()->seStart(0x593C, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
        field_0xBBC++;
    } else if (field_0xBBC == 1) {
        s16 angle = ship->shape_angle.y + 0x4000;
        field_0xBB0 = ship->current.pos.x;
        field_0xBB4 = ship->current.pos.y;
        field_0xBB8 = ship->current.pos.z;
        f32 negDist = -l_HIO.field_0x88;
        field_0xBB0 += negDist * cM_ssin(angle);
        field_0xBB8 += negDist * cM_scos(angle);
        f32 y = current.pos.y;
        if (speed.y < 1.0) {
            speed.y = 1.0f;
        }
        if (cLib_chasePosXZ(&current.pos, *(cXyz*)&field_0xBB0, l_HIO.field_0x90)) {
            current.pos.y = y;
            if (l_HIO.field_0x94 == 0) {
                g_dComIfG_gameInfo.play.mFmapOpen = 2;
            }
            shape_angle.y += 0x8000;
            field_0xBBC++;
        }
    } else if (field_0xBBC == 2) {
        s16 angle2 = ship->shape_angle.y + 0x4000;
        field_0xBB0 = ship->current.pos.x;
        field_0xBB4 = ship->current.pos.y;
        field_0xBB8 = ship->current.pos.z;
        f32 negDist2 = -l_HIO.field_0x8C;
        field_0xBB0 += negDist2 * cM_ssin(angle2);
        field_0xBB8 += negDist2 * cM_scos(angle2);
        f32 y2 = current.pos.y;
        if (cLib_chasePosXZ(&current.pos, *(cXyz*)&field_0xBB0, l_HIO.field_0x90)) {
            current.pos.y = y2;
            s8 reverb2 = dComIfGp_getReverb(current.roomNo);
            JAIZelBasic::getInterface()->seStart(0x593B, &eyePos, 0, reverb2, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            fopKyM_createWpillar(&current.pos, 1.4f * scale.x, 1.4f, 0);
            field_0xAFC = 0.0f;
            speedF = 0.0f;
            speed.y = 0.0f;
            field_0xB00 = speed.y;
            dComIfGp_evmng_cutEnd(field_0xB6C);
            offsetDive();
            field_0xBDA = 0;
        }
    }
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
    daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayer(0);
    s16 angle = player->shape_angle.y;
    cXyz pos = player->current.pos;
    u8 keep = 0;

    fopAc_ac_c* ship = g_dComIfG_gameInfo.play.getPlayerPtr(2);
    if (ship != NULL) {
        angle = ship->shape_angle.y + REG12_S(6) - 0x4000;
        pos = ship->current.pos;
    }

    if (player->checkResetFlg0(daPy_py_c::daPyRFlg0_ARROW_SHOOT)) {
        mB78++;
    }

    if (mB78 >= 0xA) {
        keep = 1;
        if (field_0xB74 <= 6) {
            player->mDemo.setDemoMode(6);
            player->mDemo.setParam0(1);
            initCam();
            moveCam();
            JAIZelBasic::getInterface()->seStart(0x8F1, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            g_dComIfG_gameInfo.play.mMiniGameType = 0;
            g_dComIfG_gameInfo.play.mMinigameFlags ^= 0x80;
            g_dComIfG_gameInfo.play.mMinigameResult = 0;
            speedF = 0.0f;
            field_0xAFC = 0.0f;
            dComIfGp_evmng_cutEnd(field_0xB6C);
            return;
        }
    }

    switch (field_0xB74) {
    case 0:
        setAnm(2, 0);
        field_0xA9C = 30;
        field_0xB84 = 0;
        field_0xB74++;
        field_0xAFC = 0.0f;
        speedF = field_0xAFC;
        offsetSwim();
        break;
    case 1:
        if (cLib_calcTimer(&field_0xA9C) == 0) {
            field_0xB74++;
        }
        break;
    case 2:
        setAnm(2, 0);
        {
            f32 c = 1000.0f;
            field_0xB8C = c + cM_rndF(400.0f);
            field_0xB88 = cM_rndF(c) + (-c) * 0.5f;
        }
        {
            cXyz v(field_0xB88, 0.0f, field_0xB8C);
            cXyz out(0.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::YrotS(angle);
            PSMTXMultVec(mDoMtx_stack_c::get(), &v, &out);
            PSVECAdd(&out, &pos, &out);
            mEventCut.setAttnPos(out);
        }
        field_0xB74++;
        offsetSwim();
        break;
    case 3: {
        cXyz attn = mEventCut.getAttnPos();
        field_0xAFC = 12.0f + REG12_F(10);
        const cXyz& diff = current.pos - attn;
        f32 sq = PSVECSquareMag(&cXyz(diff.x, 0.0f, diff.z));
        f32 dist = std::sqrtf(sq);
        cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &attn), 8, 0x400);
        if (dist < 150.0f + REG12_F(7)) {
            field_0xAFC = 0.0f;
            field_0xB74++;
        }
        break;
    }
    case 4:
        {
            f32 c = 300.0f;
            field_0xB88 += cM_rndF(c) + (-c) * 0.5f;
        }
        {
            cXyz v(field_0xB88, 0.0f, field_0xB8C);
            cXyz out(0.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::YrotS(angle);
            PSMTXMultVec(mDoMtx_stack_c::get(), &v, &out);
            PSVECAdd(&out, &pos, &out);
            mEventCut.setAttnPos(out);
        }
        field_0xAFC = 0.0f;
        speedF = field_0xAFC;
        field_0xA9C = 30;
        field_0xB74++;
        offsetSwim();
        break;
    case 5: {
        cXyz attn = mEventCut.getAttnPos();
        field_0xAFC = 0.0f;
        const cXyz& diff = current.pos - attn;
        f32 sq = PSVECSquareMag(&cXyz(diff.x, 0.0f, diff.z));
        f32 dist = std::sqrtf(sq);
        cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &attn), 8, 0x400);
        if (cLib_calcTimer(&field_0xA9C) == 0) {
            field_0xB74++;
        }
        break;
    }
    case 6:
        current.pos.y = dLib_getWaterY(current.pos, mObjAcch);
        field_0xAFC = field_0xB08 * (5.0f + cM_rndF(5.0f));
        speedF = field_0xAFC;
        speed.y = 18.0f * field_0xB08 + 4.0f * speedF;
        if (speed.y > l_HIO.field_0x50) {
            speed.y = l_HIO.field_0x50;
        }
        gravity = -0.8f;
        setAnm(4, 0);
        shape_angle.x = l_HIO.field_0x68;
        offsetZero();
        field_0xB74++;
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::getInterface()->seStart(0x5938, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
        break;
    case 7:
        f32 waterY = dLib_getWaterY(current.pos, mObjAcch);
        if (field_0xB84 == 0 && field_0xB7C < 0xA && field_0x6D8 == 0) {
            if (current.pos.y >= waterY + 50.0f) {
                mSph.SetR(l_HIO.field_0x3C);
                mSph.SetC(current.pos);
                g_dComIfG_gameInfo.play.mCcS.Set(&mSph);
            } else {
                cXyz c(0.0f, 30000.0f, 0.0f);
                mSph.SetR(0.0f);
                mSph.SetC(c);
                g_dComIfG_gameInfo.play.mCcS.Set(&mSph);
            }
            if (checkTgHit()) {
                field_0xB7C++;
                if (field_0xB7C >= 0xA) {
                    field_0xB7C = 0xA;
                }
            }
        }
        if (current.pos.y <= waterY) {
            s8 reverb = dComIfGp_getReverb(current.roomNo);
            JAIZelBasic::getInterface()->seStart(0x5939, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            fopKyM_createWpillar(&current.pos, 1.4f * scale.x, 1.4f, 0);
            field_0xAFC = 0.0f;
            speedF = field_0xAFC;
            field_0xB80++;
            if (field_0xB80 >= 0xA || keep) {
                player->mDemo.setDemoMode(6);
                player->mDemo.setParam0(1);
                initCam();
                moveCam();
                JAIZelBasic::getInterface()->seStart(0x8F1, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
                g_dComIfG_gameInfo.play.mMiniGameType = 0;
                g_dComIfG_gameInfo.play.mMinigameFlags ^= 0x80;
                g_dComIfG_gameInfo.play.mMinigameResult = 0;
                speedF = 0.0f;
                field_0xAFC = 0.0f;
                dComIfGp_evmng_cutEnd(field_0xB6C);
            } else {
                field_0xB74 = 0;
            }
        }
        break;
    }
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
    JAIZelBasic::getInterface()->field_0x00bf = 1;

    daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
    player->mDemo.mDemoType = 3;
    player->mDemo.mParam0 = 0;

    daShip_c* ship = dComIfGp_getShipActor();
    field_0xB90.y = dLib_getWaterY(field_0xB90, mObjAcch);
    field_0xBA0.x = ship->current.pos.x;
    field_0xBA0.y = ship->current.pos.y;
    field_0xBA0.z = ship->current.pos.z;
    field_0xBAC = ship->shape_angle.y;
    ship->initStartPos(&field_0xB90, field_0xB9C + 0x4000);
    csXyz sp8 = ship->shape_angle;

    player->setPlayerPosAndAngle(&field_0xB90, field_0xB9C + REG8_S(6));
    field_0xB9C = field_0xB9C;

    field_0xAFC = 4.0f;
    speedF = field_0xAFC;

    s32 angle = ship->shape_angle.y + REG12_S(6);
    angle -= 0x4000;
    current.pos = field_0xB90;
    current.pos.x += 300.0f * cM_ssin(angle);
    current.pos.z += 300.0f * cM_scos(angle);
    field_0xBDB = 1;
    field_0xA9C = REG12_S(1) + 10;

    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cam->mCamera.Reset(field_0xBCC, field_0xBC0);
    cam->mCamera.Start();
}

/* 00007324-00007438       .text cutMiniGameWarpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpProc() {
    /* Nonmatching */
    daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
    player->mDemo.mDemoType = 3;
    player->mDemo.mParam0 = 0;

    daShip_c* ship = dComIfGp_getShipActor();
    player->mDemo.mDemoMode = 6;
    player->mDemo.mParam0 = 1;

    s16 angle = ship->shape_angle.y + REG12_S(6) - 0x4000;
    current.pos = ship->current.pos;
    current.pos.x += 300.0f * cM_ssin(angle);
    current.pos.z += 300.0f * cM_scos(angle);

    if (cLib_calcTimer(&field_0xA9C) == 0) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 00007438-00007524       .text cutMiniGameReturnStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnStart() {
    /* Nonmatching */
    JAIZelBasic::getInterface()->field_0x00bf = 0;

    daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
    player->mDemo.mDemoType = 3;
    player->mDemo.mParam0 = 0;

    s16 shipName = 0xA7;
    daShip_c* ship = (daShip_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeForPName, &shipName);
    player->setPlayerPosAndAngle(&field_0xBA0, field_0xB9C + REG8_S(6));
    ship->initStartPos(&field_0xBA0, field_0xBAC);

    field_0xAFC = 4.0f;
    speedF = field_0xAFC;
    field_0xBDB = 1;
    setAnm(2, 0);
    offsetDive();
}

/* 00007524-0000781C       .text cutMiniGameReturnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnProc() {
    /* Nonmatching */
    daShip_c* ship = dComIfGp_getShipActor();
    s32 angle = ship->shape_angle.y + REG12_S(6);
    angle -= 0x4000;
    current.pos = ship->current.pos;
    current.pos.x += 300.0f * cM_ssin(angle);
    current.pos.z += 300.0f * cM_scos(angle);
    shape_angle.x = 0;

    const cXyz& sp3C = field_0xBA0 - current.pos;
    cXyz sp30(sp3C.x, 0.0f, sp3C.z);
    f32 distSq = PSVECSquareMag(&sp30);
    f32 dist = std::sqrtf(distSq);

    if (dist < 400.0f) {
        daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
        player->mDemo.mDemoType = 3;
        player->mDemo.mParam0 = 0;
        player->mDemo.mDemoMode = 6;
        player->mDemo.mParam0 = 1;

        cXyz sp54(0.0f, 0.0f, 0.0f);
        cXyz sp48(0.0f, 0.0f, 0.0f);
        mDoMtx_YrotS(*calc_mtx, player->shape_angle.y);
        sp54.x = -50.0f + REG0_F(4);
        sp54.y = 50.0f + REG0_F(5);
        sp54.z = 100.0f + REG0_F(6);
        MtxPosition(&sp54, &sp48);

        field_0xBC0 = player->current.pos + sp48;
        field_0xBCC = player->current.pos;
        field_0xBCC.y += 90.0f + REG0_F(10);

        camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
        cam->mCamera.Reset(field_0xBCC, field_0xBC0);
        cam->mCamera.Start();
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
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
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (REG8_S(1) == 0) {
        cam->mCamera.Stop();
        cam->mCamera.SetTrimSize(1);
    }
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
    daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
    player->mDemo.mDemoType = 3;
    player->mDemo.mParam0 = 0;
    daShip_c* ship = dComIfGp_getShipActor();
    player->mDemo.mDemoMode = 6;
    player->mDemo.mParam0 = 1;

    s16 angle = ship->shape_angle.y + REG12_S(6) - 0x4000;
    current.pos = ship->current.pos;
    current.pos.x += 300.0f * cM_ssin(angle);
    current.pos.z += 300.0f * cM_scos(angle);

    if (cLib_calcTimer(&field_0xA9C) == 0) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
}

/* 00007AC0-00007B1C       .text cutMiniGamePlUpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpStart() {
    field_0xA9C = 0x1E;
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cam->mCamera.Stop();
    cam->mCamera.SetTrimSize(1);
}

/* 00007B1C-00007CBC       .text cutMiniGamePlUpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpProc() {
    /* Nonmatching */
    daPy_py_c* player = (daPy_py_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
    player->mDemo.mDemoMode = 6;

    cXyz sp38(0.0f, 0.0f, 0.0f);
    cXyz sp2C(0.0f, 0.0f, 0.0f);
    mDoMtx_YrotS(*calc_mtx, player->shape_angle.y);
    sp38.x = -50.0f + REG0_F(4);
    sp38.y = 50.0f + REG0_F(5);
    sp38.z = 100.0f + REG0_F(6);
    MtxPosition(&sp38, &sp2C);

    field_0xBC0 = player->current.pos + sp2C;
    field_0xBCC = player->current.pos;
    field_0xBCC.y += 90.0f + REG0_F(10);

    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cam->mCamera.Set(field_0xBCC, field_0xBC0);
    if (cLib_calcTimer(&field_0xA9C) == 0) {
        dComIfGp_evmng_cutEnd(field_0xB6C);
    }
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
