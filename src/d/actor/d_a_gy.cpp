/**
 * d_a_gy.cpp
 * Enemy - Gyorg
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_gy.h"
#include "d/actor/d_a_gy_ctrl.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_sea.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_func.h"
#include "d/d_lib.h"
#include "d/d_particle.h"
#include "d/d_s_play.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_printf.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_camera.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "d/actor/d_a_player.h"
#include "dolphin/mtx/quat.h"
#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "JSystem/J3DGraphBase/J3DSys.h"

static dCcD_SrcSph l_sph_head_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};


static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};


static dCcD_SrcCps l_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};

#include "d/d_jnt_hit.h"

static Vec atama_cyl_offset[] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 150.0f, 0.0f},
};
static Vec ago_cyl_offset[] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 90.0f, 0.0f},
};
static Vec body1_cyl_offset[] = {
    {-40.0f, -20.0f, 0.0f},
    {40.0f, -20.0f, 0.0f},
};
static Vec body2_cyl_offset[] = {
    {-40.0f, -10.0f, 0.0f},
    {40.0f, -10.0f, 0.0f},
};
static Vec sebire1_cyl_offset[] = {
    {-40.0f, 60.0f, 0.0f},
    {150.0f, -100.0f, 0.0f},
};

static __jnt_hit_data_c search_data[] = {
    {0, 2, 30.0f, atama_cyl_offset},
    {0, 3, 30.0f, ago_cyl_offset},
    {0, 4, 60.0f, body1_cyl_offset},
    {0, 5, 20.0f, sebire1_cyl_offset},
    {0, 6, 60.0f, body1_cyl_offset},
    {0, 7, 50.0f, body1_cyl_offset},
    {0, 9, 30.0f, body1_cyl_offset},
    {0, 10, 30.0f, body2_cyl_offset},
};

static daGy_HIO_c l_HIO;

const u32 daGy_c::m_heapsize = 0x3FA0;
const char daGy_c::m_arc_name[] = "Gy";

/* 000000EC-000003CC       .text __ct__10daGy_HIO_cFv */
daGy_HIO_c::daGy_HIO_c() {
    m0C = 0xC8;
    m04 = 1.0f;
    m08 = 0.9f;
    m10 = 200.0f;
    m14 = 300.0f;
    m18 = 2.0f;
    m1C = 2.0f;
    m24 = 15.0f;
    m20 = 0.0f;
    m28 = -80.0f;
    m2C = -50.0f;
    m30 = -150.0f;
    m34 = -40.0f;
    m38 = -100.0f;
    m3C = -350.0f;
    m48 = 10.0f;
    m4C = 20.0f;
    m50 = 30.0f;
    m54 = 40.0f;
    m58 = 15.0f;
    m5C = 5.0f;
    m60 = 40.0f;
    m64 = 20.0f;
    m68 = 55.0f;
    m6C = 10.0f;
    m70 = 20.0f;
    m198 = 1;
    m40 = 60.0f;
    m44 = 2500.0f;
    m74 = 70.0f;
    m78 = 70.0f;
    m7C = 80.0f;
    m80 = 70.0f;
    m84 = 70.0f;
    m88 = 110.0f;
    m8C = 100.0f;
    m90 = 1.0f;
    m9C = 5000.0f;
    mA4 = 180.0f;
    mA8 = -400.0f;
    m94 = 0;
    m95 = 0;
    m96 = 0;
    m97 = 0;
    m98 = 0;
    m99 = 0;
    mA0 = -500.0f;
    mAC = -80.0f;
    mB4 = -25.0f;
    mB0 = 20.0f;
    mB8 = 0.0f;
    mBC = 0.0f;
    mC0 = 0.0f;
    mC4 = 8.0f;
    m178 = 0.5f;
    mC8 = 30.0f;
    mD4 = 80.0f;
    mD8 = 0.0f;
    mDC = 0.0f;
    mE0 = 0.0f;
    mE4 = 0.0f;
    mE8 = 0.0f;
    mEC = 0.0f;
    mF0 = 0.0f;
    mF4 = 120.0f;
    mF8 = 0.0f;
    mFC = 0.0f;
    m100 = 300.0f;
    mCC = 2.0f;
    mD0 = 20.0f;
    m104 = -40.0f;
    m108 = 25.0f;
    m10C = 0x78;
    m10E = 0x3C;
    m110 = 0x78;
    m112 = 0xB4;
    m114 = 0x168;
    m116 = 0x5A;
    m118 = 0xF0;
    m188 = 0.2f;
    m12C = 10.0f;
    m144 = 400.0f;
    m148 = 350.0f;
    m150 = 60.0f;
    m154 = 60.0f;
    m158 = 40.0f;
    for (s32 i = 2; i < 0xB; i++) {
        m11A[i] = 0;
    }
    m130 = 0x64;
    m132 = 0x12C;
    m134 = 45.0f;
    m138 = 45.0f;
    m13C = 30.0f;
    m15C = 45.0f;
    m160 = 10.0f;
    m140 = 0x1500;
    m142 = 0x800;
    m164 = 0x5A;
    m168 = -1000.0f;
    m16C = -100.0f;
    m170 = 50.0f;
    m174 = 0.1f;
    m17C = 0.1f;
    m184 = 4000.0f;
    m180 = 0x2000;
    m18C = 3000.0f;
    m190 = 200.0f;
    m194 = 3000.0f;
}

/* 00000450-0000049C       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daGy_c* i_this = reinterpret_cast<daGy_c*>(model->getUserArea());
        if (i_this) {
            i_this->_nodeControl(node, model);
        }
    }
    return TRUE;
}

/* 0000049C-00000888       .text _nodeControl__6daGy_cFP7J3DNodeP8J3DModel */
/* Nonmatching */
void daGy_c::_nodeControl(J3DNode* node, J3DModel* model) {
    s32 jntNo = ((J3DJoint*)node)->getJntNo();
    Mtx sp94;
    cXyz sp88;
    cXyz sp7C;
    cXyz sp70;
    cXyz sp64;
    Quaternion sp54;
    cXyz sp48;
    cXyz sp3C;
    cXyz sp24;
    cXyz sp18;
    Vec spC;
    f32 sp8;

    if (jntNo == 2) {
        PSMTXCopy(model->getAnmMtx(jntNo), mDoMtx_stack_c::now);
        sp88.set(0.0f, 0.0f, 0.0f);
        sp88.set(l_HIO.mD4, l_HIO.mD8, l_HIO.mDC);
        PSMTXMultVec(mDoMtx_stack_c::now, &sp88, &mD08);
    }

    PSMTXCopy(model->getAnmMtx(jntNo), sp94);
    sp7C.set(sp94[0][3], sp94[1][3], sp94[2][3]);
    sp94[0][3] = 0.0f;
    sp94[1][3] = 0.0f;
    sp94[2][3] = 0.0f;
    mDoMtx_stack_c::transS(sp7C);

    if (jntNo == 2) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        const cXyz& sp30 = current.pos - player->current.pos;
        spC.x = sp30.x;
        spC.y = 0.0f;
        spC.z = sp30.z;
        f32 f1 = PSVECSquareMag(&spC);
        f32 f31 = std::sqrtf(f1);
        s16 angle = fopAcM_searchActorAngleY(this, player);
        if (cLib_distanceAngleS(shape_angle.y, angle) < l_HIO.m180 && f31 < l_HIO.m184 && (s8)mD15 != 8 && (s8)mD15 != 9 && (s8)mD15 != 6 && (s8)mD15 != 0xB && (s8)mD15 != 3) {
            mCEC = player->current.pos;
            if (m2B0 == 2) {
                mCEC.y = daSea_calcWave(mCEC.x, mCEC.z) + l_HIO.mA8;
            }
            if (m2B0 == 3 && m928 == 1) {
                mCEC.y += l_HIO.mA4;
            }
            sp70 = mCEC - mD08;
            sp64 = mD08 - mD08;
            daObj::quat_rotVec(&sp54, sp64, sp70);
            C_QUATSlerp(&mCF8, &sp54, &mCF8, l_HIO.m188);
        } else {
            C_QUATSlerp(&mCF8, &ZeroQuat, &mCF8, l_HIO.m188);
        }
        mDoMtx_stack_c::quatM(&mCF8);
    }

    mDoMtx_stack_c::concat(sp94);

    if (jntNo == 2) {
        sp48.set(0.0f, 0.0f, 0.0f);
        sp48.set(l_HIO.mD4, l_HIO.mD8, l_HIO.mDC);
        PSMTXMultVec(mDoMtx_stack_c::now, &sp48, &mD08);
    }

    if (jntNo == 5) {
        sp3C.set(100.0f, -100.0f, 0.0f);
        PSMTXMultVec(mDoMtx_stack_c::now, &sp3C, &m89C);
    }

    PSMTXCopy(mDoMtx_stack_c::now, J3DSys::mCurrentMtx);
    PSMTXCopy(mDoMtx_stack_c::now, model->getAnmMtx(jntNo));
}

/* 00000888-000008A8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daGy_c*>(i_this)->_createHeap();
}

/* 000008A8-00000AAC       .text _createHeap__6daGy_cFv */
BOOL daGy_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, 0xF);
    JUT_ASSERT(0x377, modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        modelData, NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes(m_arc_name, 0xB),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0,
        0x11020203
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    mpMorf->getModel()->setUserArea((u32)this);
    if (m2D8.create(mpMorf->getModel()) == 0) {
        return FALSE;
    }

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        switch (i) {
        case 2:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeControl_CB);
            break;
        }
    }

    mCE4 = JntHit_create(mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (mCE4 != NULL) {
        jntHit = mCE4;
    } else {
        return FALSE;
    }
    return TRUE;
}

/* 00000AAC-00000C30       .text setMtx__6daGy_cFv */
void daGy_c::setMtx() {
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);

    cXyz sp14(0.0f, 0.0f, 500.0f);
    mDoMtx_stack_c::multVec(&sp14, &mE84);

    if (l_HIO.m94 != 0) {
        mDoMtx_stack_c::transM(l_HIO.mB8, l_HIO.mBC, l_HIO.mC0);
    }
    mDoMtx_stack_c::transM(0.0f, m4E4, 0.0f);
    PSMTXCopy(mDoMtx_stack_c::now, model->getBaseTRMtx());

    cXyz sp8;
    if (m4E4 <= 10.0f + l_HIO.mAC) {
        sp8.set(l_HIO.mEC, l_HIO.mF0, l_HIO.mF4);
    } else if (m4E4 > 10.0f + l_HIO.mAC) {
        sp8.set(l_HIO.mF8, l_HIO.mFC, l_HIO.m100);
    }
    mDoMtx_stack_c::transM(sp8);

    mDFC.x = mDoMtx_stack_c::now[0][3];
    mDFC.y = mDoMtx_stack_c::now[1][3];
    mDFC.z = mDoMtx_stack_c::now[2][3];
}

/* 00000C30-00000C7C       .text setAnm__6daGy_cFv */
void daGy_c::setAnm() {
    static const dLib_anm_idx_c a_anm_idx_tbl[] = {
        {0xB, -1},
        {0xC, -1},
        {0x6, -1},
        {0xA, -1},
        {0x7, -1},
        {0x8, -1},
        {0x9, -1},
        {0x4, -1},
        {0x5, -1},
    };

    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {0, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0, -1, 0, 8.0f, 2.0f, J3DFrameCtrl::EMode_LOOP},
        {1, -1, 0, 8.0f, 2.0f, J3DFrameCtrl::EMode_LOOP},
        {0, -1, 0, 8.0f, 2.5f, J3DFrameCtrl::EMode_LOOP},
        {2, 1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {3, -1, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {4, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {4, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {6, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {7, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {8, -1, 0, 2.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
    };

    dLib_setAnm(m_arc_name, mpMorf, (s8*)&mD14, (s8*)&mD15, (s8*)&mD16, a_anm_idx_tbl, a_anm_prm_tbl, false);
}

/* 00000C7C-00000E74       .text setAtCollision__6daGy_cFv */
void daGy_c::setAtCollision() {
    m50C.SetR(l_HIO.m88 * l_HIO.m90);
    m50C.SetC(mD08);
    if (m2B0 == 3) {
        s32 frame = (s32)mpMorf->getFrame();
        if (mD15 == 0xB && frame < 0x12) {
            m50C.OnAtSetBit();
            m50C.OnAtHitBit();
            m50C.SetAtAtp(2);
            m50C.SetAtSpl(dCcG_At_Spl_UNK1);
            m50C.SetAtSe(6);
            m50C.OffCoSetBit();
        } else {
            m50C.OffAtSetBit();
            m50C.OffAtHitBit();
            m50C.SetAtAtp(0);
            m50C.OnCoSetBit();
        }
    } else if (m2B0 == 2 || m2B0 == 5) {
        if (mpCtrl->m320 == 1) {
            if (m50C.ChkCoHit()) {
                if (fopAcM_GetName(m50C.GetCoHitAc()) == fpcNm_SHIP_e) {
                    m50C.OnAtSetBit();
                    m50C.OnAtHitBit();
                    m50C.SetAtAtp(2);
                    m50C.SetAtSpl(dCcG_At_Spl_UNK1);
                    m50C.SetAtSe(6);
                }
            } else {
                m50C.OffAtSetBit();
                m50C.OffAtHitBit();
                m50C.SetAtAtp(0);
            }
            m50C.OnCoSetBit();
        }
    } else {
        m50C.OffAtSetBit();
        m50C.OffAtHitBit();
        m50C.SetAtAtp(0);
        m50C.OnCoSetBit();
        if (m50C.ChkCoHit() && m2B0 != 9 && m2B0 != 8) {
            modeDiveInit();
        }
    }
    dComIfG_Ccsp()->Set(&m50C);
}

/* 00000E74-00000F3C       .text setCollision__6daGy_cFv */
void daGy_c::setCollision() {
    m638.SetR(140.0f * l_HIO.m90);
    m638.SetC(current.pos);
    dComIfG_Ccsp()->Set(&m638);
    m764.SetStartEnd(m89C, m89C);
    m764.SetR(l_HIO.m8C * l_HIO.m90);
    dComIfG_Ccsp()->Set(&m764);
}

/* 00000F3C-00000FC4       .text setAimSpeedF__6daGy_cFv */
void daGy_c::setAimSpeedF() {
    if (mpCtrl->m320 == 0) {
        m4F0 = l_HIO.m48;
        if (mpMorf->getFrame() > l_HIO.mCC && mpMorf->getFrame() < l_HIO.mD0) {
            m4F0 = l_HIO.m4C;
        }
    } else {
        m4F0 = l_HIO.m50;
        if (mpMorf->getFrame() > l_HIO.mCC && mpMorf->getFrame() < l_HIO.mD0) {
            m4F0 = l_HIO.m54;
        }
    }
}

/* 00000FC4-00000FDC       .text modeDiveInit__6daGy_cFv */
void daGy_c::modeDiveInit() {
    m2B0 = 0;
    m508 = 0.0f;
}

/* 00000FDC-000012DC       .text modeDive__6daGy_cFv */
void daGy_c::modeDive() {
    /* Nonmatching */
    if (mD15 != 5) {
        mD15 = 1;
        daGy_Ctrl_c* ctrl = mpCtrl;
        if (ctrl->m324 == 3 || mE80 != 0) {
            cLib_addCalcAngleS2(&current.angle.y, cLib_targetAngleY(&current.pos, &m2BC), 8, 0x400);
            m4F0 = 0.0f;
            m4E8 = 2.0f * l_HIO.mA0;
            m4EC = l_HIO.mC8;
            actor_status &= ~0x20;
            attention_info.flags &= ~0x4;
            return;
        }
        actor_status |= 0x20;
        attention_info.flags |= 0x4;
        m4E8 = l_HIO.mA0;
        m4EC = l_HIO.mC8;
        f32 player_dist = fopAcM_searchActorDistance(this, dComIfGp_getPlayer(0));
        if (ctrl->m312[m2AC] == 1 && m4E4 < 10.0f + l_HIO.mA0 && player_dist > l_HIO.m148) {
            modeCircleInit();
            return;
        }
        fopAc_ac_c* cb1_player = dComIfGp_getShipActor();
        Vec spC;
        const cXyz& sp3C = current.pos - m2BC;
        spC.x = sp3C.x;
        spC.y = 0.0f;
        spC.z = sp3C.z;
        f32 dist = std::sqrtf(PSVECSquareMag(&spC));
        if (cb1_player != NULL) {
            if (dist > l_HIO.m144 || cb1_player->speedF > l_HIO.m6C) {
                setAimSpeedF();
                cLib_addCalcAngleS2(&current.angle.y, cLib_targetAngleY(&current.pos, &m2BC), 8, 0x400);
                m508 = 0.0f;
            } else {
                m4F0 = 0.0f;
                cXyz sp48 = m2BC - current.pos;
                cLib_addCalc2(&m508, 1.0f, 0.01f, 0.05f);
                current.pos = current.pos + sp48 * m508;
                cLib_addCalcAngleS2(&current.angle.y, (s16)(ctrl->m308[m2AC] + 0x8000), 4, 0x400);
            }
        }
    }
}

/* 000012DC-0000141C       .text modeCircleInit__6daGy_cFv */
void daGy_c::modeCircleInit() {
    m2B0 = 1;
    s32 type = mpCtrl->m320;
    if(type == 0) {
        m914 = (s32)((f32)l_HIO.m116 + cM_rndF((f32)(l_HIO.m118 - l_HIO.m116)));
    } else if(type == 1) {
        m914 = (s32)((f32)l_HIO.m112 + cM_rndF((f32)(l_HIO.m114 - l_HIO.m112)));
    }
    m508 = 0.0f;
}

/* 0000141C-000016E4       .text modeCircle__6daGy_cFv */
void daGy_c::modeCircle() {
    /* Nonmatching */
    if (mD15 != 5) {
        mD15 = 1;
        m4E8 = l_HIO.mAC;
        m4EC = l_HIO.mC4;
        daGy_Ctrl_c* ctrl = mpCtrl;
        if (ctrl->m312[m2AC] == 0) {
            modeDiveInit();
            return;
        }
        fopAc_ac_c* cb1_player = dComIfGp_getShipActor();
        Vec spC;
        const cXyz& sp3C = current.pos - m2BC;
        spC.x = sp3C.x;
        spC.y = 0.0f;
        spC.z = sp3C.z;
        f32 dist = std::sqrtf(PSVECSquareMag(&spC));
        if (cb1_player != NULL) {
            if (dist > l_HIO.m144 || cb1_player->speedF > l_HIO.m6C) {
                setAimSpeedF();
                if (fopAcM_searchActorDistance(this, dComIfGp_getPlayer(0)) < l_HIO.m148) {
                    modeDiveInit();
                    return;
                }
                if (cb1_player->speedF > l_HIO.m70) {
                    modeWithCircleInit();
                    return;
                }
                cLib_addCalcAngleS2(&current.angle.y, cLib_targetAngleY(&current.pos, &m2BC), 8, 0x400);
                m508 = 0.0f;
            } else {
                m4F0 = 0.0f;
                cXyz sp48 = m2BC - current.pos;
                cLib_addCalc2(&m508, 1.0f, 0.01f, 0.05f);
                current.pos = current.pos + sp48 * m508;
                cLib_addCalcAngleS2(&current.angle.y, (s16)(ctrl->m308[m2AC] + 0x8000), 4, 0x400);
                if (cLib_calcTimer(&m914) == 0) {
                    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK1000000_e) == 0) {
                        if (ctrl->m320 == 0) {
                            modeAttackPlayerInit();
                        } else if (ctrl->m320 == 1) {
                            modeAttackInit();
                        }
                    }
                }
            }
        }
    }
}

/* 000016E4-00001788       .text modeWithCircleInit__6daGy_cFv */
void daGy_c::modeWithCircleInit() {
    m2B0 = 6;
    m4F8 = (s32)cM_rndF((f32)l_HIO.m132);
    if(m4F8 <= l_HIO.m130) {
        m4F8 = l_HIO.m130;
    }
    m914 = l_HIO.m110 + m4F8;
}

/* 00001788-000019AC       .text modeWithCircle__6daGy_cFv */
void daGy_c::modeWithCircle() {
    if (mD15 != 5) {
        m4E8 = l_HIO.mAC;
        m4EC = l_HIO.mC4;
        daGy_Ctrl_c* ctrl = mpCtrl;
        if (ctrl->m312[m2AC] == 0) {
            modeDiveInit();
            return;
        }
        fopAc_ac_c* cb1_player = dComIfGp_getShipActor();
        if (cb1_player != NULL) {
            if (cb1_player->speedF < l_HIO.m50) {
                modeCircleInit();
            }
            cLib_addCalcAngleS2(&current.angle.y, cb1_player->shape_angle.y, 8, 0x400);
            int dist_angle = cLib_distanceAngleS(cb1_player->shape_angle.y,
                                                 fopAcM_searchActorAngleY(cb1_player, this));
            f32 player_dist = fopAcM_searchActorDistance(this, dComIfGp_getPlayer(0));
            if (dist_angle < l_HIO.m142 && player_dist > l_HIO.m9C) {
                m4F0 = cb1_player->speedF - 5.0f;
            } else {
                m4F0 = cb1_player->speedF + l_HIO.m40;
            }
            if (dist_angle < l_HIO.m140 && dist_angle > l_HIO.m142 && player_dist > l_HIO.m9C) {
                speed.y = l_HIO.m138;
                JAIZelBasic::zel_basic->seStart(JA_SE_CM_GY_JUMP_L, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
                mD15 = 5;
                cXyz sp18(2.0f + g_regHIO.mChild[10].mFloatRegs[0],
                          2.0f + g_regHIO.mChild[10].mFloatRegs[0] + g_regHIO.mChild[10].mFloatRegs[1],
                          2.0f + g_regHIO.mChild[10].mFloatRegs[0]);
                dComIfGp_particle_set(0x3C, &current.pos, NULL, &sp18, 0xFF, NULL, -1, NULL, NULL, NULL);
                modeWithAttackInit();
            }
        }
    }
}

/* 000019AC-00001A14       .text modeAttackInit__6daGy_cFv */
void daGy_c::modeAttackInit() {
    m2B0 = 2;
    mD15 = 3;
    m8F8 = dComIfGp_getPlayer(0)->current.pos;
    m914 = l_HIO.m10C;
    m904 = m2BC;
    m928 = 0;
}

/* 00001A14-00001A74       .text modeWithAttackInit__6daGy_cFv */
void daGy_c::modeWithAttackInit() {
    m2B0 = 5;
    m8F8 = dComIfGp_getPlayer(0)->current.pos;
    m914 = l_HIO.m10C;
    m904 = m2BC;
    m928 = 0;
}

/* 00001A74-00001D60       .text modeWithAttack__6daGy_cFv */
void daGy_c::modeWithAttack() {
    /* Nonmatching */
    if (mD15 != 5) {
        mD15 = 3;
    }
    if (mpCtrl->m320 == 0) {
        modeCircleInit();
        return;
    }
    s16 target_angle = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos);
    f32 player_dist = fopAcM_searchActorDistance(this, dComIfGp_getPlayer(0));
    switch (m928) {
    case 0:
        m4E8 = l_HIO.mAC;
        m4EC = l_HIO.mC4;
        cLib_addCalcAngleS2(&current.angle.y, target_angle, 8, 0x400);        m4F0 = l_HIO.m68;
        if (player_dist < l_HIO.m44) {
            m928++;
            m914 = l_HIO.m10E;
        }
        if (cLib_calcTimer(&m914) == 0) {
            if (l_HIO.m99 == 0) {
                modeWithCircleInit();
                return;
            }
            m928++;
        }
        break;
    case 1:
        m4E8 = l_HIO.mB0;
        m4EC = l_HIO.mC4;
        m4F0 = l_HIO.m68;
        if (m50C.ChkCoHit()) {
            fopAc_ac_c* hit_ac = m50C.GetCoHitAc();
            if (fopAcM_GetName(hit_ac) == fpcNm_SHIP_e) {
                dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                Vec* eye = &eyePos;
                JAIZelBasic::zel_basic->seStart(JA_SE_CM_GY_SHIP_CRASH, eye, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
                mDoAud_monsSeStart(JA_SE_CV_GY_ATTACK, eye, fopAcM_GetID(this), 0, dComIfGp_getReverb(current.roomNo));
                modeAttackBackInit();
                return;
            }
        }
        if (cLib_calcTimer(&m914) == 0) {
            if (l_HIO.m99 == 0) {
                modeWithCircleInit();
                return;
            }
            m928++;
        }
        break;
    case 2:
        m4E8 = l_HIO.mA0;
        m4EC = l_HIO.mC4;
        if (std::fabsf(m4E4 - m4E8) < 10.0f) {
            fopAcM_delete(this);
        }
        break;
    }
}

/* 00001D60-00001F20       .text modeAttack__6daGy_cFv */
void daGy_c::modeAttack() {
    /* Nonmatching */
    if (mpCtrl->m320 == 0) {
        modeCircleInit();
        return;
    }
    m4E8 = l_HIO.mB0;
    m4EC = l_HIO.mC4;
    if (cLib_calcTimer(&m914) == 0) {
        modeCircleInit();
    }
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 player_dist = fopAcM_searchActorDistance(this, player);
    if (player_dist < l_HIO.m148) {
        m4F0 = 0.0f;
    } else {
        m4F0 = l_HIO.m64;
        cLib_addCalcAngleS2(&current.angle.y, cLib_targetAngleY(&current.pos, &player->current.pos), 8, 0x400);
    }
    if (m50C.ChkCoHit()) {
        fopAc_ac_c* hit_ac = m50C.GetCoHitAc();
        if (fopAcM_GetName(hit_ac) == fpcNm_SHIP_e) {
            dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            JAIZelBasic::zel_basic->seStart(JA_SE_CM_GY_SHIP_CRASH, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            mDoAud_monsSeStart(JA_SE_CV_GY_ATTACK, &eyePos, fopAcM_GetID(this), 0, dComIfGp_getReverb(current.roomNo));
            modeAttackBackInit();
        }
    }
}

/* 00001F20-00001F40       .text modeAttackPlayerInit__6daGy_cFv */
void daGy_c::modeAttackPlayerInit() {
    m2B0 = 3;
    mD15 = 2;
    m928 = 0;
    m924 = 0;
}

/* 00001F40-000022F8       .text modeAttackPlayer__6daGy_cFv */
void daGy_c::modeAttackPlayer() {
    /* Nonmatching */
}

/* 000022F8-00002400       .text modeAttackBackInit__6daGy_cFv */
void daGy_c::modeAttackBackInit() {
    m2B0 = 4;
    mD15 = 4;
    speedF = l_HIO.m104;
    speed.y = l_HIO.m108;
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_GY_JUMP_S, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);

    cXyz sp18(2.0f + g_regHIO.mChild[10].mFloatRegs[0],
              2.0f + g_regHIO.mChild[10].mFloatRegs[0] + g_regHIO.mChild[10].mFloatRegs[1],
              2.0f + g_regHIO.mChild[10].mFloatRegs[0]);
    dComIfGp_particle_set(0x3C, &current.pos, NULL, &sp18, 0xFF, NULL, -1, NULL, NULL, NULL);
}

/* 00002400-00002560       .text modeAttackBack__6daGy_cFv */
void daGy_c::modeAttackBack() {
    m4E8 = l_HIO.mA0;
    m4F0 = 0.0f;
    cLib_addCalcAngleS2(&m8F4, 0, 4, 0x800);

    cXyz sp18 = current.pos - m904;
    cXyz spC(sp18.x, 0.0f, sp18.z);
    f32 f1 = PSVECSquareMag(&spC);
    if (f1 > 0.0f) {
        double guess = __frsqrte(f1);
        guess = 0.5 * guess * (3.0 - guess * guess * f1);
        guess = 0.5 * guess * (3.0 - guess * guess * f1);
        guess = 0.5 * guess * (3.0 - guess * guess * f1);
        f1 = (f32)(f1 * guess);
    }

    if (f1 > l_HIO.m144) {
        setAimSpeedF();
        if (mD15 == 1) {
            modeWithCircleInit();
        }
        cLib_addCalcAngleS2(&current.angle.y, cLib_targetAngleY(&current.pos, &m904), 8, 0x400);
        return;
    }
    if (mD15 == 1) {
        modeCircleInit();
    }
}

/* 00002560-000025F0       .text modeDamageInit__6daGy_cFv */
void daGy_c::modeDamageInit() {
    m2B0 = 7;
    mD15 = 6;
    speed.y = 30.0f;
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_GY_JUMP_S, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 000025F0-00002754       .text modeDamage__6daGy_cFv */
void daGy_c::modeDamage() {
    m4F0 = 0.0f;
    f32 f2 = m920;
    if (f2 > 0.01f) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        f32 negF2 = -f2;
        cXyz vec(0.0f, 0.0f, negF2);
        cXyz out(0.0f, 0.0f, 0.0f);
        mDoMtx_YrotS(mDoMtx_stack_c::now, fopAcM_searchActorAngleY(this, player));
        PSMTXMultVec(mDoMtx_stack_c::now, &vec, &out);
        current.pos.x += out.x;
        current.pos.y += out.y;
        current.pos.z += out.z;
        cLib_addCalc0(&m920, 1.0f, 2.0f);
    }

    if (mD15 == 6) {
        bool flag = mpMorf->isStop();
        if (flag) {
            mD15 = 1;
            switch ((s8)mD16[0]) {
            case 6:
                modeWithCircleInit();
                break;
            case 0:
                modeDiveInit();
                break;
            default:
                modeCircleInit();
                break;
            }
        }
    }
}

/* 00002754-000028B8       .text modeDeleteInit__6daGy_cFv */
void daGy_c::modeDeleteInit() {
    /* Nonmatching */
    actor_status &= ~0x20;
    attention_info.flags &= ~0x4;

    dSv_event_c* evt = &g_dComIfG_gameInfo.save.getEvent();
    u8 evnt = evt->getEventReg(dSv_event_flag_c::UNK_7EFF);
    u8 evnt2 = (evnt + 1 > 0xFF) ? 0xFF : evnt + 1;
    evt->setEventReg(dSv_event_flag_c::UNK_7EFF, evnt2);

    m2B0 = 8;
    mD15 = 8;
    m4F0 = 0.0f;
    speedF = 0.0f;
    speed.y = l_HIO.m15C;
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_GY_JUMP_L, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);

    cXyz sp18(2.0f + g_regHIO.mChild[10].mFloatRegs[0],
              2.0f + g_regHIO.mChild[10].mFloatRegs[0] + g_regHIO.mChild[10].mFloatRegs[1],
              2.0f + g_regHIO.mChild[10].mFloatRegs[0]);
    dComIfGp_particle_set(0x3C, &current.pos, NULL, &sp18, 0xFF, NULL, -1, NULL, NULL, NULL);
}

/* 000028B8-00002998       .text modeDelete__6daGy_cFv */
void daGy_c::modeDelete() {
    if (m500 != -1) {
        if (cLib_calcTimer(&m500) == 0) {
            m932 = 1;
        }
    } else if (m4FC != -1) {
        if (cLib_calcTimer(&m4FC) == 0) {
            m930 = l_HIO.m0C;
        }
    } else if (mD15 == 8) {
        if (mpMorf->isStop()) {
            fopAcM_createDisappear(this, &current.pos, 0xA, 0, 0xFF);
            fopAcM_delete(this);
        }
    }
}

/* 00002998-00002A70       .text modeDeleteBombInit__6daGy_cFv */
void daGy_c::modeDeleteBombInit() {
    actor_status &= ~0x20;
    attention_info.flags &= ~0x4;
    m2B0 = 9;
    mD15 = 7;
    m4F0 = 0.0f;
    speedF = 0.0f;
    m4E4 = 0.0f;
    speed.y = l_HIO.m15C;
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_GY_JUMP_L, &eyePos, 0, dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
    m4EC = 10.0f * l_HIO.mC8;
}

/* 00002A70-00002CBC       .text modeDeleteBomb__6daGy_cFv */
void daGy_c::modeDeleteBomb() {
    /* Nonmatching */
}

/* 00002CBC-00002E24       .text modeProcCall__6daGy_cFv */
void daGy_c::modeProcCall() {
    if (l_HIO.m95 != 0) {
        m2B0 = l_HIO.m9A;
    }
    static void (daGy_c::*mode_proc[])() = {
        &daGy_c::modeDive,
        &daGy_c::modeCircle,
        &daGy_c::modeAttack,
        &daGy_c::modeAttackPlayer,
        &daGy_c::modeAttackBack,
        &daGy_c::modeWithAttack,
        &daGy_c::modeWithCircle,
        &daGy_c::modeDamage,
        &daGy_c::modeDelete,
        &daGy_c::modeDeleteBomb,
    };
    (this->*mode_proc[m2B0])();
}

/* 00002E24-00003004       .text createWave__6daGy_cFv */
void daGy_c::createWave() {
    static s8 wave_l_initialized;
    static Vec wave_l_direction;
    if (!wave_l_initialized) {
        wave_l_direction.x = 0.5f;
        wave_l_direction.y = 1.0f;
        wave_l_direction.z = -0.3f;
        wave_l_initialized = 1;
    }
    static s8 wave_r_initialized;
    static Vec wave_r_direction;
    if (!wave_r_initialized) {
        wave_r_direction.x = -0.5f;
        wave_r_direction.y = 1.0f;
        wave_r_direction.z = -0.3f;
        wave_r_initialized = 1;
    }
    if (mD18.mpBaseEmitter == NULL) {
        dComIfGp_particle_set(0x37, &mDFC, &mE08, NULL, 0xFF, &mD18, -1, NULL, NULL, NULL);
        if (mD18.mpBaseEmitter != NULL) {
            mD18.mpBaseEmitter->mEmitterDir = wave_l_direction;
        }
    }
    if (mD7C.mpBaseEmitter == NULL) {
        dComIfGp_particle_set(0x37, &mDFC, &mE08, NULL, 0xFF, &mD7C, -1, NULL, NULL, NULL);
        if (mD7C.mpBaseEmitter != NULL) {
            mD7C.mpBaseEmitter->mEmitterDir = wave_r_direction;
        }
    }
    if (mDE0.getEmitter() == NULL) {
        dComIfGp_particle_set(0x35, &mDFC, &mE08, NULL, 0xFF, &mDE0, -1, NULL, NULL, NULL);
    }
}

/* 00003004-00003268       .text setWave__6daGy_cFv */
/* Nonmatching */
void daGy_c::setWave() {
    f32 var_f29 = l_HIO.m24;
    u8 d15 = mD15;
    f32 var_f30;
    f32 var_f31;
    if ((s8)d15 == 5 || (s8)d15 == 8 || (s8)d15 == 9 || (s8)d15 == 6) {
        var_f30 = 0.0f;
        var_f31 = 0.0f;
    } else {
        f32 one = 1.0f;
        var_f30 = l_HIO.m18 * one;
        var_f31 = l_HIO.m10;
    }
    switch (m2B0) {
    case 1:
        var_f29 = l_HIO.m24 * (0.6f + g_regHIO.mChild[12].mFloatRegs[13]);
        var_f30 *= 0.7f + g_regHIO.mChild[12].mFloatRegs[13];
        break;
    case 0:
        var_f30 = 0.0f;
        var_f31 = 0.0f;
        break;
    case 8:
        var_f30 = 0.0f;
        var_f31 = 0.0f;
        break;
    }
    if ((s8)d15 != 0xA) {
    } else {
        var_f30 = 0.0f;
        var_f31 = 0.0f;
    }
    mDFC.y = daSea_calcWave(mDFC.x, mDFC.z);
    mE08.y = current.angle.y;
    mD7C.setSpeed(var_f30);
    mD18.setSpeed(var_f30);
    mD7C.setMaxSpeed(var_f29);
    mD18.setMaxSpeed(var_f29);
    mD7C.setPitch(1.0f + l_HIO.m20);
    mD18.setPitch(1.0f - l_HIO.m20);
    mD7C.setAnchor(&cXyz(l_HIO.m28, l_HIO.m2C, l_HIO.m30),
                   &cXyz(l_HIO.m34, l_HIO.m38, l_HIO.m3C));
    mD18.setAnchor(&cXyz((f32)((f64)l_HIO.m28) * -1.0f, (f32)((f64)l_HIO.m2C), (f32)((f64)l_HIO.m30)),
                   &cXyz((f32)((f64)l_HIO.m34) * -1.0f, (f32)((f64)l_HIO.m38), (f32)((f64)l_HIO.m3C)));
    mD7C.setMaxDisSpeed(l_HIO.m1C);
    mD18.setMaxDisSpeed(l_HIO.m1C);
    cLib_addCalc2(&mE10, var_f31, 0.1f, 10.0f);
    mDE0.setSpeed(mE10);
    mDE0.setMaxSpeed(l_HIO.m14);
}

/* 00003268-000032E4       .text lineCheck__6daGy_cFP4cXyzP4cXyz */
void daGy_c::lineCheck(cXyz* param_0, cXyz* param_1) {
    mE14.Set(param_0, param_1, this);
    if (dComIfG_Bgsp()->LineCross(&mE14)) {
        *param_1 = mE14.GetCross();
        mE80 = 1;
    }
}

/* 000032E4-000038EC       .text checkTgHit__6daGy_cFv */
void daGy_c::checkTgHit() {
    m8A8.Move();

    cCcD_Obj* hitObj = m764.GetTgHitObj();
    cXyz hitPos = *m764.GetTgHitPosP();
    if (hitObj == NULL) {
        hitObj = m50C.GetTgHitObj();
        hitPos = *m50C.GetTgHitPosP();
    }
    if (hitObj == NULL) {
        hitObj = m638.GetTgHitObj();
        hitPos = *m638.GetTgHitPosP();
    }

    if (hitObj != NULL) {
        u8 flag = 0;
        u32 atType = hitObj->GetAtType();

        if (atType & AT_TYPE_BOMB) {
            health = 0;
            m920 = l_HIO.m14C;
            flag = 1;
        } else if (atType & AT_TYPE_NORMAL_ARROW) {
            JAIZelBasic::zel_basic->seStart(JA_SE_LK_MS_WEP_HIT, &eyePos, 0x20,
                                            dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            health -= 2;
            m920 = l_HIO.m150;
            flag = 1;
        } else if (atType & AT_TYPE_ICE_ARROW) {
            mCE8[0] = 9;
            JAIZelBasic::zel_basic->seStart(JA_SE_LK_MS_WEP_HIT, &eyePos, 0x20,
                                            dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            m4FC = 0xA;
            mDE0.remove();
            mD18.remove();
            mD7C.remove();
            flag = 0;
        } else if (atType & AT_TYPE_FIRE_ARROW) {
            JAIZelBasic::zel_basic->seStart(JA_SE_LK_MS_WEP_HIT, &eyePos, 0x20,
                                            dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            health -= 2;
            m920 = l_HIO.m150;
            flag = 1;
        } else if (atType & AT_TYPE_LIGHT_ARROW) {
            mCE8[0] = 0xB;
            JAIZelBasic::zel_basic->seStart(JA_SE_LK_MS_WEP_HIT, &eyePos, 0x20,
                                            dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            m500 = 0xA;
            mDE0.remove();
            mD18.remove();
            mD7C.remove();
            flag = 0;
        } else if (atType & AT_TYPE_HOOKSHOT) {
            JAIZelBasic::zel_basic->seStart(JA_SE_LK_MS_WEP_HIT, &eyePos, 0x20,
                                            dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            health -= 2;
            m920 = l_HIO.m154;
            flag = 1;
        } else if (atType & AT_TYPE_BOOMERANG) {
            JAIZelBasic::zel_basic->seStart(JA_SE_LK_W_WEP_HIT, &eyePos, 0x20,
                                            dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
            health -= 2;
            m920 = l_HIO.m158;
            flag = 1;
        }

        if (flag == 1) {
            JAIZelBasic::zel_basic->onEnemyDamage();
            fopAc_ac_c* player = dComIfGp_getPlayer(0);
            dComIfGp_particle_set(0x10, &hitPos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);

            if (mCE8[0] == 0xB) {
                cXyz scale(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(0xF, &hitPos, &player->shape_angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
                JAIZelBasic::zel_basic->seStart(JA_SE_LK_LAST_HIT, &eyePos, 0,
                                                dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
                return;
            }

            if (health <= 0) {
                cXyz scale(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(0xF, &hitPos, &player->shape_angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
                JAIZelBasic::zel_basic->seStart(JA_SE_LK_LAST_HIT, &eyePos, 0,
                                                dComIfGp_getReverb(current.roomNo), 1.0f, 1.0f, -1.0f, -1.0f, 0);
                health = 0;
                JAIZelBasic::zel_basic->monsSeStart(JA_SE_CV_GY_DIE, &eyePos, fopAcM_GetID(this), 0,
                                                    dComIfGp_getReverb(current.roomNo));
                if (m920 == l_HIO.m14C) {
                    modeDeleteBombInit();
                } else {
                    modeDeleteInit();
                }
                return;
            }

            m2B4 = m2B0;
            JAIZelBasic::zel_basic->monsSeStart(JA_SE_CV_GY_DAMAGE, &eyePos, fopAcM_GetID(this), 0,
                                                dComIfGp_getReverb(current.roomNo));
            modeDamageInit();
            return;
        }

        if (mCE8[0] == 9 || mCE8[0] == 0xB) {
            modeDeleteInit();
        }
    }
}

/* 000038EC-000039AC       .text getWaterY__6daGy_cFv */
f32 daGy_c::getWaterY() {
    f32 waterY;
    if (mAcch.ChkWaterHit()) {
        waterY = mAcch.m_wtr.GetHeight();
        if (current.pos.y > waterY) {
            gravity = -2.5f;
            return current.pos.y;
        }
        gravity = 0.0f;
        return waterY;
    }

    cXyz pos = current.pos;
    pos.y += 1000.0f;
    waterY = dBgS_GetWaterHeight(pos);
    if (current.pos.y > waterY) {
        gravity = -2.5f;
        return current.pos.y;
    }
    gravity = 0.0f;
    return waterY;
}

/* 000039AC-00004264       .text _execute__6daGy_cFv */
bool daGy_c::_execute() {
    /* Nonmatching */
}

/* 00004264-00004560       .text drawDebug__6daGy_cFv */
void daGy_c::drawDebug() {
    /* Nonmatching */
}

/* 00004560-000046C8       .text _draw__6daGy_cFv */
bool daGy_c::_draw() {
    /* Nonmatching */
}

/* 000046C8-00004920       .text createInit__6daGy_cFv */
void daGy_c::createInit() {
    /* Nonmatching */
}

/* 00004920-00004A80       .text _create__6daGy_cFv */
cPhs_State daGy_c::_create() {
    /* Nonmatching */
}

/* 00004A80-00005A80       .text __ct__6daGy_cFv */
/* Nonmatching */
daGy_c::daGy_c() {}

/* 00005A80-00005AD4       .text _delete__6daGy_cFv */
bool daGy_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    mD7C.remove();
    mD18.remove();
    mDE0.remove();
    return true;
}

static cPhs_State daGyCreate(void* i_this) {
    return ((daGy_c*)i_this)->_create();
}

static BOOL daGyDelete(void* i_this) {
    return ((daGy_c*)i_this)->_delete();
}

static BOOL daGyExecute(void* i_this) {
    return ((daGy_c*)i_this)->_execute();
}

static BOOL daGyDraw(void* i_this) {
    return ((daGy_c*)i_this)->_draw();
}

static BOOL daGyIsDelete(void*) {
    return TRUE;
}

static actor_method_class daGyMethodTable = {
    (process_method_func)daGyCreate,
    (process_method_func)daGyDelete,
    (process_method_func)daGyExecute,
    (process_method_func)daGyIsDelete,
    (process_method_func)daGyDraw,
};

actor_process_profile_definition g_profile_GY = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ fpcNm_GY_e,
    /* ProcSubMtd   */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daGy_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* LeafSubMtd   */ &g_fopAc_Method.base,
    /* Priority     */ fpcDwPi_GY_e,
    /* ActorSubMtd  */ &daGyMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
