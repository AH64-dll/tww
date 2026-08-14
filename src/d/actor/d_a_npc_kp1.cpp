/**
 * d_a_npc_kp1.cpp
 * NPC - Maggie (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kp1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_vibration.h"

static daNpc_Kp1_HIO_c l_HIO;

enum { ANM_END = 6, TEXPATTERN_END = 2 };

/* 000000EC-00000150       .text __ct__15daNpc_Kp1_HIO_cFv */
daNpc_Kp1_HIO_c::daNpc_Kp1_HIO_c() { /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX          */ 0x1FFE,
        /* mMaxHeadY          */ 0x38E0,
        /* mMinHeadX          */ 0xF448,
        /* mMinHeadY          */ 0xC720,
        /* mMaxBackboneX      */ 0x0000,
        /* mMaxBackboneY      */ 0x0000,
        /* mMinBackboneX      */ 0x0000,
        /* mMinBackboneY      */ 0x0000,
        /* mMaxTurnStep       */ 0x05DC,
        /* mCalcAngleTarget   */ 0x0400,
        /* mAttPosOffsetY     */ 170.0f,
        /* field_0x18         */ 0x00000000,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

/* 00000198-0000035C       .text nodeCallBack_Kp__FP7J3DNodei */
static BOOL nodeCallBack_Kp(J3DNode* i_node, int i_param) { /* Nonmatching */
    if (i_param == 0) {
        daNpc_Kp1_c* actor = (daNpc_Kp1_c*)j3dSys.getModel()->getUserArea();
        if (actor != NULL) {
            static cXyz a_att_pos_offst;
            static cXyz a_eye_pos_offst(20.0f, -20.0f, 0.0f);

            J3DJoint* jnt_p = (J3DJoint*)i_node;
            s32 jnt_no = jnt_p->getJntNo();
            J3DModel* model = j3dSys.getModel();

            mDoMtx_stack_c::copy(model->getAnmMtx(jnt_no));
            if (jnt_no == actor->m_head_jnt_num) {
                mDoMtx_stack_c::multVec(&a_att_pos_offst, &actor->mAttPos);
                mDoMtx_stack_c::YrotM(-actor->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(-actor->m_jnt.getHead_x());
                mDoMtx_stack_c::multVec(&a_eye_pos_offst, &actor->mEyePos);
            } else if (jnt_no == actor->m_backbone_jnt_num) {
                mDoMtx_stack_c::XrotM(actor->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(-actor->m_jnt.getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 00000398-000004D0       .text createInit__11daNpc_Kp1_cFv */
bool daNpc_Kp1_c::createInit() { /* Nonmatching */
    if (!dComIfGs_isEventBit(0x2D01)) {
        return false;
    }

    mEvtCut.setActorInfo2("Kp1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    gravity = -4.0f;
    mMsgNo = 0xFF;
    mLookTarget.set(current.pos);

    set_action(&daNpc_Kp1_c::wait_action1, NULL);

    shape_angle = current.angle;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    mAttnFlag = 1;
    setMtx();
    return true;
}

/* 000004D0-00000658       .text setMtx__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::setMtx() { /* Nonmatching */
    if (mDemoFlag == 0) {
        playTexPatternAnm();
        mPlayEnd = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mMorfFrame) {
            mPlayEnd = 1;
        }
        mMorfFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    mpMorf->getModel()->setAnmMtx(m_handL_jnt_num, mDoMtx_stack_c::get());
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
    mpHandLModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpHandLModel->calc();
    setAttention();
}

/* 00000658-00000760       .text anmResID__11daNpc_Kp1_cFiPiPi */
int daNpc_Kp1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    static const int a_anm_idx_tbl[][2] = {
        { 5, -1 },
        { 1, -1 },
        { 0, -1 },
        { 3, -1 },
        { 2, -1 },
        { 4, -1 },
    };

    JUT_ASSERT(0x12A, 0 <= i_num && i_num < ANM_END);
    JUT_ASSERT(0x12B, o_bck_num && o_bas_num);
    *o_bck_num = a_anm_idx_tbl[i_num][0];
    *o_bas_num = a_anm_idx_tbl[i_num][1];
    return 1;
}

/* 00000760-000007FC       .text BtpNum2ResID__11daNpc_Kp1_cFiPi */
int daNpc_Kp1_c::BtpNum2ResID(int i_num, int* o_resID) { /* Nonmatching */
    static const int a_btp_arc_ix_tbl[] = {
        9,
        9,
    };

    JUT_ASSERT(0x141, 0 <= i_num && i_num < TEXPATTERN_END);
    *o_resID = a_btp_arc_ix_tbl[i_num];
    return 1;
}

/* 000007FC-00000840       .text setAnm_tex__11daNpc_Kp1_cFSc */
void daNpc_Kp1_c::setAnm_tex(s8 i_btpNum) {
    if (i_btpNum < 0) {
        return;
    }
    if (i_btpNum != mBtpNum) {
        mBtpNum = i_btpNum;
        initTexPatternAnm(true);
    }
}

/* 00000840-00000970       .text init_btp__11daNpc_Kp1_cFbi */
bool daNpc_Kp1_c::init_btp(bool i_bModify, int i_btpNum) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    if (i_btpNum >= 0) {
        int resID;
        BtpNum2ResID(i_btpNum, &resID);
        mpBtpAnm = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Kp", resID);
        JUT_ASSERT(0x162, mpBtpAnm != 0);
        int dummy = 0;
        if (mBtpAnm.init(modelData, mpBtpAnm, 1, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_bModify, 0) == 0) {
            return false;
        }
        mBtpFrame = 0;
        mBtpTimer = 0;
        if (mBtpNum == 1) {
            mBtpFrame = 1;
        }
    }
    return true;
}

/* 00000970-000009B4       .text initTexPatternAnm__11daNpc_Kp1_cFb */
bool daNpc_Kp1_c::initTexPatternAnm(bool i_bModify) {
    bool ret = false;
    if (init_btp(i_bModify, mBtpNum)) {
        ret = true;
    }
    return ret;
}

/* 000009B4-00000A80       .text playTexPatternAnm__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::playTexPatternAnm() {
    bool flag = true;
    s8 btp_num = mBtpNum;
    if (btp_num != 1) {
        if (btp_num == 0) {
            flag = cLib_calcTimer(&mBtpTimer) == 0;
        }
    }
    if (!flag) {
        return;
    }
    s16 frame_max = mpBtpAnm->getFrameMax();
    ++mBtpFrame;
    if (mBtpFrame >= frame_max) {
        if (mBtpNum != 0) {
            mBtpFrame = mpBtpAnm->getFrameMax();
        } else {
            mBtpFrame = 0;
            mBtpTimer = cM_rndF(60.0f) + 30.0f;
        }
    }
}

/* 00000A80-00000B4C       .text setAnm_anm__11daNpc_Kp1_cFPQ211daNpc_Kp1_c9anm_prm_c */
bool daNpc_Kp1_c::setAnm_anm(anm_prm_c* i_anmPrmP) { /* Nonmatching */
    u32 ret = 0;
    int bck_idx;
    int bas_idx;

    if (i_anmPrmP->bckNum >= 0 && mBckNum != i_anmPrmP->bckNum) {
        mBckNum = i_anmPrmP->bckNum;
        if (mpMorf != NULL) {
            anmResID(mBckNum, &bck_idx, &bas_idx);
            if (bck_idx >= 0) {
                dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed,
                                 bck_idx, bas_idx, "Kp");
            }
            ret = 1;
        }
        mMorfFrame = 0.0f;
        mAnmTimer = 0;
        mPlayEnd = 0;
    }
    return ret;
}

/* 00000B4C-00000BB8       .text setAnm_NUM__11daNpc_Kp1_cFii */
void daNpc_Kp1_c::setAnm_NUM(int i_prmIdx, int i_texPattern) { /* Nonmatching */
    static daNpc_Kp1_c::anm_prm_c a_anm_prm_tbl[] = {
        { 0, 0, 0, 8.0f, 1.0f, 2 },
        { 1, 0, 0, 8.0f, 1.0f, 2 },
        { 2, 0, 0, 8.0f, 1.0f, 2 },
        { 3, 0, 0, 8.0f, 1.0f, 2 },
        { 4, 0, 0, 8.0f, 1.0f, 2 },
        { 5, 0, 0, 8.0f, 1.0f, 2 },
    };
    if (i_texPattern) {
        setAnm_tex(a_anm_prm_tbl[i_prmIdx].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_prmIdx]);
}

/* 00000BB8-00000C20       .text setAnm__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::setAnm() { /* Nonmatching */
    static daNpc_Kp1_c::anm_prm_c a_anm_prm_tbl[] = {
        { -1, 0, 0, 0.0f, 0.0f, -1 },
        { 0, 0, 0, 8.0f, 1.0f, 2 },
        { -1, 0, 0, 0.0f, 0.0f, -1 },
    };
    setAnm_tex(a_anm_prm_tbl[mStatus].btpNum);
    setAnm_anm(&a_anm_prm_tbl[mStatus]);
}

/* 00000C20-00000C2C       .text chngAnmTag__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::chngAnmTag() {
    switch (mAnmTag) {
    case 0:
        break;
    }
}

/* 00000C2C-00000C38       .text ctrlAnmTag__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::ctrlAnmTag() {
    switch (mAnmAtr) {
    case 0:
        break;
    }
}

/* 00000C38-00000CA4       .text chngAnmAtr__11daNpc_Kp1_cFUc */
void daNpc_Kp1_c::chngAnmAtr(u8 param_1) {
    if (param_1 >= 7) {
        return;
    }
    if (param_1 == mAnmAtr) {
        return;
    }
    mShadowIdx = 0;
    if (param_1 == 2) {
        mShadowIdx = 2;
    } else if (param_1 == 3) {
        mShadowIdx = 1;
    }
    mAnmAtr = param_1;
    setAnm_ATR(1);
}

/* 00000CA4-00000D54       .text ctrlAnmAtr__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::ctrlAnmAtr() { /* Nonmatching */
    switch (mAnmAtr) {
    case 1:
        if (mPlayEnd != 0) {
            mAnmTimer++;
            if (mAnmTimer >= 2) {
                mAnmAtr = 0;
                setAnm_NUM(0, 1);
            }
        }
        break;
    case 6:
        if (mPlayEnd != 0) {
            mAnmTimer++;
            if (mAnmTimer >= 1) {
                mAnmAtr = 0;
                setAnm_NUM(0, 1);
            }
        }
        break;
    }
}

/* 00000D54-00000DBC       .text setAnm_ATR__11daNpc_Kp1_cFi */
void daNpc_Kp1_c::setAnm_ATR(int i_texPattern) { /* Nonmatching */
    static daNpc_Kp1_c::anm_prm_c a_anm_prm_tbl[] = {
        { 0, 0, 0, 8.0f, 1.0f, 2 },
        { 1, 0, 0, 8.0f, 1.0f, 2 },
        { 2, 0, 0, 8.0f, 1.0f, 2 },
        { 3, 0, 0, 8.0f, 1.0f, 2 },
        { 4, 0, 0, 8.0f, 1.0f, 2 },
        { 5, 0, 0, 8.0f, 1.0f, 2 },
        { 1, 1, 0, 8.0f, 1.0f, 2 },
    };
    if (i_texPattern) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000DBC-00000E78       .text anmAtr__11daNpc_Kp1_cFUs */
void daNpc_Kp1_c::anmAtr(u16 i_msgStatus) {
    if (i_msgStatus == fopMsgStts_MSG_TYPING_e) {
        if (mAnmAtrStep == 0) {
            mAnmTag = 0xFF;
            chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mAnmAtrStep++;
        }
        u8 tag = dComIfGp_getMesgAnimeTagInfo();
        if (tag != 0xFF && tag != mAnmTag) {
            dComIfGp_clearMesgAnimeTagInfo();
            mAnmTag = tag;
            chngAnmTag();
        }
    } else if (i_msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
        mAnmAtrStep = 0;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000E78-00000EE0       .text setStt__11daNpc_Kp1_cFSc */
void daNpc_Kp1_c::setStt(s8 param_1) { /* Nonmatching */
    s8 old_type = mType;
    mShadowIdx = 0;
    mType = param_1;

    switch (mType) {
    case 2:
        mLookMode = 1;
        m_jnt.setTrn();
        mAnmAtr = 0xFF;
        mPrevType = old_type;
        mCancelFlag = 0;
        break;
    default:
        setAnm();
        break;
    }
}

/* 00000EE0-0000102C       .text next_msgStatus__11daNpc_Kp1_cFPUl */
u16 daNpc_Kp1_c::next_msgStatus(u32* pMsgNo) { /* Nonmatching */
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
    case 0x1E84:
        *pMsgNo = 0x1E85;
        break;
    case 0x1E85:
        *pMsgNo = 0x1E86;
        break;
    case 0x1E88:
        *pMsgNo = 0x1E89;
        break;
    case 0x1E8A:
        *pMsgNo = 0x1E8B;
        break;
    case 0x1E8B:
        *pMsgNo = 0x1E8C;
        break;
    case 0x1E8C:
        *pMsgNo = 0x1E8D;
        break;
    case 0x1E8D:
        *pMsgNo = 0x1E8E;
        break;
    case 0x1E8E:
        *pMsgNo = 0x1E8F;
        break;
    case 0x1E8F:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *pMsgNo = 0x1E91;
            break;
        case 1:
            *pMsgNo = 0x1E90;
            break;
        }
        break;
    case 0x1E96:
        *pMsgNo = 0x1E97;
        mCancelFlag = 1;
        break;
    case 0x1E97:
        *pMsgNo = 0x1E98;
        break;
    case 0x1E98:
        *pMsgNo = 0x1E99;
        break;
    case 0x1E99:
        *pMsgNo = 0x1E9A;
        break;
    case 0x1E9A:
        *pMsgNo = 0x1E9B;
        break;
    case 0x1E9B:
        *pMsgNo = 0x1E9C;
        break;
    case 0x1E9C:
        *pMsgNo = 0x1E9D;
        break;
    case 0x1E91:
        mStatus = 3;
        goto msg_ends;
    case 0x1E9D:
        mStatus = 4;
        goto msg_ends;
    case 0x1E90:
        mPresentFlag = 1;
    default:
    msg_ends:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 0000102C-00001178       .text getMsg__11daNpc_Kp1_cFv */
u32 daNpc_Kp1_c::getMsg() { /* Nonmatching */
    if (mMsgNo != 0xFF) {
        if (mMsgNo == 0x9B) {
            return 0x1E96;
        }
        return (mMsgNo == 0x45) + 0x1E9F;
    }
    if (mTalkFlag != 0) {
        mTalkFlag = 0;
        return 0x1E92;
    }
    if (mEventFlag != 0) {
        mEventFlag = 0;
        return 0x1E9E;
    }
    if (dComIfGs_isGetItemReserve(0xF)) {
        if (!dComIfGs_checkReserveItem(0x9B) && dComIfGs_getEventReg(0xCCFF) != 1) {
            return 0x1E83;
        }
    }
    if (dComIfGs_isGetItemReserve(0xE)) {
        return dComIfGs_isGetItemBeast(0) ? 0x1E87 : 0x1E88;
    }
    return mPresentFlag ? 0x1E93 : 0x1E8A;
}

/* 00001178-00001204       .text eventOrder__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::eventOrder() { /* Nonmatching */
    static char* a_demo_name_tbl[] = {
        "GET_MAGYS_LTTR",
        "GET_KAKERA_HRT",
    };
    if (mStatus == 1 || mStatus == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mStatus == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mStatus >= 3) {
        fopAcM_orderOtherEvent2(this, a_demo_name_tbl[mStatus - 3], 1, 0xFFFF);
    }
}

/* 00001204-000012E4       .text checkOrder__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::checkOrder() { /* Nonmatching */
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck("GET_MAGYS_LTTR") && mStatus == 3) {
            mStatus = 0;
        }
        if (dComIfGp_evmng_startCheck("GET_KAKERA_HRT") && mStatus == 4) {
            mStatus = 0;
        }
    } else if (eventInfo.getCommand() == 1 && (mStatus == 1 || mStatus == 2)) {
        mStatus = 0;
        mTalkEnd = 1;
    }
}

/* 000012E4-00001474       .text lookBack__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::lookBack() { /* Nonmatching */
    cXyz player_eye_pos;
    cXyz current_pos;

    current_pos = current.pos;
    current_pos.y = eyePos.y;

    player_eye_pos.set(0.0f, 0.0f, 0.0f);

    cXyz* player_eye_pos_p = NULL;
    s16 target_y = current.angle.y;
    bool look_flag = mLookBackFlag;

    switch (mLookMode) {
    case 0:
        break;
    case 1:
        player_eye_pos = dNpc_playerEyePos(-20.0f);
        player_eye_pos_p = &player_eye_pos;
        current_pos = current.pos;
        current_pos.y = eyePos.y;
        break;
    case 2:
        player_eye_pos = mLookTarget;
        player_eye_pos_p = &player_eye_pos;
        current_pos = current.pos;
        current_pos.y = eyePos.y;
        break;
    case 3:
        target_y = mLookStartAngle;
        break;
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&mLookAngle, l_HIO.mPrmTbl.mCalcAngleTarget, 4, 0x800);
    } else {
        mLookAngle = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, player_eye_pos_p, current_pos, target_y, mLookAngle, look_flag);
}

/* 00001474-000014F4       .text chkAttention__11daNpc_Kp1_cFv */
bool daNpc_Kp1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 000014F4-00001558       .text setAttention__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::setAttention() {
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY,
        current.pos.z
    );
    if (mAttnFlag != 0 || mTalkResult != 0) {
        eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
        mAttnFlag = 0;
    }
}

/* 00001558-000015F4       .text chk_talk__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::chk_talk() {
    BOOL ret = TRUE;
    mMsgNo = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mMsgNo = dComIfGp_event_getPreItemNo();
        } else {
            ret = FALSE;
        }
    }
    return ret;
}

/* 000015F4-00001620       .text decideType__11daNpc_Kp1_cFi */
bool daNpc_Kp1_c::decideType(int i_type) { /* Nonmatching */
    UNUSED(i_type);
    mSpecificType = -1;
    if (fopAcM_GetName(this) == 0x165) {
        mSpecificType = 0;
        mSubType = 0;
    }
    return true;
}

/* 00001620-000016A8       .text event_actionInit__11daNpc_Kp1_cFi */
void daNpc_Kp1_c::event_actionInit(int i_staffIdx) {
    int* pSubstance = (int*)dComIfGp_getPEvtManager()->getMySubstanceP(i_staffIdx, "ActNo", 3);
    dComIfGp_getPEvtManager()->getMySubstanceP(i_staffIdx, "Timer", 3);
    if (pSubstance != NULL) {
        mEventAction = *pSubstance;
    }
}

/* 000016A8-00001778       .text event_action__11daNpc_Kp1_cFv */
bool daNpc_Kp1_c::event_action() { /* Nonmatching */
    u32 ret = 0;
    switch (mEventAction) {
    case 0: {
        fpc_ProcID itemId = fopAcM_createItemForPresentDemo(&current.pos, 0x9A, 0, -1, -1, NULL, NULL);
        if (itemId != 0xFFFFFFFF) {
            dComIfGp_event_setItemPartnerId(itemId);
            ret = 1;
        }
        break;
    }
    case 1: {
        fpc_ProcID itemId = fopAcM_createItemForPresentDemo(&current.pos, 0x7, 0, -1, -1, NULL, NULL);
        if (itemId != 0xFFFFFFFF) {
            dComIfGp_event_setItemPartnerId(itemId);
            ret = 1;
        }
        break;
    }
    default:
        ret = 1;
        break;
    }
    return ret;
}

/* 00001778-00001880       .text privateCut__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::privateCut() { /* Nonmatching */
    static char* cut_name_tbl[] = {
        "ACTION",
    };
    int staffIdx = dComIfGp_evmng_getMyStaffId("Kp1");
    if (staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, 1, 1, 0);
        if (mActIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch (mActIdx) {
                case 0:
                    event_actionInit(staffIdx);
                    break;
                }
            }
            bool bVar1;
            switch (mActIdx) {
            case 0:
                bVar1 = event_action();
                break;
            default:
                bVar1 = 1;
                break;
            }
            if (bVar1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }
    }
}

/* 00001880-000018A0       .text endEvent__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::endEvent() {
    g_dComIfG_gameInfo.play.mEvtCtrl.mEventFlag |= 8;
    mAnmAtr = 0xFF;
}

/* 000018A0-00001998       .text event_proc__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::event_proc() { /* Nonmatching */
    if (dComIfGp_evmng_endCheck("GET_MAGYS_LTTR")) {
        endEvent();
        mStatus = 1;
        mTalkFlag = 1;
    } else if (dComIfGp_evmng_endCheck("GET_KAKERA_HRT")) {
        dComIfGs_setEventReg(0xCCFF, 0);
        endEvent();
        mStatus = 1;
        mEventFlag = 1;
    } else {
        if (!mEvtCut.cutProc()) {
            privateCut();
        }
    }
    shape_angle = current.angle;
}

/* 00001998-00001A44       .text set_action__11daNpc_Kp1_cFM11daNpc_Kp1_cFPCvPvPv_iPv */
bool daNpc_Kp1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc != 0) {
            mWaitFlag = -1;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        mWaitFlag = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return true;
}

/* 00001A44-00001AFC       .text wait01__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::wait01() { /* Nonmatching */
    if (mStatus == 3 || mStatus == 4 || mStatus == 1) {
        return TRUE;
    }
    if (mTalkEnd != 0) {
        if (chk_talk()) {
            setStt(2);
        }
    } else {
        mStatus = 2;
        if (mAttention != 0) {
            mLookMode = 1;
            m_jnt.setTrn();
        } else {
            mLookMode = 3;
            mLookStartAngle = mSaveAngleY;
            m_jnt.setTrn();
        }
    }
    return TRUE;
}

/* 00001AFC-00001BD4       .text talk01__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::talk01() {
    BOOL ret = TRUE;
    talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case fopMsgStts_MSG_DESTROYED_e:
            switch (mCurrMsgNo) {
            case 0x1E9D:
                dComIfGs_setReserveItemEmpty();
                break;
            }
            mMsgNo = 0xFF;
            setStt(mPrevType);
            mTalkClear = 0;
            mTalkEnd = 0;
            endEvent();
            break;
        case fopMsgStts_BOX_OPENING_e:
        case fopMsgStts_MSG_TYPING_e:
            if (mCancelFlag != 0) {
                dComIfGp_evmng_CancelPresent();
                mCancelFlag = 0;
            }
            break;
        }
    }
    return ret;
}

/* 00001BD4-00001C88       .text wait_action1__11daNpc_Kp1_cFPv */
BOOL daNpc_Kp1_c::wait_action1(void* param_1) {
    UNUSED(param_1);

    if (mWaitFlag == 0) {
        setStt(1);
        mWaitFlag++;
    } else if (mWaitFlag != -1) {
        mAttention = chkAttention();
        switch (mType) {
        case 2:
            mTalkResult = talk01();
            break;
        case 1:
            mTalkResult = wait01();
            break;
        default:
            mTalkResult = 0;
            break;
        }
        lookBack();
    }
    return TRUE;
}

/* 00001C88-00001DB8       .text demo__11daNpc_Kp1_cFv */
u8 daNpc_Kp1_c::demo() { /* Nonmatching */
    if (demoActorID == 0) {
        if (mDemoFlag != 0) {
            mDemoFlag = 0;
        }
    } else {
        mDemoFlag = 1;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        s16 frame_max = mpBtpAnm->getFrameMax();
        mBtpFrame++;
        if (mBtpFrame >= frame_max) {
            mBtpFrame = frame_max;
        }
        J3DAnmTexPattern* btp = demo_actor->getP_BtpData("Kp");
        if (btp != NULL) {
            mpBtpAnm = btp;
            if (mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, 1, J3DFrameCtrl::EMode_LOOP, 1.0f, 0,
                             -1, true, 0) != 0)
            {
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this, dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e |
                                     dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
                          mpMorf, "Kp", 0, NULL, 0, 0);
    }
    return mDemoFlag;
}

/* 00001DB8-00001E9C       .text shadowDraw__11daNpc_Kp1_cFv */
void daNpc_Kp1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId,
        1,
        mpMorf->getModel(),
        &pos,
        800.0f, 40.0f, current.pos.y,
        mObjAcch.GetGroundH(), mObjAcch.m_gnd,
        &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
    if (mShadowId != 0) {
        switch (mShadowIdx) {
        case 1:
            dComIfGd_addRealShadow(mShadowId, mpModel);
            break;
        case 2:
            dComIfGd_addRealShadow(mShadowId, mpHandLModel);
            break;
        }
    }
}

/* 00001E9C-00001FA4       .text _draw__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::_draw() { /* Nonmatching */
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* modelData = pModel->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(modelData, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(modelData);

    J3DModel* subModel = NULL;
    switch (mShadowIdx) {
    case 1:
        subModel = mpModel;
        break;
    case 2:
        subModel = mpHandLModel;
        break;
    }
    if (subModel != NULL) {
        g_env_light.setLightTevColorType(subModel, &tevStr);
        mDoExt_modelEntryDL(subModel);
    }
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK5A, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00001FA4-00002100       .text _execute__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::_execute() { /* Nonmatching */
    if (mInitFlag == 0) {
        mSavePos = current.pos;
        mSaveAngleX = current.angle.x;
        mSaveAngleY = current.angle.y;
        mSaveAngleZ = current.angle.z;
        mInitFlag = 1;
    }
    m_jnt.setParam(
        l_HIO.mPrmTbl.mMaxBackboneX,
        l_HIO.mPrmTbl.mMaxBackboneY,
        l_HIO.mPrmTbl.mMinBackboneX,
        l_HIO.mPrmTbl.mMinBackboneY,
        l_HIO.mPrmTbl.mMaxHeadX,
        l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX,
        l_HIO.mPrmTbl.mMinHeadY,
        l_HIO.mPrmTbl.mMaxTurnStep
    );
    checkOrder();
    if (!demo()) {
        if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            event_proc();
        } else {
            (this->*mCurrProcFunc)(NULL);
        }
        shape_angle = current.angle;
    }
    eventOrder();
    if (mDemoFlag == 0) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    setMtx();
    setCollision(60.0f, 170.0f);
    return TRUE;
}

/* 00002100-0000215C       .text _delete__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Kp");
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 0000215C-0000217C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* actor) {
    return ((daNpc_Kp1_c*)actor)->CreateHeap();
}

/* 0000217C-000022A0       .text _create__11daNpc_Kp1_cFv */
cPhs_State daNpc_Kp1_c::_create() { /* Nonmatching */
    static u32 a_heap_size_tbl[] = {
        0x272E0,
    };

    fopAcM_SetupActor(this, daNpc_Kp1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Kp");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_heap_size_tbl[mSpecificType])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0f, -20.0f, -50.0f, 50.0f, 170.0f, 50.0f);
    if (createInit() == 0) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 000026D0-00002B14       .text CreateHeap__11daNpc_Kp1_cFv */
BOOL daNpc_Kp1_c::CreateHeap() { /* Nonmatching */
    static u8 a_tex_pattern_num_tbl[] = {
        0,
    };
    J3DModelData* a_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Kp", 8);
    JUT_ASSERT(0x62C, a_mdl_data != 0);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_data,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Kp", 5),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020002
    );
    if (mpMorf == NULL) {
        return FALSE;
    }
    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    m_head_jnt_num = a_mdl_data->getJointName()->getIndex("head");
    JUT_ASSERT(0x63F, m_head_jnt_num >= 0);
    m_backbone_jnt_num = a_mdl_data->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x641, m_backbone_jnt_num >= 0);
    m_handL_jnt_num = a_mdl_data->getJointName()->getIndex("handL");
    JUT_ASSERT(0x643, m_handL_jnt_num >= 0);

    mBtpNum = a_tex_pattern_num_tbl[mSpecificType];
    if (initTexPatternAnm(false) == 0) {
        mpMorf = NULL;
        return FALSE;
    }
    J3DModelData* a_itm_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Kp", 6);
    JUT_ASSERT(0x655, a_itm_mdl_data != 0);
    mpModel = mDoExt_J3DModel__create(a_itm_mdl_data, 0x80000, 0x11020002);
    if (mpModel == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    J3DModelData* a_itm2_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Kp", 7);
    JUT_ASSERT(0x65F, a_itm2_mdl_data != 0);
    mpHandLModel = mDoExt_J3DModel__create(a_itm2_mdl_data, 0x80000, 0x11020002);
    if (mpHandLModel == NULL) {
        mpMorf = NULL;
        return FALSE;
    }

    for (u16 i = 0; i < a_mdl_data->getJointNum(); i++) {
        if (i == m_head_jnt_num || i == m_backbone_jnt_num) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Kp);
        }
    }
    mpMorf->getModel()->setUserArea((u32)(this));

    mAcchCir.SetWall(170.0f, 50.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                 fopAcM_GetSpeed_p(this), NULL, NULL);
    return TRUE;
}

/* 00002B14-00002B34       .text daNpc_Kp1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kp1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_create();
}

/* 00002B34-00002B54       .text daNpc_Kp1_Delete__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_Delete(daNpc_Kp1_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_delete();
}

/* 00002B54-00002B74       .text daNpc_Kp1_Execute__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_Execute(daNpc_Kp1_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_execute();
}

/* 00002B74-00002B94       .text daNpc_Kp1_Draw__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_Draw(daNpc_Kp1_c* i_this) {
    return ((daNpc_Kp1_c*)i_this)->_draw();
}

/* 00002B94-00002B9C       .text daNpc_Kp1_IsDelete__FP11daNpc_Kp1_c */
static BOOL daNpc_Kp1_IsDelete(daNpc_Kp1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kp1_Method = {
    (process_method_func)daNpc_Kp1_Create,
    (process_method_func)daNpc_Kp1_Delete,
    (process_method_func)daNpc_Kp1_Execute,
    (process_method_func)daNpc_Kp1_IsDelete,
    (process_method_func)daNpc_Kp1_Draw,
};

actor_process_profile_definition g_profile_NPC_KP1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KP1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kp1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KP1_e,
    /* Actor SubMtd */ &l_daNpc_Kp1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
