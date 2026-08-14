/**
 * d_a_mt.cpp
 * Enemy - Magtail
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mt.h"
#include "d/actor/d_a_player.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_com_inf_game.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_hostIO.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_bg_s_lin_chk.h"
#include "res/Object/Mt.h"
#include "JAZelAudio/JAIZelBasic.h"

static daMt_HIO_c l_HIO;
static s32 mt_all_count;
static s32 mt_fight_count;
static s32 j_index;
static u16 mt_tex_anm_idx[] = {dRes_INDEX_MT_BTP_MG_MABA_e, dRes_INDEX_MT_BTP_MG_TOJI_e};
static u16 mt_tex_max_frame[] = {6, 1};

/* 000000EC-000001E8       .text __ct__10daMt_HIO_cFv */
daMt_HIO_c::daMt_HIO_c() {
    m04 = 0;
    m05 = 0;
    m06 = 0;
    m07 = 0;
    m08 = 0x157c;
    m0C = -7500.0f;
    m10 = 0xf;
    m14 = 0.5f;
    m18 = 21.0f;
    m1C = 0.8f;
    m20 = 0.8f;
    m24 = 450.0f;
    m28 = 350.0f;
    m2C = 30.0f;
    m30 = 0x11;
    m32 = 0x28;
    m34 = 400.0f;
    m38 = 0x2d;
    m3C = 0x2b;
    m3E = 0x2f;
    m3A = 0x46;
    m40 = 55.0f;
    m44 = 30.0f;
    m48 = 25.0f;
    m4C = 0.65f;
    m50 = -5;
    m52 = 0x2af8;
    m54 = 0x258;
    m58 = 1.0f;
    m5C = 1.0f;
}

/* 00000230-000002D8       .text anm_init__FP8mt_classifUcfi */
void anm_init(mt_class* i_this, int anmResIdx, float morf, unsigned char loopMode, float playSpeed, int soundResIdx) {
    i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Mt", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
}

/* 000002D8-00000350       .text mt_a_d_sub__FPvPv */
void* mt_a_d_sub(void* i_actor, void*) {
    if (fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_MT_e) {
        mt_all_count++;
        mt_class* i_this = (mt_class*)i_actor;
        if (i_this->m454 == 1) {
            mt_fight_count++;
        }
    }
    return NULL;
}

/* 00000350-00000390       .text mt_check__FP8mt_class */
void mt_check(mt_class* i_this) {
    mt_fight_count = 0;
    mt_all_count = 0;
    fpcM_Search(mt_a_d_sub, i_this);
}

/* 00000390-00000478       .text mt_bg_check__FP8mt_class */
void mt_bg_check(mt_class* i_this) {
    f32 f31 = 40.0f + REG0_F(3);

    i_this->current.pos.y -= f31;
    i_this->old.pos.y -= f31;
    i_this->actor_status |= 0x400;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    i_this->current.pos.y += f31;
    i_this->old.pos.y += f31;

    if (i_this->home.pos.y - i_this->current.pos.y > 1000.0f
        && i_this->current.pos.y - i_this->mAcch.m_ground_h > 5000.0f)
    {
        i_this->m1CBC = 1;
        fopAcM_delete(i_this);
    }
}

/* 00000478-0000053C       .text tex_anm_set__FP8mt_classUs */
void tex_anm_set(mt_class* i_this, unsigned short idx) {
    i_this->m345 = 1;
    J3DAnmTexPattern* pJVar2 = (J3DAnmTexPattern*)dComIfG_getObjectRes("Mt", mt_tex_anm_idx[idx]);
    i_this->m346 = mt_tex_max_frame[idx];
    i_this->m33C = pJVar2;
    i_this->m344 = 0;
    i_this->m33C->setFrame(0.0f);

    u16 materialNum = pJVar2->getUpdateMaterialNum();
    for (u16 i = 0; i < materialNum; i++) {
        i_this->m340[i].setAnmTexPattern(pJVar2);
    }
}

/* 0000053C-000005EC       .text mt_eye_tex_anm__FP8mt_class */
void mt_eye_tex_anm(mt_class* i_this) {
    if (i_this->m464 != 0) {
        i_this->m464--;
    } else {
        i_this->m464 = (s16)(50.0f + cM_rndF(100.0f));
        if (i_this->m345 == 0) {
            tex_anm_set(i_this, 0);
        }
    }

    if (i_this->m345 != 0) {
        if (i_this->m344 < i_this->m346) {
            i_this->m344++;
        } else {
            i_this->m345 = 0;
        }
    }
}

/* 00000390-00000478       .text mt_bg_check__FP8mt_class */
/* 000005EC-00000720       .text nodeCallBack_head__FP7J3DNodei */
static BOOL nodeCallBack_head(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        mt_class* i_this = (mt_class*)model->getUserArea();

        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[0].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[0].z);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, i_this->m640[15].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[15].z);
            } else {
                MtxScale(i_this->m18F0, i_this->m18F0, i_this->m18F0, 1);
            }

            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 0000075C-0000098C       .text nodeCallBack_body__FP7J3DNodei */
static BOOL nodeCallBack_body(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        mt_class* i_this = (mt_class*)model->getUserArea();

        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[j_index + 1].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 1].z);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[j_index + 2].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 2].z);
            } else if (jntNo == 4) {
                cMtx_YrotM(*calc_mtx, i_this->m640[j_index + 16].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 16].z);
            } else if (jntNo == 5) {
                cMtx_YrotM(*calc_mtx, i_this->m640[j_index + 17].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[j_index + 17].z);
                j_index += 2;
            }

            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 0000098C-00000B28       .text nodeCallBack_tail__FP7J3DNodei */
static BOOL nodeCallBack_tail(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        mt_class* i_this = (mt_class*)model->getUserArea();

        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

            if (jntNo == 2) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[13].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[13].z);
            } else if (jntNo == 3) {
                cMtx_YrotM(*calc_mtx, -i_this->m640[14].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[14].z);
            } else if (jntNo == 4) {
                cMtx_YrotM(*calc_mtx, i_this->m640[28].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[28].z);
            } else if (jntNo == 5) {
                cMtx_YrotM(*calc_mtx, i_this->m640[29].x);
                cMtx_ZrotM(*calc_mtx, -i_this->m640[29].z);
            }

            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000B28-0000171C       .text body_control2__FP8mt_class */
void body_control2(mt_class*) {
    /* Nonmatching */
}

/* 00001B54-00001E44       .text wall_check_sub__FP8mt_classP4cXyzP4cXyz */
BOOL wall_check_sub(mt_class* i_this, cXyz* pStart, cXyz* pEnd) {
    dBgS_LinChk linChk;

    linChk.Set(pStart, pEnd, i_this);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        return TRUE;
    }
    return FALSE;
}

/* 00001E44-00001F10       .text body_wall_check__FP8mt_class */
void body_wall_check(mt_class* i_this) {
    for (int i = 1; i < 8; i++) {
        cXyz pStart = i_this->m500[i];
        pStart.y += 50.0f;
        cXyz pEnd = i_this->m4A0[i];
        pEnd.y += 50.0f;

        if (wall_check_sub(i_this, &pStart, &pEnd)) {
            i_this->m4A0[i].x = i_this->m500[i].x;
            i_this->m4A0[i].z = i_this->m500[i].z;
        }
    }
}

/* 00001F10-000022D8       .text body_control1__FP8mt_class */
void body_control1(mt_class*) {
    /* Nonmatching */
}

/* 000022D8-000028BC       .text body_control3__FP8mt_class */
void body_control3(mt_class*) {
    /* Nonmatching */
}

/* 000028BC-00002AB0       .text body_control4__FP8mt_class */
void body_control4(mt_class*) {
    /* Nonmatching */
}

/* 00002AB0-00003008       .text body_control5__FP8mt_class */
void body_control5(mt_class*) {
    /* Nonmatching */
}

/* 00003008-00003210       .text br_draw__FP8mt_class */
void br_draw(mt_class*) {
    /* Nonmatching */
}

/* 00003210-00003360       .text daMt_shadowDraw__FP8mt_class */
static void daMt_shadowDraw(mt_class*) {
    /* Nonmatching */
}

/* 00003360-0000361C       .text daMt_Draw__FP8mt_class */
static BOOL daMt_Draw(mt_class*) {
    /* Nonmatching */
}

/* 0000361C-000037B0       .text bakuha__FP8mt_class */
void bakuha(mt_class*) {
    /* Nonmatching */
}

/* 000037B0-000042C4       .text mt_move__FP8mt_class */
void mt_move(mt_class*) {
    /* Nonmatching */
}

/* 000042C4-00005088       .text mt_fight__FP8mt_class */
void mt_fight(mt_class*) {
    /* Nonmatching */
}

/* 00005088-00005A04       .text mt_move_maru__FP8mt_class */
void mt_move_maru(mt_class*) {
    /* Nonmatching */
}

/* 00005B9C-00005C54       .text water_damage_se_set__FP8mt_class */
void water_damage_se_set(mt_class* i_this) {
    s8 reverb = dComIfGp_getReverb(i_this->current.roomNo);
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_MAGTAIL_WATER, &i_this->eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);

    reverb = dComIfGp_getReverb(i_this->current.roomNo);
    JAIZelBasic::zel_basic->monsSeStart(JA_SE_CV_MG_WATER, &i_this->eyePos, fopAcM_GetID(i_this), 0, reverb);
    i_this->m348 = 1;
}

/* 00005C54-0000614C       .text damage_check__FP8mt_class */
void damage_check(mt_class*) {
    /* Nonmatching */
}

/* 00006188-000074D4       .text daMt_Execute__FP8mt_class */
static BOOL daMt_Execute(mt_class*) {
    /* Nonmatching */
}

/* 00007CC4-00007CCC       .text daMt_IsDelete__FP8mt_class */
static BOOL daMt_IsDelete(mt_class*) {
    return TRUE;
}

/* 00007CCC-00007E18       .text daMt_Delete__FP8mt_class */
static BOOL daMt_Delete(mt_class*) {
    /* Nonmatching */
}

/* 00007E18-00008400       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000084AC-000088A8       .text daMt_Create__FP10fopAc_ac_c */
static cPhs_State daMt_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph eye_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* Radius */ 30.0f,
        }},
    };
}

static actor_method_class l_daMt_Method = {
    (process_method_func)daMt_Create,
    (process_method_func)daMt_Delete,
    (process_method_func)daMt_Execute,
    (process_method_func)daMt_IsDelete,
    (process_method_func)daMt_Draw,
};

actor_process_profile_definition g_profile_MT = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_MT_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mt_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_MT_e,
    /* Actor SubMtd */ &l_daMt_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e | fopAcStts_UNK8000000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
