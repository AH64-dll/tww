/**
 * d_a_npc_gp1.cpp
 * NPC - Maggie's Father (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_gp1.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_event.h"
#include "d/d_event_data.h"
#include "d/d_snap.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "SSystem/SComponent/c_counter.h"
#include "res/Object/Gp.h"

class daNpc_Gp1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x18 */ u8 m18;
        /* 0x1C */ f32 m1C;
        /* 0x20 */ s16 m20;
        /* 0x22 */ s16 m22;
        /* 0x24 */ f32 m24;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
        /* 0x30 */ f32 m30;
    };  // Size: 0x34

    daNpc_Gp1_HIO_c();
    virtual ~daNpc_Gp1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;

};

/* Nonmatching */
/* 000000EC-00000150       .text __ct__15daNpc_Gp1_HIO_cFv */
daNpc_Gp1_HIO_c::daNpc_Gp1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x2000,
        /* mMaxHeadY         */ 0x2A00,
        /* mMinHeadX         */ 0xF254,
        /* mMinHeadY         */ 0xD600,
        /* mMaxBackboneX     */ 0x0000,
        /* mMaxBackboneY     */ 0x1C00,
        /* mMinBackboneX     */ 0x0000,
        /* mMinBackboneY     */ 0xE400,
        /* mMaxTurnStep      */ 0x0400,
        /* mCalcAngleTarget  */ 0x0400,
        /* mAttPosOffsetY    */ 233.0f,
        /* m18               */ 0.0f,
        /* m1C               */ 300.0f,
        /* m20               */ 0x0000,
        /* m22               */ 0x0400,
        /* m24               */ 0.4f,
        /* m28               */ 3.0f,
        /* m2C               */ 0.2f,
        /* m30               */ 20.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static daNpc_Gp1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

static char* l_evn_tbl[] = {
    "Kaere_Kaere",
    "Gp1_Get_Itm",
    "Giv_Rupee",
};

/* 00000198-00000210       .text searchActor_Bm__FPvPv */
static void* searchActor_Bm(void* i_param_1, void*) {
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_BM4_e) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 00000210-0000025C       .text nodeCallBack_Gp1__FP7J3DNodei */
static BOOL nodeCallBack_Gp1(J3DNode* i_param_1, int i_param_2) {
    if(i_param_2 == 0) {
        if(j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Gp1_c*>(j3dSys.getModel()->getUserArea())->nodeGp1Control(i_param_1, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000025C-000003AC       .text nodeGp1Control__11daNpc_Gp1_cFP7J3DNodeP8J3DModel */
void daNpc_Gp1_c::nodeGp1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(24.0f, -24.0f, 0.0f);
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    if(jointIdx == m_hed_jnt_num) {
        mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    }
    if(jointIdx == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* Nonmatching */
/* 000003E8-00000468       .text init_GP1_0__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::init_GP1_0() {
    if(dComIfGs_isEventBit(0x2D01)) {
        set_action(&daNpc_Gp1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* Nonmatching */
/* 00000468-00000638       .text createInit__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::createInit() {
    for(int i = 0; i < 3; i++) {
        mEventIdTable[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xFF);
    }
    attention_info.flags = 0xA;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
    gravity = -4.5f;
    m79C = current.pos;
    u8 path_idx = fopAcM_GetParam(this) >> 16 & 0xFF;
    if(path_idx != 0xFF) {
        mPathRun.setInf(path_idx, current.roomNo, 1);
        if(mPathRun.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            path_idx = 0xD9;
        } else {
            return false;
        }
    }
    mEventCut.setActorInfo2("Gp1", this);
    mAnmNum = 8;
    bool ret;
    switch(m818) {
        case 0:
            ret = init_GP1_0();
            break;
        default:
            ret = false;
    }
    if(ret) {
        m78A = current.angle;
        shape_angle = m78A;
    } else {
        return false;
    }
    mStts.Init(path_idx, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 00000638-00000758       .text setMtx__11daNpc_Gp1_cFb */
void daNpc_Gp1_c::setMtx(bool param_1) {
    if(!mbInDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if(mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        ctrl_WAITanm();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(m78A.y);

    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention(param_1);
}

/* 00000758-0000076C       .text anmNum_toResID__11daNpc_Gp1_cFi */
int daNpc_Gp1_c::anmNum_toResID(int param_1) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_GP_BCK_WAIT01_e,
        dRes_ID_GP_BCK_WAIT01_e,
        dRes_ID_GP_BCK_TALK02_e,
        dRes_ID_GP_BCK_TALK03_e,
        dRes_ID_GP_BCK_HAIR_e,
        dRes_ID_GP_BCK_GRIN_e,
        dRes_ID_GP_BCK_GIVE_e,
        dRes_ID_GP_BCK_WALK_e,
    };
    return a_bck_resID_tbl[param_1];
}

/* 0000076C-00000780       .text btpNum_toResID__11daNpc_Gp1_cFi */
int daNpc_Gp1_c::btpNum_toResID(int param_1) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_GP_BTP_MABA01_e,
    };
    return a_btp_resID_tbl[param_1];
}

/* 00000780-00000890       .text setBtp__11daNpc_Gp1_cFbi */
bool daNpc_Gp1_c::setBtp(bool i_param_1, int i_btp_num) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    int res_id = btpNum_toResID(i_btp_num);
    m_hed_tex_pttrn = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes("Gp", res_id));
    JUT_ASSERT(VERSION_SELECT(0x1B3, 0x1B3, 0x1B3, 0x1B3), m_hed_tex_pttrn != NULL);

    int iVar1 = mHeadBtpAnm.init(model_data, m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, i_param_1, 0);
    bool o_retval = iVar1 == 1;
    if(o_retval) {
        mBlinkFrame = 0;
        mBlinkTimer = 0;
    }
    return o_retval;
}

/* 00000890-000008B8       .text iniTexPttrnAnm__11daNpc_Gp1_cFb */
bool daNpc_Gp1_c::iniTexPttrnAnm(bool i_param_1) {
    return setBtp(i_param_1, mBtpNum);
}

/* 000008B8-00000964       .text plyTexPttrnAnm__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::plyTexPttrnAnm() {
    if(mBtpNum != 0 || !cLib_calcTimer(&mBlinkTimer)) {
        mBlinkFrame += 1;
        if(mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
            if(mBtpNum != 0) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            } else {
                mBlinkTimer = cM_rndF(60.0f) + 30.0f;
                mBlinkFrame = 0;
            }
        }
    }
}

/* 00000964-000009A0       .text setAnm_tex__11daNpc_Gp1_cFSc */
void daNpc_Gp1_c::setAnm_tex(s8 i_btp_num) {
    if(mBtpNum != i_btp_num) {
        mBtpNum = i_btp_num;
        iniTexPttrnAnm(true);
    }
}

/* Nonmatching */
/* 000009A0-00000A78       .text setAnm_anm__11daNpc_Gp1_cFPQ211daNpc_Gp1_c9anm_prm_c */
BOOL daNpc_Gp1_c::setAnm_anm(daNpc_Gp1_c::anm_prm_c* i_anmPrmP) {
    if(mAnmNum == i_anmPrmP->mAnmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->mAnmNum;
    dNpc_setAnmIDRes(
        mpMorf,
        i_anmPrmP->mLoopMode,
        i_anmPrmP->mMorf,
        i_anmPrmP->mSpeed,
        anmNum_toResID(mAnmNum),
        -1,
        "Gp"
    );
    if(mAnmNum == 0) {
        m7F6 = (s16)(cM_rndF(120.0f) + 180.0f);
        mPrevMorfFrame = 0.0f;
        m7F9 = 0;
        mbMorfAnimStopped = 0;
    }
    return TRUE;
}

/* Nonmatching */
/* 00000A78-00000AE4       .text setAnm_NUM__11daNpc_Gp1_cFii */
void daNpc_Gp1_c::setAnm_NUM(int i_param_1, int i_param_2) {
    static anm_prm_c a_anm_prm_tbl[9] = {
        {0, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8, 1, J3DFrameCtrl::EMode_NONE},
        {5, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8, 1, J3DFrameCtrl::EMode_NONE},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
    };
    if(i_param_2 != 0) {
        setAnm_tex(a_anm_prm_tbl[i_param_1].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param_1]);
}

/* Nonmatching */
/* 00000AE4-00000B64       .text setAnm__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[6] = {
        {-1, -1, 0, 0, 0, -1},
        {0, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0, 0, -1},
        {7, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8, 1, J3DFrameCtrl::EMode_NONE},
        {-1, -1, 0, 0, 0, -1},
    };
    if(a_anm_prm_tbl[mPrevStatus].mBtpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mPrevStatus].mBtpNum);
    }
    if(a_anm_prm_tbl[mPrevStatus].mAnmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mPrevStatus]);
    }
    return true;
}

/* 00000B64-00000B68       .text chg_anmTag__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::chg_anmTag() {}

/* 00000B68-00000B6C       .text control_anmTag__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::control_anmTag() {}

/* 00000B6C-00000BB0       .text chg_anmAtr__11daNpc_Gp1_cFUc */
void daNpc_Gp1_c::chg_anmAtr(u8 i_param_1) {
    if((i_param_1 >= 0x7) || (i_param_1 == m80F)) {
        return;
    }
    m80F = i_param_1;
    setAnm_ATR(1);
}

/* 00000BB0-00000D00       .text control_anmAtr__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::control_anmAtr() {
    switch(m80F) {
        case 0:
            break;
        case 1:
            if(mbMorfAnimStopped) {
                m80F = 0;
                setAnm_NUM(0, 1);
            }
            break;
        case 5:
            if(!mbMorfAnimStopped) {
                if(mpMorf->checkFrame(80.0f)) {
                    create_rupee();
                    JAIZelBasic::zel_basic->seStart(JA_SE_OBJ_LUPY_OUT, NULL, 0, dComIfGp_getReverb(current.roomNo));
                    m7F4 = 0;
                }
            } else {
                m80F = 0;
                setAnm_NUM(0, 1);
            }
            break;
        case 6:
            if(mbMorfAnimStopped) {
                if(++m7F9 >= 2) {
                    m80F = 0;
                    setAnm_NUM(0, 1);
                }
            }
            break;
        default:
            break;
    }
}

/* Nonmatching */
/* 00000D00-00000D68       .text setAnm_ATR__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::setAnm_ATR(int i_param_1) {
    static anm_prm_c a_anm_prm_tbl[7] = {
        {0, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8, 1, J3DFrameCtrl::EMode_NONE},
        {2, 0, 0, 8, 1, J3DFrameCtrl::EMode_LOOP},
    };
    if(i_param_1 != 0) {
        setAnm_tex(a_anm_prm_tbl[m80F].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[m80F]);
}

/* 00000D68-00000E2C       .text anmAtr__11daNpc_Gp1_cFUs */
void daNpc_Gp1_c::anmAtr(u16 i_param_1) {
    switch(i_param_1) {
        case 6:
            if(m81A == 0) {
                m80F = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m81A++;
            }
            {
                u8 tag = dComIfGp_getMesgAnimeTagInfo();
                dComIfGp_setMesgAnimeTagInfo(0xFF);
                if(tag != 0xFF && (u8)mAnmTag != tag) {
                    mAnmTag = (s8)tag;
                    chg_anmTag();
                }
            }
            break;
        case 0xE:
            m81A = 0;
            break;
        default:
            break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00000E2C-00000EC4       .text eventOrder__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::eventOrder() {
    s8 condition = mStatus;
    if(condition == 1 || condition == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if(mStatus == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if(condition >= 3) {
        mEventIdx = condition - 3;
        fopAcM_orderOtherEventId(this, mEventIdTable[mEventIdx], 0xFF, 0xFFFF, 0, 1);
    }
}

/* 00000EC4-00000F5C       .text checkOrder__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mEventIdTable[mEventIdx])) {
            mStatus = 0;
        }
    } else if(eventInfo.checkCommandTalk() && (mStatus == 1 || mStatus == 2)) {
        mStatus = 0;
        m809 = true;
    }
}

/* 00000F5C-00001008       .text chk_talk__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chk_talk() {
    bool ret = true;
    m7FB = 0xFF;
    if(dComIfGp_event_chkTalkXY()) {
        if(dComIfGp_evmng_ChkPresentEnd()) {
            m7FB = dComIfGp_event_getPreItemNo();
        } else {
            ret = false;
        }
        m7FB = dComIfGp_event_getPreItemNo();
    }
    return ret;
}

/* 00001008-00001048       .text chk_partsNotMove__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chk_partsNotMove() {
    return mLookY == m_jnt.getHead_y() &&
        mLookX == m_jnt.getBackbone_y() &&
        mActorAngleY == current.angle.y;
}

/* Nonmatching */
/* 00001048-00001168       .text chk_forceTlkArea__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chk_forceTlkArea() {
    cXyz diff = dComIfGp_getPlayer(0)->current.pos - current.pos;
    diff.y = 0.0f;
    f32 dist = diff.abs();
    f32 y_diff = dComIfGp_getPlayer(0)->current.pos.y - current.pos.y;
    return -1.0f < y_diff && y_diff <= 100.0f && dist < l_HIO.mPrmTbl.m1C;
}

/* Nonmatching */
/* 00001168-00001308       .text lookBack__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    mLookY = m_jnt.getHead_y();
    mLookX = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = mHeadOnlyFollow;

    switch(mType) {
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
    if(!m_jnt.trnChk()) {
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, mLookAtMaxVel, headOnlyFollow);
}

/* 00001308-00001504       .text next_msgStatus__11daNpc_Gp1_cFPUl */
u16 daNpc_Gp1_c::next_msgStatus(u32* i_msg_no) {
    u16 ret = 0xF;
    s16 beast_num = dComIfGs_getBeastNum(0);
    switch(*i_msg_no) {
        case 0x1E15:
            *i_msg_no = 0x1E16;
            break;
        case 0x1E16:
            *i_msg_no = 0x1E17;
            break;
        case 0x1E17:
            *i_msg_no = 0x1E18;
            break;
        case 0x1E19:
            *i_msg_no = 0x1E1A;
            break;
        case 0x1E1A:
            *i_msg_no = 0x1E1B;
            break;
        case 0x1E1B:
            *i_msg_no = 0x1E1C;
            break;
        case 0x1E29:
            *i_msg_no = 0x1E2A;
            m7F2 = beast_num;
            m801 = 1;
            break;
        case 0x1E2A:
            if(m7F2 >= 0x10) {
                *i_msg_no = 0x1E2D;
                m7F4 = 3;
            } else if(m7F2 >= 6) {
                *i_msg_no = 0x1E2C;
                m7F4 = 2;
            } else {
                *i_msg_no = 0x1E2B;
                m7F4 = 1;
            }
            break;
        case 0x1E20:
            *i_msg_no = 0x1E21;
            break;
        case 0x1E30:
            *i_msg_no = 0x1E23;
            break;
        case 0x1E22:
        case 0x1E28:
            *i_msg_no = 0x1E24;
            m801 = 1;
            m7F2 = 0x14;
            break;
        case 0x1E24:
            *i_msg_no = 0x1E25;
            break;
        case 0x1E26:
            *i_msg_no = 0x1E27;
            break;
        case 0x1E21:
            if(beast_num >= 0x14) {
                *i_msg_no = 0x1E22;
            } else {
                *i_msg_no = 0x1E30;
            }
            break;
        case 0x1EE6:
            *i_msg_no = 0x1EE7;
            break;
        default:
            ret = 0x10;
            break;
    }
    return ret;
}

/* 00001504-0000166C       .text getMsg_GP1_0__11daNpc_Gp1_cFv */
u32 daNpc_Gp1_c::getMsg_GP1_0() {
    if(m7FB == 0x45) {
        if(dComIfGs_isEventBit(0x1420)) {
            return 0x1E29;
        }
        if(dComIfGs_isEventBit(0x1804)) {
            if((s32)dComIfGs_getBeastNum(0) >= 0x14) {
                return 0x1E28;
            }
            return 0x1E30;
        }
        return 0x1E20;
    }
    if(m7FB != 0xFF) {
        return 0x1E2F;
    }
    if(m7FA) {
        m7FA = 0;
        return 0x1E26;
    }
    if(!dComIfGs_isEventBit(0x1501)) {
        return 0x1E15;
    }
    if(dComIfGs_isEventBit(0x1808)) {
        if(dComIfGs_checkReserveItem(0x9B)) {
            return 0x1E1D;
        }
        u8 reg = dComIfGs_getEventReg(0xC5FF);
        return (reg >= 10) ? 0x1E1E : 0x1E1F;
    }
    if(dComIfGs_isEventBit(0x1920)) {
        return 0x1E1B;
    }
    return 0x1E19;
}

/* 0000166C-000016A8       .text getMsg__11daNpc_Gp1_cFv */
u32 daNpc_Gp1_c::getMsg() {
    u32 ret = 0;
    switch(m818) {
        case 0:
            ret = getMsg_GP1_0();
            break;
    }
    return ret;
}

/* 000016A8-00001728       .text chkAttention__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if(attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 00001728-00001790       .text setAttention__11daNpc_Gp1_cFb */
void daNpc_Gp1_c::setAttention(bool i_setEyePos) {
    f32 offset = l_HIO.mPrmTbl.mAttPosOffsetY;
    attention_info.position.set(
        current.pos.x,
        current.pos.y + offset,
        current.pos.z
    );

    if(!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(
        mTransformedEyePos.x,
        mTransformedEyePos.y,
        mTransformedEyePos.z
    );
    eyePos.y += m7C4;
}

/* 00001790-000017C4       .text searchByID__11daNpc_Gp1_cFUi */
fopAc_ac_c* daNpc_Gp1_c::searchByID(fpc_ProcID i_procID) {
    fopAc_ac_c* o_actor = NULL;
    fopAcM_SearchByID(i_procID, &o_actor);
    return o_actor;
}

/* 000017C4-00001874       .text partner_srch_sub__11daNpc_Gp1_cFPFPvPv_Pv */
bool daNpc_Gp1_c::partner_srch_sub(fpcLyIt_JudgeFunc i_searchFunc) {
    bool o_retval = false;
    mPartnerProcID = -1;
    l_check_wrk = 0;
    for(int i = 0; i < 20; i++) {
        l_check_inf[i] = 0;
    }
    fpcM_Search(i_searchFunc, this);
    if(l_check_wrk != 0) {
        mPartnerProcID = fopAcM_GetID(l_check_inf[0]);
        o_retval = true;
    }
    return o_retval;
}

/* 00001874-00001918       .text partner_srch__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::partner_srch() {
    if(m819 == 1) {
        bool found;
        switch(mPrevStatus) {
        case 3:
            found = partner_srch_sub(searchActor_Bm);
            if(found) {
                fopAc_ac_c* partner = searchByID(mPartnerProcID);
                if(partner != NULL) {
                    current.angle.y = cLib_targetAngleY(&current.pos, &partner->current.pos);
                }
            }
            break;
        default:
            found = true;
            break;
        }
        if(found) {
            m819++;
        }
    }
}

/* 00001918-000019AC       .text ctrl_WAITanm__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::ctrl_WAITanm() {
    switch(mAnmNum) {
        case 0:
            if(cLib_calcTimer(&m7F6) == 0) {
                setAnm_NUM(4, 1);
            }
            break;
        case 4:
            if(mbMorfAnimStopped) {
                setAnm_NUM(0, 1);
                mpMorf->setMorf(0.0f);
            }
            break;
        default:
            break;
    }
}

/* Nonmatching */
/* 000019AC-00001B1C       .text gp_movPass__11daNpc_Gp1_cFv */
int daNpc_Gp1_c::gp_movPass() {
    int ret = 0;
    if(mPathRun.isPath() && dPath_ChkClose(mPathRun.getPath())) {
        if(mPathRun.chkPointPass(current.pos, mPathRun.getDir())) {
            mPathRun.nextIdxAuto();
            ret = 1;
        }
        return ret;
    }
    cXyz diff = m7A8 - current.pos;
    diff.y = 0.0f;
    f32 dist = diff.abs();
    if(dist <= m7D4) {
        ret = 1;
        if(mPathRun.isPath()) {
            if(!mPathRun.nextIdxAuto()) {
                ret = 2;
            }
        }
    }
    return ret;
}

/* 00001B1C-00001B80       .text gp_clcMovSpd__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::gp_clcMovSpd() {
    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &m7A8), l_HIO.mPrmTbl.m20, l_HIO.mPrmTbl.m22, 0);
    cLib_chaseF(&speedF, m7CC, m7D0);
}

/* Nonmatching */
/* 00001B80-00001C40       .text gp_nMove__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::gp_nMove() {
    if(m800) {
        m7FE = 1;
        return;
    }
    switch(mActionIndex) {
        case 1:
            gp_clcMovSpd();
            f32 spd = speedF * l_HIO.mPrmTbl.m24;
            if(spd < 0.5f) {
                spd = 0.5f;
            }
            mpMorf->setPlaySpeed(spd);
            switch(gp_movPass()) {
                case 1:
                    m800 = 1;
                    break;
                case 2:
                    m800 = 1;
                    mActionIndex = 0;
                    break;
            }
            break;
    }
}

/* Nonmatching */
/* 00001C40-00001ED8       .text create_rupee__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::create_rupee() {
    cXyz scale(0.2f, 0.2f, 0.2f);
    csXyz angle(0, 0, 0);
    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hnd_L_jnt_num));
    cXyz pos(mDoMtx_stack_c::get()[0][3], mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
    int counter = g_Counter.mCounter0;
    int created = 0;
    while(created < m7F4) {
        f32 a_off_tbl[3] = {-30.0f, 0.0f, 30.0f};
        angle.y = current.angle.y + cM_deg2s((f32)(s16)((cM_rndF(30.0f) - 15.0f) + a_off_tbl[counter % 3]));
        s8 room_no = current.roomNo;
        f32 scale_y = 33.0f + cM_rndFX(6.0f);
        f32 scale_xz = 10.0f + cM_rndFX(3.0f);
        fopAc_ac_c* item = (fopAc_ac_c*)fopAcM_fastCreateItem(&pos, dItemNo_RED_RUPEE_e, room_no, NULL, NULL, scale_xz, scale_y, -2.0f);
        if(item == NULL) {
            break;
        }
        item->actor_status |= fopAcStts_UNK4000_e;
        item->scale = scale;
        item->current.angle = angle;
        item->shape_angle = angle;
        counter++;
        created++;
    }
    return true;
}

/* 00001ED8-00001EF4       .text charDecide__11daNpc_Gp1_cFi */
bool daNpc_Gp1_c::charDecide(int) {
    mSpecificType = 0;
    m818 = -1;
    m818 = 0;
    return true;
}

/* 00001EF4-00001F40       .text eInit_INI_KAERE_KAERE___11daNpc_Gp1_cFv */
void daNpc_Gp1_c::eInit_INI_KAERE_KAERE_() {
    fopAc_ac_c* partner = searchByID(mPartnerProcID);
    if(partner != NULL) {
        g_dComIfG_gameInfo.play.getEvent()->setPtI(partner);
    }
}

/* 00001F40-00001F4C       .text eInit_END_KAERE_KAERE___11daNpc_Gp1_cFv */
void daNpc_Gp1_c::eInit_END_KAERE_KAERE_() {
    current.angle.y = mInitialAngle.y;
}

/* 00001F4C-00001FE0       .text event_actionInit__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::event_actionInit(int i_staff_idx) {
    int* act_no_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx, "ActNo");
    if(act_no_p != NULL) {
        m80E = *act_no_p;
        mbSetEyePos = 0;
        switch(m80E) {
            case 0:
                eInit_INI_KAERE_KAERE_();
                break;
            case 1:
                eInit_END_KAERE_KAERE_();
                break;
        }
    }
}

/* 00001FE0-00001FF4       .text event_action__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::event_action() {
    if (m80E >= 2) {
        return true;
    }
    return true;
}

/* Nonmatching */
/* 00001FF4-000020E0       .text privateCut__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::privateCut(int i_staff_idx) {
    static char* a_cut_tbl[] = {
        "ACTION",
    };
    enum {
        ACT_ACTION,
    };

    if(i_staff_idx == -1) {
        return;
    }

    mActNo = dComIfGp_evmng_getMyActIdx(i_staff_idx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);
    if(mActNo == -1) {
        dComIfGp_evmng_cutEnd(i_staff_idx);
    } else {
        if(dComIfGp_evmng_getIsAddvance(i_staff_idx)) {
            switch(mActNo) {
                case ACT_ACTION:
                    event_actionInit(i_staff_idx);
                    break;
            }
        }
        bool endCut;
        switch(mActNo) {
            case ACT_ACTION:
                endCut = event_action();
                break;
            default:
                endCut = true;
                break;
        }
        if(endCut) {
            dComIfGp_evmng_cutEnd(i_staff_idx);
        }
    }
}

/* 000020E0-00002100       .text endEvent__11daNpc_Gp1_cFv */
void daNpc_Gp1_c::endEvent() {
    dComIfGp_event_reset();
    m80F = 0xFF;
}

/* 00002100-00002138       .text isEventEntry__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 00002138-00002268       .text event_proc__11daNpc_Gp1_cFi */
void daNpc_Gp1_c::event_proc(int i_staff_idx) {
    if(dComIfGp_evmng_endCheck(mEventIdTable[mEventIdx])) {
        switch(mEventIdx) {
            case 0:
                dComIfGs_onEventBit(0x1808);
                fopAcM_OnStatus(this, fopAcStts_NOCULLEXEC_e);
                setStt(1);
                m7EA = 0;
                m7EC = (g_Counter.mCounter0 & 3) + 2;
                break;
            case 1:
                dComIfGs_onEventBit(0x1420);
                mStatus = 1;
                m7FA = true;
                break;
            case 2:
                setStt(1);
                break;
        }
        endEvent();
        return;
    }
    if(!mEventCut.cutProc()) {
        privateCut(i_staff_idx);
    }
    lookBack();
}

/* 00002268-00002314       .text set_action__11daNpc_Gp1_cFM11daNpc_Gp1_cFPCvPvPv_iPv */
BOOL daNpc_Gp1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if(mCurrProcFunc != i_newProcFunc) {
        if(mCurrProcFunc) {
            m819 = 9;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        m819 = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00002314-0000240C       .text setStt__11daNpc_Gp1_cFSc */
void daNpc_Gp1_c::setStt(s8 i_status) {
    s8 temp = mPrevStatus;
    m7E8 = 0;
    mPrevStatus = i_status;
    switch(mPrevStatus) {
        case 1:
            m7EA = 90;
            break;
        case 2:
            m80F = 0xFF;
            mType = 1;
            m_jnt.setTrn();
            mLookBackState = temp;
            return;
        case 4:
            mType = 0;
            mActionIndex = 1;
            m7EA = (s16)(cM_rndF(120.0f) + 180.0f);
            m7CC = l_HIO.mPrmTbl.m28;
            m7D0 = l_HIO.mPrmTbl.m2C;
            m7D4 = l_HIO.mPrmTbl.m30;
            break;
        case 5:
            mType = 0;
            break;
        default:
            break;
    }
    setAnm();
}

/* Nonmatching */
/* 0000240C-0000255C       .text wait_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::wait_1() {
    m7F6 = (s16)(cM_rndF(120.0f) + 180.0f);
    if(m809 != 0 && mAnmNum != 4) {
        if(chk_talk()) {
            setStt(2);
            mHeadOnlyFollow = 0;
        }
        return TRUE;
    }
    if(mStatus != 1 && mStatus < 3) {
        mStatus = 2;
    }
    if(chk_forceTlkArea() || mbAttention) {
        m7E8 = 60;
    }
    if(cLib_calcTimer(&m7E8)) {
        mType = 1;
        return TRUE;
    }
    if(cLib_calcTimer(&m7EA) == 0) {
        setStt(4);
        return TRUE;
    }
    mType = 2;
    m79C.set(-2.0f, eyePos.y, 940.0f);
    m_jnt.setTrn();
    return TRUE;
}

/* Nonmatching */
/* 0000255C-00002724       .text talk_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::talk_1() {
    u8 ret;
    ret = chk_partsNotMove();
    talk(1);
    if(mpCurrMsg != NULL) {
        switch(mpCurrMsg->mStatus) {
            case fopMsgStts_MSG_DESTROYED_e:
                switch(mCurrMsgNo) {
                    case 0x1E18:
                        dComIfGs_onEventBit(0x1501);
                        break;
                    case 0x1E1C:
                        dComIfGs_onEventBit(0x1920);
                        break;
                    case 0x1E23:
                        dComIfGs_onEventBit(0x1804);
                        break;
                    case 0x1E25:
                        mStatus = 4;
                        break;
                    case 0x1E2B:
                    case 0x1E2C:
                    case 0x1E2D:
                        mStatus = 5;
                        break;
                }
                m7FB = 0xFF;
                m809 = false;
                setStt(mLookBackState);
                m7E8 = 60;
                endEvent();
                break;
            case fopMsgStts_MSG_TYPING_e:
            case fopMsgStts_BOX_OPENING_e:
                if(m801) {
                    dComIfGp_evmng_CancelPresent();
                    if(m7F2 != 0) {
                        u8 reg = dComIfGs_getEventReg(0xC5FF);
                        dComIfGp_setItemBeastNumCount(0, -m7F2);
                        dComIfGs_setEventReg(0xC5FF, (u8)cLib_maxLimit<s32>(reg + m7F2, 0x7F));
                        m801 = 0;
                    }
                }
                break;
        }
    }
    return ret;
}

/* Nonmatching */
/* 00002724-0000288C       .text walk_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::walk_1() {
    if(m809 == 0 && !chk_forceTlkArea()) {
        if(cLib_calcTimer(&m7EA) == 0) {
            m7CC = 0.0f;
            if(mStatus != 1 && mStatus < 3) {
                mStatus = 2;
                if(m800 != 0) {
                    m800 = 0;
                    if(mActionIndex == 0) {
                        mPathRun.setIdx(0);
                        mActionIndex = 1;
                    }
                }
                u8 idx = mPathRun.getIdx();
                m7A8 = mPathRun.getPoint(idx);
                if((s32)m7CC == 0 && (s32)speedF == 0) {
                    if(m809 != 0 || cLib_calcTimer(&m7EC) != 0) {
                        setStt(1);
                    } else {
                        setStt(5);
                        m7EC = (g_Counter.mCounter0 & 3) + 2;
                        speedF = 0.0f;
                        m7D0 = 0.0f;
                        mActionIndex = 0;
                    }
                }
            }
        }
    }
    return TRUE;
}

/* 0000288C-00002930       .text hair_1__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::hair_1() {
    if(mbMorfAnimStopped) {
        if(m809 != 0 || chk_forceTlkArea()) {
            setStt(1);
            return TRUE;
        }
        setStt(4);
        return TRUE;
    } else if(m809 == 0 && mStatus != 1 && mStatus < 3) {
        mStatus = 2;
    }
    return TRUE;
}

/* 00002930-00002988       .text wait_2__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::wait_2() {
    if(mStatus != 1 && mStatus < 3) {
        f32 y_diff = dComIfGp_getPlayer(0)->current.pos.y - current.pos.y;
        mStatus = 0;
        if(y_diff > -1.0f) {
            mStatus = 3;
        }
    }
    return TRUE;
}

/* 00002988-00002B2C       .text wait_action1__11daNpc_Gp1_cFPv */
BOOL daNpc_Gp1_c::wait_action1(void*) {
    switch(m819) {
        case 0:
            if(dNpc_chkArasoi()) {
                fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
                setStt(3);
            } else {
                fopAcM_OnStatus(this, fopAcStts_NOCULLEXEC_e);
                setStt(1);
                m7EC = (g_Counter.mCounter0 & 3) + 2;
            }
            m819++;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mPrevStatus) {
                case 1:
                    mbSetEyePos = wait_1();
                    break;
                case 2:
                    mbSetEyePos = talk_1();
                    break;
                case 4:
                    mbSetEyePos = walk_1();
                    break;
                case 5:
                    mbSetEyePos = hair_1();
                    break;
                case 3:
                    mbSetEyePos = wait_2();
                    break;
            }
            if(mStatus != 1 && mStatus < 3) {
                if(!dComIfGs_isEventBit(0x1501) && m809 == 0 && chk_forceTlkArea()) {
                    mStatus = 1;
                }
            }
            lookBack();
            break;
        default:
        case 9:
            break;
    }
    return TRUE;
}

/* Nonmatching */
/* 00002B2C-00002C6C       .text demo__11daNpc_Gp1_cFv */
bool daNpc_Gp1_c::demo() {
    if(demoActorID == 0) {
        if(mbInDemo != 0) {
            mbInDemo = 0;
        }
    } else {
        mbInDemo = 1;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if(m_hed_tex_pttrn) {
            mBlinkFrame += 1;
            if(mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demopattern = demo_actor->getP_BtpData("Gp");
        if(demopattern) {
            m_hed_tex_pttrn = demopattern;
            if(mHeadBtpAnm.init(mpMorf->getModel()->getModelData(), m_hed_tex_pttrn, 1, 2, 1.0f, 0, -1, true, FALSE)) {
                mAnmNum = 1;
                mBlinkFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Gp", 0, 0, 0, 0);
    }
    return mbInDemo;
}

/* Nonmatching */
/* 00002C6C-00002E24       .text _draw__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::_draw() {
    J3DModel* morf_model = mpMorf->getModel();
    J3DModelData* model_data = morf_model->getModelData();

    if(m7FC || m7FF) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model, &tevStr);

    mHeadBtpAnm.entry(model_data, mBlinkFrame);
    mpMorf->entryDL();
    mHeadBtpAnm.remove(model_data);
    dNpc_setShadowModel(mpShadowModel, model_data, morf_model);

    cXyz temp(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowID = dComIfGd_setRealShadow(mShadowID, 1, mpShadowModel, &temp, 800.0f,
                                       current.pos.y - mObjAcch.GetGroundH(), NULL);
    if(mShadowID == 0) {
        dComIfGd_setSimpleShadow(
            &current.pos, mObjAcch.GetGroundH(), 40.0f,
            dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd.GetBgIndex(), mObjAcch.m_gnd.GetPolyIndex())->GetNP(),
            0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
    }

    if(l_HIO.mPrmTbl.m18 != 0) {
        cXyz somevec;
        somevec.x = current.pos.x;
        somevec.y = current.pos.y;
        somevec.z = current.pos.z;
        somevec.y = eyePos.y;
    }
    dSnap_RegistFig(0x5B, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* Nonmatching */
/* 00002E24-00003008       .text _execute__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::_execute() {
    if(!m802) {
        mInitialPos = current.pos;
        mInitialAngle = current.angle;
        m802 = true;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY,
        l_HIO.mPrmTbl.mMinBackboneX, l_HIO.mPrmTbl.mMinBackboneY,
        l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY,
        l_HIO.mPrmTbl.mMaxTurnStep);
    if(m7FC && demoActorID == 0) {
        return TRUE;
    }
    m7FE = false;
    m7FC = false;
    partner_srch();
    checkOrder();
    if(!demo()) {
        s32 cond = -1;
        if(dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            cond = isEventEntry();
        }
        if(cond >= 0) {
            event_proc(cond);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }
        if(!m7FE) {
            gp_nMove();
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if(!m7FD) {
            m78A = current.angle;
            shape_angle = m78A;
        }
    }
    eventOrder();
    setMtx(false);

    if(!mbInDemo) {
        setCollision(70.0f, 230.0f);
    }

    return TRUE;
}

/* 00003008-00003064       .text _delete__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Gp");
#if VERSION > VERSION_DEMO
    if(heap != NULL && mpMorf != NULL)
#else
    if(mpMorf != NULL)
#endif
    {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00003064-00003084       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Gp1_c*>(i_this)->CreateHeap();
}

/* Nonmatching */
/* 00003084-000031A4       .text _create__11daNpc_Gp1_cFv */
cPhs_State daNpc_Gp1_c::_create() {
    static int a_size_tbl[] = {
        0x272E0
    };

    fopAcM_ct_Retail(this, daNpc_Gp1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Gp");
    if(state != cPhs_COMPLEATE_e) {
        return state;
    }
    u32 tmp = fopAcM_GetParam(this) & 0xFF;
    if(!charDecide(tmp)) {
        return cPhs_ERROR_e;
    }
    if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mSpecificType])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -70.0f, -20.0f, -70.0f, 50.0f, 240.0f, 50.0f);
    if(!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

/* 000035D4-00003844       .text create_Anm__11daNpc_Gp1_cFv */
J3DModelData* daNpc_Gp1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Gp", dRes_ID_GP_BDL_GP_e);
    JUT_ASSERT(VERSION_SELECT(0x86F, 0x86F, 0x86F, 0x86F), a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(
            "Gp",
            dRes_ID_GP_BCK_WAIT01_e
        ),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11020022
    );
    if(mpMorf == NULL) {
        return NULL;
    }
    if(mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(VERSION_SELECT(0x883, 0x883, 0x883, 0x883), m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(VERSION_SELECT(0x886, 0x886, 0x886, 0x886), m_bbone_jnt_num >= 0);
    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(VERSION_SELECT(0x889, 0x889, 0x889, 0x889), m_hnd_L_jnt_num >= 0);

    return a_mdl_dat;
}

/* Nonmatching */
/* 00003844-000039A0       .text CreateHeap__11daNpc_Gp1_cFv */
BOOL daNpc_Gp1_c::CreateHeap() {
    J3DModelData* anm_model = create_Anm();
    if(!anm_model) {
        return FALSE;
    }
    mAnmNum = 0;
    if(!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    mpShadowModel = mDoExt_J3DModel__create(anm_model, 0x20000, 0x11020203);
    if(mpShadowModel != NULL) {
        for(u16 i = 0; i < anm_model->getJointNum(); i++) {
            if((i == m_hed_jnt_num) || (i == m_bbone_jnt_num)) {
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Gp1);
            }
        }
        mpMorf->getModel()->setUserArea((u32)this);
        mAcchCir.SetWall(30.0f, 70.0f);
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
    mpMorf = NULL;
    return FALSE;
}

/* 000039A0-000039C0       .text daNpc_Gp1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Gp1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_create();
}

/* 000039C0-000039E0       .text daNpc_Gp1_Delete__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_Delete(daNpc_Gp1_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_delete();
}

/* 000039E0-00003A00       .text daNpc_Gp1_Execute__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_Execute(daNpc_Gp1_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_execute();
}

/* 00003A00-00003A20       .text daNpc_Gp1_Draw__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_Draw(daNpc_Gp1_c* i_this) {
    return ((daNpc_Gp1_c*)i_this)->_draw();
}

/* 00003A20-00003A28       .text daNpc_Gp1_IsDelete__FP11daNpc_Gp1_c */
static BOOL daNpc_Gp1_IsDelete(daNpc_Gp1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Gp1_Method = {
    (process_method_func)daNpc_Gp1_Create,
    (process_method_func)daNpc_Gp1_Delete,
    (process_method_func)daNpc_Gp1_Execute,
    (process_method_func)daNpc_Gp1_IsDelete,
    (process_method_func)daNpc_Gp1_Draw,
};

actor_process_profile_definition g_profile_NPC_GP1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_GP1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Gp1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_GP1_e,
    /* Actor SubMtd */ &l_daNpc_Gp1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
