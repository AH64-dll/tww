/**
 * d_a_npc_pm1.cpp
 * NPC - Maggie (poor)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_pm1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/Pm.h"

class daNpc_Pm1_HIO_c : public JORReflexible {
public:
    struct hio_prm_c {
        s16 mMaxHeadX;
        s16 mMaxHeadY;
        s16 mMinHeadX;
        s16 mMinHeadY;
        s16 mMaxBackboneX;
        s16 mMaxBackboneY;
        s16 mMinBackboneX;
        s16 mMinBackboneY;
        s16 mMaxTurnStep;
        s16 mCalcAngleTarget;
        f32 mAttPosOffsetY;
        f32 field_18;
    };  // Size: 0x1C

    daNpc_Pm1_HIO_c();
    virtual ~daNpc_Pm1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

static daNpc_Pm1_HIO_c l_HIO;

/* 000000EC-00000144       .text __ct__15daNpc_Pm1_HIO_cFv */
daNpc_Pm1_HIO_c::daNpc_Pm1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX         */ 0x1FFE,
        /* mMaxHeadY         */ 0x38E0,
        /* mMinHeadX         */ 0xE002,
        /* mMinHeadY         */ 0xC720,
        /* mMaxBackboneX     */ 0x0000,
        /* mMaxBackboneY     */ 0x0000,
        /* mMinBackboneX     */ 0x0000,
        /* mMinBackboneY     */ 0x0000,
        /* mMaxTurnStep      */ 0x0800,
        /* mCalcAngleTarget  */ 0x0800,
        /* mAttPosOffsetY    */ 150.0f,
        /* field_18          */ 0.0f,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

/* 00000144-00000300       .text nodeCallBack_Pm__FP7J3DNodei */
static BOOL nodeCallBack_Pm(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Pm1_c* pm1Actor = (daNpc_Pm1_c*)(model->getUserArea());
        if (pm1Actor) {
            static cXyz a_att_pos_offst(0.0f, 0.0f, 0.0f);
            static cXyz a_eye_pos_offst(20.0f, -25.0f, 0.0f);

            J3DJoint* jnt_p = (J3DJoint*)i_node;
            s32 jnt_no = jnt_p->getJntNo();

            mDoMtx_stack_c::copy(model->getAnmMtx(jnt_no));
            if (jnt_no == pm1Actor->m_head_jnt_num) {
                mDoMtx_stack_c::multVec(&a_att_pos_offst, &pm1Actor->mAttPos);
                mDoMtx_stack_c::YrotM(-pm1Actor->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(-pm1Actor->m_jnt.getHead_x());
                mDoMtx_stack_c::multVec(&a_eye_pos_offst, &pm1Actor->mEyePos);
            } else if (jnt_no == pm1Actor->m_backbone_jnt_num) {
                mDoMtx_stack_c::XrotM(pm1Actor->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(pm1Actor->m_jnt.getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 0000033C-0000044C       .text createInit__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::createInit() {
    /* Nonmatching */
    mEventCut.setActorInfo2("Pm1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.0f;
    m798 = current.pos;
    set_action(&daNpc_Pm1_c::wait_action1, NULL);
    shape_angle = current.angle;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    m7BC = 1;
    setMtx();
    return true;
}

/* 0000044C-0000055C       .text setMtx__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setMtx() {
    if (m7C7 == 0) {
        playTexPatternAnm();
        m7B4 = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < m7A4) {
            m7B4 = 1;
        }
        m7A4 = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention();
}

/* 0000055C-00000664       .text anmResID__11daNpc_Pm1_cFiPiPi */
bool daNpc_Pm1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    static const int a_anm_idx_tbl[2][2] = {
        { dRes_ID_PM_BCK_WAIT01_e, dRes_ID_PM_BAS_WAIT01_e },
        { dRes_ID_PM_BCK_TALK01_e, dRes_ID_PM_BAS_TALK01_e },
    };
    JUT_ASSERT(0x11B, 0 <= i_num && i_num < ANM_END);
    JUT_ASSERT(0x11C, o_bck_num && o_bas_num);
    *o_bck_num = a_anm_idx_tbl[i_num][0];
    *o_bas_num = a_anm_idx_tbl[i_num][1];
    return true;
}

/* 00000664-00000700       .text BtpNum2ResID__11daNpc_Pm1_cFiPi */
void daNpc_Pm1_c::BtpNum2ResID(int i_num, int* o_btp_num) {
    static const int a_btp_arc_ix_tbl[1] = { dRes_ID_PM_BTP_MABA01_e };
    JUT_ASSERT(0x131, 0 <= i_num && i_num < TEXPATTERN_END);
    *o_btp_num = a_btp_arc_ix_tbl[i_num];
}

/* 00000700-00000744       .text setAnm_tex__11daNpc_Pm1_cFSc */
void daNpc_Pm1_c::setAnm_tex(signed char i_param_1) {
    if (i_param_1 >= 0 && i_param_1 != m7CD) {
        m7CD = i_param_1;
        initTexPatternAnm(true);
    }
}

/* 00000744-00000860       .text init_btp__11daNpc_Pm1_cFbi */
bool daNpc_Pm1_c::init_btp(bool param_1, int param_2) {
    int iVar3;
    J3DModelData* pJVar4 = mpMorf->getModel()->getModelData();
    if (param_2 >= 0) {
        int btpId;
        BtpNum2ResID(param_2, &btpId);
        J3DAnmTexPattern* pVVar1 = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Pm", btpId);
        m_head_tex_pattern = pVVar1;
        JUT_ASSERT(0x152, m_head_tex_pattern != 0);
        iVar3 = mBtpAnm.init(pJVar4, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, param_1, FALSE);
        if (iVar3 == 0) {
            return false;
        }
        mBtpFrame = 0;
        m6F2 = 0;
    }
    return true;
}

/* 00000860-000008A4       .text initTexPatternAnm__11daNpc_Pm1_cFb */
bool daNpc_Pm1_c::initTexPatternAnm(bool param_1) {
    bool var_31 = false;
    if (init_btp(param_1, m7CD)) {
        var_31 = true;
    }
    return var_31;
}

/* 000008A4-00000968       .text playTexPatternAnm__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::playTexPatternAnm() {
    bool var_r4 = true;
    if (m7CD == 0) {
        var_r4 = !cLib_calcTimer(&m6F2);
    }
    if (!var_r4) {
        return;
    }

    if ((mBtpFrame += 1) < m_head_tex_pattern->getFrameMax()) {
        return;
    }

    if (m7CD) {
        mBtpFrame = m_head_tex_pattern->getFrameMax();
        return;
    } else {
        mBtpFrame = 0;
        m6F2 = cM_rndF(60.0f) + 30.0f;
    }
    return;
}

/* 00000968-00000A34       .text setAnm_anm__11daNpc_Pm1_cFPQ211daNpc_Pm1_c9anm_prm_c */
s32 daNpc_Pm1_c::setAnm_anm(daNpc_Pm1_c::anm_prm_c* i_anm_ptr) {
    u32 uVar2 = 0;
    int local_18;
    int local_14;

    if (i_anm_ptr->bckNum >= 0 && m7CE != i_anm_ptr->bckNum) {
        m7CE = i_anm_ptr->bckNum;
        if (mpMorf != NULL) {
            anmResID(m7CE, &local_18, &local_14);
            if (local_18 >= 0) {
                dNpc_setAnmIDRes(mpMorf, i_anm_ptr->loopMode, i_anm_ptr->morf, i_anm_ptr->speed, local_18, local_14, "Pm");
            }
            uVar2 = 1;
        }
        m7A4 = 0;
        m7B5 = 0;
        m7B4 = 0;
    }
    return uVar2;
}

/* 00000A34-00000A9C       .text setAnm__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setAnm() {
    /* Nonmatching */
    static daNpc_Pm1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1, -1, 0, 0.0f, 0.0f, -1},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0.0f, 0.0f, -1},
    };
    setAnm_tex(a_anm_prm_tbl[m7D0].btpNum);
    setAnm_anm(&a_anm_prm_tbl[m7D0]);
}

/* 00000A9C-00000AA8       .text chngAnmTag__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::chngAnmTag() {
    switch (m7CC) {
        case 0:
            break;
    }
}

/* 00000AA8-00000AB4       .text ctrlAnmTag__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::ctrlAnmTag() {
    switch (m7CB) {
        case 0:
            break;
    }
}

/* 00000AB4-00000AF4       .text chngAnmAtr__11daNpc_Pm1_cFUc */
void daNpc_Pm1_c::chngAnmAtr(unsigned char param_1) {
    if (param_1 < 1 && param_1 != m7CB) {
        m7CB = param_1;
        setAnm_ATR(1);
    }
}

/* 00000AF4-00000AF8       .text ctrlAnmAtr__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::ctrlAnmAtr() {
}

/* 00000AF8-00000B60       .text setAnm_ATR__11daNpc_Pm1_cFi */
void daNpc_Pm1_c::setAnm_ATR(int param_1) {
    /* Nonmatching */
    static daNpc_Pm1_c::anm_prm_c a_anm_prm_tbl[1] = {
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    if (param_1 != 0) {
        setAnm_tex(a_anm_prm_tbl[m7CB].btpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[m7CB]);
}

/* 00000B60-00000C1C       .text anmAtr__11daNpc_Pm1_cFUs */
void daNpc_Pm1_c::anmAtr(u16 i_msgStatus) {
    if (i_msgStatus == fopMsgStts_MSG_TYPING_e) {
        if (m7D6 == 0) {
            m7CC = 0xFF;
            chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            m7D6 += 1;
        }
        u8 uVar1 = dComIfGp_getMesgAnimeTagInfo();
        if (uVar1 != 0xFF && uVar1 != m7CC) {
            dComIfGp_clearMesgAnimeTagInfo();
            m7CC = uVar1;
            chngAnmTag();
        }
    } else if (i_msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
        m7D6 = 0;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000C1C-00000C74       .text setStt__11daNpc_Pm1_cFSc */
void daNpc_Pm1_c::setStt(signed char param_1) {
    s8 uVar1 = m7D0;
    m7D0 = param_1;
    switch ((s8)m7D0) {
        case 2:
            m7D2 = 1;
            m7CB = 0xFF;
            m7D1 = uVar1;
            break;
        default:
        case 1:
            setAnm();
            break;
    }
}

/* 00000C74-00000C7C       .text next_msgStatus__11daNpc_Pm1_cFPUl */
u16 daNpc_Pm1_c::next_msgStatus(unsigned long*) {
    return fopMsgStts_MSG_ENDS_e;
}

/* 00000C7C-00000C84       .text getMsg__11daNpc_Pm1_cFv */
u32 daNpc_Pm1_c::getMsg() {
    return 0;
}

/* 00000C84-00000CD4       .text eventOrder__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::eventOrder() {
    if (m7CF == 1 || m7CF == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (m7CF == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000CD4-00000D14       .text checkOrder__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        return;
    }
    if (!eventInfo.checkCommandTalk()) {
        return;
    }
    if (m7CF != 1 && m7CF != 2) {
        return;
    }
    m7CF = 0;
    m7C5 = 1;
    return;
}

/* 00000D14-00000EA4       .text lookBack__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::lookBack() {
    cXyz vec1;
    cXyz vec2 = current.pos;
    vec2.y = eyePos.y;

    vec1.setall(0.0);

    cXyz* dstPos = NULL;
    s16 targetY = current.angle.y;
    bool headOnlyFollow = mHeadOnlyFollow;
    s8 state = m7D2;

    switch (state) {
        case 0:
            break;
        case 1:
            vec1 = dNpc_playerEyePos(-20.0);
            dstPos = &vec1;
            vec2 = current.pos;
            vec2.y = eyePos.y;
            break;
        case 2:
            vec1 = m798;
            dstPos = &vec1;
            vec2 = current.pos;
            vec2.y = eyePos.y;
            break;
        case 3:
            targetY = m7B2;
            break;
    }
    if (m_jnt.trnChk() != 0) {
        cLib_addCalcAngleS2(&m7B0, l_HIO.mPrmTbl.mCalcAngleTarget, 4, 0x800);
    } else {
        m7B0 = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos, vec2, targetY, m7B0, headOnlyFollow);
}

/* 00000EA4-00000F24       .text chkAttention__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth() != 0) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 00000F24-00000F88       .text setAttention__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::setAttention() {
    f32 f1 = current.pos.z;
    f32 f2 = current.pos.y + l_HIO.mPrmTbl.mAttPosOffsetY;

    attention_info.position.set(current.pos.x, f2, f1);
    if (!m7BC && !m7C0) {
        return;
    }
    f2 = getEyePos()->z;
    f1 = getEyePos()->y;
    eyePos.set(getEyePos()->x, f1, f2);
    m7BC = 0;
}

/* 00000F88-00000FB4       .text decideType__11daNpc_Pm1_cFi */
bool daNpc_Pm1_c::decideType(int param_1) {
    m7D3 = 0xFF;
    switch (fopAcM_GetName(this)) {
        case fpcNm_NPC_PM1_e:
            m7D3 = 0;
            m7D4 = 0;
            break;
    }

    return true;
}

/* 00000FB4-0000103C       .text event_actionInit__11daNpc_Pm1_cFi */
void daNpc_Pm1_c::event_actionInit(int param_1) {
    int* puVar1 = dComIfGp_evmng_getMyIntegerP(param_1, "ActNo");
    dComIfGp_evmng_getMyIntegerP(param_1, "Timer");
    if (puVar1 != NULL) {
        m7CA = *puVar1;
    }
}

/* 0000103C-0000104C       .text event_action__11daNpc_Pm1_cFv */
bool daNpc_Pm1_c::event_action() {
    switch (m7CA) {
        case 0:
            break;
    }
    return true;
}

/* 0000104C-00001154       .text privateCut__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::privateCut() {
    /* Nonmatching */
    static char* cut_name_tbl[] = {"ACTION"};

    int staffIdx = dComIfGp_evmng_getMyStaffId("Pm1", NULL, 0);
    if (staffIdx != -1) {
        int uVar1 = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
        m7C9 = uVar1;
        if (m7C9 == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
            return;
        }
        if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch (m7C9) {
                case 0:
                    event_actionInit(staffIdx);
                    break;
            }
        }
        bool bVar1;
        switch (m7C9) {
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

/* 00001154-00001174       .text endEvent__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::endEvent() {
    dComIfGp_event_reset();
    m7CB = 0xFF;
}

/* 00001174-000011D4       .text event_proc__11daNpc_Pm1_cFv */
void daNpc_Pm1_c::event_proc() {
    if (!mEventCut.cutProc()) {
        privateCut();
    }
    lookBack();
    shape_angle = current.angle;
}

/* 000011D4-00001280       .text set_action__11daNpc_Pm1_cFM11daNpc_Pm1_cFPCvPvPv_iPv */
bool daNpc_Pm1_c::set_action(ProcFunc i_action, void* param_2) {
    if (mProcFunc != i_action) {
        if (mProcFunc != 0) {
            m7D5 = 0xFF;
            (this->*mProcFunc)(param_2);
        }
        mProcFunc = i_action;
        m7D5 = 0;
        (this->*mProcFunc)(param_2);
    }
    return true;
}

/* 00001280-00001378       .text wait01__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::wait01() {
    if (m7C5 != 0) {
        bool set_stt = true;
        m7B7 = 0xFF;
        if (dComIfGp_event_chkTalkXY()) {
            if (dComIfGp_evmng_ChkPresentEnd() != 0) {
                m7B7 = dComIfGp_event_getPreItemNo();
            } else {
                set_stt = false;
            }
        }
        if (set_stt) {
            setStt(2);
        }
    } else {
        m7CF = 2;
        if (m7C4) {
            m7D2 = 1;
        } else {
            m7D2 = 3;
            m7B2 = m76C.y;
            m_jnt.setTrn();
        }
    }
    return TRUE;
}

/* 00001378-00001408       .text talk01__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::talk01() {
    talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
            case 6:
            case 2:
                break;
            case 19:
                m7B7 = 0xFF;
                setStt(m7D1);
                m7C8 = 0;
                m7C5 = 0;
                endEvent();
                break;
        }
    }
    return TRUE;
}

/* 00001408-000014BC       .text wait_action1__11daNpc_Pm1_cFPv */
int daNpc_Pm1_c::wait_action1(void*) {
    if (m7D5 == 0) {
        setStt(1);
        m7D5 += 1;
    } else if (m7D5 != -1) {
        m7C4 = chkAttention();
        switch (m7D0) {
            case 2:
                m7C0 = talk01();
                break;
            case 1:
                m7C0 = wait01();
                break;
            default:
                m7C0 = 0;
                break;
        }
        lookBack();
    }
    return 1;
}

/* 000014BC-00001558       .text demo__11daNpc_Pm1_cFv */
u8 daNpc_Pm1_c::demo() {
    if (demoActorID == 0) {
        if (m7C7 != 0) {
            m7C7 = 0;
        }
    } else {
        m7C7 = 1;
        dComIfGp_demo_getActor(demoActorID);
        dDemo_setDemoData(
            this,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf,
            "Pm"
        );
    }
    return m7C7;
}

/* 00001558-000016BC       .text _draw__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* model_data = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(model_data, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);
    dNpc_setShadowModel(mShadowModel, model_data, model);

    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowId = dComIfGd_setRealShadow(mShadowId, 1, mShadowModel, &pos, 800.0f, current.pos.y - mObjAcch.GetGroundH(), NULL);
    if (mShadowId == 0) {
        dComIfGd_setSimpleShadow(
            &current.pos,
            mObjAcch.GetGroundH(),
            40.0f,
            dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd)->GetNP()
        );
    }
    dSnap_RegistFig(DSNAP_TYPE_UNK5A, this, 1.0f, 1.0f, 1.0f);

    // Color literals for debug drawing. Unused in non-debug builds.
    (GXColor){0xFF, 0x00, 0x00, 0x80};
    (GXColor){0x00, 0x00, 0xFF, 0x80};

    return true;
}

/* 000016BC-00001818       .text _execute__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_execute() {
    if (m7B8 == 0) {
        m774 = current.pos;
        m76C = current.angle;
        m7B8 = 1;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.mMaxBackboneX, l_HIO.mPrmTbl.mMaxBackboneY,
                   l_HIO.mPrmTbl.mMinBackboneX, l_HIO.mPrmTbl.mMinBackboneY,
                   l_HIO.mPrmTbl.mMaxHeadX, l_HIO.mPrmTbl.mMaxHeadY,
                   l_HIO.mPrmTbl.mMinHeadX, l_HIO.mPrmTbl.mMinHeadY,
                   l_HIO.mPrmTbl.mMaxTurnStep);
    checkOrder();
    if (demo() == 0) {
        if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {
            event_proc();
        } else {
            (this->*mProcFunc)(NULL);
            shape_angle = current.angle;
        }
    }
    eventOrder();
    if (m7C7 == 0) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    setMtx();
    setCollision(50.0f, 130.0f);
    return true;
}

/* 00001818-0000189C       .text _delete__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Pm");

    if (mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    if (l_HIO.field_0x8 >= 0) {
        l_HIO.field_0x8 += -1;
        if (l_HIO.field_0x8 < 0) {
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return true;
}

/* 0000189C-000018BC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* actor) {
    return ((daNpc_Pm1_c*)actor)->CreateHeap();
}

/* 000018BC-00001A2C       .text _create__11daNpc_Pm1_cFv */
cPhs_State daNpc_Pm1_c::_create() {
    /* Nonmatching */
    static int a_heap_size_tbl[] = {
        0x272E0
    };

    fopAcM_ct_Retail(this, daNpc_Pm1_c);

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    cPhs_State resLoadResult = dComIfG_resLoad(&mPhs, "Pm");
    if (resLoadResult != cPhs_COMPLEATE_e) {
        return resLoadResult;
    }
    if (l_HIO.field_0x8 < 0) {
        l_HIO.mNo = mDoHIO_createChild("貧乏マギ−", &l_HIO);
    }
    l_HIO.field_0x8 += 1;

    if (fopAcM_entrySolidHeap(this, CheckCreateHeap, a_heap_size_tbl[m7D3])) {
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -50.0f, -20.0f, -50.0f, 50.0f, 150.0f, 50.0f);
    } else {
        return cPhs_ERROR_e;
    }
    if (createInit() == 0) {
        resLoadResult = cPhs_ERROR_e;
    }
    return resLoadResult;
}

/* 00001E5C-00002168       .text CreateHeap__11daNpc_Pm1_cFv */
BOOL daNpc_Pm1_c::CreateHeap() {
    /* Nonmatching */
    static u8 a_tex_pattern_num_tbl[1] = {TEXPATTERN_MABA01};
    J3DModelData* a_mdl_data;

    a_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Pm", dRes_ID_PM_BDL_PM_e);
    JUT_ASSERT(0x527, a_mdl_data != 0);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_data,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Pm", dRes_ID_PM_BCK_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020002
    );
    if (mpMorf) {
        if (mpMorf->getModel()) {
            m_head_jnt_num = a_mdl_data->getJointName()->getIndex("head");
            JUT_ASSERT(0x53A, m_head_jnt_num >= 0);
            m_backbone_jnt_num = a_mdl_data->getJointName()->getIndex("backbone");
            JUT_ASSERT(0x53C, m_backbone_jnt_num >= 0);
            m7CD = a_tex_pattern_num_tbl[m7D3];
            if (initTexPatternAnm(false) != 0) {
                mShadowModel = mDoExt_J3DModel__create(a_mdl_data, 0x20000, 0x11020203);
                if (mShadowModel != 0) {
                    for (u16 i = 0; i < a_mdl_data->getJointNum(); i += 1) {
                        if ((i == m_head_jnt_num) || (i == m_backbone_jnt_num)) {
                            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Pm);
                        }
                    }
                    mpMorf->getModel()->setUserArea((u32)this);
                    mAcchCir.SetWall(30.0f, 50.0f);
                    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
                    return TRUE;
                }
            }
        }
        mpMorf = NULL;
    }
    return FALSE;
}

/* 00002168-00002188       .text daNpc_Pm1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Pm1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_create();
}

/* 00002188-000021A8       .text daNpc_Pm1_Delete__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Delete(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_delete();
}

/* 000021A8-000021C8       .text daNpc_Pm1_Execute__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Execute(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_execute();
}

/* 000021C8-000021E8       .text daNpc_Pm1_Draw__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_Draw(daNpc_Pm1_c* i_this) {
    return ((daNpc_Pm1_c*)i_this)->_draw();
}

/* 000021E8-000021F0       .text daNpc_Pm1_IsDelete__FP11daNpc_Pm1_c */
static BOOL daNpc_Pm1_IsDelete(daNpc_Pm1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Pm1_Method = {
    (process_method_func)daNpc_Pm1_Create,
    (process_method_func)daNpc_Pm1_Delete,
    (process_method_func)daNpc_Pm1_Execute,
    (process_method_func)daNpc_Pm1_IsDelete,
    (process_method_func)daNpc_Pm1_Draw,
};

actor_process_profile_definition g_profile_NPC_PM1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_PM1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Pm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_PM1_e,
    /* Actor SubMtd */ &l_daNpc_Pm1_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
