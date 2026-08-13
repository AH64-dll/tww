/**
 * d_a_npc_sarace.cpp
 * NPC - Loot the Sailor (Boating Course)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_sarace.h"
#include "d/actor/d_a_obj_barrel2.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_snap.h"
#include "math.h"

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

static daNpc_Sarace_HIO_c l_HIO;

/* 000000EC-00000198       .text __ct__18daNpc_Sarace_HIO_cFv */
daNpc_Sarace_HIO_c::daNpc_Sarace_HIO_c() {
    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0xFA0;
    mNpc.mMaxHeadY = 0x1770;
    mNpc.mMaxBackboneX = 0;
    mNpc.mMaxBackboneY = 0x1B58;
    mNpc.mMinHeadX = -0x7D0;
    mNpc.mMinHeadY = -0x1770;
    mNpc.mMinBackboneX = -0x7D0;
    mNpc.mMinBackboneY = -0x1B58;
    mNpc.mMaxTurnStep = 0x3E8;
    mNpc.mMaxHeadTurnVel = 0x640;
    mNpc.mAttnYOffset = 45.0f;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0f;
    m30 = 11.0f;
    m34 = 8.0f;
    mNo = -1;
}

static const int l_bck_ix_tbl[] = {0x9, 0x8, 0xB};
static const int l_bck_head_ix_tbl[] = {0x7, 0x6, 0xA};
static const int l_btp_ix_tbl[] = {0x14};

/* 00000198-00000328       .text nodeCallBack__FP7J3DNodei */

    /* Nonmatching */static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Sarace_c* i_this = (daNpc_Sarace_c*)model->getUserArea();
        if (i_this != NULL) {
            J3DJoint* joint = (J3DJoint*)node;
            u16 jointNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointNo));

            if (jointNo == i_this->m_jnt.getHeadJntNum()) {
                static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
                cXyz pos(24.0f, 14.0f, 0.0f);
                mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->m708);
                mDoMtx_XrotM(mDoMtx_stack_c::now, i_this->m_jnt.getHead_y());
                mDoMtx_ZrotM(mDoMtx_stack_c::now, -i_this->m_jnt.getHead_x());
                mDoMtx_stack_c::multVec(&pos, &i_this->m6FC);
            }
            else if (jointNo == i_this->m_jnt.getBackboneJntNum()) {
                mDoMtx_XrotM(mDoMtx_stack_c::now, i_this->m_jnt.getBackbone_y());
                mDoMtx_ZrotM(mDoMtx_stack_c::now, -i_this->m_jnt.getBackbone_x());
            }
            MTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jointNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 00000364-00000478       .text initTexPatternAnm__14daNpc_Sarace_cFb */

BOOL daNpc_Sarace_c::initTexPatternAnm(bool modify) {
    J3DModelData* modelData = mpMorf2->getModel()->getModelData();
    m_btp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Sarace", l_btp_ix_tbl[m740]);
    JUT_ASSERT(0xF9, m_btp != 0);
    BOOL ret = mBtpAnm.init(modelData, m_btp, 1, 2, 1.0f, 0, -1, modify, FALSE);
    if (ret == FALSE)
        return FALSE;
    else {
        mBtpFrame = 0;
        mTimer = 0;
        return TRUE;
    }
}

/* 00000478-00000504       .text playTexPatternAnm__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::playTexPatternAnm() {
    if (!cLib_calcTimer(&mTimer)) {
        if (mBtpFrame >= m_btp->getFrameMax()) {
            mBtpFrame -= m_btp->getFrameMax();
            mTimer = cM_rndF(100.0f) + 30.0f;
        }
        else {
            mBtpFrame++;
        }
    }
}

/* 00000504-0000060C       .text setAnm__14daNpc_Sarace_cFScf */

    void daNpc_Sarace_c::setAnm(s8 anmIdx, f32 morf) {
    static u32 a_play_mode_tbl[] = {
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
    };
    static f32 a_morf_frame_tbl[] = {8.0f, 8.0f, 8.0f};
    static f32 a_play_speed_tbl[] = {1.0f, 1.0f, 1.0f};

    if (morf < 0.0f) {
        morf = a_morf_frame_tbl[anmIdx];
    }
    if (anmIdx != m741 && m741 != -1) {
        m741 = anmIdx;
        dNpc_setAnm(mpMorf, a_play_mode_tbl[m741], morf, a_play_speed_tbl[m741], l_bck_ix_tbl[m741], -1, "Sarace");
        dNpc_setAnm(mpMorf2, a_play_mode_tbl[m741], morf, a_play_speed_tbl[m741], l_bck_head_ix_tbl[m741], -1, "Sarace");
    }
}

/* 0000060C-00000760       .text chkAttention__14daNpc_Sarace_cF4cXyzs */

    /* Nonmatching */BOOL daNpc_Sarace_c::chkAttention(cXyz pos, s16 angle) {
    cXyz sp10;
    f32 distXZ;

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 maxDist = l_HIO.mNpc.mMaxAttnDistXZ;
    s16 maxAngle = l_HIO.mNpc.mMaxAttnAngleY;
    sp10.x = player->current.pos.x - pos.x;
    sp10.z = player->current.pos.z - pos.z;
    distXZ = sp10.x * sp10.x + sp10.z * sp10.z;
    distXZ = std::sqrtf(distXZ);
    s16 atanAngle = cM_atan2s(sp10.x, sp10.z);
    if (m728 != 0) {
        maxDist += 40.0f;
        maxAngle += 0x71C;
    }
    s16 diff = atanAngle - angle;
    BOOL ret = FALSE;
    s16 angleDiff = abs(diff);
    if (maxAngle > angleDiff && maxDist > distXZ)
        ret = TRUE;
    return ret;
}

/* 00000760-000007D8       .text eventOrder__14daNpc_Sarace_cFv */

void daNpc_Sarace_c::eventOrder() {
    if (m742 == 3) {
        fopAcM_orderOtherEvent2(this, "SARACE_EXPCAM", 1, 0xFFFF);
    }
    else if (m742 == 1 || m742 == 2) {
        eventInfo.onCondition(1);
        if (m742 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000007D8-000008E8       .text checkOrder__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::checkOrder() {
    if (eventInfo.getCommand() == 2) {
        if (m742 == 3) {
            setAction(&daNpc_Sarace_c::event_endCheck_action, NULL);
            m742 = 0;
        }
    }
    else if (eventInfo.getCommand() == 1) {
        if (m742 == 1 || m742 == 2) {
            m742 = 0;
            m729 = 1;
        }
    }
}

/* 000008E8-00000A6C       .text next_msgStatus__14daNpc_Sarace_cFPUl */

    /* Nonmatching */u16 daNpc_Sarace_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
        case 0xFA1:
        case 0xFA2:
        case 0xFA5:
        case 0xFA7:
        case 0xFB1:
        case 0xFB2:
        case 0xFB4:
        case 0xFB5:
        case 0xFB7:
            (*pMsgNo)++;
            break;
        case 0xFB8:
            *pMsgNo = 0xFB3;
            break;
        case 0xFB3:
            *pMsgNo = 0xFA3;
            break;
        case 0xFA3:
            if (mpCurrMsg->mSelectNum == 0) {
                *pMsgNo = 0xFA4;
            }
            else if (mpCurrMsg->mSelectNum == 1) {
                if ((u16)dComIfGs_getRupee() < 0x1E) {
                    *pMsgNo = 0xFAF;
                }
                else {
                    g_dComIfG_gameInfo.play.mItemRupeeCount -= 0x1E;
                    dComIfGs_offEventBit(0x2820);
                    *pMsgNo = 0xFB0;
                }
            }
            else {
                if (dComIfGs_isEventBit(0x2808) == 0) {
                    dComIfGs_onEventBit(0x2808);
                    *pMsgNo = 0xFAD;
                }
                else {
                    *pMsgNo = 0xFAE;
                }
            }
            break;
        case 0xFA8:
            if (dComIfGs_isEventBit(0x2820)) {
                *pMsgNo = 0xFAA;
            }
            else {
                *pMsgNo = 0xFA9;
            }
            break;
        case 0xFAA:
            *pMsgNo = 0xFA9;
            break;
        case 0xFA9:
            *pMsgNo = 0xFA3;
            break;
        case 0xFA4:
        case 0xFA6:
        case 0xFAB:
        case 0xFAC:
        case 0xFAD:
        case 0xFAE:
        case 0xFAF:
        case 0xFB0:
        case 0xFB6:
            ret = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return ret;
}

/* 00000A6C-00000B50       .text getMsg__14daNpc_Sarace_cFv */
u32 daNpc_Sarace_c::getMsg() {
    u32 ret = 0;
    if (mMsgNo != 0) {
        if (mMsgNo == 0xFB4) {
            if (ship_race_result == 1) {
                mMsgNo = 0xFB7;
            }
            else if (ship_race_result == 3) {
                mMsgNo = 0xFB1;
            }
            else {
                dComIfGp_setMessageCountNumber(ship_race_rupee);
            }
        }
        ret = mMsgNo;
        mMsgNo = 0;
    }
    else {
        if (dComIfGs_isEventBit(0x2810) == 0) {
            dComIfGs_onEventBit(0x2810);
            ret = 0xFA1;
        }
        else if (dComIfGs_isEventBit(0x2840) == 0) {
            ret = 0xFA1;
        }
        else {
            ret = 0xFA2;
        }
    }
    return ret;
}

/* 00000B50-00000BEC       .text anmAtr__14daNpc_Sarace_cFUs */
void daNpc_Sarace_c::anmAtr(u16) {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnm(0, -1.0f);
            break;
        case 1:
            setAnm(1, l_HIO.m30);
            break;
        case 2:
            setAnm(2, l_HIO.m34);
            break;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xFF);
}

/* 00000BEC-00000E24       .text CreateInit__14daNpc_Sarace_cFv */
BOOL daNpc_Sarace_c::CreateInit() {
    m718 = current.angle.x;
    m71A = current.angle.y;
    m71C = current.angle.z;
    attention_info.flags = 0xA;
    gravity = -30.0f;

    setAction(&daNpc_Sarace_c::wait_action, NULL);

    m708.set(current.pos);
    m6FC.set(current.pos);
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(60.0f, 150.0f);
    m730 = 0;
    mEventCut.setActorInfo2("Sarace", this);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAD;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAD;
    set_mtx();
    mMsgNo = 0;
    mBarrelAId = -1;
    mBarrelBId = -1;
    setAnm(0, -1.0f);

    if (dComIfGp_getStartStagePoint() == 1 && dComIfGp_getStartStageRoomNo() == 0x30 && ship_race_result != 0) {
        m742 = 1;
        mMsgNo = 0xFB4;
        fopAcM_orderSpeakEvent(this);
    }

    mpMorf->play(&eyePos, 0, 0);
    mpMorf->calc();
    mpMorf2->play(NULL, 0, 0);
    mpMorf2->calc();
    return TRUE;
}

/* 00000E24-00000E68       .text setAttention__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::setAttention() {
    eyePos.set(m6FC.x, m6FC.y, m6FC.z);
    attention_info.position.set(m708.x, m708.y + l_HIO.mNpc.mAttnYOffset, m708.z);
}

/* 00000E68-00000FF4       .text lookBack__14daNpc_Sarace_cFv */

    /* Nonmatching */void daNpc_Sarace_c::lookBack() {
    cXyz srcPos(0.0f, 0.0f, 0.0f);
    cXyz* pDstPos = NULL;
    s16 defaultY = current.angle.y;
    bool param_6 = true;

    if (m743 < 3 && m743 >= 1) {
        if (m743 == 2) {
            m_jnt.setTrn();
            if (m728 == 0) {
                cXyz eyePosLocal = dNpc_playerEyePos(l_HIO.mNpc.m04);
                cLib_addCalcAngleS2(&current.angle.y, cLib_targetAngleY(&current.pos, &eyePosLocal), 4, 0x1800);
            }
        }
        if (m728 != 0) {
            cXyz eyePosLocal = dNpc_playerEyePos(l_HIO.mNpc.m04);
            pDstPos = &eyePosLocal;
            srcPos = current.pos;
            srcPos.y = eyePos.y;
        }
    }

    if (m_jnt.trnChk()) {
        param_6 = false;
    }
    else {
        m714 = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, pDstPos, srcPos, defaultY, l_HIO.mNpc.mMaxHeadTurnVel, param_6);
}

/* 00000FF4-00001024       .text wait01__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::wait01() {
    if (m729 != 0) {
        m743 = 2;
    }
    else if (m742 == 0) {
        m742 = 2;
    }
}

/* 00001024-000014B8       .text talk01__14daNpc_Sarace_cFv */

    void daNpc_Sarace_c::talk01() {
    if (fopNpc_npc_c::talk(1) == fopMsgStts_BOX_CLOSED_e) {
        m743 = 1;
        if (mCurrMsgNo == 0xFA4) {
            static cXyz create_pos[] = {
                cXyz(175875.0f, 50.0f, 276520.0f),
                cXyz(176030.0f, 50.0f, 278884.0f),
            };
            dComIfGp_event_onEventFlag(dEvtFlag_UNK8_e);
            m742 = 3;
            mBarrelAId = fopAcM_create(fpcNm_Obj_Barrel2_e, 0x17F0101, &create_pos[0], -1, NULL, NULL, -1, NULL);
            mBarrelBId = fopAcM_create(fpcNm_Obj_Barrel2_e, 0x7F0101, &create_pos[1], -1, NULL, NULL, -1, NULL);
        }
        else if (mCurrMsgNo == 0xFB0) {
            dComIfGs_onEventBit(0x2840);
            dComIfGp_setNextStage("Ocean", 1, 0, 0, 0.0f, 0, 1, 0);

            if (dComIfGs_getSelectItem(dItemBtn_X_e) != 1 && dComIfGs_getSelectItem(dItemBtn_Y_e) != 1 &&
                dComIfGs_getSelectItem(dItemBtn_Z_e) != 1) {
                dComIfGs_setSelectItem(dItemBtn_Y_e, 1);
                dComIfGp_setSelectItem(dItemBtn_Y_e);
            }
            setAction(&daNpc_Sarace_c::dummy_action, NULL);
        }
        else {
            dComIfGp_event_onEventFlag(dEvtFlag_UNK8_e);
            ship_race_result = 0;
            ship_race_rupee = 0;
            setAnm(0, -1.0f);
        }
        m729 = 0;
    }
    else if (mCurrMsgNo == 0xFB6) {
        if (dComIfGp_checkMesgSendButton() == 1) {
            dComIfGp_setItemRupeeCount(ship_race_rupee);
            u8 reg = dComIfGs_getEventReg(0xAAFF);
            u8 newReg = reg + 1 > 0xC ? 0xC : reg + 1;
            dComIfGs_setEventReg(0xAAFF, newReg);
            if (reg != newReg) {
                dComIfGs_onEventBit(0x2820);
            }
        }
    }
}

/* 000014B8-000014E0       .text dummy_action__14daNpc_Sarace_cFPv */
BOOL daNpc_Sarace_c::dummy_action(void*) {
    if (m746 == 0) {
        m743 = 1;
        m746++;
    }
    return TRUE;
}

/* 000014E0-000015BC       .text wait_action__14daNpc_Sarace_cFPv */

    BOOL daNpc_Sarace_c::wait_action(void*) {
    if (m746 == 0) {
        m743 = 1;
        m746++;
    } else if (m746 != -1) {
        s16 angle = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        m728 = chkAttention(current.pos, angle);
        switch (m743) {
            case 1:
                wait01();
                break;
            case 2:
                talk01();
                break;
        }
        lookBack();
        setAttention();
    }
    return TRUE;
}

/* 000015BC-0000173C       .text event_endCheck_action__14daNpc_Sarace_cFPv */

    BOOL daNpc_Sarace_c::event_endCheck_action(void*) {
    if (m746 == 0) {
        m746++;
    } else if (m746 != -1) {
        if (dComIfGp_evmng_endCheck("SARACE_EXPCAM")) {
            mMsgNo = 0xFA7;
            dComIfGp_event_onEventFlag(dEvtFlag_UNK8_e);
            m742 = 1;
            setAction(&daNpc_Sarace_c::wait_action, NULL);

            fopAc_ac_c* actorA = fopAcM_SearchByID(mBarrelAId);
            fopAc_ac_c* actorB = fopAcM_SearchByID(mBarrelBId);
            if (actorA != NULL) {
                ((daObjBarrel2::Act_c*)actorA)->m475 = 1;
            }
            if (actorB != NULL) {
                ((daObjBarrel2::Act_c*)actorB)->m475 = 1;
            }
        }
    }
    return TRUE;
}

/* 0000173C-000017E0       .text set_mtx__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::set_mtx() {
    J3DModel* model1 = mpMorf->getModel();
    J3DModel* model2 = mpMorf2->getModel();

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model1->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    model2->setBaseTRMtx(model1->getAnmMtx(m_jnt.getHeadJntNum()));
    mpMorf2->calc();
}

/* 000017E0-00001938       .text _draw__14daNpc_Sarace_cFv */

    BOOL daNpc_Sarace_c::_draw() {
    J3DModel* model1 = mpMorf->getModel();
    J3DModel* model2 = mpMorf2->getModel();
    J3DModelData* modelData = model2->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model1, &tevStr);
    g_env_light.setLightTevColorType(model2, &tevStr);
    mBtpAnm.entry(modelData, mBtpFrame);
    mpMorf->entryDL();
    mpMorf2->entryDL();
    mBtpAnm.remove(modelData);

    cXyz shadowPos;
    shadowPos.set(current.pos.x, current.pos.y + 130.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(mShadowId, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f, current.pos.y,
                                    mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr);
    if (mShadowId != 0) {
        dComIfGd_addRealShadow(mShadowId, mpMorf2->getModel());
    }
    dSnap_RegistFig(0x82, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00001938-00001A68       .text _execute__14daNpc_Sarace_cFv */
BOOL daNpc_Sarace_c::_execute() {
    m_jnt.setParam(l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY, l_HIO.mNpc.mMinBackboneX,
                   l_HIO.mNpc.mMinBackboneY, l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
                   l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY, l_HIO.mNpc.mMaxTurnStep);
    playTexPatternAnm();
    mpMorf->play(NULL, 0, 0);
    mpMorf2->play(NULL, 0, 0);
    checkOrder();
    (this->*mAction)(NULL);
    mEventCut.cutProc();
    eventOrder();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    set_mtx();
    setCollision(60.0f, 150.0f);
    return TRUE;
}

/* 00001A68-00001AE0       .text _delete__14daNpc_Sarace_cFv */
BOOL daNpc_Sarace_c::_delete() {
    dComIfG_resDelete(&mPhs, "Sarace");
    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    if (l_HIO.mNo >= 0) {
        mDoHIO_root.m_subroot.deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return TRUE;
}

/* 00001AE0-00001B00       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->CreateHeap();
}

/* 00001B00-00001D1C       .text _create__14daNpc_Sarace_cFv */

cPhs_State daNpc_Sarace_c::_create() {
    fopAcM_ct_Retail(this, daNpc_Sarace_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Sarace");
    if (state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CallbackCreateHeap, 0x2760)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_createChild("船乗りレースゲーム専用", &l_HIO);
        }
        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }
    return state;
}

/* 000020CC-00002498       .text CreateHeap__14daNpc_Sarace_cFv */

    /* Nonmatching */BOOL daNpc_Sarace_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Sarace", 0xE);
    JUT_ASSERT(0x3F0, modelData != 0);
    mpMorf = new mDoExt_McaMorf(modelData, NULL, NULL,
                                (J3DAnmTransform*)dComIfG_getObjectRes("Sarace", 0x9),
                                J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    m_jnt.setHeadJntNum(modelData->getJointTree().getJointName()->getIndex("head"));
    JUT_ASSERT(0x400, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointTree().getJointName()->getIndex("backbone"));
    JUT_ASSERT(0x402, m_jnt.getBackboneJntNum() >= 0);

    J3DModelData* headModelData = (J3DModelData*)dComIfG_getObjectRes("Sarace", 0x11);
    JUT_ASSERT(0x40A, headModelData != 0);
    mpMorf2 = new mDoExt_McaMorf(headModelData, NULL, NULL,
                                 (J3DAnmTransform*)dComIfG_getObjectRes("Sarace", 0x7),
                                 J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);
    if (mpMorf2 == NULL || mpMorf2->getModel() == NULL)
        return FALSE;

    m740 = 0;
    if (initTexPatternAnm(false) == FALSE)
        return FALSE;

    for (u16 jntIdx = 0; jntIdx < modelData->getJointNum(); jntIdx++) {
        if (jntIdx == m_jnt.getHeadJntNum() || jntIdx == m_jnt.getBackboneJntNum()) {
            mpMorf->getModel()->getModelData()->getJointTree().getJointNodePointer(jntIdx)->setCallBack(nodeCallBack);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 0.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                 fopAcM_GetSpeed_p(this), NULL, NULL);
    return TRUE;
}

/* 00002498-000024B8       .text daNpc_Sarace_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Sarace_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_create();
}

/* 000024B8-000024D8       .text daNpc_Sarace_Delete__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Delete(daNpc_Sarace_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_delete();
}

/* 000024D8-000024F8       .text daNpc_Sarace_Execute__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Execute(daNpc_Sarace_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_execute();
}

/* 000024F8-00002518       .text daNpc_Sarace_Draw__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Draw(daNpc_Sarace_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_draw();
}

/* 00002518-00002520       .text daNpc_Sarace_IsDelete__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_IsDelete(daNpc_Sarace_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Sarace_Method = {
    (process_method_func)daNpc_Sarace_Create,
    (process_method_func)daNpc_Sarace_Delete,
    (process_method_func)daNpc_Sarace_Execute,
    (process_method_func)daNpc_Sarace_IsDelete,
    (process_method_func)daNpc_Sarace_Draw,
};

actor_process_profile_definition g_profile_NPC_SARACE = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_SARACE_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Sarace_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_SARACE_e,
    /* Actor SubMtd */ &l_daNpc_Sarace_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
