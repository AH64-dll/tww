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

static const char l_arcname[] = "BO";

/* 000000EC-000001E8       .text smoke_set__FP8bo_class */
static void smoke_set(bo_class* i_this) {
    /* Nonmatching */
}

/* 000001E8-00000638       .text nodeCallBack_UP__FP7J3DNodei */
static BOOL nodeCallBack_UP(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000638-000006C8       .text nodeCallBack_DW__FP7J3DNodei */
static BOOL nodeCallBack_DW(J3DNode*, int) {
    /* Nonmatching */
}

/* 000006C8-0000079C       .text execute__22yodare_ato_PcallBack_cFP14JPABaseEmitterP15JPABaseParticle */
void yodare_ato_PcallBack_c::execute(JPABaseEmitter*, JPABaseParticle*) {
    /* Nonmatching */
}

/* 0000079C-00000930       .text draw_SUB__FP8bo_class */
static void draw_SUB(bo_class* i_this) {
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
static void anm_init(bo_class*, int, float, unsigned char, float, int, int) {
    /* Nonmatching */
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
static void start_bakutsuki_event_camera(fopAc_ac_c*) {
    /* Nonmatching */
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
    dComIfG_resDelete(&i_this->mPhase, l_arcname);
    return TRUE;
}

/* 00004998-00004D08       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
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
