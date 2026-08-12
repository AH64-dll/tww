/**
 * d_a_npc_ob1.cpp
 * NPC - Rose (Outset Island pig girl)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ob1.h"
#include "d/d_snap.h"
#include "res/Object/Ob.h"

/* 000000EC-00000150       .text __ct__15daNpc_Ob1_HIO_cFv */
daNpc_Ob1_HIO_c::daNpc_Ob1_HIO_c() {
/* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x2000,
        /* mMaxHeadY         */ 0x1388,
        /* mMinHeadX         */ 0xFC18,
        /* mMinHeadY         */ 0xEC78,
        /* mMaxBackboneX     */ 0x05DC,
        /* mMaxBackboneY     */ 0x1F40,
        /* mMinBackboneX     */ 0xF830,
        /* mMinBackboneY     */ 0xE0C0,
        /* mMaxTurnStep      */ 0x04B0,
        /* mCalcAngleTarget  */ 0x04B0,
        /* mAttPosOffsetY    */ 170.0f,
        /* field_0x24        */ 0,
        /* field_0x26        */ 6,
        /* field_0x28        */ 0x0400,
        /* field_0x2A        */ 0,
        /* field_0x2C        */ 0.5f,
        /* field_0x30        */ 3.0f,
        /* field_0x34        */ 0.1f,
        /* field_0x38        */ 40.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static daNpc_Ob1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;
static u8 l_check_flg;

/* 00000198-00000228       .text searchActor_Kb__FPvPv */
static void* searchActor_Kb(void* i_param_1, void*) {
    if (l_check_wrk < 0x14 && fopAcM_IsActor(i_param_1) &&
        fopAcM_GetName(i_param_1) == fpcNm_KB_e) {
        u8 flag = *(u8*)((u8*)i_param_1 + 0x405);
        if (flag != 0) {
            l_check_flg |= flag;
        }
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 00000228-00000274       .text nodeCallBack_Ob1__FP7J3DNodei */
static BOOL nodeCallBack_Ob1(J3DNode* i_param_1, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ob1_c*>(j3dSys.getModel()->getUserArea())->nodeOb1Control(i_param_1,
                                                                                             j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000274-000003C4       .text nodeOb1Control__11daNpc_Ob1_cFP7J3DNodeP8J3DModel */
void daNpc_Ob1_c::nodeOb1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(20.0f, -20.0f, 0.0f);
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    if (jointIdx == m_hed_jnt_num) {
        mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    }
    if (jointIdx == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

static char* l_evn_tbl[] = {
    "Get_Rupee",
};

/* 00000400-00000480       .text init_OB1_0__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_0() {
/* Nonmatching */
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        set_action(&daNpc_Ob1_c::wait_action1, NULL);
        return true;
    } else {
        return false;
    }
}

/* 00000480-00000518       .text init_OB1_1__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_1() {
/* Nonmatching */
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && !dKy_daynight_check()) {
        fopAcM_OffStatus(this, fopAcStts_NODRAW_e);
        set_action(&daNpc_Ob1_c::wait_action2, NULL);
        return true;
    } else {
        return false;
    }
}

/* 00000518-000005A4       .text init_OB1_2__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::init_OB1_2() {
/* Nonmatching */
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 1) {
        set_action(&daNpc_Ob1_c::wait_action2, NULL);
        return true;
    } else {
        return false;
    }
}

/* 000005A4-000007AC       .text createInit__11daNpc_Ob1_cFv */
bool daNpc_Ob1_c::createInit() {
/* Nonmatching */
    mEventIdx[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0], 0xFF);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAC;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAC;
    gravity = -4.5f;
    mAnmNum = 8;
    mInitialAngle = current.angle;
    mInitialPos.set(current.pos);
    m79C.set(mInitialPos);

    s8 pathRet = 0xFF;
    u32 prm = fopAcM_GetParam(this);
    u8 pathIdx = (u8)(prm >> 8);
    if (pathIdx != 0xFF) {
        if (!mPathRun.setInf(pathIdx, current.roomNo, 1)) {
            return false;
        }
        fopAcM_OffStatus(this, fopAcStts_NODRAW_e);
        pathRet = 0xD9;
    }

    mEventCut.setActorInfo2("Ob1", this);
    mOrderIdx = 8;

    bool init_success;
    switch (mSpecificType) {
        case 0:
            init_success = init_OB1_0();
            break;
        case 1:
            init_success = init_OB1_1();
            break;
        case 2:
            init_success = init_OB1_2();
            break;
        default:
            init_success = false;
            break;
    }
    if (init_success) {
        m78A = current.angle;
        shape_angle = m78A;
    } else {
        return false;
    }

    mStts.Init(pathRet, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 000007AC-00000900       .text setMtx__11daNpc_Ob1_cFb */
void daNpc_Ob1_c::setMtx(bool i_param_1) {
/* Nonmatching */
    if (!mbInDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(m78A.y);

    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    if (mpClothModel != NULL) {
        mpClothModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mpClothModel->calc();
    }
    setAttention(i_param_1);
}

static const int a_bck_resID_tbl[] = {
    dRes_ID_OB_BCK_WAIT_e, dRes_ID_OB_BCK_TALK_e, dRes_ID_OB_BCK_THANK_e, dRes_ID_OB_BCK_WALK_e,
    dRes_ID_OB_BCK_THANK02_e, dRes_ID_OB_BCK_LAUGH_e, dRes_ID_OB_BCK_SHUTUP01_e,
    dRes_ID_OB_BCK_SHUTUP02_e,
};

static const int a_btp_resID_tbl[] = {
    dRes_ID_OB_BTP_MABA_A_e,
    dRes_ID_OB_BTP_MABA_A_e,
};

/* 00000900-00000914       .text anmNum_toResID__11daNpc_Ob1_cFi */
int daNpc_Ob1_c::anmNum_toResID(int i_anmNum) {
    return a_bck_resID_tbl[i_anmNum];
}

/* 00000914-00000928       .text btpNum_toResID__11daNpc_Ob1_cFi */
int daNpc_Ob1_c::btpNum_toResID(int i_btpNum) {
    return a_btp_resID_tbl[i_btpNum];
}

/* 00000928-00000A34       .text setBtp__11daNpc_Ob1_cFbi */
bool daNpc_Ob1_c::setBtp(bool i_anmPlay, int i_btpNum) {
/* Nonmatching */
    J3DModelData* model_data = mpClothModel->getModelData();
    m_hed_tex_pttrn = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Ob", btpNum_toResID(i_btpNum));
    JUT_ASSERT(0x1FF, m_hed_tex_pttrn != 0);
    if (mHeadBtpAnm.init(model_data, m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, false, i_anmPlay)) {
        mBlinkFrame = 0;
        mBlinkTimer = 0;
        return true;
    }
    return false;
}

/* 00000A34-00000A5C       .text iniTexPttrnAnm__11daNpc_Ob1_cFb */
bool daNpc_Ob1_c::iniTexPttrnAnm(bool i_anmPlay) {
    return setBtp(i_anmPlay, mBtpNum);
}

/* 00000A5C-00000B08       .text plyTexPttrnAnm__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::plyTexPttrnAnm() {
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

/* 00000B08-00000B44       .text setAnm_tex__11daNpc_Ob1_cFSc */
void daNpc_Ob1_c::setAnm_tex(s8 i_btpNum) {
    if (mBtpNum != i_btpNum) {
        mBtpNum = i_btpNum;
        iniTexPttrnAnm(true);
    }
}

/* 00000B44-00000C04       .text setAnm_anm__11daNpc_Ob1_cFPQ211daNpc_Ob1_c9anm_prm_c */
BOOL daNpc_Ob1_c::setAnm_anm(anm_prm_c* i_anm) {
/* Nonmatching */
    if (mAnmNum == i_anm->mAnmNum) {
        return TRUE;
    }
    mAnmNum = i_anm->mAnmNum;
    int anmResID = anmNum_toResID(mAnmNum);
    dNpc_setAnmIDRes(mpMorf, i_anm->mLoopMode, i_anm->mMorf, i_anm->mSpeed, anmResID, -1, "Ob");
    int zero = 0;
    mbMorfAnimStopped = zero;
    m7E5 = zero;
    mPrevMorfFrame = zero;
    return TRUE;
}

static daNpc_Ob1_c::anm_prm_c a_anm_prm_tbl[] = {
    { 0, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 1, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 2, 0, 0, 8.0f, 1.0f, 0, 0 },
    { 3, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 4, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 5, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 6, 0, 0, 8.0f, 1.0f, 0, 0 },
    { 7, 0, 0, 8.0f, 1.0f, 2, 0 },
};

/* 00000C04-00000C70       .text setAnm_NUM__11daNpc_Ob1_cFii */
void daNpc_Ob1_c::setAnm_NUM(int i_anmNum, int i_tex) {
/* Nonmatching */
    if (i_tex != 0) {
        setAnm_tex(a_anm_prm_tbl[i_anmNum].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

static daNpc_Ob1_c::anm_prm_c a_anm_prm_tbl2[] = {
    { -1, -1, 0, 0.0f, 0.0f, -1, 0 },
    { 0, 0, 0, 8.0f, 1.0f, 2, 0 },
    { -1, -1, 0, 0.0f, 0.0f, -1, 0 },
    { 3, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 0, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 1, 0, 0, 8.0f, 1.0f, 2, 0 },
    { -1, -1, 0, 0.0f, 0.0f, -1, 0 },
};

/* 00000C70-00000CF0       .text setAnm__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::setAnm() {
/* Nonmatching */
    anm_prm_c* prm = &a_anm_prm_tbl2[mStatus];
    if (prm->mBtpNum >= 0) {
        setAnm_tex(prm->mBtpNum);
    }
    if (a_anm_prm_tbl2[mStatus].mAnmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl2[mStatus]);
    }
    return TRUE;
}

/* 00000CF0-00000CFC       .text chg_anmTag__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::chg_anmTag() {
    if ((int)mTag == 0xFF) {
        return;
    }
}

/* 00000CFC-00000D08       .text control_anmTag__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::control_anmTag() {
    if ((int)mTag == 0xFF) {
        return;
    }
}

/* 00000D08-00000E00       .text chg_anmAtr__11daNpc_Ob1_cFUc */
void daNpc_Ob1_c::chg_anmAtr(u8 i_param_1) {
/* Nonmatching */
    s32 msgNo = m7CC;
    if ((u32)(msgNo + 0x10000) != 0xFFFF) {
        switch (msgNo) {
            case 0xAFE:
                break;
            case 0xAFC:
            case 0xAFD:
            case 0xAFF:
            case 0xB02:
            case 0xB05:
            case 0xB06:
            case 0xB09:
            case 0xB0C:
            case 0xB0D:
            case 0xB5D:
            case 0xB61:
            case 0xB64:
            case 0xB65:
                mLookBackState = 1;
                mHeadOnlyFollow = 0;
                m_jnt.setTrn();
                break;
        }
    }
    if (i_param_1 >= 7) {
        return;
    }
    if (i_param_1 == mAttr) {
        return;
    }
    mAttr = i_param_1;
    setAnm_ATR(true);
}

/* 00000E00-00000E8C       .text control_anmAtr__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::control_anmAtr() {
/* Nonmatching */
    switch (mAttr) {
        case 3:
            if (mbMorfAnimStopped) {
                setAnm_NUM(4, 1);
                mAttr = 7;
            }
            break;
        case 6:
            if (mbMorfAnimStopped) {
                setAnm_NUM(7, 1);
                mAttr = 7;
            }
            break;
    }
}

static daNpc_Ob1_c::anm_prm_c a_anm_prm_tbl3[] = {
    { 0, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 1, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 2, 1, 0, 8.0f, 1.0f, 0, 0 },
    { 2, 0, 0, 8.0f, 1.0f, 0, 0 },
    { 4, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 5, 0, 0, 8.0f, 1.0f, 2, 0 },
    { 6, 0, 0, 8.0f, 1.0f, 0, 0 },
};

/* 00000E8C-00000EF4       .text setAnm_ATR__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::setAnm_ATR(int i_tex) {
/* Nonmatching */
    if (i_tex != 0) {
        setAnm_tex(a_anm_prm_tbl3[mAttr].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl3[mAttr]);
}

/* 00000EF4-00000FFC       .text anmAtr__11daNpc_Ob1_cFUs */
void daNpc_Ob1_c::anmAtr(u16 i_msgNo) {
/* Nonmatching */
    if (field_0x6bc[0] == 2) {
        if (g_dComIfG_gameInfo.play.mMesgCamInfo.mActor[g_dComIfG_gameInfo.play.mMesgCamInfo.mBasicID - 1] !=
            this) {
            control_anmTag();
            control_anmAtr();
            return;
        }
    } else if (i_msgNo == 6) {
        if (m80B == 0) {
            mAttr = 0xFF;
            chg_anmAtr(g_dComIfG_gameInfo.play.mMesgAnime);
            m80B++;
        }
        u8 tag = g_dComIfG_gameInfo.play.mMesgAnimeTagInfo;
        g_dComIfG_gameInfo.play.mMesgAnimeTagInfo = 0xFF;
        if (tag != 0xFF && mTag != tag) {
            mTag = tag;
            chg_anmTag();
        }
    } else if (i_msgNo == 0xE) {
        m80B = 0;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00000FFC-00001088       .text eventOrder__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::eventOrder() {
/* Nonmatching */
    s8 order = mOrderIdx;
    if (order == 1 || order == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (order == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (order >= 3) {
        mEventIdx[1] = order - 3;
        fopAcM_orderOtherEventId(this, mEventIdx[mEventIdx[1]], 0xFF, 0xFFFF, 0, 1);
    }
}

/* 00001088-00001120       .text checkOrder__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdx[mEventIdx[1]])) {
            mOrderIdx = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrderIdx == 1 || mOrderIdx == 2) {
            mOrderIdx = 0;
            m7F9 = 1;
        }
    }
}

/* 00001120-000011C0       .text chk_talk__11daNpc_Ob1_cFv */
u8 daNpc_Ob1_c::chk_talk() {
/* Nonmatching */
    BOOL ret = FALSE;
    u8 present = 0;
    u8 talkBtn = dComIfGp_event_getTalkXYBtn();
    if (talkBtn == dTalkBtn_X_e) {
        present = 1;
    }
    if (talkBtn == dTalkBtn_Y_e) {
        present = 1;
    }
    if (talkBtn == dTalkBtn_Z_e) {
        present = 1;
    }
    if (present) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            m7EB = dComIfGp_event_getPreItemNo();
            ret = TRUE;
        }
    } else {
        m7EB = 0xFF;
        ret = TRUE;
    }
    return ret;
}

/* 000011C0-00001200       .text chk_partsNotMove__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::chk_partsNotMove() {
    BOOL ret = FALSE;
    if (mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() &&
        mActorAngleY == current.angle.y) {
        ret = TRUE;
    }
    return ret;
}

/* 00001200-000013A0       .text lookBack__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::lookBack() {
/* Nonmatching */
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = mHeadOnlyFollow;

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
            dstPos.set(m79C);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 3:
            desiredYrot = mTargetYRot;
            break;
    }
    cLib_addCalcAngleS2(&mLookAtMaxVel, l_HIO.mPrmTbl.mCalcAngleTarget, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, mLookAtMaxVel, headOnlyFollow);
}

/* 000013A0-000014CC       .text next_msgStatus__11daNpc_Ob1_cFPUl */
u16 daNpc_Ob1_c::next_msgStatus(u32* i_msg_no) {
/* Nonmatching */
    u16 ret = 0xF;
    switch (*i_msg_no) {
        case 0xA8D:
            *i_msg_no = 0xA8E;
            break;
        case 0xA8F:
            *i_msg_no = 0xA91;
            break;
        case 0xA92:
            *i_msg_no = 0xA94;
            break;
        case 0xA95:
            *i_msg_no = 0xA98;
            break;
        case 0xA96:
        case 0xA97:
        case 0xA9B:
        case 0xA9F:
        case 0xAA0:
        case 0xAA1:
        case 0xAA3:
        case 0xAA4:
        case 0xAA5:
        case 0xAA6:
        case 0xAA8:
        case 0xAAA:
        case 0xAAE:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20) &&
                !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0308)) {
                *i_msg_no = 0xAA7;
            }
            break;
        case 0xAAD:
            if (dKy_daynight_check() == 0) {
                *i_msg_no = 0xAA9;
            } else {
                *i_msg_no = 0xAAA;
            }
            break;
        case 0xAA9:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0304)) {
                *i_msg_no = 0xA8F;
            } else {
                *i_msg_no = 0xA8D;
            }
            break;
        default:
            ret = 0x10;
            break;
    }
    return ret;
}

/* 000014CC-000017F0       .text getMsg_OB1_0__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_0() {
/* Nonmatching */
    u32 ret = 0;
    if (m7E8 != 0 || m7E7 != 0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0302)) {
            if (m7E9 != 0) {
                if (m7E7 == 2) {
                    if (m7EA != 0) {
                        ret = 0xAA2;
                        m7EA = 0;
                    } else {
                        ret = 0xAA1;
                        m7EA = 1;
                    }
                } else {
                    switch (m7E9) {
                        case 1:
                            if (m7EA == 1) {
                                ret = 0xA9D;
                                m7EA = 0;
                            } else {
                                ret = 0xA9C;
                                m7EA = 1;
                            }
                            break;
                        case 2:
                            if (m7EA == 2) {
                                ret = 0xA9F;
                                m7EA = 1;
                            } else if (m7EA == 1) {
                                ret = 0xAA0;
                                m7EA = 0;
                            } else {
                                ret = 0xA9E;
                                m7EA = 2;
                            }
                            break;
                    }
                }
            } else {
                if (m7E7 > m7E8) {
                    ret = 0xAA3;
                } else {
                    switch (m7E8) {
                        case 1:
                            ret = 0xAA4;
                            break;
                        case 2:
                            ret = 0xAA5;
                            break;
                        default:
                            ret = 0xAA6;
                            break;
                    }
                }
            }
        } else {
            switch (m7E9) {
                case 1:
                    if (m7EA == 1) {
                        ret = 0xA92;
                        m7EA = 0;
                    } else {
                        ret = 0xA90;
                        m7EA = 1;
                    }
                    break;
                case 2:
                    if (m7EA == 2) {
                        ret = 0xA95;
                        m7EA = 1;
                    } else if (m7EA == 1) {
                        ret = 0xA96;
                        m7EA = 0;
                    } else {
                        ret = 0xA93;
                        m7EA = 2;
                    }
                    break;
                case 3:
                    switch (m7EA) {
                        case 3:
                            ret = 0xA99;
                            m7EA = 2;
                            break;
                        case 2:
                            ret = 0xA9A;
                            m7EA = 1;
                            break;
                        case 1:
                            ret = 0xA9B;
                            m7EA = 0;
                            break;
                        default:
                            ret = 0xA97;
                            m7EA = 3;
                            break;
                    }
                    break;
            }
            m7EC = 1;
        }
        return ret;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80)) {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C40)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C40);
            return 0xAAD;
        }
    } else if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C80)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C80);
        return 0xAAE;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0304)) {
        return 0xA8F;
    }
    return 0xA8D;
}

/* 000017F0-0000185C       .text getMsg_OB1_1__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_1() {
/* Nonmatching */
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C20)) {
        return 0xAA8;
    }
    if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF) != 0) {
        return 0xAAC;
    }
    return 0xAAB;
}

/* 0000185C-0000187C       .text getMsg_OB1_2__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg_OB1_2() {
    return getMsg_OB1_1();
}

/* 0000187C-000018EC       .text getMsg__11daNpc_Ob1_cFv */
u32 daNpc_Ob1_c::getMsg() {
    u32 msgNo = 0;
    switch (mSpecificType) {
        case 0:
            msgNo = getMsg_OB1_0();
            break;
        case 1:
            msgNo = getMsg_OB1_1();
            break;
        case 2:
            msgNo = getMsg_OB1_2();
            break;
    }
    return msgNo;
}

/* 000018EC-0000196C       .text chkAttention__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::chkAttention() {
/* Nonmatching */
    if (dComIfGp_getAttention().LockonTruth()) {
        return dComIfGp_getAttention().LockonTarget(0) == this;
    } else {
        return dComIfGp_getAttention().ActionTarget(0) == this;
    }
}

/* 0000196C-000019C4       .text setAttention__11daNpc_Ob1_cFb */
void daNpc_Ob1_c::setAttention(bool i_param_1) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY,
                                current.pos.z);
    if (mCurrActionRet != 0 || i_param_1) {
        eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
    }
}

/* 000019C4-000019F8       .text searchByID__11daNpc_Ob1_cFUi */
fopAc_ac_c* daNpc_Ob1_c::searchByID(fpc_ProcID i_procID) {
    fopAc_ac_c* actor = NULL;
    fopAcM_SearchByID(i_procID, &actor);
    return actor;
}

/* 000019F8-00001A04       .text partner_srch__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::partner_srch() {
    if ((int)mActionIndex == 1) {
        return;
    }
}

/* 00001A04-00001A34       .text bitCount__11daNpc_Ob1_cFUc */
s32 daNpc_Ob1_c::bitCount(u8 i_param_1) {
/* Nonmatching */
    s8 count = 0;
    s32 i = 0;
    while (i < 8) {
        if (i_param_1 & 1) {
            count += 1;
        }
        i_param_1 = i_param_1 >> 1;
        i++;
    }
    return count;
}

/* 00001A34-00001B14       .text set_pigCnt__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::set_pigCnt() {
/* Nonmatching */
    m7E7 = bitCount(dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF));
    l_check_wrk = 0;
    l_check_flg = 0;
    for (int i = 0; i < 0x14; i++) {
        l_check_inf[i] = NULL;
    }
    fpcEx_Search(searchActor_Kb, this);
    m7E8 = bitCount(l_check_flg);
    m7E9 = bitCount(dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF) & ~l_check_flg);
    m7EA = 0;
}

/* 00001B14-00001BB0       .text ob_setPthPos__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_setPthPos() {
/* Nonmatching */
    if (mPathRun.getPath() != NULL) {
        cXyz pos = mPathRun.getPoint(mPathRun.getIdx());
        current.pos.set(pos);
        mPathRun.nextIdxAuto();
        cXyz next_pos = mPathRun.getPoint(mPathRun.getIdx());
        current.angle.y = cLib_targetAngleY(&current.pos, &next_pos);
    }
}

/* 00001BB0-00001C50       .text get_attPos__11daNpc_Ob1_cFv */
cXyz daNpc_Ob1_c::get_attPos() {
    cXyz ret;
    dPath* path = mPathRun.nextPath(current.roomNo);
    if (path != NULL) {
        u8 idx = mPathRun.getIdx();
        if (idx == 0) {
            idx = mPathRun.maxPoint();
        }
        idx--;
        dPnt* pnt = &path->m_points[idx];
        ret.set(pnt->m_position.x, pnt->m_position.y, pnt->m_position.z);
    }
    return ret;
}

/* 00001C50-00001DC0       .text ob_movPass__11daNpc_Ob1_cFv */
s32 daNpc_Ob1_c::ob_movPass() {
/* Nonmatching */
    s32 ret = 0;
    if (mPathRun.getPath() != NULL && dPath_ChkClose(mPathRun.getPath())) {
        if (mPathRun.chkPointPass(current.pos, mPathRun.getDir())) {
            mPathRun.nextIdxAuto();
            ret = 1;
        }
        return ret;
    }
    cXyz diff = m7A8 - current.pos;
    f32 dist = PSVECSquareMag((Vec*)&cXyz(diff.x, 0.0f, diff.z));
    if (dist > 0.0f) {
        dist = std::sqrtf(dist);
    }
    if (dist <= m7C0) {
        ret = 1;
        if (mPathRun.getPath() != NULL) {
            if (!mPathRun.nextIdxAuto()) {
                ret = 2;
            }
        }
    }
    return ret;
}

/* 00001DC0-00001E50       .text ob_clcMovSpd__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_clcMovSpd() {
/* Nonmatching */
    cXyz diff = m7A8 - current.pos;
    PSVECSquareMag(&cXyz(diff.x, 0.0f, diff.z));
    cLib_chaseAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &m7A8),
                     l_HIO.mPrmTbl.field_0x28);
    cLib_chaseF(&speedF, m7B8, m7BC);
}

/* 00001E50-00001F28       .text ob_nMove__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::ob_nMove() {
/* Nonmatching */
    f32 moveSpeed = 0.0f;
    if (m7FC == 1) {
        ob_clcMovSpd();
        if (m7FC == 1) {
            moveSpeed = speedF * l_HIO.mPrmTbl.field_0x2C;
        }
    }
    if (moveSpeed < 0.5f) {
        moveSpeed = 0.5f;
    }
    mpMorf->setPlaySpeed(moveSpeed);
    s32 movRet = ob_movPass();
    if (movRet == 1 || movRet == 2) {
        m7F2 = 1;
        if (movRet == 2) {
            m7FC = 0;
        }
    }
    if (m7F2 != 0) {
        m7F0 = 1;
    }
}

/* 00001F28-00001F78       .text charDecide__11daNpc_Ob1_cFi */
BOOL daNpc_Ob1_c::charDecide(int i_param_1) {
    mType = 0;
    mSpecificType = -1;
    switch (i_param_1) {
        case 1:
            mSpecificType = 1;
            break;
        case 2:
            mSpecificType = 2;
            break;
        default:
            mSpecificType = 0;
            break;
    }
    return TRUE;
}

/* 00001F78-00001FD0       .text event_actionInit__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::event_actionInit(int i_staff_idx) {
    int* act_no_p = (int*)dComIfGp_evmng_getMyIntegerP(i_staff_idx, "ActNo");
    if (act_no_p != NULL) {
        m7FF = *act_no_p;
    }
}

/* 00001FD0-00001FE0       .text event_action__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::event_action() {
    if ((s32)m7FF != 0) {
        return TRUE;
    }
    return TRUE;
}

static char* a_cut_tbl[] = {
    "ACTION",
};

/* 00001FE0-000020CC       .text privateCut__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::privateCut(int i_staff_idx) {
/* Nonmatching */
    if (i_staff_idx == -1) {
        return;
    }
    m7FE = dComIfGp_evmng_getMyActIdx(i_staff_idx, a_cut_tbl, 1, 1, 0);
    if (m7FE == -1) {
        dComIfGp_evmng_cutEnd(i_staff_idx);
        return;
    }
    if (dComIfGp_evmng_getIsAddvance(i_staff_idx)) {
        if (m7FE == 0) {
            event_actionInit(i_staff_idx);
        }
    }
    BOOL done;
    if (m7FE == 0) {
        done = event_action();
    } else {
        done = TRUE;
    }
    if (done) {
        dComIfGp_evmng_cutEnd(i_staff_idx);
    }
}

/* 000020CC-000020EC       .text endEvent__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::endEvent() {
    dComIfGp_event_reset();
    mAttr = 0xFF;
}

/* 000020EC-00002124       .text isEventEntry__11daNpc_Ob1_cFv */
int daNpc_Ob1_c::isEventEntry() {
/* Nonmatching */
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), this, 0);
}

/* 00002124-000021B8       .text event_proc__11daNpc_Ob1_cFi */
void daNpc_Ob1_c::event_proc(int i_staff_idx) {
    if (dComIfGp_evmng_endCheck(mEventIdx[mEventIdx[1]])) {
        mOrderIdx = 1;
        endEvent();
        return;
    }
    if (!mEventCut.cutProc()) {
        privateCut(i_staff_idx);
    }
    lookBack();
}

/* 000021B8-00002264       .text set_action__11daNpc_Ob1_cFM11daNpc_Ob1_cFPCvPvPv_iPv */
BOOL daNpc_Ob1_c::set_action(int (daNpc_Ob1_c::*i_newProcFunc)(void*), void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc != NULL) {
            mActionIndex = 0;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        mActionIndex = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00002264-00002288       .text clrSpd__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::clrSpd() {
    m7B8 = 0.0f;
    m7BC = 0.0f;
    speedF = 0.0f;
    gravity = -4.5f;
}

/* 00002288-00002488       .text setStt__11daNpc_Ob1_cFSc */
void daNpc_Ob1_c::setStt(s8 i_status) {
/* Nonmatching */
    searchByID(mPartnerProcID);
    s8 oldStatus = mStatus;
    mTimer = 0;
    mStatus = i_status;
    switch (mStatus) {
        case 0:
            break;
        case 4:
            m7DA = cLib_getRndValue<int>(0x5A, 0xB4);
        case 1:
        case 5:
            if (oldStatus != 2) {
                switch (mStatus) {
                    case 1:
                        mLookBackState = 3;
                        mTargetYRot = mInitialAngle.y;
                        break;
                    case 4:
                        mLookBackState = 2;
                        m79C.set(get_attPos());
                        break;
                    case 5:
                        mLookBackState = 1;
                        break;
                }
                m_jnt.setTrn();
                mHeadOnlyFollow = 0;
            }
            mOrderIdx = 0;
            m7FC = 0;
            clrSpd();
            break;
        case 2:
            mLookBackState = 1;
            m_jnt.setTrn();
            mHeadOnlyFollow = 0;
            mOrderIdx = 0;
            m7FC = 0;
            clrSpd();
            mAttr = 0xFF;
            if (oldStatus != 5) {
                mPrevStatus = oldStatus;
            }
            set_pigCnt();
            break;
        case 3:
            m7A8.set(mPathRun.getPoint(mPathRun.getIdx()));
            mLookBackState = 0;
            mHeadOnlyFollow = 1;
            mOrderIdx = 0;
            m7FC = 1;
            m7F2 = 0;
            gravity = -4.5f;
            m7B8 = l_HIO.mPrmTbl.field_0x30;
            m7BC = l_HIO.mPrmTbl.field_0x34;
            m7C0 = l_HIO.mPrmTbl.field_0x38;
            break;
        case 6:
            mAttr = 0xFF;
            mPrevStatus = oldStatus;
            return;
    }
    setAnm();
}

/* 00002488-00002564       .text wait_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_1() {
    if (m7F9 != 0) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    if (field_0x6bc[0] == 1) {
        field_0x6bc[0] = 2;
        setStt(6);
        mLookBackState = 3;
        mTargetYRot = mInitialAngle.y;
        return TRUE;
    }
    mOrderIdx = 2;
    if (m7F8 != 0) {
        mTimer = 0x3C;
    }
    if (cLib_calcTimer(&mTimer) != 0) {
        mLookBackState = 1;
    } else {
        mLookBackState = 3;
        mTargetYRot = mInitialAngle.y;
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 00002564-0000264C       .text wait_2__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_2() {
    if (m7F9 != 0) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    mOrderIdx = 2;
    if (m7F8 != 0) {
        mTimer = 0x3C;
    }
    if (cLib_calcTimer(&mTimer) != 0) {
        mLookBackState = 1;
    } else if (cLib_calcTimer(&m7DA) == 0) {
        setStt(3);
        return TRUE;
    } else {
        mLookBackState = 2;
        m79C.set(get_attPos());
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 0000264C-000026F0       .text wait_3__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::wait_3() {
    if (m7F9 != 0) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    if (mbMorfAnimStopped) {
        m7E5++;
        if (m7E5 > 3) {
            setStt(mPrevStatus);
            return TRUE;
        }
    }
    mOrderIdx = 2;
    mLookBackState = 1;
    m_jnt.setTrn();
    return TRUE;
}

/* 000026F0-00002808       .text walk_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::walk_1() {
    if (m7F9 != 0) {
        setAnm_NUM(0, 1);
        speedF = 0.0f;
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    mOrderIdx = 2;
    if (m7F8 != 0) {
        mTimer = 0x14;
    }
    if (cLib_calcTimer(&mTimer) != 0) {
        mLookBackState = 1;
    } else {
        mLookBackState = 0;
    }
    if (m7F2 != 0) {
        if (mPathRun.getIdx() == 0) {
            mPathRun.nextIdxAuto();
        }
        setStt(4);
        return TRUE;
    }
    m7F2 = 0;
    m7A8.set(mPathRun.getPoint(mPathRun.getIdx()));
    return TRUE;
}

/* 00002808-00002A58       .text talk_1__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::talk_1() {
/* Nonmatching */
    BOOL partsNotMove = chk_partsNotMove();
    if (mOrderIdx == 1 || mOrderIdx >= 3) {
        return TRUE;
    }
    if (mpCurrMsg != NULL) {
        m7E2 = mpCurrMsg->mStatus;
    } else {
        m7E2 = 0;
    }
    if (m7ED != 0 && mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        mCurrMsgNo = getMsg();
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, g_dComIfG_gameInfo.play.mMesgCamInfo.mActor[0]);
        mpCurrMsg = NULL;
    } else {
        m7CC = -1;
        talk(1);
    }
    if (mpCurrMsg != NULL && mpCurrMsg->mStatus != fopMsgStts_MSG_DISPLAYED_e &&
        mpCurrMsg->mStatus != fopMsgStts_MSG_CONTINUES_e && mpCurrMsg->mStatus != fopMsgStts_MSG_ENDS_e) {
        switch (mpCurrMsg->mStatus) {
            case fopMsgStts_MSG_DESTROYED_e:
                if (m7EA != 0) {
                    mOrderIdx = 3;
                    setAnm_NUM(0, 1);
                    endEvent();
                    return partsNotMove;
                }
                u8 eventReg = l_check_flg | dComIfGs_getEventReg(dSv_event_flag_c::UNK_B6FF);
                l_check_flg = eventReg;
                dComIfGs_setEventReg(dSv_event_flag_c::UNK_B6FF, eventReg);
                switch (mCurrMsgNo) {
                    case 0xA8E:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0304);
                        break;
                    case 0xAA7:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0308);
                        break;
                    default:
                        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2C20);
                        break;
                }
                if (m7EC != 0) {
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_0302);
                }
                m7EB = 0xFF;
                m7F9 = 0;
                if (mSpecificType != 0) {
                    setStt(mPrevStatus);
                    mTimer = 0x3C;
                } else {
                    setStt(5);
                }
                endEvent();
                return partsNotMove;
        }
    }
    return partsNotMove;
}

/* 00002A58-00002B60       .text manzai__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::manzai() {
    dComIfG_MesgCamInfo_c* camInfo = &g_dComIfG_gameInfo.play.mMesgCamInfo;
    switch (field_0x6bc[0]) {
        case 2:
            fopAc_ac_c* partner = searchByID(*(u32*)&field_0x6b4[0]);
            if (this != camInfo->mActor[camInfo->mBasicID - 1]) {
                if (mAttr != 0xFF) {
                    mLookBackState = 3;
                    mTargetYRot = mInitialAngle.y;
                    m_jnt.setTrn();
                    mStatus = mPrevStatus;
                    setAnm();
                    mStatus = 6;
                    mAttr = 0xFF;
                }
            } else {
                m7CC = ((fopNpc_npc_c*)partner)->mCurrMsgNo;
                anmAtr(*(u16*)&((fopNpc_npc_c*)partner)->field_0x6b4[4]);
            }
            break;
        case 3:
            fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
            setStt(mPrevStatus);
            field_0x6bc[0] = 0;
            break;
    }
    return TRUE;
}

/* 00002B60-00002C54       .text wait_action1__11daNpc_Ob1_cFPv */
BOOL daNpc_Ob1_c::wait_action1(void*) {
    switch (mActionIndex) {
        case 0:
            ob_setPthPos();
            setStt(3);
            mActionIndex++;
            break;
        case 1:
        case 2:
        case 3:
            m7F8 = chkAttention();
            switch (mStatus) {
                case 4:
                    mCurrActionRet = wait_2();
                    break;
                case 5:
                    mCurrActionRet = wait_3();
                    break;
                case 3:
                    mCurrActionRet = walk_1();
                    break;
                case 2:
                    mCurrActionRet = talk_1();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00002C54-00002D2C       .text wait_action2__11daNpc_Ob1_cFPv */
BOOL daNpc_Ob1_c::wait_action2(void*) {
    switch (mActionIndex) {
        case 0:
            setStt(1);
            mActionIndex++;
            break;
        case 1:
        case 2:
        case 3:
            m7F8 = chkAttention();
            switch (mStatus) {
                case 1:
                    mCurrActionRet = wait_1();
                    break;
                case 2:
                    mCurrActionRet = talk_1();
                    break;
                case 6:
                    mCurrActionRet = manzai();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00002D2C-00002E68       .text demo__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::demo() {
/* Nonmatching */
    if (demoActorID == 0) {
        if (mbInDemo) {
            mbInDemo = false;
        }
    } else {
        mbInDemo = true;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if (m_hed_tex_pttrn != NULL) {
            mBlinkFrame++;
            if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* btpData = demo_actor->getP_BtpData("Ob");
        if (btpData != NULL) {
            m_hed_tex_pttrn = btpData;
            mHeadBtpAnm.init(mpClothModel->getModelData(), m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, false, true);
            mBtpNum = 2;
            mBlinkFrame = 0;
        }
#if VERSION > VERSION_DEMO
        dDemo_setDemoData(this, 0x6A, mpMorf, "Ob", 0, NULL, 0, 0);
#else
        dDemo_setDemoData(this, 0x6A, mpMorf, "Ob", 0, NULL);
#endif
    }
    return mbInDemo;
}

/* 00002E68-00002F18       .text shadowDraw__11daNpc_Ob1_cFv */
void daNpc_Ob1_c::shadowDraw() {
/* Nonmatching */
    cXyz temp(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &temp, 800.0f, 40.0f,
                                   current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0,
                                   1.0f, dDlst_shadowControl_c::getSimpleTex());
    if (mShadowID != 0) {
        dComIfGd_addRealShadow(mShadowID, mpClothModel);
    }
}

/* 00002F18-0000300C       .text _draw__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_draw() {
/* Nonmatching */
    if (m7EE != 0 || m7F1 != 0) {
        return TRUE;
    }
    J3DModel* clothModel = mpClothModel;
    J3DModelData* clothModelData = clothModel->getModelData();
    J3DModel* model = mpMorf->getModel();
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mpMorf->entryDL();
    mHeadBtpAnm.entry(clothModelData, mBlinkFrame);
    mDoExt_modelEntryDL(clothModel);
    clothModelData->getMaterialTable().removeTexNoAnimator(m_hed_tex_pttrn);
    g_env_light.setLightTevColorType(clothModel, &tevStr);
    shadowDraw();
    dSnap_RegistFig(0x4F, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

static const u32 l_mask_block[] = { // to match rodata
    0xFF000080,
    0x0000FF80,
    0x00FF0080,
};

/* 0000300C-000031F0       .text _execute__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_execute() {
/* Nonmatching */
    if (m7F3 == 0) {
        mInitialPos.set(current.pos);
        mInitialAngle = current.angle;
        m7F3 = 1;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.mMinHeadY, l_HIO.mPrmTbl.mMaxBackboneX,
                   l_HIO.mPrmTbl.mMaxBackboneY, l_HIO.mPrmTbl.mMinBackboneX,
                   l_HIO.mPrmTbl.mMinBackboneY, l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
                   l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMaxTurnStep);
    if (m7EE != 0 && demoActorID == 0) {
        return TRUE;
    }
    m7F0 = 0;
    m7EE = 0;
    partner_srch();
    checkOrder();
    if (!demo()) {
        int staffIdx = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk()) {
            staffIdx = isEventEntry();
        }
        if (staffIdx >= 0) {
            event_proc(staffIdx);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }
        if (m7F0 == 0) {
            ob_nMove();
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if (m7EF == 0) {
            m78A = current.angle;
            shape_angle = m78A;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbInDemo) {
        setCollision(80.0f, 160.0f);
    }
    return TRUE;
}

/* 000031F0-0000324C       .text _delete__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Ob");
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 0000324C-0000326C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ob1_c*>(i_this)->CreateHeap();
}

static u32 a_size_tbl[] = {
    0x272E0,
};

/* 0000326C-0000338C       .text _create__11daNpc_Ob1_cFv */
cPhs_State daNpc_Ob1_c::_create() {
/* Nonmatching */
    fopAcM_ct(this, daNpc_Ob1_c);
    cPhs_State phase = dComIfG_resLoad(&mPhs, "Ob");
    if (phase == cPhs_COMPLEATE_e) {
        if (!charDecide(fopAcM_GetParam(this) & 0xFF)) {
            return cPhs_ERROR_e;
        }
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mType])) {
            return cPhs_ERROR_e;
        }
        cullMtx = mpMorf->getModel()->getBaseTRMtx();
        fopAcM_setCullSizeBox(this, -60.0f, -20.0f, -60.0f, 60.0f, 170.0f, 60.0f);
        if (!createInit()) {
            return cPhs_ERROR_e;
        }
        return phase;
    }
    return phase;
}

/* 0000338C-000034F0       .text __ct__11daNpc_Ob1_cFv */
daNpc_Ob1_c::daNpc_Ob1_c() {}

static u32 a_hed_mdl_resID_tbl[] = {
    dRes_ID_OB_BDL_OBA_HEAD_e,
};

/* 000037BC-000039D0       .text create_Anm__11daNpc_Ob1_cFv */
J3DModelData* daNpc_Ob1_c::create_Anm() {
/* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ob", dRes_ID_OB_BDL_OB_e);
    JUT_ASSERT(0x977, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Ob", dRes_ID_OB_BCK_WAIT_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x110222
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    }
    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x98B, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x98E, m_bbone_jnt_num >= 0);
    return a_mdl_dat;
}

/* 000039D0-00003A9C       .text create_hed_Mdl__11daNpc_Ob1_cFv */
J3DModel* daNpc_Ob1_c::create_hed_Mdl() {
/* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ob", (u16)a_hed_mdl_resID_tbl[mType]);
    JUT_ASSERT(0x9A1, a_mdl_dat != NULL);
    mpClothModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x110222);
    return mpClothModel;
}

/* 00003A9C-00003BD0       .text CreateHeap__11daNpc_Ob1_cFv */
BOOL daNpc_Ob1_c::CreateHeap() {
/* Nonmatching */
    J3DModelData* model_data = create_Anm();
    if (model_data == NULL) {
        return FALSE;
    }
    if (create_hed_Mdl() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    mBtpNum = 0;
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    for (u16 i = 0; i < model_data->getJointNum(); i++) {
        if (i == m_hed_jnt_num || i == m_bbone_jnt_num) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ob1);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 80.0f);
    mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, NULL, NULL);
    return TRUE;
}

static BOOL daNpc_Ob1_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ob1_c*>(i_this)->_create();
}

static BOOL daNpc_Ob1_Delete(daNpc_Ob1_c* i_this) {
    return i_this->_delete();
}

static BOOL daNpc_Ob1_Execute(daNpc_Ob1_c* i_this) {
    return i_this->_execute();
}

static BOOL daNpc_Ob1_IsDelete(daNpc_Ob1_c*) {
    return TRUE;
}

static BOOL daNpc_Ob1_Draw(daNpc_Ob1_c* i_this) {
    return i_this->_draw();
}

static actor_method_class l_daNpc_Ob1_Method = {
    (process_method_func)daNpc_Ob1_Create,
    (process_method_func)daNpc_Ob1_Delete,
    (process_method_func)daNpc_Ob1_Execute,
    (process_method_func)daNpc_Ob1_IsDelete,
    (process_method_func)daNpc_Ob1_Draw,
};

actor_process_profile_definition g_profile_NPC_OB1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_OB1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ob1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ 0x150,
    /* Actor SubMtd */ &l_daNpc_Ob1_Method,
    /* Status       */ 0x401A8,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
