/**
 * d_a_npc_kk1.cpp
 * NPC - Mila (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kk1.h"
#include "d/actor/d_a_swc00.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_bg_s.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor_mng.h"

/* 000000EC-00000150       .text __ct__15daNpc_Kk1_HIO_cFv */
daNpc_Kk1_HIO_c::daNpc_Kk1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX        */ 0x2000,
        /* mMaxHeadY        */ 0x251C,
        /* mMinHeadX        */ 0xE002,
        /* mMinHeadY        */ 0xDAE4,
        /* mMaxBackboneX    */ 0x0000,
        /* mMaxBackboneY    */ 0x2AF8,
        /* mMinBackboneX    */ 0x0000,
        /* mMinBackboneY    */ 0xD508,
        /* mMaxTurnStep     */ 0x0640,
        /* mCalcAngleTarget */ 0x04B0,
        /* mAttPosOffsetY   */ 150.0f,
        /* m18              */ 0x0000,
        /* m1A              */ 0x00D2,
        /* m1C              */ 0x0028,
        /* m1E              */ 0x005A,
        /* m20              */ 0x001E,
        /* m22              */ 0x0014,
        /* m24              */ 0x0004,
        /* m26              */ 0x1000,
        /* m28              */ 40.0f,
        /* m2C              */ 3.0f,
        /* m30              */ 0.2f,
        /* m34              */ 0.5f,
        /* m38              */ 13.0f,
        /* m3C              */ 1.0f,
        /* m40              */ 0.1f,
        /* m44              */ 10.0f,
        /* m48              */ 1.0f,
        /* m4C              */ 0.2f,
        /* m50              */ 1000.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

static const char* l_evn_tbl[8] = {
    "run_start",
    "run_start_2",
    "catch",
    "get_empty_btl",
    "bye",
    "otoboke",
    "runaway",
    "bye_2",
};

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param) {

    if(i_param == 0) {
        daNpc_Kk1_c* actor = (daNpc_Kk1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_Head(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-00000304       .text _nodeCB_Head__11daNpc_Kk1_cFP7J3DNodeP8J3DModel */
void daNpc_Kk1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {
    /* Nonmatching */
    static cXyz a_eye_pos_off(14.0f, 18.0f, 0.0f);
    J3DJoint* jnt_p = ((J3DJoint*)(i_node));
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jnt_no));
    mDoMtx_stack_c::multVecZero(&field_0x750);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000340-0000038C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param) {
    
    if(i_param == 0) {
        daNpc_Kk1_c* actor = (daNpc_Kk1_c*)j3dSys.getModel()->getUserArea();
        if(actor != NULL) {
            actor->_nodeCB_BackBone(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000038C-0000042C       .text _nodeCB_BackBone__11daNpc_Kk1_cFP7J3DNodeP8J3DModel */
void daNpc_Kk1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {
    
    J3DJoint* jnt_p = ((J3DJoint*)(i_node));
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 0000042C-0000044C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Kk1_c*)i_this)->CreateHeap();
}

static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

static daNpc_Kk1_HIO_c l_HIO;

/* 0000044C-000004EC       .text searchActor_SWC00__FPvPv */
static void* searchActor_SWC00(void* i_actor, void* i_this) {
    if(l_check_wrk < 20) {
        if(fopAcM_IsActor(i_actor)) {
            if(fopAcM_GetName(i_actor) == fpcNm_SWC00_e) {
                if(daSwc00_getType((swc00_class*)i_actor) == 0) {
                    if(daSwc00_getSw1No((swc00_class*)i_actor) ==
                       ((daNpc_Kk1_c*)i_this)->getSWbit()) {
                        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
                        l_check_wrk++;
                    }
                }
            }
        }
    }
    return NULL;
}

/* 000004EC-00000598       .text init_KK1_0__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::init_KK1_0() {
    /* Nonmatching */
    if (dComIfGs_isEventBit(0x2D01) && (!dKy_daynight_check() || !dComIfGs_isEventBit(0x0E08))) {
        set_action(&daNpc_Kk1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* 00000598-000007B0       .text createInit__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::createInit() {
    /* Nonmatching */

    for(int i = 0; i < ARRAY_SIZE(l_evn_tbl); i++) {
        mEventIDTbl[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }

    mEventCut.setActorInfo2("Kk1", this);
    m7B5 = (fopAcM_GetParam(this) >> 8) & 0xFF;

    u8 pathIdx = (fopAcM_GetParam(this) >> 0x10) & 0xFF;
    if(pathIdx != 0xFF) {
        if(!mPathRun.setInf(pathIdx, current.roomNo, 1)) {
            return false;
        }
        fopAcM_OffStatus(this, fopAcStts_NODRAW_e);
        set_pthPoint(0);
    }

    if(!mPathRun.isPath()) {
        return false;
    }

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    switch(m820) {
        case 0:
            break;
    }

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.5f;
    mBckNum = 12;
    bool ret;
    switch(m820) {
        case 0:
            ret = init_KK1_0();
            break;
        default:
            ret = false;
    }
    if(!ret) {
        return false;
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
    return true;
}

/* 000007B0-00000918       .text play_animation__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::play_animation() {
    /* Nonmatching */

    u32 snd_id = 0;
    play_btp_anm();
    if(mObjAcch.ChkGroundHit()) {
        snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    mbMorfAnimStopped = mpMorf->play(
        &eyePos,
        snd_id,
        dComIfGp_getReverb(current.roomNo)
    );

    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = true;
    }
    mPrevMorfFrame = mpMorf->getFrame();

    switch(mBckNum) {
        case 8:
            if(mpMorf->checkFrame(4.0f)) {
                setBikon(cXyz(0.0f, -50.0f, -15.0f));
            }
            break;
        case 9:
            if(mpMorf->checkFrame(4.0f)) {
                setBikon(cXyz(0.0f, -50.0f, 0.0f));
            }
            break;
    }
    play_eff_anm();
}

/* 00000918-00000A98       .text setMtx__11daNpc_Kk1_cFb */
void daNpc_Kk1_c::setMtx(bool i_setEyePos) {


    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    cXyz l_off(0.0f, 120.0f, 30.0f);
    mBckAnm.entry(mpModelEff->getModelData(), (f32)m804);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::transM(l_off.x, l_off.y, l_off.z);
    mpModelEff->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModelEff->calc();
    mBckAnm.remove(mpModelEff->getModelData());
    flwAse();
    setAttention(i_setEyePos);
}

/* 00000A98-00000AAC       .text bckResID__11daNpc_Kk1_cFi */
int daNpc_Kk1_c::bckResID(int i_idx) {

    static const int a_resID_tbl[12] = {
        0x00000009, 0x0000000A, 0x0000000B, 0x0000000C,
        0x00000004, 0x00000005, 0x00000006, 0x00000007,
        0x00000001, 0x00000002, 0x00000003, 0x00000008,
    };
    return a_resID_tbl[i_idx];
}

/* 00000AAC-00000AC0       .text btpResID__11daNpc_Kk1_cFi */
int daNpc_Kk1_c::btpResID(int i_idx) {

    static const int a_resID_tbl[1] = {
        0x00000011,
    };
    return a_resID_tbl[i_idx];
}

/* 00000AC0-00000BC4       .text setBtp__11daNpc_Kk1_cFScb */
bool daNpc_Kk1_c::setBtp(s8 i_btpNum, bool i_bModify) {


    J3DModel* morf_model_p = mpMorf->getModel();
    if(i_btpNum < 0) {
        return false;
    }
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern *)dComIfG_getObjectIDRes(mArcName, btpResID(i_btpNum));
    JUT_ASSERT(564, a_btp != NULL);
    mBtpNum = i_btpNum;
    mBtpFrame = 0;
    mTimer1 = 0;

    return mBtpAnm.init(
        morf_model_p->getModelData(),
        a_btp,TRUE,
        J3DFrameCtrl::EMode_NONE,
        1.0f, 0, -1,
        i_bModify, 0
    ) != 0;
}

/* 00000BC4-00000BE4       .text init_texPttrnAnm__11daNpc_Kk1_cFScb */
bool daNpc_Kk1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {
    return setBtp(i_btpNum, i_bModify);
}

/* 00000BE4-00000C80       .text play_btp_anm__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::play_btp_anm() {

    u8 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
    if(mBtpNum != 0 || cLib_calcTimer(&mTimer1) == 0) {
        mBtpFrame++;
        if(mBtpFrame >= frame_max) {
            if(mBtpNum != 0) {
                mBtpFrame = frame_max;
            } else {
                mTimer1 = cLib_getRndValue(0x3C, 0x5A);
                mBtpFrame = 0;
            }
        }
    }
}

/* 00000C80-00000CFC       .text play_eff_anm__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::play_eff_anm() {
    /* Nonmatching */
    m800++;
    if(m800 >= 0x1E) {
        m800 = 0x1D;
    }

    s16 frameMax1 = mBtkAnm.getBtkAnm()->getFrameMax();
    m802++;
    if(m802 >= frameMax1) {
        m802 = frameMax1 - 1;
    }

    s16 frameMax2 = mBckAnm.getBckAnm()->getFrameMax();
    m804++;
    if(m804 >= frameMax2) {
        m804 = 0x3B;
    }
}

/* 00000CFC-00000DDC       .text setAnm_anm__11daNpc_Kk1_cFPQ211daNpc_Kk1_c9anm_prm_c */
void daNpc_Kk1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    /* Nonmatching */

    if(i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf,
        i_anmPrmP->loopMode,
        i_anmPrmP->morf,
        i_anmPrmP->speed,
        bckResID(i_anmPrmP->bckNum),
        -1,
        mArcName
    );
    mBckNum = i_anmPrmP->bckNum;
    delBikon();
    delAse();
    m7BE = 1;
    if(mBckNum == 1) {
        setAse();
        m804 = 0;
        m802 = 0;
        m800 = 0;
        m7BE = 0;
    }
    mbMorfAnimStopped = 0;
    field_0x7B3 = 0;
    mPrevMorfFrame = 0.0f;
}

/* 00000DDC-00000E4C       .text setAnm_NUM__11daNpc_Kk1_cFii */
void daNpc_Kk1_c::setAnm_NUM(int i_anmIdx, int i_bModify) {
    /* Nonmatching */

    static daNpc_Kk1_c::anm_prm_c a_anm_prm_tbl[14] = {
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {7, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {8, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {9, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0xA, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0xB, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0, 0, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NONE},
        {0, 0, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NONE},
    };

    if(i_bModify != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmIdx].btpNum, 1);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmIdx]);
}

/* 00000E4C-00000EB8       .text setAnm__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::setAnm() {
    /* Nonmatching */

    static daNpc_Kk1_c::anm_prm_c a_anm_prm_tbl[8] = {
        {-1, -1, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {3, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmIdx].btpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[mAnmIdx]);
}

/* 00000EB8-00000EBC       .text chngAnmTag__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::chngAnmTag() {
}

/* 00000EBC-00000EC0       .text ctrlAnmTag__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::ctrlAnmTag() {
}

/* 00000EC0-00000FA0       .text chngAnmAtr__11daNpc_Kk1_cFUc */
void daNpc_Kk1_c::chngAnmAtr(unsigned char i_atr) {
    /* Nonmatching */

    if(mCurrMsgNo == 0x1CAC) {
        int param;
        fopAc_ac_c* actor = searchByID(mProcId1, &param);
        if(actor != NULL && param == 0) {
            mPlayerEyePos.x = actor->current.pos.x;
            mPlayerEyePos.y = actor->current.pos.y;
            mPlayerEyePos.z = actor->current.pos.z;
            mPlayerEyePos.y = mPlayerEyePos.y + 200.0f + l_HIO.mPrmTbl.mAttPosOffsetY;
            m81E = 2;
            m7C4 = 1;
            field_0x7A2 = l_HIO.mPrmTbl.m22;
        }
    }
    if(i_atr != mAnmAtr && i_atr <= 0xD) {
        mAnmAtr = i_atr;
        setAnm_ATR();
    }
}

/* 00000FA0-00001080       .text ctrlAnmAtr__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::ctrlAnmAtr() {
    /* Nonmatching */

    switch(mAnmAtr) {
        case 8:
            if(mbMorfAnimStopped != 0) {
                current.angle.y += 0x8000;
                setAnm_NUM(0, 1);
                mpMorf->setMorf(0.0f);
                mAnmAtr = 0;
            }
            break;
        case 0xA:
            if(mbMorfAnimStopped != 0) {
                setAnm_NUM(0, 1);
                mAnmAtr = 0;
            }
            break;
        case 0xB:
            if(mbMorfAnimStopped != 0) {
                setAnm_NUM(6, 1);
                mAnmAtr = 6;
            }
            break;
    }
}

/* 00001080-000010E4       .text setAnm_ATR__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::setAnm_ATR() {
    /* Nonmatching */

    static daNpc_Kk1_c::anm_prm_c a_anm_prm_tbl[13] = {
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {7, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {8, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {9, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0xA, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0xA, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {0xB, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].btpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 000010E4-000011A0       .text anmAtr__11daNpc_Kk1_cFUs */
void daNpc_Kk1_c::anmAtr(unsigned short i_status) {


    switch(i_status) {
        case 6:
            if(m822 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m822++;
            }
            {
                u8 tag = dComIfGp_getMesgAnimeTagInfo();
                if(tag != 0xFF && tag != m818) {
                    dComIfGp_clearMesgAnimeTagInfo();
                    m818 = tag;
                    chngAnmTag();
                }
            }
            break;
        case 0xE:
            m822 = 0;
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 000011A0-0000149C       .text next_msgStatus__11daNpc_Kk1_cFPUl */
u16 daNpc_Kk1_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 0000149C-00001534       .text getMsg_KK1_0__11daNpc_Kk1_cFv */
u32 daNpc_Kk1_c::getMsg_KK1_0() {
    /* Nonmatching */
}

/* 00001534-00001570       .text getMsg__11daNpc_Kk1_cFv */
u32 daNpc_Kk1_c::getMsg() {
    /* Nonmatching */
}

/* 00001570-000015FC       .text eventOrder__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::eventOrder() {
    /* Nonmatching */
}

/* 000015FC-000016DC       .text checkOrder__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::checkOrder() {
    /* Nonmatching */
}

/* 000016DC-00001774       .text chk_talk__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chk_talk() {
    /* Nonmatching */
}

/* 00001774-000017B4       .text chk_parts_notMov__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chk_parts_notMov() {
    /* Nonmatching */
}

/* 000017B4-00001808       .text searchByID__11daNpc_Kk1_cFUiPi */
fopAc_ac_c* daNpc_Kk1_c::searchByID(fpc_ProcID, int*) {
    /* Nonmatching */
}

/* 00001808-000018B8       .text partner_search_sub__11daNpc_Kk1_cFPFPvPv_Pv */
void daNpc_Kk1_c::partner_search_sub(void* (*)(void*, void*)) {
    /* Nonmatching */
}

/* 000018B8-00001924       .text partner_search__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::partner_search() {
    /* Nonmatching */
}

/* 00001924-00001B10       .text lookBack__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::lookBack() {
    /* Nonmatching */
}

/* 00001B10-00001B90       .text chkAttention__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chkAttention() {
    /* Nonmatching */
}

/* 00001B90-00001BE8       .text setAttention__11daNpc_Kk1_cFb */
void daNpc_Kk1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 00001BE8-00001C70       .text decideType__11daNpc_Kk1_cFi */
bool daNpc_Kk1_c::decideType(int) {
    /* Nonmatching */
}

/* 00001C70-00001D10       .text cut_init_RUN_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUN_START(int) {
    /* Nonmatching */
}

/* 00001D10-00001DD0       .text cut_move_RUN_START__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_RUN_START() {
    /* Nonmatching */
}

/* 00001DD0-00001E58       .text cut_init_RUN__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUN(int) {
    /* Nonmatching */
}

/* 00001E58-00001EAC       .text cut_move_RUN__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_RUN() {
    /* Nonmatching */
}

/* 00001EAC-00001F08       .text cut_init_CATCH_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_CATCH_START(int) {
    /* Nonmatching */
}

/* 00001F08-00001F2C       .text cut_move_CATCH_START__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_CATCH_START() {
    /* Nonmatching */
}

/* 00001F2C-00001FAC       .text cut_init_CATCH_END__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_CATCH_END(int) {
    /* Nonmatching */
}

/* 00001FAC-00001FB4       .text cut_move_CATCH_END__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_CATCH_END() {
    /* Nonmatching */
}

/* 00001FB4-000022BC       .text cut_init_TRN__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_TRN(int) {
    /* Nonmatching */
}

/* 000022BC-00002364       .text cut_move_TRN__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_TRN() {
    /* Nonmatching */
}

/* 00002364-00002388       .text cut_init_BYE_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_BYE_START(int) {
    /* Nonmatching */
}

/* 00002388-00002390       .text cut_move_BYE_START__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_BYE_START() {
    /* Nonmatching */
}

/* 00002390-00002490       .text cut_init_BYE__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_BYE(int) {
    /* Nonmatching */
}

/* 00002490-00002568       .text cut_move_BYE__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_BYE() {
    /* Nonmatching */
}

/* 00002568-000025C8       .text cut_init_BYE_CONTINUE__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_BYE_CONTINUE(int) {
    /* Nonmatching */
}

/* 000025C8-00002620       .text cut_move_BYE_CONTINUE__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_BYE_CONTINUE() {
    /* Nonmatching */
}

/* 00002620-000026BC       .text cut_init_BYE_END__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_BYE_END(int) {
    /* Nonmatching */
}

/* 000026BC-000026C4       .text cut_move_BYE_END__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_BYE_END() {
    /* Nonmatching */
}

/* 000026C4-000026C8       .text cut_init_PLYER_TRN__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_PLYER_TRN(int) {

}

/* 000026C8-000026D0       .text cut_move_PLYER_TRN__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_PLYER_TRN() {
    /* Nonmatching */
}

/* 000026D0-00002744       .text cut_init_OTOBOKE__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_OTOBOKE(int) {
    /* Nonmatching */
}

/* 00002744-00002798       .text cut_move_OTOBOKE__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_OTOBOKE() {
    /* Nonmatching */
}

/* 00002798-000028A4       .text cut_init_PLYER_MOV__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_PLYER_MOV(int) {
    /* Nonmatching */
}

/* 000028A4-000028AC       .text cut_move_PLYER_MOV__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_PLYER_MOV() {
    /* Nonmatching */
}

/* 000028AC-00002A40       .text cut_init_RUNAWAY_START__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUNAWAY_START(int) {
    /* Nonmatching */
}

/* 00002A40-00002AD0       .text cut_move_RUNAWAY_START__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_RUNAWAY_START() {
    /* Nonmatching */
}

/* 00002AD0-00002B08       .text cut_init_RUNAWAY_END__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::cut_init_RUNAWAY_END(int) {
    /* Nonmatching */
}

/* 00002B08-00002B10       .text cut_move_RUNAWAY_END__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::cut_move_RUNAWAY_END() {
    /* Nonmatching */
}

/* 00002B10-00002D98       .text privateCut__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::privateCut(int) {
    /* Nonmatching */
}

/* 00002D98-00002DBC       .text endEvent__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::endEvent() {
    /* Nonmatching */
}

/* 00002DBC-00002DF4       .text isEventEntry__11daNpc_Kk1_cFv */
int daNpc_Kk1_c::isEventEntry() {
    /* Nonmatching */
}

/* 00002DF4-00002F80       .text event_proc__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00002F80-00002FB8       .text checkCommandTalk__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::checkCommandTalk() {
    /* Nonmatching */
}

/* 00002FB8-00003064       .text set_action__11daNpc_Kk1_cFM11daNpc_Kk1_cFPCvPvPv_iPv */
bool daNpc_Kk1_c::set_action(ProcFunc, void*) {
    /* Nonmatching */
}

/* 00003064-0000311C       .text setStt__11daNpc_Kk1_cFSc */
void daNpc_Kk1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 0000311C-000032D8       .text createTama__11daNpc_Kk1_cFf */
void daNpc_Kk1_c::createTama(float) {
    /* Nonmatching */
}

/* 000032D8-0000345C       .text chk_areaIN__11daNpc_Kk1_cFf4cXyz */
void daNpc_Kk1_c::chk_areaIN(float, cXyz) {
    /* Nonmatching */
}

/* 0000345C-00003578       .text startEvent_check__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::startEvent_check() {
    /* Nonmatching */
}

/* 00003578-00003600       .text chkHitPlayer__11daNpc_Kk1_cFv */
bool daNpc_Kk1_c::chkHitPlayer() {
    /* Nonmatching */
}

/* 00003600-000036A8       .text set_pthPoint__11daNpc_Kk1_cFUc */
void daNpc_Kk1_c::set_pthPoint(unsigned char) {
    /* Nonmatching */
}

/* 000036A8-00003940       .text event_move__11daNpc_Kk1_cFb */
BOOL daNpc_Kk1_c::event_move(bool) {
    /* Nonmatching */
}

/* 00003940-000039F0       .text kyoroPos__11daNpc_Kk1_cFi */
void daNpc_Kk1_c::kyoroPos(int) {
    /* Nonmatching */
}

/* 000039F0-00003A84       .text kyorokyoro__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::kyorokyoro() {
    /* Nonmatching */
}

/* 00003A84-00003C9C       .text chk_attn__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::chk_attn() {
    /* Nonmatching */
}

/* 00003C9C-00003D9C       .text setBikon__11daNpc_Kk1_cF4cXyz */
void daNpc_Kk1_c::setBikon(cXyz) {
    /* Nonmatching */
}

/* 00003D9C-00003DA0       .text delBikon__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::delBikon() {

}

/* 00003DA0-00003E18       .text setAse__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::setAse() {
    /* Nonmatching */
}

/* 00003E18-00003EA4       .text flwAse__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::flwAse() {
    /* Nonmatching */
}

/* 00003EA4-00003ED0       .text delAse__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::delAse() {
    /* Nonmatching */
}

/* 00003ED0-0000415C       .text wait_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_1() {
    /* Nonmatching */
}

/* 0000415C-0000449C       .text walk_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::walk_1() {
    /* Nonmatching */
}

/* 0000449C-00004614       .text wait_2__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_2() {
    /* Nonmatching */
}

/* 00004614-0000466C       .text init_CMT_WAI__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::init_CMT_WAI() {
    /* Nonmatching */
}

/* 0000466C-00004754       .text move_CMT_WAI__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::move_CMT_WAI() {
    /* Nonmatching */
}

/* 00004754-000047D4       .text init_CMT_TRN__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::init_CMT_TRN() {
    /* Nonmatching */
}

/* 000047D4-00004A14       .text move_CMT_TRN__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::move_CMT_TRN() {
    /* Nonmatching */
}

/* 00004A14-00004A84       .text init_CMT_PCK__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::init_CMT_PCK() {
    /* Nonmatching */
}

/* 00004A84-00004C34       .text move_CMT_PCK__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::move_CMT_PCK() {
    /* Nonmatching */
}

/* 00004C34-00004DD0       .text cmmt_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::cmmt_1() {
    /* Nonmatching */
}

/* 00004DD0-00004F74       .text wait_3__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_3() {
    /* Nonmatching */
}

/* 00004F74-00005170       .text wait_4__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::wait_4() {
    /* Nonmatching */
}

/* 00005170-000052B4       .text talk_1__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::talk_1() {
    /* Nonmatching */
}

/* 000052B4-000053F4       .text wait_action1__11daNpc_Kk1_cFPv */
BOOL daNpc_Kk1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 000053F4-00005534       .text demo__11daNpc_Kk1_cFv */
u8 daNpc_Kk1_c::demo() {
    /* Nonmatching */
}

/* 00005534-000055C4       .text shadowDraw__11daNpc_Kk1_cFv */
void daNpc_Kk1_c::shadowDraw() {
    /* Nonmatching */
}

/* 000055C4-00005798       .text _draw__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::_draw() {
    /* Nonmatching */
}

/* 00005798-000059EC       .text _execute__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::_execute() {
    /* Nonmatching */
}

/* 000059EC-00005A58       .text _delete__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::_delete() {
    /* Nonmatching */
}

/* 00005A58-00005B98       .text _create__11daNpc_Kk1_cFv */
cPhs_State daNpc_Kk1_c::_create() {
    /* Nonmatching */
}

/* 00006118-0000638C       .text bodyCreateHeap__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::bodyCreateHeap() {
    /* Nonmatching */
}

/* 0000638C-000065E0       .text effcCreateHeap__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::effcCreateHeap() {
    /* Nonmatching */
}

/* 000065E0-00006684       .text CreateHeap__11daNpc_Kk1_cFv */
BOOL daNpc_Kk1_c::CreateHeap() {
    /* Nonmatching */
}

/* 00006684-000066A4       .text daNpc_Kk1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kk1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kk1_c*)i_this)->_create();
}

/* 000066A4-000066C4       .text daNpc_Kk1_Delete__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_Delete(daNpc_Kk1_c* i_this) {
    return ((daNpc_Kk1_c*)i_this)->_delete();
}

/* 000066C4-000066E4       .text daNpc_Kk1_Execute__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_Execute(daNpc_Kk1_c* i_this) {
    return ((daNpc_Kk1_c*)i_this)->_execute();
}

/* 000066E4-00006704       .text daNpc_Kk1_Draw__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_Draw(daNpc_Kk1_c* i_this) {
    return ((daNpc_Kk1_c*)i_this)->_draw();
}

/* 00006704-0000670C       .text daNpc_Kk1_IsDelete__FP11daNpc_Kk1_c */
static BOOL daNpc_Kk1_IsDelete(daNpc_Kk1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kk1_Method = {
    (process_method_func)daNpc_Kk1_Create,
    (process_method_func)daNpc_Kk1_Delete,
    (process_method_func)daNpc_Kk1_Execute,
    (process_method_func)daNpc_Kk1_IsDelete,
    (process_method_func)daNpc_Kk1_Draw,
};

actor_process_profile_definition g_profile_NPC_KK1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KK1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kk1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KK1_e,
    /* Actor SubMtd */ &l_daNpc_Kk1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
