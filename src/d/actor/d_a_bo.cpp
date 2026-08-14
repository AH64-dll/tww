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
                mDoMtx_YrotM(*calc_mtx, i_this->m334.y + g_regHIO.mChild[0].mShortRegs[15]);
                mDoMtx_XrotM(*calc_mtx, i_this->m334.z + g_regHIO.mChild[0].mShortRegs[19]);
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
    /* Nonmatching */
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

/* 00000E24-000013A4       .text head_atari_check__FP8bo_class */
static void head_atari_check(bo_class*) {
    /* Nonmatching */
}

/* 000013A4-0000170C       .text nokezori_damage_rtn__FP8bo_class */
static void nokezori_damage_rtn(bo_class*) {
    /* Nonmatching */
}

/* 0000170C-00001BB8       .text body_atari_check__FP8bo_class */
static void body_atari_check(bo_class*) {
    /* Nonmatching */
}

/* 00001BB8-00002048       .text damage_check__FP8bo_class */
static void damage_check(bo_class*) {
    /* Nonmatching */
}

/* 00002048-00002080       .text angle_initial__FP8bo_class */
static void angle_initial(bo_class* i_this) {
    /* Nonmatching */
    i_this->m33A.setall(0);
    i_this->m352.setall(0);
    i_this->m334.setall(0);
    i_this->m340.setall(0);
}

/* 00002080-00002170       .text wait_initial__FP8bo_class */
static void wait_initial(bo_class* i_this) {
    /* Nonmatching */
    if (cM_rnd() < 0.5f) {
        anm_init(i_this, 0x15, 5.0f, 2, 1.0f, -1, 0);
    } else {
        anm_init(i_this, 0x16, 5.0f, 2, 1.0f, -1, 0);
    }
    i_this->m366 = (s16)(60.0f + cM_rndF(60.0f));
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
    /* Nonmatching */
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
static void bo_move(bo_class*) {
    /* Nonmatching */
}

/* 00002FC4-0000380C       .text bo2_move__FP8bo_class */
static void bo2_move(bo_class*) {
    /* Nonmatching */
}

/* 0000380C-00003AD4       .text bo3_move__FP8bo_class */
static void bo3_move(bo_class*) {
    /* Nonmatching */
}

/* 00003AD4-00003E8C       .text bo4_move__FP8bo_class */
static void bo4_move(bo_class*) {
    /* Nonmatching */
}

/* 00003E8C-000042B8       .text bo5_move__FP8bo_class */
static void bo5_move(bo_class*) {
    /* Nonmatching */
}

/* 000042B8-000048B0       .text daBO_Execute__FP8bo_class */
static BOOL daBO_Execute(bo_class*) {
    /* Nonmatching */
}

/* 000048B0-000048B8       .text daBO_IsDelete__FP8bo_class */
static BOOL daBO_IsDelete(bo_class*) {
    return TRUE;
}

/* 000048B8-00004998       .text daBO_Delete__FP8bo_class */
static BOOL daBO_Delete(bo_class* i_this) {
    /* Nonmatching */
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

/* 00004D50-000050DC       .text daBO_Create__FP10fopAc_ac_c */
static cPhs_State daBO_Create(fopAc_ac_c* i_this) {
    /* Nonmatching */
}

static actor_method_class l_daBO_Method = {
    (process_method_func)daBO_Create,
    (process_method_func)daBO_Delete,
    (process_method_func)daBO_Execute,
    (process_method_func)daBO_IsDelete,
    (process_method_func)daBO_Draw,
};

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
