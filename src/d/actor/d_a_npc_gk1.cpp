/**
 * d_a_npc_gk1.cpp
 * NPC - Mila's Father (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_gk1.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_lib.h"
#include "res/Object/Gk.h"

class daNpc_Gk1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackboneX;
        /* 0x0A */ s16 mMaxBackboneY;
        /* 0x0C */ s16 mMinBackboneX;
        /* 0x0E */ s16 mMinBackboneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 mLookAtMaxVel;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ f32 field_0x18;
    };  // Size: 0x1C

    daNpc_Gk1_HIO_c();
    virtual ~daNpc_Gk1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m8;
    /* 0x0C */ hio_prm_c mPrmTbl;

};

/* 000000EC-00000150       .text __ct__15daNpc_Gk1_HIO_cFv */
daNpc_Gk1_HIO_c::daNpc_Gk1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x2000,
        /* mMaxHeadY         */ 0x0FA0,
        /* mMinHeadX         */ 0xEE6C,
        /* mMinHeadY         */ 0xF060,
        /* mMaxBackboneX     */ 0x0000,
        /* mMaxBackboneY     */ 0x0DAC,
        /* mMinBackboneX     */ 0xFC18,
        /* mMinBackboneY     */ 0xF254,
        /* mMaxTurnStep      */ 0x0578,
        /* mLookAtMaxVel     */ 0x03E8,
        /* mAttPosOffsetY    */ 200.0f,
        /* field_0x18        */ 0.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m8 = -1;
}


static daNpc_Gk1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

static char* l_evn_tbl[] = {
    "dummy",
};


/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Gk1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_Head(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    
    static cXyz a_head_pos_off(30.0f, 30.0f, 0.0f);
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mHeadPos.x = mDoMtx_stack_c::get()[0][3];
    mHeadPos.y = mDoMtx_stack_c::get()[1][3];
    mHeadPos.z = mDoMtx_stack_c::get()[2][3];
    mDoMtx_stack_c::multVec(&a_head_pos_off, &mTargetPos);
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000314-00000360       .text nodeCB_Neck__FP7J3DNodei */
static BOOL nodeCB_Neck(J3DNode* i_node, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Gk1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_Neck(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_Neck(J3DNode* i_node, J3DModel* i_model) {
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000400-0000044C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Gk1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_BackBone(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Gk1_cFP7J3DNodeP8J3DModel */
void daNpc_Gk1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 000004EC-0000050C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Gk1_c*>(i_this)->CreateHeap();
}

/* 0000050C-0000058C       .text init_GK1_0__11daNpc_Gk1_cFv */
u8 daNpc_Gk1_c::init_GK1_0() {
    /* Nonmatching */
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
        set_action(&daNpc_Gk1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 0000058C-00000720       .text createInit__11daNpc_Gk1_cFv */
u8 daNpc_Gk1_c::createInit() {
    mEventIdTable[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0], 0xFF);
    mEventCut.setActorInfo2("Gk1", this);
    attention_info.flags = 0xA;
    cullSizeFar = 12000.0f / mDoLib_clipper::mSystemFar;
    switch (mType) {
        case 0:
            break;
    }
    attention_info.distances[1] = 0xA9;
    attention_info.distances[3] = 0xA9;
    gravity = -4.5f;
    mActNo = 5;
    u8 init_result;
    switch (mType) {
        case 0:
            init_result = init_GK1_0();
            break;
        default:
            init_result = 0;
            break;
    }
    if (init_result == 0) {
        return FALSE;
    }
    mAngle = current.angle;
    shape_angle = mAngle;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    play_animation();
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return TRUE;
}

/* 00000720-000007C8       .text play_animation__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::play_animation() {
    u32 mtrl_snd_id = 0;
    play_btp_anm();
    if (mObjAcch.ChkGroundHit()) {
        mtrl_snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    m79C = mpMorf->play(&eyePos, mtrl_snd_id, dComIfGp_getReverb(current.roomNo));
    if (mpMorf->getFrame() < mPrevMorfFrame) {
        m79C = 1;
    }
    mPrevMorfFrame = mpMorf->getFrame();
}

/* 000007C8-00000930       .text setMtx__11daNpc_Gk1_cFb */
void daNpc_Gk1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle.x, mAngle.y, mAngle.z);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if (mpItemModel != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mpItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpItemModel->calc();
    }
    if (mpHatModel != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mpHatModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpHatModel->calc();
    }
    setAttention(i_setEyePos);
}

/* 00000930-00000944       .text bckResID__11daNpc_Gk1_cFi */
int daNpc_Gk1_c::bckResID(int i_bck_num) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_GK_BCK_GK_WAIT01_e,
        dRes_ID_GK_BCK_GK_WALK_e,
        dRes_ID_GK_BCK_GK_TALK01_e,
        dRes_ID_GK_BCK_GK_TALK02_e,
        dRes_ID_GK_BCK_GK_TALK03_e,
    };
    return a_bck_resID_tbl[i_bck_num];
}

/* 00000944-00000958       .text btpResID__11daNpc_Gk1_cFi */
int daNpc_Gk1_c::btpResID(int i_btp_num) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_GK_BTP_GK_e,
    };
    return a_btp_resID_tbl[i_btp_num];
}

/* 00000958-00000A5C       .text setBtp__11daNpc_Gk1_cFScb */
bool daNpc_Gk1_c::setBtp(s8 i_btp_num, bool i_param_2) {
    J3DModel* model = mpMorf->getModel();
    if (i_btp_num < 0) {
        return FALSE;
    }
    J3DAnmTexPattern* a_btp = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes(m_arcname, btpResID(i_btp_num)));
    JUT_ASSERT(VERSION_SELECT(451, 451, 451, 453), a_btp != NULL);
    mBtpNum = i_btp_num;
    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return mBtpAnm.init(model->getModelData(), a_btp, 1, 0, 1.0f, 0, -1, i_param_2, FALSE) != 0;
}

/* 00000A5C-00000A7C       .text init_texPttrnAnm__11daNpc_Gk1_cFScb */
bool daNpc_Gk1_c::init_texPttrnAnm(s8 i_btp_num, bool i_param_2) {
    return setBtp(i_btp_num, i_param_2);
}

/* 00000A7C-00000B18       .text play_btp_anm__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::play_btp_anm() {
    u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
    if (mBtpNum != 0 || !cLib_calcTimer(&mBlinkTimer)) {
        mBlinkFrame += 1;
        if (mBlinkFrame >= frame_max) {
            if (mBtpNum != 0) {
                mBlinkFrame = frame_max;
            } else {
                mBlinkTimer = cLib_getRndValue(60, 90);
                mBlinkFrame = 0;
            }
        }
    }
}

/* 00000B18-00000BB4       .text setAnm_anm__11daNpc_Gk1_cFPQ211daNpc_Gk1_c9anm_prm_c */
void daNpc_Gk1_c::setAnm_anm(daNpc_Gk1_c::anm_prm_c* i_anmPrmP) {
    s8 temp = i_anmPrmP->mAnmNum;
    if (temp < 0 || mActNo == temp) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, bckResID(temp), -1, m_arcname);
    mActNo = i_anmPrmP->mAnmNum;
    m79C = 0;
    m79D = 0;
    mPrevMorfFrame = 0.0f;
}

/* 00000BB4-00000C20       .text setAnm__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::setAnm() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0, 0.0f, 0.0f, -1},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0.0f, 0.0f, -1},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mAnmNum].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[mAnmNum]);
}

/* 00000C20-00000C24       .text chngAnmTag__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::chngAnmTag() {}

/* 00000C24-00000C28       .text ctrlAnmTag__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::ctrlAnmTag() {}

/* 00000C28-00000C68       .text chngAnmAtr__11daNpc_Gk1_cFUc */
void daNpc_Gk1_c::chngAnmAtr(u8 i_anmAtr) {
    if (i_anmAtr == mAnmAtr || i_anmAtr > 5) {
        return;
    }
    mAnmAtr = i_anmAtr;
    setAnm_ATR();
}

/* 00000C68-00000C74       .text ctrlAnmAtr__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::ctrlAnmAtr() {
    if (mAnmAtr == (s8)5) {
        return;
    }
}

/* 00000C74-00000CD8       .text setAnm_ATR__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::setAnm_ATR() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[5] = {
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00000CD8-00000D94       .text anmAtr__11daNpc_Gk1_cFUs */
void daNpc_Gk1_c::anmAtr(u16 i_msgStatus) {
    switch (i_msgStatus) {
        case 6:
            if (m7B5 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m7B5++;
            }
            {
                u8 mesg_anime_tag_info = dComIfGp_getMesgAnimeTagInfo();
                if (mesg_anime_tag_info != 0xFF && mesg_anime_tag_info != mAnmTag) {
                    dComIfGp_clearMesgAnimeTagInfo();
                    mAnmTag = mesg_anime_tag_info;
                    chngAnmTag();
                }
            }
            break;
        case 0xE:
            m7B5 = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000D94-00000EAC       .text next_msgStatus__11daNpc_Gk1_cFPUl */
u16 daNpc_Gk1_c::next_msgStatus(u32* i_msg_no) {
    /* Nonmatching */
    u16 ret = 0xF;
    switch (*i_msg_no) {
        case 0x28A1:
            *i_msg_no = 0x28A2;
            break;
        case 0x28A2:
            *i_msg_no = 0x28A3;
            break;
        case 0x28A3:
            *i_msg_no = 0x28A4;
            break;
        case 0x28A4:
            *i_msg_no = 0x28A5;
            break;
        case 0x28A6:
            *i_msg_no = 0x28A7;
            break;
        case 0x28A7:
            *i_msg_no = 0x28A8;
            break;
        case 0x28A8:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1640)) {
                ret = 0x10;
            } else {
                *i_msg_no = 0x28A9;
            }
            break;
        case 0x28A9:
            *i_msg_no = 0x28AA;
            break;
        case 0x28AB:
            *i_msg_no = 0x28AC;
            break;
        case 0x28AC:
            *i_msg_no = 0x28AD;
            break;
        case 0x28AD:
            *i_msg_no = 0x28AE;
            break;
        case 0x28AF:
            *i_msg_no = 0x28B0;
            break;
        default:
            ret = 0x10;
            break;
    }
    return ret;
}

/* 00000EAC-00000F50       .text getMsg_GK1_0__11daNpc_Gk1_cFv */
u32 daNpc_Gk1_c::getMsg_GK1_0() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B02) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1680)) {
        return 0x28A1;
    }
    if (dKy_daynight_check() == 0) {
        return (dComIfGs_isEventBit(dSv_event_flag_c::UNK_1640) != 0 ? 1 : 0) + 0x28A6;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E08)) {
        return 0x28AF;
    }
    return 0x28AB;
}

/* 00000F50-00000F8C       .text getMsg__11daNpc_Gk1_cFv */
u32 daNpc_Gk1_c::getMsg() {
    u32 ret = 0;
    switch (mType) {
        case 0:
            ret = getMsg_GK1_0();
            break;
    }
    return ret;
}


/* 00000F8C-00001018       .text eventOrder__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::eventOrder() {
    s8 status = mStatus;
    if (status == 1 || status == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mStatus == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (status >= 3) {
        mEventIdx = status - 3;
        fopAcM_orderOtherEventId(this, mEventIdTable[mEventIdx], 0xFF, 0xFFFF, 0, 1);
    }
}

/* 00001018-000010CC       .text checkOrder__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdTable[mEventIdx]) && mStatus >= 3) {
            mStatus = 0;
            mAnmAtr = 0xFF;
            mAnmTag = 0xFF;
        }
    } else if (eventInfo.checkCommandTalk() && (mStatus == 1 || mStatus == 2)) {
        mStatus = 0;
        m7A5 = 1;
    }
}

/* 000010CC-00001164       .text chk_talk__11daNpc_Gk1_cFv */
u8 daNpc_Gk1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mTalkStatus = dComIfGp_event_getPreItemNo();
            return TRUE;
        }
        return FALSE;
    }
    mTalkStatus = 0xFF;
    return TRUE;
}

/* 00001164-000011A4       .text chk_parts_notMov__11daNpc_Gk1_cFv */
u8 daNpc_Gk1_c::chk_parts_notMov() {
    u8 ret = FALSE;
    if (mLookAtNckX != m_jnt.getHead_y() || mLookAtBoneX != m_jnt.getBackbone_y() || mLookAtY != current.angle.y) {
        ret = TRUE;
    }
    return ret;
}

/* 000011A4-000011F8       .text searchByID__11daNpc_Gk1_cFUiPi */
fopAc_ac_c* daNpc_Gk1_c::searchByID(fpc_ProcID i_procID, int* i_param_2) {
    fopAc_ac_c* actor = NULL;
    *i_param_2 = 0;
    if (fopAcM_SearchByID(i_procID, &actor) == 0) {
        *i_param_2 = 1;
    }
    return actor;
}

/* 000011F8-000013BC       .text lookBack__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::lookBack() {
    cXyz dst_pos;
    cXyz* dst_pos_p;
    cXyz src_pos;
    s16 desired_yrot;
    bool head_only_follow;
    mLookAtNckX = m_jnt.getHead_y();
    mLookAtBoneX = m_jnt.getBackbone_y();
    mLookAtY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dst_pos.set(0.0f, 0.0f, 0.0f);
    dst_pos_p = NULL;
    desired_yrot = current.angle.y;
    head_only_follow = m7A6;

    switch (m7B1) {
        case 1:
            mEyePos = dNpc_playerEyePos(-20.0f);
            dst_pos = mEyePos;
            dst_pos_p = &dst_pos;
            break;
        case 2:
            dst_pos = mEyePos;
            dst_pos_p = &dst_pos;
            break;
        case 3:
            desired_yrot = m79A;
            break;
        case 4:
        {
            int result;
            fopAc_ac_c* actor = searchByID(mPartnerProcID, &result);
            if (actor != NULL && result == 0) {
                mEyePos = actor->current.pos;
                mEyePos.y = actor->eyePos.y;
                dst_pos = mEyePos;
                dst_pos_p = &dst_pos;
            }
            break;
        }
    }
    m_jnt.lookAtTarget_2(&current.angle.y, dst_pos_p, src_pos, desired_yrot, l_HIO.mPrmTbl.mLookAtMaxVel, head_only_follow);
}

/* 000013BC-0000143C       .text chkAttention__11daNpc_Gk1_cFv */
bool daNpc_Gk1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 0000143C-00001494       .text setAttention__11daNpc_Gk1_cFb */
void daNpc_Gk1_c::setAttention(bool i_setEyePos) {
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY,
        current.pos.z
    );
    if (mActionResult != 0 || i_setEyePos) {
        eyePos.set(mTargetPos.x, mTargetPos.y, mTargetPos.z);
    }
}

/* 00001494-0000151C       .text decideType__11daNpc_Gk1_cFi */
bool daNpc_Gk1_c::decideType(int i_type) {
    if (mTypeInit > 0) {
        return 1;
    }
    mTypeInit = 1;
    mType = 0;
    strcpy(m_arcname, "Gk");
    return mTypeInit != -1 && mType != -1;
}


/* 0000151C-000015BC       .text privateCut__11daNpc_Gk1_cFi */
void daNpc_Gk1_c::privateCut(int i_staff_idx) {
    /* Nonmatching */
    static char* a_cut_tbl[] = {
        "dummy",
    };
    if (i_staff_idx != -1) {
        m7A9 = dComIfGp_evmng_getMyActIdx(i_staff_idx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);
        if (m7A9 == -1) {
            dComIfGp_evmng_cutEnd(i_staff_idx);
            return;
        }
        dComIfGp_evmng_getIsAddvance(i_staff_idx);
        dComIfGp_evmng_cutEnd(i_staff_idx);
    }
}

/* 000015BC-000015E0       .text endEvent__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mAnmTag = 0xFF;
}

/* 000015E0-00001618       .text isEventEntry__11daNpc_Gk1_cFv */
s32 daNpc_Gk1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 00001618-0000169C       .text event_proc__11daNpc_Gk1_cFi */
void daNpc_Gk1_c::event_proc(int i_staff_idx) {
    if (dComIfGp_evmng_endCheck(mEventIdTable[mEventIdx])) {
        endEvent();
        return;
    }
    if (!mEventCut.cutProc()) {
        privateCut(i_staff_idx);
    }
}

/* 0000169C-00001748       .text set_action__11daNpc_Gk1_cFM11daNpc_Gk1_cFPCvPvPv_iPv */
BOOL daNpc_Gk1_c::set_action(int (daNpc_Gk1_c::*i_newProcFunc)(void*), void* i_argsP) {
    if (mProcFunc != i_newProcFunc) {
        if (mProcFunc) {
            m7B4 = 9;
            (this->*mProcFunc)(i_argsP);
        }
        mProcFunc = i_newProcFunc;
        m7B4 = 0;
        (this->*mProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00001748-000017C8       .text setStt__11daNpc_Gk1_cFSc */
void daNpc_Gk1_c::setStt(s8 i_status) {
    s8 temp = mAnmNum;
    mAnmNum = i_status;
    switch (mAnmNum) {
        case 0:
            break;
        case 1:
            mStatus = 0;
            speedF = 0.0f;
            break;
        case 2:
            mStatus = 0;
            mAnmAtr = 0xFF;
            mAnmTag = 0xFF;
            m7B5 = 0;
            m7B0 = temp;
            break;
    }
    setAnm();
}

/* 000017C8-000019E0       .text chk_attn__11daNpc_Gk1_cFv */
u8 daNpc_Gk1_c::chk_attn() {
    /* Nonmatching */
    f32 dist = std::sqrtf((current.pos - dComIfGp_getPlayer(0)->current.pos).abs2XZ());
    f32 height_diff = current.pos.y - dComIfGp_getPlayer(0)->current.pos.y;
    s16 target_angle = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos);
    s16 angle_diff = target_angle - current.angle.y;
    if (m7B1 == 1) {
        u8 ret = FALSE;
        u8 flag = ret;
        if (dist < 200.0f && (f32)abs(angle_diff) / DEG2S_CONSTANT < 90.0f) {
            flag = TRUE;
        }
        if (flag && std::fabsf(height_diff) < 300.0f) {
            ret = TRUE;
        }
        return ret;
    } else {
        u8 ret = FALSE;
        u8 flag = ret;
        if (dist < 200.0f && (f32)abs(angle_diff) / DEG2S_CONSTANT < 60.0f) {
            flag = TRUE;
        }
        if (flag && std::fabsf(height_diff) < 300.0f) {
            ret = TRUE;
        }
        return ret;
    }
}

/* 000019E0-00001B74       .text wait_1__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::wait_1() {
    f32 dist = std::sqrtf((current.pos - dComIfGp_getPlayer(0)->current.pos).abs2XZ());
    m7A7 = dist > 300.0f;
    if (m7A7) {
        cLib_addCalcAngleS(&current.angle.y, mPrevAngle.y, 4, 0x800, 0x80);
    }
    if (m7A5) {
        if (chk_talk()) {
            setStt(2);
            m7B1 = 1;
            m7A6 = 0;
            m7A7 = 0;
            m_jnt.setTrn();
        }
        return TRUE;
    }
    mStatus = 2;
    m7A6 = 1;
    if (chk_attn()) {
        m7B1 = 1;
        return TRUE;
    }
    m7B1 = 0;
    return TRUE;
}

/* 00001B74-00001C74       .text talk_1__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::talk_1() {
    BOOL parts_not_mov = chk_parts_notMov();
    talk(1);
    if (mpCurrMsg == NULL) {
        return TRUE;
    }
    switch (mpCurrMsg->mStatus) {
        case 2:
        case 6:
            break;
        case 19:
            switch (mCurrMsgNo) {
                case 0x28A5:
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_1680);
                    break;
                case 0x28AA:
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_1640);
                    break;
            }
            mTalkStatus = 0xFF;
            m7A5 = 0;
            setStt(m7B0);
            mEvTimer = cLib_getRndValue(15, 30);
            endEvent();
            break;
    }
    return parts_not_mov;
}

/* 00001C74-00001D30       .text wait_action1__11daNpc_Gk1_cFPv */
BOOL daNpc_Gk1_c::wait_action1(void*) {
    switch (m7B4) {
        case 0:
            setStt(1);
            m7A7 = 1;
            m7B4++;
            break;
        case 1:
        case 2:
        case 3:
            m7A4 = chkAttention();
            switch (mAnmNum) {
                case 1:
                    mActionResult = wait_1();
                    break;
                case 2:
                    mActionResult = talk_1();
                    break;
            }
            break;
        case 9:
            break;
        default:
            break;
    }
    return TRUE;
}

/* 00001D30-00001E70       .text demo__11daNpc_Gk1_cFv */
u8 daNpc_Gk1_c::demo() {
    if (demoActorID == 0) {
        if (m7A8 != 0) {
            m7A8 = 0;
        }
    } else {
        if (m7A8 == 0) {
            m7A8 = 1;
            m7A1 = 0;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        J3DAnmTexPattern* demo_btp = mBtpAnm.getBtpAnm();
        if (demo_btp) {
            u8 frame_max = (u8)demo_btp->getFrameMax();
            mBlinkFrame += 1;
            if (mBlinkFrame >= frame_max) {
                mBlinkFrame = frame_max;
            }
        }
        J3DAnmTexPattern* demo_pattern = demo_actor->getP_BtpData(m_arcname);
        if (demo_pattern) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), demo_pattern, 1, 0, 1.0f, 0, -1, true, FALSE);
            mBtpNum = 1;
            mBlinkFrame = 0;
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, m_arcname, 0, NULL, 0, 0);
    }
    return m7A8;
}

/* 00001E70-00001F48       .text shadowDraw__11daNpc_Gk1_cFv */
void daNpc_Gk1_c::shadowDraw() {
    cXyz temp(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowID = dComIfGd_setShadow(
        mShadowID,
        1,
        mpMorf->getModel(),
        &temp,
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
        if (mpItemModel != NULL) {
            dComIfGd_addRealShadow(mShadowID, mpItemModel);
        }
        if (mpHatModel != NULL) {
            dComIfGd_addRealShadow(mShadowID, mpHatModel);
        }
    }
}

/* 00001F48-00002064       .text _draw__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_draw() {
    J3DModel* morf_model = mpMorf->getModel();
    J3DModelData* model_data = morf_model->getModelData();
    if (m7A0 || m7A2) {
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model, &tevStr);
    mBtpAnm.entry(model_data, mBlinkFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);
    if (mpItemModel != NULL) {
        g_env_light.setLightTevColorType(mpItemModel, &tevStr);
        mDoExt_modelEntryDL(mpItemModel);
    }
    if (mpHatModel != NULL) {
        g_env_light.setLightTevColorType(mpHatModel, &tevStr);
        mDoExt_modelEntryDL(mpHatModel);
    }
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK59, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002064-00002280       .text _execute__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_execute() {
    if (!m7A3) {
        mPrevPos = current.pos;
        mPrevAngle = current.angle;
        m7A3 = true;
    }
    m_jnt.setParam(
        l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY,
        l_HIO.mPrmTbl.mMinBackboneX, l_HIO.mPrmTbl.mMinBackboneY,
        l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY,
        l_HIO.mPrmTbl.mMaxTurnStep);
    if (m7A0 && demoActorID == 0) {
        return TRUE;
    }
    checkOrder();
    if (!demo()) {
        s32 cond = -1;
        if (dComIfGp_event_runCheck() && eventInfo.getCommand() != 1) {
            cond = isEventEntry();
        }
        if (cond >= 0) {
            event_proc(cond);
        } else {
            (this->*mProcFunc)(NULL);
        }
        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        play_animation();
    } else {
        m7A0 = false;
    }
    eventOrder();
    mAngle = current.angle;
    if (!m7A1) {
        shape_angle = current.angle;
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);
    if (!m7A8) {
        setCollision(90.0f, 200.0f);
    }
    return TRUE;
}

/* 00002280-000022D4       .text _delete__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arcname);
#if VERSION > VERSION_DEMO
    if (heap != NULL && mpMorf != NULL)
#else
    if (mpMorf != NULL)
#endif
    {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 000022D4-00002520       .text _create__11daNpc_Gk1_cFv */
cPhs_State daNpc_Gk1_c::_create() {
    /* Nonmatching */
    static int a_siz_tbl[] = {
        0x00000000,
        0x00000000
    };

    fopAcM_ct_Retail(this, daNpc_Gk1_c);
    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    cPhs_State state = dComIfG_resLoad(&mPhs, m_arcname);
    mCreatePhase = state == cPhs_COMPLEATE_e;
    if (!mCreatePhase) {
        return state;
    }
#if VERSION == VERSION_DEMO
    l_HIO.entryHIO("");
    fopAcM_ct(this, daNpc_Gk1_c);
#endif
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[mTypeInit])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -90.0f, -20.0f, -80.0f, 90.0f, 200.0f, 80.0f);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 000027EC-00002AE8       .text bodyCreateHeap__11daNpc_Gk1_cFv */
s32 daNpc_Gk1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(m_arcname, dRes_ID_GK_BDL_GK_e);
    JUT_ASSERT(VERSION_SELECT(1551, 1551, 1553, 1553), a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        NULL,
        -1,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11020022
    );
    if (mpMorf == NULL) {
        return FALSE;
    }
    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    if (!init_texPttrnAnm(0, false)) {
        mpMorf = NULL;
        return FALSE;
    }
    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(VERSION_SELECT(1571, 1571, 1573, 1573), m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(VERSION_SELECT(1573, 1573, 1575, 1575), m_bbone_jnt_num >= 0);
    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(VERSION_SELECT(1575, 1575, 1577, 1577), m_nck_jnt_num >= 0);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_nck_jnt_num)->setCallBack(nodeCB_Neck);
    mpMorf->getModel()->setUserArea((u32)this);
    return TRUE;
}

/* 00002AE8-00002BA8       .text itemCreateHeap__11daNpc_Gk1_cFv */
s32 daNpc_Gk1_c::itemCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(m_arcname, dRes_ID_GK_BDL_GK_HAIR_e);
    JUT_ASSERT(VERSION_SELECT(1596, 1596, 1598, 1598), a_mdl_dat != NULL);
    mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    if (mpItemModel == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00002BA8-00002C68       .text hat_CreateHeap__11daNpc_Gk1_cFv */
s32 daNpc_Gk1_c::hat_CreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(m_arcname, dRes_ID_GK_BDL_GK_HAT_e);
    JUT_ASSERT(VERSION_SELECT(1612, 1612, 1614, 1614), a_mdl_dat != NULL);
    mpHatModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    if (mpHatModel == NULL) {
        return FALSE;
    }
    return TRUE;
}

/* 00002C68-00002D2C       .text CreateHeap__11daNpc_Gk1_cFv */
BOOL daNpc_Gk1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }
    if (!itemCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }
    if (!hat_CreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }
    mAcchCir.SetWall(30.0f, 90.0f);
    mObjAcch.Set(
        fopAcM_GetPosition_p(this),
        fopAcM_GetOldPosition_p(this),
        this,
        1,
        &mAcchCir,
        fopAcM_GetSpeed_p(this),
        NULL,
        NULL
    );
    return TRUE;
}

/* 00002D2C-00002D4C       .text daNpc_Gk1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Gk1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_create();
}

/* 00002D4C-00002D6C       .text daNpc_Gk1_Delete__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Delete(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_delete();
}

/* 00002D6C-00002D8C       .text daNpc_Gk1_Execute__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Execute(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_execute();
}

/* 00002D8C-00002DAC       .text daNpc_Gk1_Draw__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_Draw(daNpc_Gk1_c* i_this) {
    return ((daNpc_Gk1_c*)i_this)->_draw();
}

/* 00002DAC-00002DB4       .text daNpc_Gk1_IsDelete__FP11daNpc_Gk1_c */
static BOOL daNpc_Gk1_IsDelete(daNpc_Gk1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Gk1_Method = {
    (process_method_func)daNpc_Gk1_Create,
    (process_method_func)daNpc_Gk1_Delete,
    (process_method_func)daNpc_Gk1_Execute,
    (process_method_func)daNpc_Gk1_IsDelete,
    (process_method_func)daNpc_Gk1_Draw,
};

actor_process_profile_definition g_profile_NPC_GK1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_GK1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Gk1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_GK1_e,
    /* Actor SubMtd */ &l_daNpc_Gk1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
