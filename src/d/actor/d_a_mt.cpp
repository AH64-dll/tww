/**
 * d_a_mt.cpp
 * Enemy - Magtail
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mt.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_main.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_com_inf_game.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_hostIO.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_snap.h"
#include "d/d_path.h"
#include "res/Object/Mt.h"
#include "JAZelAudio/JAIZelBasic.h"

static daMt_HIO_c l_HIO;
static s32 mt_all_count;
static s32 mt_fight_count;
static s32 j_index;
static u16 mt_tex_anm_idx[] = {dRes_INDEX_MT_BTP_MG_MABA_e, dRes_INDEX_MT_BTP_MG_TOJI_e};
static u16 mt_tex_max_frame[] = {6, 1};
static s32 brk_data[] = {dRes_INDEX_MT_BRK_MG_HEAD1_e, dRes_INDEX_MT_BRK_MG_BODY1_e, dRes_INDEX_MT_BRK_MG_BODY1_e, dRes_INDEX_MT_BRK_MG_BODY1_e, dRes_INDEX_MT_BRK_MG_BODY1_e, dRes_INDEX_MT_BRK_MG_BODY1_e, dRes_INDEX_MT_BRK_MG_BODY1_e, dRes_INDEX_MT_BRK_MG_TAIL1_e};
static s32 btk_data[] = {dRes_INDEX_MT_BTK_MG_HEAD1_e, dRes_INDEX_MT_BTK_MG_BODY1_e, dRes_INDEX_MT_BTK_MG_BODY1_e, dRes_INDEX_MT_BTK_MG_BODY1_e, dRes_INDEX_MT_BTK_MG_BODY1_e, dRes_INDEX_MT_BTK_MG_BODY1_e, dRes_INDEX_MT_BTK_MG_BODY1_e, dRes_INDEX_MT_BTK_MG_TAIL1_e};
static s32 move_ad[] = {0, -6, -12, -18, -24, -30, -36, -42};
static s32 move_ad2[] = {0, -3, -6, -9, -12, -15, -18, -21};
static u8 br_no[] = {0, 1, 1, 2, 2, 2, 1, 0, 0, 0, 0};
static s16 br_ya[] = {0xCD38, 0xDCD8, 0xF060, 0, 0, 0, 0, 0, 0, 0, 0};

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
    i_this->mpMorf[0]->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Mt", anmResIdx), loopMode, morf, playSpeed, 0.0f, -1.0f, NULL);
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
    /* Nonmatching */
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
void body_control1(mt_class* i_this) {
    /* Nonmatching */
    cXyz* p6F4 = &i_this->m6F4[i_this->mBF4];
    p6F4->x = i_this->current.pos.x;
    p6F4->y = i_this->current.pos.y;
    p6F4->z = i_this->current.pos.z;
    csXyz* p9F4 = &i_this->m9F4[i_this->mBF4];
    p9F4->x = i_this->shape_angle.x;
    p9F4->y = i_this->shape_angle.y;
    p9F4->z = i_this->shape_angle.z;
    i_this->mB74[i_this->mBF4] = i_this->m468;

    for (int i = 0; i < 8; i++) {
        u32 idx;
        if (i_this->mC00 != 0) {
            idx = (i_this->mBF4 + move_ad2[i]) & 0x3F;
        } else {
            idx = (i_this->mBF4 + move_ad[i]) & 0x3F;
        }

        mDoExt_McaMorf* morf = i_this->mpMorf[i];
        J3DModel* model = morf->getModel();
        model->setBaseScale(i_this->scale);
        
        

        cXyz* pPos = &i_this->m6F4[idx];
        mDoMtx_stack_c::transS(pPos->x, pPos->y, pPos->z);
        csXyz* pAng = &i_this->m9F4[idx];
        mDoMtx_YrotM(mDoMtx_stack_c::now, pAng->y);
        mDoMtx_XrotM(mDoMtx_stack_c::now, pAng->x);
        mDoMtx_ZrotM(mDoMtx_stack_c::now, pAng->z);
        mDoMtx_YrotM(mDoMtx_stack_c::now, i_this->mB74[idx]);
        if (i == 0) {
            mDoMtx_stack_c::scaleM(l_HIO.m1C, l_HIO.m1C, l_HIO.m1C);
        } else {
            mDoMtx_stack_c::scaleM(i_this->m600[i], i_this->m600[i] * i_this->m620[i], 1.0f);
        }
        mDoMtx_stack_c::transM(0.0f, 0.0f, i_this->m470);
        PSMTXCopy(mDoMtx_stack_c::now, model->getBaseTRMtx());

        if (i == 0) {
            cXyz local14;
            cXyz local8;
            local14.x = 0.0f;
            local14.y = 0.0f;
            local14.z = 30.0f + REG0_F(9);
            PSMTXMultVec(mDoMtx_stack_c::now, &local14, &i_this->eyePos);
            i_this->m17A8.SetC(i_this->eyePos);
            i_this->m17A8.SetR(l_HIO.m44);
            dComIfG_Ccsp()->Set(&i_this->m17A8);

            local14.x = 0.0f;
            local14.y = 0.0f;
            local14.z = 100.0f + g_regHIO.mChild[0].mFloatRegs[225];
            PSMTXMultVec(mDoMtx_stack_c::now, &local14, &local8);
            i_this->mE48[0].SetC(local8);
            i_this->mE48[0].SetR(50.0f);
        } else {
            i_this->mE48[i].SetC(*pPos);
            if (i_this->m460 != 0) {
                i_this->mE48[i].SetR(-200.0f);
            } else {
                i_this->mE48[i].SetR(l_HIO.m48);
            }
        }
        dComIfG_Ccsp()->Set(&i_this->mE48[i]);

        if (i_this->mC01 != 0) {
            i_this->m4A0[i] = *pPos;
            i_this->m560[i] = *pAng;
        }
    }

    if (i_this->m48E == 0) {
        i_this->mBF4++;
    }
    i_this->mBF4 &= 0x3F;

    if (i_this->mC01 != 0) {
        i_this->mC01 = 0;
        i_this->m454 = 1;
        i_this->m455 = 0;
        i_this->m456 = l_HIO.m10;
        i_this->m48E = 0;
        anm_init(i_this, 0xA, 20.0f, 2, 1.0f, 0);
    }

    cLib_addCalc2(&i_this->m470, -10.0f, 1.0f, 1.0f);
}

/* 000022D8-000028BC       .text body_control3__FP8mt_class */
void body_control3(mt_class* i_this) {
    /* Nonmatching */
    cXyz sp30;
    cXyz sp24;
    cXyz sp18;
    cXyz spC;

    i_this->m4A0[0].x = i_this->current.pos.x;
    i_this->m4A0[0].y = i_this->current.pos.y;
    i_this->m4A0[0].z = i_this->current.pos.z;
    i_this->m560[0].x = i_this->shape_angle.x;
    i_this->m560[0].y = i_this->shape_angle.y;
    i_this->m560[0].z = i_this->shape_angle.z;

    cXyz* p500 = &i_this->m500[0];
    cXyz* p4A0 = &i_this->m4A0[0];
    csXyz* p560 = &i_this->m560[0];

    mDoMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
    mDoMtx_XrotM(*calc_mtx, i_this->shape_angle.z);

    sp30.x = 0.0f;
    sp30.y = 32.0f * i_this->m474;
    sp30.z = -17.0f * i_this->m474;
    MtxPosition(&sp30, &spC);

    s16 r19 = 0;
    if (i_this->m18FC != 0) {
        r19 = (s16)((i_this->m18FC & 2) * 0x1F4);
    }

    s32 r28 = 0;
    int i = 0;
    do {
        if (i > 0) {
            r28 -= (s16)(i_this->m488[1] + r19);
            sp30.x = i_this->m330
                     * jmaSinTable[(u16)(i_this->m466 * (REG0_S(5) + 0x1388)
                                         + i * (REG0_S(6) + 0x1B58))
                                   >> jmaSinShift];
            sp30.y = 0.0f;
            sp30.z = -i_this->m478;
            mDoMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
            mDoMtx_XrotM(*calc_mtx, (s16)(i_this->shape_angle.x + r28));
            mDoMtx_ZrotM(*calc_mtx, i_this->shape_angle.z);
            MtxPosition(&sp30, &sp18);

            f32 f30 = sp18.x + (p4A0[0].x - p4A0[-1].x);
            f32 f31 = sp18.y + (p4A0[0].y - p4A0[-1].y);
            f32 f29 = sp18.z + (p4A0[0].z - p4A0[-1].z);
            s16 r20 = cM_atan2s(f30, f29);
            f32 f2 = f30 * f30 + f29 * f29;
            f2 = std::sqrtf(f2);
            s16 r17 = -cM_atan2s(f31, f2);

            sp30.x = 0.0f;
            sp30.y = 0.0f;
            sp30.z = 35.0f + REG0_F(7);
            mDoMtx_YrotS(*calc_mtx, r20);
            mDoMtx_XrotM(*calc_mtx, r17);
            MtxPosition(&sp30, &sp24);

            s16 r0 = r20 - i_this->shape_angle.y;
            if (r0 < 0) {
                r0 = -r0;
            }
            if ((u16)r0 < 0x4000) {
                p560[0].y = r20;
                p560[0].x = (s16)(r17 - 0x8000);
            } else {
                p560[0].y = (s16)(r20 + 0x8000);
                p560[0].x = -r17;
            }

            p500[0].x = p4A0[0].x;
            p500[0].y = p4A0[0].y;
            p500[0].z = p4A0[0].z;
            p4A0[0].x = p4A0[-1].x + sp24.x;
            p4A0[0].y = p4A0[-1].y + sp24.y;
            p4A0[0].z = p4A0[-1].z + sp24.z;
        }

        J3DModel* model = i_this->mpMorf[i]->getModel();
        model->setBaseScale(i_this->scale);
        PSMTXTrans(mDoMtx_stack_c::now, p4A0[0].x + spC.x, p4A0[0].y + spC.y,
                   p4A0[0].z + spC.z);
        mDoMtx_YrotM(mDoMtx_stack_c::now, p560[0].y);
        mDoMtx_XrotM(mDoMtx_stack_c::now, p560[0].x);
        mDoMtx_ZrotM(mDoMtx_stack_c::now, p560[0].z);
        if (i == 0) {
            mDoMtx_stack_c::scaleM(l_HIO.m20, l_HIO.m20, l_HIO.m20);
        } else {
            mDoMtx_stack_c::scaleM(i_this->m600[i], i_this->m600[i] * i_this->m620[i], 1.0f);
            if (i == 7) {
                mDoMtx_stack_c::scaleM(i_this->m18F0, i_this->m18F0, i_this->m18F0);
            }
        }
        mDoMtx_stack_c::transM(0.0f, 0.0f, i_this->m470);
        PSMTXCopy(mDoMtx_stack_c::now, model->getBaseTRMtx());

        if (i == 0) {
            i_this->eyePos = i_this->current.pos;
            i_this->mE48[0].SetC(i_this->current.pos);
            i_this->mE48[0].OnAtSetBit();
            i_this->m17A8.SetR(-30.0f);
            if (fabs(i_this->speedF) > 2.0f) {
                i_this->mE48[0].OnAtVsBitSet(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
            } else {
                i_this->mE48[0].OffAtVsBitSet(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
            }
            if (i_this->m466 < 0x5A) {
                i_this->mE48[0].OnAtVsPlayerBit();
                i_this->mE48[0].SetR(60.0f);
            } else {
                i_this->mE48[0].OffAtVsPlayerBit();
                i_this->mE48[0].SetR(40.0f);
            }
            dComIfG_Ccsp()->Set(&i_this->mE48[0]);
        }
        p500++;
        p4A0++;
        p560++;
        i++;
    } while (i < 8);

    cLib_addCalc0(&i_this->m18F4, 1.0f, 0.01f);
    cLib_addCalc2(&i_this->m470, 20.0f, 1.0f, 1.0f);
    cLib_addCalcAngleS2(&i_this->current.angle.z, 0, 2, 0x400);
}

/* 000028BC-00002AB0       .text body_control4__FP8mt_class */
void body_control4(mt_class* i_this) {
    /* Nonmatching */
    cXyz* pPos = &i_this->m4A0[1];
    cXyz* pSpd = &i_this->m590[1];
    csXyz* pAng = &i_this->m560[1];

    J3DModel* baseModel = i_this->mpMorf[0]->getModel();
    mDoMtx_stack_c::scaleS(0.0f, 0.0f, 0.0f);
    PSMTXCopy(mDoMtx_stack_c::now, baseModel->getBaseTRMtx());

    for (int i = 1; i < 8; i++, pPos++, pAng++, pSpd++) {
        if (i_this->m5F0[i] != 0) {
            i_this->m5F0[i]--;
        } else {
            g_dComIfG_gameInfo.play.getParticle()->setSimple(
                dPa_name::ID_IT_SN_O_MAGT_HAHEN_B, pPos, 0xFF, g_whiteColor, g_whiteColor, 0);
            pPos->x += pSpd->x;
            pPos->y += pSpd->y;
            pPos->z += pSpd->z;
            pSpd->y -= 2.5f;
            pAng->x += 0x1800;
            pAng->y += 0x1000;
            if (pSpd->y < 0.0f) {
                cLib_addCalc0(&i_this->m600[i], 1.0f, 0.025f);
            }
        }

        J3DModel* model = i_this->mpMorf[i]->getModel();
        mDoMtx_stack_c::transS(*pPos);
        mDoMtx_YrotM(mDoMtx_stack_c::now, pAng->y);
        mDoMtx_XrotM(mDoMtx_stack_c::now, pAng->x);
        mDoMtx_ZrotM(mDoMtx_stack_c::now, pAng->z);
        mDoMtx_stack_c::scaleM(i_this->m600[i], i_this->m600[i], i_this->m600[i]);
        if (i == 7) {
            mDoMtx_stack_c::scaleM(0.0f, 0.0f, 0.0f);
        }
        PSMTXCopy(mDoMtx_stack_c::now, model->getBaseTRMtx());
    }
}

/* 00002AB0-00003008       .text body_control5__FP8mt_class */
void body_control5(mt_class*) {
    /* Nonmatching */
}

/* 00003008-00003210       .text br_draw__FP8mt_class */
void br_draw(mt_class* i_this) {
    /* Nonmatching */
    if (i_this->m18D4 == 0) {
        return;
    }

    MtxTrans(i_this->eyePos.x, i_this->eyePos.y, i_this->eyePos.z, 0);
    mDoMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->shape_angle.x);
    mDoMtx_ZrotM(*calc_mtx, i_this->shape_angle.z);
    f32 f31 = l_HIO.m1C * (2.0f + g_regHIO.mChild[0].mFloatRegs[4]);

    MtxPush();
    mDoMtx_YrotM(*calc_mtx, br_ya[i_this->m18D4 - 1]);
    mDoMtx_XrotM(*calc_mtx, -0x4000);
    MtxScale(f31, f31, f31, 1);

    J3DModel* model = i_this->br_modelL[br_no[i_this->m18D4 - 1]];
    g_env_light.setLightTevColorType(model, &i_this->tevStr);
    PSMTXCopy(*calc_mtx, model->getBaseTRMtx());
    mDoExt_modelUpdateDL(model);

    MtxPull();
    mDoMtx_ZrotM(*calc_mtx, -0x8000);
    mDoMtx_YrotM(*calc_mtx, br_ya[i_this->m18D4 - 1]);
    mDoMtx_XrotM(*calc_mtx, -0x4000);
    MtxScale(f31, f31, f31, 1);

    model = i_this->br_modelR[br_no[i_this->m18D4 - 1]];
    g_env_light.setLightTevColorType(model, &i_this->tevStr);
    PSMTXCopy(*calc_mtx, model->getBaseTRMtx());
    mDoExt_modelUpdateDL(model);
}

/* 00003210-00003360       .text daMt_shadowDraw__FP8mt_class */
static void daMt_shadowDraw(mt_class* i_this) {
    /* Nonmatching */
    if (!(i_this->actor_status & 0x2000)) {
        cXyz pos(i_this->current.pos.x, i_this->current.pos.y + 150.0f + REG0_F(18),
                 i_this->current.pos.z);

        i_this->m1CB8 = dComIfGd_setShadow(
            i_this->m1CB8, 1, i_this->mpMorf[0]->getModel(), &pos,
            REG0_F(19) + 800.0f, REG0_F(17) + 40.0f,
            i_this->current.pos.y, i_this->mAcch.GetGroundH(), i_this->mAcch.m_gnd,
            &i_this->tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());

        for (int i = 1; i < 8; i++) {
            dComIfGd_addRealShadow(i_this->m1CB8, i_this->mpMorf[i]->getModel());
        }
    } else {
        daPy_lk_c* player = (daPy_lk_c*)g_dComIfG_gameInfo.play.getPlayerPtr(0);
        u32 shadowId = player->mShadowId;
        if (shadowId != 0) {
            for (int i = 0; i < 8; i++) {
                dComIfGd_addRealShadow(shadowId, i_this->mpMorf[i]->getModel());
            }
        }
    }
}

/* 00003360-00003604       .text daMt_Draw__FP8mt_class */
static BOOL daMt_Draw(mt_class* i_this) {
    /* Nonmatching */
    cXyz zero(0.0f, 0.0f, 0.0f);

    if (i_this->m2BB != 0) {
        return TRUE;
    }

    j_index = 0;
    for (int i = 0; i < 8; i++) {
        mDoExt_McaMorf* morf = i_this->mpMorf[i];
        J3DModel* model = morf->getModel();

        if (i_this->mEnemyIce.mLightShrinkTimer == 0) {
            cXyz pos;
            PSMTXMultVec(model->getBaseTRMtx(), &zero, &pos);
            g_env_light.settingTevStruct(0, &pos, &i_this->tevStr);
        } else {
            f32 iceScale = i_this->mEnemyIce.mScaleXZ;
            i_this->scale.z = iceScale;
            i_this->scale.y = iceScale;
            i_this->scale.x = iceScale;
            model->setBaseScale(i_this->scale);
        }

        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        i_this->btk[i]->entry(model->getModelData());
        i_this->brk[i]->entry(model->getModelData());

        if (i_this->m2E4 == 0) {
            s32 frame = i_this->m2E8 + i * l_HIO.m50;
            while (frame < 0) {
                frame += 0x29;
            }
            i_this->brk[i]->setFrame((f32)frame);

            frame = i_this->m2EC + i * l_HIO.m50;
            while (frame < 0) {
                frame += 0x1F;
            }
            i_this->btk[i]->setFrame((f32)frame);
        } else {
            i_this->brk[i]->setFrame((f32)i_this->m2E8);
            i_this->btk[i]->setFrame((f32)i_this->m2EC);
        }

        if (i == 0) {
            model->getModelData()->setTexNoAnimator(i_this->m33C, i_this->m340);
            i_this->m33C->setFrame((f32)i_this->m344);
        }

        i_this->mpMorf[i]->updateDL();
    }

    br_draw(i_this);
    daMt_shadowDraw(i_this);
    dSnap_RegistFig(DSNAP_TYPE_UNKAF, i_this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 0000361C-000037B0       .text bakuha__FP8mt_class */
void bakuha(mt_class* i_this) {
    /* Nonmatching */
    fopAcM_createDisappear(i_this, &i_this->eyePos, 0xA, 0, 0xFF);

    if (i_this->m2B6 == 0 && i_this->m2B9 != 0) {
        dComIfGs_onSwitch(i_this->m2B9, fopAcM_GetRoomNo(i_this));
    }

    i_this->m454 = 3;
    i_this->m45A = REG0_S(0) + 0x39;

    for (int i = 1; i < 8; i++) {
        i_this->m590[i].x = cM_rndFX(30.0f + REG0_F(4));
        i_this->m590[i].y = REG0_F(5) + (20.0f + cM_rndF(10.0f));
        i_this->m590[i].z = cM_rndFX(30.0f + REG0_F(4));
        i_this->m5F0[i] = (s16)cM_rndF(3.0f);
        if ((s32)i_this->m18F8 == 3) {
            i_this->m5F0[i] += 5;
        }
    }

    dPa_control_c* particle = g_dComIfG_gameInfo.play.getParticle();
    particle->set(0, dPa_name::ID_IT_SN_MAGT_HAHEN_A, &i_this->current.pos, NULL, NULL, 0xFF,
                  NULL, -1, NULL, NULL, NULL);
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
static BOOL daMt_Execute(mt_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    if (enemy_ice(&i_this->mEnemyIce)) {
        return TRUE;
    }

    if (i_this->m2BB != 0) {
        if (!dComIfGs_isSwitch(i_this->m2BB - 1, i_this->current.roomNo)) {
            return TRUE;
        }
        i_this->m2BB = 0;
    }

    i_this->actor_status |= 0x20;

    dBgS_ObjGndChk_Yogan gndChk;
    cXyz gndPos = i_this->current.pos;
    gndPos.y += 200.0f;
    gndChk.SetPos(&gndPos);
    f32 gndH = dComIfG_Bgsp()->GroundCross(&gndChk);
    if (gndH != -1.0e9f && (i_this->current.pos.y - 30.0f) + REG0_F(13) < gndH) {
        if (i_this->m18FA == 0) {
            i_this->speedF *= 0.1f;
            i_this->speed.y = 0.0f;
            cXyz pillarPos = i_this->current.pos;
            fopKyM_createMpillar(&pillarPos, 0.5f);
        }
        i_this->m18FA = 1;
        i_this->gravity = -0.5f;
        if (i_this->speed.y < -5.0f) {
            i_this->speed.y = -5.0f;
        }
    } else {
        i_this->m18FA = 0;
        i_this->gravity = -3.0f;
    }

    i_this->attention_info.flags = 4;
    mt_eye_tex_anm(i_this);

    if (l_HIO.m04 == 0) {
        if (i_this->m18D4 != 0) {
            i_this->m18D4++;
            if (i_this->m18D4 == 0xB) {
                i_this->m18D4 = 0;
            }
        }

        i_this->mBtStartFrame = 100.0f;
        i_this->mBtEndFrame = 100.0f;
        i_this->mBtMaxDis = 10000.0f;
        i_this->mBtAttackType = 0;
        i_this->mBtNowFrame = 0.0f;

        for (int i = 0; i < 5; i++) {
            s16* timer = &i_this->m456 + i;
            if (*timer != 0) {
                (*timer)--;
            }
        }
        if (i_this->m18FC != 0) {
            i_this->m18FC--;
        }
        if (i_this->m460 != 0) {
            i_this->m460--;
        }
        if (i_this->m462 != 0) {
            i_this->m462--;
        }
        if (i_this->m34A != 0) {
            i_this->m34A--;
        }
        if (i_this->m48E != 0) {
            i_this->m48E--;
            i_this->m490++;
        } else {
            if (i_this->m490 != 0) {
                if (i_this->m490 > 0xF) {
                    i_this->m490 = 0xF;
                }
                i_this->m490--;
            }
        }
        i_this->m46A++;
        if (i_this->m466 != 0) {
            i_this->m466--;
        }

        if (i_this->m454 < 3) {
            damage_check(i_this);
        }

        i_this->mC04 = 0;

        dBgS_LinChk linChk;
        cXyz playerPos = player->current.pos;
        playerPos.y += 20.0f;
        cXyz selfPos = i_this->current.pos;
        selfPos.y += 30.0f;
        linChk.Set(&selfPos, &playerPos, i_this);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            i_this->m18F9 = 1;
        } else {
            i_this->m18F9 = 0;
        }

        switch (i_this->m454) {
        case 0:
            mt_move(i_this);
            cLib_addCalcAngleS2(&i_this->shape_angle.x, i_this->current.angle.x, 2, 0x800);
            cLib_addCalcAngleS2(&i_this->shape_angle.y, i_this->current.angle.y, 2, 0x800);
            cLib_addCalcAngleS2(&i_this->shape_angle.z, i_this->current.angle.z, 4, 0x400);
            body_control1(i_this);

            cXyz* ccmove = i_this->mStts.GetCCMoveP();
            if (ccmove != NULL) {
                i_this->current.pos.x += ccmove->x;
                i_this->current.pos.z += ccmove->z;
                for (int i = 0; i < 64; i++) {
                    i_this->m6F4[i].x += ccmove->x;
                    i_this->m6F4[i].z += ccmove->z;
                }
            }

            if (i_this->m458 == 0) {
                i_this->m458 = (s16)(150.0f + cM_rndF(100.0f));
                if (l_HIO.m05 == 0 && abs(i_this->current.angle.x) < 0x1000) {
                    i_this->m48E = (s16)(REG0_F(8) + (50.0f + cM_rndF(50.0f)));
                }
            }
            break;
        case 1: {
            mt_fight(i_this);
            {
                f32 scale = (f32)i_this->m462 * (500.0f + REG0_F(14));
                i_this->m49C = (s16)(scale * jmaSinTable[(u16)(i_this->m46A * 0x2100) >> jmaSinShift]);
                i_this->m49A = (s16)(scale * jmaCosTable[(u16)(i_this->m46A * 0x2300) >> jmaSinShift]);
            }
            csXyz sp18 = i_this->current.angle + *(csXyz*)&i_this->m49A;
            i_this->shape_angle.x = sp18.x;
            i_this->shape_angle.y = sp18.y;
            i_this->shape_angle.z = sp18.z;
            body_control2(i_this);
            body_wall_check(i_this);
            mt_bg_check(i_this);

            cXyz* ccmove = i_this->mStts.GetCCMoveP();
            if (ccmove != NULL) {
                i_this->current.pos.x += ccmove->x;
                i_this->current.pos.z += ccmove->z;
            }
            break;
        }
        case 2: {
            mt_move_maru(i_this);
            body_control3(i_this);
            if (i_this->m466 <= 0x64) {
                body_wall_check(i_this);
            } else if (i_this->m18FA != 0 && i_this->m466 > 0x32) {
                i_this->m466 = 0x47;
            }

            cXyz* ccmove = i_this->mStts.GetCCMoveP();
            if (ccmove != NULL) {
                i_this->current.pos.x += ccmove->x;
                i_this->current.pos.z += ccmove->z;
            }

            if (i_this->m466 == 0x32) {
                i_this->m2E4 = 0;
                i_this->m454 = 1;
                i_this->m455 = 0;
                i_this->m18FB = 2;
                i_this->max_health = 8;
                i_this->mE48[0].OnTgSetBit();
                i_this->m456 = l_HIO.m10;
                i_this->m48E = 0;
                anm_init(i_this, 0xA, 20.0f, 2, 1.0f, 0);
                fopAcM_SetMin(i_this, -200.0f, -200.0f, -200.0f);
                fopAcM_SetMax(i_this, 200.0f, 200.0f, 200.0f);
                i_this->mE48[0].OffAtVsBitSet(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
                i_this->mE48[0].OnAtVsPlayerBit();
            }
            break;
        }
        case 3:
            i_this->m460 = 5;
            i_this->attention_info.flags = 0;
            body_control4(i_this);
            if (i_this->m45A == 1) {
                i_this->m1CBC = 1;
                fopAcM_delete(i_this);
                dComIfGs_onActor(i_this->setID, fopAcM_GetHomeRoomNo(i_this));
            }
            break;
        case 6:
            if (((daPy_lk_c*)player)->mCutType == 0x10) {
                mDoMtx_YrotS(*calc_mtx, i_this->shape_angle.y);
                cXyz offset(0.0f, 0.0f, -50.0f + REG0_F(14));
                cXyz result;
                MtxPosition(&offset, &result);
                cLib_addCalc2(&i_this->current.pos.x, player->current.pos.x + result.x, 0.5f, 50.0f);
                cLib_addCalc2(&i_this->current.pos.z, player->current.pos.z + result.z, 0.5f, 50.0f);
            }
            i_this->m464 = 3;
            i_this->m2E4 = 1;
            i_this->m460 = 5;
            body_control5(i_this);
            i_this->current.pos.y += i_this->speed.y;
            i_this->speed.y += i_this->gravity;
            mt_bg_check(i_this);

            if (i_this->m456 == 0) {
                if (((daPy_lk_c*)player)->mCutType != 0x10) {
                    i_this->m2E4 = 0;
                    i_this->m454 = 1;
                    i_this->m455 = 0;
                    i_this->mE48[0].OnTgSetBit();
                    i_this->m456 = l_HIO.m10;
                    i_this->m48E = 0;
                    anm_init(i_this, 0xA, 20.0f, 2, 1.0f, 0);
                    i_this->mE48[0].OffAtVsBitSet(cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e);
                    i_this->mE48[0].OnAtVsPlayerBit();
                } else {
                    i_this->m474 = 0.2f + REG0_F(13);
                    if (i_this->m17A8.ChkTgHit()) {
                        i_this->max_health = 0;
                        i_this->m456 = REG0_S(3) + 0x28;
                        i_this->m474 = 1.5f + REG0_F(13);
                        JAIZelBasic::zel_basic->seStart(0x2828, &i_this->eyePos, 0,
                                                        dComIfGp_getReverb(i_this->current.roomNo), 1.0f, 1.0f,
                                                        -1.0f, -1.0f, 0);
                        s8 reverb = dComIfGp_getReverb(i_this->current.roomNo);
                        JAIZelBasic::zel_basic->monsSeStart(0x4803, &i_this->eyePos, fopAcM_GetID(i_this), 0, reverb);
                        CcAtInfo atInfo;
                        atInfo.mpObj = i_this->m17A8.GetTgHitObj();
                        at_power_check(&atInfo);
                        JAIZelBasic::zel_basic->onEnemyDamage();
                        JAIZelBasic::zel_basic->bgmHitSound(atInfo.mHitSoundId);
                        dScnPly_ply_c::nextPauseTimer = REG0_S(7) + 6;
                        g_dComIfG_gameInfo.play.getParticle()->set(
                            0, dPa_name::ID_AK_JN_CRITICALHITFLASH, &i_this->current.pos, NULL, NULL, 0xFF, NULL,
                            -1, NULL, NULL, NULL);
                        cXyz scale(2.0f, 2.0f, 2.0f);
                        csXyz angle(0, 0, fopAcM_searchActorAngleY(i_this, player));
                        g_dComIfG_gameInfo.play.getParticle()->set(
                            0, dPa_name::ID_AK_JN_OK, &i_this->current.pos, &angle, &scale, 0xFF, NULL, -1, NULL,
                            NULL, NULL);
                        dKy_SordFlush_set(i_this->current.pos, 1);
                        anm_init(i_this, 8, 5.0f, 0, 1.0f, 0);
                    }
                }
            } else {
                i_this->m46E = 0;
                cLib_addCalc0(&i_this->m474, 0.05f, 0.02f + REG0_F(12));
                if (i_this->m456 == 1) {
                    bakuha(i_this);
                }
            }
            break;
        }

        if (i_this->m466 > 0x3C) {
            cLib_addCalc0(&i_this->m18F0, 1.0f, 0.05f);
        } else {
            cLib_addCalc2(&i_this->m18F0, 1.0f, 1.0f, 0.1f);
        }
    }

    f32 f30 = 40.0f;
    dBgS_ObjLinChk linChk1;
    cXyz oldPos1 = i_this->old.pos;
    oldPos1.y += f30;
    linChk1.Set(&i_this->old.pos, &oldPos1, i_this);
    if (dComIfG_Bgsp()->LineCross(&linChk1)) {
        f30 = (linChk1.GetCross().y - 1.0f) - i_this->old.pos.y;
        if (f30 < 0.0f) {
            f30 = 0.0f;
        }
    }

    cXyz selfPos1 = i_this->old.pos;
    selfPos1.y += f30;
    cXyz selfPos2 = i_this->current.pos;
    selfPos2.y += f30;
    dBgS_ObjLinChk linChk2;
    linChk2.Set(&selfPos1, &selfPos2, i_this);
    u8 cross2 = dComIfG_Bgsp()->LineCross(&linChk2);
    dBgS_ObjLinChk linChk3;
    linChk3.Set(&selfPos2, &selfPos1, i_this);
    u8 cross3 = dComIfG_Bgsp()->LineCross(&linChk3);
    if (cross2 != 0 && cross3 == 0) {
        i_this->current.pos = linChk2.GetCross();
        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(linChk2.GetBgIndex(), linChk2.GetPolyIndex());
        i_this->current.pos.x += triPla->mNormal.x;
        i_this->current.pos.y += triPla->mNormal.y;
        i_this->current.pos.z += triPla->mNormal.z;
    }

    i_this->attention_info.position = i_this->eyePos;

    s32 step = 1;
    s32 min1, max1, max2;
    switch (i_this->m2E4) {
    case 0:
        min1 = 0;
        max1 = 0x28;
        max2 = 0x1E;
        break;
    case 1:
        min1 = 0x28;
        max1 = 0x64;
        max2 = 0x5A;
        step = 2;
        break;
    case 2:
        min1 = 0x64;
        max1 = 0x82;
        max2 = 0x78;
        break;
    }

    i_this->m2E8 += step;
    if (i_this->m2E8 > max1) {
        i_this->m2E8 = i_this->m2E4 == 0 ? min1 : max1;
    }
    i_this->m2EC += step;
    if (i_this->m2EC > max2) {
        i_this->m2EC = i_this->m2E4 == 0 ? 0 : max2;
    }

    if (i_this->m454 < 2 || i_this->m466 <= 0x78) {
        if (i_this->m466 == 0x78) {
            i_this->m490 = 0xF;
        }
        i_this->mpMorf[0]->play(&i_this->current.pos, 0, 0);
        i_this->m46E += l_HIO.m08;

        for (int i = 0; i < 0x1E; i++) {
            s32 idx = i >= 0xF ? i - 0xF : i;
            s16 angle;
            if (i_this->m48E != 0) {
                angle = idx >= i_this->m490 ? i_this->m46E : 0;
            } else {
                angle = (0xE - idx) >= i_this->m490 ? i_this->m46E : 0;
            }
            i_this->m640[i].x = (s16)((5000.0f + REG6_F(11)) * -jmaSinTable[(u16)(angle + i * (REG6_S(2) + 0x32C8)) >> jmaSinShift]);
            cLib_addCalcAngleS2(&i_this->m640[i].y,
                                (s16)(l_HIO.m0C + (5000.0f + REG6_F(12)) * jmaCosTable[(u16)(angle + i * (REG6_S(3) + 0x32C8)) >> jmaSinShift]),
                                1, i_this->m334);
        }
        cLib_addCalcAngleS2(&i_this->m334, 0x2000, 1, 0x100);

        for (int i = 0; i < 8; i++) {
            i_this->m620[i] = 1.0f + i_this->m338 * jmaSinTable[(u16)(i_this->m46A * (REG0_S(5) + 0x9C4) + i * (REG0_S(6) + 0x1D4C)) >> jmaSinShift];
        }
        cLib_addCalc2(&i_this->m338, 0.1f, 1.0f, 0.002f);
    } else {
        i_this->m334 = 0;
        for (int i = 0; i < 0x1E; i++) {
            i_this->m640[i].x = 0;
            cLib_addCalcAngleS2(&i_this->m640[i].y, 0x2710, 0xA, 0x12C);
        }
    }

    if (!(i_this->m2B4 & 1)) {
        for (int i = 0; i < 8; i++) {
            cXyz pos(REG0_F(5), REG0_F(6), REG0_F(7));
            J3DModel* model = i_this->mpMorf[i]->getModel();
            PSMTXMultVec(model->getBaseTRMtx(), &pos, &i_this->m350[i]);
            if ((i_this->m454 >= 2 && i_this->m466 > 0x28) || i_this->m454 == 6 || l_HIO.m07 != 0) {
                i_this->m350[i].y += 10000.0f;
            }
            if (i >= 0 && i <= 6) {
                g_dComIfG_gameInfo.play.getParticle()->setSimple(dPa_name::ID_IT_SN_O_MAGT_FCHIP, &i_this->m350[i],
                                                                 0xFF, g_whiteColor, g_whiteColor, 0);
            }
            if (i >= 1 && i <= 6) {
                g_dComIfG_gameInfo.play.getParticle()->setSimple(dPa_name::ID_IT_SN_O_MAGT_NETSU, &i_this->m350[i],
                                                                 0xFF, g_whiteColor, g_whiteColor, 0);
            }
            if (i_this->m34C == 0 && (i == 1 || i == 3 || i == 5)) {
                g_dComIfG_gameInfo.play.getParticle()->set(
                    4, dPa_name::ID_IT_SP_MAGT_KAGERO, &i_this->m350[i], NULL, NULL, 0xFF, &i_this->m3B0[i], -1,
                    NULL, NULL, NULL);
            }
        }
        i_this->m34C = 1;
    }

    if (i_this->m454 < 2 && i_this->m18FA == 0 && i_this->m48E == 0) {
        if (i_this->m45C == 0) {
            i_this->m45C = (s16)(45.0f + cM_rndF(45.0f));
            s8 reverb = dComIfGp_getReverb(i_this->current.roomNo);
            JAIZelBasic::zel_basic->monsSeStart(0x4801, &i_this->eyePos, fopAcM_GetID(i_this), 0, reverb);
        }
        if (i_this->m45E == 0) {
            i_this->m45E = (s16)(6.0f + cM_rndF(3.0f));
            s8 reverb = dComIfGp_getReverb(i_this->current.roomNo);
            JAIZelBasic::zel_basic->monsSeStart(0x580F, &i_this->eyePos, fopAcM_GetID(i_this), 0, reverb);
        }
    }

    if ((s8)i_this->m18F8 >= 2) {
        bakuha(i_this);
        i_this->m18F8 = 0xFF;
    }

    return TRUE;
}

/* 00007CC4-00007CCC       .text daMt_IsDelete__FP8mt_class */
static BOOL daMt_IsDelete(mt_class*) {
    return TRUE;
}

/* 00007CCC-00007E18       .text daMt_Delete__FP8mt_class */
static BOOL daMt_Delete(mt_class* i_this) {
    dComIfG_resDelete(&i_this->mPhase, "Mt");

    if (i_this->m450 != NULL) {
        i_this->m450->quitImmortalEmitter();
        JPABaseEmitter* emitter = i_this->m450;
        emitter->mMaxFrame = -1;
        emitter->setStatus(JPAEmtrStts_StopEmit);
        i_this->m450 = NULL;
    }

    for (int i = 0; i < 8; i++) {
        i_this->m3B0[i].end();
    }

    if (i_this->m1CBC != 0 && i_this->m2B6 != 0 && i_this->m2BA != 0
        && !dComIfGs_isSwitch(i_this->m2BA, fopAcM_GetRoomNo(i_this)))
    {
        fopAcM_prm_class* prm = fopAcM_CreateAppend();
        prm->base.position = i_this->home.pos;
        prm->base.angle = i_this->home.angle;
        prm->base.parameters = fopAcM_GetParam(i_this);
        prm->room_no = fopAcM_GetRoomNo(i_this);
        fpcSCtRq_Request(fpcLy_CurrentLayer(), fpcNm_MT_e, NULL, NULL, prm);
    }

    return TRUE;
}

/* 00007E18-00008400       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* pActor) {
    /* Nonmatching */
    static s32 bmd_data[] = {dRes_INDEX_MT_BDL_MG_HEAD_e, dRes_INDEX_MT_BDL_MG_BODY_e, dRes_INDEX_MT_BDL_MG_BODY_e, dRes_INDEX_MT_BDL_MG_BODY_e, dRes_INDEX_MT_BDL_MG_BODY_e, dRes_INDEX_MT_BDL_MG_BODY_e, dRes_INDEX_MT_BDL_MG_BODY_e, dRes_INDEX_MT_BDL_MG_TAIL_e};
    static f32 scale_data[] = {1.0f, 1.0f, 1.0f, 0.975f, 0.925f, 0.825f, 0.75f, 0.525f};
    static s32 br_bmd[] = {dRes_INDEX_MT_BDL_KBA_e, dRes_INDEX_MT_BDL_KBB_e, dRes_INDEX_MT_BDL_KBC_e};
    mt_class* actor = (mt_class*)pActor;

    for (int i = 0; i < 8; i++) {
        actor->mpMorf[i] = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("Mt", bmd_data[i]), NULL, NULL, NULL,
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x00080000, 0x37440402);
        if (actor->mpMorf[i] == NULL || actor->mpMorf[i]->getModel() == NULL) {
            return FALSE;
        }
        J3DModelData* modelData = actor->mpMorf[i]->getModel()->getModelData();

        actor->btk[i] = new mDoExt_btkAnm();
        JUT_ASSERT(0x11c0, actor->btk[i]);
        if (!actor->btk[i]->init(modelData,
                                 (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Mt", btk_data[i]),
                                 1, 2, 1.0f, 0, -1, 0, 0)) {
            return FALSE;
        }

        actor->brk[i] = new mDoExt_brkAnm();
        JUT_ASSERT(0x11cd, actor->brk[i]);
        if (!actor->brk[i]->init(modelData,
                                 (J3DAnmTevRegKey*)dComIfG_getObjectRes("Mt", brk_data[i]),
                                 1, 2, 1.0f, 0, -1, 0, 0)) {
            return FALSE;
        }

        if (i == 0) {
            anm_init(actor, 0xa, 20.0f, 2, 1.0f, 0);

            J3DAnmTexPattern* texPattern = NULL;
            for (int j = 0; j < 2; j++) {
                texPattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Mt", mt_tex_anm_idx[j]);
                texPattern->searchUpdateMaterialID(modelData);
            }
            u16 count = texPattern->getUpdateMaterialNum();
            actor->m340 = new J3DTexNoAnm[count];
            for (u16 j = 0; j < count; j++) {
                actor->m340[j].setAnmIndex(j);
            }
            tex_anm_set(actor, 0);
        }

        actor->mpMorf[i]->getModel()->setUserArea((u32)actor);

        for (u16 j = 0; j < modelData->getJointNum(); j++) {
            if (i == 0) {
                if (j >= 2 && j <= 5) {
                    modelData->getJointNodePointer(j)->setCallBack(nodeCallBack_head);
                }
            } else if (i == 7) {
                if (j >= 2 && j <= 5) {
                    modelData->getJointNodePointer(j)->setCallBack(nodeCallBack_tail);
                }
            } else {
                if (j >= 2 && j <= 5) {
                    modelData->getJointNodePointer(j)->setCallBack(nodeCallBack_body);
                }
            }
        }

        actor->m600[i] = scale_data[i];
    }

    for (int i = 0; i < 3; i++) {
        J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Mt", br_bmd[i]);
        JUT_ASSERT(0x127a, modelData != 0);
        actor->br_modelL[i] = mDoExt_J3DModel__create(modelData, 0, 0x110203);
        JUT_ASSERT(0x127d, actor->br_modelL[i] != 0);
        actor->br_modelR[i] = mDoExt_J3DModel__create(modelData, 0, 0x110203);
        JUT_ASSERT(0x127f, actor->br_modelR[i] != 0);
        actor->br_modelL[i]->setBaseScale(actor->scale);
        actor->br_modelR[i]->setBaseScale(actor->scale);
    }
    return TRUE;
}

/* 000084AC-000088A8       .text daMt_Create__FP10fopAc_ac_c */
static cPhs_State daMt_Create(fopAc_ac_c* pActor) {
    static dCcD_SrcSph sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK2,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ dCcG_SE_METAL,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 30.0f,
        }},
    };
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

    mt_class* i_this = (mt_class*)pActor;
    fopAcM_ct(i_this, mt_class);

    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "Mt");
    if (res == cPhs_COMPLEATE_e) {
        i_this->gbaName = 5;

        i_this->m2B4 = fopAcM_GetParam(i_this) & 0xFF;
        if (i_this->m2B4 == 0xFF) {
            i_this->m2B4 = 0;
        }
        i_this->m2B5 = (fopAcM_GetParam(i_this) >> 8) & 0x7F;
        i_this->m2B6 = (fopAcM_GetParam(i_this) >> 15) & 1;
        i_this->m2B7 = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
        i_this->m2B8 = (fopAcM_GetParam(i_this) >> 24) & 0xFF;

        if (i_this->m2B6 == 0) {
            i_this->m2B9 = i_this->current.angle.z;
            if (i_this->m2B9 != 0 && dComIfGs_isSwitch(i_this->m2B9, fopAcM_GetRoomNo(i_this))) {
                return cPhs_ERROR_e;
            }
        } else {
            i_this->m2BA = i_this->current.angle.z;
        }
        i_this->current.angle.z = 0;

        cDT_NamePTbl* nameTbl = (cDT_NamePTbl*)((u8*)&g_dComIfG_gameInfo + 0x50AC);
        i_this->itemTableIdx = nameTbl->GetIndex("magtail", 0);

        if (!fopAcM_entrySolidHeap(i_this, CallbackCreateHeap, 0x1BFC8)) {
            return cPhs_ERROR_e;
        }

        i_this->mBtHeight = 162.5f;
        i_this->mBtBodyR = 200.0f;

        if (i_this->m2B4 >= 0xA) {
            switch (i_this->m2B5) {
            case 0:
                break;
            case 1:
                i_this->m488[0] = 0x3E8;
                break;
            case 2:
                i_this->m488[0] = 0x1F4;
                break;
            case 3:
                i_this->m488[0] = 0xFA;
                break;
            case 11:
                i_this->m488[0] = -0x3E8;
                break;
            case 12:
                i_this->m488[0] = -0x1F4;
                break;
            case 13:
                i_this->m488[0] = -0xFA;
                break;
            }
        } else if (i_this->m2B7 != 0xFF) {
            i_this->m2C0 = (u32)dPath_GetRoomPath(i_this->m2B7, fopAcM_GetRoomNo(i_this));
            if (i_this->m2C0 == 0) {
                return cPhs_ERROR_e;
            }
            i_this->m2BC = i_this->m2B7 + 1;
            i_this->m2BE = 1;
            dPnt* point = ((dPath*)i_this->m2C0)->m_points;
            i_this->m47C = point->m_position.x;
            i_this->m480 = point->m_position.y;
            i_this->m484 = point->m_position.z;
        }

        if (i_this->m2B8 != 0xFF) {
            i_this->m2BB = i_this->m2B8 + 1;
        }

        i_this->cullMtx = i_this->mpMorf[1]->getModel()->getBaseTRMtx();
        fopAcM_SetMin(i_this, -200.0f, -200.0f, -200.0f);
        fopAcM_SetMax(i_this, 200.0f, 200.0f, 200.0f);
        i_this->gravity = -3.0f;
        i_this->m46A = (s16)cM_rndF(32768.0f);

        for (int i = 0; i < 64; i++) {
            i_this->m6F4[i] = i_this->current.pos;
            i_this->m9F4[i] = i_this->current.angle;
        }

        i_this->mAcch.Set(&i_this->current.pos, &i_this->old.pos, i_this, 1, &i_this->mC08, &i_this->speed);
        i_this->mC08.SetWall(50.0f, 19.0f + REG0_F(0));
        i_this->mStts.Init(0xFA, 2, i_this);

        for (int i = 0; i < 8; i++) {
            i_this->mE48[i].Set(sph_src);
            i_this->mE48[i].SetStts(&i_this->mStts);
        }
        i_this->mE48[0].SetAtAtp(2);

        i_this->m17A8.Set(eye_sph_src);
        i_this->m17A8.SetStts(&i_this->mStts);
        i_this->m18F0 = 1.0f;
        i_this->m18FB = 2;
        i_this->max_health = 8;
        i_this->health = 8;
        i_this->mEnemyIce.mpActor = i_this;
        i_this->mEnemyIce.mDeathSwitch = i_this->m2B9;
        daMt_Execute(i_this);
    }
    return res;
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
