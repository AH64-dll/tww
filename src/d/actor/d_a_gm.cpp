/**
 * d_a_gm.cpp
 * Mini-Boss - Mothula / Enemy - Mothula Larva
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_gm.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_player.h"
#include "SSystem/SComponent/c_math.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"

/* 000000EC-0000032C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        gm_class* i_this = (gm_class*)model->getUserArea();
        s32 jntNo = ((J3DJoint*)node)->getJntNo();
        if (i_this && i_this->m2CD == 0) {
            cXyz offset;
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            switch (jntNo) {
            case 3: {
                offset.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&offset, &i_this->m3FC);
                break;
            }
            case 4: {
                offset.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&offset, &i_this->m3F0);
                mDoMtx_YrotM(*calc_mtx, i_this->m43A);
                mDoMtx_XrotM(*calc_mtx, i_this->m438);
                mDoMtx_ZrotM(*calc_mtx, i_this->m43C);
                break;
            }
            case 5: {
                offset.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&offset, &i_this->m3E4);
                offset.x = 70.0f;
                MtxPosition(&offset, &i_this->m3A8);
                break;
            }
            case 12:
            case 14:
            case 16:
            case 18: {
                s32 idx = (jntNo - 0xC) >> 1;
                mDoMtx_YrotM(*calc_mtx, i_this->m414[idx].y);
                mDoMtx_XrotM(*calc_mtx, i_this->m414[idx].x);
                mDoMtx_ZrotM(*calc_mtx, i_this->m414[idx].z);
                break;
            }
            }
            if (jntNo != 12 && jntNo != 14 && jntNo != 16 && jntNo != 18) {
                mDoMtx_YrotM(*calc_mtx, i_this->m42E);
                mDoMtx_XrotM(*calc_mtx, i_this->m42C);
                mDoMtx_ZrotM(*calc_mtx, i_this->m430);
            }
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000368-0000048C       .text draw_SUB__FP8gm_class */
void draw_SUB(gm_class* i_this) {
    J3DModel* model = i_this->mpMorf->getModel();
    model->setBaseScale(i_this->scale);

    mDoMtx_stack_c::transS(i_this->current.pos.x + i_this->m3B4.x, i_this->current.pos.y + i_this->m3B4.y,
                           i_this->current.pos.z + i_this->m3B4.z);
    mDoMtx_XrotM(mDoMtx_stack_c::get(), i_this->m43E);
    mDoMtx_ZrotM(mDoMtx_stack_c::get(), i_this->m442);
    mDoMtx_YrotM(mDoMtx_stack_c::get(), i_this->shape_angle.y);
    mDoMtx_XrotM(mDoMtx_stack_c::get(), i_this->shape_angle.x);
    mDoMtx_YrotM(mDoMtx_stack_c::get(), i_this->m320);
    mDoMtx_ZrotM(mDoMtx_stack_c::get(), i_this->shape_angle.z);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

    if (i_this->m2CD == 0) {
        i_this->mpMorf->calc();
        enemy_fire(&i_this->mEnemyFire);
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);
}

/* 0000048C-00000908       .text daGM_Draw__FP8gm_class */
static BOOL daGM_Draw(gm_class*) {
    /* Nonmatching */
}

/* 00000908-00000A34       .text anm_init__FP8gm_classifUcfi */
static void anm_init(gm_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    /* Nonmatching */
    i_this->m344 = bckFileIdx;
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("GM", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            dComIfG_getObjectRes("GM", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("GM", bckFileIdx),
            loopMode, morf, speed, 0.0f, -1.0f,
            NULL
        );
    }
}

/* 00000A34-00000D00       .text wing_cut_stat__FP8gm_class */
void wing_cut_stat(gm_class*) {
    /* Nonmatching */
}

/* 00000D3C-0000170C       .text body_atari_check__FP8gm_class */
void body_atari_check(gm_class*) {
    /* Nonmatching */
}

/* 0000170C-000017D8       .text BG_check__FP8gm_class */
void BG_check(gm_class*) {
    /* Nonmatching */
}

/* 000017D8-00001B84       .text Line_check__FP8gm_class4cXyz */
void Line_check(gm_class*, cXyz) {
    /* Nonmatching */
}

/* 00001FBC-0000212C       .text ks_set_rtn__FP8gm_class */
s32 ks_set_rtn(gm_class* i_this) {
    /* Nonmatching */
    s32 type = 4;

    if (i_this->m2CE == 1) {
        if (i_this->m31E >= 10) {
            return 1;
        }
    } else if (i_this->m31E >= 20) {
        return 1;
    }

    if (i_this->mAction == 0x53) {
        type = 5;
    }

    JAIZelBasic::zel_basic->seStart(0x58A6, &i_this->eyePos, 0, dComIfGp_getReverb((s8)i_this->current.roomNo), 900.0f, 900.0f, -30.0f, -30.0f, 0);

    csXyz sp10 = i_this->current.angle;
    sp10.y = (s16)((f32)sp10.y + cM_rndFX(300.0f));

    if ((u32)(fopAcM_createChild(0xCE, fopAcM_GetID(i_this), type, &i_this->m3FC, (s8)i_this->current.roomNo, &sp10, &i_this->scale, 0, NULL) + 0x10000) != 0xFFFF) {
        i_this->m31E++;
        return 0;
    }
    return 1;
}

/* 0000212C-00002204       .text wing_ret_set__FP8gm_class */
void wing_ret_set(gm_class*) {
    /* Nonmatching */
}

/* 00002204-000022C4       .text fuwafuwa_set__FP8gm_class */
void fuwafuwa_set(gm_class* i_this) {
    /* Nonmatching */
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if (i_this->current.pos.z >= player->current.pos.z + 176.0f) {
        i_this->m2F0 += 1000;
        i_this->m3C4 = cM_ssin(i_this->m2F0) * 0.5f;
        if (i_this->mAction == 3 || i_this->mAction == 4) {
            i_this->m3C0 = 0.0f;
            i_this->m3C4 = 0.0f;
            i_this->m3C8 = 0.0f;
        }
        cLib_addCalc2(&i_this->m3B4.y, i_this->m3C4, 900.0f, 94.0f);
    }
}

/* 000022C4-00002474       .text fly_move__FP8gm_class */
void fly_move(gm_class*) {
    /* Nonmatching */
}

/* 00002474-00002AB8       .text action_dousa__FP8gm_class */
void action_dousa(gm_class*) {
    /* Nonmatching */
}

/* 00002AB8-00002C9C       .text action_hane_rakka__FP8gm_class */
void action_hane_rakka(gm_class*) {
    /* Nonmatching */
}

/* 00002C9C-000030FC       .text action_uchiwa_dousa__FP8gm_class */
void action_uchiwa_dousa(gm_class*) {
    /* Nonmatching */
}

/* 000030FC-00003E54       .text action_totugeki__FP8gm_class */
void action_totugeki(gm_class*) {
    /* Nonmatching */
}

/* 00003E54-00004204       .text action_kabehari__FP8gm_class */
void action_kabehari(gm_class*) {
    /* Nonmatching */
}

/* 00004204-000046F0       .text action_fly_damage__FP8gm_class */
void action_fly_damage(gm_class*) {
    /* Nonmatching */
}

/* 000046F0-00005C78       .text action_ground_attack__FP8gm_class */
void action_ground_attack(gm_class*) {
    /* Nonmatching */
}

/* 00005C78-00006A98       .text action_demo__FP8gm_class */
void action_demo(gm_class*) {
    /* Nonmatching */
}

/* 00006A98-00007770       .text daGM_Execute__FP8gm_class */
static BOOL daGM_Execute(gm_class*) {
    /* Nonmatching */
}

/* 00007770-00007778       .text daGM_IsDelete__FP8gm_class */
static BOOL daGM_IsDelete(gm_class*) {
    return TRUE;
}

/* 00007778-000078C4       .text daGM_Delete__FP8gm_class */
static BOOL daGM_Delete(gm_class*) {
    /* Nonmatching */
}

/* 000078C4-00007E74       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00007EBC-0000842C       .text daGM_Create__FP10fopAc_ac_c */
static cPhs_State daGM_Create(fopAc_ac_c* i_this) {
    /* Nonmatching */
    gm_class* a_this = (gm_class*)i_this;

    fopAcM_SetupActor(a_this, gm_class);

    static dCcD_SrcSph weapon_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK2,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
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
    static dCcD_SrcCyl body_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_METAL,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcCyl wing_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_METAL,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK6,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcCyl wind_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_WIND,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e | cCcD_AtSPrm_NoTgHitInfSet_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsOther_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
}

static actor_method_class l_daGM_Method = {
    (process_method_func)daGM_Create,
    (process_method_func)daGM_Delete,
    (process_method_func)daGM_Execute,
    (process_method_func)daGM_IsDelete,
    (process_method_func)daGM_Draw,
};

actor_process_profile_definition g_profile_GM = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_GM_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(gm_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_GM_e,
    /* Actor SubMtd */ &l_daGM_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
