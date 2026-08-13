/**
 * d_a_npc_bms1.cpp
 * NPC - Bomb-Master Cannon (Windfall Bomb Shop shopkeeper)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bms1.h"
#include "d/actor/d_a_player.h"
#include "d/d_cc_d.h"
#include "d/d_vibration.h"
#include "d/d_a_obj.h"
#include "d/d_item.h"
#include "d/d_lib.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_controller_pad.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};


static daNpc_Bms1_HIO_c l_HIO;
char daNpc_Bms1_c::m_arcname[] = "Bms";

/* 000000EC-00000108       .text __ct__21daNpc_Bms1_childHIO_cFv */
daNpc_Bms1_childHIO_c::daNpc_Bms1_childHIO_c() {
}

/* 00000108-00000148       .text daNpc_Bms1_shopMsgCheck__FUl */
static BOOL daNpc_Bms1_shopMsgCheck(u32 i_msgNo) {
    if ((i_msgNo >= 0x2788 && i_msgNo <= 0x2790) || (i_msgNo >= 0x277A && i_msgNo <= 0x2781) ||
        i_msgNo == 0x2783 || i_msgNo == 0x2776)
    {
        return TRUE;
    }
    return FALSE;
}

/* 00000148-00000188       .text daNpc_Bms1_shopStickMoveMsgCheck__FUl */
static BOOL daNpc_Bms1_shopStickMoveMsgCheck(u32 i_msgNo) {
    if ((i_msgNo >= 0x2788 && i_msgNo <= 0x278A) || (i_msgNo >= 0x277A && i_msgNo <= 0x277C) ||
        i_msgNo == 0x2783 || i_msgNo == 0x2776)
    {
        return TRUE;
    }
    return FALSE;
}

/* 00000188-000002A0       .text __ct__16daNpc_Bms1_HIO_cFv */
daNpc_Bms1_HIO_c::daNpc_Bms1_HIO_c() {
    mChild[0].mNpc.m04 = -50.0f;
    mChild[0].mNpc.mMaxHeadX = 0x1388;
    mChild[0].mNpc.mMaxHeadY = 0x2710;
    mChild[0].mNpc.mMaxBackboneX = 0;
    mChild[0].mNpc.mMaxBackboneY = 0x834;
    mChild[0].mNpc.mMinHeadX = -0x1FFE;
    mChild[0].mNpc.mMinHeadY = 0;
    mChild[0].mNpc.mMinBackboneX = 0;
    mChild[0].mNpc.mMinBackboneY = 0;
    mChild[0].mNpc.mMaxTurnStep = 0x1000;
    mChild[0].mNpc.mMaxHeadTurnVel = 0x800;
    mChild[0].mNpc.mAttnYOffset = 40.0f;
    mChild[0].mNpc.m22 = 0;
    mChild[0].mNpc.mMaxAttnDistXZ = 300.0f;
    mChild[0].m2C = 0.65f;
    mChild[0].m30 = 0.9f;
    mChild[0].m34 = 0.5f;
    mChild[0].m38 = 27.0f;
    mChild[0].m3C = 20.0f;
    mChild[0].m40 = 0.45f;
    mChild[0].m44 = 0.8f;
    mChild[0].m48 = 0.9f;
    mChild[0].m4C = 0.000122f;
    mNo = 0xFF;
    m8 = -1;
}

/* 00000300-000004C4       .text nodeCallBack_Bms__FP7J3DNodei */
static BOOL nodeCallBack_Bms(J3DNode* node, int calcTiming) {
    /* Nonmatching */
    if (calcTiming == 0) {
        J3DModel* pModel = j3dSys.getModel();
        daNpc_Bms1_c* pBms = (daNpc_Bms1_c*)pModel->getUserArea();
        u16 jntNo = ((J3DJoint*)node)->getJntNo();
        if (pBms != NULL) {
            PSMTXCopy(pModel->getAnmMtx(jntNo), *calc_mtx);

            if (jntNo == pBms->getHeadJntNum()) {
                cXyz offset(0.0f, 0.0f, 0.0f);
                mDoMtx_YrotM(*calc_mtx, -(pBms->getHead_y() + pBms->mHeadAnm.field_0x02));
                mDoMtx_ZrotM(*calc_mtx, -(pBms->getHead_x() + pBms->mHeadAnm.field_0x00));
                cXyz result;
                MtxPosition(&offset, &result);
                pBms->setAttentionBasePos(result);

                cXyz offset2(28.0f, -20.0f, 0.0f);
                MtxPosition(&offset2, &result);
                pBms->setEyePos(result);
            } else if (jntNo == pBms->getBackboneJntNum()) {
                mDoMtx_XrotM(*calc_mtx, pBms->getBackbone_y());
                mDoMtx_ZrotM(*calc_mtx, pBms->getBackbone_x());
            }

            PSMTXCopy(*calc_mtx, j3dSys.mCurrentMtx);
            PSMTXCopy(*calc_mtx, pModel->getAnmMtx(jntNo));
        }
    }
    return TRUE;
}

/* 000004C4-00000A00       .text nodeCallBack_BmsHead__FP7J3DNodei */
static BOOL nodeCallBack_BmsHead(J3DNode* node, int calcTiming) {
    /* Nonmatching */
    if (calcTiming == 0) {
        J3DModel* pModel = j3dSys.getModel();
        daNpc_Bms1_c* pBms = (daNpc_Bms1_c*)pModel->getUserArea();
        u16 jntNo = ((J3DJoint*)node)->getJntNo();
        if (pBms != NULL) {
            static cXyz l_zero = cXyz::Zero;
            static cXyz l_ten = cXyz(40.0f, 0.0f, 0.0f);

            PSMTXCopy(pModel->getAnmMtx(jntNo), mDoMtx_stack_c::now);

    if (jntNo == pBms->getHairLJntNum()) {
        mDoMtx_stack_c::scaleM(pBms->m2B4.x * pBms->m2CC, pBms->m2B4.y, pBms->m2B4.z);
        Mtx local;
        PSMTXCopy(mDoMtx_stack_c::now, local);
        cXyz trans(local[0][3], local[1][3], local[2][3]);
        local[0][3] = 0.0f;
        local[1][3] = 0.0f;
        local[2][3] = 0.0f;
        mDoMtx_stack_c::transS(trans.x, trans.y, trans.z);
        mDoMtx_stack_c::quatM(&pBms->m304);
        PSMTXConcat(mDoMtx_stack_c::now, local, mDoMtx_stack_c::now);
        cXyz v1;
        cXyz v2;
        PSMTXMultVec(mDoMtx_stack_c::now, &l_ten, &v1);
        PSMTXMultVec(mDoMtx_stack_c::now, &l_zero, &v2);
        PSMTXCopy(mDoMtx_stack_c::now, pModel->getAnmMtx(jntNo));

        if (pBms->m2D4.isZero()) {
            pBms->m2D4 = v1;
        }
        cXyz diff = v1 - pBms->m2D4;
        cXyz scaled = diff * l_HIO.mChild[0].m40;
        pBms->m2EC = pBms->m2EC + scaled;
        pBms->m2EC = pBms->m2EC * l_HIO.mChild[0].m44;
        pBms->m2D4 = pBms->m2D4 + pBms->m2EC;

        cXyz d1 = v1 - v2;
        cXyz d2 = pBms->m2D4 - v2;
        Quaternion rot;
        daObj::quat_rotVec(&rot, d1, d2);
        C_QUATSlerp(&pBms->m304, &rot, &pBms->m304, l_HIO.mChild[0].m48);
        f32 dot = PSVECDotProduct(&d2, &pBms->m2EC);
        pBms->m2CC = 1.0f - l_HIO.mChild[0].m4C * dot;
        if (pBms->m2CC < 0.5f) {
            pBms->m2CC = 0.5f;
        } else if (pBms->m2CC > 1.0f) {
            pBms->m2CC = 1.0f;
        }
    } else if (jntNo == pBms->getHairRJntNum()) {
        mDoMtx_stack_c::scaleM(pBms->m2C0.x * pBms->m2D0, pBms->m2C0.y, pBms->m2C0.z);
        Mtx local;
        PSMTXCopy(mDoMtx_stack_c::now, local);
        cXyz trans(local[0][3], local[1][3], local[2][3]);
        local[0][3] = 0.0f;
        local[1][3] = 0.0f;
        local[2][3] = 0.0f;
        mDoMtx_stack_c::transS(trans.x, trans.y, trans.z);
        mDoMtx_stack_c::quatM(&pBms->m314);
        PSMTXConcat(mDoMtx_stack_c::now, local, mDoMtx_stack_c::now);
        cXyz v1;
        cXyz v2;
        PSMTXMultVec(mDoMtx_stack_c::now, &l_ten, &v1);
        PSMTXMultVec(mDoMtx_stack_c::now, &l_zero, &v2);
        PSMTXCopy(mDoMtx_stack_c::now, pModel->getAnmMtx(jntNo));

        if (pBms->m2E0.isZero()) {
            pBms->m2E0 = v1;
        }
        cXyz diff = v1 - pBms->m2E0;
        cXyz scaled = diff * l_HIO.mChild[0].m40;
        pBms->m2EC = pBms->m2EC + scaled;
        pBms->m2EC = pBms->m2EC * l_HIO.mChild[0].m44;
        pBms->m2E0 = pBms->m2E0 + pBms->m2EC;

        cXyz d1 = v1 - v2;
        cXyz d2 = pBms->m2E0 - v2;
        Quaternion rot;
        daObj::quat_rotVec(&rot, d1, d2);
        C_QUATSlerp(&pBms->m314, &rot, &pBms->m314, l_HIO.mChild[0].m48);
        f32 dot = PSVECDotProduct(&d2, &pBms->m2EC);
        pBms->m2D0 = 1.0f - l_HIO.mChild[0].m4C * dot;
        if (pBms->m2D0 < 0.5f) {
            pBms->m2D0 = 0.5f;
        } else if (pBms->m2D0 > 1.0f) {
            pBms->m2D0 = 1.0f;
        }
        }
    }
    }

    return TRUE;
}

/* 00000A00-00000C4C       .text set_mtx__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::set_mtx() {
    /* Nonmatching */
    J3DModel* pModel = mpMorf->getModel();
    if (mShopIdx == 0) {
        cXyz offset(0.0f, 100.0f, 35.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::transM(offset);
    } else {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(shape_angle.y);
    }

    PSMTXCopy(mDoMtx_stack_c::now, pModel->getBaseTRMtx());
    mDoMtx_stack_c::copy(pModel->getAnmMtx(m_head_jnt_num));
    PSMTXCopy(mDoMtx_stack_c::now, mpModel->getBaseTRMtx());

    if (mShopIdx == 1) {
        mDoMtx_stack_c::copy(pModel->getAnmMtx(m_head_jnt_num));
        PSMTXCopy(mDoMtx_stack_c::now, mpModel2->getBaseTRMtx());
        mDoMtx_stack_c::copy(pModel->getAnmMtx(m_head_jnt_num));
        PSMTXCopy(mDoMtx_stack_c::now, mpModel3->getBaseTRMtx());
    } else if (dComIfGs_isEventBit(0xA02)) {
        mDoMtx_stack_c::copy(pModel->getAnmMtx(m_head_jnt_num));
        PSMTXCopy(mDoMtx_stack_c::now, mpModel3->getBaseTRMtx());
    }

    if (mpModel4 != NULL) {
        mDoMtx_stack_c::copy(pModel->getAnmMtx(m_leg_jnt_num));
        PSMTXCopy(mDoMtx_stack_c::now, mpModel4->getBaseTRMtx());
    }

    if (mpModel5 != NULL) {
        mDoMtx_stack_c::transS(current.pos);
        PSMTXCopy(mDoMtx_stack_c::now, mpModel5->getBaseTRMtx());
    }
}

static msg_class* l_msg;

static const int l_btp_ix_tbl[] = { 0x0F, 0x0E };
static const int l_bck_ix_tbl[] = { 0x13, 0x14, 0x16, 0x17, 0x15, 0x16, 0x17 };

/* 00000C4C-00000D54       .text initTexPatternAnm__12daNpc_Bms1_cFb */
/* Nonmatching */
BOOL daNpc_Bms1_c::initTexPatternAnm(bool i_0) {
    J3DModelData* modelData = mpModel->getModelData();
    mpBtpRes = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname, l_btp_ix_tbl[mBtpIdx]);
    JUT_ASSERT(0x23E, mpBtpRes != NULL);

    if (mBtpAnm.init(modelData, mpBtpRes, TRUE, 2, 1.0f, 0, -1, i_0) == 0) {
        return FALSE;
    }
    mBtpFrame = 0;
    m34E = 0;
    return TRUE;
}

/* 00000D54-00000DE0       .text playTexPatternAnm__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::playTexPatternAnm() {
    /* Nonmatching */
    if (cLib_calcTimer(&m34E) == 0) {
        s16 frameCount = mpBtpRes->getFrameMax();
        if (mBtpFrame >= frameCount) {
            mBtpFrame = mBtpFrame - frameCount;
            m34E = (s16)(cM_rndF(100.0f) + 30.0f);
        } else {
            mBtpFrame = mBtpFrame + 1;
        }
    }
}

/* 00000DE0-00000E78       .text setAnm__12daNpc_Bms1_cFScf */
void daNpc_Bms1_c::setAnm(s8 index, f32 morfFrame) {
    /* Nonmatching */
    static u32 play_mode_tbl[7] = {
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
    };
    static f32 morf_frame_tbl[7] = {8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f};
    static f32 play_speed_tbl[7] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

    if (morfFrame < 0.0f) {
        morfFrame = morf_frame_tbl[index];
    }

    if (index != m899 || m899 == -1) {
        m899 = index;
        dNpc_setAnm_2(mpMorf, play_mode_tbl[index], morfFrame, play_speed_tbl[index],
                      l_bck_ix_tbl[index], 0, m_arcname);
    }
}

/* 00000E78-00000EBC       .text setTexAnm__12daNpc_Bms1_cFSc */
void daNpc_Bms1_c::setTexAnm(s8 i_texNo) {
    u8 texNo = mBtpIdx;
    if ((s8)texNo != i_texNo || (s8)texNo == -1) {
        mBtpIdx = i_texNo;
        initTexPatternAnm(TRUE);
    }
}

/* 00000EBC-00001100       .text setAnmFromMsgTag__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::setAnmFromMsgTag() {
    /* Nonmatching */
    if (mShopIdx == 1) {
        return;
    }

    switch (g_dComIfG_gameInfo.play.mMesgAnime) {
    case 0:
        setAnm(0, -1.0f);
        break;
    case 1:
        setAnm(1, -1.0f);
        break;
    case 2:
        setAnm(2, -1.0f);
        break;
    case 3:
        setAnm(3, -1.0f);
        break;
    case 4:
        setAnm(4, -1.0f);
        m89A = 1;
        break;
    case 5:
        setAnm(5, -1.0f);
        m89A = 3;
        break;
    case 6:
        setAnm(6, -1.0f);
        m89A = 3;
        break;
    }

    if (m899 == 5) {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            if ((m89A -= 1) != 0) {
            } else {
                setAnm(0, 13.0f);
            }
        }
    } else if (m899 == 6) {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            if ((m89A -= 1) != 0) {
            } else {
                setAnm(1, -1.0f);
            }
        }
    } else if (m899 == 4) {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            if ((m89A -= 1) != 0) {
            } else {
                setAnm(1, -1.0f);
            }
        }
    }

    g_dComIfG_gameInfo.play.mMesgAnime = 0xFF;
}

/* 00001100-000011D8       .text chkAttention__12daNpc_Bms1_cF4cXyzs */
BOOL daNpc_Bms1_c::chkAttention(cXyz param, s16) {
    /* Nonmatching */
    daPy_py_c* pPlayer = daPy_getPlayerActorClass();
    f32 maxAttnDistXZ = l_HIO.mChild[0].m30;
    cXyz sp20 = pPlayer->current.pos - param;
    cXyz sp14(cM_ssin(shape_angle.y), 0.0f, cM_scos(shape_angle.y));
    return maxAttnDistXZ > sp14.inprod(sp20);
}

/* 000011D8-00001278       .text eventOrder__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::eventOrder() {
    /* Nonmatching */
    if (m89B == 0x4) {
        fopAcM_orderOtherEvent2(this, "BMS_LAND_DEMO", 1, 0xFFFF);
    } else if (m89B == 0x3) {
        fopAcM_orderOtherEvent2(this, "BMS_GET_DEMO", 1, 0xFFFF);
    } else if (m89B == 0x1 || m89B == 0x2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m89B == 0x1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00001278-000014AC       .text checkOrder__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::checkOrder() {
    /* Nonmatching */
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (m89B == 4) {
            m89B = 0;
            mShopCam.Reset();
            setAction(&daNpc_Bms1_c::event_action, NULL);
        } else if (m89B == 3) {
            m89B = 0;
            mShopCam.Reset();
            setAction(&daNpc_Bms1_c::getdemo_action, NULL);
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (m89B == 1 || m89B == 2) {
            m89B = 0;
            m7CD = 1;
            talkInit();
            mShopCam.shop_cam_action_init();
            cXyz pos(-70.0f, 0.0f, 150.0f);
            daPy_getPlayerActorClass()->setPlayerPosAndAngle(&pos, -0x7000);
        }
    } else {
        mShopCam.Save();
    }
}

/* 000014AC-000017FC       .text next_msgStatus__12daNpc_Bms1_cFPUl */
u16 daNpc_Bms1_c::next_msgStatus(u32* pMsgNo) {
    /* Nonmatching */
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;

    switch (*pMsgNo) {
    case 0x2775:
    case 0x2777:
    case 0x2780:
    case 0x2782:
        *pMsgNo += 1;
        break;
    case 0x2784:
        *pMsgNo = 0x2786;
        break;
    case 0x2776:
        if (g_mDoCPd_cpadInfo[0].mButtonTrig.b) {
            *pMsgNo = 0x2779;
        } else {
            g_dComIfG_gameInfo.play.mDoStatusForce = 0x17;
            g_dComIfG_gameInfo.play.mAStatusForce = 0x27;
            msgStatus = 0xE;
        }
        break;
    case 0x2783:
        if (g_mDoCPd_cpadInfo[0].mButtonTrig.b) {
            *pMsgNo = 0x2787;
        } else {
            g_dComIfG_gameInfo.play.mDoStatusForce = 0x17;
            g_dComIfG_gameInfo.play.mAStatusForce = 0x27;
            msgStatus = 0xE;
        }
        break;
    case 0x277A:
    case 0x277B:
    case 0x277C:
        if (g_mDoCPd_cpadInfo[0].mButtonTrig.b) {
            *pMsgNo = 0x2779;
        } else {
            g_dComIfG_gameInfo.play.mDoStatusForce = 0x17;
            g_dComIfG_gameInfo.play.mAStatusForce = 0x27;
            *pMsgNo += 3;
            msgStatus = 0xE;
        }
        break;
    case 0x2788:
    case 0x2789:
    case 0x278A:
        if (g_mDoCPd_cpadInfo[0].mButtonTrig.b) {
            *pMsgNo = 0x2787;
        } else {
            g_dComIfG_gameInfo.play.mDoStatusForce = 0x17;
            g_dComIfG_gameInfo.play.mAStatusForce = 0x27;
            *pMsgNo += 3;
            msgStatus = 0xE;
        }
        break;
    case 0x2778:
    case 0x2781:
        *pMsgNo = 0x2776;
        break;
    case 0x277D:
    case 0x277E:
    case 0x277F:
        if (g_dComIfG_gameInfo.play.mMesgCancelButton != 0) {
            *pMsgNo = *pMsgNo - 3;
        } else if (l_msg->mSelectNum == 0) {
            *pMsgNo = 0x2780;
        }
        break;
    case 0x278B:
    case 0x278C:
    case 0x278D:
        if (g_dComIfG_gameInfo.play.mMesgCancelButton != 0) {
            *pMsgNo = *pMsgNo - 3;
        } else if (l_msg->mSelectNum == 0) {
            int itemPrice = dComIfGp_getMessageRupee();
            u8 status = dShop_BoughtErrorStatus(&mShopItems, 0, itemPrice);
            if (status & 0x20) {
                *pMsgNo = 0x278E;
                break;
            }
            if (status & 0x4) {
                *pMsgNo = 0x278F;
                break;
            }
            fopAcM_seStart(this, JA_SE_SHOP_BOUGHT, 0);
            mShopItems.hideSelectItem();
            m7E8 = mShopItems.getSelectItemNo();
            dComIfGp_setItemRupeeCount(-itemPrice);
            u8 itemNo = mShopItems.getSelectItemNo();
            if (!checkItemGet(itemNo, TRUE)) {
                m89B = 3;
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
            }
            itemNo = mShopItems.getSelectItemNo();
            execItemGet(itemNo);
            *pMsgNo = 0x2790;
        } else {
            *pMsgNo = *pMsgNo - 3;
        }
        break;
    case 0x2790:
        *pMsgNo = 0x2783;
        break;
    case 0x2786:
    case 0x278E:
    case 0x278F:
        *pMsgNo = 0x2783;
        break;
    default:
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    }

    return msgStatus;
}

/* 000017FC-00001860       .text getMsg__12daNpc_Bms1_cFv */
u32 daNpc_Bms1_c::getMsg() {
    u32 msgNo;
    if (mLastMsgNo) {
        msgNo = mLastMsgNo;
        mLastMsgNo = 0;
    } else if (!dComIfGs_isEventBit(0xA02)) {
        msgNo = 0x2775;
    } else {
        msgNo = 0x2782;
    }
    return msgNo;
}

/* 00001860-0000191C       .text setCollision__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::setCollision() {
    /* Nonmatching */
    cXyz offset(0.0f, 0.0f, 0.0f);
    offset.z = -16.0f;
    cXyz out;
    MtxTrans(current.pos.x, current.pos.y, current.pos.z, false);
    cMtx_YrotM(*calc_mtx, m7C4);
    MtxPosition(&offset, &out);
    mCyl.SetC(out);
    mCyl.SetR(46.0f);
    mCyl.SetH(130.0f);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 0000191C-00001928       .text talkInit__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::talkInit() {
    m8A1[0] = 0;
}

/* 00001928-00001A34       .text normal_talk__12daNpc_Bms1_cFv */
u16 daNpc_Bms1_c::normal_talk() {
    /* Nonmatching */
}

/* 00001A34-00001B88       .text shop_talk__12daNpc_Bms1_cFv */
u16 daNpc_Bms1_c::shop_talk() {
    /* Nonmatching */
}

/* 00001B88-00001D68       .text talk__12daNpc_Bms1_cFv */
u16 daNpc_Bms1_c::talk() {
    /* Nonmatching */
}

/* 00001D68-00002104       .text CreateInit__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::CreateInit() {
    /* Nonmatching */
    cXyz zero(0.0f, 0.0f, 0.0f);
    m7C2 = current.angle.x;
    m7C4 = current.angle.y;
    m7C6 = current.angle.z;
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAD;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAD;
    gravity = -30.0f;

    switch (mShopIdx) {
    case 0:
        setAction(&daNpc_Bms1_c::wait_action, 0);
        break;
    case 1:
        setAction(&daNpc_Bms1_c::wait_action, 0);
        break;
    }

    mAttnBasePos = current.pos;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    m8A2 = 0;
    m7A4 = 0;
    mLastMsgNo = 0;
    m7E8 = 0xFF;

    int stock = (checkItemGet(dItemNo_PEARL_NAYRU_e, TRUE) != 0) + 1;

    if (mShopIdx == 1) {
        m2B4.set(1.2f, 0.9f, 0.9f);
        m2C0.set(0.7f, 0.6f, 0.6f);
    } else if (checkItemGet(dItemNo_PEARL_NAYRU_e, TRUE)) {
        m2B4.set(0.4f, 0.4f, 0.4f);
        m2C0.set(0.4f, 0.4f, 0.4f);
    } else {
        m2B4.set(1.2f, 0.9f, 0.9f);
        m2C0.set(0.7f, 0.6f, 0.6f);
    }

    m2CC = 1.0f;
    m2D0 = 1.0f;
    m304 = ZeroQuat;
    m314 = ZeroQuat;

    mShopCam.setCamDataIdx(stock);
    mShopItems.setItemDataIdx(stock);
    mShopCam.mCurrActionFunc = NULL;
    mShopItems.setItemSetDataList();
    mShopItems.createItem(3, current.roomNo);
    m7E9 = 0;
    m7D4 = current.pos.y;
    mEventCut.setActorInfo("BMS_LAND_DEMO", this);
    mEventCut.setJntCtrlPtr(&mJntCtrl);
    mpMorf->calc();
    set_mtx();
    return TRUE;
}

/* 00002104-00002144       .text setAttention__12daNpc_Bms1_cFb */
void daNpc_Bms1_c::setAttention(bool i_attn) {
    if (i_attn || m7CB < 2) {
        attention_info.position.set(mAttnBasePos.x, mAttnBasePos.y + l_HIO.mChild[0].mNpc.mAttnYOffset,
                                    mAttnBasePos.z);
    }
}

/* 00002144-000021F4       .text checkPlayerLanding__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::checkPlayerLanding() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    f32 playerY = player->current.pos.y;
    BOOL landed = FALSE;
    if (m7D4 - playerY > 200.0f && !player->checkPlayerFly()) {
        landed = TRUE;
    }
    if (!player->checkPlayerFly()) {
        m7D4 = playerY;
    }
    return landed;
}

/* 000021F4-00002424       .text lookBack__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::lookBack() {
    /* Nonmatching */
    cXyz target(0.0f, 0.0f, 0.0f);
    cXyz* pTarget = NULL;
    s16 angle = shape_angle.y;

    switch (m89C) {
    case 0:
        break;
    case 1:
        if (m7CC != 0) {
            cXyz eyePos = dNpc_playerEyePos(l_HIO.field_0x14);
            target.x = eyePos.x;
            target.y = eyePos.y;
            target.z = eyePos.z;
            pTarget = &target;
            target.x = current.pos.x;
            target.y = current.pos.y;
            target.z = current.pos.z;
            target.y = eyePos.y;
        } else {
            pTarget = NULL;
        }
        break;
    case 2:
        if (mShopItems.mItemId == -1) {
            cXyz itemPos = mShopCam.getItemZoomPos(1.0f);
            target.x = itemPos.x;
            target.y = itemPos.y;
            target.z = itemPos.z;
        } else {
            cXyz basePos = mShopItems.getSelectItemBasePos();
            target.x = basePos.x;
            target.y = basePos.y;
            target.z = basePos.z;
            cXyz itemPos = mShopItems.getSelectItemPos();
            target.x = itemPos.x;
            target.y = itemPos.y;
            target.z = itemPos.z;
            mpShopCursor->setPos(target);
            mpShopCursor->setPos(basePos);
            mpShopCursor->anm_play();
        }
        pTarget = &target;
        target.x = current.pos.x;
        target.y = current.pos.y;
        target.z = current.pos.z;
        target.y = eyePos.y;
        break;
    }

    if (mJntCtrl.mbTrn) {
        cLib_addCalcAngleS2(&m7C0, l_HIO.field_0x2A, 4, 0x800);
    } else {
        m7C0 = 0;
    }

    mJntCtrl.lookAtTarget(&shape_angle.y, &target, pTarget, angle, m7C0, true);
}

/* 00002424-0000249C       .text wait01__12daNpc_Bms1_cFv */
bool daNpc_Bms1_c::wait01() {
    /* Nonmatching */
    if (m7CD != 0) {
        m89D = m89C;
        m89C = 2;
    } else if (m7CC != 0) {
        if (mShopIdx == 1) {
            m89B = 0;
        } else {
            m89B = 2;
        }
    }
    return mpMorf->isMorf();
}

/* 0000249C-00002590       .text talk01__12daNpc_Bms1_cFv */
bool daNpc_Bms1_c::talk01() {
    /* Nonmatching */
    u16 status = talk();
    if (status == 0x12) {
        daPy_py_c* player = daPy_getPlayerActorClass();
        m89C = m89D;
        dComIfGp_event_reset();
        mShopCam.Reset();
        player->offPlayerNoDraw();
        m7CD = 0;
    } else if (daNpc_Bms1_shopMsgCheck(mMsgNo) && status == 8 &&
               mMsgNo == mShopItems.getSelectItemBuyMsg()) {
        dComIfGp_setDoStatusForce(dActStts_CHOOSE_e);
        dComIfGp_setAStatusForce(dActStts_CANCEL_e);
    }
    return mpMorf->isMorf();
}

/* 00002590-00002764       .text getdemo_action__12daNpc_Bms1_cFPv */
BOOL daNpc_Bms1_c::getdemo_action(void*) {
    /* Nonmatching */
}

/* 00002764-00002918       .text wait_action__12daNpc_Bms1_cFPv */
BOOL daNpc_Bms1_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00002918-00002A98       .text event_action__12daNpc_Bms1_cFPv */
BOOL daNpc_Bms1_c::event_action(void*) {
    /* Nonmatching */
}

/* 00002A98-00002B94       .text evn_talk_init__12daNpc_Bms1_cFi */
BOOL daNpc_Bms1_c::evn_talk_init(int) {
    /* Nonmatching */
}

/* 00002B94-00002BFC       .text evn_continue_talk_init__12daNpc_Bms1_cFi */
BOOL daNpc_Bms1_c::evn_continue_talk_init(int) {
    /* Nonmatching */
}

/* 00002BFC-00002DD8       .text evn_talk__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::evn_talk() {
    /* Nonmatching */
}

/* 00002DD8-00002E30       .text evn_viblation_init__12daNpc_Bms1_cFi */
BOOL daNpc_Bms1_c::evn_viblation_init(int) {
    /* Nonmatching */
    dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
    return TRUE;
}

/* 00002E30-00002E68       .text evn_head_swing_init__12daNpc_Bms1_cFi */
BOOL daNpc_Bms1_c::evn_head_swing_init(int) {
    mHeadAnm.swing_vertical_init(1, 0x1800, 0x1000, 1);
    return TRUE;
}

/* 00002E68-00002FBC       .text privateCut__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::privateCut() {
    /* Nonmatching */
}

/* 00002FBC-000030A4       .text demo_move__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::demo_move() {
    /* Nonmatching */
}

/* 000030A4-000030B0       .text demo_end_init__12daNpc_Bms1_cFv */
void daNpc_Bms1_c::demo_end_init() {
    m7E9 = 0;
}

/* 000030B0-00003314       .text _draw__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::_draw() {
    /* Nonmatching */
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = mpModel->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(pModelData, mBtpFrame);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpMorf->entryDL();
    mDoExt_modelUpdateDL(mpModel);

    if (mShopIdx == 1) {
        g_env_light.setLightTevColorType(mpModel2, &tevStr);
        mDoExt_modelUpdateDL(mpModel2);
        g_env_light.setLightTevColorType(mpModel3, &tevStr);
        mDoExt_modelUpdateDL(mpModel3);
    } else if (dComIfGs_isEventBit(0xA02)) {
        g_env_light.setLightTevColorType(mpModel2, &tevStr);
        mDoExt_modelUpdateDL(mpModel2);
    }

    if (mpModel4 != NULL) {
        g_env_light.setLightTevColorType(mpModel4, &tevStr);
        mDoExt_modelUpdateDL(mpModel4);
    }

    if (mpModel5 != NULL) {
        g_env_light.setLightTevColorType(mpModel5, &tevStr);
        mDoExt_modelUpdateDL(mpModel5);
    }

    mBtpAnm.remove(pModelData);

    cXyz shadowPos(current.pos.x, current.pos.y + 130.0f, current.pos.z);
    mShadowID = dComIfGd_setShadow(
        mShadowID, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr
    );

    if (mShadowID != 0) {
        g_dComIfG_gameInfo.drawlist.addRealShadow(mShadowID, mpModel);
    }

    if (mShopItems.mSelectedItemIdx >= 0) {
        mpShopCursor->draw();
    }

    cXyz snapPos(current.pos);
    if (mShopIdx == 1) {
        snapPos.y -= 90.0f;
    }
    dSnap_RegistFig(0x5C, this, snapPos, current.angle.y, 1.0f, 1.0f, 1.0f);

    return TRUE;
}

/* 00003314-00003474       .text _execute__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::_execute() {
    mJntCtrl.setParam(
        l_HIO.mChild[0].mNpc.mMaxBackboneX, l_HIO.mChild[0].mNpc.mMaxBackboneY,
        l_HIO.mChild[0].mNpc.mMinBackboneX, l_HIO.mChild[0].mNpc.mMinBackboneY,
        l_HIO.mChild[0].mNpc.mMaxHeadX, l_HIO.mChild[0].mNpc.mMaxHeadY,
        l_HIO.mChild[0].mNpc.mMinHeadX, l_HIO.mChild[0].mNpc.mMinHeadY,
        l_HIO.mChild[0].mNpc.mMaxTurnStep);
    playTexPatternAnm();
    mMorfIsStop = mpMorf->play(&eyePos, 0, 0);
    mpMorf->calc();
    if (mpMorf->getFrame() < mMorfPrevFrame) {
        mMorfIsStop = 1;
    }
    mMorfPrevFrame = mpMorf->getFrame();

    if (!demo_move()) {
        checkOrder();
        (this->*mCurrActionFunc)(NULL);
        mShopCam.move();
        mShopItems.Item_Move();
        eventOrder();
    }

    mHeadAnm.move();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
    set_mtx();
    setCollision();
    return TRUE;
}

/* 00003474-00003514       .text _delete__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::_delete() {
    if (m8A5 == 1) {
        return TRUE;
    }
    dComIfG_resDelete(&mPhs, m_arcname);
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    if (l_HIO.m8 >= 0 && (l_HIO.m8 -= 1) < 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    return TRUE;
}
/* 00003514-00003534       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->CreateHeap();
}

/* 00003534-00003718       .text _create__12daNpc_Bms1_cFv */
cPhs_State daNpc_Bms1_c::_create() {
    /* Nonmatching */
    fopAcM_ct_Retail(this, daNpc_Bms1_c);

    mShopIdx = fopAcM_GetParam(this) >> 24;
    if (mShopIdx == 0) {
        if (dComIfGs_isEventBit(0xA02) && !checkItemGet(dItemNo_PEARL_NAYRU_e, TRUE)) {
            m8A5 = 1;
            return cPhs_ERROR_e;
        }
        m8A5 = 0;
    } else {
        if (dComIfGs_isEventBit(0xA02) && !checkItemGet(dItemNo_PEARL_NAYRU_e, TRUE)) {
            m8A5 = 0;
        } else {
            m8A5 = 1;
            return cPhs_ERROR_e;
        }
    }

    cPhs_State phase = (cPhs_State)dComIfG_resLoad(&mPhs, m_arcname);
    if (phase == cPhs_COMPLEATE_e) {
        switch (mShopIdx) {
        case 0:
            mShopIdx = 0;
            break;
        default:
            mShopIdx = 1;
            break;
        }

        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x28000)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());

        if (l_HIO.m8 < 0) {
            l_HIO.mNo = mDoHIO_createChild("Bms", &l_HIO);
        }
        l_HIO.m8 += 1;

        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 00003CE8-000043B8       .text CreateHeap__12daNpc_Bms1_cFv */
BOOL daNpc_Bms1_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* modelData;
    J3DAnmTransform* anmTransform;
    if (mShopIdx == 0) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x1D);
        if (!checkItemGet(dItemNo_PEARL_NAYRU_e, TRUE)) {
            anmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, 0x13);
        } else {
            anmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, 0x14);
        }
    } else {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x1A);
        anmTransform = (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, 0x12);
        m89A = 3;
    }

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        anmTransform,
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x00000000,
        0x110203
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }

    m_head_jnt_num = modelData->getJointName()->getIndex("head");
    JUT_ASSERT(0x823, m_head_jnt_num >= 0);

    m_backbone_jnt_num = modelData->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x826, m_backbone_jnt_num >= 0);

    if (mShopIdx == 0) {
        m_leg_jnt_num = modelData->getJointName()->getIndex("center");
        JUT_ASSERT(0x82B, m_leg_jnt_num >= 0);
    }

    J3DModelData* headModelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x23);
    mpModel = mDoExt_J3DModel__create(headModelData, 0x80000, 0x110202);
    if (mpModel == NULL) {
        return FALSE;
    }

    m_hairL_jnt_num = headModelData->getJointName()->getIndex("hairL");
    JUT_ASSERT(0x83E, m_hairL_jnt_num >= 0);

    m_hairR_jnt_num = headModelData->getJointName()->getIndex("hairR");
    JUT_ASSERT(0x841, m_hairR_jnt_num >= 0);

    mBtpIdx = 1;
    if (!initTexPatternAnm(FALSE)) {
        return FALSE;
    }

    switch (mShopIdx) {
    case 0:
        if (dComIfGs_isEventBit(0xA02)) {
            setTexAnm(1);
        } else {
            setTexAnm(0);
        }
        break;
    case 1:
        setTexAnm(1);
        break;
    }

    mpModel2 = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x1B), 0, 0x110203);
    if (mpModel2 == NULL) {
        return FALSE;
    }

    mpModel3 = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x1C), 0, 0x110203);

    if (mShopIdx == 0) {
        J3DModelData* resData;
        if (dComIfGs_isEventBit(0xA02)) {
            resData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x1F);
        } else {
            resData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x1E);
        }
        mpModel4 = mDoExt_J3DModel__create(resData, 0, 0x110203);
        if (mpModel4 == NULL) {
            return FALSE;
        }
        mpModel5 = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x20), 0, 0x110203);
        if (mpModel5 == NULL) {
            return FALSE;
        }
    } else {
        mpModel4 = NULL;
    }

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == m_head_jnt_num || i == m_backbone_jnt_num) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Bms);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);

    for (u16 i = 0; i < mpModel->getModelData()->getJointNum(); i++) {
        if (i == m_hairL_jnt_num || i == m_hairR_jnt_num) {
            mpModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_BmsHead);
        }
    }
    mpModel->setUserArea((u32)this);

    mAcchCir.SetWall(30.0f, 0.0f);
    mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed);

    J3DAnmTevRegKey* tevRegKey = (J3DAnmTevRegKey*)dComIfG_getObjectRes(m_arcname, 0x0B);
    J3DModelData* cursorModelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x08);
    mpShopCursor = ShopCursor_create(cursorModelData, tevRegKey, l_HIO.mChild[0].m2C);

    return mpShopCursor != NULL ? TRUE : FALSE;
}

/* 000043B8-000043D8       .text daNpc_Bms1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Bms1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_create();
}

/* 000043D8-000043F8       .text daNpc_Bms1_Delete__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_Delete(daNpc_Bms1_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_delete();
}

/* 000043F8-00004418       .text daNpc_Bms1_Execute__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_Execute(daNpc_Bms1_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_execute();
}

/* 00004418-00004438       .text daNpc_Bms1_Draw__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_Draw(daNpc_Bms1_c* i_this) {
    return ((daNpc_Bms1_c*)i_this)->_draw();
}

/* 00004438-00004440       .text daNpc_Bms1_IsDelete__FP12daNpc_Bms1_c */
static BOOL daNpc_Bms1_IsDelete(daNpc_Bms1_c*) {
    return TRUE;
}

// /* 000047AC-000047C8       .text setEyePos__12daNpc_Bms1_cF4cXyz */
// void daNpc_Bms1_c::setEyePos(cXyz) {
//     /* Nonmatching */
// }

// /* 000047C8-000047E4       .text setAttentionBasePos__12daNpc_Bms1_cF4cXyz */
// void daNpc_Bms1_c::setAttentionBasePos(cXyz) {
//     /* Nonmatching */
// }

// /* 00004820-00004900       .text getItemZoomPos__16ShopCam_action_cFf */
// void ShopCam_action_c::getItemZoomPos(float) {
//     /* Nonmatching */
// }

static actor_method_class l_daNpc_Bms1_Method = {
    (process_method_func)daNpc_Bms1_Create,
    (process_method_func)daNpc_Bms1_Delete,
    (process_method_func)daNpc_Bms1_Execute,
    (process_method_func)daNpc_Bms1_IsDelete,
    (process_method_func)daNpc_Bms1_Draw,
};

actor_process_profile_definition g_profile_NPC_BMS1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BMS1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bms1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BMS1_e,
    /* Actor SubMtd */ &l_daNpc_Bms1_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
