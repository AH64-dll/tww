/**
 * d_a_npc_pf1.cpp
 * NPC - Windfall - Orca's Pupil (Wandering Kid)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_pf1.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_tama.h"
#include "d/d_com_inf_game.h"
#include "c/c_dylink.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_counter.h"
#include "res/Object/Pf.h"

class daNpc_Pf1_HIO_c : public mDoHIO_entry_c {
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
        /* 0x1A */ s16 m1A;
        /* 0x1C */ s16 m1C;
        /* 0x1E */ s16 m1E;
        /* 0x20 */ f32 m20;
        /* 0x24 */ f32 m24;
        /* 0x28 */ f32 m28;
        /* 0x2C */ f32 m2C;
        /* 0x30 */ f32 m30;
        /* 0x34 */ f32 m34;
        /* 0x38 */ f32 m38;
        /* 0x3C */ f32 m3C;
    };  // Size: 0x40

    daNpc_Pf1_HIO_c();
    virtual ~daNpc_Pf1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

/* 000000EC-00000150       .text __ct__15daNpc_Pf1_HIO_cFv */
daNpc_Pf1_HIO_c::daNpc_Pf1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x2000,
        /* mMaxHeadY         */ 0x38E0,
        /* mMinHeadX         */ 0xEC78,
        /* mMinHeadY         */ 0xC720,
        /* mMaxBackboneX     */ 0x0000,
        /* mMaxBackboneY     */ 0x1C70,
        /* mMinBackboneX     */ 0x0000,
        /* mMinBackboneY     */ 0xE390,
        /* mMaxTurnStep      */ 0x0400,
        /* mCalcAngleTarget  */ 0x0400,
        /* mAttPosOffsetY    */ 70.0f,
        /* m18               */ 0,
        /* m1A               */ 8,
        /* m1C               */ 0x0400,
        /* m1E               */ 0,
        /* m20               */ 1.0f,
        /* m24               */ 0.9f,
        /* m28               */ 0.3f,
        /* m2C               */ 0.2f,
        /* m30               */ 9.5f,
        /* m34               */ 0.6f,
        /* m38               */ 900.0f,
        /* m3C               */ 1050.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static daNpc_Pf1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;



static char* l_evn_tbl[] = {
    "dummy",
};

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_param_1, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Pf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_Head(i_param_1, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-0000030C       .text _nodeCB_Head__11daNpc_Pf1_cFP7J3DNodeP8J3DModel */
void daNpc_Pf1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    /* Nonmatching */
    static cXyz a_eye_pos_off(20.0f, -30.0f, 0.0f);
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mHeadPos.set(mDoMtx_stack_c::get()[0][3], mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mEyePos);
    mDoMtx_stack_c::YrotM(-m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000348-00000394       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_param_1, int i_param_2) {
    if (i_param_2 == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Pf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_BackBone(i_param_1, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000394-0000042C       .text _nodeCB_BackBone__11daNpc_Pf1_cFP7J3DNodeP8J3DModel */
void daNpc_Pf1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    s32 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 0000042C-0000044C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Pf1_c*>(i_this)->CreateHeap();
}

/* 0000044C-000004CC       .text init_PF1_0__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::init_PF1_0() {
    /* Nonmatching */
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)) {
        set_action(&daNpc_Pf1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

/* 000004CC-000006B8       .text createInit__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::createInit() {
    /* Nonmatching */
    mEventIdTable[0] = dComIfGp_evmng_getEventIdx(l_evn_tbl[0], 0xFF);
    mEventCut.setActorInfo2("Pf1", this);
    u8 path_idx = (u8)(fopAcM_GetParam(this) >> 0x10);
    s32 stts_param = 0xFF;
    if (path_idx != 0xFF) {
        mPathRun.setInf(path_idx, fopAcM_GetRoomNo(this), 1);
        if (mPathRun.isPath()) {
            actor_status &= ~fopAcStts_UNK40000_e;
            stts_param = 0xD9;
            set_pthPoint(0);
            goto path_ok;
        }
        return FALSE;
    }
path_ok:
    if (!mPathRun.isPath()) {
        return FALSE;
    }
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.5f;
    m7B6 = 8;
    BOOL init_success;
    if (m7BC != 0) {
        init_success = FALSE;
    } else {
        init_success = init_PF1_0();
    }
    if (!init_success) {
        return FALSE;
    }
    mAngle = current.angle;
    shape_angle = mAngle;
    mStts.Init(stts_param, 0xFF, this);
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

/* 000006B8-00000760       .text play_animation__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::play_animation() {
    /* Nonmatching */
    play_btp_anm();
    u32 mtrl_snd_id = 0;
    if (mObjAcch.m_flags & 0x20) {
        mtrl_snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    m7A0 = mpMorf->play(&eyePos, mtrl_snd_id, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    if (mpMorf->getFrame() < mPrevMorfFrame) {
        m7A0 = 1;
    }
    mPrevMorfFrame = mpMorf->getFrame();
}

/* 00000760-00000810       .text setMtx__11daNpc_Pf1_cFb */
void daNpc_Pf1_c::setMtx(bool i_param_1) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle.x, mAngle.y, mAngle.z);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention(i_param_1);
}

/* 00000810-00000824       .text bckResID__11daNpc_Pf1_cFi */
int daNpc_Pf1_c::bckResID(int i_param_1) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_PF_BCK_WAIT01_e,
        dRes_ID_PF_BCK_WALK01_e,
        dRes_ID_PF_BCK_WALK02_e,
        dRes_ID_PF_BCK_CRY_e,
        dRes_ID_PF_BCK_REGRET_e,
        dRes_ID_PF_BCK_SPIT_e,
        dRes_ID_PF_BCK_WISH_e,
        dRes_ID_PF_BCK_TALK01_e,
    };
    return a_bck_resID_tbl[i_param_1];
}

/* 00000824-00000838       .text btpResID__11daNpc_Pf1_cFi */
int daNpc_Pf1_c::btpResID(int i_param_1) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_PF_BTP_MABA01_e,
        dRes_ID_PF_BTP_MABA01_e,
    };
    return a_btp_resID_tbl[i_param_1];
}

/* 00000838-00000958       .text setBtp__11daNpc_Pf1_cFScb */
bool daNpc_Pf1_c::setBtp(s8 i_btp_num, bool i_param_1) {
    /* Nonmatching */
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    if (i_btp_num < 0) {
        return false;
    }
    J3DAnmTexPattern* a_btp = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes(m_arcname, btpResID(i_btp_num)));
    JUT_ASSERT(0x1CE, a_btp != 0);
    m7B5 = i_btp_num;
    if (m7B5 == 1) {
        mBtpFrame = 2;
    } else {
        mBtpFrame = 0;
    }
    m6EE = 0;
    return mBtpAnm.init(model_data, a_btp, 1, 0, 1.0f, 0, -1, i_param_1, 0) != 0;
}

/* 00000958-00000978       .text init_texPttrnAnm__11daNpc_Pf1_cFScb */
bool daNpc_Pf1_c::init_texPttrnAnm(s8 i_btp_num, bool i_param_1) {
    return setBtp(i_btp_num, i_param_1);
}

/* 00000978-00000A1C       .text play_btp_anm__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::play_btp_anm() {
    /* Nonmatching */
    u8 frame_max = (u8)mBtpAnm.getBtpAnm()->getFrameMax();
    if (m7B5 != 1 && (m7B5 != 0 || cLib_calcTimer(&m6EE) == 0)) {
        mBtpFrame += 1;
        if (mBtpFrame >= frame_max) {
            if (m7B5 != 0) {
                mBtpFrame = frame_max;
            } else {
                m6EE = cLib_getRndValue(0x3C, 0x5A);
                mBtpFrame = 0;
            }
        }
    }
}

/* 00000A1C-00000AB8       .text setAnm_anm__11daNpc_Pf1_cFPQ211daNpc_Pf1_c9anm_prm_c */
void daNpc_Pf1_c::setAnm_anm(daNpc_Pf1_c::anm_prm_c* i_anmPrmP) {
    /* Nonmatching */
    if (i_anmPrmP->mAnmNum >= 0) {
        if (m7B6 == i_anmPrmP->mAnmNum) {
            return;
        }
        dNpc_setAnmIDRes(
            mpMorf,
            i_anmPrmP->mLoopMode,
            i_anmPrmP->mMorf,
            i_anmPrmP->mSpeed,
            bckResID(i_anmPrmP->mAnmNum),
            -1,
            m_arcname
        );
        m7B6 = i_anmPrmP->mAnmNum;
        m7A0 = 0;
        m7A1 = 0;
        mPrevMorfFrame = 0.0f;
    }
}

/* 00000AB8-00000B28       .text setAnm_NUM__11daNpc_Pf1_cFii */
void daNpc_Pf1_c::setAnm_NUM(int i_param_1, int i_param_2) {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[8] = {
        {0, 0, 0, 8, 1, 2},
        {1, 0, 0, 8, 1, 2},
        {2, 0, 0, 8, 1, 2},
        {3, 1, 0, 8, 1, 2},
        {4, 0, 0, 8, 1, 0},
        {5, 0, 0, 8, 1, 0},
        {6, 0, 0, 8, 1, 2},
        {7, 0, 0, 8, 1, 2},
    };
    if (i_param_2 != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[i_param_1].mBtpNum, 1);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param_1]);
}

/* 00000B28-00000B94       .text setAnm__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::setAnm() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[8] = {
        {0xFF, 0xFF, 0, 0, 0, -1},
        {0, 0, 0, 8, 1, 2},
        {0xFF, 0xFF, 0, 0, 0, -1},
        {1, 0, 0, 8, 1, 2},
        {4, 0, 0, 8, 1, 0},
        {0, 0, 0, 4, 0, 2},
        {0, 0, 0, 8, 1, 2},
        {0, 0, 0, 8, 1, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mStt].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* 00000B94-00000B98       .text chngAnmTag__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::chngAnmTag() {}

/* 00000B98-00000B9C       .text ctrlAnmTag__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::ctrlAnmTag() {}

/* 00000B9C-00000BDC       .text chngAnmAtr__11daNpc_Pf1_cFUc */
void daNpc_Pf1_c::chngAnmAtr(u8 i_param_1) {
    /* Nonmatching */
    if (i_param_1 != m7B3) {
        if (i_param_1 > 6) {
            return;
        }
        m7B3 = i_param_1;
        setAnm_ATR();
    }
}

/* 00000BDC-00000C48       .text ctrlAnmAtr__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::ctrlAnmAtr() {
    /* Nonmatching */
    switch (m7B3) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            if (m7A0 != 0) {
                m7A1++;
                if (m7A1 > 2) {
                    m7B3 = 6;
                    setAnm_NUM(0, 1);
                }
            }
            break;
        default:
            break;
    }
}

/* 00000C48-00000CAC       .text setAnm_ATR__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::setAnm_ATR() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[6] = {
        {0, 0, 0, 8, 1, 2},
        {3, 1, 0, 8, 1, 2},
        {5, 0, 0, 8, 1, 0},
        {6, 0, 0, 8, 1, 2},
        {6, 0, 0, 8, 1, 2},
        {7, 0, 0, 8, 1, 2},
    };
    init_texPttrnAnm(a_anm_prm_tbl[m7B3].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[m7B3]);
}

/* 00000CAC-00000D68       .text anmAtr__11daNpc_Pf1_cFUs */
void daNpc_Pf1_c::anmAtr(u16 i_msgStatus) {
    /* Nonmatching */
    switch (i_msgStatus) {
        case 6:
            if (m7BE == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m7BE += 1;
            }
            u8 mesg_anime_tag_info = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if (mesg_anime_tag_info != 0xFF && mesg_anime_tag_info != m7B4) {
                m7B4 = mesg_anime_tag_info;
                chngAnmTag();
            }
            break;
        case 0xE:
            m7BE = 0;
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000D68-00000E60       .text next_msgStatus__11daNpc_Pf1_cFPUl */
u16 daNpc_Pf1_c::next_msgStatus(u32* i_msg_no) {
    /* Nonmatching */
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*i_msg_no) {
        case 0x1B59:
            switch (mpCurrMsg->mSelectNum) {
                case 0:
                    *i_msg_no = 0x1B5A;
                    break;
                case 1:
                    *i_msg_no = 0x1B5D;
                    break;
            }
            m7A5 = 1;
            break;
        case 0x1B5A:
            *i_msg_no = 0x1B61;
            break;
        case 0x1B61:
            *i_msg_no = 0x1B5B;
            break;
        case 0x1B5B:
            *i_msg_no = 0x1B62;
            break;
        case 0x1B62:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B04);
            msg_status = fopMsgStts_MSG_ENDS_e;
            break;
        case 0x1B60:
            m7A4 = 1;
            msg_status = fopMsgStts_MSG_ENDS_e;
            break;
        case 0x1B5C:
            *i_msg_no = 0x1B5F;
            break;
        case 0x1B5E:
            *i_msg_no = 0x1B60;
            break;
        default:
            msg_status = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msg_status;
}

/* 00000E60-00000EC0       .text getMsg_PF1_0__11daNpc_Pf1_cFv */
u32 daNpc_Pf1_c::getMsg_PF1_0() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B04)) {
        return 0x1B5C;
    }
    if (m7A5) {
        return 0x1B5E;
    }
    return 0x1B59;
}

/* 00000EC0-00000EFC       .text getMsg__11daNpc_Pf1_cFv */
u32 daNpc_Pf1_c::getMsg() {
    /* Nonmatching */
    u32 ret = 0;
    if ((s32)m7BC != 0) {
    } else {
        ret = getMsg_PF1_0();
    }
    return ret;
}

/* 00000EFC-00000F88       .text eventOrder__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::eventOrder() {
    s8 cond = m7B7;
    if (cond == 1 || cond == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m7B7 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (cond >= 3) {
        m78A = cond - 3;
        fopAcM_orderOtherEventId(this, mEventIdTable[m78A], 0xFF, 0xFFFF, 0, 1);
    }
}

/* 00000F88-00001044       .text checkOrder__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::checkOrder() {
    /* Nonmatching */
    u16 command = eventInfo.getCommand();
    if (command == 2) {
        if (dComIfGp_evmng_startCheck(mEventIdTable[m78A]) && m7B7 >= 3) {
            switch (m78A) {
                case 0:
                    break;
            }
            m7B7 = 0;
            m7B3 = 0xFF;
            m7B4 = 0xFF;
        }
    } else if (command == 1) {
        if (m7B7 == 1 || m7B7 == 2) {
            m7B7 = 0;
            m7AE = 1;
        }
    }
}

/* 00001044-000010DC       .text chk_talk__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::chk_talk() {
    /* Nonmatching */
    if (dComIfGp_event_chkTalkXY() != 0) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            m7A2 = dComIfGp_event_getPreItemNo();
            return TRUE;
        }
        return FALSE;
    }
    m7A2 = 0xFF;
    return TRUE;
}

/* 000010DC-0000111C       .text chk_parts_notMov__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::chk_parts_notMov() {
    /* Nonmatching */
    return m77E != m_jnt.getHead_y() ||
        m780 != m_jnt.getBackbone_y() ||
        m77C != current.angle.y;
}

/* 0000111C-00001170       .text searchByID__11daNpc_Pf1_cFUiPi */
fopAc_ac_c* daNpc_Pf1_c::searchByID(fpc_ProcID i_procID, int* o_result) {
    fopAc_ac_c* o_actor = NULL;
    *o_result = 0;
    if (fopAcM_SearchByID(i_procID, &o_actor) == 0) {
        *o_result = 1;
    }
    return o_actor;
}

/* 00001170-00001334       .text lookBack__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::lookBack() {
    /* Nonmatching */
    cXyz dst_pos;
    cXyz* dst_pos_p;
    cXyz src_pos;
    s16 desired_yrot;
    u8 head_only_follow;
    m77E = m_jnt.getHead_y();
    m780 = m_jnt.getBackbone_y();
    m77C = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dst_pos.set(0.0f, 0.0f, 0.0f);
    dst_pos_p = NULL;
    desired_yrot = current.angle.y;
    head_only_follow = mHeadOnlyFollow;

    switch (m7BA) {
        case 1:
            mLookTargetPos = dNpc_playerEyePos(-20.0f);
            dst_pos = mLookTargetPos;
            dst_pos_p = &dst_pos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 2:
            dst_pos = mLookTargetPos;
            dst_pos_p = &dst_pos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 3:
            desired_yrot = m79E;
            break;
        case 4:
        {
            int result;
            fopAc_ac_c* actor = searchByID(mTargetProcID, &result);
            if (actor != NULL && result == 0) {
                mLookTargetPos = actor->current.pos;
                mLookTargetPos.y = actor->eyePos.y;
                dst_pos = mLookTargetPos;
                dst_pos_p = &dst_pos;
            }
            break;
        }
    }
    m_jnt.lookAtTarget_2(&current.angle.y, dst_pos_p, src_pos, desired_yrot, l_HIO.mPrmTbl.mCalcAngleTarget, head_only_follow);
}

/* 00001334-000013B4       .text chkAttention__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::chkAttention() {
    /* Nonmatching */
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 000013B4-0000140C       .text setAttention__11daNpc_Pf1_cFb */
void daNpc_Pf1_c::setAttention(bool i_setEyePos) {
    f32 offset = l_HIO.mPrmTbl.mAttPosOffsetY;
    attention_info.position.set(
        mHeadPos.x,
        mHeadPos.y + offset,
        mHeadPos.z
    );
    if (mActionResult != 0 || i_setEyePos) {
        eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    }
}

/* 0000140C-00001494       .text decideType__11daNpc_Pf1_cFi */
BOOL daNpc_Pf1_c::decideType(int i_param_1) {
    /* Nonmatching */
    if (mType > 0) {
        return TRUE;
    }
    mType = 1;
    m7BC = 0;
    strcpy(m_arcname, "Pf");
    BOOL ret = FALSE;
    if (mType != -1 && m7BC != -1) {
        ret = TRUE;
    }
    return ret;
}

/* 00001494-00001534       .text privateCut__11daNpc_Pf1_cFi */
void daNpc_Pf1_c::privateCut(int i_staff_idx) {
    /* Nonmatching */
    static char* a_cut_tbl[] = {
        "DUMMY",
    };
    if (i_staff_idx == -1) {
        return;
    }
    m7B2 = dComIfGp_evmng_getMyActIdx(i_staff_idx, a_cut_tbl, 1, 1, 0);
    if (m7B2 == -1) {
        dComIfGp_evmng_cutEnd(i_staff_idx);
    } else {
        dComIfGp_evmng_getIsAddvance(i_staff_idx);
        dComIfGp_evmng_cutEnd(i_staff_idx);
    }
}

/* 00001534-00001558       .text endEvent__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::endEvent() {
    dComIfGp_event_reset();
    m7B3 = 0xFF;
    m7B4 = 0xFF;
}

/* 00001558-00001590       .text isEventEntry__11daNpc_Pf1_cFv */
int daNpc_Pf1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 00001590-0000161C       .text event_proc__11daNpc_Pf1_cFi */
void daNpc_Pf1_c::event_proc(int i_staff_idx) {
    /* Nonmatching */
    if (dComIfGp_evmng_endCheck(mEventIdTable[m78A])) {
        endEvent();
        return;
    }
    if (!mEventCut.cutProc()) {
        privateCut(i_staff_idx);
    }
}

/* 0000161C-000016C8       .text set_action__11daNpc_Pf1_cFM11daNpc_Pf1_cFPCvPvPv_iPv */
void daNpc_Pf1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    /* Nonmatching */
    if (mProcFunc != i_newProcFunc) {
        if (mProcFunc) {
            m7BD = 9;
            (this->*mProcFunc)(i_argsP);
        }
        mProcFunc = i_newProcFunc;
        m7BD = 0;
        (this->*mProcFunc)(i_argsP);
    }
}

/* 000016C8-0000179C       .text setStt__11daNpc_Pf1_cFSc */
void daNpc_Pf1_c::setStt(s8 i_status) {
    /* Nonmatching */
    s8 prev_stt = mStt;
    mStt = i_status;
    switch (mStt) {
        case 1:
        case 4:
        case 6:
        case 7:
            m7B7 = 0;
            speedF = 0.0f;
            break;
        case 2:
            m7B7 = 0;
            speedF = 0.0f;
            m7B3 = 0xFF;
            m7B4 = 0xFF;
            m7BE = 0;
            m7B9 = prev_stt;
            break;
        case 3:
            m7B7 = 0;
            m798 = cLib_getRndValue(0xB4, 0x5A);
            break;
        case 5:
            m7B7 = 0;
            m796 = 0x1E;
            break;
        case 0:
        default:
            break;
    }
    setAnm();
}

/* 0000179C-00001958       .text createTama__11daNpc_Pf1_cFf */
void daNpc_Pf1_c::createTama(f32 i_param_1) {
    /* Nonmatching */
    csXyz angle(0, 0, 0);
    cXyz eye_pos = eyePos;
    eye_pos.y += 15.0f;
    cXyz player_eye_pos = dNpc_playerEyePos(-20.0f);
    cXyz diff = player_eye_pos - eye_pos;
    f32 mag = std::sqrtf(diff.abs2());
    angle.x = cLib_targetAngleX(&eye_pos, &player_eye_pos);
    angle.y = cLib_targetAngleY(&eye_pos, &player_eye_pos);
    fopAc_ac_c* tama = (fopAc_ac_c*)fopAcM_fastCreate(fpcNm_TAMA_e, 0, &eyePos, fopAcM_GetRoomNo(this), &angle, NULL, -1, NULL);
    if (tama != NULL) {
        static_cast<daTama_c*>(tama)->setPartnerID(fopAcM_GetID(this));
        static_cast<daTama_c*>(tama)->setDis(i_param_1);
        static_cast<daTama_c*>(tama)->setSpd(50.0f);
    }
}

/* 00001958-00001A80       .text chk_areaIN__11daNpc_Pf1_cFf4cXyz */
bool daNpc_Pf1_c::chk_areaIN(f32 i_param_1, cXyz i_param_2) {
    /* Nonmatching */
    cXyz diff = dComIfGp_getLinkPlayer()->current.pos - i_param_2;
    f32 mag = std::sqrtf(diff.abs2XZ());
    BOOL ret = mag < i_param_1;
    if (ret && (g_Counter.mTimer % 3) == 0) {
        createTama(i_param_1);
    }
    return ret;
}

/* 00001A80-00001ACC       .text endEvent_check__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::endEvent_check() {
    /* Nonmatching */
    if (m7A5) {
        return !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B04);
    }
    return FALSE;
}

/* 00001ACC-00001BEC       .text startEvent_check__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::startEvent_check() {
    cXyz pos(mHomePos.x, mHomePos.y + 100.0f, mHomePos.z);
    if (chk_areaIN(l_HIO.mPrmTbl.m38, pos)) {
        cXyz* playerPos = &dComIfGp_getLinkPlayer()->current.pos;
        f32 dist = std::sqrtf(current.pos.abs2(*playerPos));
        if (dist < 210.0f || field_0x6ba != 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 00001BEC-00001C94       .text set_pthPoint__11daNpc_Pf1_cFUc */
void daNpc_Pf1_c::set_pthPoint(u8 i_param_1) {
    if (mPathRun.isPath()) {
        mPathRun.setIdx(i_param_1);
        current.pos = mPathRun.getPoint(mPathRun.getIdx());
        if (mPathRun.nextIdx()) {
            cXyz point = mPathRun.getPoint(mPathRun.getIdx());
            current.angle.y = cLib_targetAngleY(&current.pos, &point);
        }
    }
}

/* 00001C94-00001EAC       .text chk_attn__11daNpc_Pf1_cFv */
bool daNpc_Pf1_c::chk_attn() {
    f32 dist = std::sqrtf((current.pos - dComIfGp_getLinkPlayer()->current.pos).abs2XZ());
    f32 height_diff = current.pos.y - dComIfGp_getLinkPlayer()->current.pos.y;
    s16 target_angle = cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos);
    s16 angle_diff = target_angle - current.angle.y;
    if (m7BA == 1) {
        return dist < 200.0f && (f32)abs(angle_diff) / DEG2S_CONSTANT < 90.0f &&
               std::fabsf(height_diff) < 300.0f;
    } else {
        return dist < 200.0f && (f32)abs(angle_diff) / DEG2S_CONSTANT < 60.0f &&
               std::fabsf(height_diff) < 300.0f;
    }
}

/* 00001EAC-00001F68       .text setBikon__11daNpc_Pf1_cF4cXyz */
void daNpc_Pf1_c::setBikon(cXyz i_param_1) {
    /* Nonmatching */
    delBikon();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    cXyz bikon_pos;
    mDoMtx_stack_c::multVec(&i_param_1, &bikon_pos);
    cXyz zero(0.0f, 0.0f, 0.0f);
    dComIfGp_particle_set(0x8152, &bikon_pos, NULL, NULL, 0xFF, NULL, 0);
}

/* 00001F68-00001F6C       .text delBikon__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::delBikon() {}

/* 00001F6C-00001F74       .text wait_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::wait_1() {
    return TRUE;
}

/* 00001F74-00002030       .text regret__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::regret() {
    /* Nonmatching */
    if (m7AE) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    if (!endEvent_check()) {
        m7B7 = 0;
        if (startEvent_check()) {
            setStt(5);
        }
    } else {
        m7B7 = 2;
    }
    m7BA = 0;
    mHeadOnlyFollow = 1;
    if (m7A0 != 0) {
        setStt(3);
    }
    return TRUE;
}

/* 00002030-00002350       .text attk_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::attk_1() {
    /* Nonmatching */
    cXyz diff = current.pos - dComIfGp_getLinkPlayer()->current.pos;
    f32 dist = std::sqrtf(diff.abs2XZ());
    if (m7AE) {
        if (chk_talk()) {
            setStt(6);
            setStt(2);
        }
        return TRUE;
    }
    m7BA = 0;
    mHeadOnlyFollow = 1;
    if (m7B6 == 0) {
        if (m798 == 0) {
            s16 target_angle = cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos);
            cLib_addCalcAngleS(&current.angle.y, target_angle, 4, 0x1000, 0x80);
            if (abs((s16)(current.angle.y - target_angle)) < 0x800) {
                cXyz bikon(0.0f, -40.0f, 60.0f);
                JAIZelBasic::zel_basic->seStart(0x58BD, &current.pos, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
                setBikon(bikon);
                m798 = 0x14;
            }
        } else if (cLib_calcTimer(&m798) == 0) {
            setAnm_NUM(2, 1);
        }
        return TRUE;
    }
    if (m7B7 != 1 && dist < 200.0f) {
        m7B7 = 1;
    }
    if (cLib_calcTimer(&m796) == 0) {
        cXyz pos = mHomePos;
        if (!chk_areaIN(l_HIO.mPrmTbl.m3C, pos)) {
            setStt(6);
            return TRUE;
        }
    }
    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos), l_HIO.mPrmTbl.m1A, l_HIO.mPrmTbl.m1C, 0x80);
    cLib_chaseF(&speedF, l_HIO.mPrmTbl.m30, l_HIO.mPrmTbl.m34);
    f32 play_speed = speedF * l_HIO.mPrmTbl.m2C;
    if (play_speed < 0.5f) {
        play_speed = 0.5f;
    }
    mpMorf->setPlaySpeed(play_speed);
    return TRUE;
}

/* 00002350-000025D0       .text walk_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::walk_1() {
    /* Nonmatching */
    if (!mPathRun.isPath()) {
        return TRUE;
    }
    if (dPath_ChkClose(mPathRun.getPath())) {
        if (mPathRun.chkPointPass(current.pos, mPathRun.getDir())) {
            mPathRun.nextIdxAuto();
        }
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &point), l_HIO.mPrmTbl.m1A, l_HIO.mPrmTbl.m1C, 0x80);
        f32 target_speed = l_HIO.mPrmTbl.m24;
        if (cLib_calcTimer(&m798) == 0 || m7AE) {
            target_speed = 0.0f;
        }
        if (!endEvent_check() && startEvent_check()) {
            speedF = 0.0f;
            m798 = 0;
            setStt(5);
            m7BA = 0;
            mHeadOnlyFollow = 1;
            return TRUE;
        }
        cLib_chaseF(&speedF, target_speed, l_HIO.mPrmTbl.m28);
        f32 play_speed = speedF * l_HIO.mPrmTbl.m20;
        if (play_speed < 0.5f) {
            play_speed = 0.5f;
        }
        mpMorf->setPlaySpeed(play_speed);
        if ((int)(0.5f + target_speed) == 0 && (int)speedF == 0) {
            if (m7AE) {
                if (chk_talk()) {
                    setStt(2);
                }
                return TRUE;
            }
            setStt(4);
            return TRUE;
        }
        m7B7 = 0;
        if (endEvent_check()) {
            m7B7 = 2;
        }
        m7BA = 0;
        mHeadOnlyFollow = 1;
    }
    return TRUE;
}

/* 000025D0-000026E4       .text wait_2__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::wait_2() {
    /* Nonmatching */
    if (m7AE) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }
    cXyz pos = mHomePos;
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B04) || !chk_areaIN(l_HIO.mPrmTbl.m3C, pos)) {
        mPathRun.setNearPathIndx(&current.pos, 0.0f);
        setStt(3);
        return TRUE;
    }
    m7B7 = 2;
    mHeadOnlyFollow = 1;
    if (chk_attn()) {
        m7BA = 1;
        return TRUE;
    }
    m7BA = 0;
    return TRUE;
}

/* 000026E4-00002874       .text wait_3__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::wait_3() {
    /* Nonmatching */
    cXyz diff = current.pos - dComIfGp_getLinkPlayer()->current.pos;
    f32 dist = std::sqrtf(diff.abs2XZ());
    if (m7AE) {
        if (chk_talk()) {
            setStt(2);
            m7B0 = 0;
        }
        return TRUE;
    }
    m7B0 = dist > 300.0f;
    if (m7B0) {
        setStt(3);
        m7BA = 0;
        mHeadOnlyFollow = 1;
        return TRUE;
    }
    m7B7 = 2;
    mHeadOnlyFollow = 1;
    if (chk_attn()) {
        m7BA = 1;
        return TRUE;
    }
    m7BA = 0;
    return TRUE;
}

/* 00002874-00002980       .text talk_1__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::talk_1() {
    /* Nonmatching */
    u8 ret = chk_parts_notMov();
    cLib_addCalcAngleS(&current.angle.y, cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos), 4, l_HIO.mPrmTbl.mCalcAngleTarget, 0x80);
    u16 talk_status = talk(1);
    if (mpCurrMsg == NULL) {
        return TRUE;
    }
    if (talk_status == fopMsgStts_CLOSE_WAIT_e && m7A0 != 0 && mCurrMsgNo == 0x1B60) {
        fopMsgM_messageSendOn();
    }
    switch (mpCurrMsg->mStatus) {
        case fopMsgStts_BOX_OPENING_e:
        case fopMsgStts_MSG_TYPING_e:
            break;
        case fopMsgStts_MSG_DESTROYED_e:
            m7A2 = 0xFF;
            m7AE = 0;
            setStt(m7B9);
            endEvent();
            break;
    }
    return ret;
}

/* 00002980-00002A8C       .text wait_action1__11daNpc_Pf1_cFPv */
BOOL daNpc_Pf1_c::wait_action1(void*) {
    /* Nonmatching */
    switch (m7BD) {
        case 0:
            setStt(3);
            m7BD++;
            break;
        case 1:
        case 2:
        case 3:
            mActNo = chkAttention();
            switch (mStt) {
                case 1:
                    mActionResult = wait_1();
                    break;
                case 2:
                    mActionResult = talk_1();
                    break;
                case 3:
                    mActionResult = walk_1();
                    break;
                case 4:
                    mActionResult = regret();
                    break;
                case 5:
                    mActionResult = attk_1();
                    break;
                case 6:
                    mActionResult = wait_2();
                    break;
                case 7:
                    mActionResult = wait_3();
                    break;
            }
            break;
        case 9:
        default:
            break;
    }
    return TRUE;
}

/* 00002A8C-00002BCC       .text demo__11daNpc_Pf1_cFv */
u8 daNpc_Pf1_c::demo() {
    /* Nonmatching */
    if (demoActorID == 0) {
        if (m7B1 != 0) {
            m7B1 = 0;
        }
    } else {
        if (m7B1 == 0) {
            m7B1 = 1;
            mAnmAtr = 0;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        J3DAnmTexPattern* btp_anm = mBtpAnm.getBtpAnm();
        if (btp_anm != NULL) {
            u8 frame_max = (u8)btp_anm->getFrameMax();
            mBtpFrame += 1;
            if (mBtpFrame >= frame_max) {
                mBtpFrame = frame_max;
            }
        }
        J3DAnmTexPattern* demo_pattern = demo_actor->getP_BtpData(m_arcname);
        if (demo_pattern != NULL) {
            if (mBtpAnm.init(mpMorf->getModel()->getModelData(), demo_pattern, 1, 0, 1.0f, 0, -1, 1, 0)) {
                m7B5 = 2;
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, m_arcname, 0, NULL, 0, 0);
    }
    return m7B1;
}

/* 00002BCC-00002C5C       .text shadowDraw__11daNpc_Pf1_cFv */
void daNpc_Pf1_c::shadowDraw() {
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
}

/* 00002C5C-00002D30       .text _draw__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::_draw() {
    J3DModel* morf_model = mpMorf->getModel();
    J3DModelData* model_data = morf_model->getModelData();
    if (m7A8 != 0 || mAnmTag != 0) {
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model, &tevStr);
    mBtpAnm.entry(model_data, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK5B, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002D30-00002F94       .text _execute__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::_execute() {
    /* Nonmatching */
    if (m7AC == 0) {
        mHomePos = current.pos;
        m718 = current.angle.x;
        m71A = current.angle.y;
        m71C = current.angle.z;
        m7AC = 1;
    }
    m_jnt.setParam(
        l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY,
        l_HIO.mPrmTbl.mMinBackboneX, l_HIO.mPrmTbl.mMinBackboneY,
        l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
        l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY,
        l_HIO.mPrmTbl.mMaxTurnStep
    );
    if (m7A8 != 0 && demoActorID == 0) {
        return TRUE;
    }
    checkOrder();
    if (!demo()) {
        s32 cond = -1;
        if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            cond = isEventEntry();
        }
        if (cond >= 0) {
            event_proc(cond);
        } else {
            (this->*mProcFunc)(NULL);
        }
        field_0x6ba = 0;
        lookBack();
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        if (mObjAcch.GetGroundH() != -G_CM3D_F_INF) {
            cM3dGPla* tri_pla = dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd);
            if (tri_pla != NULL) {
                mObjAcchNormal = tri_pla->mNormal;
            }
        }
        play_animation();
    } else {
        m7A8 = 0;
    }
    eventOrder();
    mAngle.x = current.angle.x;
    mAngle.y = current.angle.y;
    mAngle.z = current.angle.z;
    if (mAnmAtr == 0) {
        shape_angle.x = current.angle.x;
        shape_angle.y = current.angle.y;
        shape_angle.z = current.angle.z;
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);
    if (m7B1 == 0) {
        setCollision(100.0f, 200.0f);
    }
    return TRUE;
}

/* 00002F94-00002FF8       .text _delete__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::_delete() {
    cDyl_Unlink(fpcNm_TAMA_e);
    dComIfG_resDelete(&mPhs, m_arcname);
    delBikon();
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00002FF8-00003258       .text _create__11daNpc_Pf1_cFv */
cPhs_State daNpc_Pf1_c::_create() {
    /* Nonmatching */
    static int a_size_tbl[] = {
        0,
        0,
    };
    fopAcM_ct_Retail(this, daNpc_Pf1_c);
    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    cPhs_State state = dComIfG_resLoad(&mPhs, m_arcname);
    mCreatePhase = state == cPhs_COMPLEATE_e;
    if (!mCreatePhase) {
        return state;
    }
    cPhs_State link_state = cDyl_LinkASync(fpcNm_TAMA_e);
    if (link_state != cPhs_COMPLEATE_e) {
        return link_state;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mType])) {
        return cPhs_ERROR_e;
    }
    cullMtx = mpMorf->getModel()->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, -100.0f, -20.0f, -80.0f, 100.0f, 180.0f, 140.0f);
    cPhs_State result = cPhs_ERROR_e;
    if (createInit()) {
        result = state;
    }
    return result;
}

/* 00003524-00003798       .text bodyCreateHeap__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::bodyCreateHeap() {
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(m_arcname, dRes_ID_PF_BDL_PF_e);
    JUT_ASSERT(0x803, a_mdl_dat != 0);
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
    if (init_texPttrnAnm(0, 0) == 0) {
        mpMorf = NULL;
        return FALSE;
    }
    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x817, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone1");
    JUT_ASSERT(0x819, m_bbone_jnt_num >= 0);
    a_mdl_dat->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    a_mdl_dat->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((u32)this);
    return TRUE;
}

/* 00003798-0000381C       .text CreateHeap__11daNpc_Pf1_cFv */
BOOL daNpc_Pf1_c::CreateHeap() {
    /* Nonmatching */
    if (bodyCreateHeap() == 0) {
        return FALSE;
    }
    mAcchCir.SetWall(30.0f, 100.0f);
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

/* 0000381C-0000383C       .text daNpc_Pf1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Pf1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_create();
}

/* 0000383C-0000385C       .text daNpc_Pf1_Delete__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_Delete(daNpc_Pf1_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_delete();
}

/* 0000385C-0000387C       .text daNpc_Pf1_Execute__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_Execute(daNpc_Pf1_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_execute();
}

/* 0000387C-0000389C       .text daNpc_Pf1_Draw__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_Draw(daNpc_Pf1_c* i_this) {
    return ((daNpc_Pf1_c*)i_this)->_draw();
}

/* 0000389C-000038A4       .text daNpc_Pf1_IsDelete__FP11daNpc_Pf1_c */
static BOOL daNpc_Pf1_IsDelete(daNpc_Pf1_c*) {
    return TRUE;
}

static void dummy() {
    const GXColor dummy1 = { 0x00, 0xFF, 0x00, 0x80 };
    const GXColor dummy2 = { 0xFF, 0xFF, 0x00, 0x80 };
    const GXColor dummy3 = { 0xFF, 0x00, 0x00, 0x80 };
    const GXColor dummy4 = { 0x00, 0x00, 0xFF, 0x80 };
}

static actor_method_class l_daNpc_Pf1_Method = {
    (process_method_func)daNpc_Pf1_Create,
    (process_method_func)daNpc_Pf1_Delete,
    (process_method_func)daNpc_Pf1_Execute,
    (process_method_func)daNpc_Pf1_IsDelete,
    (process_method_func)daNpc_Pf1_Draw,
};

actor_process_profile_definition g_profile_NPC_PF1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_PF1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Pf1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_PF1_e,
    /* Actor SubMtd */ &l_daNpc_Pf1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
