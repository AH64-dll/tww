/**
 * d_a_npc_kg2.cpp
 * NPC - Salvatore (Cannon Minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kg2.h"
#include "d/actor/d_a_player.h"
#include "m_Do/m_Do_controller_pad.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_lib.h"
#include "d/d_cc_d.h"
#include "d/d_snap.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "d/d_s_play.h"
#include "SSystem/SComponent/c_math.h"

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

static const int l_bck_ix_tbl[] = {
    0x11, 0x1A, 0x19, 0x14, 0x16, 0x12, 0x13, 0x15, 0x17, 0x18, 0x1B, 0x1C, 0x14, 0x16, 0x1D,
};
static const int l_btp_ix_tbl[] = {9, 11, 13, 12, 14};

static daNpc_Kg2_HIO_c l_HIO;

u8 daNpc_Kg2_c::canon_game_result = 0;
daNpc_Kg2_c* daNpc_Kg2_c::l_kg2_pointer = NULL;

/* 000000EC-00000194       .text __ct__15daNpc_Kg2_HIO_cFv */
daNpc_Kg2_HIO_c::daNpc_Kg2_HIO_c() {
    /* Nonmatching */
    mHio.m04 = -20.0f;
    mHio.mMaxHeadX = 0x9C4;
    mHio.mMaxHeadY = 0x1B58;
    mHio.mMaxBackboneX = 0x7D0;
    mHio.mMaxBackboneY = 0x1F40;
    mHio.mMinHeadX = -0x9C4;
    mHio.mMinHeadY = -0x1B58;
    mHio.mMinBackboneX = -0x7D0;
    mHio.mMinBackboneY = -0x1F40;
    mHio.mMaxTurnStep = 0x1000;
    mHio.mMaxHeadTurnVel = 0x3E8;
    mHio.mAttnYOffset = 35.0f;
    mHio.mMaxAttnAngleY = 0x4000;
    mHio.m22 = 0;
    mHio.mMaxAttnDistXZ = 400.0f;
    field_0x30 = 0;
    mNo = -1;
}

static BOOL daNpc_Kg2_nodeCallBack(J3DNode* node, int param) {
    /* Nonmatching */
    if (param == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Kg2_c* actor = (daNpc_Kg2_c*)model->getUserArea();
        u16 jnt_no_raw = ((J3DJoint*)node)->getJntNo();
        int jnt_no = jnt_no_raw;
        mDoMtx_stack_c::copy(model->getAnmMtx(jnt_no));
        if (jnt_no == actor->m_jnt.getHeadJntNum()) {
            cXyz sp8;
            static cXyz l_offsetEyePos(24.0f, -16.0f, 0.0f);
            sp8.x = 24.0f + REG10_F(0);
            sp8.y = 5.0f + REG10_F(1);
            sp8.z = REG10_F(2);
            mDoMtx_stack_c::multVec(&sp8, &actor->getAttentionBasePos());
            mDoMtx_XrotM(mDoMtx_stack_c::now, actor->m_jnt.getHead_y());
            mDoMtx_ZrotM(mDoMtx_stack_c::now, -actor->m_jnt.getHead_x());
            mDoMtx_stack_c::multVec(&l_offsetEyePos, &actor->getEyePos());
            mDoMtx_stack_c::multVec(&sp8, &actor->attention_info.position);
            actor->attention_info.position.y += l_HIO.mHio.mAttnYOffset;
        }
        if (jnt_no == actor->m_jnt.getBackboneJntNum()) {
            mDoMtx_XrotM(mDoMtx_stack_c::now, actor->m_jnt.getBackbone_y());
            mDoMtx_ZrotM(mDoMtx_stack_c::now, -actor->m_jnt.getBackbone_x());
        }
        model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
        if (jnt_no == actor->m_handL_num) {
            mDoMtx_stack_c::transM(23.467f, -22.26f, -47.1f);
            mDoMtx_stack_c::XYZrotM(0x1F4B, -0x4F00, 0x1F4B);
            actor->m6D4->setBaseTRMtx(mDoMtx_stack_c::get());
        }
    }
    return 1;
}

/* 000003A4-0000048C       .text set_mtx__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if (m736) {
        mDoMtx_stack_c::copy(model->getAnmMtx(m_handL_num));
        mDoMtx_stack_c::transM(23.467f, -22.26f, -47.1f);
        mDoMtx_stack_c::XYZrotM(0x1F4B, -0x4F00, 0x1F4B);
        m6D4->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 0000048C-000005A0       .text initTexPatternAnm__11daNpc_Kg2_cFb */
BOOL daNpc_Kg2_c::initTexPatternAnm(bool param) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_btp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Kg", l_btp_ix_tbl[m748]);
    JUT_ASSERT(0x12B, m_btp != 0);
    BOOL ret = m6F0.init(modelData, m_btp, 1, 2, 1.0f, 0, -1, param, FALSE);
    if (ret == FALSE) {
        return FALSE;
    }
    m704 = 0;
    m706 = 0;
    return TRUE;
}

/* 000005A0-000006EC       .text playTexPatternAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::playTexPatternAnm() {
    if (m738 == 1 && m748 == 0 && m704 == 2) {
        m704 = 0;
        m748 = 4;
        initTexPatternAnm(true);
    } else {
        if (cLib_calcTimer(&m706)) {
            return;
        }
        if (m748 == 4) {
            if (m704 == 0) {
                m704 = 1;
                m706 = (s16)(150.0f + cM_rndF(150.0f));
            } else {
                m704 = 0;
                m706 = (s16)(150.0f + cM_rndF(150.0f)) * 2;
            }
        } else if (m704 >= m_btp->getFrameMax()) {
            m704 -= m_btp->getFrameMax();
            m706 = (s16)(30.0f + cM_rndF(100.0f));
        } else {
            m704++;
        }
    }
}

/* 000006EC-00000838       .text setAnm__11daNpc_Kg2_cFScf */
void daNpc_Kg2_c::setAnm(s8 i_anmNo, f32 i_morf) {
    /* Nonmatching */
    static int a_play_mode_tbl[] = {
        2, 2, 2, 0, 2, 2, 2, 2, 2, 0, 2, 2, 0, 0, 2,
    };
    static f32 a_morf_frame_tbl[] = {
        8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f,
    };
    static f32 a_play_speed_tbl[] = {
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
    };
    f32 morf = i_morf;
    if (morf < 0.0f) {
        morf = a_morf_frame_tbl[i_anmNo];
    }
    if (i_anmNo != m749 && m749 != -1) {
        m749 = i_anmNo;
        dNpc_setAnm(mpMorf, a_play_mode_tbl[m749], morf, a_play_speed_tbl[m749], l_bck_ix_tbl[m749], -1,
                    "Kg");
        if (m749 == 0xC) {
            mpMorf->setFrame(mpMorf->getEndFrame() - 1.0f);
            mpMorf->setPlaySpeed(-1.0f);
        }
    }
    if (m749 == 2) {
        m_jnt.mbHeadLock = false;
        m_jnt.mbBackBoneLock = true;
    } else {
        m_jnt.mbHeadLock = true;
        m_jnt.mbBackBoneLock = true;
    }
}

/* 00000838-000009E8       .text subAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::subAnm() {
    /* Nonmatching */
    if (m748 == 4) {
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::getInterface()->seStart(JA_SE_CV_KG_SLEEP, &eyePos, 0, reverb, 1.0f, 1.0f,
                                             -1.0f, -1.0f, 0);
    }
    if (m749 == 3 || m749 == 0xD) {
        if (mpMorf->checkFrame(1.0f)) {
            m736 = 1;
            if (m749 == 3) {
                m737 = 3;
            } else {
                m737 = 4;
            }
        }
    } else if (m749 == 9) {
        if (mpMorf->checkFrame(30.0f)) {
            m736 = 1;
            m737 = 2;
        }
    } else if (m749 == 0xC) {
        if (mpMorf->checkFrame(1.0f)) {
            m736 = 0;
            setAnm(1, -1.0f);
        }
    } else if (m749 == 0xD) {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            setAnm(4, -1.0f);
        }
    }
}

/* 000009E8-00000B3C       .text chkAttention__11daNpc_Kg2_cF4cXyzs */
s32 daNpc_Kg2_c::chkAttention(cXyz i_pos, s16 i_angleY) {
    /* Nonmatching */
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    f32 max_attn_dist = l_HIO.mHio.mMaxAttnDistXZ;
    s16 max_attn_angle = l_HIO.mHio.mMaxAttnAngleY;
    cXyz spC;
    spC.x = player->current.pos.x - i_pos.x;
    spC.z = player->current.pos.z - i_pos.z;
    f32 dist = std::sqrtf(spC.x * spC.x + spC.z * spC.z);
    s16 angle = cM_atan2s(spC.x, spC.z);
    if (m72C) {
        max_attn_angle += 0x71C;
        max_attn_dist += 40.0f;
    }
    s32 ret = 0;
    if (max_attn_angle > abs((s16)(cM_atan2s(spC.x, spC.z) - i_angleY)) && max_attn_dist > dist) {
        ret = 1;
    }
    return ret;
}

/* 00000B3C-00000BC0       .text eventOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::eventOrder() {
    s8 event_no = m750;
    if (event_no == 1 || event_no == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m750 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (event_no == 3) {
        fopAcM_orderOtherEventId(this, m758[m754], 0xFF, 0xFFFF, 0, 1);
    }
}

/* 00000BC0-00000CC4       .text checkOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        setAction(&daNpc_Kg2_c::event_wait_action, 0);
        m750 = 0;
    } else if (eventInfo.checkCommandTalk()) {
        if (m750 == 1 || m750 == 2) {
            m750 = 0;
            m72D = 1;
        }
    }
}

/* 00000CC4-00000E38       .text getMsg__11daNpc_Kg2_cFv */
u32 daNpc_Kg2_c::getMsg() {
    u32 msgNo;
    if (m74C) {
        u8 reg = dComIfGs_getEventReg(0xB703);
        if (m74C == 0x3145) {
            if (m735 == 1) {
                m74C = 0x314B;
            } else {
                if (dComIfGs_isEventBit(0x2508)) {
                    m74C = 0x314C;
                }
            }
        } else if (m74C == 0x3150) {
            if (reg != 0) {
                m74C = 0x3154;
            }
        } else if (m74C == 0x3152) {
            if (reg == 1) {
                m74C = 0x3156;
            } else if (reg >= 2) {
                m74C = 0x3158;
            }
        }
        msgNo = m74C;
        m74C = 0;
    } else if (m738 == 1) {
        msgNo = 0x315B;
    } else {
        if (dComIfGs_isEventBit(0x2540) && !dComIfGs_isEventBit(0x2520)) {
            dComIfGs_onEventBit(0x2520);
            msgNo = 0x3140;
        } else {
            if (m734 == 0) {
                m734 = 1;
                msgNo = 0x3139;
            } else {
                msgNo = 0x313A;
            }
        }
    }
    return msgNo;
}

/* 00000E38-00001028       .text next_msgStatus__11daNpc_Kg2_cFPUl */
u16 daNpc_Kg2_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
    case 0x3140:
    case 0x3145:
    case 0x3146:
    case 0x3147:
    case 0x3148:
    case 0x314C:
    case 0x314E:
    case 0x3150:
    case 0x3152:
    case 0x3154:
    case 0x3156:
    case 0x3158:
        (*pMsgNo)++;
        break;
    case 0x314D:
        *pMsgNo = 0x3147;
        break;
    case 0x3139:
        if (!dComIfGs_getEventReg(0xB703)) {
            *pMsgNo = 0x313E;
        } else if ((s32)dLib_getIplDaysFromSaveTime() < 4) {
            *pMsgNo = 0x313B;
        } else {
            if (dComIfGs_isTmpBit(0x102)) {
                *pMsgNo = 0x313C;
            } else {
                dComIfGs_onTmpBit(0x102);
                *pMsgNo = 0x313D;
            }
        }
        break;
    case 0x3149:
        if (mpCurrMsg->mSelectNum == 0) {
            dComIfGs_onEventBit(0x2508);
            m735 = 1;
            *pMsgNo = 0x314B;
        } else {
            *pMsgNo = 0x314A;
        }
        break;
    case 0x314A:
        *pMsgNo = 0x3148;
        break;
    case 0x313A:
    case 0x313B:
    case 0x313C:
    case 0x313D:
    case 0x313E:
        *pMsgNo = 0x313F;
        break;
    case 0x313F:
    case 0x314F:
        if (mpCurrMsg->mSelectNum == 0) {
            if (dComIfGs_getRupee() < 50) {
                *pMsgNo = 0x3143;
            } else {
                dComIfGp_setItemRupeeCount(-50);
                dComIfGp_setAStatusForce(dActStts_NEXT_e);
                *pMsgNo = 0x3144;
            }
        } else {
            *pMsgNo = 0x3142;
        }
        break;
    case 0x3141:
        if (m734 == 0) {
            m734 = 1;
            *pMsgNo = 0x3139;
        } else {
            *pMsgNo = 0x313A;
        }
        break;
    default:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 00001028-000012EC       .text anmAtr__11daNpc_Kg2_cFUs */
void daNpc_Kg2_c::anmAtr(u16 i_msgStatus) {
    u8 msg_attr = dComIfGp_getMesgAnimeAttrInfo();
    if (m738 != 1) {
        switch (msg_attr) {
        case 0:
            setAnm(0, -1.0f);
            m748 = 0;
            initTexPatternAnm(true);
            break;
        case 1:
            setAnm(1, -1.0f);
            m748 = 0;
            initTexPatternAnm(true);
            break;
        case 2:
            setAnm(2, -1.0f);
            m748 = 1;
            initTexPatternAnm(true);
            break;
        case 3:
            setAnm(3, -1.0f);
            m748 = 0;
            initTexPatternAnm(true);
            break;
        case 4:
            setAnm(5, -1.0f);
            m748 = 1;
            initTexPatternAnm(true);
            break;
        case 5:
            setAnm(6, -1.0f);
            m748 = 1;
            initTexPatternAnm(true);
            break;
        case 6:
            setAnm(7, -1.0f);
            m748 = 2;
            initTexPatternAnm(true);
            break;
        case 7:
            setAnm(8, -1.0f);
            m748 = 3;
            initTexPatternAnm(true);
            break;
        case 8:
            setAnm(9, -1.0f);
            m748 = 0;
            initTexPatternAnm(true);
            break;
        case 9:
            setAnm(0xA, -1.0f);
            m748 = 1;
            initTexPatternAnm(true);
            break;
        case 0xA:
            setAnm(0xB, -1.0f);
            m748 = 2;
            initTexPatternAnm(true);
            break;
        case 0xB:
            setAnm(0xE, -1.0f);
            m748 = 2;
            initTexPatternAnm(true);
            break;
        }
        if (m749 == 3) {
            if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
                setAnm(4, -1.0f);
                m748 = 0;
                initTexPatternAnm(true);
            }
        }
        dComIfGp_setMesgAnimeAttrInfo(0xFF);
    }
}

/* 000012EC-00001308       .text setAttention__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::setAttention() {
    eyePos.set(m708.x, m708.y, m708.z);
}

/* 00001308-00001448       .text lookBack__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::lookBack() {
    /* Nonmatching */
    cXyz eye_pos;
    cXyz look_pos(0.0f, 0.0f, 0.0f);
    cXyz* p_look_pos = NULL;
    s16 target_y = current.angle.y;
    switch (m760) {
    case 1:
    case 2:
        if (m760 == 2) {
            m_jnt.mbTrn = true;
        }
        if (m72C) {
            eye_pos = dNpc_playerEyePos(l_HIO.mHio.m04);
            p_look_pos = &eye_pos;
            look_pos.x = current.pos.x;
            look_pos.y = current.pos.y;
            look_pos.z = current.pos.z;
            look_pos.y = eyePos.y;
        }
        break;
    default:
        break;
    }
    if (m_jnt.mbTrn) {
        cLib_addCalcAngleS2(&m720, l_HIO.mHio.mMaxHeadTurnVel, 4, 0x800);
    } else {
        m720 = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, p_look_pos, look_pos, target_y, m720, 1);
}

/* 00001448-00001468       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->CreateHeap();
}

/* 00001468-0000180C       .text CreateHeap__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Kg", 5);
    JUT_ASSERT(0x391, modelData != 0);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Kg", 0x1A),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x11020203
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x3A1, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone2"));
    JUT_ASSERT(0x3A6, m_jnt.getBackboneJntNum() >= 0);
    m_handL_num = modelData->getJointName()->getIndex("handL");
    JUT_ASSERT(0x3AA, m_handL_num >= 0);
    m748 = 0;
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }
    J3DModelData* cannonData = (J3DModelData*)dComIfG_getObjectRes("Kg", 6);
    m6D4 = mDoExt_J3DModel__create(cannonData, 0x80000, 0x11020002);
    if (m6D4 == NULL) {
        return FALSE;
    }
    J3DAnmTexPattern* cannonBtp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Kg", 0xA);
    if (!mBtpAnm.init(cannonData, cannonBtp, 1, 2, 1.0f, 0, -1, FALSE, 0)) {
        return FALSE;
    }
    J3DModel* model = mpMorf->getModel();
    J3DModelData* data = model->getModelData();
    model->getModelData()->getJointNodePointer(m_jnt.getHeadJntNum())->setCallBack(daNpc_Kg2_nodeCallBack);
    model->getModelData()->getJointNodePointer(m_jnt.getBackboneJntNum())->setCallBack(daNpc_Kg2_nodeCallBack);
    model->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 1.0f);
    mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, 0, 0);
    return TRUE;
}

/* 0000180C-00001A9C       .text CreateInit__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::CreateInit() {
    /* Nonmatching */
    m724 = current.angle.x;
    m726 = current.angle.y;
    m728 = current.angle.z;
    attention_info.flags = 0xA;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x6E;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x6E;
    gravity = -30.0f;
    setAction(&daNpc_Kg2_c::wait_action, 0);
    m708 = current.pos;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(60.0f, 150.0f);
    mEventCut.setActorInfo2("Kg2", this);
    mEventCut.setJntCtrlPtr(&m_jnt);
    m734 = 0;
    m735 = 0;
    m736 = 0;
    m737 = 0;
    m74C = 0;
    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;
    m750 = 0;
    m754 = 4;
    m758[0] = dComIfGp_evmng_getEventIdx("KG2_START_DEMO", 0xFF);
    m758[1] = dComIfGp_evmng_getEventIdx("KG2_CLEAR_DEMO", 0xFF);
    m758[2] = dComIfGp_evmng_getEventIdx("KG2_GETDEMO", 0xFF);
    m758[3] = dComIfGp_evmng_getEventIdx("CANON_GAME", 0xFF);
    set_mtx();
    if (dComIfGs_getTime() >= 105.0f && dComIfGs_getTime() < 300.0f) {
        m738 = 0;
        setAnm(1, -1.0f);
    } else {
        m738 = 1;
        setAnm(0xD, 0.0f);
    }
    l_kg2_pointer = this;
    return TRUE;
}

/* 00001A9C-00001BDC       .text wait01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::wait01() {
    /* Nonmatching */
    if (dComIfGs_getTime() >= 105.0f && dComIfGs_getTime() < 300.0f) {
        if (m738 == 1) {
            m738 = 0;
            setAnm(0xC, -1.0f);
            m748 = 0;
            initTexPatternAnm(true);
        }
    } else if (m738 == 0) {
        m738 = 1;
        setAnm(0xD, -1.0f);
        m748 = 0;
        initTexPatternAnm(true);
    }
    if (m72D) {
        m760 = 2;
    } else {
        f32 dist = std::fabsf(dComIfGp_getPlayer(0)->current.pos.y - current.pos.y);
        if (m72C && dist < 50.0f && m749 != 0xD && m749 != 0xC) {
            m750 = 2;
        }
    }
}

/* 00001BDC-00001CA4       .text talk01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::talk01() {
    if (talk(1) == 0x12) {
        m760 = 1;
        g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
        m72D = 0;
        if (mCurrMsgNo == 0x3144) {
            m750 = 3;
            m754 = 0;
        } else if (m738 == 0) {
            setAnm(1, -1.0f);
            m748 = 0;
            initTexPatternAnm(true);
        } else {
            setAnm(4, -1.0f);
        }
    }
}

/* 00001CA4-00001D88       .text evn_setAnm_init__11daNpc_Kg2_cFi */
int daNpc_Kg2_c::evn_setAnm_init(int i_staffId) {
    int* anm_no = dComIfGp_evmng_getMyIntegerP(i_staffId, "AnmNo");
    int* count = dComIfGp_evmng_getMyIntegerP(i_staffId, "count");
    f32* morf = dComIfGp_evmng_getMyFloatP(i_staffId, "hokan");
    if (anm_no != NULL) {
        f32 morf_f = -1.0f;
        if (morf != NULL) {
            morf_f = *morf;
        }
        setAnm((s8)*anm_no, morf_f);
        if (count != NULL) {
            m739 = *count;
        } else {
            m739 = 0;
        }
    }
    return 1;
}

/* 00001D88-00001E4C       .text evn_setAnm__11daNpc_Kg2_cFv */
int daNpc_Kg2_c::evn_setAnm() {
    if (m749 == 0xC) {
        if (mpMorf->checkFrame(1.0f)) {
            m739--;
        }
    } else {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            m739--;
        }
    }
    if ((s8)m739 <= 0) {
        return 1;
    }
    return 0;
}

/* 00001E4C-00001F14       .text evn_jnt_lock_init__11daNpc_Kg2_cFi */
int daNpc_Kg2_c::evn_jnt_lock_init(int i_staffId) {
    int* lock = dComIfGp_evmng_getMyIntegerP(i_staffId, "prm");
    s32 lock_no = 0;
    if (lock != NULL) {
        lock_no = *lock;
    }
    switch (lock_no) {
    case 0:
        m_jnt.mbHeadLock = false;
        m_jnt.mbBackBoneLock = false;
        break;
    case 1:
        m_jnt.mbHeadLock = true;
        m_jnt.mbBackBoneLock = false;
        break;
    case 2:
        m_jnt.mbHeadLock = false;
        m_jnt.mbBackBoneLock = true;
        break;
    case 3:
        m_jnt.mbHeadLock = true;
        m_jnt.mbBackBoneLock = true;
        break;
    }
    return 1;
}

/* 00001F14-00001F88       .text evn_talk_init__11daNpc_Kg2_cFi */
int daNpc_Kg2_c::evn_talk_init(int i_staffId) {
    int* msg_no = dComIfGp_evmng_getMyIntegerP(i_staffId, "msg_num");
    mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
    mpCurrMsg = NULL;
    if (msg_no != NULL) {
        m74C = *msg_no;
    } else {
        m74C = 0;
    }
    return 1;
}

/* 00001F88-00001FBC       .text evn_talk__11daNpc_Kg2_cFv */
int daNpc_Kg2_c::evn_talk() {
    return (talk(1) == 0x12) ? 1 : 0;
}

/* 00001FBC-00002070       .text evn_createItem_init__11daNpc_Kg2_cFi */
int daNpc_Kg2_c::evn_createItem_init(int i_staffId) {
    u8 reg = dComIfGs_getEventReg(0xB703);
    u8 item = 6;
    switch (reg) {
    case 0:
    case 1:
        item = 7;
        break;
    case 2:
        item = 0xD7;
        break;
    case 3:
    default:
        item = 6;
        break;
    }
    fpc_ProcID proc_id = fopAcM_createItemForPresentDemo(&current.pos, item, 0, -1, current.roomNo, NULL, NULL);
    if (proc_id != fpcM_ERROR_PROCESS_ID_e) {
        g_dComIfG_gameInfo.play.getEvent()->setPtI_Id(proc_id);
    }
    return 1;
}

/* 00002070-000021EC       .text privateCut__11daNpc_Kg2_cFv */
int daNpc_Kg2_c::privateCut() {
    /* Nonmatching */
    static char* cut_name_tbl[] = {
        "SETANM",
        "JNTLOCK",
        "SHOWITEM",
        "KGTALK",
        "CREATEITEM",
    };
    int staff_id = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL, 0);
    if (staff_id == -1) {
        return 0;
    }
    s32 act_idx = dComIfGp_evmng_getMyActIdx(staff_id, cut_name_tbl, 5, 1, 0);
    if (act_idx == -1) {
        dComIfGp_evmng_cutEnd(staff_id);
    } else if (dComIfGp_evmng_getIsAddvance(staff_id)) {
        switch (act_idx) {
        case 0:
            evn_setAnm_init(staff_id);
            break;
        case 1:
            evn_jnt_lock_init(staff_id);
            break;
        case 3:
            evn_talk_init(staff_id);
            break;
        case 4:
            evn_createItem_init(staff_id);
            break;
        }
    }
    int ret = 1;
    switch (act_idx) {
    case 0:
        ret = evn_setAnm();
        break;
    case 2:
        ret = 1;
        break;
    case 3:
        ret = evn_talk();
        break;
    default:
        ret = 1;
        break;
    }
    if (ret) {
        dComIfGp_evmng_cutEnd(staff_id);
    }
    return 1;
}

/* 000021EC-00002250       .text processMove__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::processMove() {
    (this->*mAction)(0);
    if (mEventCut.cutProc() || privateCut()) {
        return 1;
    }
    return 0;
}

/* 00002250-00002334       .text wait_action__11daNpc_Kg2_cFPv */
int daNpc_Kg2_c::wait_action(void*) {
    if (m763 == 0) {
        m760 = 1;
        m763++;
    } else if (m763 != -1) {
        s16 angleY = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        m72C = chkAttention(current.pos, angleY);
        m750 = 0;
        switch (m760) {
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
    return 1;
}

/* 00002334-00002590       .text event_wait_action__11daNpc_Kg2_cFPv */
int daNpc_Kg2_c::event_wait_action(void*) {
    if (m763 == 0) {
        m760 = 1;
        m763++;
    } else if (m763 != -1) {
        s16 angleY = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        m72C = chkAttention(current.pos, angleY);
        lookBack();
        setAttention();
        if (dComIfGp_evmng_endCheck(m758[m754])) {
            if (m754 == 0) {
                m750 = 3;
                m754 = 3;
            } else if (m754 == 3) {
                if (canon_game_result == 1) {
                    m750 = 3;
                    m754 = 1;
                } else {
                    m750 = 1;
                    m74C = 0x314E;
                }
            } else if (m754 == 1) {
                m750 = 3;
                m754 = 2;
                u8 reg = dComIfGs_getEventReg(0xB703);
                dComIfGs_setEventReg(0xB703, (u8)((reg + 1) > 3 ? 3 : (reg + 1)));
            } else if (m754 == 2) {
                m750 = 1;
                m74C = 0x315A;
            } else {
                m754 = 4;
            }
            g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
            setAction(&daNpc_Kg2_c::wait_action, 0);
        }
    }
    return 1;
}

/* 00002590-000027BC       .text _create__11daNpc_Kg2_cFv */
cPhs_State daNpc_Kg2_c::_create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daNpc_Kg2_c);
    cPhs_State phase = dComIfG_resLoad(&mPhs, "Kg");
    if (phase == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CallbackCreateHeap, 0x2D00)) {
            return cPhs_ERROR_e;
        }
        cullMtx = mpMorf->getModel()->getBaseTRMtx();
        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_root.createChild("Kg2", &l_HIO);
        }
        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 00002B6C-00002BFC       .text _delete__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_delete() {
    dComIfG_resDelete(&mPhs, "Kg");
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    l_kg2_pointer = NULL;
    if (l_HIO.mNo >= 0) {
        mDoHIO_root.deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return TRUE;
}

/* 00002BFC-00002D14       .text _execute__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_execute() {
    m_jnt.setParam(l_HIO.mHio.mMaxBackboneX, l_HIO.mHio.mMaxBackboneY, l_HIO.mHio.mMinBackboneX,
                   l_HIO.mHio.mMinBackboneY, l_HIO.mHio.mMaxHeadX, l_HIO.mHio.mMaxHeadY,
                   l_HIO.mHio.mMinHeadX, l_HIO.mHio.mMinHeadY, l_HIO.mHio.mMaxTurnStep);
    playTexPatternAnm();
    mpMorf->play(&eyePos, 0, 0);
    mpMorf->calc();
    checkOrder();
    processMove();
    eventOrder();
    subAnm();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    set_mtx();
    setCollision(60.0f, 150.0f);
    return TRUE;
}

/* 00002D14-00002E74       .text _draw__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_draw() {
    /* Nonmatching */
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    m6F0.entry(modelData, m704);
    mpMorf->entryDL();
    modelData->getMaterialTable().removeTexNoAnimator(m6F0.getBtpAnm());
    if (m736) {
        J3DModelData* cannonData = m6D4->getModelData();
        g_env_light.setLightTevColorType(m6D4, &tevStr);
        mBtpAnm.entry(cannonData, m737);
        mDoExt_modelUpdateDL(m6D4);
        cannonData->getMaterialTable().removeTexNoAnimator(mBtpAnm.getBtpAnm());
    }
    cXyz shadow_pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    m6D0 = dComIfGd_setShadow(m6D0, 1, mpMorf->getModel(), &shadow_pos, 800.0f, 20.0f,
                              current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr,
                              0, 1.0f, &dDlst_shadowControl_c::mSimpleTexObj);
    dSnap_RegistFig(0x81, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

namespace {
/* 00002E74-00002E94       .text daNpc_Kg2_Create__FP10fopAc_ac_c */
cPhs_State daNpc_Kg2_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_create();
}

/* 00002E94-00002EB4       .text daNpc_Kg2_Delete__FP11daNpc_Kg2_c */
BOOL daNpc_Kg2_Delete(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_delete();
}

/* 00002EB4-00002ED4       .text daNpc_Kg2_Execute__FP11daNpc_Kg2_c */
BOOL daNpc_Kg2_Execute(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_execute();
}

/* 00002ED4-00002EF4       .text daNpc_Kg2_Draw__FP11daNpc_Kg2_c */
BOOL daNpc_Kg2_Draw(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_draw();
}

/* 00002EF4-00002EFC       .text daNpc_Kg2_IsDelete__FP11daNpc_Kg2_c */
BOOL daNpc_Kg2_IsDelete(daNpc_Kg2_c*) {
    return TRUE;
}
}; // namespace

static actor_method_class l_daNpc_Kg2_Method = {
    (process_method_func)daNpc_Kg2_Create,
    (process_method_func)daNpc_Kg2_Delete,
    (process_method_func)daNpc_Kg2_Execute,
    (process_method_func)daNpc_Kg2_IsDelete,
    (process_method_func)daNpc_Kg2_Draw,
};

actor_process_profile_definition g_profile_NPC_KG2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KG2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kg2_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KG2_e,
    /* Actor SubMtd */ &l_daNpc_Kg2_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
