/**
 * d_a_npc_kg1.cpp
 * NPC - Salvatore (Squid-Hunt/"Sploosh Kaboom" Minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kg1.h"
#include "d/actor/d_a_mgameboard.h"
#include "d/actor/d_a_player.h"
#include "m_Do/m_Do_controller_pad.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_lib.h"
#include "d/d_cc_d.h"
#include "d/d_snap.h"

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
        /* Radius */ 40.0f,
        /* Height */ 160.0f,
    }},
};


/* 000000EC-000001E0       .text __ct__15daNpc_Kg1_HIO_cFv */
daNpc_Kg1_HIO_c::daNpc_Kg1_HIO_c() {
    mNo = -1;
    field_0x8 = -1;
    mHio[0].m04 = 0.0f;
    mHio[0].mMaxHeadX = 0x9C4;
    mHio[0].mMaxHeadY = 0x1B58;
    mHio[0].mMaxBackboneX = 0x7D0;
    mHio[0].mMaxBackboneY = 0x1F40;
    mHio[0].mMinHeadX = -0x9C4;
    mHio[0].mMinHeadY = -0x1B58;
    mHio[0].mMinBackboneX = -0x7D0;
    mHio[0].mMinBackboneY = -0x1F40;
    mHio[0].mMaxTurnStep = 0x3E8;
    mHio[0].mMaxHeadTurnVel = 0x7D0;
    mHio[0].mAttnYOffset = 35.0f;
    mHio[0].mMaxAttnAngleY = 0x4000;
    mHio[0].m22 = 0;
    mHio[0].mMaxAttnDistXZ = 400.0f;
    field_0xC = 0;
    field_0x38 = 0;
    field_0x39 = 0;
}

/* 0000203C-000021B4       .text __ct__11daNpc_Kg1_cFv */
daNpc_Kg1_c::daNpc_Kg1_c() {}

static daNpc_Kg1_HIO_c l_HIO;
const char daNpc_Kg1_c::m_arcname[] = "Kg";
cXyz daNpc_Kg1_c::m_camera_ctr(-200.0f, 140.0f, 85.0f);
cXyz daNpc_Kg1_c::m_camera_eye(-117.0f, 92.0f, 344.0f);
const f32 daNpc_Kg1_c::m_camera_fovy = 40.0f;

/* 000001E0-00000428       .text daNpc_Kg1_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Kg1_nodeCallBack(J3DNode* node, int param) {
    if (param == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Kg1_c* actor = (daNpc_Kg1_c*)model->getUserArea();
        u16 jnt_no_raw = ((J3DJoint*)node)->getJntNo();
        int jnt_no = jnt_no_raw;
        mDoMtx_stack_c::copy(model->getAnmMtx(jnt_no));
        if (jnt_no == actor->m_jnt.getHeadJntNum()) {
            mDoMtx_XrotM(mDoMtx_stack_c::now, actor->m_jnt.getHead_y());
            mDoMtx_ZrotM(mDoMtx_stack_c::now, -actor->m_jnt.getHead_x());
            static cXyz l_head_pos(24.0f, 5.0f, 0.0f);
            static cXyz l_eye_pos(24.0f, -16.0f, 0.0f);
            mDoMtx_stack_c::multVec(&l_head_pos, &actor->getAttentionBasePos());
            mDoMtx_XrotM(mDoMtx_stack_c::now, actor->m_jnt.getHead_y());
            mDoMtx_ZrotM(mDoMtx_stack_c::now, -actor->m_jnt.getHead_x());
            mDoMtx_stack_c::multVec(&l_eye_pos, &actor->getEyePos());
            mDoMtx_stack_c::multVec(&l_head_pos, &actor->attention_info.position);
            actor->attention_info.position.y += l_HIO.mHio[0].mAttnYOffset;
        }
        if (jnt_no == actor->m_jnt.getBackboneJntNum()) {
            mDoMtx_XrotM(mDoMtx_stack_c::now, actor->m_jnt.getBackbone_y());
            mDoMtx_ZrotM(mDoMtx_stack_c::now, -actor->m_jnt.getBackbone_x());
        }
        model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
        if (jnt_no == 8) {
            mDoMtx_stack_c::transM(23.467f, -22.26f, -47.1f);
            mDoMtx_stack_c::XYZrotM(0x1F4B, -0x4F00, 0x1F4B);
            actor->m6C4->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
    return 1;
}

/* 00000464-00000688       .text lookBack__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::lookBack() {
    cXyz dist = dComIfGp_getPlayer(0)->current.pos - current.pos;
    f32 dist_xz = dist.absXZ();
    cXyz* p_look_pos = NULL;
    if (mEventCut.getAttnFlag()) {
        m_jnt.setTrn();
        cXyz attn_pos = mEventCut.getAttnPos();
        p_look_pos = &attn_pos;
        m731 = 1;
    } else if (m74D == 8) {
        cXyz cam_eye = m_camera_eye;
        p_look_pos = &cam_eye;
    } else if (dist_xz < l_HIO.mHio[0].mMaxAttnDistXZ) {
        cXyz player_eye = dNpc_playerEyePos(l_HIO.mHio[0].m04);
        p_look_pos = &player_eye;
        m731 = chkAttention();
    } else {
        m731 = 0;
    }
    if (mEventCut.getAttnFlag()) {
        s16 turn_speed = l_HIO.mHio[0].mMaxHeadTurnVel;
        s16 turn_speed2 = m72E;
        if (turn_speed2 != 0) {
            turn_speed = turn_speed2;
        }
        cLib_addCalcAngleS2(&m72E, turn_speed, 4, 0x800);
    } else {
        m72E = 0;
    }
    cXyz eye_pos = eyePos;
    m_jnt.lookAtTarget(&current.angle.y, p_look_pos, eye_pos, current.angle.y, m72E, 1);
}

/* 00000688-000007D8       .text chkAttention__11daNpc_Kg1_cFv */
s32 daNpc_Kg1_c::chkAttention() {
    cXyz dist = dComIfGp_getPlayer(0)->current.pos - current.pos;
    f32 dist_xz = dist.absXZ();
    if (dist_xz < l_HIO.mHio[0].mMaxAttnDistXZ) {
        f32 dx = dComIfGp_getPlayer(0)->current.pos.x - current.pos.x;
        f32 dz = dComIfGp_getPlayer(0)->current.pos.z - current.pos.z;
        s16 angle = cM_atan2s(dx, dz) - (current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y());
        if (abs(angle) < l_HIO.mHio[0].mMaxAttnAngleY) {
            return 1;
        }
    }
    return 0;
}

static const int l_btp_ix_tbl[] = {9, 11, 13, 12};

/* 000007D8-000008D8       .text initTexPatternAnm__11daNpc_Kg1_cFib */
BOOL daNpc_Kg1_c::initTexPatternAnm(int param_2, bool param_3) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_eye_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname, l_btp_ix_tbl[param_2]);
    JUT_ASSERT(0x1CC, m_eye_tex_pattern != 0);
    BOOL ret = m6F8.init(modelData, m_eye_tex_pattern, 1, 2, 1.0f, 0, -1, param_3, FALSE);
    if (ret == FALSE) {
        return FALSE;
    }
    m720 = 0;
    m72C = 0;
    return TRUE;
}

/* 000008D8-00000944       .text playTexPatternAnm__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::playTexPatternAnm() {
    if (!cLib_calcTimer(&m72C)) {
        if (m720 >= m_eye_tex_pattern->getFrameMax()) {
            m720 -= m_eye_tex_pattern->getFrameMax();
            m72C = 0x78;
        } else {
            m720++;
        }
    }
}

/* 00000944-000009E8       .text set_mtx__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::set_mtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    m6C4->setBaseScale(scale);
}

/* 000009E8-00000A08       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Kg1_c*)i_this)->CreateHeap();
}

/* 00000A08-00000D34       .text CreateHeap__11daNpc_Kg1_cFv */
BOOL daNpc_Kg1_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 5);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, 0x11),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x11020022
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x223, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone2"));
    JUT_ASSERT(0x228, m_jnt.getBackboneJntNum() >= 0);
    if (!initTexPatternAnm(3, false)) {
        return FALSE;
    }
    initTexPatternAnm(0, true);
    m6C4 = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectRes(m_arcname, 6), 0x80000, 0x11020022);
    if (m6C4 == NULL) {
        return FALSE;
    }
    if (!mBtpAnm.init((J3DModelData*)dComIfG_getObjectRes(m_arcname, 6), (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname, 0xA), 1, 2, 1.0f, 0, -1, false, FALSE)) {
        return FALSE;
    }
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == (u8)m_jnt.getHeadJntNum() || i == (u8)m_jnt.getBackboneJntNum() || i == 8) {
            modelData->getJointNodePointer(i)->setCallBack(daNpc_Kg1_nodeCallBack);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                 fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    return TRUE;
}

/* 00000D34-00000EF0       .text CreateInit__11daNpc_Kg1_cFv */
cPhs_State daNpc_Kg1_c::CreateInit() {
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(60.0f, 150.0f);
    gravity = -18.0f;
    mEventCut.setActorInfo2((char*)m_arcname, this);
    set_mtx();
    m72E = 0;
    m730 = 0;
    m731 = 0;
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    wait_action_init();
    if (l_HIO.field_0x8 < 0) {
        l_HIO.mNo = mDoHIO_createChild("\212C\220\355\203Q\201[\203\200\211\256", (JORReflexible*)&l_HIO);
    }
    l_HIO.field_0x8++;
    attention_info.flags = 0xA;
    m784 = dComIfGp_evmng_getEventIdx("MINIGAME_START", 0xFF);
    m786 = dComIfGp_evmng_getEventIdx("MINIGAME_END", 0xFF);
    m788 = dComIfGp_evmng_getEventIdx("KAISEN_GETITEM", 0xFF);
    m74E = 0;
    m74D = 2;
    setAnm();
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    m750 = 1;
    mEyePos = current.pos;
    return cPhs_COMPLEATE_e;
}

/* 00000EF0-00000FE8       .text eventOrder__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::eventOrder() {
    if (m732 == 2 || m732 == 1) {
        eventInfo.onCondition(1);
        if (m732 == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (m732 == 3) {
        fopAcM_orderOtherEventId(this, m784, 0xFF, 0xFFFF, 0, 1);
        eventInfo.onCondition(2);
    } else if (m732 == 4) {
        fopAcM_orderOtherEventId(this, m786, 0xFF, 0xFFFF, 0, 1);
        eventInfo.onCondition(2);
    } else if (m732 == 5) {
        fopAcM_orderOtherEventId(this, m788, 0xFF, 0xFFFF, 0, 1);
        eventInfo.onCondition(2);
    }
}

/* 00000FE8-000010C4       .text checkOrder__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(m784) && m732 == 3) {
            m732 = 0;
        }
        if (dComIfGp_evmng_endCheck(m784)) {
            m732 = 0;
        }
        if (dComIfGp_evmng_startCheck(m788) && m732 == 5) {
            m732 = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (m732 == 2 || m732 == 1) {
            m730 = 1;
        }
    }
}

/* 000010C4-00001188       .text kg1_talk_camera__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::kg1_talk_camera() {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (m751 && camera != NULL) {
        camera->mCamera.Stay();
        camera->mCamera.Set(m_camera_ctr, m_camera_eye, m_camera_fovy, 0);
        camera->mCamera.Reset();
        camera->mCamera.SetTrimSize(1);
    }
}

/* 00001188-000011D4       .text wait_action_init__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::wait_action_init() {
    clr_seq_flag();
    mAction = &daNpc_Kg1_c::wait_action;
}

/* 000011D4-00001858       .text wait_action__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::wait_action() {
    int staffIdx = dComIfGp_evmng_getMyStaffId("Kg1", NULL, 0);
    s16 procName = fpcNm_MGBOARD_e;
    daMgBoard_c* mgBoard = (daMgBoard_c*)fopAcIt_Judge(fpcSch_JudgeForPName, &procName);
    switch (mWaitMode) {
    case 0:
        m751 = 0;
        m_jnt.mbHeadLock = true;
        m_jnt.mbBackBoneLock = true;
        if (mgBoard != NULL) {
            mgBoard->clrGInfoDraw();
        }
        clr_seq_flag();
        m732 = (m731 != 0) ? 1 : 0;
        if (m730 != 0) {
            mWaitMode = 1;
            mBtpAnm.setFrame(0.0f);
            /* fallthrough */
        } else {
            break;
        }
    case 1: {
        u16 talkRet = talk(1);
        if (mCurrMsgNo < 0x1D56 && m74D == 4) {
            m_jnt.mbHeadLock = false;
        } else {
            m_jnt.mbHeadLock = true;
        }
        if (mCurrMsgNo == 0x1D5B) {
            m750 = 0;
        } else if ((mCurrMsgNo == 0x1D5C || mCurrMsgNo == 0x1D57) && talkRet == 6) {
            m750 = 1;
        }
        if (talkRet == 0x12) {
            dComIfGp_event_onHindFlag(8);
            if (m772) {
                m732 = 3;
                mWaitMode = 2;
                m751 = 0;
            } else {
                m74D = 2;
                mWaitMode = 0;
            }
            m730 = 0;
        }
        break;
    }
    case 2:
        m751 = 0;
        if (mgBoard != NULL) {
            mgBoard->reqStartGame();
            mgBoard->setGInfoDraw();
        }
        mWaitMode = 3;
        fopAcM_seStart(this, 0x8A8, 0);
        mEndGameTimer = 0x3C;
        break;
    case 3:
        if (m732 == 0 && mgBoard != NULL) {
            m774 = mgBoard->checkEndGame() != 0;
            if (m774 && !cLib_calcTimer(&mEndGameTimer)) {
                m773 = mgBoard->checkClearGame();
                if (m773) {
                    mGameBoardScore = mgBoard->getScore();
                } else {
                    m74D = 4;
                }
                mEndGameTimer = 0x5A;
                m778 = 0;
                mWaitMode = 4;
                dComIfGp_event_offHindFlag(3);
                m779 = 1;
            }
        }
        break;
    case 4:
        if (CPad_CHECK_TRIG_A(0)) {
            m779 = 0;
            dComIfGs_onEventBit(0x2540);
            if (mgBoard != NULL) {
                mgBoard->mbForceEnd = 1;
            }
            if (mgBoard != NULL) {
                mgBoard->clrGInfoDraw();
            }
            mWaitMode = 5;
            m732 = 2;
            dComIfGp_evmng_cutEnd(staffIdx);
            dComIfGp_event_onHindFlag(8);
        }
        break;
    case 5:
        if (m730 == 1) {
            m751 = 1;
            if (talk(1) == 0x12) {
                m732 = 0;
                dComIfGp_event_onHindFlag(8);
                m730 = 0;
                if (m773) {
                    m732 = 5;
                    mWaitMode = 6;
                } else if (m772) {
                    m732 = 3;
                    mWaitMode = 2;
                } else {
                    m74D = 2;
                    mWaitMode = 0;
                }
            }
        }
        break;
    case 6: {
        u8 item_tbl[3] = {0x07, 0xCC, 0x05};
        if (m732 == 0) {
            m751 = 0;
            m77C = fopAcM_createItemForPresentDemo(&current.pos, item_tbl[dComIfGs_getEventReg(0xFE07) - 1], 0, -1,
                                                   fopAcM_GetRoomNo(this));
            if (m77C != fpcM_ERROR_PROCESS_ID_e) {
                dComIfGp_event_setItemPartnerId(m77C);
            }
            mWaitMode = 7;
        }
        break;
    }
    case 7:
        if (dComIfGp_evmng_endCheck(m788)) {
            dComIfGp_event_onHindFlag(8);
            m775 = 1;
            m732 = 2;
            mWaitMode = 8;
            m74D = 0xB;
        }
        break;
    case 8:
        m_jnt.mbBackBoneLock = true;
        m_jnt.mbHeadLock = true;
        if (m730 == 1) {
            m751 = 1;
            if (talk(1) == 0x12) {
                dComIfGp_event_onHindFlag(8);
                m730 = 0;
                m732 = 0;
                if (m777) {
                    m732 = 5;
                    mWaitMode = 9;
                } else {
                    m74D = 2;
                    mWaitMode = 0;
                }
            }
        }
        break;
    case 9: {
        u8 item_tbl[2] = {0xF1, 0x06};
        if (m732 == 0) {
            m751 = 0;
            u8 idx = dComIfGs_getEventReg(0xFF07) - 1;
            if (idx > 1) {
                idx = 1;
            }
            m77C = fopAcM_createItemForPresentDemo(&current.pos, item_tbl[idx], 0, -1, fopAcM_GetRoomNo(this));
            if (m77C != fpcM_ERROR_PROCESS_ID_e) {
                dComIfGp_event_setItemPartnerId(m77C);
            }
            mWaitMode = 0xA;
        }
        break;
    }
    case 10:
        if (dComIfGp_evmng_endCheck(m788)) {
            dComIfGp_event_onHindFlag(8);
            m776 = 1;
            m732 = 2;
            mWaitMode = 0xB;
        }
        break;
    case 11:
        if (m730 == 1) {
            m751 = 1;
            if (talk(1) == 0x12) {
                dComIfGp_event_onHindFlag(8);
                m732 = 0;
                m730 = 0;
                mWaitMode = 0;
                m74D = 2;
            }
        }
        break;
    }
    kg1_talk_camera();
}

/* 00001858-00001878       .text clr_seq_flag__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::clr_seq_flag() {
    m772 = 0;
    m773 = 0;
    m774 = 0;
    m775 = 0;
    m776 = 0;
    m777 = 0;
}

/* 00001878-000019B4       .text getMsg__11daNpc_Kg1_cFv */
u32 daNpc_Kg1_c::getMsg() {
    u32 msgNo;
    if (m774) {
        if (m773) {
            if (m775) {
                if (!m776) {
                    if (dComIfGs_getEventReg(0xBEFF) > mGameBoardScore) {
                        dComIfGs_onEventBit(0xE04);
                        dComIfGs_setEventReg(0xBEFF, mGameBoardScore);
                        u8 reg = dComIfGs_getEventReg(0xFF07);
                        if (reg < 3) {
                            reg++;
                            dComIfGs_setEventReg(0xFF07, reg);
                        }
                        m777 = 1;
                        msgNo = 0x1D63;
                        goto out;
                    }
                    msgNo = 0x1D64;
                    goto out;
                }
            }
            if (m775 && m776) {
                msgNo = 0x1D64;
                goto out;
            }
            msgNo = 0x1D5F;
            goto out;
        }
        msgNo = 0x1D5D;
        goto out;
    }
    if (m770 == 0) {
        msgNo = 0x1D4D;
        goto out;
    } else {
        msgNo = 0x1D4E;
        goto out;
    }
out:
    return msgNo;
}

/* 000019B4-00001C7C       .text next_msgStatus__11daNpc_Kg1_cFPUl */
u16 daNpc_Kg1_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_ENDS_e;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (*pMsgNo) {
    case 0x1D4D:
        if (!dComIfGs_isEventBit(0xE04)) {
            *pMsgNo = 0x1D52;
        } else if (dLib_getIplDaysFromSaveTime() < 4) {
            *pMsgNo = 0x1D4F;
        } else if (dComIfGs_isTmpBit(0x101)) {
            *pMsgNo = 0x1D50;
        } else {
            dComIfGs_onTmpBit(0x101);
            *pMsgNo = 0x1D51;
        }
        m770 = 1;
        break;
    case 0x1D4E:
    case 0x1D4F:
    case 0x1D50:
    case 0x1D51:
        *pMsgNo = 0x1D52;
        break;
    case 0x1D52:
    case 0x1D5E:
        clr_seq_flag();
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            if (dComIfGp_getItemRupeeCount() < 0xA) {
                *pMsgNo = 0x1D54;
            } else {
                m74D = 1;
                dComIfGs_setRupee(dComIfGs_getRupee() - 10);
                m751 = 1;
                m_jnt.mbHeadLock = true;
                cXyz pos(0.0f, 0.0f, 250.0f);
                player->setPlayerPosAndAngle(&pos, 0x2000);
                *pMsgNo = 0x1D55;
            }
            break;
        case 1:
            *pMsgNo = 0x1D53;
            break;
        }
        break;
    case 0x1D55:
        *pMsgNo = (m771 != 0) ? 0x1D5C : 0x1D56;
        m772 = 1;
        break;
    case 0x1D56:
    case 0x1D57:
    case 0x1D58:
    case 0x1D59:
    case 0x1D5D:
        (*pMsgNo)++;
        break;
    case 0x1D5A:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *pMsgNo = 0x1D5C;
            break;
        case 1:
            *pMsgNo = 0x1D5B;
            break;
        }
        break;
    case 0x1D5B:
        *pMsgNo = 0x1D57;
        break;
    case 0x1D5F: {
        u8 count = dComIfGs_getEventReg(0xFE07);
        switch (count) {
        case 0:
            *pMsgNo = 0x1D60;
            break;
        case 1:
            *pMsgNo = 0x1D61;
            break;
        default:
            *pMsgNo = 0x1D62;
            break;
        }
        if (count < 3) {
            count++;
        }
        dComIfGs_setEventReg(0xFE07, count);
        break;
    }
    case 0x1D5C:
        m771 = 1;
        ret = 0x10;
        break;
    default:
        ret = 0x10;
        break;
    }
    return ret;
}

static const u8 anm_atr[] = { 0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };

/* 00001C7C-00001CB8       .text anmAtr__11daNpc_Kg1_cFUs */
void daNpc_Kg1_c::anmAtr(u16 i_msgStatus) {
    if (i_msgStatus == 6) {
        u8 anime = dComIfGp_getMesgAnimeAttrInfo();
        if (anime < 9) {
            m74D = anm_atr[anime];
            dComIfGp_clearMesgAnimeAttrInfo();
        }
    }
}

/* 00001CB8-00001E60       .text daNpc_Kg1_bcks_setAnm__FPCcP14mDoExt_McaMorfPScPScPScPCiPC14dLib_anm_prm_c */
void daNpc_Kg1_bcks_setAnm(const char* arcName, mDoExt_McaMorf* morf, s8* pBckIdx, s8* pPrmIdx, s8* pOldPrmIdx,
                           const int* bcksTbl, const dLib_anm_prm_c* anmPrmTbl) {
    if (*pOldPrmIdx != *pPrmIdx && anmPrmTbl[*pPrmIdx].mAnmIdx != -1) {
        *pBckIdx = anmPrmTbl[*pPrmIdx].mAnmIdx;
        J3DAnmTransform* bck = (J3DAnmTransform*)dComIfG_getObjectRes(arcName, bcksTbl[*pBckIdx]);
        morf->setAnm(bck, anmPrmTbl[*pPrmIdx].mLoopMode, anmPrmTbl[*pPrmIdx].mMorf,
                     anmPrmTbl[*pPrmIdx].mPlaySpeed, 0.0f, -1.0f, NULL);
        if (anmPrmTbl[*pPrmIdx].mPlaySpeed < 0.0f) {
            morf->setFrame(morf->getEndFrame());
        }
    }
    *pOldPrmIdx = *pPrmIdx;
    if (morf->isStop()) {
        if (anmPrmTbl[*pPrmIdx].mNextPrmIdx != -1 && anmPrmTbl[*pPrmIdx].mLoopMode == J3DFrameCtrl::EMode_NONE) {
            *pPrmIdx = anmPrmTbl[*pPrmIdx].mNextPrmIdx;
        }
    }
}

static const int a_anm_bck_tbl[] = {0x11, 0x1A, 0x16, 0x19, 0x14, 0x12, 0x13, 0x15, 0x17, 0x18};
static const s16 a_anm_btp_tbl[] = {0, 0, 0, 0, 1, 0, 1, 1, 2, 3, 0, 0};

/* 00001E60-00001F8C       .text setAnm__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::setAnm() {
    dLib_anm_prm_c l_anm_prm_tbl[12] = {
        { -1, -1, 0, 0.0f, 0.0f, 0 },
        { 0, -1, 0, 8.0f, 1.0f, 2 },
        { 1, -1, 0, 8.0f, 1.0f, 2 },
        { 2, -1, 0, 8.0f, 1.0f, 2 },
        { 3, -1, 0, 8.0f, 1.0f, 2 },
        { 4, 3, 0, 8.0f, 1.0f, 0 },
        { 5, -1, 0, 8.0f, 1.0f, 2 },
        { 6, -1, 0, 8.0f, 1.0f, 2 },
        { 7, -1, 0, 6.0f, 1.0f, 2 },
        { 8, -1, 0, 6.0f, 1.0f, 2 },
        { 9, 8, 0, 8.0f, 1.0f, 0 },
        { 4, 3, 0, 8.0f, -1.0f, 0 },
    };
    if (m74D != m74E) {
        initTexPatternAnm(a_anm_btp_tbl[m74D], 1);
    }
    if (m74C == 4 || m74C == 2 || m74C == 5 || m74C == 6 || m74C == 7 || m74C == 8 || m74C == 9) {
        m74F = 1;
        if (m74C == 9 && mpMorf->getFrame() == 31.0f) {
            mBtpAnm.setFrame(1.0f);
        }
    } else {
        m74F = 0;
    }
    daNpc_Kg1_bcks_setAnm(m_arcname, mpMorf, &m74C, &m74D, &m74E, a_anm_bck_tbl, l_anm_prm_tbl);
}

/* 00001F8C-00001FAC       .text daNpc_Kg1Create__FPv */
static cPhs_State daNpc_Kg1Create(void* i_this) {
    return ((daNpc_Kg1_c*)i_this)->_create();
}

/* 00001FAC-0000203C       .text _create__11daNpc_Kg1_cFv */
cPhs_State daNpc_Kg1_c::_create() {
    fopAcM_ct(this, daNpc_Kg1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, m_arcname);
    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x10000) != 0) {
            return CreateInit();
        }
        state = cPhs_ERROR_e;
    }
    return state;
}

/* 00002480-0000250C       .text daNpc_Kg1Delete__FPv */
static BOOL daNpc_Kg1Delete(void* i_this) {
    daNpc_Kg1_c* self = static_cast<daNpc_Kg1_c*>(i_this);
    dComIfG_resDelete(&self->mPhs, daNpc_Kg1_c::m_arcname);
    if (self->heap != NULL && self->mpMorf != NULL) {
        self->mpMorf->stopZelAnime();
    }
    if (l_HIO.field_0x8 >= 0) {
        l_HIO.field_0x8--;
        if (l_HIO.field_0x8 < 0) {
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return TRUE;
}

/* 0000250C-00002648       .text daNpc_Kg1Execute__FPv */
static BOOL daNpc_Kg1Execute(void* i_this) {
    daNpc_Kg1_c* self = static_cast<daNpc_Kg1_c*>(i_this);
    self->m_jnt.setParam(l_HIO.mHio[0].mMaxBackboneX, l_HIO.mHio[0].mMaxBackboneY,
                         l_HIO.mHio[0].mMinBackboneX, l_HIO.mHio[0].mMinBackboneY,
                         l_HIO.mHio[0].mMaxHeadX, l_HIO.mHio[0].mMaxHeadY,
                         l_HIO.mHio[0].mMinHeadX, l_HIO.mHio[0].mMinHeadY,
                         l_HIO.mHio[0].mMaxTurnStep);
    self->checkOrder();
    (self->*self->mAction)();
    self->eventOrder();
    self->playTexPatternAnm();
    self->setAnm();
    if (self->m750) {
        self->mpMorf->play(NULL, 0, 0);
    }
    self->mObjAcch.CrrPos(*dComIfG_Bgsp());
    self->setCollision(60.0f, 150.0f);
    self->attention_info.position.set(self->current.pos.x, self->current.pos.y + 190.0f, self->current.pos.z);
    self->eyePos.set(self->current.pos.x, self->current.pos.y + 150.0f, self->current.pos.z);
    self->lookBack();
    self->set_mtx();
    return 0;
}

/* 00002648-000027CC       .text daNpc_Kg1Draw__FPv */
static BOOL daNpc_Kg1Draw(void* i_this) {
    daNpc_Kg1_c* self = static_cast<daNpc_Kg1_c*>(i_this);
    dSnap_RegistFig(0x81, (fopAc_ac_c*)i_this, 1.0f, 1.0f, 1.0f);
    J3DModelData* modelData = self->mpMorf->getModel()->getModelData();
    g_env_light.settingTevStruct(0, &self->current.pos, &self->tevStr);
    g_env_light.setLightTevColorType(self->mpMorf->getModel(), &self->tevStr);
    g_env_light.setLightTevColorType(self->m6C4, &self->tevStr);
    self->m6F8.entry(modelData, self->m720);
    self->mpMorf->updateDL();
    self->m6F8.remove(modelData);
    if (self->m74F) {
        self->mBtpAnm.entry(self->m6C4->getModelData(), (s16)self->mBtpAnm.getFrame());
        mDoExt_modelUpdateDL(self->m6C4);
    }
    cXyz shadow_pos(self->current.pos.x, self->current.pos.y + 150.0f, self->current.pos.z);
    self->m724 = dComIfGd_setShadow(self->m724, 1, self->mpMorf->getModel(), &shadow_pos, 800.0f, 20.0f,
                                    self->current.pos.y, self->mObjAcch.GetGroundH(), self->mObjAcch.m_gnd,
                                    &self->tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    return 1;
}

/* 000027CC-000027D4       .text daNpc_Kg1IsDelete__FPv */
static BOOL daNpc_Kg1IsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_Kg1MethodTable = {
    (process_method_func)daNpc_Kg1Create,
    (process_method_func)daNpc_Kg1Delete,
    (process_method_func)daNpc_Kg1Execute,
    (process_method_func)daNpc_Kg1IsDelete,
    (process_method_func)daNpc_Kg1Draw,
};

actor_process_profile_definition g_profile_NPC_KG1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KG1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kg1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KG1_e,
    /* Actor SubMtd */ &daNpc_Kg1MethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
