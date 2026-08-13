/**
 * d_a_npc_aj1.cpp
 * NPC - Sturgeon
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_aj1.h"
#include "d/actor/d_a_player.h"
#include "d/d_attention.h"
#include "d/d_com_inf_game.h"
#include "d/d_demo.h"
#include "d/d_particle.h"
#include "d/d_snap.h"
#include "d/d_s_play.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Aj.h"

class daNpc_Aj1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x18 */ u8 m24;
        /* 0x1C */ f32 mAreaRadius;
        /* 0x20 */ s16 mAreaAngle;
        /* 0x24 */ f32 mCallRadius;
        /* 0x28 */ s16 mCallAngle;
        /* 0x2A */ s16 mSppriseTimer;
        /* 0x2C */ s16 mLokTimer;
    };  // Size: 0x30

    daNpc_Aj1_HIO_c();
    virtual ~daNpc_Aj1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

/* 000000EC-00000150       .text __ct__15daNpc_Aj1_HIO_cFv */
        /* Nonmatching */
daNpc_Aj1_HIO_c::daNpc_Aj1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x1F40,
        /* mMaxHeadY         */ 0x2000,
        /* mMinHeadX         */ 0xCD38,
        /* mMinHeadY         */ 0x01F4,
        /* mMaxBackboneX     */ 0x1C70,
        /* mMaxBackboneY     */ 0x0000,
        /* mMinBackboneX     */ 0xFF6A,
        /* mMinBackboneY     */ 0xFA24,
        /* mMaxTurnStep      */ 0x0400,
        /* mCalcAngleTarget  */ 0x0400,
        /* mAttPosOffsetY    */ 150.0f,
        /* m24               */ 0x00,
        /* mAreaRadius       */ 1500.0f,
        /* mAreaAngle        */ 0x5208,
        /* mCallRadius       */ 550.0f,
        /* mCallAngle        */ 0x61A8,
        /* mSppriseTimer     */ 0x001E,
        /* mLokTimer         */ 0x0014,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static daNpc_Aj1_HIO_c l_HIO;

static char* l_evn_tbl[] = {
    "angry",
};

static int a_res_id_tbl[9] = {
    dRes_ID_AJ_BCK_WAIT01_e, dRes_ID_AJ_BCK_WAIT02_e, dRes_ID_AJ_BCK_ANGRY_e,
    dRes_ID_AJ_BCK_JAMP_e, dRes_ID_AJ_BCK_SHOCK_e, dRes_ID_AJ_BCK_LOOK_e,
    dRes_ID_AJ_BCK_TIRE_e, dRes_ID_AJ_BCK_CALL_e, dRes_ID_AJ_BCK_NOBI_e,
};

static int a_res_id_tbl2[1] = {
    dRes_ID_AJ_BTP_MABA_e,
};

static daNpc_Aj1_c::anm_prm_c a_anm_prm_tbl[] = {
    { 0, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 1, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 2, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 3, 0, 0, 0, 8.0f, 1.0f, 0 },
    { 4, 0, 0, 0, 0.0f, 1.0f, 0 },
    { 5, 0, 0, 0, 5.0f, 1.0f, 0 },
    { 6, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 7, 0, 0, 0, 8.0f, 1.0f, 2 },
    { 8, 0, 0, 0, 8.0f, 1.0f, 0 },
};

static daNpc_Aj1_c::anm_prm_c a_anm_prm_tbl2[] = {
    { -1, -1, 0, 0, 0.0f, 0.0f, -1 },
    { 0, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 7, 0, 0, 0, 8.0f, 1.0f, 2 },
    { -1, -1, 0, 0, 0.0f, 0.0f, -1 },
    { 0, 0, 0, 0, 8.0f, 1.0f, 2 },
};

static daNpc_Aj1_c::anm_prm_c a_anm_prm_tbl3[] = {
    { 0, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 1, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 0, 0, 0, 0, 8.0f, 1.0f, 2 },
    { 2, 0, 0, 0, 0.0f, 1.0f, 2 },
    { 3, 0, 0, 0, 8.0f, 1.0f, 0 },
    { 1, 0, 0, 0, 8.0f, 1.0f, 2 },
    { 4, 0, 0, 0, 0.0f, 1.0f, 0 },
    { 5, 0, 0, 0, 5.0f, 1.0f, 0 },
    { 6, 0, 0, 0, 0.0f, 1.0f, 2 },
};

static char* a_cut_tbl[] = {
    "AJ1_TLK",
    "INI_ANGRY",
    "VIVRATE",
    "JMP",
    "SPPRISE",
    "LOK",
    "DAN",
    "INVITE",
};

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_jntNo) {
    if (i_jntNo == 0) {
        daNpc_Aj1_c* actor = (daNpc_Aj1_c*)j3dSys.getModel()->getUserArea();
        if (actor != NULL) {
            actor->_nodeCB_Head(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-0000030C       .text _nodeCB_Head__11daNpc_Aj1_cFP7J3DNodeP8J3DModel */
        /* Nonmatching */
void daNpc_Aj1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(24.0f, -16.0f, 0.0f);
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jntNo));
    m72C.set(mDoMtx_stack_c::get()[0][3], mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
    mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mHeadPos);
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 00000348-00000394       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_jntNo) {
    if (i_jntNo == 0) {
        daNpc_Aj1_c* actor = (daNpc_Aj1_c*)j3dSys.getModel()->getUserArea();
        if (actor != NULL) {
            actor->_nodeCB_BackBone(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000394-0000042C       .text _nodeCB_BackBone__11daNpc_Aj1_cFP7J3DNodeP8J3DModel */
void daNpc_Aj1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    s32 jntNo = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jntNo));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
}

/* 0000042C-0000044C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Aj1_c*>(i_this)->CreateHeap();
}

/* 0000044C-0000046C       .text daNpc_Aj1_XyCheck_CB__FPvi */
static void daNpc_Aj1_XyCheck_CB(void* i_this, int i_itemBtn) {
    static_cast<daNpc_Aj1_c*>(i_this)->_XyCheckCB(i_itemBtn);
}

/* 0000046C-0000048C       .text _XyCheckCB__11daNpc_Aj1_cFi */
u8 daNpc_Aj1_c::_XyCheckCB(int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == 0x48;
}

/* 0000048C-00000574       .text init_AJ1_0__11daNpc_Aj1_cFv */
        /* Nonmatching */
u8 daNpc_Aj1_c::init_AJ1_0() {
    if (dComIfGs_isEventBit(0xE20) == 0 && dComIfGs_isEventBit(0x502) == 0) {
        max_health = 0x1A;
        set_action(&daNpc_Aj1_c::wait_action1, NULL);
        return 1;
    }
    u8 temp = m75B;
    if (temp != 0xFF && dComIfGs_isSwitch(temp, current.roomNo) == 0) {
        dComIfGs_onSwitch(m75B, current.roomNo);
    }
    return 0;
}

/* 00000574-00000624       .text init_AJ1_1__11daNpc_Aj1_cFv */
        /* Nonmatching */
u8 daNpc_Aj1_c::init_AJ1_1() {
    if (dComIfGs_isEventBit(0x520) == 0) {
        dComIfGs_onEventBit(0x502);
        set_action(&daNpc_Aj1_c::wait_action2, NULL);
        actor_status &= ~0x80;
        actor_status |= 0x4000;
        return 1;
    }
    return 0;
}

/* 00000624-000006B0       .text init_AJ1_2__11daNpc_Aj1_cFv */
        /* Nonmatching */
u8 daNpc_Aj1_c::init_AJ1_2() {
    if (dComIfGs_isEventBit(0x520) != 0) {
        eventInfo.setXyCheckCB((dEvt_info_c::CallbackFunc)daNpc_Aj1_XyCheck_CB);
        set_action(&daNpc_Aj1_c::wait_action2, NULL);
        return 1;
    }
    return 0;
}

/* 000006B0-00000868       .text createInit__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::createInit() {
    m75B = (fopAcM_GetParam(this) >> 8) & 0xFF;
    mEventIdTable[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0], 0xFF);
    mEventCut.setActorInfo2("Aj1", this);
    attention_info.flags = 0xA;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAD;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAD;
    mAnmNum = 9;
    u8 init_ret;
    switch (mSpecificType) {
        case 0:
            init_ret = init_AJ1_0();
            break;
        case 1:
            init_ret = init_AJ1_1();
            break;
        case 2:
            init_ret = init_AJ1_2();
            break;
        default:
            init_ret = 0;
            break;
    }
    if (init_ret == 0) {
        return 0;
    }
    m70E.x = current.angle.x;
    m70E.y = current.angle.y;
    m70E.z = current.angle.z;
    shape_angle.x = m70E.x;
    shape_angle.y = m70E.y;
    shape_angle.z = m70E.z;
    gravity = -4.5f;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    play_animation();
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(TRUE);
    return 1;
}

/* 00000868-00000910       .text play_animation__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::play_animation() {
    u32 mtrlSnd = 0;
    play_texPttrnAnm();
    if (mObjAcch.m_flags & 0x20) {
        mtrlSnd = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    mbMorfAnimStopped = mpMorf->play(&eyePos, mtrlSnd, dComIfGp_getReverb(current.roomNo));
    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = 1;
    }
    mPrevMorfFrame = mpMorf->getFrame();
}

/* 00000910-000009C0       .text ctrl_WAITanm__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::ctrl_WAITanm() {
    switch (mAnmNum) {
        case 0:
            if (cLib_calcTimer(&mWaitTimer) == 0 && mbMorfAnimStopped && chk_parts_notMov()) {
                setAnm_NUM(1, 1);
            }
            break;
        case 1:
            if (mbMorfAnimStopped) {
                setAnm_NUM(0, 1);
                mWaitTimer = cLib_getRndValue(0x5A, 0xB4);
            }
            break;
    }
}

/* 000009C0-00000A3C       .text ctrl_TIREanm__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::ctrl_TIREanm() {
    if (mAnmNum == 6) {
        if (mbMorfAnimStopped && cLib_calcTimer(&m75C) == 0) {
            setAnm_NUM(0, 1);
            mpMorf->setMorf(20.0f);
        }
    } else {
        m75C = 0;
    }
}

/* 00000A3C-00000B30       .text setMtx__11daNpc_Aj1_cFb */
        /* Nonmatching */
void daNpc_Aj1_c::setMtx(bool i_setMtx) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(m70E.x, m70E.y, m70E.z);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if (mpItemModel != NULL) {
        PSMTXCopy(mpMorf->getModel()->getAnmMtx(m_hnd_L_jnt_num), mpItemModel->getBaseTRMtx());
        mpItemModel->calc();
    }
    setAttention(i_setMtx);
}

/* 00000B30-00000B44       .text bckResID__11daNpc_Aj1_cFi */
        /* Nonmatching */
int daNpc_Aj1_c::bckResID(int i_resNo) {
    return a_res_id_tbl[i_resNo];
}

/* 00000B44-00000B58       .text btpResID__11daNpc_Aj1_cFi */
        /* Nonmatching */
int daNpc_Aj1_c::btpResID(int i_resNo) {
    return a_res_id_tbl2[i_resNo];
}

/* 00000B58-00000C64       .text init_texPttrnAnm__11daNpc_Aj1_cFScb */
        /* Nonmatching */
s32 daNpc_Aj1_c::init_texPttrnAnm(s8 i_btpNo, bool i_entry) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    if (i_btpNo < 0) {
        return 0;
    }
    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Aj", btpResID(i_btpNo));
    JUT_ASSERT(VERSION_SELECT(531, 530, 531, 531), btp != NULL);
    mBtpNum = i_btpNo;
    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return mBtpAnm.init(modelData, btp, TRUE, 0, 1.0f, 0, -1, i_entry, FALSE);
}

/* 00000C64-00000CF4       .text play_texPttrnAnm__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::play_texPttrnAnm() {
    if (mBtpNum != 0 || cLib_calcTimer(&mBlinkTimer) == 0) {
        mBlinkFrame++;
        s16 frameMax = mBtpAnm.getBtpAnm()->getFrameMax();
        if (mBlinkFrame >= frameMax) {
            if (mBtpNum != 0) {
                mBlinkFrame = frameMax;
                return;
            }
            mBlinkTimer = cLib_getRndValue(0x3C, 0x5A);
            mBlinkFrame = 0;
        }
    }
}

/* 00000CF4-00000DFC       .text setAnm_anm__11daNpc_Aj1_cFPQ211daNpc_Aj1_c9anm_prm_c */
        /* Nonmatching */
void daNpc_Aj1_c::setAnm_anm(daNpc_Aj1_c::anm_prm_c* i_prm) {
    if (i_prm->mAnmNum < 0 || mAnmNum == i_prm->mAnmNum) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf, i_prm->mLoopMode, i_prm->mMorf, i_prm->mSpeed,
                     bckResID(i_prm->mAnmNum), -1, "Aj");
    mAnmNum = i_prm->mAnmNum;
    mbMorfAnimStopped = 0;
    m759 = 0;
    mPrevMorfFrame = 0.0f;
    switch (mAnmNum) {
        case 2:
            set_pa_pun();
            set_pa_aka();
            set_pa_don();
            break;
        default:
            if (mAkaEmitter != NULL) {
                mAkaEmitter->setStatus(1);
                m7B4 = 1;
            }
            del_pa(&mPunEmitter);
            del_pa(&mDonEmitter);
            break;
    }
}

/* 00000DFC-00000E6C       .text setAnm_NUM__11daNpc_Aj1_cFii */
        /* Nonmatching */
void daNpc_Aj1_c::setAnm_NUM(int i_anmNum, int i_btpEntry) {
    if (i_btpEntry != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].mBtpNum, 1);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 00000E6C-00000ED8       .text setAnm__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::setAnm() {
    init_texPttrnAnm(a_anm_prm_tbl2[mStatus].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl2[mStatus]);
}

/* 00000ED8-00000EF0       .text chngAnmTag__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::chngAnmTag() {
}

/* 00000EF0-00000F08       .text ctrlAnmTag__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::ctrlAnmTag() {
}

/* 00000F08-00000F44       .text chngAnmAtr__11daNpc_Aj1_cFUc */
        /* Nonmatching */
void daNpc_Aj1_c::chngAnmAtr(u8 i_atr) {
    if (i_atr != mAnmAtr) {
        if (i_atr > 9) {
            return;
        }
        mAnmAtr = i_atr;
        setAnm_ATR();
        if (mAnmAtr == 8) {
            m75C = 3;
        }
    }
}

/* 00000F44-00000F98       .text ctrlAnmAtr__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::ctrlAnmAtr() {
    switch (mAnmAtr) {
        case 2:
            ctrl_WAITanm();
            break;
        case 5:
            if (mbMorfAnimStopped) {
                mAnmAtr = 0;
                setAnm_NUM(0, 1);
            }
            break;
    }
    ctrl_TIREanm();
}

/* 00000F98-00001008       .text setAnm_ATR__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::setAnm_ATR() {
    init_texPttrnAnm(a_anm_prm_tbl3[mAnmAtr].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl3[mAnmAtr]);
}

/* 00001024-000010B8       .text anmAtr__11daNpc_Aj1_cFUs */
        /* Nonmatching */
void daNpc_Aj1_c::anmAtr(u16 i_msgStatus) {
    switch (i_msgStatus) {
        case 6:
            if (m7C1 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            }
            m7C1++;
            u8 tagInfo = dComIfGp_getMesgAnimeTagInfo();
            if (tagInfo != 0xFF && tagInfo != mMesgAnimeTagInfo) {
                dComIfGp_clearMesgAnimeTagInfo();
                mMesgAnimeTagInfo = tagInfo;
                chngAnmTag();
            }
            break;
        case 0xE:
            m7C1 = 0;
            ctrlAnmAtr();
            ctrlAnmTag();
            break;
    }
}

/* 000010E0-000012AC       .text next_msgStatus__11daNpc_Aj1_cFPUl */
        /* Nonmatching */
u16 daNpc_Aj1_c::next_msgStatus(u32* i_pMsgNo) {
    u16 status = 0xF;
    u32 msgNo = *i_pMsgNo;
    switch (msgNo) {
        case 0x9C6:
            *i_pMsgNo = 0x9C7;
            break;
        case 0x9C7:
            *i_pMsgNo = 0x9C8;
            break;
        case 0x9C9:
            *i_pMsgNo = 0x9CA;
            break;
        case 0x9C8:
        case 0x9CA:
            if (dComIfGs_isEventBit(0x1) && !dComIfGs_isEventBit(0x3704)) {
                *i_pMsgNo = 0x9DA;
                break;
            }
            status = 0x10;
            break;
        case 0x9DB:
            if (!dComIfGs_isEventBit(0x504)) {
                if (dComIfGs_isEventBit(0x2A80)) {
                    *i_pMsgNo = 0x9DC;
                } else {
                    *i_pMsgNo = 0x9CB;
                }
            } else {
                *i_pMsgNo = 0x9CF;
            }
            break;
        case 0x9CB:
        case 0x9DC:
            *i_pMsgNo = 0x9CC;
            break;
        case 0x9CD:
            *i_pMsgNo = 0x9CE;
            break;
        case 0x9CF:
            if (dComIfGs_isEventBit(0x1) && !dComIfGs_isEventBit(0x3704)) {
                *i_pMsgNo = 0x9DD;
                break;
            }
            status = 0x10;
            break;
        case 0x9D0:
            if (!dComIfGs_isEventBit(0x2A20)) {
                *i_pMsgNo = 0x9D1;
            } else {
                if (!dKy_daynight_check()) {
                    *i_pMsgNo = 0x9D2;
                } else {
                    *i_pMsgNo = 0x9D3;
                }
            }
            break;
        default:
            status = 0x10;
            break;
    }
    return status;
}

/* 000012B4-000012F0       .text getMsg_AJ1_0__11daNpc_Aj1_cFv */
u32 daNpc_Aj1_c::getMsg_AJ1_0() {
    if (dComIfGs_isEventBit(0x510)) {
        return 0x9C9;
    }
    return 0x9C6;
}

/* 000012F4-00001394       .text getMsg_AJ1_1__11daNpc_Aj1_cFv */
u32 daNpc_Aj1_c::getMsg_AJ1_1() {
    if (dComIfGs_isEventBit(0xE20) && !dComIfGs_isEventBit(0x3702)) {
        dComIfGs_onEventBit(0x3702);
        return 0x9DB;
    }
    if (dComIfGs_isEventBit(0x504)) {
        return 0x9CF;
    }
    if (dComIfGs_isEventBit(0x2A80)) {
        return 0x9DC;
    }
    return 0x9CB;
}

/* 00001398-0000145C       .text getMsg_AJ1_2__11daNpc_Aj1_cFv */
        /* Nonmatching */
u32 daNpc_Aj1_c::getMsg_AJ1_2() {
    if (mItemNo == 0x48) {
        if (!dComIfGs_isEventBit(0x3701)) {
            return 0x9D7;
        }
        if (dComIfGs_isEventBit(0xB20)) {
            return 0x9D9;
        }
        return 0x9DA;
    }
    if (!dComIfGs_isEventBit(0x3708)) {
        return 0x9D0;
    }
    if (!dComIfGs_isEventBit(0x2A20)) {
        return 0x9D4;
    }
    if (dKy_daynight_check()) {
        return 0x9D6;
    }
    return 0x9D7;
}

/* 00001460-0000146C       .text getMsg__11daNpc_Aj1_cFv */
u32 daNpc_Aj1_c::getMsg() {
    u32 result = 0;
    switch (mSpecificType) {
        case 0:
            result = getMsg_AJ1_0();
            break;
        case 1:
            result = getMsg_AJ1_1();
            break;
        case 2:
            result = getMsg_AJ1_2();
            break;
    }
    return result;
}

/* 0000146C-000014E8       .text eventOrder__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::eventOrder() {
    if (m812 == 1 || m812 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mSpecificType == 2) {
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        }
        if (m812 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (m812 >= 3) {
        mEventIdx = m812 - 3;
        fopAcM_orderOtherEventId(this, mEventIdTable[mEventIdx], 0xFF, 0xFFFF, 0, 1);
    }
}

/* 00001574-00001624       .text checkOrder__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::checkOrder() {
    if (eventInfo.getCommand() == dEvtCmd_INDEMO_e) {
        if (dComIfGp_evmng_startCheck(mEventIdTable[mEventIdx])) {
            if (mEventIdx == 0) {
                actor_status &= ~0x4000;
            }
            m812 = 0;
        }
    } else if (eventInfo.getCommand() == dEvtCmd_INTALK_e) {
        if (m812 == 1 || m812 == 2) {
            m812 = 0;
            m769 = 1;
        }
    }
}

/* 00001628-000016B8       .text chk_talk__11daNpc_Aj1_cFv */
u8 daNpc_Aj1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            return 1;
        }
        return 0;
    }
    mItemNo = 0xFF;
    return 1;
}

/* 000016B8-000016D8       .text chk_parts_notMov__11daNpc_Aj1_cFv */
s32 daNpc_Aj1_c::chk_parts_notMov() {
    s32 result = 0;
    if (mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() &&
        mActorAngleY == current.angle.y) {
        result = 1;
    }
    return result;
}

/* 000016D8-0000184C       .text lookBack__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::lookBack() {
    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    cXyz temp_pos(current.pos.x, current.pos.y, current.pos.z);
    temp_pos.y = eyePos.y;
    cXyz look_pos(0.0f, 0.0f, 0.0f);
    cXyz* pLookPos = NULL;
    s16 angle = current.angle.y;
    u8 headOnlyFollow = mHeadOnlyFollow;
    switch (mLookBackState) {
        case 1:
            dNpc_playerEyePos(-20.0f);
            look_pos = cXyz(temp_pos.x, temp_pos.y, temp_pos.z);
            pLookPos = &look_pos;
            break;
        case 2:
            look_pos = m720;
            pLookPos = &look_pos;
            break;
        case 3:
            angle = mTargetYRot;
            break;
    }
    cLib_addCalcAngleS2(&mLookAtMaxVel, l_HIO.mPrmTbl.mCalcAngleTarget, 4, 0x800);
    if (m_jnt.trnChk() == 0) {
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, pLookPos, temp_pos, angle, mLookAtMaxVel, headOnlyFollow);
}

/* 0000184C-0000189C       .text chkAttention__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::chkAttention() {
    dAttention_c* attn = &dComIfGp_getAttention();
    if (attn->LockonTruth()) {
        return this == attn->LockonTarget(0);
    }
    return this == attn->ActionTarget(0);
}

/* 0000189C-000018DC       .text setAttention__11daNpc_Aj1_cFb */
        /* Nonmatching */
void daNpc_Aj1_c::setAttention(bool i_flag) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY, current.pos.z);
    if (mActionResult != 0 || i_flag) {
        eyePos = mHeadPos;
    }
}

/* 000018DC-00001930       .text decideType__11daNpc_Aj1_cFi */
        /* Nonmatching */
s32 daNpc_Aj1_c::decideType(int i_type) {
    mType = 0;
    mSpecificType = -1;
    switch (i_type) {
        case 0:
            mSpecificType = 0;
            break;
        case 1:
            mSpecificType = 1;
            break;
        case 2:
            mSpecificType = 2;
            break;
    }
    if (mType != -1 && mSpecificType != -1) {
        return 1;
    }
    return 0;
}

/* 00001930-00001950       .text cut_init_AJ1_TLK__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::cut_init_AJ1_TLK() {
    mAnmAtr = 0xFF;
    mMesgAnimeTagInfo = 0xFF;
    m7C1 = 0;
}

/* 00001950-000019A8       .text cut_move_AJ1_TLK__11daNpc_Aj1_cFv */
s32 daNpc_Aj1_c::cut_move_AJ1_TLK() {
    if (talk(1) == 0x12) {
        mAnmAtr = 0xFF;
        mMesgAnimeTagInfo = 0xFF;
        m7C1 = 0;
        return 1;
    }
    return 0;
}

/* 000019A8-000019C8       .text cut_init_INI_ANGRY__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::cut_init_INI_ANGRY() {
    setAnm_NUM(0, 1);
    mpMorf->setMorf(8.0f);
}

/* 000019C8-000019E8       .text cut_move_INI_ANGRY__11daNpc_Aj1_cFv */
s32 daNpc_Aj1_c::cut_move_INI_ANGRY() {
    return 1;
}

/* 000019E8-00001A08       .text cut_init_VIVRATE__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::cut_init_VIVRATE() {
}

/* 00001A08-00001A84       .text cut_move_VIVRATE__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::cut_move_VIVRATE() {
    if (mbMorfAnimStopped) {
        mDoAud_seStart(0x58A2, NULL, 0, dComIfGp_getReverb(current.roomNo));
        dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
        setAnm_NUM(3, 1);
        return 1;
    }
    return 0;
}

/* 00001A84-00001AA4       .text cut_init_JMP__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::cut_init_JMP() {
}

/* 00001AA4-00001AF4       .text cut_move_JMP__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::cut_move_JMP() {
    if (mbMorfAnimStopped) {
        dComIfGp_getDetect().set_quake(NULL);
        mCutTimer = 0x14;
        return 1;
    }
    return 0;
}

/* 00001AF4-00001B14       .text cut_init_SPPRISE__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::cut_init_SPPRISE() {
}

/* 00001B14-00001B60       .text cut_move_SPPRISE__11daNpc_Aj1_cFv */
s32 daNpc_Aj1_c::cut_move_SPPRISE() {
    if (cLib_calcTimer(&mCutTimer) == 0) {
        setAnm_NUM(4, 1);
        mCutTimer = l_HIO.mPrmTbl.mSppriseTimer;
        return 1;
    }
    return 0;
}

/* 00001B60-00001B80       .text cut_init_LOK__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::cut_init_LOK() {
}

/* 00001B80-00001BE4       .text cut_move_LOK__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::cut_move_LOK() {
    if (mbMorfAnimStopped && cLib_calcTimer(&mCutTimer) == 0) {
        setAnm_NUM(5, 1);
        mDoAud_seStart(0x4894, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
        mCutTimer = l_HIO.mPrmTbl.mLokTimer;
        return 1;
    }
    return 0;
}

/* 00001BE4-00001C04       .text cut_init_DAN__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::cut_init_DAN() {
}

/* 00001C04-00001C44       .text cut_move_DAN__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::cut_move_DAN() {
    if (mbMorfAnimStopped && cLib_calcTimer(&mCutTimer) == 0) {
        setAnm_NUM(2, 1);
        return 1;
    }
    return 0;
}

/* 00001C44-00001C64       .text cut_init_INVIT__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::cut_init_INVIT() {
    mDoAud_seStart(0x4893, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
}

/* 00001C64-00001C84       .text cut_move_INVIT__11daNpc_Aj1_cFv */
s32 daNpc_Aj1_c::cut_move_INVIT() {
    return 1;
}

/* 00001C84-00001DF8       .text privateCut__11daNpc_Aj1_cFi */
        /* Nonmatching */
void daNpc_Aj1_c::privateCut(int i_staffIdx) {
    if (i_staffIdx != -1) {
        dEvent_manager_c* evtmgr = dComIfGp_getPEvtManager();
        m7B5 = evtmgr->getMyActIdx(i_staffIdx, a_cut_tbl, 8, TRUE, 0);
        if (m7B5 == -1) {
            evtmgr->cutEnd(i_staffIdx);
            return;
        }
        if (evtmgr->getIsAddvance(i_staffIdx)) {
            switch (m7B5) {
                case 0:
                    cut_init_AJ1_TLK();
                    break;
                case 1:
                    cut_init_INI_ANGRY();
                    break;
                case 2:
                    cut_init_VIVRATE();
                    break;
                case 3:
                    cut_init_JMP();
                    break;
                case 4:
                    cut_init_SPPRISE();
                    break;
                case 5:
                    cut_init_LOK();
                    break;
                case 6:
                    cut_init_DAN();
                    break;
                case 7:
                    cut_init_INVIT();
                    break;
            }
        }
        s32 cutEnd;
        switch (m7B5) {
            case 0:
                cutEnd = cut_move_AJ1_TLK();
                break;
            case 1:
                cutEnd = cut_move_INI_ANGRY();
                break;
            case 2:
                cutEnd = cut_move_VIVRATE();
                break;
            case 3:
                cutEnd = cut_move_JMP();
                break;
            case 4:
                cutEnd = cut_move_SPPRISE();
                break;
            case 5:
                cutEnd = cut_move_LOK();
                break;
            case 6:
                cutEnd = cut_move_DAN();
                break;
            case 7:
                cutEnd = cut_move_INVIT();
                break;
            default:
                cutEnd = 1;
                break;
        }
        if (cutEnd != 0) {
            evtmgr->cutEnd(i_staffIdx);
        }
    }
}

/* 00001DF8-00001E10       .text endEvent__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::endEvent() {
    dComIfGp_event_onEventFlag(8);
    mAnmAtr = 0xFF;
    mMesgAnimeTagInfo = 0xFF;
}

/* 00001E10-00001E2C       .text isEventEntry__11daNpc_Aj1_cFv */
s32 daNpc_Aj1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL, 0);
}

/* 00001E2C-00001EB4       .text event_proc__11daNpc_Aj1_cFi */
        /* Nonmatching */
void daNpc_Aj1_c::event_proc(int i_eventNo) {
    if (dComIfGp_evmng_endCheck(mEventIdTable[mEventIdx])) {
        if (mEventIdx == 0) {
            dComIfGs_onEventBit(0x508);
            dComIfGs_onEventBit(0x504);
        }
        endEvent();
        return;
    }
    if (mEventCut.cutProc() == 0) {
        privateCut(i_eventNo);
    }
    lookBack();
}

/* 00002098-00002118       .text set_pa_pun__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::set_pa_pun() {
    mPunEmitter = dComIfGp_particle_set(0x8113, &current.pos, NULL, NULL, 0xFF, NULL,
                                        current.roomNo, NULL, NULL, NULL);
    if (mPunEmitter != NULL) {
        mPunTimer = 0;
    }
}

/* 00002120-000021B0       .text set_pa_aka__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::set_pa_aka() {
    JPABaseEmitter* emitter = mAkaEmitter;
    if (emitter != NULL) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
    }
    mAkaEmitter = dComIfGp_particle_set(0x811F, &current.pos, NULL, NULL, 0xFF, NULL,
                                        current.roomNo, NULL, NULL, NULL);
}

/* 000021B4-00002280       .text set_pa_don__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::set_pa_don() {
    cXyz pos(24.0f, 0.0f, -4.5f);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&pos, &m7A8);
    mDonEmitter = dComIfGp_particle_set(0x8114, &m7A8, NULL, NULL, 0xFF, NULL,
                                        current.roomNo, NULL, NULL, NULL);
}

/* 00002284-00002404       .text set_pa_smk__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::set_pa_smk() {
    static const GXColor l_color = { 0xC8, 0x80, 0xA0, 0xA0 };
    PSMTXCopy(mpMorf->getModel()->getAnmMtx(m_fot_L_jnt_num), mDoMtx_stack_c::get());
    m79C.set(mDoMtx_stack_c::get()[0][3], mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
    mSmokeEcallBack.end();
    mSmokeEmitter = dComIfGp_particle_set(0x2027, &m79C, &current.angle, NULL, 0xC8, &mSmokeEcallBack,
                                          current.roomNo, NULL, NULL, NULL);
    if (mSmokeEmitter != NULL) {
        mSmokeEmitter->setGlobalParticleScale(0.3f, 0.3f);
        mSmokeEmitter->setGlobalDynamicsScale(JGeometry::TVec3<f32>(0.1f, 0.1f, 0.1f));
        mSmokeEmitter->setLifeTime(0x28);
        mSmokeEmitter->setRate(3.0f);
        mSmokeEmitter->setMaxFrame(1);
        mSmokeEmitter->setDirectionalSpeed(120.0f);
        mSmokeEmitter->setEmitterScale(JGeometry::TVec3<f32>(1.0f, 0.1f, 1.0f));
        mSmokeEcallBack.setColor(l_color);
    }
}

/* 00002404-0000247C       .text flw_pa_pun__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::flw_pa_pun() {
    if (mPunEmitter != NULL) {
        mPunEmitter->setGlobalRTMatrix(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        if (cLib_calcTimer(&mPunTimer) == 0) {
            mDoAud_seStart(0x58A3, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
            mPunTimer = 5;
        }
    }
}

/* 0000247C-000024B0       .text flw_pa_aka__11daNpc_Aj1_cFv */
void daNpc_Aj1_c::flw_pa_aka() {
    if (mAkaEmitter != NULL) {
        mAkaEmitter->setGlobalRTMatrix(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    }
}

/* 000024B0-000024EC       .text del_pa_aka__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::del_pa_aka() {
    if (m7B4 != 0) {
        if (mAkaEmitter != NULL) {
            if (mAkaEmitter->getParticleNumber() == 0) {
                mAkaEmitter->setMaxFrame(-1);
                mAkaEmitter->setStatus(1);
                m7B4 = 0;
                mAkaEmitter = NULL;
            }
        } else {
            m7B4 = 0;
        }
    }
}

/* 000024EC-00002530       .text del_pa__11daNpc_Aj1_cFPP14JPABaseEmitter */
void daNpc_Aj1_c::del_pa(JPABaseEmitter** i_ppEmitter) {
    JPABaseEmitter* emitter = *i_ppEmitter;
    if (emitter != NULL) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        *i_ppEmitter = NULL;
    }
}

/* 00002530-000025F8       .text setSmoke__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::setSmoke() {
    if (mAnmNum == 2) {
        if (mpMorf->checkFrame(0.0f) || mpMorf->checkFrame(9.0f)) {
            set_pa_smk();
        }
        if (mpMorf->checkFrame(0.0f) || mpMorf->checkFrame(10.0f)) {
            mDoAud_seStart(0x58A4, &current.pos, 0, dComIfGp_getReverb(current.roomNo));
        }
    }
}

/* 00002678-00002720       .text set_action__11daNpc_Aj1_cFM11daNpc_Aj1_cFPCvPvPv_iPv */
int daNpc_Aj1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc) {
            mActionIndex = 9;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        mActionIndex = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return 1;
}

/* 00002724-00002808       .text setStt__11daNpc_Aj1_cFSc */
        /* Nonmatching */
void daNpc_Aj1_c::setStt(s8 i_status) {
    s8 temp = mStatus;
    mStatus = i_status;
    switch (mStatus) {
        case 1:
            m812 = 0;
            mFARwaiTimer = cLib_getRndValue(0x5A, 0x78);
            break;
        case 2:
            m812 = 0;
            break;
        case 3:
            m812 = 0;
            mAnmAtr = 0xFF;
            mMesgAnimeTagInfo = 0xFF;
            m7C1 = 0;
            mPrevStatus = temp;
            break;
        case 4:
            m812 = 0;
            mWaitTimer = cLib_getRndValue(0x5A, 0xB4);
            if (mAnmNum == 1 || mAnmNum == 6) {
                return;
            }
            break;
        default:
            break;
    }
    setAnm();
}

/* 0000280C-00002984       .text chk_areaIN__11daNpc_Aj1_cFfs4cXyz */
        /* Nonmatching */
s32 daNpc_Aj1_c::chk_areaIN(f32 i_radius, s16 i_angle, cXyz i_pos) {
    cXyz diff = i_pos - dComIfGp_getPlayer(0)->current.pos;
    cXyz diffXZ;
    diffXZ.x = diff.x;
    diffXZ.y = 0.0f;
    diffXZ.z = diff.z;
    f32 distSq = PSVECSquareMag(&diffXZ);
    f32 dist;
    if (distSq > 0.0f) {
        dist = std::sqrtf(distSq);
    } else {
        dist = distSq;
    }
    f32 yDiff = dComIfGp_getPlayer(0)->current.pos.y - i_pos.y;
    s16 angleDiff = cLib_targetAngleY(&current.pos, &dComIfGp_getPlayer(0)->current.pos) - m708.y;
    if (dist < i_radius && std::fabsf(yDiff) < 500.0f && abs(angleDiff) < i_angle) {
        return 1;
    }
    return 0;
}

/* 00002984-00002A14       .text FARwai__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::FARwai() {
    if (chk_areaIN(l_HIO.mPrmTbl.mAreaRadius, l_HIO.mPrmTbl.mAreaAngle, current.pos)) {
        setStt(2);
        mLookBackState = 1;
        mHeadOnlyFollow = 0;
        m_jnt.setTrn();
        return 1;
    }
    if (mAnmNum == 8) {
        if (mbMorfAnimStopped) {
            setAnm_NUM(0, 1);
            mpMorf->setMorf(8.0f);
        }
        return 1;
    }
    if (cLib_calcTimer(&mFARwaiTimer) == 0) {
        setAnm_NUM(8, 1);
        mFARwaiTimer = cLib_getRndValue(0x5A, 0x78);
    }
    return 1;
}

/* 00002A14-00002AC8       .text call_1__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::call_1() {
    if (m769 != 0) {
        if (chk_talk()) {
            setStt(3);
            mLookBackState = 1;
            mHeadOnlyFollow = 0;
            m_jnt.setTrn();
        }
        return 1;
    }
    if (chk_areaIN(l_HIO.mPrmTbl.mAreaRadius, l_HIO.mPrmTbl.mAreaAngle, current.pos) == 0) {
        setStt(1);
        mpMorf->setMorf(15.0f);
        mLookBackState = 3;
        mTargetYRot = m708.y;
        mHeadOnlyFollow = 0;
        m_jnt.setTrn();
        return 1;
    }
    m_jnt.setTrn();
    if (chk_areaIN(l_HIO.mPrmTbl.mCallRadius, l_HIO.mPrmTbl.mCallAngle, current.pos)) {
        m812 = 2;
        if (m768 != 0) {
            if (mAnmNum != 0) {
                setAnm_NUM(0, 1);
                mpMorf->setMorf(15.0f);
            }
            return 1;
        }
        if (mAnmNum != 7) {
            setAnm_NUM(7, 1);
        }
    }
    return 1;
}

/* 00002AC8-00002BC8       .text wait_1__11daNpc_Aj1_cFv */
s32 daNpc_Aj1_c::wait_1() {
    cLib_addCalcAngleS(&current.angle.y, m708.y, 4, 0x400, 0);
    ctrl_WAITanm();
    if (m812 == 1 || m812 >= 3) {
        return 1;
    }
    ctrl_TIREanm();
    if (m769 != 0) {
        if (chk_talk()) {
            setStt(3);
            mLookBackState = 1;
            mHeadOnlyFollow = 0;
            m_jnt.setTrn();
        }
        return 1;
    }
    m812 = 2;
    if (mAnmNum != 1 && m768 != 0) {
        mLookBackState = 1;
        return 1;
    }
    mLookBackState = 3;
    mTargetYRot = m708.y;
    return 1;
}

/* 00002BC8-00002D08       .text talk_1__11daNpc_Aj1_cFv */
        /* Nonmatching */
int daNpc_Aj1_c::talk_1() {
    u8 partsNotMov = chk_parts_notMov();
    talk(1);
    if (mpCurrMsg == NULL) {
        return partsNotMov;
    }
    switch (mpCurrMsg->mMsgNo) {
        case 6:
        case 2:
            break;
        case 19:
            switch (mCurrMsgNo) {
                case 0x9DA:
                    dComIfGs_onEventBit(0x3704);
                    /* fallthrough */
                case 0x9C8:
                    dComIfGs_onEventBit(0x510);
                    break;
                case 0x9DD:
                    dComIfGs_onEventBit(0x3704);
                    break;
                case 0x9D1:
                case 0x9D2:
                case 0x9D3:
                    dComIfGs_onEventBit(0x3708);
                    break;
                case 0x9D7:
                    dComIfGs_onEventBit(0x3701);
                    break;
            }
            mItemNo = 0xFF;
            m769 = 0;
            setStt(mPrevStatus);
            mTalkTimer = cLib_getRndValue(0xF, 0x1E);
            endEvent();
            break;
    }
    return partsNotMov;
}

/* 00002D08-00002DD0       .text wait_action1__11daNpc_Aj1_cFPv */
int daNpc_Aj1_c::wait_action1(void*) {
    switch (mActionIndex) {
        case 9:
            break;
        case 0:
            setStt(1);
            mActionIndex++;
            break;
        case 1:
        case 2:
        case 3:
            m768 = chkAttention();
            switch (mStatus) {
                case 1:
                    mActionResult = FARwai();
                    break;
                case 2:
                    mActionResult = call_1();
                    break;
                case 3:
                    mActionResult = talk_1();
                    break;
            }
            lookBack();
            break;
    }
    return 1;
}

/* 00002DD0-00002E8C       .text wait_action2__11daNpc_Aj1_cFPv */
        /* Nonmatching */
int daNpc_Aj1_c::wait_action2(void*) {
    switch (mActionIndex) {
        case 9:
            break;
        case 0:
            setStt(4);
            if (strcmp(dComIfGp_getStartStageName(), "Ojhous2") == 0 && mSpecificType == 1 &&
                !dComIfGs_isEventBit(0x508)) {
                m812 = 3;
            }
            mActionIndex++;
            break;
        case 1:
        case 2:
        case 3:
            m768 = chkAttention();
            switch (mStatus) {
                case 4:
                    mActionResult = wait_1();
                    break;
                case 3:
                    mActionResult = talk_1();
                    break;
            }
            lookBack();
            break;
    }
    return 1;
}

/* 0000304C-0000319C       .text demo__11daNpc_Aj1_cFv */
        /* Nonmatching */
u8 daNpc_Aj1_c::demo() {
    if (demoActorID == 0) {
        if (mInDemo != 0) {
            mInDemo = 0;
        }
    } else {
        if (mInDemo == 0) {
            mInDemo = 1;
            m75F = 0;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }
        dDemo_actor_c* demoActor = dComIfGp_demo_getActor(demoActorID);
        if (mBtpAnm.getBtpAnm() != NULL) {
            mBlinkFrame++;
            s16 frameMax = mBtpAnm.getBtpAnm()->getFrameMax();
            if (mBlinkFrame >= frameMax) {
                mBlinkFrame = frameMax;
            }
        }
        J3DAnmTexPattern* btp = demoActor->getP_BtpData("Aj");
        if (btp != NULL) {
            mBtpAnm.init(mpMorf->getModel()->getModelData(), btp, TRUE, 0, 1.0f, 0, -1, 1, FALSE);
            mBtpNum = 1;
            mBlinkFrame = 0;
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Aj", 0, NULL, 0, 0);
    }
    return mInDemo;
}

/* 0000319C-00003254       .text shadowDraw__11daNpc_Aj1_cFv */
        /* Nonmatching */
void daNpc_Aj1_c::shadowDraw() {
    cXyz temp(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &temp, 800.0f, 40.0f,
                                   current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr,
                                   0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    if (mShadowID != 0) {
        if (mpItemModel != NULL) {
            dComIfGd_addRealShadow(mShadowID, mpItemModel);
        }
    }
}

/* 00003254-00003378       .text _draw__11daNpc_Aj1_cFv */
        /* Nonmatching */
BOOL daNpc_Aj1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    if (m75E != 0 || m760 != 0) {
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(modelData, mBlinkFrame);
    mpMorf->entryDL();
    modelData->removeTexNoAnimator(mBtpAnm.getBtpAnm());
    if (mpItemModel != NULL) {
        g_env_light.setLightTevColorType(mpItemModel, &tevStr);
        mDoExt_modelEntryDL(mpItemModel);
    }
    shadowDraw();
    if (l_HIO.mPrmTbl.m24 != 0) {
        cXyz pos = current.pos;
        pos.y = eyePos.y;
    }
    dSnap_RegistFig(DSNAP_TYPE_UNK4C, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00003380-000035A8       .text _execute__11daNpc_Aj1_cFv */
        /* Nonmatching */
BOOL daNpc_Aj1_c::_execute() {
    if (m761 == 0) {
        m6FC = current.pos;
        m708 = current.angle;
        m761 = 1;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY,
                   l_HIO.mPrmTbl.mMinBackboneX, l_HIO.mPrmTbl.mMinBackboneY,
                   l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
                   l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY,
                   l_HIO.mPrmTbl.mMaxTurnStep);
    if (m75E != 0 && demoActorID == 0) {
        return TRUE;
    }
    checkOrder();
    if (demo() == 0) {
        s32 staffIdx = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == 0) {
            staffIdx = isEventEntry();
        }
        if (staffIdx >= 0) {
            mHeadOnlyFollow = 1;
            event_proc(staffIdx);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        play_animation();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    eventOrder();
    m70E.x = current.angle.x;
    m70E.y = current.angle.y;
    m70E.z = current.angle.z;
    if (m75F == 0) {
        shape_angle.x = current.angle.x;
        shape_angle.y = current.angle.y;
        shape_angle.z = current.angle.z;
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(FALSE);
    flw_pa_pun();
    del_pa_aka();
    flw_pa_aka();
    setSmoke();
    if (mInDemo == 0) {
        setCollision(60.0f, 140.0f);
    }
    return TRUE;
}

/* 000035A8-00003638       .text _delete__11daNpc_Aj1_cFv */
        /* Nonmatching */
BOOL daNpc_Aj1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Aj");
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    del_pa(&mPunEmitter);
    del_pa(&mAkaEmitter);
    del_pa(&mDonEmitter);
    mSmokeEcallBack.end();
    return TRUE;
}

/* 0000363C-0000388C       .text _create__11daNpc_Aj1_cFv */
        /* Nonmatching */
cPhs_State daNpc_Aj1_c::_create() {
    static int a_siz_tbl[] = {
        0x0,
    };
    fopAcM_ct_Retail(this, daNpc_Aj1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Aj");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[mType])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -60.0f, -20.0f, -60.0f, 80.0f, 260.0f, 100.0f);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 00003B5C-00003E88       .text bodyCreateHeap__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Aj", dRes_ID_AJ_BDL_AJ_e);
    JUT_ASSERT(VERSION_SELECT(2238, 2237, 2238, 2238), a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        NULL,
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11020022
    );
    if (mpMorf == NULL) {
        return 0;
    }
    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return 0;
    }
    if (!init_texPttrnAnm(0, FALSE)) {
        mpMorf = NULL;
        return 0;
    }
    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(VERSION_SELECT(2259, 2258, 2259, 2259), m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(VERSION_SELECT(2261, 2260, 2261, 2261), m_bbone_jnt_num >= 0);
    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(VERSION_SELECT(2263, 2262, 2263, 2263), m_hnd_L_jnt_num >= 0);
    m_fot_L_jnt_num = a_mdl_dat->getJointName()->getIndex("footL");
    JUT_ASSERT(VERSION_SELECT(2265, 2264, 2265, 2265), m_fot_L_jnt_num >= 0);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((u32)this);
    return 1;
}

/* 00003E90-00003F78       .text itemCreateHeap__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::itemCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Aj", dRes_ID_AJ_BDL_AJ_STICK_e);
    JUT_ASSERT(VERSION_SELECT(2291, 2290, 2291, 2291), a_mdl_dat != NULL);
    mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    if (mpItemModel == NULL) {
        return 0;
    }
    return 1;
}

/* 000039D4-00003B5C       .text CreateHeap__11daNpc_Aj1_cFv */
        /* Nonmatching */
s32 daNpc_Aj1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return 0;
    }
    if (!itemCreateHeap()) {
        mpMorf = NULL;
        return 0;
    }
    mAcchCir.SetWall(30.0f, 60.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                 fopAcM_GetSpeed_p(this), NULL, NULL);
    return 1;
}

/* 0000485C-0000487C       .text daNpc_Aj1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Aj1_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Aj1_c*>(i_this)->_create();
}

/* 0000487C-0000489C       .text daNpc_Aj1_Delete__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_Delete(daNpc_Aj1_c* i_this) {
    return static_cast<daNpc_Aj1_c*>(i_this)->_delete();
}

/* 0000489C-000048BC       .text daNpc_Aj1_Execute__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_Execute(daNpc_Aj1_c* i_this) {
    return static_cast<daNpc_Aj1_c*>(i_this)->_execute();
}

/* 000048BC-000048DC       .text daNpc_Aj1_Draw__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_Draw(daNpc_Aj1_c* i_this) {
    return static_cast<daNpc_Aj1_c*>(i_this)->_draw();
}

/* 000048DC-000048E4       .text daNpc_Aj1_IsDelete__FP11daNpc_Aj1_c */
static BOOL daNpc_Aj1_IsDelete(daNpc_Aj1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Aj1_Method = {
    (process_method_func)daNpc_Aj1_Create,
    (process_method_func)daNpc_Aj1_Delete,
    (process_method_func)daNpc_Aj1_Execute,
    (process_method_func)daNpc_Aj1_IsDelete,
    (process_method_func)daNpc_Aj1_Draw,
};

actor_process_profile_definition g_profile_NPC_AJ1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007FFFD,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_AJ1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ 0x000007C4,
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_AJ1_e,
    /* Actor SubMtd */ &l_daNpc_Aj1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
