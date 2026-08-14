/**
 * d_a_sss.cpp
 * Enemy - Dexivine (Forbidden Woods, Wind Temple)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_sss.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_cc_d.h"
#include "d/d_cc_uty.h"
#include "d/d_com_inf_game.h"
#include "d/d_particle_name.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_player.h"
#include "res/Object/Sss.h"

static f32 l_size_d[10] = {10.0f, 10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.5f};
static f32 l_g_d[10] = {50.0f, 50.0f, 35.0f, 25.0f, 15.0f, 9.0f, 6.0f, 6.0f, 6.0f, 6.0f};

static cXyz non_pos;

/* 000000EC-000001F0       .text hand_draw__FP9sss_class */
void hand_draw(sss_class* i_this) {
        fopAc_ac_c* actor = i_this;
    g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &actor->tevStr);
    i_this->mpMorf->updateDL();
    i_this->m300.update(0xA, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, &actor->tevStr);
    dComIfGd_set3DlineMat(&i_this->m300);
    if (i_this->m2FC > 0.1f) {
        i_this->m454.update(5, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, &actor->tevStr);
        dComIfGd_set3DlineMat(&i_this->m454);
    }
}

/* 000001F0-00000248       .text daSss_Draw__FP9sss_class */
static BOOL daSss_Draw(sss_class* i_this) {
    fopAc_ac_c* actor = i_this;
    if (i_this->m2B8 != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->eyePos, &actor->tevStr);
        hand_draw(i_this);
    }
    return TRUE;
}

/* 00000248-000002C8       .text hand_close__FP9sss_class */
void hand_close(sss_class* i_this) {
    i_this->mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_TOJIRU_e),
        0, 1.0f, 1.0f, 0.0f, -1.0f, NULL
    );
}

/* 000002C8-00000348       .text hand_open__FP9sss_class */
void hand_open(sss_class* i_this) {
    i_this->mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e),
        0, 1.0f, 1.0f, 0.0f, -1.0f, NULL
    );
}

/* 00000348-00000444       .text hand_mtx_set__FP9sss_class */
void hand_mtx_set(sss_class* i_this) {
        MtxTrans(i_this->m2D4.x, i_this->m2D4.y, i_this->m2D4.z, 0);
    mDoMtx_XrotM(*calc_mtx, i_this->m2E0);
    mDoMtx_YrotM(*calc_mtx, i_this->m2E2);
    mDoMtx_XrotM(*calc_mtx, REG12_S(1) - 0x4000);
    MtxScale(0.5f, 0.2f + REG0_F(0), 0.5f, 1);
    MtxTrans(0.0f, -130.0f + REG12_F(3), 0.0f, 1);
    i_this->mpMorf->getModel()->setBaseTRMtx(*calc_mtx);
}

/* 00000444-000004CC       .text control3__FP9sss_class */
void control3(sss_class* i_this) {
    /* Nonmatching */
    sss_s* p = i_this->m33C;
    for (int i = 0; i < 10; i++, p++) {
        f32 s = cM_ssin(i_this->m2BC * 0x1F4 + i * 0x64);
        p->mSize = (0.8f + 0.1f * s) * l_size_d[i];
    }
}

/* 000004CC-00000804       .text control1__FP9sss_class */
void control1(sss_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = i_this;
    cXyz pos;
    cXyz pos2;
    cXyz pos3;
    cXyz pos4;

    i_this->m33C[0].mPos = actor->current.pos;
    sss_s* hand_i = &i_this->m33C[1];
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, actor->current.angle.x);
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = i_this->m2F0;
    MtxPosition(&pos, &pos2);
    pos.z = i_this->m2E8;
    f32 dVar9 = i_this->m2F4;
    f32 fVar1 = 1.0f;
    for (int i = 1; i < 9; i++, ++hand_i) {
        cXyz local_c4;
        local_c4.x = dVar9 * cM_ssin(i_this->m2BC * (REG0_S(5) + 0x44C) + i * (REG0_S(6) + 0xFA0));
        local_c4.y = l_g_d[i];
        local_c4.z = dVar9 * cM_scos(i_this->m2BC * (REG0_S(7) + 0x320) + i * (REG0_S(8) + 0xFA0));
        MtxPosition(&local_c4, &pos3);
        f32 fVar4 = hand_i->mPos.x - hand_i[-1].mPos.x + (pos2.x * fVar1) + (pos3.x * fVar1);
        f32 fVar5 = hand_i->mPos.y - hand_i[-1].mPos.y + (pos2.y * fVar1) + (pos3.y * fVar1);
        f32 fVar6 = hand_i->mPos.z - hand_i[-1].mPos.z + (pos2.z * fVar1) + (pos3.z * fVar1);
        s16 angle_x = cM_atan2s(fVar4, fVar6);
        f32 fVar7 = (fVar4 * fVar4) + (fVar6 * fVar6);
        if (fVar7 > 0.0f) {
            fVar7 = std::sqrtf(fVar7);
        }
        s16 angle_y = -cM_atan2s(fVar5, fVar7);
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, angle_x);
        mDoMtx_XrotM(*calc_mtx, angle_y);
        MtxPosition(&pos, &pos4);
        MtxPull();
        hand_i->mPos = (cXyz&)hand_i[-1].mPos + pos4;
    }
}

/* 00000840-00000B0C       .text control2__FP9sss_class */
void control2(sss_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = i_this;
    cXyz pos;
    cXyz pos2;
    cXyz pos3;
    f32 f1;
    f32 f2;

    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = i_this->m2E8;
    i_this->m33C[9].mPos = i_this->m2C8;
    sss_s* hand_i = &i_this->m33C[8];
    int i = 8;
    for (i = 8; i >= 1; i--, hand_i--) {
        f32 fVar1 = hand_i->mPos.x - hand_i[1].mPos.x;
        f32 dVar9 = hand_i->mPos.y - hand_i[1].mPos.y;
        f32 fVar2 = hand_i->mPos.z - hand_i[1].mPos.z;
        int angle_x = cM_atan2s(fVar1, fVar2);
        f32 fVar3 = (fVar1 * fVar1) + (fVar2 * fVar2);
        if (fVar3 > 0.0f) {
            fVar3 = std::sqrtf(fVar3);
        }
        s16 angle_y = -cM_atan2s(dVar9, fVar3);
        mDoMtx_YrotS(*calc_mtx, angle_x);
        mDoMtx_XrotM(*calc_mtx, angle_y);
        if (i == 8) {
            f1 = i_this->m2E8 - 10.0f;
            pos.z = f1;
            if (f1 < 0.0f) {
                pos.z = 0.0f;
            }
        } else {
            pos.z = i_this->m2E8;
        }
        MtxPosition(&pos, &pos2);
        hand_i->mPos = (cXyz&)hand_i[1].mPos + pos2;
    }
    i_this->m2D4 = i_this->m33C[9].mPos;
    pos3 = (cXyz&)i_this->m33C[8].mPos - i_this->m33C[9].mPos;
    i_this->m2E0 = -cM_atan2s(pos3.y, pos3.z);
    i_this->m2E2 = cM_atan2s(pos3.x, std::sqrtf(pos3.y * pos3.y + pos3.z * pos3.z));
    hand_mtx_set(i_this);
}

/* 00000B0C-00000F78       .text cut_control1__FP9sss_class */
void cut_control1(sss_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = i_this;
    cXyz pos;
    cXyz pos2;
    cXyz pos3;
    cXyz pos4;
    cXyz pos5;
    f32 f4;
    f32 f3;
    f32 f2;
    f32 f1;

    i_this->m490[0].mPos = actor->current.pos;
    sss_s* hand_i = &i_this->m490[1];
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, actor->current.angle.x);
    f32 fVar2 = i_this->m2FC;
    f32 fVar1 = 50.0f;
    f32 fVar5 = fVar1 + REG0_F(18);
    int i = 1;
    f32 fVar6 = 0.0f;
    for (i = 1; i < 5; i++, ++hand_i) {
        cXyz local_c4;
        local_c4.x = fVar5 * cM_ssin(i_this->m2BC * (REG0_S(5) + 0x1004) + i * (REG0_S(6) + 0x2710));
        local_c4.y = fVar1 + REG0_F(17);
        local_c4.z = fVar5 * cM_scos(i_this->m2BC * (REG0_S(7) + 0x1130) + i * (REG0_S(8) + 0x2710));
        MtxPosition(&local_c4, &pos2);
        f32 fVar7 = pos2.x + (hand_i->mPos.x - hand_i[-1].mPos.x);
        f32 fVar8 = pos2.y + (hand_i->mPos.y - hand_i[-1].mPos.y);
        f32 fVar9 = pos2.z + (hand_i->mPos.z - hand_i[-1].mPos.z);
        int angle_x = cM_atan2s(fVar7, fVar9);
        f32 fVar10 = (fVar7 * fVar7) + (fVar9 * fVar9);
        if (fVar10 > fVar6) {
            fVar10 = std::sqrtf(fVar10);
        }
        s16 angle_y = -cM_atan2s(fVar8, fVar10);
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, angle_x);        mDoMtx_XrotM(*calc_mtx, angle_y);
        MtxPosition(&pos, &pos3);
        MtxPull();
        hand_i->mPos = (cXyz&)hand_i[-1].mPos + pos3;
    }
    if (i_this->mpEmitterA10 == NULL && i_this->mA18 != 0) {
        i_this->mpEmitterA10 = dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, (cXyz*)&i_this->m490[4].mPos, NULL, NULL, 0xFF);
        i_this->m2C2[1] = 0x3C;
    }
    if (i_this->mpEmitterA10 != NULL) {
        pos4 = (cXyz&)i_this->m490[4].mPos - i_this->m490[3].mPos;
        pos.x = pos4.x;
        pos.y = pos4.y;
        pos.z = pos4.z;
        int angle_x = cM_atan2s(pos.x, pos.z);
        f32 fVar11 = (pos.x * pos.x) + (pos.z * pos.z);
        if (fVar11 > 0.0f) {
            fVar11 = std::sqrtf(fVar11);
        }
        s16 angle_y = -cM_atan2s(pos.y, fVar11);
        i_this->mpEmitterA10->setGlobalTranslation(i_this->m490[4].mPos.x, i_this->m490[4].mPos.y, i_this->m490[4].mPos.z);
        csXyz angle;
        angle.x = angle_y;
        angle.y = angle_x;
        angle.z = 0;
        i_this->mpEmitterA10->setGlobalRotation(angle);
        if (i_this->m2C2[1] == 1) {
            i_this->mpEmitterA10->becomeInvalidEmitter();
            i_this->mpEmitterA10 = NULL;
        }
    }
}

/* 00000F78-000014F4       .text cut_control2__FP9sss_class */
void cut_control2(sss_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = i_this;
    cXyz pos;
    cXyz pos2;
    cXyz pos3;
    cXyz pos4;
    cXyz pos5;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    f32 f8;

    f4 = 0.0f;
    pos.x = f4;
    pos.y = f4;
    pos.z = i_this->m2E8;
    i_this->m33C[9].mPos = i_this->m2C8;
    sss_s* hand_i = &i_this->m33C[8];
    f32 dVar9 = i_this->m2F4;
    int i = 8;
    f32 fVar1 = 10.0f;
    f32 fVar2 = 5.0f;
    for (i = 8; i >= 0; i--, hand_i--) {
        cXyz local_c4;
        f32 fVar3 = dVar9 * cM_ssin(i_this->m2BC * (REG0_S(5) + 0x9C4) + i * (REG0_S(6) + 0xBB8));
        local_c4.x = fVar3;
        f32 fVar4 = dVar9 * cM_ssin(i_this->m2BC * (REG0_S(5) + 0xB86) + i * (REG0_S(6) + 0xFA0));
        local_c4.y = fVar4;
        local_c4.z = dVar9 * cM_scos(i_this->m2BC * (REG0_S(7) + 0xAF0) + i * (REG0_S(8) + 0xDAC));
        f32 fVar5 = fVar3 + (hand_i->mPos.x - hand_i[1].mPos.x);
        f32 fVar6 = (hand_i->mPos.y - fVar1) + fVar4;
        f32 fVar7 = fVar2 + i_this->m2F8;
        if (fVar6 < fVar7) {
            fVar6 = fVar7;
        }
        f32 fVar8 = fVar6 - hand_i[1].mPos.y;
        f32 fVar9_2 = local_c4.z + (hand_i->mPos.z - hand_i[1].mPos.z);
        s16 angle_x = cM_atan2s(fVar5, fVar9_2);
        f32 fVar10 = (fVar5 * fVar5) + (fVar9_2 * fVar9_2);
        if (fVar10 > f4) {
            fVar10 = std::sqrtf(fVar10);
        }
        s16 angle_y = -cM_atan2s(fVar8, fVar10);
        mDoMtx_YrotS(*calc_mtx, angle_x);
        mDoMtx_XrotM(*calc_mtx, angle_y);
        if (i == 8) {
            f1 = i_this->m2E8 - 10.0f;
            pos.z = f1;
            if (f1 < 0.0f) {
                pos.z = 0.0f;
            }
        } else {
            pos.z = i_this->m2E8;
        }
        MtxPosition(&pos, &pos2);
        hand_i->mPos = (cXyz&)hand_i[1].mPos + pos2;
    }
    i_this->m2D4 = i_this->m33C[9].mPos;
    pos3 = (cXyz&)i_this->m33C[8].mPos - i_this->m33C[9].mPos;
    i_this->m2E0 = -cM_atan2s(pos3.y, pos3.z);
    i_this->m2E2 = cM_atan2s(pos3.x, std::sqrtf(pos3.y * pos3.y + pos3.z * pos3.z));
    hand_mtx_set(i_this);
    if (i_this->mpEmitterA14 == NULL && i_this->mA18 != 0) {
        i_this->mpEmitterA14 = dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, (cXyz*)&i_this->m33C[0].mPos, NULL, NULL, 0xFF);
    }
    if (i_this->mpEmitterA14 != NULL) {
        pos4 = (cXyz&)i_this->m33C[0].mPos - i_this->m33C[1].mPos;
        pos.x = pos4.x;
        pos.y = pos4.y;
        pos.z = pos4.z;
        int angle_x = cM_atan2s(pos.x, pos.z);
        f32 fVar11 = (pos.x * pos.x) + (pos.z * pos.z);
        if (fVar11 > 0.0f) {
            fVar11 = std::sqrtf(fVar11);
        }
        s16 angle_y = -cM_atan2s(pos.y, fVar11);
        i_this->mpEmitterA14->setGlobalTranslation(i_this->m33C[0].mPos.x, i_this->m33C[0].mPos.y, i_this->m33C[0].mPos.z);
        csXyz angle;
        angle.x = angle_y;
        angle.y = angle_x;
        angle.z = 0;
        i_this->mpEmitterA14->setGlobalRotation(angle);
        if (i_this->m2C2[1] == 1) {
            i_this->mpEmitterA14->becomeInvalidEmitter();
            i_this->mpEmitterA14 = NULL;
            i_this->mA18 = 0;
        }
    }
}

/* 000014F4-00002614       .text hand_move__FP9sss_class */
void hand_move(sss_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = i_this;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    fopAc_ac_c* link_player = dComIfGp_getLinkPlayer();
    dBgS_GndChk gndChk;
    cXyz pos;
    cXyz pos2;
    cXyz pos3;
    cXyz pos4;
    cXyz pos5;
    cXyz pos6;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    f32 f8;
    f32 f9;
    f32 f10;
    f32 f11;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 f15;
    f32 f17;
    f32 f18;
    f32 f19;
    f32 f20;
    f32 f21;
    f32 f22;

    u8 keep_3 = 0;
    u8 keep_angle = 0;
    f3 = 0.1f;
    f5 = 8.0f;
    f4 = f3;
    f32 f27 = 0.0f;
    f6 = 30.0f;
    f8 = 1.0f;
    f9 = f27;
    f32 dist = fopAcM_searchPlayerDistance(actor);
    f22 = 5.0f;
    if (i_this->m2B9 != 0xFF) {
        f10 = 10.0f * i_this->m2B9;
    } else {
        f10 = 1000.0f;
    }
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, actor->current.angle.x);
    s8 cut = 0;
    switch (i_this->m2C0) {
    case 0:
        pos.x = actor->current.pos.x;
        pos.y = actor->current.pos.y;
        pos.z = actor->current.pos.z;
        f6 = 0.0f;
        f8 = 0.5f;
        f9 = -20.0f;
        if (i_this->m2C2[0] == 0) {
            if (i_this->m2BA != 0) {
                if (dComIfGs_isSwitch(i_this->m2BA, (s8)actor->current.roomNo) || REG0_S(0) != 0) {
                    i_this->m2C0 = 1;
                    i_this->m2C2[0] = 0x1E;
                    hand_open(i_this);
                    cut = 1;
                }
            } else if (dist < f10) {
                i_this->m2C0 = 1;
                i_this->m2C2[0] = 0x1E;
                hand_open(i_this);
                cut = 1;
            }
        }
        if (std::fabsf(i_this->m2C8.y - actor->current.pos.y) < 5.0f && cut != 0) {
            if (i_this->m2B8 == 1) {
                mDoAud_seStart(JA_SE_OBJ_SVINE_OUT_WATER, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            } else {
                mDoAud_seStart(JA_SE_OBJ_SVINE_OUT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
        }
        break;
    case 1:
        pos.x = (50.0f + REG0_F(13)) * cM_ssin(i_this->m2BC * 0x258);
        pos.y = 250.0f;
        pos.z = (50.0f + REG0_F(13)) * cM_ssin(i_this->m2BC * 0x2BC);
        MtxPosition(&pos, &pos2);
        pos = pos2 + actor->current.pos;
        if (i_this->m2C2[0] == 0 && dist < 300.0f + REG0_F(14)) {
            i_this->m2C0 = 2;
        }
        if (dist > 100.0f + f10) {
            i_this->m2C0 = 0;
        }
        break;
    case 2:
        f5 = 15.0f;
        f27 = 10.0f;
        f4 = 0.5f;
        keep_angle = 1;
        pos.x = player->current.pos.x;
        f11 = player->current.pos.y;
        pos.y = f11;
        pos.z = player->current.pos.z;
        pos.y = f11 + 70.0f;
        if (dist > 450.0f + REG0_F(14)) {
            i_this->m2C0 = 1;
            actor->speedF = 0.0f;
        }
        pos2 = pos - i_this->m2C8;
        f12 = PSVECSquareMag(&pos2);
        f12 = std::sqrtf(f12);
        if (f12 < 20.0f && player == link_player) {
            i_this->m2C0 = 3;
            hand_close(i_this);
            mDoAud_seStart(JA_SE_OBJ_SVINE_GRASP, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            /* fallthrough to case 3 */
        } else {
            break;
        }
    case 3:
        player->onVineCatch();
        player->setFace(daPy_py_c::daPyFace_TIYAYA);
        if (dComIfGs_getMagic() != 0) {
            g_dComIfG_gameInfo.play.field_0x4965 |= 1;
            mDoAud_seStart(JA_SE_OBJ_ATK_VINE_MP_SUCK, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            if (!(i_this->m2BC & 0x1F)) {
                dComIfGp_setItemMagicCount(-1);
            }
        }
        f13 = 400.0f + REG6_F(2);
        if (dist > f13) {
            f14 = (0.1f + REG6_F(0)) * (dist - f13);
            f15 = 100.0f + REG6_F(1);
            if (f14 > f15) {
                f14 = f15;
            }
            player->setOutPower(f14, (s16)(fopAcM_searchPlayerAngleY(actor) + 0x8000), 0);
        }
        pos.x = player->current.pos.x;
        f11 = player->current.pos.y;
        pos.y = f11;
        pos.z = player->current.pos.z;
        pos.y = f11 + 70.0f;
        f5 = 200.0f;
        f3 = 1.0f;
        f4 = 5.0f;
        i_this->m2F4 = 10.0f + REG6_F(6);
        if (dist > 800.0f) {
            i_this->m2C0 = 1;
            actor->speedF = 30.0f;
            hand_open(i_this);
        }
        break;
    case 5:
        f22 = 50.0f;
        i_this->m2F4 = f22;
        keep_3 = 1;
        f6 = 25.0f;
        f8 = 1.0f;
        i_this->m2C8 += actor->speed;
        actor->speed.y -= 3.0f;
        i_this->m2C6 = 5;
        Vec v;
        v.y = i_this->m2C8.y;
        v.z = i_this->m2C8.z;
        v.y += 200.0f;
        v.x = i_this->m2C8.x;
        gndChk.SetPos(&v);
        i_this->m2F8 = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (i_this->m2F8 == -1.0e9f || i_this->m2C8.y <= i_this->m2F8 + 10.0f) {
            i_this->m2C8.y = i_this->m2F8 + 10.0f;
            i_this->m2C2[0] = 0x64;
            i_this->m2C0 = 6;
        }
        break;
    case 6:
        keep_3 = 1;
        f22 = 0.0f;
        i_this->m2C6 = 0xA;
        if (i_this->m2C2[0] < 0x28) {
            f6 = f22;
            f8 = 1.0f;
            i_this->m2C8.y -= 2.0f;
        }
        if (i_this->m2C2[0] == 0) {
            i_this->m2C8 = actor->current.pos;
            i_this->m2C0 = 0;
            i_this->m2E8 = 0.0f;
            i_this->m2FC = 0.0f;
        }
        break;
    }
    cLib_addCalc2(&i_this->m2E8, f6, 0.5f, f8);
    cLib_addCalc2(&i_this->m2F0, f27, 1.0f, 0.2f);
    cLib_addCalc2(&i_this->m2F4, f22, 1.0f, 0.3f);
    if (keep_3 == 0) {
        cLib_addCalc2(&actor->speedF, f5, 1.0f, f4);
        if (i_this->mA08 > 1.0f && i_this->m2C0 != 3) {
            mDoMtx_YrotS(*calc_mtx, i_this->mA0C);
            pos.x = 0.0f;
            pos.y = 100.0f + REG6_F(9);
            pos.z = i_this->mA08;
            MtxPosition(&pos, &pos2);
            pos = pos2 + actor->current.pos;
            f3 = 0.1f;
            actor->speedF = 0.2f * i_this->mA08;
            if (actor->speedF > 30.0f + REG6_F(8)) {
                actor->speedF = 30.0f + REG6_F(8);
            }
        }
        cLib_addCalc0(&i_this->mA08, 1.0f, 5.0f + REG6_F(7));
        cLib_addCalc2(&i_this->m2C8.x, pos.x, f3, actor->speedF);
        cLib_addCalc2(&i_this->m2C8.y, pos.y, f3, actor->speedF);
        cLib_addCalc2(&i_this->m2C8.z, pos.z, f3, actor->speedF);
        cLib_addCalc2(&actor->current.pos.y, actor->home.pos.y + f9, 0.5f, 0.5f);
        if (keep_angle && actor->current.angle.x == 0) {
            cLib_addCalcAngleS2(&actor->current.angle.y, fopAcM_searchPlayerAngleY(actor), 0x10, 0x800);
        }
        control1(i_this);
        control2(i_this);
    } else {
        cut_control1(i_this);
        cut_control2(i_this);
        sss_s* src = i_this->m490;
        cXyz* posArr = i_this->m454.getPos(0);
        u8* sizeArr = i_this->m454.getSize(0);
        for (int i = 0; i < 5; i++, src++, posArr++, sizeArr++) {
            *posArr = src->mPos;
            *sizeArr = (u8)src->mSize;
        }
        cLib_addCalc0(&i_this->m2FC, 1.0f, 1.0f + REG0_F(1));
    }
    control3(i_this);
    i_this->mpMorf->play(NULL, 0, 0);
    sss_s* src = i_this->m33C;
    cXyz* posArr = i_this->m300.getPos(0);
    u8* sizeArr = i_this->m300.getSize(0);
    for (int i = 0; i < 10; i++, src++, posArr++, sizeArr++) {
        *posArr = src->mPos;
        *sizeArr = (u8)src->mSize;
    }
    cXyz* pLinePos = i_this->m300.getPos(0);
    actor->eyePos = pLinePos[5];
    actor->attention_info.position = actor->eyePos;
    i_this->mStts.Move();
    if (keep_3 == 0) {
        i_this->m8DC.SetC(actor->eyePos);
    } else {
        i_this->m8DC.SetC(non_pos);
    }
    u8 hit = 0;
    dComIfG_Ccsp()->Set(&i_this->m8DC);
    for (int i = 0; i < 3; i++) {
        int idx = (i_this->m2BC & 3) + i * 2;
        cXyz pos = pLinePos[idx % 10];
        if (keep_3 == 0) {
            i_this->mSph[i].SetC(pos);
        } else {
            i_this->mSph[i].SetC(non_pos);
        }
        if (i_this->m2C0 == 3) {
            i_this->mSph[i].OffCoSetBit();
        } else {
            i_this->mSph[i].OnCoSetBit();
        }
        dComIfG_Ccsp()->Set(&i_this->mSph[i]);
    }
    for (int i = 0; i < 3; i++) {
        if (i_this->mSph[i].ChkTgHit()) {
            hit = i + 1;
            break;
        }
    }
    if ((hit != 0 || i_this->m8DC.ChkTgHit()) && i_this->m2C6 == 0) {
        CcAtInfo atInfo;
        atInfo.pParticlePos = NULL;
        i_this->m2C6 = 0x14;
        if (hit == 0) {
            atInfo.mpObj = i_this->m8DC.GetTgHitObj();
            atInfo.pParticlePos = i_this->m8DC.GetTgHitPosP();
            at_power_check(&atInfo);
            if (atInfo.mResultingAttackType == 8) {
                i_this->mA08 = 100.0f + REG6_F(6);
                i_this->mA0C = fopAcM_searchPlayerAngleY(actor) + 0x8000;
                return;
            }
        } else {
            atInfo.mpObj = i_this->mSph[hit - 1].GetTgHitObj();
            atInfo.pParticlePos = i_this->mSph[hit - 1].GetTgHitPosP();
        }
        mDoAud_seStart(JA_SE_LK_LAST_HIT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        mDoAud_seStart(JA_SE_OBJ_SVINE_CRASH, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        i_this->m2C0 = 5;
        i_this->speed.x = cM_rndFX(10.0f);
        i_this->speed.y = 30.0f + cM_rndF(10.0f);
        i_this->speed.z = cM_rndFX(10.0f);
        cXyz scale(0.3f, 0.3f, 0.3f);
        dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, &actor->eyePos, NULL, &scale, 0xFF);
        i_this->mA18 = 1;
        sss_s* dst = i_this->m490;
        sss_s* src = i_this->m33C;
        for (int i = 0; i < 5; i++, dst++, src++) {
            dst->mPos = src->mPos;
            dst->mSize = src->mSize;
            if (i == 4) {
                pos3 = *(cXyz*)&dst->mPos - (dst - 1)->mPos;
                f17 = PSVECSquareMag(&pos3);
                f17 = std::sqrtf(f17);
                i_this->m2FC = (1.5f + REG0_F(2)) * f17;
            }
        }
        hand_open(i_this);
    }
}

/* 00002614-00002618       .text hand_main__FP9sss_class */
void hand_main(sss_class*) {
}

/* 00002618-0000269C       .text daSss_Execute__FP9sss_class */
static BOOL daSss_Execute(sss_class* i_this) {
    i_this->m2BC++;
    for (int i = 0; i < 2; i++) {
        if (i_this->m2C2[i] != 0) {
            i_this->m2C2[i]--;
        }
    }
    if (i_this->m2C6 != 0) {
        i_this->m2C6--;
    }
    if (i_this->m2B8 == 0) {
        hand_main(i_this);
    } else {
        hand_move(i_this);
    }
    return TRUE;
}

/* 0000269C-000026A4       .text daSss_IsDelete__FP9sss_class */
static BOOL daSss_IsDelete(sss_class*) {
    return TRUE;
}

/* 000026A4-00002720       .text daSss_Delete__FP9sss_class */
static BOOL daSss_Delete(sss_class* i_this) {
    dComIfG_resDelete(&i_this->mPhase, "Sss");
    if (i_this->mpEmitterA10 != NULL) {
        i_this->mpEmitterA10->becomeInvalidEmitter();
    }
    if (i_this->mpEmitterA14 != NULL) {
        i_this->mpEmitterA14->becomeInvalidEmitter();
    }
    return TRUE;
}

/* 00002720-000028A0       .text useHeapInit__FP9sss_class */
BOOL useHeapInit(sss_class* i_this) {
    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BMD_SSS_HAND_e),
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e),
        J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1,
        NULL, 0, 0x11020203
    );
    if (i_this->mpMorf->getModel() == NULL) {
        return FALSE;
    }
    if (!i_this->m300.init(1, 0xA, (ResTIMG*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BTI_SSS_e), 1)) {
        return FALSE;
    }
    return i_this->m454.init(1, 5, (ResTIMG*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BTI_SSS_e), 1) != 0 ? 1 : 0;
}

/* 000028A0-000028C0       .text daSss_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSss_solidHeapCB(fopAc_ac_c* a_this) {
    sss_class* i_this = (sss_class*)a_this;
    return useHeapInit(i_this);
}

/* 000028C0-00002BB4       .text daSss_Create__FP10fopAc_ac_c */
static cPhs_State daSss_Create(fopAc_ac_c* a_this) {
    /* Nonmatching */
    static dCcD_SrcSph tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 20.0f,
        }},
    };
    static dCcD_SrcSph bm_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_BOOMERANG | AT_TYPE_WIND,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 80.0f,
        }},
    };

    fopAc_ac_c* actor = a_this;
    fopAcM_ct(actor, sss_class);
    sss_class* i_this = (sss_class*)a_this;
    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "Sss");
    if (res == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    } else if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    if (!fopAcM_entrySolidHeap(actor, daSss_solidHeapCB, 0x3040)) {
        return cPhs_ERROR_e;
    }
    non_pos.set(0.0f, 30000.0f, -20000.0f);
    i_this->m2B8 = fopAcM_GetParam(actor) & 0xFF;
    if (i_this->m2B8 == 0xFF) {
        i_this->m2B8 = 0;
    }
    if (i_this->m2B8 != 1) {
        i_this->m2B8 = 0x23;
    }
    i_this->m2B9 = (fopAcM_GetParam(actor) >> 8) & 0xFF;
    i_this->m2BA = (fopAcM_GetParam(actor) >> 0x10) & 0xFF;
    if (i_this->m2BA == 0xFF) {
        i_this->m2BA = 0;
    }
    actor->health = 2;
    i_this->m2BC = (s16)cM_rndF(10000.0f);
    i_this->mStts.Init(0xFF, 0xFF, actor);
    for (int i = 0; i < 3; i++) {
        i_this->mSph[i].Set(tg_sph_src);
        i_this->mSph[i].SetStts(&i_this->mStts);
    }
    i_this->m8DC.Set(bm_sph_src);
    i_this->m8DC.SetStts(&i_this->mStts);
    i_this->m2C8 = actor->current.pos;
    i_this->m2C8.y = actor->current.pos.y;
    i_this->m2C8.z = actor->current.pos.z;
    if (i_this->m2BA == 0) {
        i_this->m2C8.y += 230.0f;
    }
    daSss_Execute(i_this);
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daSss_Method = {
    (process_method_func)daSss_Create,
    (process_method_func)daSss_Delete,
    (process_method_func)daSss_Execute,
    (process_method_func)daSss_IsDelete,
    (process_method_func)daSss_Draw,
};

actor_process_profile_definition g_profile_SSS = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_SSS_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sss_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_SSS_e,
    /* Actor SubMtd */ &l_daSss_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
