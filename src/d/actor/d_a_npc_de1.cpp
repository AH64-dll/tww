/**
 * d_a_npc_de1.cpp
 * NPC - Deku Tree
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_de1.h"
#include "d/actor/d_a_cc.h"
#include "d/actor/d_a_leaflift.h"
#include "d/actor/d_a_player.h"
#include "d/d_lib.h"
#include "d/d_particle.h"
#include "d/d_snap.h"
#include "res/Object/De.h"

class daNpc_De1_HIO_c : public JORReflexible {
public:
    struct hio_prm_c {
        /* 0x00 */ f32 mAttPosOffsetY;
        /* 0x04 */ f32 mChkAttentionRadius;
        /* 0x08 */ f32 mScale;
        /* 0x0C */ f32 mPlayerDist;
        /* 0x10 */ f32 mDemoCenterX;
        /* 0x14 */ f32 mDemoCenterY;
        /* 0x18 */ f32 mDemoCenterZ;
        /* 0x1C */ u8 mDebug;
        /* 0x1D */ u8 field_0x1D[3];
    };  // Size: 0x20

    daNpc_De1_HIO_c();
    virtual ~daNpc_De1_HIO_c() {};

public:
    /* 0x04 */ s8 mChildID;
    /* 0x08 */ int mRefCount;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

/* 000000EC-00000144       .text __ct__15daNpc_De1_HIO_cFv */
daNpc_De1_HIO_c::daNpc_De1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mAttPosOffsetY      */ 100.0f,
        /* mChkAttentionRadius */ 150.0f,
        /* mScale              */ 1.0f,
        /* mPlayerDist         */ 800.0f,
        /* mDemoCenterX        */ 44.0f,
        /* mDemoCenterY        */ 100.0f,
        /* mDemoCenterZ        */ 980.0f,
        /* mDebug              */ 0,
    };
    memcpy(&mPrmTbl, &a_prm_tbl, sizeof(hio_prm_c));
    mChildID = -1;
    mRefCount = -1;
}

static daNpc_De1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[100];
static int l_check_wrk;

/* 00000144-000001BC       .text searchActor_leafLift__FPvPv */
static void* searchActor_leafLift(void* i_actor, void*) {
    if (l_check_wrk < 100 && fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_LEAF_LIFT_e) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk++;
    }
    return NULL;
}

/* 000001BC-0000033C       .text createInit__11daNpc_De1_cFv */
BOOL daNpc_De1_c::createInit() {
    mEventCut.setActorInfo2("De1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x15;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x16;
    gravity = 0.0f;
    m778 = current.pos;
    switch (mSpecificType) {
        case 0:
            if (dComIfGs_isEventBit(0x1801)) {
                set_action(&daNpc_De1_c::wait_action2, NULL);
            } else {
                set_action(&daNpc_De1_c::wait_action1, NULL);
            }
            break;
        case 1:
            set_action(&daNpc_De1_c::wait_action2, NULL);
            break;
    }
    shape_angle = current.angle;
    mpMorf->setMorf(0.0f);
    m7AC = 1;
    setMtx();
    return TRUE;
}

/* 0000033C-00000550       .text setMtx__11daNpc_De1_cFv */
void daNpc_De1_c::setMtx() {
    if (mbInDemo == 0) {
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = 1;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    if (cLib_calcTimer(&mTimer0) == 0 && mbMorfAnimStopped && mStatus == 3) {
        mDoAud_seStart(JA_SE_CV_DEKU_AGONY, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::scaleM(l_HIO.mPrmTbl.mScale, l_HIO.mPrmTbl.mScale, l_HIO.mPrmTbl.mScale);
    PSMTXCopy(mDoMtx_stack_c::get(), mpMorf->getModel()->getBaseTRMtx());
    mpDeform->CopyBackVtx();
    mpMorf->calc();
    mpDeform->SetVtx((Vec*)mpMorf->getModel()->getCurrentVtxPos());
    mpDeform->Move();
    followPa_happa();
    setDemoStartCenter();
    if (mSpecificType == 0 && !dComIfGs_isEventBit(0x1801)) {
        cc_set();
    }
    setAttention();
}

/* 00000550-00000658       .text anmResID__11daNpc_De1_cFiPiPi */
void daNpc_De1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    static const int a_anm_idx_tbl[][2] = {
        {5, -1},
        {0, -1},
        {6, -1},
        {1, -1},
        {2, -1},
        {3, -1},
        {4, -1},
    };
    JUT_ASSERT(0x11c, 0 <= i_num && i_num < ANM_END);
    JUT_ASSERT(0x11d, o_bck_num && o_bas_num);
    *o_bck_num = a_anm_idx_tbl[i_num][0];
    *o_bas_num = a_anm_idx_tbl[i_num][1];
}

/* 00000658-00000744       .text setAnm_anm__11daNpc_De1_cFPQ211daNpc_De1_c9anm_prm_c */
BOOL daNpc_De1_c::setAnm_anm(daNpc_De1_c::anm_prm_c* i_anmPrmP) {
    BOOL o_retval = FALSE;
    if (i_anmPrmP->mAnmNum >= 0) {
        if (mAnmNum == i_anmPrmP->mAnmNum) {
            return FALSE;
        }
        mAnmNum = i_anmPrmP->mAnmNum;
        if (mpMorf != NULL) {
            int bck_num, bas_num;
            anmResID(mAnmNum, &bck_num, &bas_num);
            if (bck_num >= 0) {
                dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, bck_num, bas_num, "De");
            }
            if (mAnmNum == 3) {
                set_pa_happa();
            } else {
                del_pa_happa();
            }
            o_retval = TRUE;
        }
        mPrevMorfFrame = 0.0f;
        m7A5 = 0;
        mbMorfAnimStopped = 0;
    }
    return o_retval;
}

/* 00000744-00000774       .text setAnm_NUM__11daNpc_De1_cFi */
void daNpc_De1_c::setAnm_NUM(int i_num) {
    static anm_prm_c a_anm_prm_tbl[] = {
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {3, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    setAnm_anm(&a_anm_prm_tbl[i_num]);
}

/* 00000774-000007AC       .text setAnm__11daNpc_De1_cFv */
BOOL daNpc_De1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0xFF, 0, 0, 0.0f, 0.0f, -1},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0xFF, 0, 0, 0.0f, 0.0f, -1},
        {0xFF, 0, 0, 0.0f, 0.0f, -1},
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {0xFF, 0, 0, 0.0f, 0.0f, -1},
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    return setAnm_anm(&a_anm_prm_tbl[mStatus]);
}

/* 000007AC-000007B8       .text chngAnmTag__11daNpc_De1_cFv */
void daNpc_De1_c::chngAnmTag() {
    switch (mAnmTag) {
        case 0:
            break;
    }
}

/* 000007B8-000007C4       .text ctrlAnmTag__11daNpc_De1_cFv */
void daNpc_De1_c::ctrlAnmTag() {
    switch (mAnmAtr) {
        case 0:
            break;
    }
}

/* 000007C4-00000800       .text chngAnmAtr__11daNpc_De1_cFUc */
void daNpc_De1_c::chngAnmAtr(u8 i_param_1) {
    if (i_param_1 >= 0x4 || i_param_1 == mAnmAtr) {
        return;
    }
    mAnmAtr = i_param_1;
    setAnm_ATR();
}

/* 00000800-00000848       .text ctrlAnmAtr__11daNpc_De1_cFv */
void daNpc_De1_c::ctrlAnmAtr() {
    if (mAnmAtr == 3 && mbMorfAnimStopped) {
        mAnmAtr = 0;
        setAnm_ATR();
    }
}

/* 00000848-0000087C       .text setAnm_ATR__11daNpc_De1_cFv */
void daNpc_De1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 0000087C-00000938       .text anmAtr__11daNpc_De1_cFUs */
void daNpc_De1_c::anmAtr(u16 i_msgStatus) {
    switch (i_msgStatus) {
        case 6:
            if (mTagInitCounter == 0) {
                mAnmTag = 0xFF;
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                mTagInitCounter++;
            }
            {
                u8 mesgAnimeTagInfo = dComIfGp_getMesgAnimeTagInfo();
                if (mesgAnimeTagInfo != 0xFF && mAnmTag != mesgAnimeTagInfo) {
                    dComIfGp_clearMesgAnimeTagInfo();
                    mAnmTag = mesgAnimeTagInfo;
                    chngAnmTag();
                }
            }
            break;
        case 0xE:
            mTagInitCounter = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000938-000009B4       .text setStt__11daNpc_De1_cFSc */
void daNpc_De1_c::setStt(s8 i_status) {
    s8 prev_status = mStatus;
    mStatus = i_status;
    switch (mStatus) {
        case 4:
        case 2:
            mAnmAtr = 0xFF;
            mPrevStatus = prev_status;
            return;
        case 7:
            attention_info.flags |= fopAc_Attn_ENEMYFLAG_NOLOCKON_e;
            attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0x22;
            // fall through
        case 3:
        default:
            setAnm();
            return;
    }}

/* 000009B4-00000C98       .text next_msgStatus__11daNpc_De1_cFPUl */
u16 daNpc_De1_c::next_msgStatus(u32* i_msg_no) {
    u16 o_retval = fopMsgStts_MSG_CONTINUES_e;
    switch (*i_msg_no) {
        case 0x139D:
            *i_msg_no = 0x139E;
            break;
        case 0x139F:
            *i_msg_no = 0x13A0;
            break;
        case 0x13A1:
            *i_msg_no = 0x13A2;
            break;
        case 0x13A3:
            *i_msg_no = 0x13A4;
            break;
        case 0x13A4:
            *i_msg_no = 0x13A5;
            break;
        case 0x13A5:
            *i_msg_no = 0x13A6;
            break;
        case 0x13A8:
            *i_msg_no = 0x13A9;
            break;
        case 0x13AC:
            *i_msg_no = 0x13A9;
            break;
        case 0x13A9:
        case 0x13C5:
            if (dComIfGs_isEventBit(0x1D40)) {
                *i_msg_no = 0x13AA;
            } else {
                *i_msg_no = 0x13AB;
            }
            break;
        case 0x13AA:
            switch (mpCurrMsg->mSelectNum) {
                case 0:
                    *i_msg_no = 0x13AD;
                    break;
                case 1:
                    *i_msg_no = 0x13C7;
                    break;
                default:
                    *i_msg_no = 0x13C6;
                    break;
            }
            break;
        case 0x13AB:
            switch (mpCurrMsg->mSelectNum) {
                case 0:
                    *i_msg_no = 0x13AD;
                    break;
                case 1:
                    *i_msg_no = 0x13CC;
                    break;
                default:
                    *i_msg_no = 0x13C6;
                    break;
            }
            break;
        case 0x13CC:
            *i_msg_no = 0x13CD;
            break;
        case 0x13CD:
            *i_msg_no = 0x13CE;
            break;
        case 0x13CE:
            *i_msg_no = 0x13CF;
            break;
        case 0x13CF:
            *i_msg_no = 0x13D0;
            break;
        case 0x13D0:
            *i_msg_no = 0x13D1;
            break;
        case 0x13C7:
            *i_msg_no = 0x13C8;
            break;
        case 0x13C8:
            *i_msg_no = 0x13C9;
            break;
        case 0x13C9:
            *i_msg_no = 0x13CA;
            break;
        case 0x13CA:
            *i_msg_no = 0x13CB;
            break;
        case 0x13AD:
            switch (mpCurrMsg->mSelectNum) {
                case 0:
                    if (dComIfGs_isEventBit(0x102)) {
                        *i_msg_no = 0x13B0;
                    } else if (dComIfGs_isEventBit(0x3940)) {
                        *i_msg_no = 0x13AF;
                    } else {
                        dComIfGs_onEventBit(0x3940);
                        *i_msg_no = 0x13AE;
                    }
                    break;
                case 1:
                    *i_msg_no = 0x13B6;
                    break;
                default:
                    *i_msg_no = 0x13C6;
                    break;
            }
            break;
        case 0x13B6:
            if (dComIfGs_isEventBit(0x1820)) {
                if (dComIfGs_isStageBossEnemy(6)) {
                    *i_msg_no = 0x13C2;
                } else {
                    *i_msg_no = 0x13C4;
                }
            } else {
                *i_msg_no = 0x13C0;
            }
            break;
        case 0x13C0:
            *i_msg_no = 0x13C1;
            break;
        case 0x13C2:
            *i_msg_no = 0x13C3;
            break;
        case 0x13AE:
        case 0x13AF:
        case 0x13B0:
        case 0x13C1:
        case 0x13C3:
        case 0x13C4:
            *i_msg_no = 0x13C5;
            break;
        default:
            o_retval = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return o_retval;
}

/* 00000C98-00000D6C       .text getMsg__11daNpc_De1_cFv */
u32 daNpc_De1_c::getMsg() {
    u32 o_retval = 0;
    switch (mSpecificType) {
        case 0:
            if (dComIfGs_checkGetItem(0x20)) {
                o_retval = dLib_setFirstMsg(0xE40, 0x139F, 0x13A1);
            } else {
                o_retval = dLib_setFirstMsg(0xE80, 0x139C, 0x139D);
            }
            break;
        case 1:
            if (dComIfGs_isEventBit(0x1C40)) {
                if (m7A7 != 0) {
                    o_retval = 0x13AC;
                } else {
                    m7A7 = 1;
                    o_retval = 0x13A8;
                }
            } else {
                o_retval = dLib_setFirstMsg(0x1C20, 0x13A3, 0x13A7);
            }
            break;
        default:
            break;
    }
    return o_retval;
}

/* 00000D6C-00000E14       .text eventOrder__11daNpc_De1_cFv */
void daNpc_De1_c::eventOrder() {
    s8 order = mOrder;
    if (order == 1 || order == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (order == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (order >= 3) {
        static char* a_demo_name_tbl[] = {
            "LIFT_UP",
            "DE_CHUCHU",
            "contact",
        };
        if (order == 3) {
            fopAcM_orderOtherEvent2(this, a_demo_name_tbl[order - 3], 1, 0xF);
        } else {
            fopAcM_orderOtherEvent2(this, a_demo_name_tbl[order - 3], 1, 0xFFFF);
        }
    }
}

/* 00000E14-00000F8C       .text checkOrder__11daNpc_De1_cFv */
void daNpc_De1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck("LIFT_UP") && mOrder == 3) {
            mOrder = 0;
        } else if (dComIfGp_evmng_startCheck("DE_CHUCHU") && mOrder == 4) {
            mDoAud_bgmStart(JA_BGM_DEKU_PINCH);
            mOrder = 0;
        } else if (dComIfGp_evmng_startCheck("contact") && mOrder == 5) {
            dComIfGs_onEventBit(0x1801);
            dComIfGp_setNextStage("Omori", 0xD5, 0, 8, 0.0f, 0, 1, 0);
            mOrder = 0;
        }
    } else if (eventInfo.checkCommandTalk() && (mOrder == 1 || mOrder == 2)) {
        mOrder = 0;
        m7B5 = 1;
    }
}

/* 00000F8C-000010B8       .text chkAttention__11daNpc_De1_cFv */
bool daNpc_De1_c::chkAttention() {
    fopAc_ac_c* partner = searchByID(mPartnerProcID);
    if (partner != NULL) {
        f32 radius = l_HIO.mPrmTbl.mChkAttentionRadius;
        if (mbAttention != 0) {
            radius += 50.0f;
        }
        f32 dist = std::sqrtf((dComIfGp_getPlayer(0)->current.pos - partner->current.pos).abs2XZ());
        return radius >= dist;
    }
    return false;
}

/* 000010B8-00001194       .text setAttention__11daNpc_De1_cFv */
void daNpc_De1_c::setAttention() {
    cXyz offset(0.0f, 1100.0f, 700.0f);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&offset, &m76C);
    mTransformedEyePos = m76C;
    attention_info.position.set(mTransformedEyePos.x, mTransformedEyePos.y + l_HIO.mPrmTbl.mAttPosOffsetY, mTransformedEyePos.z);
    eyePos = m76C;
}

/* 00001194-000011C8       .text searchByID__11daNpc_De1_cFUi */
fopAc_ac_c* daNpc_De1_c::searchByID(fpc_ProcID i_procID) {
    fopAc_ac_c* o_actor = NULL;
    fopAcM_SearchByID(i_procID, &o_actor);
    return o_actor;
}

/* 000011C8-0000124C       .text setDemoStartCenter__11daNpc_De1_cFv */
void daNpc_De1_c::setDemoStartCenter() {
    cXyz offset(l_HIO.mPrmTbl.mDemoCenterX, l_HIO.mPrmTbl.mDemoCenterY, l_HIO.mPrmTbl.mDemoCenterZ);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::multVec(&offset, &mDemoStartCenter);
}

/* 0000124C-00001300       .text partner_srch__11daNpc_De1_cFv */
bool daNpc_De1_c::partner_srch() {
    bool o_retval = false;
    mPartnerProcID = -1;
    l_check_wrk = 0;
    for (int i = 0; i < 100; i++) {
        l_check_inf[i] = NULL;
    }
    fpcM_Search(searchActor_leafLift, this);
    if (l_check_wrk != 0) {
        mPartnerProcID = fopAcM_GetID(l_check_inf[0]);
        o_retval = true;
    }
    return o_retval;
}

/* 00001300-000013F0       .text ccCreate__11daNpc_De1_cFv */
void daNpc_De1_c::ccCreate() {
    static const u32 a_cc_prm_tbl[] = {
        0x00000002, 0x00000102, 0x00000002, 0x00000102, 0x00000002,
        0x00000102, 0x00000002, 0x00000102, 0x00000002, 0x00000102,
    };
    u32 prm_tbl[10];
    memcpy(prm_tbl, a_cc_prm_tbl, sizeof(prm_tbl));
    for (int i = 0; i < 10; i++) {
        m_cc_ID[i] = fopAcM_create(fpcNm_CC_e, prm_tbl[i], &current.pos, fopAcM_GetRoomNo(this), NULL, NULL, -1, NULL);
        JUT_ASSERT(0x373, m_cc_ID[ i] != fpcM_ERROR_PROCESS_ID_e);
    }
}

/* 000013F0-000014A0       .text cc_set__11daNpc_De1_cFv */
void daNpc_De1_c::cc_set() {
    cXyz zero(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 10; i++) {
        fopAc_ac_c* cc_actor = searchByID(m_cc_ID[i]);
        if (cc_actor != NULL) {
            PSMTXCopy(mpMorf->getModel()->getAnmMtx(m_c0_jnt_num[i]), mDoMtx_stack_c::get());
            PSMTXCopy(mDoMtx_stack_c::get(), ((cc_class*)cc_actor)->m7EC);
        }
    }
}

/* 000014A0-00001524       .text set_pa_happa__11daNpc_De1_cFv */
void daNpc_De1_c::set_pa_happa() {
    mEcallBack.remove();
    dComIfGp_particle_set(dPa_name::ID_IT_SN_DEKU_HAPPA00, &mParticlePos, &current.angle, NULL, 0xFF, &mEcallBack, fopAcM_GetRoomNo(this), NULL, NULL, NULL);
}

/* 00001524-00001550       .text del_pa_happa__11daNpc_De1_cFv */
void daNpc_De1_c::del_pa_happa() {
    mEcallBack.remove();
}

/* 00001550-000015CC       .text followPa_happa__11daNpc_De1_cFv */
void daNpc_De1_c::followPa_happa() {
    if (mEcallBack.getEmitter() != NULL) {
        PSMTXCopy(mpMorf->getModel()->getAnmMtx(m_head_jnt_num), mDoMtx_stack_c::get());
        mParticlePos.set(mDoMtx_stack_c::get()[0][3], mDoMtx_stack_c::get()[1][3], mDoMtx_stack_c::get()[2][3]);
    }
}

/* 000015CC-0000165C       .text decideType__11daNpc_De1_cFi */
bool daNpc_De1_c::decideType(int i_param_1) {
    bool o_retval = true;
    mType = -1;
    if (fopAcM_GetName(this) == fpcNm_NPC_DE1_e) {
        mType = 0;
        if (dComIfGs_isSymbol(2)) {
            mSpecificType = 1;
        } else {
            mSpecificType = 0;
        }
    } else {
        o_retval = false;
    }
    return o_retval;
}

/* 0000165C-00001858       .text event_actionInit__11daNpc_De1_cFi */
void daNpc_De1_c::event_actionInit(int i_staff_idx) {
    int* act_no_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx, "ActNo");
    int* timer_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx, "Timer");
    int* num_p = dComIfGp_evmng_getMyIntegerP(i_staff_idx, "Num");
    if (act_no_p != NULL) {
        mActNo = *act_no_p;
        switch (mActNo) {
            case 0:
                if (num_p != NULL) {
                    fopAc_ac_c* actor = searchByID(m_cc_ID[*num_p]);
                    if (actor != NULL) {
                        dComIfGp_event_setItemPartner(actor);
                    }
                }
                break;
            case 1:
                break;
            case 2:
                mTimer1 = (timer_p != NULL) ? *timer_p : 0;
                mTimer2 = (num_p != NULL) ? *num_p : 0;
                break;
            case 3:
                if (num_p != NULL) {
                    setAnm_NUM(*num_p);
                }
                break;
            case 4:
                mDoAud_seStart(JA_SE_CV_DEKU_AGONY_L, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mTimer0 = 0x54;
                break;
            case 5:
                daPy_py_c* player = daPy_getPlayerActorClass();
                player->mDemo.setDemoType(daPy_demo_c::TYPE_ORIGINAL_e);
                player->mDemo.setParam0(0);
                player->mDemo.setDemoMode(0x18);
                player->onFrollCrashFlg(0x1D);
                break;
        }
    }
}

/* 00001858-00001938       .text event_action__11daNpc_De1_cFv */
bool daNpc_De1_c::event_action() {
    bool o_retval = false;
    switch (mActNo) {
        case 0:
            if (searchByID(mPartnerProcID) != NULL) {
                daLlift_c* lift = (daLlift_c*)searchByID(mPartnerProcID);
                if (lift->MoveUpLift()) {
                    o_retval = true;
                }
            }
            break;
        case 2:
            if (cLib_calcTimer(&mTimer1) == 0) {
                if (mTimer2 >= 0 && mTimer2 < 10) {
                    fopAc_ac_c* actor = searchByID(m_cc_ID[mTimer2]);
                    if (actor != NULL) {
                        ((cc_class*)actor)->m2FB = 1;
                    }
                }
                o_retval = true;
            }
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
            o_retval = true;
            break;
        default:
            break;
    }
    return o_retval;
}

/* 00001938-00001A40       .text privateCut__11daNpc_De1_cFv */
void daNpc_De1_c::privateCut() {
    static char* a_cut_tbl[] = {
        "ACTION",
    };
    int staff_idx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL, 0);
    if (staff_idx == -1) {
        return;
    }
    mActIdx = dComIfGp_evmng_getMyActIdx(staff_idx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);
    if (mActIdx == -1) {
        dComIfGp_evmng_cutEnd(staff_idx);
    } else {
        if (dComIfGp_evmng_getIsAddvance(staff_idx)) {
            switch (mActIdx) {
                case 0:
                    event_actionInit(staff_idx);
                    break;
            }
        }
        BOOL end_cut;
        switch (mActIdx) {
            case 0:
                end_cut = event_action();
                break;
            default:
                end_cut = true;
                break;
        }
        if (end_cut) {
            dComIfGp_evmng_cutEnd(staff_idx);
        }
    }
}

/* 00001A40-00001A60       .text endEvent__11daNpc_De1_cFv */
void daNpc_De1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
}

/* 00001A60-00001B90       .text event_proc__11daNpc_De1_cFv */
void daNpc_De1_c::event_proc() {
    if (dComIfGp_evmng_endCheck("LIFT_UP")) {
        endEvent();
        mOrder = 1;
        setStt(3);
        return;
    }
    if (dComIfGp_evmng_endCheck("DE_CHUCHU")) {
        dComIfGs_onTmpBit(0x308);
        endEvent();
        setStt(7);
        return;
    }
    if (dComIfGp_evmng_endCheck("contact")) {
        endEvent();
        set_action(&daNpc_De1_c::wait_action2, NULL);
        return;
    }
    if (!mEventCut.cutProc()) {
        privateCut();
    }
}

/* 00001B90-00001C3C       .text set_action__11daNpc_De1_cFM11daNpc_De1_cFPCvPvPv_iPv */
BOOL daNpc_De1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc) {
            mStep = -1;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        mStep = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00001C3C-00001C94       .text wait01__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait01() {
    if (m7B5 != 0) {
        setStt(2);
    } else if (mbAttention != 0) {
        mOrder = 2;
    } else {
        mOrder = 0;
    }
    return TRUE;
}

/* 00001C94-00001D38       .text wait02__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait02() {
    if (m7B5 != 0) {
        setStt(4);
    } else {
        daLlift_c* lift = (daLlift_c*)searchByID(mPartnerProcID);
        if (lift != NULL) {
            if (lift->current.pos.y < lift->home.pos.y + daLlift_c::m_height) {
                setStt(5);
                return TRUE;
            }
        }
        if (mbAttention != 0) {
            mOrder = 2;
        } else {
            mOrder = 0;
        }
    }
    return TRUE;
}

/* 00001D38-00001D8C       .text wait03__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait03() {
    daLlift_c* lift = (daLlift_c*)searchByID(mPartnerProcID);
    if (lift != NULL && lift->checkEndDownLift()) {
        setStt(1);
    }
    return TRUE;
}

/* 00001D8C-00001EA0       .text wait04__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait04() {
    mOrder = 0;
    f32 dist = std::sqrtf((dComIfGp_getPlayer(0)->current.pos - mDemoStartCenter).abs2XZ());
    if (dist < l_HIO.mPrmTbl.mPlayerDist) {
        daPy_py_c* player = daPy_getPlayerActorClass();
        mOrder = 4;
        player->changeDemoMoveAngle(cLib_targetAngleY(&player->current.pos, &current.pos));
    }
    return TRUE;
}

/* 00001EA0-00001F38       .text wait05__11daNpc_De1_cFv */
BOOL daNpc_De1_c::wait05() {
    if (mOrder == 5) {
        return TRUE;
    }
    mOrder = 0;
    int found_count = 0;
    int i = 0;
    while (true) {
        if (searchByID(m_cc_ID[i]) != NULL) {
            break;
        }
        found_count++;
        if (found_count == 10) {
            break;
        }
        i++;
    }
    if (found_count == 10) {
        attention_info.flags &= ~fopAc_Attn_UNK1000000_e;
        mOrder = 5;
    }
    return TRUE;
}

/* 00001F38-00001F90       .text talk01__11daNpc_De1_cFv */
BOOL daNpc_De1_c::talk01() {
    if (mOrder != 3) {
        m7A6 = 0xFF;
        m7B8 = 0;
        m7B5 = 0;
        endEvent();
        mOrder = 3;
    }
    return TRUE;
}

/* 00001F90-00002020       .text talk02__11daNpc_De1_cFv */
BOOL daNpc_De1_c::talk02() {
    talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
            case fopMsgStts_BOX_OPENING_e:
            case fopMsgStts_MSG_TYPING_e:
                break;
            case fopMsgStts_MSG_DESTROYED_e:
                m7A6 = 0xFF;
                setStt(mPrevStatus);
                m7B8 = 0;
                m7B5 = 0;
                endEvent();
                break;
            default:
                break;
        }
    }
    return TRUE;
}

/* 00002020-000020C0       .text wait_action1__11daNpc_De1_cFPv */
BOOL daNpc_De1_c::wait_action1(void*) {
    if (mStep == 0) {
        setStt(6);
        ccCreate();
        mStep++;
    } else if (mStep != -1) {
        mbAttention = chkAttention();
        switch (mStatus) {
            case 6:
                wait04();
                break;
            case 7:
                wait05();
                break;
            default:
                break;
        }
    }
    return TRUE;
}

/* 000020C0-000021AC       .text wait_action2__11daNpc_De1_cFPv */
BOOL daNpc_De1_c::wait_action2(void*) {
    if (mStep == 0) {
        setStt(1);
        mStep++;
    } else if (mStep != -1) {
        if (mStep == 1) {
            partner_srch();
            mStep++;
        }
        mbAttention = chkAttention();
        switch (mStatus) {
            case 1:
                wait01();
                break;
            case 2:
                talk01();
                break;
            case 3:
                wait02();
                break;
            case 4:
                talk02();
                break;
            case 5:
                wait03();
                break;
            default:
                break;
        }
    }
    return TRUE;
}

/* 000021AC-00002248       .text demo__11daNpc_De1_cFv */
bool daNpc_De1_c::demo() {
    if (demoActorID == 0) {
        if (mbInDemo != 0) {
            mbInDemo = 0;
        }
    } else {
        mbInDemo = 1;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        dDemo_setDemoData(this, 0x6A, mpMorf, "De", NULL, 0, 0, 0);
    }
    return mbInDemo;
}

/* 00002248-00002358       .text _draw__11daNpc_De1_cFv */
BOOL daNpc_De1_c::_draw() {
    J3DModel* morf_model = mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model, &tevStr);
    dComIfGd_setListBG();
    mpMorf->entryDL();
    dComIfGd_setList();
    if (l_HIO.mPrmTbl.mDebug != 0) {
        fopAc_ac_c* partner = searchByID(mPartnerProcID);
        if (partner != NULL) {
            cXyz pos = partner->current.pos;
            pos.y = 950.0f;
            // Debug:
            (GXColor){0xFF, 0x00, 0x00, 0x80};
            (GXColor){0x00, 0x00, 0xFF, 0x80};
            (GXColor){0xFF, 0x00, 0x00, 0x80};
            (GXColor){0x00, 0x00, 0xFF, 0x80};
            (GXColor){0x00, 0xFF, 0x00, 0x80};
        }
    }
    dSnap_RegistFig(0xA6, this, 50.0f, 50.0f, 50.0f);
    return TRUE;
}

/* 00002358-00002454       .text _execute__11daNpc_De1_cFv */
BOOL daNpc_De1_c::_execute() {
    if (mbRanExecute == 0) {
        mInitialPos = current.pos;
        mInitialAngle = current.angle;
        mbRanExecute = 1;
    }
    checkOrder();
    if (!demo()) {
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
            event_proc();
        } else {
            (this->*mCurrProcFunc)(NULL);
        }
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        shape_angle = current.angle;
    }
    eventOrder();
    setMtx();
    return TRUE;
}

/* 00002454-00002500       .text _delete__11daNpc_De1_cFv */
BOOL daNpc_De1_c::_delete() {
    dComIfG_resDelete(&mPhs, "De");
    dComIfG_Bgsp()->Release(mpDeform);
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    del_pa_happa();
    if (l_HIO.mRefCount >= 0) {
        if (--l_HIO.mRefCount < 0) {
            mDoHIO_root.m_subroot.deleteChild(l_HIO.mChildID);
        }
    }
    return TRUE;
}

/* 00002500-00002520       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_De1_c*>(i_this)->CreateHeap();
}

/* 00002520-000027A4       .text _create__11daNpc_De1_cFv */
cPhs_State daNpc_De1_c::_create() {
    fopAcM_ct_Retail(this, daNpc_De1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "De");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (l_HIO.mRefCount < 0) {
        l_HIO.mChildID = mDoHIO_root.m_subroot.createChild("デクの木", &l_HIO);
    }
    l_HIO.mRefCount++;
    {
        static int a_heap_size_tbl[] = {0x272E0};
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_heap_size_tbl[mType])) {
            return cPhs_ERROR_e;
        }
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    dComIfG_Bgsp()->Regist(mpDeform, this);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 00002AB0-00002E04       .text CreateHeap__11daNpc_De1_cFv */
BOOL daNpc_De1_c::CreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("De", dRes_ID_DE_BDL_DE_e);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat,
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("De", dRes_ID_DE_BCK_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        2,
        NULL,
        0x80000,
        0x11000002
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    m_branchL_jnt_num = a_mdl_dat->getJointName()->getIndex("branchL");
    JUT_ASSERT(0x6d0, m_branchL_jnt_num >= 0);
    m_head_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x6d2, m_head_jnt_num >= 0);
    {
        static char* a_jnt_name_tbl[] = {
            "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "c10",
        };
        for (int i = 0; i < 10; i++) {
            m_c0_jnt_num[i] = a_mdl_dat->getJointName()->getIndex(a_jnt_name_tbl[i]);
            JUT_ASSERT(0x6d5, m_c0_jnt_num[ i] >= 0);
        }
    }
    mpMorf->getModel()->setUserArea(0);
    mpDeform = new dBgWDeform();
    if (mpDeform != NULL) {
        if (mpDeform->Set((cBgD_t*)dComIfG_getObjectIDRes("De", dRes_ID_DE_DZB_DE_e), mpMorf->getModel(), 0)) {
            return FALSE;
        }
        mAcchCir.SetWall(0.0f, 0.0f);
        mObjAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, NULL, NULL);
        mObjAcch.SetWaterNone();
        mObjAcch.SetWallNone();
        mObjAcch.SetRoofNone();
        return TRUE;
    }
    return FALSE;
}

/* 00002E04-00002E24       .text daNpc_De1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_De1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_create();
}

/* 00002E24-00002E44       .text daNpc_De1_Delete__FP11daNpc_De1_c */
static BOOL daNpc_De1_Delete(daNpc_De1_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_delete();
}

/* 00002E44-00002E64       .text daNpc_De1_Execute__FP11daNpc_De1_c */
static BOOL daNpc_De1_Execute(daNpc_De1_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_execute();
}

/* 00002E64-00002E84       .text daNpc_De1_Draw__FP11daNpc_De1_c */
static BOOL daNpc_De1_Draw(daNpc_De1_c* i_this) {
    return ((daNpc_De1_c*)i_this)->_draw();
}

/* 00002E84-00002E8C       .text daNpc_De1_IsDelete__FP11daNpc_De1_c */
static BOOL daNpc_De1_IsDelete(daNpc_De1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_De1_Method = {
    (process_method_func)daNpc_De1_Create,
    (process_method_func)daNpc_De1_Delete,
    (process_method_func)daNpc_De1_Execute,
    (process_method_func)daNpc_De1_IsDelete,
    (process_method_func)daNpc_De1_Draw,
};

actor_process_profile_definition g_profile_NPC_DE1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_DE1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_De1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_DE1_e,
    /* Actor SubMtd */ &l_daNpc_De1_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
