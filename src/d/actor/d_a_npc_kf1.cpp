/**
 * d_a_npc_kf1.cpp
 * NPC - Mila's Father (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kf1.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_tsubo.h"
#include "d/d_a_obj.h"
#include "d/d_com_lib_game.h"
#include "d/d_snap.h"
#include "d/d_demo.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_executor.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_counter.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "m_Do/m_Do_mtx.h"

class daNpc_Kf1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x12 */ s16 mCalcAngleTarget;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ s16 m18;
        /* 0x1A */ s16 mWalkStep;
        /* 0x1C */ s16 mWalkMaxStep;
        /* 0x1E */ s16 m1E;
        /* 0x20 */ f32 mWalkSpeed;
        /* 0x24 */ f32 mWalkMaxSpeed;
        /* 0x28 */ f32 mChaseSpeed;
        /* 0x2C */ f32 m2C;
    };  // Size: 0x30

    daNpc_Kf1_HIO_c();
    virtual ~daNpc_Kf1_HIO_c() {};

    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};  // Size: 0x3C

/* 000000EC-00000150       .text __ct__15daNpc_Kf1_HIO_cFv */
daNpc_Kf1_HIO_c::daNpc_Kf1_HIO_c() { /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX      */ 0x2000,
        /* mMaxHeadY      */ 0x07D0,
        /* mMinHeadX      */ 0xFC18,
        /* mMinHeadY      */ 0xF830,
        /* mMaxBackboneX  */ 0x0000,
        /* mMaxBackboneY  */ 0x1388,
        /* mMinBackboneX  */ 0xF060,
        /* mMinBackboneY  */ 0xEC78,
        /* mMaxTurnStep   */ 0x05DC,
        /* mCalcAngleTarget */ 0x04B0,
        /* mAttPosOffsetY */ 200.0f,
        /* m18            */ 0,
        /* mWalkStep      */ 10,
        /* mWalkMaxStep   */ 0x0400,
        /* m1E            */ 0,
        /* mWalkSpeed     */ 0.5f,
        /* mWalkMaxSpeed  */ 2.0f,
        /* mChaseSpeed    */ 0.2f,
        /* m2C            */ 8.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static daNpc_Kf1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_judge) {
    if (i_judge == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Kf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_Head(i_node,
                                                                                           j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) { /* Nonmatching */
    static cXyz a_eye_pos_off(30.0f, 30.0f, 0.0f);

    s32 jointIdx = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mHeadPos.set(mDoMtx_stack_c::get()[0][3], mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mEyePos);
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000314-00000360       .text nodeCB_Neck__FP7J3DNodei */
static BOOL nodeCB_Neck(J3DNode* i_node, int i_judge) {
    if (i_judge == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Kf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_Neck(i_node,
                                                                                           j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Neck(J3DNode* i_node, J3DModel* i_model) {
    s32 jointIdx = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000400-0000044C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_judge) {
    if (i_judge == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Kf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_BackBone(
                i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    s32 jointIdx = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 000004EC-0000050C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->CreateHeap();
}

/* 0000050C-0000059C       .text searchActor_Tsubo__FPvPv */
static void* searchActor_Tsubo(void* i_actor, void*) {
    if (l_check_wrk < 0x14 && fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_TSUBO_e &&
        ((daTsubo::Act_c*)i_actor)->prm_chk_type_kutani())
    {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 0000059C-0000061C       .text init_KF1_0__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::init_KF1_0() { /* Nonmatching */
    if (!dComIfGs_isEventBit(0x2D01)) {
        set_action(&daNpc_Kf1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 0000061C-0000083C       .text createInit__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::createInit() { /* Nonmatching */
    static const char* l_evn_tbl[] = {"angry", "rupee_age", "bensyou"};

    s32 i;

    for (i = 0; i < 3; i++) {
        mEvtIdx[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xFF);
    }
    mEventCut.setActorInfo2("Kf1", this);
    m79F = (fopAcM_GetParam(this) >> 8) & 0xFF;
    int roomNo = 0xFF;
    u8 paramRoom = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (paramRoom != 0xFF) {
        mPath.setInf(paramRoom, current.roomNo, TRUE);
        if (mPath.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            roomNo = 0xD9;
            set_pthPoint(0);
        } else {
            return FALSE;
        }
    } else if (!mPath.isPath()) {
        return FALSE;
    }
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    gravity = -4.5f;
    mAnmNo = 10;
    bool init_success;
    switch (mType2) {
        case 0:
            init_success = init_KF1_0();
            break;
        default:
            init_success = false;
            break;
    }
    if (!init_success) {
        return FALSE;
    }
    m722.x = current.angle.x;
    m722.y = current.angle.y;
    m722.z = current.angle.z;
    shape_angle.x = m722.x;
    shape_angle.y = m722.y;
    shape_angle.z = m722.z;
    mStts.Init(roomNo, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    play_animation();
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(TRUE);
    return TRUE;
}

/* 0000083C-000008E4       .text play_animation__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_animation() {
    u32 snd = 0;
    play_btp_anm();
    if (mObjAcch.ChkGroundHit()) {
        snd = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    mAnmResult = mpMorf->play(&eyePos, snd, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mAnmResult = 1;
    }
    mPrevMorfFrame = mpMorf->getFrame();
}

/* 000008E4-00000A20       .text setMtx__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setMtx(bool i_setAttention) { /* Nonmatching */
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(m722.x, m722.y, m722.z);
    PSMTXCopy(mDoMtx_stack_c::get(), mpMorf->getModel()->getBaseTRMtx());
    mpMorf->calc();
    if (mpItemModel != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(mHeadJntNo));
        mDoMtx_stack_c::transM(33.12f, 3.26f, 0.0f);
        mDoMtx_stack_c::XYZrotM(-0x4000, -0x4000, 0);
        PSMTXCopy(mDoMtx_stack_c::get(), mpItemModel->getBaseTRMtx());
        mDoExt_modelEntryDL(mpItemModel);
    }
    setAttention(i_setAttention);
}

/* 00000A20-00000A34       .text bckResID__11daNpc_Kf1_cFi */
int daNpc_Kf1_c::bckResID(int i_idx) { /* Nonmatching */
    static int a_resID_tbl[] = {0xA, 0xC, 0x6, 0x7, 0x8, 0x9, 0x5, 0x3, 0x4, 0xB};
    return a_resID_tbl[i_idx];
}

/* 00000A34-00000A48       .text btpResID__11daNpc_Kf1_cFi */
int daNpc_Kf1_c::btpResID(int i_idx) { /* Nonmatching */
    static int a_resID_tbl[] = {0x2, 0xD};
    return a_resID_tbl[i_idx];
}

/* 00000A48-00000B4C       .text setBtp__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::setBtp(s8 i_btpNo, bool i_modify) { /* Nonmatching */
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    if (i_btpNo < 0) {
        return false;
    }
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectRes(mArcName, btpResID(i_btpNo));
    JUT_ASSERT(0x20A, a_btp != 0);
    mBtpNo = i_btpNo;
    mBtpFrame = 0;
    mBtpTimer = 0;
    bool ret = mBtpAnm.init(model_data, a_btp, TRUE, 0, 1.0f, 0, -1, i_modify, FALSE);
    return ret;
}

/* 00000B4C-00000B6C       .text init_texPttrnAnm__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::init_texPttrnAnm(s8 i_btpNo, bool i_modify) {
    return setBtp(i_btpNo, i_modify);
}

/* 00000B6C-00000C08       .text play_btp_anm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_btp_anm() { /* Nonmatching */
    u8 attr = mBtpAnm.getBtpAnm()->getAttribute();
    if (mBtpNo == 0 && cLib_calcTimer<s16>(&mBtpTimer)) {
        return;
    }
    mBtpFrame++;
    if (mBtpFrame >= attr) {
        if (mBtpNo != 0) {
            mBtpFrame = attr;
        } else {
            mBtpTimer = cLib_getRndValue(0x3C, 0x5A);
            mBtpFrame = 0;
        }
    }
}

/* 00000C08-00000CA4       .text setAnm_anm__11daNpc_Kf1_cFPQ211daNpc_Kf1_c9anm_prm_c */
void daNpc_Kf1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->mAnmNum < 0 || mAnmNo == i_anmPrmP->mAnmNum) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed,
                     bckResID(i_anmPrmP->mAnmNum), -1, mArcName);
    mAnmNo = i_anmPrmP->mAnmNum;
    mAnmResult = 0;
    m79D = 0;
    mPrevMorfFrame = 0.0f;
}

/* 00000CA4-00000D14       .text setAnm_NUM__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::setAnm_NUM(int i_anmNum, int i_tex) { /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 0, 15.0f, 1.0f, 2},
        {1, 1, 0, 8.0f, 1.0f, 2},
        {2, 0, 0, 8.0f, 1.0f, 2},
        {3, 0, 0, 8.0f, 1.0f, 2},
        {4, 0, 0, 8.0f, 1.0f, 2},
        {5, 0, 0, 8.0f, 1.0f, 2},
        {6, 0, 0, 8.0f, 1.0f, 2},
        {7, 0, 0, 8.0f, 1.0f, 0},
        {8, 0, 0, 8.0f, 1.0f, 0},
        {9, 1, 0, 8.0f, 1.0f, 2},
    };
    if (i_tex != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].mBtpNum, TRUE);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 00000D14-00000D80       .text setAnm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm() { /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[] = {
        {-1, -1, 0, 0.0f, 0.0f, -1},
        {-1, -1, 0, 0.0f, 0.0f, -1},
        {-1, -1, 0, 0.0f, 0.0f, -1},
        {1, 1, 0, 8.0f, 1.0f, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mStatus].mBtpNum, TRUE);
    setAnm_anm(&a_anm_prm_tbl[mStatus]);
}

/* 00000D80-00000D84       .text chngAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::chngAnmTag() {}

/* 00000D84-00000D88       .text ctrlAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmTag() {}

/* 00000D88-00000DEC       .text chngAnmAtr__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::chngAnmAtr(u8 i_attr) { /* Nonmatching */
    if ((s32)mCurrMsgNo == 0x1C2E) {
        g_dComIfG_gameInfo.play.getEvent()->mHindFlag &= ~0x80;
    }
    if (i_attr != mAtr && i_attr <= 0xB) {
        mAtr = i_attr;
        setAnm_ATR();
    }
}

/* 00000DEC-00000E60       .text ctrlAnmAtr__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmAtr() { /* Nonmatching */
    switch (mAtr) {
        case 7:
        case 8:
        case 9:
            if (mAnmResult != 0) {
                setAnm_NUM(0, TRUE);
                mAtr = 0;
            }
            break;
    }
}

/* 00000E60-00000EC4       .text setAnm_ATR__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm_ATR() { /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 0, 15.0f, 1.0f, 2},
        {1, 1, 0, 8.0f, 1.0f, 2},
        {2, 0, 0, 8.0f, 1.0f, 2},
        {3, 0, 0, 8.0f, 1.0f, 2},
        {4, 0, 0, 8.0f, 1.0f, 2},
        {5, 0, 0, 8.0f, 1.0f, 2},
        {6, 0, 0, 8.0f, 1.0f, 2},
        {7, 0, 0, 8.0f, 1.0f, 0},
        {8, 0, 0, 8.0f, 1.0f, 0},
        {3, 0, 0, 8.0f, 1.0f, 2},
        {9, 1, 0, 8.0f, 1.0f, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mAtr].mBtpNum, TRUE);
    setAnm_anm(&a_anm_prm_tbl[mAtr]);
}

/* 00000EC4-00000F80       .text anmAtr__11daNpc_Kf1_cFUs */
void daNpc_Kf1_c::anmAtr(u16 i_msgStatus) {
    switch (i_msgStatus) {
        case 6:
            if ((s8)m7FE == 0) {
                chngAnmAtr(g_dComIfG_gameInfo.play.mMesgAnime);
                m7FE = m7FE + 1;
            }
            if (g_dComIfG_gameInfo.play.mMesgAnimeTagInfo != 0xFF &&
                g_dComIfG_gameInfo.play.mMesgAnimeTagInfo != mTag)
            {
                u8 oldTag = g_dComIfG_gameInfo.play.mMesgAnimeTagInfo;
                g_dComIfG_gameInfo.play.mMesgAnimeTagInfo = 0xFF;
                mTag = oldTag;
                chngAnmTag();
            }
            break;
        case 0xE:
            m7FE = 0;
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000F80-000010F4       .text next_msgStatus__11daNpc_Kf1_cFPUl */
u16 daNpc_Kf1_c::next_msgStatus(u32* i_msgNo) { /* Nonmatching */
    u16 ret = 0xF;
    switch (*i_msgNo) {
        case 0x1C23:
            switch (mpCurrMsg->mSelectNum) {
                case 0:
                    *i_msgNo = 0x1C24;
                    break;
                case 1:
                    *i_msgNo = 0x1C25;
                    break;
            }
            break;
        case 0x1C28:
            switch (mpCurrMsg->mSelectNum) {
                case 0:
                    *i_msgNo = 0x1C2A;
                    break;
                case 1:
                    *i_msgNo = 0x1C29;
                    break;
            }
            break;
        case 0x1C24:
            dComIfGs_onEventBit(0xB02);
            ret = 0x10;
            break;
        case 0x1C2B:
            m7A0 = 1;
            ret = 0x10;
            break;
        case 0x1C21:
            *i_msgNo = 0x1C22;
            break;
        case 0x1C22:
            *i_msgNo = 0x1C34;
            break;
        case 0x1C34:
            *i_msgNo = 0x1C23;
            break;
        case 0x1C27:
            *i_msgNo = 0x1C28;
            break;
        case 0x1C2A:
            *i_msgNo = 0x1C2B;
            break;
        case 0x1C30:
            *i_msgNo = 0x1C31;
            break;
        case 0x1C2D:
            *i_msgNo = 0x1C2E;
            break;
        case 0x1C33: {
            s32 bensyou = mTsuboIdx * 10;
            *i_msgNo = (mRupeeCnt >= bensyou) ? 0x1C2F : 0x1C30;
            break;
        }
        case 0x1C36:
            *i_msgNo = 0x1C37;
            break;
        default:
            ret = 0x10;
            break;
    }
    return ret;
}

/* 000010F4-000011DC       .text getMsg_KF1_0__11daNpc_Kf1_cFv */
u32 daNpc_Kf1_c::getMsg_KF1_0() {
    if (mTalkStt != 0) {
        return 0x1C38;
    }
    if (dComIfGs_isEventBit(0xA02)) {
        if (!dComIfGs_isSymbol(0)) {
            return 0x1C3B;
        }
    }
    if (dComIfGs_isEventBit(0xB02)) {
        u8 eventReg = dComIfGs_getEventReg(0xBCFF);
        if (dKy_daynight_check() == 1 || !dComIfGs_isEventBit(0x2780) || (eventReg & 1) != 0) {
            return 0x1C26;
        }
        return 0x1C27;
    }
    return 0x1C21;
}

/* 000011DC-00001218       .text getMsg__11daNpc_Kf1_cFv */
u32 daNpc_Kf1_c::getMsg() { /* Nonmatching */
    u32 msgNo = 0;
    if ((s32)mType2 == 0) {
        msgNo = getMsg_KF1_0();
    }
    return msgNo;
}

/* 00001218-000012A4       .text eventOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::eventOrder() {
    s8 order = mOrder;
    if (order == 1 || order == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (order >= 3) {
        mCurEvtIdx = order - 3;
        fopAcM_orderOtherEventId(this, mEvtIdx[mCurEvtIdx], 0xFF, 0xFFFF, 0, 1);
    }
}

/* 000012A4-00001380       .text checkOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::checkOrder() { /* Nonmatching */
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEvtIdx[mCurEvtIdx])) {
            if (mOrder >= 3) {
                if (mCurEvtIdx == 0) {
                    dComIfGp_getPlayer(0)->shape_angle.y = dComIfGp_getPlayer(0)->current.angle.y;
                }
                mOrder = 0;
                mAtr = 0xFF;
                mTag = 0xFF;
            }
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mTalkOrder = 1;
        }
    }
}

/* 00001380-00001418       .text chk_talk__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::chk_talk() { /* Nonmatching */
    if (g_dComIfG_gameInfo.play.getEvent()->mTalkButton == 1 ||
        g_dComIfG_gameInfo.play.getEvent()->mTalkButton == 2 ||
        g_dComIfG_gameInfo.play.getEvent()->mTalkButton == 3)
    {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            m79E = g_dComIfG_gameInfo.play.getEvent()->mItemNo;
            return TRUE;
        }
        return FALSE;
    }
    m79E = 0xFF;
    return TRUE;
}

/* 00001418-0000146C       .text searchByID__11daNpc_Kf1_cFUiPi */
fopAc_ac_c* daNpc_Kf1_c::searchByID(fpc_ProcID i_id, int* o_flg) {
    fopAc_ac_c* o_actor = NULL;
    *o_flg = 0;
    if (!fopAcM_SearchByID(i_id, &o_actor)) {
        *o_flg = 1;
    }
    return o_actor;
}

/* 0000146C-0000156C       .text srch_Tsubo__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::srch_Tsubo() { /* Nonmatching */
    s32 i;
    BOOL ret = FALSE;
    if (mPhase != 1) {
        return FALSE;
    }
    m700 = fpcM_ERROR_PROCESS_ID_e;
    l_check_wrk = 0;
    for (i = 0; i < 0x14; i++) {
        l_check_inf[i] = NULL;
    }
    fpcEx_Search(searchActor_Tsubo, this);
    if (l_check_wrk >= 8) {
        mTsuboCnt = 0;
        for (i = 0; i < 8; i++) {
            mTsuboProcId[i] = l_check_inf[i] ? fopAcM_GetID(l_check_inf[i]) : fpcM_ERROR_PROCESS_ID_e;
            mTsuboCnt++;
        }
        ret = TRUE;
        mPhase++;
    }
    return ret;
}

/* 0000156C-000017F4       .text create_rupee__11daNpc_Kf1_cF4cXyzi */
void daNpc_Kf1_c::create_rupee(cXyz i_pos, int i_num) { /* Nonmatching */
    cXyz local(0.2f, 0.2f, 0.2f);
    csXyz angle(0, 0, 0);

    s32 counter = g_Counter.mCounter0;
    for (int i = 0; i < i_num; i++, counter++) {
        f32 a_off_tbl[3] = {-30.0f, 0.0f, 30.0f};
        s16 s = (s16)(cM_rndF(30.0f) - 15.0f + a_off_tbl[counter % 3]);
        s32 rot = (s32)(s * 182.0389f);
        angle.y = current.angle.y + rot;
        s8 roomNo = current.roomNo;
        f32 speedY = 31.0f + cM_rndFX(4.0f);
        f32 speed = 13.0f + cM_rndFX(2.0f);
        fopAc_ac_c* a_actor = fopAcM_createItemForKP2(&i_pos, 4, roomNo, NULL, NULL, speed, speedY,
                                                      -2.0f, 1);
        JUT_ASSERT(0x412, 0 != a_actor);
        if (a_actor != NULL) {
            fopAcM_OnStatus(a_actor, fopAcStts_UNK4000_e);
            fopAcM_OffStatus(a_actor, fopAcStts_NOCULLEXEC_e);
            a_actor->scale.set(local);
            a_actor->shape_angle = angle;
            a_actor->current.angle = a_actor->shape_angle;
        }
        mItemProcId[i] = (a_actor != NULL) ? fopAcM_GetID(a_actor) : -1;
    }
}

/* 000017F4-00001A0C       .text ready_kutaniCamera__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::ready_kutaniCamera(int i_idx, int i_flg) { /* Nonmatching */
    cXyz local;
    csXyz angle;
    fopAc_ac_c* a_actor;
    int i_flg2;

    fopAc_ac_c* old = searchByID(m7E8, &i_flg2);
    if (old != NULL && i_flg2 == 0) {
        fopAcM_delete(old);
    }
    if (i_flg == 0) {
        return;
    }
    local.set(0.0f, 0.0f, 0.0f);
    angle.set(0, 0, 0);
    a_actor = searchByID(mKutaniProcId[i_idx], &i_flg2);
    JUT_ASSERT(0x432, 0 != a_actor && 0 == i_flg2);
    g_dComIfG_gameInfo.play.getEvent()->setPtI(a_actor);
    angle.y = a_actor->shape_angle.y;
    local.x = a_actor->current.pos.x;
    local.y = a_actor->current.pos.y;
    local.z = a_actor->current.pos.z;
    local.y += 0.1f;
    fopAc_ac_c* item = fopAcM_createItemForKP2(&local, 4, current.roomNo, &angle, &local, 180.0f,
                                               180.0f, 0.5f, 1);
    JUT_ASSERT(0x43E, 0 != a_actor);
    fopAcM_OnStatus(item, fopAcStts_UNK40000_e);
    fopAcM_OffStatus(item, fopAcStts_UNK40_e);
    item->current.pos.set(local);
    item->shape_angle.x = angle.x;
    item->shape_angle.y = angle.y;
    item->shape_angle.z = angle.z;
    m7E8 = fopAcM_GetID(item);
}

/* 00001A0C-00001BD0       .text lookBack__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::lookBack() { /* Nonmatching */
    cXyz src_pos;
    cXyz dstPos;
    cXyz* dstPos_p;
    s16 desiredYrot;
    s16 maxStep;
    BOOL headOnlyFollow;

    m776 = m_jnt.getHead_y();
    m778 = m_jnt.getBackbone_y();
    m774 = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = current.pos.y + eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    headOnlyFollow = mLookFlag;
    switch (mLookMode) {
        case 1:
            dstPos = dNpc_playerEyePos(-20.0f);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = current.pos.y + eyePos.y;
            break;
        case 2:
            dstPos.set(mTargetPos);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = current.pos.y + eyePos.y;
            break;
        case 3:
            desiredYrot = m79A;
            break;
        case 4: {
            int flg;
            fopAc_ac_c* tsubo = searchByID(m704, &flg);
            if (tsubo != NULL && flg == 0) {
                mTargetPos.set(tsubo->current.pos);
                mTargetPos.y = tsubo->current.pos.y + tsubo->speedF;
                dstPos.set(mTargetPos);
                dstPos_p = &dstPos;
            }
            break;
        }
    }
    src_pos.x = src_pos.x;
    src_pos.y = src_pos.y;
    src_pos.z = src_pos.z;
    m_jnt.lookAtTarget_2(&current.angle.y, dstPos_p, src_pos, desiredYrot, l_HIO.mPrmTbl.mCalcAngleTarget,
                         headOnlyFollow);
}

/* 00001BD0-00001C50       .text chkAttention__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::chkAttention() { /* Nonmatching */
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 00001C50-00001CA8       .text setAttention__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setAttention(bool i_setEyePos) {
    f32 offset = l_HIO.mPrmTbl.mAttPosOffsetY;
    attention_info.position.set(current.pos.x, current.pos.y + offset, current.pos.z);
    if (m77C != 0 || i_setEyePos) {
        eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    }
}

/* 00001CA8-00001D30       .text decideType__11daNpc_Kf1_cFi */
BOOL daNpc_Kf1_c::decideType(int i_type) { /* Nonmatching */
    if (mType > 0) {
        return TRUE;
    }
    mType = 1;
    mType2 = 0;
    strcpy(mArcName, "Kf");
    if (mType != -1 && (s8)mType2 != -1) {
        return TRUE;
    }
    return FALSE;
}

/* 00001D30-00001E04       .text cut_init_ANGRY_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_ANGRY_START(int i_actIdx) { /* Nonmatching */
    cXyz* pos = (cXyz*)dComIfGp_getPEvtManager()->getMySubstanceP(i_actIdx, "Pos", 1);
    if (pos != NULL) {
        current.pos.set(*pos);
        mObjAcch.SetOld();
    }
    mTargetPos.set(0.0f, eyePos.y, 0.0f);
    mLookMode = 2;
    current.angle.y = cLib_targetAngleY(&current.pos, &mTargetPos);
    speedF = 0.0f;
    setAnm_NUM(0, TRUE);
}

/* 00001E04-00001E0C       .text cut_move_ANGRY_START__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_ANGRY_START() {
    return TRUE;
}

/* 00001E0C-00001E5C       .text cut_init_BENSYOU_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU_START(int i_actIdx) { /* Nonmatching */
    cut_init_ANGRY_START(i_actIdx);
    cXyz goal(0.0f, 0.0f, 700.0f);
    dComIfGp_evmng_setGoal(&goal);
}

/* 00001E5C-00001E64       .text cut_move_BENSYOU_START__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_BENSYOU_START() {
    return TRUE;
}

/* 00001E64-00001EB4       .text cut_init_TSUBO_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_CNT(int i_actIdx) { /* Nonmatching */
    mTsuboIdx = mTsuboCnt - chk_tsubo();
    m_jnt.setTrn();
    m_jnt.setBackBone_x(0);
    m_jnt.setBackBone_y(0);
    m_jnt.setHead_x(0);
    m_jnt.setHead_y(0);
    mLookMode = 0;
}

/* 00001EB4-00001EBC       .text cut_move_TSUBO_CNT__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_TSUBO_CNT() {
    return TRUE;
}

/* 00001EBC-00001EE8       .text cut_init_BENSYOU__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU(int i_actIdx) { /* Nonmatching */
    mRupeeCnt = dComIfGp_getItemRupeeCount();
    g_dComIfG_gameInfo.play.mItemRupeeCount -= mTsuboIdx * 10;
}

/* 00001EE8-00001EF0       .text cut_move_BENSYOU__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_BENSYOU() {
    return TRUE;
}

/* 00001EF0-00001FE4       .text cut_init_GET_OUT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_GET_OUT(int i_actIdx) { /* Nonmatching */
    s32* timer = (s32*)dComIfGp_getPEvtManager()->getMySubstanceP(i_actIdx, "Timer", 3);
    mCutTimer = 0;
    if (timer != NULL) {
        mCutTimer = timer[0];
    }
    daPy_getPlayerActorClass()->mDemo.setMoveAngle(0);
    daPy_getPlayerActorClass()->mDemo.setDemoType(daPy_demo_c::TYPE_ORIGINAL_e);
    daPy_getPlayerActorClass()->mDemo.setParam0(0);
    if (mRupeeCnt >= mTsuboIdx * 10) {
        cXyz target(0.0f, 0.0f, 999.0f);
        cLib_targetAngleY(&daPy_getPlayerActorClass()->current.pos, &target);
        daPy_getPlayerActorClass()->mDemo.setDemoMode(daPy_demo_c::DEMO_N_DASH_e);
    } else {
        daPy_getPlayerActorClass()->mDemo.setParam0(1);
        daPy_getPlayerActorClass()->mDemo.setDemoMode(daPy_demo_c::DEMO_LDAM_e);
    }
}

/* 00001FE4-00002044       .text cut_move_GET_OUT__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_GET_OUT() { /* Nonmatching */
    if (!cLib_calcTimer<s16>(&mCutTimer)) {
        dComIfGp_setNextStage("sea", 3, 0xB, -1, 0.0f, 0, 1);
    }
    return FALSE;
}

/* 00002044-0000205C       .text cut_init_DSP_RUPEE_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_DSP_RUPEE_CNT(int i_actIdx) {
    g_dComIfG_gameInfo.play.getEvent()->mHindFlag &= ~0x80;
}

/* 0000205C-00002064       .text cut_move_DSP_RUPEE_CNT__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_DSP_RUPEE_CNT() {
    return TRUE;
}

/* 00002064-000020AC       .text cut_init_PLYER_TRN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_TRN(int i_actIdx) { /* Nonmatching */
    dComIfGp_getPlayer(0)->current.angle.y =
        cLib_targetAngleY(&dComIfGp_getPlayer(0)->current.pos, &current.pos);
}

/* 000020AC-000020B4       .text cut_move_PLYER_TRN__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_PLYER_TRN() {
    return TRUE;
}

/* 000020B4-000020B8       .text cut_init_RUPEE_CNT_END__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_CNT_END(int i_actIdx) {}

/* 000020B8-000020EC       .text cut_move_RUPEE_CNT_END__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_RUPEE_CNT_END() { /* Nonmatching */
    if ((u16)dComIfGs_getRupee() == (u16)g_dComIfG_gameInfo.play.mItemNowRupee) {
        g_dComIfG_gameInfo.play.getEvent()->mHindFlag |= 0x80;
        return TRUE;
    }
    return FALSE;
}

/* 000020EC-00002168       .text cut_init_START_AGE__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_START_AGE(int i_actIdx) {
    mTargetPos.set(0.0f, eyePos.y, 0.0f);
    shape_angle.y = cLib_targetAngleY(&current.pos, &mTargetPos);
    mStartAge = 1;
    mLookMode = 3;
    m79A = shape_angle.y;
    m_jnt.setTrn();
    setAnm_NUM(0, TRUE);
}

/* 00002168-00002178       .text cut_move_START_AGE__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_START_AGE() { /* Nonmatching */
    return !m_jnt.trnChk();
}

/* 00002178-00002284       .text cut_init_PLYER_MOV__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_MOV(int i_actIdx) { /* Nonmatching */
    s16 angle =
        (s16)(cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos) - current.angle.y);
    if (abs(angle) > 0x2000) {
        dComIfGp_evmng_setGoal(&dComIfGp_getPlayer(0)->current.pos);
        return;
    }
    cXyz goal(0.0f, 0.0f, 0.0f);
    s16 dir = angle > 0 ? 0x2800 : -0x2800;
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM((s16)(current.angle.y + dir));
    goal.z = 150.0f;
    mDoMtx_stack_c::multVec(&goal, &goal);
    dComIfGp_evmng_setGoal(&goal);
}

/* 00002284-0000228C       .text cut_move_PLYER_MOV__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_PLYER_MOV() {
    return TRUE;
}

/* 0000228C-000023E8       .text cut_init_RUPEE_SET__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_SET(int i_actIdx) { /* Nonmatching */
    if (mTsuboCnt != 8) {
        return;
    }
    u8 set[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    for (i = 0; i < 3; i++) {
        s32 idx;
        do {
            idx = (s32)(cM_rndF(32.0f) * 0.25f);
        } while (set[idx] != 0);
        fpc_ProcID procId = mTsuboProcId[idx];
        fopAc_ac_c* a_tsubo_actor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &procId);
        JUT_ASSERT(0x5C3, 0 != a_tsubo_actor);
        fopAcM_SetParam(a_tsubo_actor, (fopAcM_GetParam(a_tsubo_actor) & ~0x3F) | 0x4);
        g_dComIfG_gameInfo.play.getEvent()->setPtI(a_tsubo_actor);
        mKutaniProcId[i] = mTsuboProcId[idx];
        set[idx] = 1;
    }
    setAnm_NUM(8, TRUE);
}

/* 000023E8-0000260C       .text cut_move_RUPEE_SET__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_RUPEE_SET() { /* Nonmatching */
    int i;
    if (mAnmResult == 0) {
        if (mpMorf->checkFrame(68.0f)) {
            cXyz pos(0.0f, 40.0f, 40.0f);
            mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
            mDoMtx_stack_c::YrotM(current.angle.y);
            mDoMtx_stack_c::multVec(&pos, &pos);
            create_rupee(pos, 3);
            return FALSE;
        }
        if (68.0f >= mpMorf->getFrame()) {
            for (i = 0; i < 3; i++) {
                int flg;
                fopAc_ac_c* item = searchByID(mItemProcId[i], &flg);
                if (item != NULL && flg == 0) {
                    current.pos.set(item->current.pos);
                }
            }
            m77C = 0;
        }
        return FALSE;
    }
    for (i = 0; i < 3; i++) {
        int flg;
        fopAc_ac_c* item = searchByID(mItemProcId[i], &flg);
        if (item != NULL) {
            fopAcM_delete(item);
        }
    }
    if (i == 3) {
        ready_kutaniCamera(0, TRUE);
        m77C = 1;
        setAnm_NUM(0, TRUE);
        return TRUE;
    }
    return FALSE;
}

/* 0000260C-000026B4       .text cut_init_TSUBO_ATN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_ATN(int i_actIdx) { /* Nonmatching */
    s32* timer = (s32*)dComIfGp_getPEvtManager()->getMySubstanceP(i_actIdx, "Timer", 3);
    s32* count = (s32*)dComIfGp_getPEvtManager()->getMySubstanceP(i_actIdx, "Count", 3);
    mCutTimer = 0;
    if (timer != NULL) {
        mCutTimer = timer[0];
    }
    m78E = 0;
    if (count != NULL) {
        m78E = count[0];
    }
}

/* 000026B4-00002794       .text cut_move_TSUBO_ATN__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_TSUBO_ATN() { /* Nonmatching */
    if (!cLib_calcTimer<s16>(&mCutTimer)) {
        if (m78E >= 0 && m78E <= 3) {
            if (m78E == 0) {
                ready_kutaniCamera(0, TRUE);
            } else {
                ready_kutaniCamera(0, FALSE);
            }
        }
        return TRUE;
    }
    if (mCutTimer == 0x14) {
        JAIZelBasic::getInterface()->seStart(0x6981, &current.pos, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    }
    return FALSE;
}

/* 00002794-0000292C       .text cut_init_TLK_MSG__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TLK_MSG(int i_actIdx) { /* Nonmatching */
    u32* endMsg = (u32*)dComIfGp_getPEvtManager()->getMySubstanceP(0, "MsgNum", 3);
    u32* startMsg = (u32*)dComIfGp_getPEvtManager()->getMySubstanceP(i_actIdx, "EndMsg", 3);
    mAtr = 0xFF;
    mTag = 0xFF;
    m7FE = 0;
    mCurrMsgNo = 0;
    mEndMsgNo = fpcM_ERROR_PROCESS_ID_e;
    if (startMsg != NULL) {
        mEndMsgNo = startMsg[0];
    }
    if (endMsg != NULL) {
        mCurrMsgNo = endMsg[0];
        switch (mCurrMsgNo) {
            case 0x1C2D:
                g_dComIfG_gameInfo.play.mMsgCountNumber = mTsuboIdx * 10;
                break;
            case 0x1C2E:
                mCurrMsgNo = (mRupeeCnt < mTsuboIdx * 10) ? 0x1C2F : 0x1C30;
                break;
            case 0x1C39:
                g_dComIfG_gameInfo.play.getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                break;
        }
    }
    mCurrMsgBsPcId = fpcM_ERROR_PROCESS_ID_e;
}

/* 0000292C-0000298C       .text cut_init_CONTNUE_TLK__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_CONTNUE_TLK(int i_actIdx) { /* Nonmatching */
    u32* startMsg = (u32*)dComIfGp_getPEvtManager()->getMySubstanceP(i_actIdx, "EndMsg", 3);
    mEndMsgNo = fpcM_ERROR_PROCESS_ID_e;
    if (startMsg != NULL) {
        mEndMsgNo = startMsg[0];
    }
}

/* 0000298C-00002A10       .text cut_move_TLK_MSG__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::cut_move_TLK_MSG() {
    u16 msgStatus = talk(0);
    if (msgStatus == 0x12) {
        mAtr = 0xFF;
        mTag = 0xFF;
        m7FE = 0;
        return TRUE;
    }
    if (msgStatus == 0x2 || msgStatus == 0x6) {
        return (mCurrMsgNo == mEndMsgNo) ? TRUE : FALSE;
    }
    return FALSE;
}

/* 00002A10-00002C98       .text privateCut__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::privateCut(int i_actIdx) { /* Nonmatching */
    static const char* a_cut_tbl[] = {
        "ANGRY_START",   "BENSYOU_START", "TSUBO_CNT", "BENSYOU",   "GET_OUT",
        "DSP_RUPEE_CNT", "PLYER_TRN",     "RUPEE_CNT_END", "START_AGE", "PLYER_MOV",
        "RUPEE_SET",     "TSUBO_ATN",     "TLK_MSG",  "CONTNUE_TLK",
    };
    if (i_actIdx == -1) {
        return;
    }
    dEvent_manager_c* evmng = dComIfGp_getPEvtManager();
    mCutIdx = evmng->getMyActIdx(i_actIdx, a_cut_tbl, 0xE, 1, 0);
    if (mCutIdx == -1) {
        evmng->cutEnd(i_actIdx);
        return;
    }
    if (evmng->getIsAddvance(i_actIdx) || mCutIdx <= 0xD) {
        switch (mCutIdx) {
            case 0:
                cut_init_ANGRY_START(i_actIdx);
                break;
            case 1:
                cut_init_BENSYOU_START(i_actIdx);
                break;
            case 2:
                cut_init_TSUBO_CNT(i_actIdx);
                break;
            case 3:
                cut_init_BENSYOU(i_actIdx);
                break;
            case 4:
                cut_init_GET_OUT(i_actIdx);
                break;
            case 5:
                cut_init_DSP_RUPEE_CNT(i_actIdx);
                break;
            case 6:
                cut_init_PLYER_TRN(i_actIdx);
                break;
            case 7:
                cut_init_RUPEE_CNT_END(i_actIdx);
                break;
            case 8:
                cut_init_START_AGE(i_actIdx);
                break;
            case 9:
                cut_init_PLYER_MOV(i_actIdx);
                break;
            case 10:
                cut_init_RUPEE_SET(i_actIdx);
                break;
            case 11:
                cut_init_TSUBO_ATN(i_actIdx);
                break;
            case 12:
                cut_init_TLK_MSG(i_actIdx);
                break;
            case 13:
                cut_init_CONTNUE_TLK(i_actIdx);
                break;
        }
        if (mCutIdx <= 0xD) {
            BOOL ret = TRUE;
            switch (mCutIdx) {
                case 0:
                    ret = cut_move_ANGRY_START();
                    break;
                case 1:
                    ret = cut_move_BENSYOU_START();
                    break;
                case 2:
                    ret = cut_move_TSUBO_CNT();
                    break;
                case 3:
                    ret = cut_move_BENSYOU();
                    break;
                case 4:
                    ret = cut_move_GET_OUT();
                    break;
                case 5:
                    ret = cut_move_DSP_RUPEE_CNT();
                    break;
                case 6:
                    ret = cut_move_PLYER_TRN();
                    break;
                case 7:
                    ret = cut_move_RUPEE_CNT_END();
                    break;
                case 8:
                    ret = cut_move_START_AGE();
                    break;
                case 9:
                    ret = cut_move_PLYER_MOV();
                    break;
                case 10:
                    ret = cut_move_RUPEE_SET();
                    break;
                case 11:
                    ret = cut_move_TSUBO_ATN();
                    break;
                case 12:
                    ret = cut_move_TLK_MSG();
                    break;
                case 13:
                    ret = cut_move_TLK_MSG();
                    break;
            }
            if (ret) {
                evmng->cutEnd(i_actIdx);
            }
        }
    }
}

/* 00002C60-00002C84       .text endEvent__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::endEvent() {
    g_dComIfG_gameInfo.play.getEvent()->mEventFlag |= 0x8;
    mAtr = 0xFF;
    mTag = 0xFF;
}

/* 00002C84-00002CBC       .text isEventEntry__11daNpc_Kf1_cFv */
int daNpc_Kf1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL, 0);
}

/* 00002CBC-00002E14       .text event_proc__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::event_proc(int i_actIdx) {
    if (dComIfGp_evmng_endCheck(mEvtIdx[mCurEvtIdx])) {
        switch (mCurEvtIdx) {
            case 0:
                dComIfGs_onEventBit(0x2780);
                mTsuboCnt = chk_tsubo();
                break;
            case 1: {
                u8 eventReg = dComIfGs_getEventReg(0xBCFF);
                eventReg |= 1;
                dComIfGs_setEventReg(0xBCFF, eventReg);
                mStartAge = 0;
                setStt(1);
                setAnm_NUM(0, TRUE);
                m792 = cLib_getRndValue(0x1E, 0x3C);
                m790 = cLib_getRndValue(0xF, 0x1E);
                mTalkStt = 1;
                /* fall through */
            }
            case 2:
                break;
        }
        m792 = cLib_getRndValue(0x1E, 0x3C);
        endEvent();
    } else {
        if (!mEventCut.cutProc()) {
            privateCut(i_actIdx);
        }
    }
}

/* 00002E14-00002F88       .text set_action__11daNpc_Kf1_cFM11daNpc_Kf1_cFPCvPvPv_iPv */
BOOL daNpc_Kf1_c::set_action(ProcFunc i_action, void* i_param_2) {
    if (mProcFunc != i_action) {
        if (mProcFunc) {
            mPhase = 9;
            (this->*mProcFunc)(i_param_2);
        }
        mProcFunc = i_action;
        mPhase = 0;
        (this->*mProcFunc)(i_param_2);
    }
    return TRUE;
}

/* 00002F88-00003030       .text setStt__11daNpc_Kf1_cFSc */
void daNpc_Kf1_c::setStt(s8 i_status) {
    u8 prev_status = mStatus;
    mStatus = i_status;
    switch (mStatus) {
        case 0:
            break;
        case 1:
            mOrder = 0;
            m794 = cLib_getRndValue(0x3C, 0x5A);
            speedF = 0.0f;
            break;
        case 2:
            mOrder = 0;
            mAtr = 0xFF;
            mTag = 0xFF;
            m7FE = 0;
            mPrevStatus = prev_status;
            break;
        case 3:
            mOrder = 0;
            m794 = cLib_getRndValue(0x5A, 0x5A);
            break;
    }
    setAnm();
}

/* 00003030-000030E8       .text set_pthPoint__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::set_pthPoint(u8 i_idx) { /* Nonmatching */
    if (mPath.isPath()) {
        mPath.setIdx(i_idx);
        cXyz pos = mPath.getPoint(mPath.getIdx());
        current.pos.set(pos);
        if (mPath.nextIdx()) {
            cXyz nextPos = mPath.getPoint(mPath.getIdx());
            current.angle.y = cLib_targetAngleY(&current.pos, &nextPos);
        }
    }
}

/* 000030E8-0000317C       .text chk_tsubo__11daNpc_Kf1_cFv */
s16 daNpc_Kf1_c::chk_tsubo() {
    s16 ret = 0;
    int i;
    for (i = 0; i < 8; i++) {
        int flg;
        fopAc_ac_c* tsubo = searchByID(mTsuboProcId[i], &flg);
        if (flg == 0) {
            ret += 1;
        }
    }
    return ret;
}

/* 0000317C-00003278       .text orderTsuboEvent__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::orderTsuboEvent() {
    if (mTalkOrder != 0) {
        return FALSE;
    }
    if (!dComIfGs_isEventBit(0x2780)) {
        if (mTsuboCnt > chk_tsubo()) {
            mOrder = 3;
            return TRUE;
        }
    } else if (m79F != 0xFF && dComIfGs_isSwitch(m79F, current.roomNo)) {
        if (mTsuboCnt > chk_tsubo()) {
            mOrder = 5;
            return TRUE;
        }
    }
    return FALSE;
}

/* 00003278-00003374       .text wait_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::wait_1() {
    if (mTalkOrder != 0) {
        u8 talk = chk_talk();
        if (talk) {
            setStt(2);
            mLookMode = 1;
            mLookFlag = 0;
            m_jnt.setTrn();
        }
        return TRUE;
    }
    if (mOrder < 3) {
        mOrder = 2;
    }
    mLookFlag = 1;
    if (mAnmNo == 9) {
        m792 = 0;
    }
    if (cLib_calcTimer<s16>(&m792) == 0) {
        if (mAnmNo != 9) {
            setAnm_NUM(9, TRUE);
            m794 = 0;
        }
        if (cLib_calcTimer<s16>(&m794) == 0) {
            setStt(3);
            return TRUE;
        }
    }
    mLookMode = 0;
    return TRUE;
}

/* 00003374-000035B0       .text walk_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::walk_1() { /* Nonmatching */
    f32 target;
    if (mPath.getPath() == NULL) {
        return TRUE;
    }
    if (mPath.getDir()) {
        cXyz pos = current.pos;
        if (mPath.chkPointPass(pos, mPath.getIdx() == 0)) {
            mPath.nextIdxAuto();
        }
    } else {
        return TRUE;
    }
    cXyz nextPos = mPath.getPoint(mPath.getIdx());
    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &nextPos),
                       l_HIO.mPrmTbl.mWalkStep, l_HIO.mPrmTbl.mWalkMaxStep, 0x80);
    target = l_HIO.mPrmTbl.mWalkMaxSpeed;
    if (cLib_calcTimer<s16>(&m794) || mTalkOrder != 0) {
        target = 0.0f;
    }
    cLib_chaseF(&speedF, target, l_HIO.mPrmTbl.mChaseSpeed);
    f32 playSpeed = speedF * l_HIO.mPrmTbl.mWalkSpeed;
    if (playSpeed < 0.5f) {
        playSpeed = 0.5f;
    }
    mpMorf->setPlaySpeed(playSpeed);
    if ((s32)target == 0 && (s32)speedF == 0) {
        if (mTalkOrder != 0) {
            if (chk_talk()) {
                setStt(1);
                setAnm_NUM(9, TRUE);
                mLookMode = 1;
                mLookFlag = 0;
                m_jnt.setTrn();
            }
            return TRUE;
        }
        setStt(1);
        setAnm_NUM(9, TRUE);
        return TRUE;
    }
    if (mOrder < 3) {
        mOrder = 2;
    }
    mLookMode = 0;
    mLookFlag = 1;
    return TRUE;
}

/* 000035B0-00003670       .text talk_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::talk_1() { /* Nonmatching */
    bool ret = false;
    talk(1);
    if (mpCurrMsg == NULL) {
        return TRUE;
    }
    switch (mpCurrMsg->mStatus) {
        case 2:
        case 6:
            break;
        case 0x13:
            if ((s32)mCurrMsgNo == 0x1C2B) {
                ret = true;
            }
            m79E = 0xFF;
            mTalkOrder = 0;
            setStt(mPrevStatus);
            setAnm_NUM(0, TRUE);
            m792 = cLib_getRndValue(0x1E, 0x3C);
            m790 = cLib_getRndValue(0xF, 0x1E);
            if (ret) {
                mOrder = 4;
            }
            endEvent();
            break;
    }
    return mAnmNo == 4;
}

/* 00003670-00003754       .text wait_action1__11daNpc_Kf1_cFPv */
BOOL daNpc_Kf1_c::wait_action1(void*) {
    switch (mPhase) {
        case 0:
            setStt(3);
            mPhase++;
            break;
        case 1:
        case 2:
        case 3:
            mAttention = chkAttention();
            switch (mStatus) {
                case 1:
                    m77C = wait_1();
                    break;
                case 2:
                    m77C = talk_1();
                    break;
                case 3:
                    m77C = walk_1();
                    break;
            }
            if (mPhase > 1) {
                orderTsuboEvent();
            }
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00003754-00003890       .text demo__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::demo() { /* Nonmatching */
    if (demoActorID == 0) {
        if (mDemoFlag != 0) {
            mDemoFlag = 0;
        }
    } else {
        if (mDemoFlag == 0) {
            mDemoFlag = 1;
            mStartAge = 0;
            m_jnt.setTrn();
            m_jnt.setHead_x(0);
            m_jnt.setHead_y(0);
            m_jnt.setBackBone_x(0);
            m_jnt.setBackBone_y(0);
        }
        dDemo_object_c* demoObj = g_dComIfG_gameInfo.play.getDemo()->getObject();
        dDemo_actor_c* demoActor = demoObj->getActor(demoActorID);
        if (mBtpAnm.getBtpAnm() != NULL) {
            mBtpFrame++;
            if (mBtpFrame >= mBtpAnm.getBtpAnm()->getAttribute()) {
                mBtpFrame = mBtpAnm.getBtpAnm()->getAttribute();
            }
        }
        J3DAnmTexPattern* btp = demoActor->getP_BtpData(mArcName);
        if (btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, 1, 0, 1.0f, 0, -1, TRUE, FALSE);
            mBtpNo = 2;
            mBtpFrame = 0;
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, mArcName, 0, NULL, 0, 0);
    }
    return mDemoFlag;
}

/* 00003890-00003920       .text shadowDraw__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::shadowDraw() { /* Nonmatching */
    cXyz pos;
    pos.x = current.pos.x;
    pos.y = current.pos.y + 800.0f;
    pos.z = current.pos.z;
    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 30.0f, 40.0f,
                                   current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr,
                                   0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
}

/* 00003920-000039C8       .text _draw__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_draw() { /* Nonmatching */
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    if (m7A7 != 0 || m7A9 != 0) {
        return TRUE;
    }
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(modelData, mBtpFrame);
    mpMorf->entryDL();
    modelData->removeTexNoAnimator(mBtpAnm.getBtpAnm());
    if (mpItemModel != NULL) {
        g_env_light.setLightTevColorType(mpItemModel, &tevStr);
        mDoExt_modelEntryDL(mpItemModel);
    }
    shadowDraw();
    dSnap_RegistFig(0x59, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 000039C8-00003C20       .text _execute__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_execute() { /* Nonmatching */
    if (mInitFlag == 0) {
        mHomePos.set(current.pos);
        mHomeAngle.x = current.angle.x;
        mHomeAngle.y = current.angle.y;
        mHomeAngle.z = current.angle.z;
        mInitFlag = 1;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY,
                   l_HIO.mPrmTbl.mMinBackboneX, l_HIO.mPrmTbl.mMinBackboneY,
                   l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY, l_HIO.mPrmTbl.mMinHeadX,
                   l_HIO.mPrmTbl.mMinHeadY, l_HIO.mPrmTbl.mMaxTurnStep);
    if (m7A7 != 0 && demoActorID == 0) {
        return TRUE;
    }
    srch_Tsubo();
    checkOrder();
    if (!demo()) {
        int staffId = -1;
        if (g_dComIfG_gameInfo.play.getEvent()->mMode != 0 &&
            eventInfo.mCommand != dEvtCmd_INTALK_e) {
            staffId = isEventEntry();
        }
        if (staffId >= 0 || m7A5 != 0) {
            event_proc(staffId);
        } else {
            (this->*mProcFunc)(NULL);
        }
    } else {
        m7A7 = 0;
    }
    lookBack();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mGroundChk = mObjAcch.ChkGroundHit();
    mWallChk = mObjAcch.ChkWaterIn();
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    play_animation();
    eventOrder();
    m722.x = current.angle.x;
    m722.y = current.angle.y;
    m722.z = current.angle.z;
    if (mStartAge == 0) {
        current.angle.x = m722.x;
        current.angle.y = m722.y;
        current.angle.z = m722.z;
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(FALSE);
    if (mDemoFlag == 0) {
        setCollision(90.0f, 200.0f);
    }
    return TRUE;
}

/* 00003C20-00003C80       .text _delete__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_delete() {
    dComIfG_resDelete(&mPhs, mArcName);
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00003C80-00003EEC       .text _create__11daNpc_Kf1_cFv */
cPhs_State daNpc_Kf1_c::_create() { /* Nonmatching */
    static int a_siz_tbl[] = {0x0, 0x0};
    fopAcM_ct_Retail(this, daNpc_Kf1_c);
    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, mArcName);
    mPhaseFlag = phase_state == cPhs_COMPLEATE_e;
    if (!mPhaseFlag) {
        return phase_state;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[mType])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -90.0f, -20.0f, -80.0f, 90.0f, 200.0f, 80.0f);
    if (createInit()) {
        return phase_state;
    }
    return cPhs_ERROR_e;
}

/* 00004130-0000442C       .text bodyCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::bodyCreateHeap() { /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName, 1);
    JUT_ASSERT(0x97F, a_mdl_dat != 0);
    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, 0, 1.0f, -1, 1, 0, NULL,
                                0x80000, 0x11020022);
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    if (!init_texPttrnAnm(0, FALSE)) {
        mpMorf = NULL;
        return FALSE;
    }
    mHeadJntNo = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x993, mHeadJntNo >= 0);
    mBackboneJntNo = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x995, mBackboneJntNo >= 0);
    mNeckJntNo = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(0x997, mNeckJntNo >= 0);
    J3DJoint* joint = mpMorf->getModel()->getModelData()->getJointNodePointer(mHeadJntNo);
    joint->setCallBack(nodeCB_Head);
    joint = mpMorf->getModel()->getModelData()->getJointNodePointer(mBackboneJntNo);
    joint->setCallBack(nodeCB_BackBone);
    joint = mpMorf->getModel()->getModelData()->getJointNodePointer(mNeckJntNo);
    joint->setCallBack(nodeCB_Neck);
    mpMorf->getModel()->setUserArea((u32)this);
    return TRUE;
}

/* 0000442C-000044EC       .text itemCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::itemCreateHeap() { /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName, 0);
    JUT_ASSERT(0x9AC, a_mdl_dat != 0);
    mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    return mpItemModel != NULL;
}

/* 000044EC-00004590       .text CreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::CreateHeap() { /* Nonmatching */
    if (!bodyCreateHeap()) {
        return FALSE;
    }
    if (!itemCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }
    mAcchCir.SetWall(30.0f, 90.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                 fopAcM_GetSpeed_p(this), NULL, NULL);
    return TRUE;
}

/* 00004590-000045B0       .text daNpc_Kf1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kf1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_create();
}

/* 000045B0-000045D0       .text daNpc_Kf1_Delete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Delete(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_delete();
}

/* 000045D0-000045F0       .text daNpc_Kf1_Execute__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Execute(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_execute();
}

/* 000045F0-00004610       .text daNpc_Kf1_Draw__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Draw(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_draw();
}

/* 00004610-00004618       .text daNpc_Kf1_IsDelete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_IsDelete(daNpc_Kf1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kf1_Method = {
    (process_method_func)daNpc_Kf1_Create,
    (process_method_func)daNpc_Kf1_Delete,
    (process_method_func)daNpc_Kf1_Execute,
    (process_method_func)daNpc_Kf1_IsDelete,
    (process_method_func)daNpc_Kf1_Draw,
};

actor_process_profile_definition g_profile_NPC_KF1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KF1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kf1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KF1_e,
    /* Actor SubMtd */ &l_daNpc_Kf1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
