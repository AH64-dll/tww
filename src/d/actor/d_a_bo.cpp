/**
 * d_a_bo.cpp
 * Enemy - Boko Baba
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bo.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "f_pc/f_pc_name.h"
#include "d/actor/d_a_player.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_audio.h"
#include "f_op/f_op_actor_mng.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_malloc.h"
#include "d/d_kankyo.h"
#include "d/d_camera.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "f_op/f_op_camera.h"
#include "d/d_material.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_controller_pad.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_particle_name.h"

static const GXColor l_smokeColor = {0xA0, 0xA0, 0x80, 0xFF};


/* 000000EC-000001E8       .text smoke_set__FP8bo_class */
static void smoke_set(bo_class* i_this) {
    /* Nonmatching */
    GXColor color = l_smokeColor;
    i_this->mSmokeEcallBack.remove();
    dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE01, &i_this->m39C, &i_this->shape_angle, NULL, 0xB9, &i_this->mSmokeEcallBack, i_this->current.roomNo, NULL, NULL, NULL);
    JPABaseEmitter* emitter = i_this->mSmokeEcallBack.getEmitter();
    if (emitter != NULL) {
        emitter->mGlobalParticleScale.set(3.0f, 3.0f, 3.0f);
        emitter->setRate(30.0f);
        emitter->setMaxFrame(1);
        emitter->setAwayFromCenterSpeed(10.0f);
        emitter->setAwayFromAxisSpeed(10.0f);
        emitter->setStatus(0x40);
        i_this->mSmokeEcallBack.setColor(color);
    }
}

/* 000001E8-00000638       .text nodeCallBack_UP__FP7J3DNodei */
static BOOL nodeCallBack_UP(J3DNode* node, int calcTiming) {
    /* Nonmatching */
    if (calcTiming == 0) {
        int jntNo = ((J3DJoint*)node)->getJntNo();
        BOOL isSet = FALSE;
        J3DModel* model = j3dSys.getModel();
        bo_class* i_this = (bo_class*)model->getUserArea();
        if (i_this != NULL) {
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            PSMTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo <= 0xA) {
                f32 scale = 0.025f * jntNo;
                mDoMtx_YrotM(*calc_mtx, (s16)(i_this->m33A.y * scale));
                mDoMtx_XrotM(*calc_mtx, (s16)(i_this->m33A.x * scale));
                mDoMtx_ZrotM(*calc_mtx, (s16)(i_this->m33A.z * scale));
                isSet = TRUE;
            }
            if (jntNo == 1) {
                cXyz zero(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m2F8);
                isSet = TRUE;
            }
            if (jntNo == 0xA) {
                cXyz zero(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m328);
                isSet = TRUE;
            }
            if (jntNo == 0xB) {
                cXyz zero(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m2E0);
                isSet = TRUE;
            }
            if (jntNo == 4) {
                cXyz zero(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m310);
                isSet = TRUE;
            }
            if (jntNo >= 5 && jntNo <= 7) {
                f32 scale = (f32)(s16)(8 - jntNo) * 1.75f;
                mDoMtx_YrotM(*calc_mtx, (s16)(i_this->m352.y * scale));
                mDoMtx_ZrotM(*calc_mtx, (s16)(i_this->m352.z * scale));
                isSet = TRUE;
            }
            if (jntNo == 8) {
                mDoMtx_YrotM(*calc_mtx, i_this->m334.y + g_regHIO.mChild[12].mShortRegs[3]);
                mDoMtx_XrotM(*calc_mtx, i_this->m334.z + g_regHIO.mChild[12].mShortRegs[5]);
                cXyz zero(0.0f, 0.0f, 0.0f);
                MtxPosition(&zero, &i_this->m31C);
                isSet = TRUE;
            }
            if (jntNo == 0xC) {
                if (i_this->m2CC != 0) {
                    cXyz pos(0.0f, 0.0f, 0.0f);
                    cXyz dst;
                    MtxPosition(&pos, &dst);
                    f32 dx = i_this->m31C.x - dst.x;
                    f32 dz = i_this->m31C.z - dst.z;
                    if (i_this->m2CD != 0) {
                        csXyz angle;
                        angle.x = -0x5FB4;
                        angle.y = cM_atan2s(dz, dx) + 0x7FFF;
                        angle.z = 0;
                        player->setPlayerPosAndAngle(&dst, &angle);
                    } else {
                        csXyz angle;
                        angle.x = 0x5BCC;
                        angle.y = cM_atan2s(dz, dx);
                        angle.z = 0;
                        player->setPlayerPosAndAngle(&dst, &angle);
                    }
                    isSet = TRUE;
                }
            }
            if (isSet) {
                PSMTXCopy(*calc_mtx, model->getAnmMtx(jntNo));
                PSMTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 00000638-000006C8       .text nodeCallBack_DW__FP7J3DNodei */
static BOOL nodeCallBack_DW(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        int jntNo = ((J3DJoint*)node)->getJntNo();
        J3DModel* model = j3dSys.getModel();
        bo_class* i_this = (bo_class*)model->getUserArea();
        if (i_this != NULL && jntNo == 9) {
            PSMTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cXyz zero(0.0f, 0.0f, 0.0f);
            MtxPosition(&zero, &i_this->m304);
        }
    }
    return TRUE;
}

/* 000006C8-0000079C       .text execute__22yodare_ato_PcallBack_cFP14JPABaseEmitterP15JPABaseParticle */
void yodare_ato_PcallBack_c::execute(JPABaseEmitter* i_emitter, JPABaseParticle* i_particle) {
    /* Nonmatching */
    f32 y = i_particle->mGlobalPosition.y;
    cXyz pos(i_particle->mGlobalPosition.x, y + 20.0f, i_particle->mGlobalPosition.z);
    mGndChk.SetPos(&pos);
    pos.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (pos.y > y) {
        dComIfGp_particle_set(dPa_name::ID_IT_SN_BKBABA_YODAPOTA00, &pos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
    }
}

/* 0000079C-00000930       .text draw_SUB__FP8bo_class */
static void draw_SUB(bo_class* i_this) {
    /* Nonmatching */
    if (i_this->mType == 0 || i_this->mType == 2) {
        if (i_this->mType == 2) {
            i_this->m304 = i_this->current.pos;
            i_this->mpBaseAnm->play();
        }
        mDoMtx_stack_c::transS(i_this->m304.x, i_this->m304.y + i_this->m394, i_this->m304.z);
        mDoMtx_stack_c::YrotM(i_this->m348);
        mDoMtx_stack_c::XrotM(i_this->shape_angle.x);
        mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);
        mDoMtx_stack_c::transM(0.0f, -i_this->m394, 0.0f);
        Mtx& base = i_this->mpMorf->getModel()->getBaseTRMtx();
        MtxP now = mDoMtx_stack_c::get();
        PSMTXCopy(now, base);
        i_this->mpMorf->calc();
        if (i_this->mType == 0) {
            enemy_fire(&i_this->mEnemyFire);
        }
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        mDoMtx_stack_c::transS(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z);
        mDoMtx_stack_c::YrotM(i_this->shape_angle.y);
        mDoMtx_stack_c::XrotM(i_this->shape_angle.x);
        mDoMtx_stack_c::ZrotM(i_this->shape_angle.z);
        Mtx& base2 = i_this->mpMorf2->getModel()->getBaseTRMtx();
        MtxP now2 = mDoMtx_stack_c::get();
        PSMTXCopy(now2, base2);
        i_this->mpMorf2->calc();
    }
    g_env_light.settingTevStruct(0, &i_this->current.pos, &i_this->tevStr);
}

/* 00000930-00000AD4       .text daBO_Draw__FP8bo_class */
static BOOL daBO_Draw(bo_class* i_this) {
    /* Nonmatching */
    if (REG13_S(5) != 0) {
        return TRUE;
    }
    u8 isIce = 0;
    if (i_this->mType == 0 || i_this->mType == 2) {
        g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &i_this->tevStr);
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        if (i_this->mEnemyIce.mLightShrinkTimer == 0) {
            g_env_light.setLightTevColorType(i_this->mpMorf2->getModel(), &i_this->tevStr);
        }
    }
    dSnap_RegistFig(DSNAP_TYPE_UNKB2, i_this, i_this->current.pos, i_this->m348, 1.0f, 1.0f, 1.0f);
    if (i_this->mType == 0) {
        if (i_this->mEnemyIce.mFreezeTimer > 0x14) {
            dMat_control_c::iceEntryDL(i_this->mpMorf, -1, &i_this->mInvisibleModel);
            isIce = 1;
        }
    }
    if (!isIce) {
        if (i_this->mType == 0 || i_this->mType == 2) {
            J3DModel* model = i_this->mpMorf->getModel();
            if (i_this->mType == 2) {
                J3DModelData* modelData = model->getModelData();
                i_this->mpBaseAnm->entry(modelData, i_this->mpBaseAnm->getFrame());
            }
            i_this->mpMorf->entryDL();
            if (i_this->mType == 2) {
                i_this->mpBaseAnm->remove(model->getModelData());
            }
        }
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        if (i_this->mEnemyIce.mLightShrinkTimer == 0) {
            i_this->mpMorf2->entryDL();
        }
    }
    return TRUE;
}

/* 00000AD4-00000CD4       .text anm_init__FP8bo_classifUcfii */
static void anm_init(bo_class* i_this, int i_anmIdx, f32 i_playSpeed, u8 i_attr, f32 i_rate, int i_soundRes, int i_flag) {
    /* Nonmatching */
    i_this->m2DC = i_anmIdx; // 0x2DC
    if (i_flag == 0) {
        if (i_soundRes >= 0) {
            J3DAnmTransform* soundAnm = (J3DAnmTransform*)dComIfG_getObjectRes("BO", i_soundRes);
            J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("BO", i_anmIdx);
            i_this->mpMorf->setAnm(anm, i_attr, i_playSpeed, i_rate, 0.0f, -1.0f, soundAnm);
        } else {
            J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("BO", i_anmIdx);
            i_this->mpMorf->setAnm(anm, i_attr, i_playSpeed, i_rate, 0.0f, -1.0f, NULL);
        }
    } else {
        if (i_soundRes >= 0) {
            J3DAnmTransform* soundAnm = (J3DAnmTransform*)dComIfG_getObjectRes("BO", i_soundRes);
            J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("BO", i_anmIdx);
            i_this->mpMorf2->setAnm(anm, i_attr, i_playSpeed, i_rate, 0.0f, -1.0f, soundAnm);
        } else {
            J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("BO", i_anmIdx);
            i_this->mpMorf2->setAnm(anm, i_attr, i_playSpeed, i_rate, 0.0f, -1.0f, NULL);
        }
    }
}

/* 00000CD4-00000E24       .text shock_damage_check__FP8bo_class */
static BOOL shock_damage_check(bo_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (player->checkHammerQuake()) {
        cXyz diff = player->getSwordTopPos();
        diff.x -= i_this->current.pos.x;
        diff.z -= i_this->current.pos.z;
        f32 dist = std::sqrtf(diff.x * diff.x + diff.z * diff.z);
        if (dist < 1000.0f) {
            mDoAud_seStart(0x2855, &i_this->eyePos, 0x31, dComIfGp_getReverb(i_this->current.roomNo));
            return TRUE;
        }
    }
    return FALSE;
}

static s16 pl_cut_real_no_dt[32] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
};

static u8 nokezoru_on_off_dt[32] = {
    0, 0, 0, 0,
    0, 1, 1, 1,
    1, 1, 1, 0,
    1, 1, 1, 1,
    1, 1, 1, 1,
    0, 1, 0, 1,
    0, 1, 1, 1,
    1, 1, 1, 1,
};

/* 00000E24-000013A4       .text head_atari_check__FP8bo_class */
static BOOL head_atari_check(bo_class* i_this) {
    /* Nonmatching */
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->mStts.Move();
    if (i_this->m366[4] != 0) {
        return FALSE;
    }
    if (shock_damage_check(i_this)) {
        i_this->m2CA = 1;
        return TRUE;
    }
    if (!i_this->mSph.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hit_obj = i_this->mSph.GetTgHitObj();
    if (hit_obj == NULL) {
        return FALSE;
    }
    i_this->m358 = *i_this->mSph.GetTgHitPosP();
    i_this->m366[4] = (s16)(8.0f + g_regHIO.mChild[8].mFloatRegs[10]);
    i_this->m370 = cM_atan2s(player->current.pos.x - i_this->m2E0.x, player->current.pos.z - i_this->m2E0.z);
    i_this->m2CA = 0;
    i_this->m364 = 0;
    i_this->m2CA = 1;
    mDoAud_onEnemyDamage();
    u32 hit_type = hit_obj->GetAtType();
    switch (hit_type) {
    case AT_TYPE_GRAPPLING_HOOK:
        if ((s8)i_this->stealItemLeft > 0) {
            u8 old_health = i_this->health;
            i_this->health = 10;
            CcAtInfo atInfo;
            atInfo.mpObj = i_this->mSph.GetTgHitObj();
            atInfo.pParticlePos = NULL;
            cc_at_check(i_this, &atInfo);
            i_this->health = old_health;
        }
        g_dComIfG_gameInfo.play.getParticle()->set(dPa_control_c::dPtclGroup_Normal_e, 0x27B, &i_this->attention_info.position, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        i_this->m2CA = 0;
        mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
        JAIZelBasic::zel_basic->seStart(0x2836, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        return TRUE;
    case AT_TYPE_SWORD: {
        int i;
        for (i = 0; i < 0x20; i++) {
            if (pl_cut_real_no_dt[i] == player->getCutType()) {
                break;
            }
        }
        if (i >= 0x20) {
            return FALSE;
        }
        i_this->m2CA = nokezoru_on_off_dt[i];
        return TRUE;
    }
    case AT_TYPE_BOOMERANG: {
        i_this->m2CA = 1;
        i_this->m364 = (s16)(u8)(g_regHIO.mChild[8].mShortRegs[5] + 5);
        i_this->mSph.ClrTgHit();
        i_this->attention_info.flags &= ~4;
        i_this->m398 = 1.0f;
        dPa_control_c* particle = g_dComIfG_gameInfo.play.getParticle();
        particle->set(dPa_control_c::dPtclGroup_Normal_e, 0x10, &i_this->m358, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        cXyz scale(2.0f, 2.0f, 2.0f);
        particle->set(dPa_control_c::dPtclGroup_Normal_e, 0xF, &i_this->m358, &player->shape_angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
        JAIZelBasic::zel_basic->seStart(0x2828, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        return TRUE;
    }
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_FIRE:
        i_this->mEnemyFire.mFireDuration = (s16)(34.0f + g_regHIO.mChild[8].mFloatRegs[12]);
        i_this->m2D0 = 1;
        i_this->attention_info.flags = 0;
        return TRUE;
    case AT_TYPE_ICE_ARROW:
        i_this->mEnemyIce.mFreezeDuration = (s16)(80.0f + g_regHIO.mChild[8].mFloatRegs[13]);
        i_this->m2D0 = 2;
        i_this->mEnemyIce.m00C = 1;
        i_this->attention_info.flags = 0;
        i_this->health = 30;
        return TRUE;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 80.0f + g_regHIO.mChild[8].mFloatRegs[13];
        i_this->attention_info.flags = 0;
        i_this->m2D0 = 3;
        fopAcM_create(0xD7, (i_this->m2C1 << 8) | 1, &i_this->current.pos, i_this->current.roomNo, &i_this->shape_angle, &i_this->scale, 0, NULL);
        return TRUE;
    case AT_TYPE_SKULL_HAMMER:
        if (player->getCutType() != 0x11) {
            i_this->m2CA = 2;
        } else {
            i_this->m2CA = 1;
        }
        return TRUE;
    default:
        i_this->m2CA = 1;
        return TRUE;
    }
}

/* 000013A4-0000170C       .text nokezori_damage_rtn__FP8bo_class */
static void nokezori_damage_rtn(bo_class* i_this) {
    /* Nonmatching */
    s16 angle = i_this->m370 - i_this->m348;
    anm_init(i_this, 7, 5.0f, 0, 1.0f, -1, 0);
    mDoMtx_YrotS(*calc_mtx, angle);
    cXyz sp14(0.0f, 0.0f, 6250.0f);
    cXyz sp8;
    MtxPosition(&sp14, &sp8);
    i_this->m340.z = (s16)sp8.x;
    i_this->m340.y = (s16)sp8.z;
    i_this->m334.setall(0);
    i_this->scale.y = 1.75f;
    i_this->m37C = 1200;
    cCcD_Obj* hit_obj = i_this->mSph.GetTgHitObj();
    if (hit_obj != NULL) {
        u32 hit_type = hit_obj->GetAtType();
        if (hit_type & AT_TYPE_SWORD) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            JAIZelBasic::zel_basic->seStart(0x2806, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else if (hit_type & AT_TYPE_BOKO_STICK) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            JAIZelBasic::zel_basic->seStart(0x2835, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else if (hit_type & AT_TYPE_SKULL_HAMMER) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            JAIZelBasic::zel_basic->seStart(0x2855, &i_this->eyePos, 0x31, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        } else if (!(hit_type & AT_TYPE_BOOMERANG)) {
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            JAIZelBasic::zel_basic->seStart(0x2836, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        }
    }
    i_this->m398 = 1.0f;
    i_this->m372 = 0;
    i_this->m376 = 0;
    i_this->m366[2] = 3;
    if (i_this->m2D0 == 0) {
        i_this->mAction = 0;
        i_this->m2C5 = 5;
    } else {
        i_this->mAction = 4;
        i_this->m2C5 = 0x32;
    }
}

/* 0000170C-00001BB8       .text body_atari_check__FP8bo_class */
static BOOL body_atari_check(bo_class* i_this) {
    /* Nonmatching */
    if (i_this->m366[2] != 0) {
        return FALSE;
    }
    if (!i_this->mCyl.ChkTgHit()) {
        return FALSE;
    }
    cCcD_Obj* hit_obj = i_this->mCyl.GetTgHitObj();
    if (hit_obj == NULL) {
        return FALSE;
    }
    u32 hit_type = hit_obj->GetAtType();
    switch (hit_type) {
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_FIRE:
        i_this->mEnemyFire.mFireDuration = 0x50;
        i_this->m2D0 = 1;
        nokezori_damage_rtn(i_this);
        i_this->m2C8 = 0;
        i_this->m372 = 0;
        i_this->m374 = 0;
        g_dComIfG_gameInfo.play.getParticle()->set(dPa_control_c::dPtclGroup_Normal_e, 0x8109, &i_this->m328, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        return TRUE;
    case AT_TYPE_ICE_ARROW:
        i_this->mEnemyIce.mFreezeDuration = (s16)(80.0f + g_regHIO.mChild[8].mFloatRegs[13]);
        i_this->m2D0 = 2;
        i_this->mEnemyIce.m00C = 1;
        i_this->attention_info.flags = 0;
        i_this->health = 30;
        nokezori_damage_rtn(i_this);
        i_this->m2C8 = 0;
        i_this->m372 = 0;
        i_this->m374 = 0;
        g_dComIfG_gameInfo.play.getParticle()->set(dPa_control_c::dPtclGroup_Normal_e, 0x8109, &i_this->m328, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        return TRUE;
    case AT_TYPE_LIGHT_ARROW:
        i_this->mEnemyIce.mLightShrinkTimer = 1;
        i_this->mEnemyIce.mParticleScale = 1.0f;
        i_this->mEnemyIce.mYOffset = 80.0f + g_regHIO.mChild[8].mFloatRegs[13];
        i_this->attention_info.flags = 0;
        i_this->m2D0 = 3;
        fopAcM_create(0xD7, (i_this->m2C1 << 8) | 1, &i_this->current.pos, i_this->current.roomNo, &i_this->shape_angle, &i_this->scale, 0, NULL);
        nokezori_damage_rtn(i_this);
        i_this->m2C8 = 0;
        i_this->m372 = 0;
        i_this->m374 = 0;
        g_dComIfG_gameInfo.play.getParticle()->set(dPa_control_c::dPtclGroup_Normal_e, 0x8109, &i_this->m328, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
        JAIZelBasic::zel_basic->seStart(0x2828, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        return TRUE;
    default: {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        cXyz hit_pos = *i_this->mCyl.GetTgHitPosP();
        i_this->mSph.ClrTgHit();
        i_this->attention_info.flags &= ~4;
        i_this->m398 = 1.0f;
        dPa_control_c* particle = g_dComIfG_gameInfo.play.getParticle();
        particle->set(dPa_control_c::dPtclGroup_Normal_e, 0x10, &hit_pos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        cXyz scale(2.0f, 2.0f, 2.0f);
        particle->set(dPa_control_c::dPtclGroup_Normal_e, 0xF, &hit_pos, &player->shape_angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
        i_this->m364 = (s16)(u8)(g_regHIO.mChild[8].mShortRegs[5] + 5);
        i_this->mAction = 2;
        i_this->m2C5 = 0x14;
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
        JAIZelBasic::zel_basic->seStart(0x2828, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
        return TRUE;
    }
    }
}

/* 00001BB8-00002048       .text damage_check__FP8bo_class */
static BOOL damage_check(bo_class* i_this) {
    /* Nonmatching */
    if (head_atari_check(i_this)) {
        s16 angle = i_this->m370 - i_this->m348;
        if (i_this->m2CA == 2) {
            fopAc_ac_c* player = dComIfGp_getPlayer(0);
            cXyz hit_pos = *i_this->mSph.GetTgHitPosP();
            dPa_control_c* particle = g_dComIfG_gameInfo.play.getParticle();
            particle->set(dPa_control_c::dPtclGroup_Normal_e, 0x10, &hit_pos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            cXyz scale(2.0f, 2.0f, 2.0f);
            particle->set(dPa_control_c::dPtclGroup_Normal_e, 0xF, &hit_pos, &player->shape_angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
            i_this->mAction = 4;
            i_this->m2C5 = 0x28;
            mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            JAIZelBasic::zel_basic->seStart(0x2828, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            return TRUE;
        }
        i_this->mSph.ClrTgHit();
        if (i_this->m2CA == 1) {
            nokezori_damage_rtn(i_this);
        } else {
            if (g_regHIO.mChild[8].mFloatRegs[11] != 0.0f && i_this->m2C5 == 4) {
                return FALSE;
            }
            mDoAud_monsSeStart(0x484F, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            cXyz sp3C(0.0f, 0.0f, 2250.0f);
            cXyz sp30;
            mDoMtx_YrotS(*calc_mtx, angle);
            MtxPosition(&sp3C, &sp30);
            anm_init(i_this, 0x12, 2.0f, 0, 1.0f, -1, 0);
            i_this->m352.z = (s16)sp30.x;
            i_this->m352.y = (s16)sp30.z;
            i_this->m388 = -10000.0f;
            i_this->m37E = 0;
            i_this->m380 = 0x1C52;
            i_this->m382 = i_this->m370 - i_this->m348;
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            if (player->getCutType() == 3) {
                i_this->m382 -= 0x4000;
            } else if (player->getCutType() == 4) {
                i_this->m382 += 0x4000;
            }
            i_this->m37C = 0x800;
            cCcD_Obj* hit_obj = i_this->mSph.GetTgHitObj();
            if (hit_obj != NULL) {
                u32 hit_type = hit_obj->GetAtType();
                if (hit_type & AT_TYPE_SWORD) {
                    JAIZelBasic::zel_basic->seStart(0x2803, &i_this->eyePos, 0x31, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
                } else if (hit_type & AT_TYPE_BOKO_STICK) {
                    JAIZelBasic::zel_basic->seStart(0x2833, &i_this->eyePos, 0x31, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
                } else {
                    JAIZelBasic::zel_basic->seStart(0x2834, &i_this->eyePos, 0x31, dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
                }
            }
            i_this->mAction = 0;
            i_this->m2C5 = 4;
        }
        i_this->m2C8 = 0;
        i_this->m372 = 0;
        i_this->m374 = 0;
        g_dComIfG_gameInfo.play.getParticle()->set(dPa_control_c::dPtclGroup_Normal_e, 0x8109, &i_this->m328, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 00002048-00002080       .text angle_initial__FP8bo_class */
static void angle_initial(bo_class* i_this) {
    i_this->m33A.setall(0);
    i_this->m352.setall(0);
    i_this->m334.setall(0);
    i_this->m340.setall(0);
}

/* 00002080-00002170       .text wait_initial__FP8bo_class */
static void wait_initial(bo_class* i_this) {
    if (cM_rnd() < 0.5f) {
        anm_init(i_this, 0x15, 5.0f, 2, 1.0f, -1, 0);
    } else {
        anm_init(i_this, 0x16, 5.0f, 2, 1.0f, -1, 0);
    }
    i_this->m366[0] = (s16)(60.0f + cM_rndF(60.0f));
    i_this->mSph.ClrAtSet();
    i_this->mSph.ClrAtSet();
    i_this->mSph.SetAtSpl(dCcG_At_Spl_UNK0);
    i_this->mSph.OnCoSetBit();
    angle_initial(i_this);
    i_this->mAction = 0;
    i_this->m2C5 = 2;
}
/* 00002170-000022F8       .text start_bakutsuki_event_camera__FP10fopAc_ac_c */
static void start_bakutsuki_event_camera(fopAc_ac_c* i_this) {
    static cXyz cam_pos(40.0f, 10.0f, 280.0f);
    static cXyz ctr_pos(0.0f, 50.0f, 50.0f);
    static f32 cam_fovy = 75.0f;
    static s32 cam_timer = 30;
    dComIfGp_getCamera(0)->mCamera.StartEventCamera(0x5, fopAcM_GetID(i_this), "RelActor", "@STARTER", "RelUseMask", "--or", "Timer", &cam_timer, "Center", &ctr_pos, "Eye", &cam_pos, "Fovy", &cam_fovy, 0);
}

/* 000022F8-0000233C       .text end_event_camera__FP10fopAc_ac_c */
static void end_event_camera(fopAc_ac_c* i_this) {
    dComIfGp_getCamera(0)->mCamera.EndEventCamera(fopAcM_GetID(i_this));
}

/* 0000233C-00002FC4       .text bo_move__FP8bo_class */
static void bo_move(bo_class* i_this) {
    /* Nonmatching */
    dComIfG_play_c& play = g_dComIfG_gameInfo.play;
    fopAc_ac_c* player = play.getPlayer(0);

    switch (i_this->m2C5) {
    case 0:
        if (fopAcM_searchActorDistance(i_this, player) < 600.0f) {
            i_this->mCyl.OnTgSetBit();
            i_this->mSph.OnTgSetBit();
            i_this->mSph.OnCoSetBit();
            JAIZelBasic::zel_basic->seStart(0x5844, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                                1.0f, 1.0f, -1.0f, -1.0f, 0);
            mDoAud_monsSeStart(0x484D, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            anm_init(i_this, 9, 5.0f, 0, 1.0f, -1, 0);
            anm_init(i_this, 8, 5.0f, 0, 1.0f, -1, 1);
            i_this->mSph.OnAtSetBit();
            i_this->mSph.OnAtHitBit();
            i_this->mSph.SetAtSpl(dCcG_At_Spl_UNK1);
            i_this->mSph.OffAtSPrmBit(cCcD_AtSPrm_VsOther_e);
            i_this->attention_info.flags |= 4;
            i_this->m2C5 = 1;
        }
        break;
    case 3:
        if (i_this->m2DC == 5) {
            f32 frame = i_this->mpMorf->getFrame();
            if (frame < 27.0f || frame > 55.0f) {
                i_this->m34E = fopAcM_searchActorAngleY(i_this, player);
            } else {
                if (frame < 38.0f) {
                    if (frame == 27.0f) {
                        i_this->mSph.OnAtSetBit();
                        i_this->mSph.OnAtHitBit();
                        JAIZelBasic::zel_basic->seStart(0x5845, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
                    } else {
                        int flag = 0;
                        if (i_this->mSph.mGObjAt.mRPrm & cCcD_AtRPrm_Hit_e) {
                            i_this->m2C5 = 6;
                            flag = 1;
                        } else if (i_this->mSph.ChkAtHit() && i_this->mSph.mGObjAt.GetAc() == player) {
                            flag = 1;
                        }
                        if (flag) {
                            i_this->mSph.OffAtSetBit();
                            i_this->mSph.OffAtSetBit();
                            i_this->mSph.SetAtSpl(dCcG_At_Spl_UNK0);
                            anm_init(i_this, 0xC, 0.0f, 0, 1.0f, -1, 0);
                        }
                    }
                } else {
                    if (i_this->mpMorf->checkFrame(38.0f)) {
                        i_this->mSph.OffAtSetBit();
                        i_this->mSph.OffAtSetBit();
                        i_this->mSph.SetAtSpl(dCcG_At_Spl_UNK0);
                    }
                }
            }
        }
        // falls through to case 6 (shared isStop check)
    case 6:
        if (i_this->mpMorf->isStop()) {
            i_this->m366[1] = (s16)(30.0f + cM_rndF(30.0f));
            wait_initial(i_this);
        }
        break;
    case 1:
        i_this->m34E = fopAcM_searchActorAngleY(i_this, player);
        if (i_this->mpEmitter1 == NULL) {
            i_this->mpEmitter1 = play.getParticle()->set(
                dPa_control_c::dPtclGroup_Normal_e, 0x8106, &i_this->current.pos, NULL, NULL, 0xFF, NULL,
                -1, NULL, NULL, NULL);
        } else {
            i_this->mpEmitter1->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(9));
        }
        if (i_this->mpMorf->getFrame() > 39.0f) {
            i_this->mSph.SetAtSpl(dCcG_At_Spl_UNK0);
            i_this->mSph.OffAtSetBit();
            i_this->mSph.OffAtSetBit();
        }
        if (i_this->mpMorf->isStop()) {
            if (i_this->mpEmitter1 != NULL) {
                i_this->mpEmitter1->mMaxFrame = -1;
                i_this->mpEmitter1->setStatus(JPAEmtrStts_StopEmit);
                i_this->mpEmitter1 = NULL;
            }
            wait_initial(i_this);
        }
        break;
    case 2:
        if (i_this->m366[3] == 0) {
            if (i_this->mpEmitter2 == NULL) {
                i_this->mpEmitter2 = play.getParticle()->set(
                    dPa_control_c::dPtclGroup_Normal_e, 0x8107, &i_this->current.pos, NULL, NULL, 0xFF, NULL,
                    -1, NULL, NULL, NULL);
                if (i_this->mpEmitter2 != NULL) {
                    i_this->mpEmitter2->mpParticleCallBack = &i_this->mYodare;
                }
                i_this->m2C6 = 0;
            } else {
                i_this->mpEmitter2->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(9));
            }
            if (i_this->m366[0] == 0) {
                f32 frame = i_this->mpMorf->getFrame();
                if (i_this->m2DC == 0x16) {
                    anm_init(i_this, 0x15, 20.0f, 2, 1.0f, -1, 0);
                } else {
                    anm_init(i_this, 0x16, 20.0f, 2, 1.0f, -1, 0);
                }
                i_this->mpMorf->setFrame((s16)frame);
                i_this->m366[0] = (s16)(60.0f + cM_rndF(60.0f));
            }
            if (i_this->m366[1] == 0) {
                if (fopAcM_searchActorDistance(i_this, player) < 380.0f) {
                    anm_init(i_this, 5, 5.0f, 0, 1.0f, -1, 0);
                    if (cM_rnd() < 0.5f) {
                        i_this->mSph.SetAtAtp(0);
                        i_this->mAction = 1;
                        i_this->m2C5 = 0xA;
                    } else {
                        i_this->mSph.SetAtAtp(1);
                        i_this->mSph.OffAtSPrmBit(cCcD_AtSPrm_VsOther_e);
                        i_this->mCyl.OnCoSetBit();
                        mDoAud_monsSeStart(0x484E, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
                        i_this->m2C5 = 3;
                    }
                } else if (fopAcM_searchActorDistance(i_this, player) > 900.0f) {
                    anm_init(i_this, 0x11, 5.0f, 0, 1.0f, -1, 0);
                    anm_init(i_this, 0x10, 5.0f, 0, 1.0f, -1, 1);
                    i_this->attention_info.flags &= ~4;
                    JAIZelBasic::zel_basic->seStart(0x5848, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                                    1.0f, 1.0f, -1.0f, -1.0f, 0);
                    i_this->mCyl.OffTgSetBit();
                    i_this->mSph.OffTgSetBit();
                    i_this->mSph.OffCoSetBit();
                    i_this->mCyl.ClrTgHit();
                    i_this->mSph.ClrTgHit();
                    angle_initial(i_this);
                    i_this->m2C5 = 0;
                }
            }
            i_this->m34E = fopAcM_searchActorAngleY(i_this, player);
        }
        break;
    case 4:
        if (player->attention_info.flags == 3) {
            mDoMtx_YrotS(*calc_mtx, i_this->m37E);
        } else {
            mDoMtx_YrotS(*calc_mtx, -i_this->m37E);
        }
        {
            cXyz offset(0.0f, 0.0f, i_this->m388);
            cXyz out;
            MtxPosition(&offset, &out);
            i_this->m334.y = (s16)out.z;
            i_this->m334.x = (s16)out.y;
            i_this->m37E += i_this->m380;
            cLib_addCalc0(&i_this->m388, 1.0f, 250.0f);
            cLib_addCalcAngleS2(&i_this->m352.x, 0, 1, 0x87);
            cLib_addCalcAngleS2(&i_this->m352.y, 0, 1, 0x87);
            if (std::fabsf(i_this->m388) < 1.875f) {
                i_this->m352.setall(0);
                i_this->m334.setall(0);
                i_this->m366[0] = 0;
                i_this->m2C5 = 2;
                if (i_this->m364 != 0) {
                    i_this->m366[3] = 0x2D;
                }
            }
        }
        break;
    case 5:
        if (i_this->m364 != 0) {
            i_this->m364--;
        }
        if (i_this->m364 == 1) {
            i_this->mAction = 2;
            i_this->m2C5 = 0x14;
            break;
        }
        if (i_this->m372 < 0x10 && !(i_this->m2C8 & 1)) {
            if (cLib_distanceAngleS(i_this->m33A.y, i_this->m340.y) < 0x100) {
                i_this->m340.y ^= 0xFF00;
                i_this->m340.y = (s16)(i_this->m340.y * 0.1f);
                i_this->m372++;
                if (i_this->m372 >= 0x10) {
                    i_this->m340.y = 0;
                    i_this->m33A.y = 0;
                    i_this->m2C8 |= 1;
                }
            }
        }
        if (i_this->m374 < 0x10 && !(i_this->m2C8 & 2)) {
            if (cLib_distanceAngleS(i_this->m33A.z, i_this->m340.z) < 0x100) {
                i_this->m340.z ^= 0xFF00;
                i_this->m340.z = (s16)(i_this->m340.z * 0.1f);
                i_this->m374++;
                if (i_this->m374 >= 0x10) {
                    i_this->m340.z = 0;
                    i_this->m33A.z = 0;
                    i_this->m2C8 |= 2;
                }
            }
        }
        if (i_this->m340.y == 0 && i_this->m340.z == 0) {
            i_this->m376++;
        }
        if (i_this->m376 > 0x1E) {
            wait_initial(i_this);
            i_this->m376 = 0;
            i_this->m398 = 1.0f;
        }
        if (i_this->m2D0 == 0) {
            body_atari_check(i_this);
        }
        break;
    case 7:
        if (i_this->mpMorf->isStop()) {
            i_this->m2C5 = 0;
        }
        break;
    }

    cLib_addCalcAngleS2(&i_this->m348, i_this->m34E, 1, 0x800);
    cLib_addCalcAngleS2(&i_this->m33A.y, i_this->m340.y, 1, i_this->m37C);
    cLib_addCalcAngleS2(&i_this->m33A.z, i_this->m340.z, 1, i_this->m37C);
    if (i_this->m2C5 == 4) {
        s16 angle = cLib_distanceAngleS(fopAcM_searchActorAngleY(i_this, player), i_this->m348);
        if (angle > 0x337F) {
            wait_initial(i_this);
            anm_init(i_this, 0x11, 5.0f, 0, 1.0f, -1, 0);
            anm_init(i_this, 0x10, 5.0f, 0, 1.0f, -1, 1);
            i_this->attention_info.flags &= ~4;
            JAIZelBasic::zel_basic->seStart(0x5848, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                            1.0f, 1.0f, -1.0f, -1.0f, 0);
            i_this->mCyl.OffTgSetBit();
            i_this->mSph.OffTgSetBit();
            i_this->mSph.OffCoSetBit();
            i_this->mCyl.ClrTgHit();
            i_this->mSph.ClrTgHit();
            angle_initial(i_this);
            i_this->m2C5 = 7;
        }
    }
    if (i_this->m2C5 != 0 && i_this->m2C5 != 5) {
        damage_check(i_this);
    }
}

/* 00002FC4-0000380C       .text bo2_move__FP8bo_class */
static void bo2_move(bo_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 stickX = g_mDoCPd_cpadInfo[0].mMainStickPosX;
    f32 stickY = g_mDoCPd_cpadInfo[0].mMainStickPosY;

    switch (i_this->m2C5) {
    case 0xA:
        anm_init(i_this, 0x14, 5.0f, 0, 1.0f, -1, 0);
        JAIZelBasic::zel_basic->seStart(0x5849, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        i_this->mSph.OnAtSPrmBit(cCcD_AtSPrm_NoTgHitInfSet_e);
        i_this->mSph.OffCoSetBit();
        i_this->m2CB = 0;
        i_this->m2CC = 0;
        i_this->m2C5++;
        break;
    case 0xB:
        if (i_this->mpMorf->getFrame() >= 0xB4 && i_this->mpMorf->getFrame() <= 0xB8) {
            if (i_this->mSph.ChkAtHit()) {
                fopAc_ac_c* hitAc = i_this->mSph.mGObjAt.GetAc();
                if (hitAc != NULL && hitAc == player) {
                    i_this->m2CB = 1;
                }
            }
        }
        if (i_this->mpMorf->checkFrame(0xB4)) {
            i_this->mSph.OnAtSetBit();
            i_this->mSph.OnAtHitBit();
            mDoAud_monsSeStart(0x4851, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
        }
        if (i_this->mpMorf->checkFrame(0xB8)) {
            i_this->mSph.OffAtSetBit();
            i_this->mSph.OffAtSetBit();
            i_this->mSph.SetAtSpl(dCcG_At_Spl_UNK0);
        }
        if (i_this->mpMorf->isStop()) {
            wait_initial(i_this);
            i_this->m366[1] = (s16)(30.0f + cM_rndF(30.0f));
        }
        break;
    case 0xC:
        if (i_this->m2CC == 0) {
            if (i_this->mpMorf->checkFrame(0xB8) || i_this->mpMorf->getFrame() >= 0xB8) {
                ((daPy_py_c*)player)->mDemo.mDemoType = daPy_demo_c::TYPE_ORIGINAL_e;
                ((daPy_py_c*)player)->mDemo.mParam0 = 0;
                ((daPy_py_c*)player)->mDemo.mDemoMode = 0x1E;
                s16 angle = cLib_distanceAngleS(fopAcM_searchActorAngleY(player, i_this), ((daPy_py_c*)player)->shape_angle.y);
                i_this->m2CD = (angle > 0x4000) ? 1 : 0;
                i_this->m2CC = 1;
            }
        }
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, 0xD, 5.0f, 2, 1.0f, -1, 0);
            JPABaseEmitter* emitter = g_dComIfG_gameInfo.play.getParticle()->set(
                dPa_control_c::dPtclGroup_Normal_e, 0x810C, &i_this->current.pos, NULL, NULL, 0xFF, NULL,
                -1, NULL, NULL, NULL);
            if (emitter != NULL) {
                emitter->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(9));
            }
            i_this->m376 = 0;
            i_this->m366[1] = 0;
            i_this->m2D4 = 1;
            i_this->m2D8 = 1;
            mDoAud_monsSeStart(0x4852, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            i_this->m2C5++;
        }
        break;
    case 0xD:
        if (i_this->mpEmitter3 == NULL) {
            i_this->mpEmitter3 = g_dComIfG_gameInfo.play.getParticle()->set(
                dPa_control_c::dPtclGroup_Normal_e, 0x8107, &i_this->current.pos, NULL, NULL, 0xFF, NULL,
                -1, NULL, NULL, NULL);
            if (i_this->mpEmitter3 != NULL) {
                i_this->mpEmitter3->mpParticleCallBack = &i_this->mYodare;
                i_this->mpEmitter3->mRate = 0.0f;
            }
            i_this->m2C7 = 0;
        } else {
            i_this->mpEmitter3->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(9));
        }
        if (i_this->m366[1] == 0) {
            daPy_lk_c* pyPlayer = (daPy_lk_c*)player;
            if (!(pyPlayer->mNoResetFlg1 & 1) && pyPlayer->checkTinkleShield() == 0) {
                pyPlayer->setDamagePoint(-1.0f);
            }
            i_this->m366[1] = 0x1E;
        }
        i_this->m376++;
        if (i_this->m376 > 0x78) {
            i_this->m376 = 0;
            anm_init(i_this, 0xB, 5.0f, 0, 1.0f, -1, 0);
            mDoAud_monsSeStart(0x5846, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            end_event_camera(i_this);
            i_this->m2C5++;
            break;
        }
        if (i_this->mpMorf->checkFrame(0.0f)) {
            mDoAud_monsSeStart(0x4852, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
            JPABaseEmitter* emitter = g_dComIfG_gameInfo.play.getParticle()->set(
                dPa_control_c::dPtclGroup_Normal_e, 0x810C, &i_this->current.pos, NULL, NULL, 0xFF, NULL,
                -1, NULL, NULL, NULL);
            if (emitter != NULL) {
                emitter->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(9));
            }
        }
        if (i_this->m2D4 > 0) {
            if (stickX < 0.0f) {
                i_this->m2D4 = -1;
                i_this->m376 += 2;
            }
        } else if (i_this->m2D4 < 0) {
            if (stickX > 0.0f) {
                i_this->m2D4 = 1;
                i_this->m376 += 2;
            }
        }
        if (i_this->m2D8 > 0) {
            if (stickY < 0.0f) {
                i_this->m2D8 = -1;
                i_this->m376 += 2;
            }
        } else if (i_this->m2D8 < 0) {
            if (stickY > 0.0f) {
                i_this->m2D8 = 1;
                i_this->m376 += 2;
            }
        }
        if (g_mDoCPd_cpadInfo[0].mButtonTrig.a) {
            i_this->m376 += 2;
        }
        break;
    case 0xE:
        if (i_this->mpMorf->checkFrame(0xC0)) {
            ((daPy_py_c*)player)->current.angle.y = i_this->m348;
            ((daPy_py_c*)player)->mDemo.mDemoMode = 9;
            i_this->m2CC = 0;
            if (i_this->m2CD) {
                ((daPy_py_c*)player)->mDemo.mParam0 = 0;
            } else {
                ((daPy_py_c*)player)->mDemo.mParam0 = 1;
            }
        }
        if (i_this->mpMorf->isStop()) {
            g_dComIfG_gameInfo.play.mEvtCtrl.mEventFlag |= 8;
            wait_initial(i_this);
            i_this->m366[1] = (s16)(30.0f + cM_rndF(30.0f));
            i_this->m366[1] *= 2;
        }
        break;
    }

    if (i_this->m2C5 < 0xC && i_this->m2CB == 0) {
        damage_check(i_this);
    }
}

/* 0000380C-00003AD4       .text bo3_move__FP8bo_class */
static void bo3_move(bo_class* i_this) {
    /* Nonmatching */
    switch (i_this->m2C5) {
    case 0x14:
        if (i_this->m364 != 0) {
            i_this->m364--;
        }
        if (i_this->m364 == 0) {
            i_this->mCyl.OffTgSetBit();
            i_this->mSph.OffTgSetBit();
            i_this->mSph.OffCoSetBit();
            i_this->mCyl.ClrTgHit();
            i_this->mSph.ClrTgHit();
            csXyz angle;
            angle.x = i_this->current.angle.x;
            angle.y = i_this->m348;
            angle.z = i_this->current.angle.z;
            if (i_this->m2CE == 0) {
                fopAcM_create(0xD7, 2, &i_this->m304, i_this->current.roomNo, &angle, &i_this->scale, 0, 0);
            }
            i_this->m2CE = 0;
            i_this->mType = 1;
            anm_init(i_this, 0x13, 5.0f, 0, 1.0f, -1, 1);
            dScnPly_ply_c::nextPauseTimer = 4;
            i_this->m2C5++;
        }
        break;
    case 0x15:
        if (i_this->mpMorf2->checkFrame(0xC4)) {
            int dropType = 0;
            if (i_this->m2C1 != 0) {
                dropType = 3;
                i_this->m366[1] = 0x32;
            }
            if (i_this->m2D0 != 3) {
                fopAcM_createDisappear(i_this, &i_this->current.pos, 5, dropType, i_this->stealItemBitNo);
            }
        }
        if (i_this->mpMorf2->isStop()) {
            if (i_this->m2C1 != 0) {
                i_this->m2C5++;
            } else {
                g_dComIfG_gameInfo.save.onActor(i_this->setID, fopAcM_GetHomeRoomNo(i_this));
                fopAcM_delete(i_this);
            }
        }
        break;
    case 0x16:
        if (i_this->m366[1] == 0) {
            fopAcM_create(0xD6, 1, &i_this->current.pos, i_this->current.roomNo, &i_this->current.angle, &i_this->scale, 0, 0);
            g_dComIfG_gameInfo.save.onActor(i_this->setID, fopAcM_GetHomeRoomNo(i_this));
            fopAcM_delete(i_this);
        }
        break;
    }

    if (i_this->mSmokeEcallBack.getEmitter() != NULL && i_this->m366[2] == 0) {
        i_this->mSmokeEcallBack.getEmitter()->mGlobalPrmColor.a = i_this->m376;
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmokeEcallBack.end();
        }
    }
}

/* 00003AD4-00003E8C       .text bo4_move__FP8bo_class */
static void bo4_move(bo_class* i_this) {
    /* Nonmatching */
    switch (i_this->m2C5) {
    case 0x1E:
        i_this->mSph.OffTgSetBit();
        i_this->mSph.OffCoSetBit();
        i_this->mSph.OffAtSetBit();
        i_this->mSph.ClrTgHit();
        i_this->mSph.ClrTgHit();
        anm_init(i_this, 7, 5.0f, 0, 1.0f, -1, 0);
        i_this->speed.y = 30.0f;
        i_this->gravity = -3.0f;
        i_this->speedF = 10.0f;
        i_this->current.angle.y = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0)) + 0x8000;
        i_this->m390 = i_this->current.pos.y - 80.0f;
        i_this->m2C5++;
        break;
    case 0x1F:
        i_this->shape_angle.x -= 0x1200;
        if (i_this->speed.y < 0.0f && i_this->current.pos.y < i_this->m390) {
            i_this->current.pos.y = i_this->m390;
            i_this->shape_angle.x = -0x8000;
            i_this->speed.y = 0.0f;
            i_this->gravity = 0.0f;
            i_this->speedF = 0.0f;
            i_this->m366[1] = 0xA;
            JAIZelBasic::zel_basic->seStart(0x5847, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
            g_dComIfG_gameInfo.play.getParticle()->set(
                dPa_control_c::dPtclGroup_Normal_e, 0x810A, &i_this->m328, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
            i_this->m366[2] = 0xA;
            i_this->m376 = 0xB4;
            i_this->m39C = i_this->m328;
            smoke_set(i_this);
            anm_init(i_this, 6, 0.0f, 0, 1.0f, -1, 0);
            i_this->m2C5++;
        }
        break;
    case 0x20:
        if (i_this->m366[1] == 0) {
            i_this->m394 = 200.0f;
            i_this->current.pos.y = i_this->m390 - 200.0f;
            i_this->speed.y = 10.0f;
            i_this->gravity = -1.0f;
            i_this->m2C5++;
        }
        break;
    case 0x21:
        i_this->shape_angle.z += 0x1000;
        if (i_this->shape_angle.z > 0x4000) {
            csXyz angle;
            angle.x = 0;
            angle.y = i_this->m348 + 0xC000;
            angle.z = 0;
            cXyz pos = i_this->m310;
            pos.y = 30.0f + i_this->m390;
            fopAcM_create(0x1D5, 0, &pos, i_this->current.roomNo, &angle, &i_this->scale, 0, 0);
            i_this->scale.setall(0.0f);
            i_this->m398 = 0.0f;
            i_this->m366[1] = 0xA;
            i_this->m2C5++;
        }
        break;
    case 0x22:
        if (i_this->m366[1] == 0 && i_this->mSmokeEcallBack.getEmitter() == NULL) {
            fopAcM_delete(i_this);
        }
        break;
    }

    if (i_this->mSmokeEcallBack.getEmitter() != NULL && i_this->m366[2] == 0) {
        i_this->mSmokeEcallBack.getEmitter()->mGlobalPrmColor.a = i_this->m376;
        i_this->m376 -= 4;
        if (i_this->m376 < 0) {
            i_this->mSmokeEcallBack.end();
        }
    }
}

/* 00003E8C-000042B8       .text bo5_move__FP8bo_class */
static void bo5_move(bo_class* i_this) {
    /* Nonmatching */
    switch (i_this->m2C5) {
    case 0x28:
        i_this->m376 = 3;
        i_this->mCyl.OffTgSetBit();
        i_this->mSph.OffTgSetBit();
        i_this->mSph.OffCoSetBit();
        i_this->mCyl.ClrTgHit();
        i_this->mSph.ClrTgHit();
        dScnPly_ply_c::nextPauseTimer = 2;
        anm_init(i_this, 0xF, 5.0f, 2, 1.0f, -1, 0);
        i_this->attention_info.flags &= ~4;
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
        JAIZelBasic::zel_basic->seStart(0x2828, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        i_this->m2C5++;
        break;
    case 0x29:
        if (i_this->mpMorf->checkFrame(0xD0)) {
            i_this->m376--;
            if (i_this->m376 <= 0) {
                i_this->attention_info.flags &= ~4;
                anm_init(i_this, 9, 0.0f, 0, 0.0f, -1, 0);
                dPa_control_c* particle = g_dComIfG_gameInfo.play.getParticle();
                particle->set(dPa_control_c::dPtclGroup_Normal_e, 0x810A, &i_this->m328, NULL, NULL, 0xFF, NULL,
                              -1, &i_this->tevStr.mColorK0, NULL, NULL);
                i_this->m39C = i_this->m328;
                i_this->m366[2] = 0xA;
                i_this->m376 = 0xB4;
                smoke_set(i_this);
                JAIZelBasic::zel_basic->seStart(0x5801, &i_this->eyePos, 0, dComIfGp_getReverb(i_this->current.roomNo),
                                                1.0f, 1.0f, -1.0f, -1.0f, 0);
                i_this->m2CE = 1;
                i_this->mAction = 2;
                i_this->m2C5 = 0x14;
            }
        }
        break;
    case 0x32:
        i_this->mCyl.OffTgSetBit();
        i_this->mSph.OffTgSetBit();
        i_this->mSph.OffCoSetBit();
        i_this->mCyl.ClrTgHit();
        i_this->mSph.ClrTgHit();
        dScnPly_ply_c::nextPauseTimer = 2;
        anm_init(i_this, 0xE, 5.0f, 0, 1.0f, -1, 0);
        i_this->attention_info.flags = 0;
        mDoAud_monsSeStart(0x4850, &i_this->eyePos, fopAcM_GetID(i_this), 0, dComIfGp_getReverb(i_this->current.roomNo));
        JAIZelBasic::zel_basic->seStart(0x2828, &i_this->eyePos, 0x20, dComIfGp_getReverb(i_this->current.roomNo),
                                        1.0f, 1.0f, -1.0f, -1.0f, 0);
        i_this->m2C5++;
        // fallthrough
    case 0x33:
        if (i_this->m366[0] == 0) {
            if (i_this->mpMorf->isStop()) {
                i_this->m366[2] = 0xA;
                i_this->m376 = 0xB4;
                i_this->m2CE = 1;
                i_this->mAction = 2;
                i_this->m2C5 = 0x14;
            }
        }
        break;
    }
}

/* 000042B8-000048B0       .text daBO_Execute__FP8bo_class */
static BOOL daBO_Execute(bo_class* i_this) {
    /* Nonmatching */
    if (i_this->mType == 0) {
        if (enemy_ice(&i_this->mEnemyIce)) {
            if (i_this->mEnemyIce.mLightShrinkTimer != 0) {
                i_this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
                i_this->mpMorf->calc();
            } else {
                i_this->mSph.SetC(i_this->m2E0);
                i_this->mSph.SetR(60.0f);
                dComIfG_Ccsp()->Set(&i_this->mSph);
            }
            return 1;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (i_this->m366[i] != 0) {
            i_this->m366[i]--;
        }
    }

    switch (i_this->mAction) {
    case 0:
        bo_move(i_this);
        i_this->shape_angle = i_this->current.angle;
        break;
    case 1:
        bo2_move(i_this);
        if (i_this->m2CB != 0) {
            if (i_this->eventInfo.mCommand == 2) {
                if (i_this->mAction != 1) {
                    g_dComIfG_gameInfo.play.mEvtCtrl.mEventFlag |= 8;
                } else {
                    i_this->m2C5 = 0xC;
                    start_bakutsuki_event_camera(i_this);
                }
                i_this->m2CB = 0;
            } else {
                fopAcM_orderPotentialEvent(i_this, 2, 0xFFFF, 0);
                i_this->eventInfo.mCondition |= 2;
            }
        }
        break;
    case 2:
        bo3_move(i_this);
        break;
    case 3:
        bo4_move(i_this);
        break;
    case 4:
        bo5_move(i_this);
        break;
    }

    if (i_this->m2C6 != 0 || (i_this->m2DC != 0x16 && i_this->m2DC != 0x15)) {
        if (i_this->mpEmitter2 != NULL) {
            i_this->mpEmitter2->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(9));
            switch (i_this->m2C6) {
            case 0:
                i_this->mpEmitter2->setStatus(JPAEmtrStts_StopEmit);
                i_this->m2C6 = 1;
                break;
            case 1:
                if (i_this->mpEmitter2->getParticleNumber() == 0) {
                    i_this->mpEmitter2->mpParticleCallBack = NULL;
                    i_this->mpEmitter2->mMaxFrame = -1;
                    i_this->mpEmitter2->setStatus(JPAEmtrStts_StopEmit);
                    i_this->mpEmitter2 = NULL;
                    i_this->m2C6 = 0;
                }
                break;
            }
        }
    }

    if (i_this->m2C7 != 0 || i_this->m2DC != 0xD) {
        if (i_this->mpEmitter3 != NULL) {
            i_this->mpEmitter3->setGlobalSRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(9));
            switch (i_this->m2C7) {
            case 0:
                i_this->mpEmitter3->setStatus(JPAEmtrStts_StopEmit);
                i_this->m2C7 = 1;
                break;
            case 1:
                if (i_this->mpEmitter3->getParticleNumber() == 0) {
                    i_this->mpEmitter3->mpParticleCallBack = NULL;
                    i_this->mpEmitter3->mMaxFrame = -1;
                    i_this->mpEmitter3->setStatus(JPAEmtrStts_StopEmit);
                    i_this->mpEmitter3 = NULL;
                    i_this->m2C7 = 0;
                }
                break;
            }
        }
    }

    cLib_addCalc2(&i_this->scale.y, i_this->m398, 1.0f, 0.0875f);
    i_this->mStts.SetWeight(0xFF);
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    cXyz offset(0.0f, 0.0f, i_this->speedF);
    cXyz out;
    MtxPosition(&offset, &out);
    i_this->speed.x = out.x;
    i_this->speed.y += i_this->gravity;
    i_this->speed.z = out.z;
    fopAcM_posMove(i_this, i_this->mStts.GetCCMoveP());

    if (i_this->mType == 0 || i_this->mType == 2) {
        i_this->mpMorf->play(NULL, 0, 0);
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        i_this->mpMorf2->play(NULL, 0, 0);
    }

    if (i_this->mType == 0) {
        if (i_this->m2C5 != 5) {
            i_this->attention_info.position = i_this->m2E0;
            i_this->attention_info.position.y += 60.0f;
            i_this->eyePos = i_this->m328;
        } else {
            i_this->eyePos = i_this->m2F8;
            i_this->eyePos.y += 60.0f;
            i_this->attention_info.position = i_this->eyePos;
        }
        if (i_this->m2CC != 0 || i_this->m2C5 == 0xC) {
            i_this->attention_info.position = i_this->current.pos;
            i_this->attention_info.position.y += 60.0f;
            i_this->shape_angle.y = i_this->m348;
        }
    }

    i_this->mSph.SetC(i_this->m2E0);
    i_this->mSph.SetR(60.0f);
    dComIfG_Ccsp()->Set(&i_this->mSph);
    if (i_this->mAction == 0) {
        i_this->mCyl.SetC(i_this->m2F8);
        i_this->mCyl.SetH(160.0f);
        i_this->mCyl.SetR(15.0f);
        dComIfG_Ccsp()->Set(&i_this->mCyl);
    }
    if (i_this->mType == 0 || i_this->mType == 1) {
        cXyz pos = i_this->current.pos;
        pos.y += 10.0f;
        i_this->mSph2.SetC(pos);
        i_this->mSph2.SetR(45.0f);
        dComIfG_Ccsp()->Set(&i_this->mSph2);
    }
    draw_SUB(i_this);
    return 1;
}

/* 000048B0-000048B8       .text daBO_IsDelete__FP8bo_class */
static BOOL daBO_IsDelete(bo_class*) {
    return TRUE;
}

/* 000048B8-00004998       .text daBO_Delete__FP8bo_class */
static BOOL daBO_Delete(bo_class* i_this) {
    i_this->mSmokeEcallBack.remove();
    if (i_this->mpEmitter1 != NULL) {
        i_this->mpEmitter1->becomeInvalidEmitter();
        i_this->mpEmitter1 = NULL;
    }
    if (i_this->mpEmitter2 != NULL) {
        i_this->mpEmitter2->deleteAllParticle();
        i_this->mpEmitter2->becomeInvalidEmitter();
        i_this->mpEmitter2 = NULL;
    }
    if (i_this->mpEmitter3 != NULL) {
        i_this->mpEmitter3->deleteAllParticle();
        i_this->mpEmitter3->becomeInvalidEmitter();
        i_this->mpEmitter3 = NULL;
    }
    enemy_fire_remove(&i_this->mEnemyFire);
    dComIfG_resDelete(&i_this->mPhase, "BO");
    return TRUE;
}

/* 00004998-00004D08       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_this) {
    /* Nonmatching */
    bo_class* bo = (bo_class*)i_this;
    int modelIdx = 9;
    if (bo->mType == 2) {
        modelIdx = 7;
    }
    bo->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("BO", 0x1A), NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("BO", modelIdx), 1, 0.0f, 0, -1, 1, NULL, 0x80000, 0x37441422);
    if (bo->mpMorf == NULL || bo->mpMorf->getModel() == NULL) {
        return FALSE;
    }
    J3DModel* model = bo->mpMorf->getModel();
    bo->mpMorf->getModel()->setUserArea((u32)bo);
    for (u16 i = 0; i < bo->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        bo->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_UP);
    }
    if (bo->mType == 2) {
        bo->mpBaseAnm = new mDoExt_brkAnm();
        if (bo->mpBaseAnm == NULL) {
            return FALSE;
        }
        if (!bo->mpBaseAnm->init(model->getModelData(), (J3DAnmTevRegKey*)dComIfG_getObjectRes("BO", 0x1D), 1, 0, 1.0f, 0, -1, 0, FALSE)) {
            return FALSE;
        }
    } else {
        bo->mpMorf2 = new mDoExt_McaMorf((J3DModelData*)dComIfG_getObjectRes("BO", 0x19), NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectRes("BO", 8), 1, 0.0f, 0, -1, 1, NULL, 0x80000, 0x33221202);
        if (bo->mpMorf2 == NULL || bo->mpMorf2->getModel() == NULL) {
            return FALSE;
        }
        bo->mpMorf2->getModel()->setUserArea((u32)bo);
        for (u16 i = 0; i < bo->mpMorf2->getModel()->getModelData()->getJointNum(); i++) {
            bo->mpMorf2->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_DW);
        }
    }
    if (bo->mType == 0) {
        if (!bo->mInvisibleModel.create(bo->mpMorf->getModel())) {
            return FALSE;
        }
    }
    return TRUE;
}

static dCcD_SrcSph head_co_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK2000,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ 0x5,
        /* SrcObjTg  Type    */ 0xFF3DFEFF,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0x15,
        /* SrcGObjAt Se      */ 6,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 15.0f,
    }},
};

static dCcD_SrcSph foot_co_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0x75,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 15.0f,
    }},
};

static dCcD_SrcCyl body_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0xFF1DFEFF,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    }},
};

static u8 fire_j[10] = {1, 3, 5, 6, 8, 9, 0xA, 0xB, 0xC, 0xD};
static f32 fire_sc[10] = {1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};

/* 00004D50-000050DC       .text daBO_Create__FP10fopAc_ac_c */
static cPhs_State daBO_Create(fopAc_ac_c* i_this) {
    /* Nonmatching */
    bo_class* bo = (bo_class*)i_this;

    fopAcM_ct(i_this, bo_class);

    cPhs_State res = dComIfG_resLoad(&bo->mPhase, "BO");
    if (res == cPhs_COMPLEATE_e) {
        bo->mType = fopAcM_GetParam(i_this);
        bo->m2C1 = fopAcM_GetParam(i_this) >> 8;
        if (bo->mType == 0xff) {
            bo->mType = 0;
        }
        if (bo->m2C1 == 0xff) {
            bo->m2C1 = 0;
        }

        cDT_NamePTbl* nameTbl = (cDT_NamePTbl*)((u8*)&g_dComIfG_gameInfo + 0x50AC);
        bo->itemTableIdx = nameTbl->GetIndex("bbaba", 0);

        if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x3100)) {
            return cPhs_ERROR_e;
        }

        if (bo->mType == 0 || bo->mType == 2) {
            bo->cullMtx = bo->mpMorf->getModel()->getBaseTRMtx();
        } else {
            bo->cullMtx = bo->mpMorf2->getModel()->getBaseTRMtx();
        }

        fopAcM_setCullSizeBox(i_this, -150.0f, 0.0f, -150.0f, 150.0f, 330.0f, 150.0f);

        bo->attention_info.flags = 0;
        bo->max_health = 1;
        bo->health = 1;
        bo->m398 = 1.0f;

        bo->mStts.Init(0xff, 0x1, i_this);
        bo->mAction = 0;
        bo->m2C5 = 0;

        if (bo->mType == 0) {
            bo->mSph.Set(head_co_sph_src);
            bo->mSph.SetStts(&bo->mStts);
            bo->stealItemLeft = 3;
            bo->mCyl.Set(body_cyl_src);
            bo->mCyl.SetStts(&bo->mStts);
            bo->mSph.OffAtSetBit();
            bo->mSph.OffAtSetBit();
            bo->mSph.SetAtSpl(dCcG_At_Spl_UNK0);
            bo->mEnemyIce.mpActor = bo;
            bo->mEnemyIce.mWallRadius = 15.0f;
            bo->mEnemyIce.mCylHeight = 160.0f;
            bo->mEnemyFire.mpMcaMorf = bo->mpMorf;
            bo->mEnemyFire.mpActor = bo;
            for (int i = 0; i < 10; i++) {
                bo->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
                bo->mEnemyFire.mParticleScale[i] = fire_sc[i];
            }
        }

        if (bo->mType == 0 || bo->mType == 1) {
            bo->mSph2.Set(foot_co_sph_src);
            bo->mSph2.SetStts(&bo->mStts);
        }

        if (bo->mType == 1) {
            bo->m366[0] = (s16)(15.0f + g_regHIO.mChild[8].mFloatRegs[14]);
            anm_init(bo, 8, 0.0f, 0, 0.0f, -1, 1);
            bo->mAction = 4;
            bo->m2C5 = 0x33;
            bo->m2D0 = 3;
            bo->mpMorf2->play(NULL, 0, 0);
            draw_SUB(bo);
        }

        bo->m34E = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0));
        bo->m348 = bo->m34E;
        bo->m304 = bo->current.pos;

        if (bo->mType == 2) {
            bo->m394 = 100.0f;
            bo->attention_info.flags = 0;
            bo->mAction = 3;
            bo->m2C5 = 0x1e;
            bo->mpMorf->play(NULL, 0, 0);
            draw_SUB(bo);
        }

        daBO_Execute(bo);
    }
    return res;
}

static actor_method_class l_daBO_Method = {
    (process_method_func)daBO_Create,
    (process_method_func)daBO_Delete,
    (process_method_func)daBO_Execute,
    (process_method_func)daBO_IsDelete,
    (process_method_func)daBO_Draw,
};

/* Nonmatching */ /* g_profile_BO 96.67: profile data layout diff */
actor_process_profile_definition g_profile_BO = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    fpcNm_BO_e,
    &g_fpcLf_Method.base,
    sizeof(bo_class),
    0,
    0,
    &g_fopAc_Method.base,
    fpcDwPi_BO_e,
    &l_daBO_Method,
    0x00044100,
    fopAc_ENEMY_e,
    fopAc_CULLBOX_CUSTOM_e,
};
