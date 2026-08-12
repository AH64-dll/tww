/**
 * d_a_npc_ac1.cpp
 * NPC - Prince Komali (after Dragon Roost)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ac1.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/d_snap.h"
#include "res/Object/Ac.h"

static daNpc_Ac1_HIO_c l_HIO;

/* 000000EC-00000150       .text __ct__15daNpc_Ac1_HIO_cFv */
daNpc_Ac1_HIO_c::daNpc_Ac1_HIO_c() {
    static daNpc_Ac1_HIO_c::hio_prm_c a_prm_tbl = {
        /* mMaxHeadX        */ 0x2000,
        /* mMaxHeadY        */ 0x2710,
        /* mMinHeadX        */ 0xF000,
        /* mMinHeadY        */ 0xD8F0,
        /* mMaxBackboneX    */ 0x0000,
        /* mMaxBackboneY    */ 0x1770,
        /* mMinBackboneX    */ 0x0000,
        /* mMinBackboneY    */ 0xE890,
        /* mMaxTurnStep     */ 0x0708,
        /* mMaxHeadTurnVel  */ 0x0578,
        /* mAttnYOffset     */ 150.0f,
        /* m18              */ 0,
        /* mMaxAttnAngleY   */ 6,
        /* m1C              */ 0x400,
        /* m1E              */ 0,
        /* mMaxAttnDistXZ   */ 0.5f,
        /* m24              */ 3.0f,
        /* m28              */ 0.1f,
        /* m2C              */ 40.0f,
    };
    memcpy(&hio_prm, &a_prm_tbl, sizeof(hio_prm_c));
    m4 = -1;
    m8 = -1;
}

/* 00000198-000001E4       .text nodeCallBack_Wng__FP7J3DNodei */
static BOOL nodeCallBack_Wng(J3DNode* i_param_1, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ac1_c*>(j3dSys.getModel()->getUserArea())->nodeWngControl(i_param_1, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-00000294       .text nodeWngControl__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeWngControl(J3DNode* i_node, J3DModel* i_model) {
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if (uVar1 == m_wngL1_jnt_num) {
        cMtx_copy(mLeftArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mLeftArmMtx);
    }
    if (uVar1 == m_wngR1_jnt_num) {
        cMtx_copy(mRightArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mRightArmMtx);
    }
}

/* 00000294-000002E0       .text nodeCallBack_Arm__FP7J3DNodei */
static BOOL nodeCallBack_Arm(J3DNode* i_param_1, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ac1_c*>(j3dSys.getModel()->getUserArea())->nodeArmControl(i_param_1, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000002E0-00000390       .text nodeArmControl__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeArmControl(J3DNode* i_node, J3DModel* i_model) {
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if (uVar1 == m_armL1_jnt_num) {
        cMtx_copy(mLeftArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mLeftArmMtx);
    }
    if (uVar1 == m_armR1_jnt_num) {
        cMtx_copy(mRightArmMtx, j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1, mRightArmMtx);
    }
}

/* 00000390-000003DC       .text nodeCallBack_Ac1__FP7J3DNodei */
static BOOL nodeCallBack_Ac1(J3DNode* i_param_1, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ac1_c*>(j3dSys.getModel()->getUserArea())->nodeAc1Control(i_param_1, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000003DC-0000056C       .text nodeAc1Control__11daNpc_Ac1_cFP7J3DNodeP8J3DModel */
void daNpc_Ac1_c::nodeAc1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(20.0f, 18.0f, 0.0f);
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if (uVar1 == m_hed_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mEyePos);
    }
    if (uVar1 == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }
    if (uVar1 == m_arm_L_jnt_num) {
        cMtx_copy(mDoMtx_stack_c::get(), mLeftArmMtx);
    }
    if (uVar1 == m_arm_R_jnt_num) {
        cMtx_copy(mDoMtx_stack_c::get(), mRightArmMtx);
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(uVar1, mDoMtx_stack_c::get());
}

/* 000005A8-00000640       .text init_AC1_0__11daNpc_Ac1_cFv */
u8 daNpc_Ac1_c::init_AC1_0() {
    u8 ret = dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) != 0;
    if (ret != 0) {
        dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580);
        set_action(&daNpc_Ac1_c::wait_action1, NULL);
    }
    return ret;
}

/* 00000640-000007C8       .text createInit__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::createInit() {
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.5;
    m814 = current.pos;
    u8 path_no = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (path_no != 0xFF) {
        mPathRun.setInf(path_no, fopAcM_GetRoomNo(this), true);
        if (mPathRun.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        } else {
            return false;
        }
    }

    mEventCut.setActorInfo2("Ac1", this);
    mAnmNum = 4;

    u8 init_success;
    switch (m879) {
        case 0:
            init_success = init_AC1_0();
            break;
        default:
            init_success = 0;
            break;
    }
    if (init_success) {
        shape_angle = current.angle;
    } else {
        return false;
    }
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    if (mbHasArms) {
        mpArmMorf->setMorf(0.0f);
    } else {
        mpWingMorf->setMorf(0.0f);
    }
    setMtx(true);
    return true;
}

/* 000007C8-00000988       .text setMtx__11daNpc_Ac1_cFb */
void daNpc_Ac1_c::setMtx(bool i_param_1) {
    if (!mbInDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mFrame) {
            mbMorfAnimStopped = true;
        }
        mFrame = mpMorf->getFrame();
        if (mbHasArms) {
            mpArmMorf->play(&eyePos, 0, 0);
        } else {
            mpWingMorf->play(&eyePos, 0, 0);
        }
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    cMtx_copy(mDoMtx_stack_c::get(), mpMorf->getModel()->getBaseTRMtx());
    mpMorf->calc();
    if (!mbHasArms) {
        mpWingMorf->calc();
    } else {
        mpArmMorf->calc();
    }
    if (mpItemModel != NULL && mbHasArms) {
        cMtx_copy(mpArmMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num), mpItemModel->getBaseTRMtx());
        mpItemModel->calc();
    }
    setAttention(i_param_1);
}

/* 00000988-0000099C       .text anmNum_toResID__11daNpc_Ac1_cFi */
int daNpc_Ac1_c::anmNum_toResID(int i_anmNum) {
    static int a_bck_resID_tbl[] = {
        0x1,
        0xC,
        0xD,
        0xE,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 0000099C-000009B0       .text wingAnmNum_toResID__11daNpc_Ac1_cFi */
int daNpc_Ac1_c::wingAnmNum_toResID(int i_anmNum) {
    static int a_bck_resID_tbl[] = {
        0x0,
        0x9,
        0xA,
        0xB,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 000009B0-000009C4       .text btpNum_toResID__11daNpc_Ac1_cFi */
int daNpc_Ac1_c::btpNum_toResID(int i_btpNum) {
    static int a_btp_resID_tbl[] = {
        0x7,
        0x6,
        0x8,
    };
    return a_btp_resID_tbl[i_btpNum];
}

/* 000009C4-00000AD4       .text setBtp__11daNpc_Ac1_cFbi */
bool daNpc_Ac1_c::setBtp(bool i_param_1, int i_btp_num) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    int res_id = btpNum_toResID(i_btp_num);
    m_hed_tex_pttrn =
        reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes("Ac", static_cast<u16>(res_id)));
    JUT_ASSERT(0x216, m_hed_tex_pttrn != NULL);
    int iVar1 = mBtpAnim.init(model_data, m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, i_param_1, 0);
    bool o_retval = iVar1 == 1;
    if (o_retval) {
        mBlinkFrame = 0;
        mBlinkTimer = 0;
    }
    return o_retval;
}

/* 00000AD4-00000AFC       .text iniTexPttrnAnm__11daNpc_Ac1_cFb */
bool daNpc_Ac1_c::iniTexPttrnAnm(bool i_param_1) {
    return setBtp(i_param_1, mBtpNum);
}

/* 00000AFC-00000BA8       .text plyTexPttrnAnm__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::plyTexPttrnAnm() {
    if (mBtpNum != 0 || !cLib_calcTimer(&mBlinkTimer)) {
        mBlinkFrame += 1;
        if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
            if (mBtpNum != 0) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            } else {
                mBlinkTimer = cM_rndF(60.0f) + 30.0f;
                mBlinkFrame = 0;
            }
        }
    }
}

/* 00000BA8-00000BE4       .text setAnm_tex__11daNpc_Ac1_cFSc */
void daNpc_Ac1_c::setAnm_tex(s8 i_param_1) {
    if (mBtpNum != i_param_1) {
        mBtpNum = i_param_1;
        iniTexPttrnAnm(true);
    }
}

/* 00000BE4-00000D0C       .text setAnm_anm__11daNpc_Ac1_cFPQ211daNpc_Ac1_c9anm_prm_c */
BOOL daNpc_Ac1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (mAnmNum == i_anmPrmP->anmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->anmNum;
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, anmNum_toResID(mAnmNum), -1, "Ac");
    int wing_res_id = wingAnmNum_toResID(mAnmNum);
    mbHasArms = i_anmPrmP->hasArms == 1;
    if (mbHasArms) {
        dNpc_setAnmIDRes(mpArmMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, wing_res_id, -1, "Ac");
    } else {
        dNpc_setAnmIDRes(mpWingMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, wing_res_id, -1, "Ac");
    }
    mFrame = 0.0f;
    m859 = 0;
    mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00000D0C-00000D8C       .text setAnm__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {-1, -1,  0.0f, 0.0f, -1, -1},
        { 0,  0,  8.0f, 1.0f,  2,  1},
        {-1, -1,  0.0f, 0.0f, -1, -1},
    };
    if (a_anm_prm_tbl[mStatus].btpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStatus].btpNum);
    }
    if (a_anm_prm_tbl[mStatus].anmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStatus]);
    }
    return true;
}

/* 00000D8C-00000D90       .text chg_anmTag__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::chg_anmTag() {
}

/* 00000D90-00000D94       .text control_anmTag__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::control_anmTag() {
}

/* 00000D94-00000DD8       .text chg_anmAtr__11daNpc_Ac1_cFUc */
void daNpc_Ac1_c::chg_anmAtr(u8 i_param_1) {
    if (i_param_1 >= 6 || i_param_1 == mAnmAtr) {
        return;
    }
    mAnmAtr = i_param_1;
    setAnm_ATR(1);
}

/* 00000DD8-00000DE4       .text control_anmAtr__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::control_anmAtr() {
    switch (mAnmAtr) {
        case 6:
            break;
    }
}

/* 00000DE4-00000E4C       .text setAnm_ATR__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::setAnm_ATR(int i_param_1) {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 8.0f, 1.0f, 2, 1},
        {1, 0, 8.0f, 1.0f, 2, 1},
        {2, 1, 8.0f, 1.0f, 2, 1},
        {3, 0, 8.0f, 1.0f, 2, 1},
        {1, 2, 8.0f, 1.0f, 2, 1},
        {1, 1, 8.0f, 1.0f, 2, 1},
    };
    if (i_param_1 != 0) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000E4C-00000F10       .text anmAtr__11daNpc_Ac1_cFUs */
void daNpc_Ac1_c::anmAtr(u16 i_param_1) {
    switch (i_param_1) {
        case 6:
            if (m87B == 0) {
                mAnmAtr = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m87B += 1;
            }
            u8 tag = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if (tag != 0xFF && mAnmTag != tag) {
                mAnmTag = tag;
                chg_anmTag();
            }
            break;
        case 0xE:
            m87B = 0;
            break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00000F10-00000F60       .text eventOrder__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::eventOrder() {
    s8 condition = m874;
    if (condition == 1 || condition == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m874 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000F60-00000FA0       .text checkOrder__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::checkOrder() {
    u16 command = eventInfo.getCommand();
    if (command == 2) {
        return;
    }
    if (command != 1) {
        return;
    }
    if ((s8)m874 == 1 || (s8)m874 == 2) {
        m874 = 0;
        m869 = 1;
    }
}

/* 00000FA0-0000103C       .text chk_talk__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_talk() {
    bool uVar3 = true;
    m85B = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            m85B = dComIfGp_event_getPreItemNo();
        } else {
            uVar3 = false;
        }
    }
    return uVar3;
}

/* 0000103C-0000107C       .text chk_partsNotMove__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chk_partsNotMove() {
    bool result = false;
    if (m844 == m_jnt.getHead_y() && m846 == m_jnt.getBackbone_y() && m848 == current.angle.y) {
        result = true;
    }
    return result;
}

/* 0000107C-0000121C       .text lookBack__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    m844 = m_jnt.getHead_y();
    m846 = m_jnt.getBackbone_y();
    m848 = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = m86A;

    switch (mLookBackState) {
        case 1:
            dstPos = dNpc_playerEyePos(-20.0f);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 2:
            dstPos = m814;
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 3:
            desiredYrot = m854;
            break;
    }

    cLib_addCalcAngleS2(&m852, l_HIO.hio_prm.mMaxHeadTurnVel, 4, 0x800);
    if (!m_jnt.trnChk()) {
        m852 = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, m852, headOnlyFollow);
}

/* 0000121C-0000128C       .text next_msgStatus__11daNpc_Ac1_cFPUl */
u16 daNpc_Ac1_c::next_msgStatus(u32* i_msg_no) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*i_msg_no) {
        case 0x184C:
            *i_msg_no = 0x184D;
            break;
        case 0x184D:
            *i_msg_no = 0x184E;
            break;
        case 0x1850:
            *i_msg_no = 0x1851;
            break;
        case 0x1851:
            *i_msg_no = 0x1852;
            break;
        default:
            msg_status = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msg_status;
}

/* 0000128C-000012AC       .text getBitMask__11daNpc_Ac1_cFv */
s32 daNpc_Ac1_c::getBitMask() {
    s32 result = 0;
    switch (m879) {
        case 0:
            result = 0x10;
            break;
        default:
            break;
    }
    return result;
}

/* 000012AC-00001380       .text getMsg_AC1_0__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg_AC1_0() {
    s8 event_reg = (s8)dComIfGs_getEventReg(dSv_event_flag_c::UNK_B8FF);
    s32 bit_mask = getBitMask();
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580)) {
        if ((s8)bit_mask & event_reg) {
            return 0x1853;
        }
        dComIfGs_setEventReg(dSv_event_flag_c::UNK_B8FF, event_reg | (s8)bit_mask);
        return 0x1850;
    }
    if ((s8)bit_mask & event_reg) {
        return 0x184F;
    }
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_B8FF, event_reg | (s8)bit_mask);
    return 0x184C;
}

/* 00001380-000013BC       .text getMsg__11daNpc_Ac1_cFv */
u32 daNpc_Ac1_c::getMsg() {
    u32 retval = 0;
    switch (m879) {
        case 0:
            retval = getMsg_AC1_0();
            break;
        default:
            break;
    }
    return retval;
}

/* 000013BC-0000143C       .text chkAttention__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 0000143C-00001494       .text setAttention__11daNpc_Ac1_cFb */
void daNpc_Ac1_c::setAttention(bool i_param_1) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.hio_prm.mAttnYOffset, current.pos.z);
    if (m864 != 0 || i_param_1) {
        eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    }
}

/* 00001494-000014B0       .text charDecide__11daNpc_Ac1_cFi */
bool daNpc_Ac1_c::charDecide(int i_param_1) {
    m878 = 0;
    m879 = -1;
    m879 = 0;
    return TRUE;
}

/* 000014B0-00001508       .text event_actionInit__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::event_actionInit(int i_param_1) {
    int* substance = dComIfGp_evmng_getMyIntegerP(i_param_1, "ActNo");
    if (substance != NULL) {
        m86D = *substance;
    }
}

/* 00001508-00001528       .text event_action__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::event_action() {
    switch (m86D) {
        case 0:
            return TRUE;
        default:
            return TRUE;
    }
}

/* 00001528-00001614       .text privateCut__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::privateCut(int i_param_1) {
    if (i_param_1 != -1) {
        static char* a_cut_tbl[] = {
            "ActNo",
        };
        m86C = dComIfGp_evmng_getMyActIdx(i_param_1, a_cut_tbl, 1, TRUE, 0);
        if ((s8)m86C == -1) {
            dComIfGp_evmng_cutEnd(i_param_1);
            return;
        }
        if (dComIfGp_evmng_getIsAddvance(i_param_1)) {
            switch (m86C) {
                case 0:
                    event_actionInit(i_param_1);
                    break;
            }
        }
        int result;
        switch (m86C) {
            case 0:
                result = event_action();
                break;
            default:
                result = TRUE;
                break;
        }
        if ((u8)result) {
            dComIfGp_evmng_cutEnd(i_param_1);
        }
    }
}
/* 00001614-00001634       .text endEvent__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
}

/* 00001634-0000166C       .text isEventEntry__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL, 0);
}

/* 0000166C-000016C4       .text event_proc__11daNpc_Ac1_cFi */
void daNpc_Ac1_c::event_proc(int i_param_1) {
    if (!mEventCut.cutProc()) {
        privateCut(i_param_1);
    }
    lookBack();
}

/* 000016C4-00001770       .text set_action__11daNpc_Ac1_cFM11daNpc_Ac1_cFPCvPvPv_iPv */
BOOL daNpc_Ac1_c::set_action(ActionFunc i_action, void* i_param_2) {
    if (mCurrActionFunc != i_action) {
        if (mCurrActionFunc) {
            mActionIndex = 9;
            (this->*mCurrActionFunc)(i_param_2);
        }
        mCurrActionFunc = i_action;
        mActionIndex = 0;
        (this->*mCurrActionFunc)(i_param_2);
    }
    return TRUE;
}

/* 00001770-000017D4       .text setStt__11daNpc_Ac1_cFSc */
void daNpc_Ac1_c::setStt(s8 i_status) {
    u8 previous_status = mStatus;
    m84C = 0;
    mStatus = i_status;
    switch (mStatus) {
        case 2:
            mAnmAtr = 0xFF;
            mLookBackState = 1;
            mPrevStatus = previous_status;
            m_jnt.setTrn();
            break;
        case 1:
        default:
            setAnm();
            break;
    }
}

/* 000017D4-0000189C       .text wait_1__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::wait_1() {
    if (m874 == 1 || m874 >= 3) {
        return TRUE;
    }
    if (m869 != 0) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    m874 = 2;
    if (m868 != 0) {
        m84C = 0x3C;
    }
    if (cLib_calcTimer(&m84C)) {
        mLookBackState = 1;
    } else {
        mLookBackState = 3;
        m854 = mInitAngle.y;
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 0000189C-00001978       .text talk_1__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::talk_1() {
    u8 o_retval = chk_partsNotMove();
    if (mpCurrMsg != NULL) {
        m856 = mpCurrMsg->mStatus;
    } else {
        m856 = 0;
    }
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
            case 0x13:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3F02);
                m85B = 0xFF;
                m869 = 0;
                setStt(mPrevStatus);
                m84C = 0x3C;
                endEvent();
                break;
            case 0x2:
            case 0x6:
                break;
        }
    }
    return o_retval;
}

/* 00001978-00001A34       .text wait_action1__11daNpc_Ac1_cFPv */
BOOL daNpc_Ac1_c::wait_action1(void*) {
    switch (mActionIndex) {
        case 0:
            setStt(1);
            mActionIndex += 1;
            break;
        case 1:
        case 2:
        case 3:
            m868 = chkAttention();
            switch (mStatus) {
                case 1:
                    m864 = wait_1();
                    break;
                case 2:
                    m864 = talk_1();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00001A34-00001B74       .text demo__11daNpc_Ac1_cFv */
u8 daNpc_Ac1_c::demo() {
    if (demoActorID == 0) {
        if (mbInDemo != 0) {
            mbInDemo = 0;
        }
    } else {
        mbInDemo = 1;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if (m_hed_tex_pttrn) {
            mBlinkFrame += 1;
            if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demopattern = demo_actor->getP_BtpData("Ac");
        if (demopattern) {
            m_hed_tex_pttrn = demopattern;
            if (mBtpAnim.init(mpMorf->getModel()->getModelData(), m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, true, 0)) {
                mBtpNum = 3;
                mBlinkFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Ac");
    }
    return mbInDemo;
}

/* 00001B74-00001C70       .text shadowDraw__11daNpc_Ac1_cFv */
void daNpc_Ac1_c::shadowDraw() {
    cXyz local_18(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowID = dComIfGd_setShadow(
        mShadowID,
        1,
        mpMorf->getModel(),
        &local_18,
        800.0f,
        40.0f,
        current.pos.y,
        mObjAcch.GetGroundH(),
        mObjAcch.m_gnd,
        &tevStr,
        0,
        1.0f,
        dDlst_shadowControl_c::getSimpleTex()
    );
    if (mShadowID != 0) {
        if (mbHasArms) {
            dComIfGd_addRealShadow(mShadowID, mpArmMorf->getModel());
        } else {
            dComIfGd_addRealShadow(mShadowID, mpWingMorf->getModel());
        }
        if (mpItemModel != NULL) {
            dComIfGd_addRealShadow(mShadowID, mpItemModel);
        }
    }
}

/* 00001C70-00001DC4       .text _draw__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    if (m85D != 0 || m861 != 0) {
        return TRUE;
    }
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnim.entry(modelData, mBlinkFrame);
    mpMorf->entryDL();
    modelData->getMaterialTable().removeTexNoAnimator(m_hed_tex_pttrn);
    if (mbHasArms) {
        g_env_light.setLightTevColorType(mpArmMorf->getModel(), &tevStr);
        mpArmMorf->entryDL();
    } else {
        g_env_light.setLightTevColorType(mpWingMorf->getModel(), &tevStr);
        mpWingMorf->entryDL();
    }
    if (mpItemModel != NULL && mbHasArms) {
        g_env_light.setLightTevColorType(mpItemModel, &tevStr);
        mDoExt_modelEntryDL(mpItemModel);
    }
    shadowDraw();
    dSnap_RegistFig(0x8B, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00001DC4-00001F80       .text _execute__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_execute() {
    if (m863 == 0) {
        mInitPos = current.pos;
        mInitAngle = current.angle;
        m863 = 1;
    }
    m_jnt.setParam(l_HIO.hio_prm.mMaxBackboneX, l_HIO.hio_prm.mMaxBackboneY, l_HIO.hio_prm.mMinBackboneX, l_HIO.hio_prm.mMinBackboneY,
                   l_HIO.hio_prm.mMaxHeadX, l_HIO.hio_prm.mMaxHeadY, l_HIO.hio_prm.mMinHeadX, l_HIO.hio_prm.mMinHeadY,
                   l_HIO.hio_prm.mMaxTurnStep);
    if (m85D != 0 && demoActorID == 0) {
        return TRUE;
    }
    m860 = 0;
    m85D = 0;
    checkOrder();
    if (!demo()) {
        s32 staff_id = -1;
        if (dComIfGp_event_runCheck() && eventInfo.getCommand() != 1) {
            staff_id = isEventEntry();
        }
        if (staff_id >= 0) {
            event_proc(staff_id);
        } else {
            (this->*mCurrActionFunc)(NULL);
        }
        if (m860 == 0) {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if (m85F == 0) {
            shape_angle = current.angle;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbInDemo) {
        setCollision(50.0f, 140.0f);
    }
    return TRUE;
}

/* 00001F80-00001FFC       .text _delete__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Ac");
    if (heap != NULL) {
        if (mpMorf != NULL) {
            mpMorf->stopZelAnime();
        }
        if (mpWingMorf != NULL) {
            mpWingMorf->stopZelAnime();
        }
        if (mpArmMorf != NULL) {
            mpArmMorf->stopZelAnime();
        }
    }
    return TRUE;
}

/* 00001FFC-0000201C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->CreateHeap();
}

/* 0000201C-0000213C       .text _create__11daNpc_Ac1_cFv */
cPhs_State daNpc_Ac1_c::_create() {
    fopAcM_ct_Retail(this, daNpc_Ac1_c);
    static u32 a_size_tbl[] = {
        0x272E0,
    };
    cPhs_State state = dComIfG_resLoad(&mPhs, "Ac");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    if (!charDecide(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[m878])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -200.0f, -20.0f, -200.0f, 50.0f, 140.0f, 50.0f);
    return createInit() ? state : cPhs_ERROR_e;
}

/* 0000256C-00002838       .text create_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes("Ac", 5);
    JUT_ASSERT(0x6BE, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Ac", 1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0x80000,
        0x11020022
    );
    if (mpMorf == NULL) {
        return NULL;
    } else if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x6D2, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x6D5, m_bbone_jnt_num >= 0);
    m_arm_L_jnt_num = a_mdl_dat->getJointName()->getIndex("armL");
    JUT_ASSERT(0x6D8, m_arm_L_jnt_num >= 0);
    m_arm_R_jnt_num = a_mdl_dat->getJointName()->getIndex("armR");
    JUT_ASSERT(0x6DB, m_arm_R_jnt_num >= 0);
    return a_mdl_dat;
}

/* 00002838-00002A4C       .text create_wng_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_wng_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes("Ac", 3);
    JUT_ASSERT(0x6EA, a_mdl_dat != NULL);
    mpWingMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Ac", 0),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0x80000,
        0x11000002
    );
    if (mpWingMorf == NULL) {
        return NULL;
    } else if (mpWingMorf->getModel() == NULL) {
        mpWingMorf = NULL;
        return NULL;
    }

    m_wngL1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingL_loc");
    JUT_ASSERT(0x6FF, m_wngL1_jnt_num >= 0);
    m_wngR1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingR_loc");
    JUT_ASSERT(0x702, m_wngR1_jnt_num >= 0);
    return a_mdl_dat;
}

/* 00002A4C-00002CBC       .text create_arm_Anm__11daNpc_Ac1_cFv */
J3DModelData* daNpc_Ac1_c::create_arm_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes("Ac", 2);
    JUT_ASSERT(0x711, a_mdl_dat != NULL);
    mpArmMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Ac", 0),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0x80000,
        0x11000002
    );
    if (mpArmMorf == NULL) {
        return NULL;
    } else if (mpArmMorf->getModel() == NULL) {
        mpArmMorf = NULL;
        return NULL;
    }

    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(0x726, m_hnd_R_jnt_num >= 0);
    m_armL1_jnt_num = a_mdl_dat->getJointName()->getIndex("armL_loc");
    JUT_ASSERT(0x729, m_armL1_jnt_num >= 0);
    m_armR1_jnt_num = a_mdl_dat->getJointName()->getIndex("armR_loc");
    JUT_ASSERT(0x72C, m_armR1_jnt_num >= 0);
    return a_mdl_dat;
}

/* 00002CBC-00002DC8       .text create_itm_Mdl__11daNpc_Ac1_cFv */
bool daNpc_Ac1_c::create_itm_Mdl() {
    mpItemModel = NULL;
    J3DModelData* a_mdl_dat;
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1580)) {
        a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes("Ac", 0xF);
    } else {
        a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes("Ac", 4);
    }
    JUT_ASSERT(0x744, a_mdl_dat != NULL);
    mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    return true;
}

/* 00002DC8-00003044       .text CreateHeap__11daNpc_Ac1_cFv */
BOOL daNpc_Ac1_c::CreateHeap() {
    J3DModelData* modeldat;
    J3DModelData* anm_model = create_Anm();
    if (!anm_model) {
        return FALSE;
    }
    mBtpNum = 0;
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    modeldat = create_wng_Anm();
    if (!modeldat) {
        mpMorf = NULL;
        return FALSE;
    }
    J3DModelData* arm_anmdata = create_arm_Anm();
    if (arm_anmdata != NULL && create_itm_Mdl()) {
        for (u16 i = 0; i < modeldat->getJointNum(); i++) {
            if ((i == m_wngL1_jnt_num) || (i == m_wngR1_jnt_num)) {
                mpWingMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Wng);
            }
        }
        mpWingMorf->getModel()->setUserArea((u32)this);
        for (u16 i = 0; i < arm_anmdata->getJointNum(); i++) {
            if ((i == m_armL1_jnt_num) || (i == m_armR1_jnt_num)) {
                mpArmMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Arm);
            }
        }
        mpArmMorf->getModel()->setUserArea((u32)this);
        for (u16 i = 0; i < anm_model->getJointNum(); i++) {
            if ((i == m_hed_jnt_num) || (i == m_bbone_jnt_num) || (i == m_arm_L_jnt_num) || (i == m_arm_R_jnt_num)) {
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ac1);
            }
        }
        mpMorf->getModel()->setUserArea((u32)this);
        mAcchCir.SetWall(30.0f, 50.0f);
        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
        return TRUE;
    } else {
        mpMorf = NULL;
        mpWingMorf = NULL;
        return FALSE;
    }
}

/* 00003044-00003064       .text daNpc_Ac1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ac1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_create();
}

/* 00003064-00003084       .text daNpc_Ac1_Delete__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Delete(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_delete();
}

/* 00003084-000030A4       .text daNpc_Ac1_Execute__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Execute(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_execute();
}

/* 000030A4-000030C4       .text daNpc_Ac1_Draw__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_Draw(daNpc_Ac1_c* i_this) {
    return ((daNpc_Ac1_c*)i_this)->_draw();
}

/* 000030C4-000030CC       .text daNpc_Ac1_IsDelete__FP11daNpc_Ac1_c */
static BOOL daNpc_Ac1_IsDelete(daNpc_Ac1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ac1_Method = {
    (process_method_func)daNpc_Ac1_Create,
    (process_method_func)daNpc_Ac1_Delete,
    (process_method_func)daNpc_Ac1_Execute,
    (process_method_func)daNpc_Ac1_IsDelete,
    (process_method_func)daNpc_Ac1_Draw,
};

actor_process_profile_definition g_profile_NPC_AC1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_AC1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ac1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_AC1_e,
    /* Actor SubMtd */ &l_daNpc_Ac1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};










