/**
 * d_a_npc_yw1.cpp
 * NPC - Sue-Belle
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_yw1.h"

/* 000000EC-00000108       .text __ct__20daNpc_Yw1_childHIO_cFv */
daNpc_Yw1_childHIO_c::daNpc_Yw1_childHIO_c() {}

/* 00000150-000001DC       .text __ct__15daNpc_Yw1_HIO_cFv */
daNpc_Yw1_HIO_c::daNpc_Yw1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX      */ 0x2000,
        /* mMaxHeadY      */ 0x1E78,
        /* mMinHeadX      */ 0xE000,
        /* mMinHeadY      */ 0xE188,
        /* mMaxBackboneX  */ 0x0000,
        /* mMaxBackboneY  */ 0x20D0,
        /* mMinBackboneX  */ 0x0000,
        /* mMinBackboneY  */ 0xDF30,
        /* mMaxTurnStep   */ 0x0640,
        /* mCalcAngleTarget */ 0x04B0,
        /* mAttPosOffsetY */ 170.0f,
        /* m18            */ 0.0f,
        /* mMaxAttnDistXZ */ 300.0f,
        /* mMaxAttnAngleY */ 0x0006,
        /* m22            */ 0x0400,
        /* m24            */ 0.95f,
        /* m28            */ 1.2f,
        /* m2C            */ 0.5f,
    };
    mChildHIO[0].field_0x34 = 0;
    memcpy(&mChildHIO[0].field_0x04, (const u8*)&a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

/* 00000238-00000284       .text nodeCB_Hair__FP7J3DNodei */
static BOOL nodeCB_Hair(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000284-00000414       .text _nodeCB_Hair__11daNpc_Yw1_cFP7J3DNodeP8J3DModel */
void daNpc_Yw1_c::_nodeCB_Hair(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 00000450-0000049C       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000049C-000005BC       .text _nodeCB_Head__11daNpc_Yw1_cFP7J3DNodeP8J3DModel */
void daNpc_Yw1_c::_nodeCB_Head(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 000005BC-00000608       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000608-000006A8       .text _nodeCB_BackBone__11daNpc_Yw1_cFP7J3DNodeP8J3DModel */
void daNpc_Yw1_c::_nodeCB_BackBone(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 000006A8-000006C8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Yw1_c*>(i_this)->CreateHeap();
}

/* 000006C8-00000740       .text searchActor_Bm1__FPvPv */
void searchActor_Bm1(void*, void*) {
    /* Nonmatching */
}

/* 00000740-00000844       .text init_YW1_0__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::init_YW1_0() {
    /* Nonmatching */
}

/* 00000844-000008F8       .text init_YW1_1__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::init_YW1_1() {
    /* Nonmatching */
}

/* 000008F8-000009A4       .text init_YW1_2__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::init_YW1_2() {
    /* Nonmatching */
}

/* 000009A4-00000AB4       .text init_YW1_3__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::init_YW1_3() {
    /* Nonmatching */
}

/* 00000AB4-00000C9C       .text createInit__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::createInit() {
    /* Nonmatching */
}

/* 00000C9C-00000D44       .text play_animation__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::play_animation() {
    /* Nonmatching */
}

/* 00000D44-00000E4C       .text upLift__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::upLift() {
    /* Nonmatching */
}

/* 00000E4C-00000F48       .text setMtx__11daNpc_Yw1_cFb */
void daNpc_Yw1_c::setMtx(bool) {
    /* Nonmatching */
}

/* 00000F48-00000F5C       .text bckResID__11daNpc_Yw1_cFi */
int daNpc_Yw1_c::bckResID(int param) {
    static const int a_res_id_tbl[] = {0, 3, 4, 2, 1, 5, 9};
    return a_res_id_tbl[param];
}

/* 00000F5C-00000F70       .text btpResID__11daNpc_Yw1_cFi */
int daNpc_Yw1_c::btpResID(int param) {
    static const int a_res_id_tbl[] = {8};
    return a_res_id_tbl[param];
}

/* 00000F70-00001078       .text init_texPttrnAnm__11daNpc_Yw1_cFScb */
void daNpc_Yw1_c::init_texPttrnAnm(signed char, bool) {
    /* Nonmatching */
}

/* 00001078-00001108       .text play_texPttrnAnm__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::play_texPttrnAnm() {
    /* Nonmatching */
}

/* 00001108-000011AC       .text setAnm_anm__11daNpc_Yw1_cFPQ211daNpc_Yw1_c9anm_prm_c */
void daNpc_Yw1_c::setAnm_anm(daNpc_Yw1_c::anm_prm_c* i_anmPrmP) {
    /* Nonmatching */
    if (i_anmPrmP->mAnmNum < 0) {
        return;
    }
    if (mAnmNum == i_anmPrmP->mAnmNum) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, bckResID(i_anmPrmP->mAnmNum), -1, "Yw");
    mAnmNum = i_anmPrmP->mAnmNum;
    m770 = 0;
    m771 = 0;
    m750 = 0.0f;
}

/* 000011AC-0000121C       .text setAnm_NUM__11daNpc_Yw1_cFii */
void daNpc_Yw1_c::setAnm_NUM(int i_anmNum, int i_texOn) {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    if (i_texOn != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].mBtpNum, 1);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 0000121C-00001288       .text setAnm__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {-1, -1, 0, 0.0f, 0.0f, -1},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0, 0.0f, 0.0f, -1},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mStt].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* 00001288-0000128C       .text chngAnmTag__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::chngAnmTag() {
}

/* 0000128C-00001290       .text ctrlAnmTag__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::ctrlAnmTag() {
}

/* 00001290-000012D0       .text chngAnmAtr__11daNpc_Yw1_cFUc */
void daNpc_Yw1_c::chngAnmAtr(unsigned char i_param) {
    if (i_param == mAnmAtr || i_param > 7) {
        return;
    }
    mAnmAtr = i_param;
    setAnm_ATR();
}

/* 000012D0-000012D4       .text ctrlAnmAtr__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::ctrlAnmAtr() {
}

/* 000012D4-00001338       .text setAnm_ATR__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {4, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].mBtpNum, 1);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00001338-000013F4       .text anmAtr__11daNpc_Yw1_cFUs */
void daNpc_Yw1_c::anmAtr(unsigned short i_param) {
    u32 mesgAnimeTagInfo;
    switch (i_param) {
        case 6:
            if (m7C8 == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m7C8++;
            }
            mesgAnimeTagInfo = dComIfGp_getMesgAnimeTagInfo();
            if (mesgAnimeTagInfo != 0xFF && mesgAnimeTagInfo != mAnmTag) {
                dComIfGp_clearMesgAnimeTagInfo();
                mAnmTag = mesgAnimeTagInfo;
                chngAnmTag();
            }
            break;
        case 0xE:
            m7C8 = 0;
            break;
        default:
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 000013F4-0000148C       .text next_msgStatus__11daNpc_Yw1_cFPUl */
u16 daNpc_Yw1_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    switch ((s32)*pMsgNo) {
        case 0x8A3:
            if (!dComIfGs_isEventBit(0x2A20)) {
                *pMsgNo = 0x8A4;
            } else if (dKy_daynight_check() == dKy_TIME_DAY_e) {
                *pMsgNo = 0x8A6;
            } else {
                *pMsgNo = 0x8A5;
            }
            break;
        default:
            status = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return status;
}

/* 0000148C-00001588       .text getMsg_YW1_0__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_0() {
    if (m774) {
        return 0x8A0;
    }
    if (m775) {
        return 0x89F;
    }
    if (dComIfGs_isEventBit(0x1)) {
        return dComIfGs_isEventBit(0x140) ? 0x89C : 0x89B;
    }
    if (m70C != 0 && m776 == 1) {
        return m712 == 1 ? 0x8A2 : 0x8A1;
    }
    if (dComIfGs_isEventBit(0x180) == false) {
        u32 msg = 0x899;
        if (dComIfGs_isEventBit(0x2A80)) {
            return 0x8AA;
        }
        return msg;
    }
    return 0x89A;
}

/* 00001588-00001600       .text getMsg_YW1_1__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_1() {
    if (dComIfGs_isEventBit(0xE20)) {
        return dComIfGs_isEventBit(0x120) ? 0x89E : 0x89D;
    }
    return dComIfGs_isEventBit(0x140) ? 0x89C : 0x89B;
}

/* 00001600-00001678       .text getMsg_YW1_2__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_2() {
    if (!dComIfGs_isEventBit(0x3A40)) {
        return 0x8A3;
    }
    if (!dComIfGs_isEventBit(0x2A20)) {
        return 0x8A7;
    }
    return dKy_daynight_check() == dKy_TIME_DAY_e ? 0x8A9 : 0x8A8;
}

/* 00001678-000016F0       .text getMsg_YW1_3__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_3() {
    if (m774) {
        return 0x8A0;
    }
    if (m775) {
        return 0x89F;
    }
    if (m70C != 0 && m776 == 1) {
        return m712 == 1 ? 0x8A2 : 0x8A1;
    }
    return getMsg_YW1_2();
}

/* 000016F0-00001770       .text getMsg__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg() {
    u32 msg = 0;
    switch (m7C6) {
        case 0:
            msg = getMsg_YW1_0();
            break;
        case 1:
            msg = getMsg_YW1_1();
            break;
        case 2:
            msg = getMsg_YW1_2();
            break;
        case 3:
            msg = getMsg_YW1_3();
            break;
        default:
            break;
    }
    return msg;
}

/* 00001770-000017C0       .text eventOrder__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::eventOrder() {
    s8 condition = mStatus;
    if (condition == 1 || condition == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mStatus == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000017C0-00001800       .text checkOrder__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::checkOrder() {
    if (eventInfo.getCommand() != dEvtCmd_INDEMO_e && eventInfo.getCommand() == dEvtCmd_INTALK_e) {
        if (mStatus == 1 || mStatus == 2) {
            mStatus = 0;
            m77C = 1;
        }
    }
}

/* 00001800-00001898       .text chk_talk__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            m772 = dComIfGp_event_getPreItemNo();
            return true;
        }
        return false;
    }
    m772 = 0xFF;
    return true;
}

/* 00001898-000018D8       .text chk_parts_notMov__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::chk_parts_notMov() {
    return m75A == m_jnt.getHead_y() && m75C == m_jnt.getBackbone_y() && m758 == current.angle.y;
}

/* 000018D8-00001938       .text searchByID__11daNpc_Yw1_cFUiPi */
void daNpc_Yw1_c::searchByID(fpc_ProcID, int*) {
    /* Nonmatching */
}

/* 00001938-000019E8       .text partner_search_sub__11daNpc_Yw1_cFPFPvPv_Pv */
void daNpc_Yw1_c::partner_search_sub(void* (*)(void*, void*)) {
    /* Nonmatching */
}

/* 000019E8-00001A54       .text partner_search__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::partner_search() {
    /* Nonmatching */
}

/* 00001A54-00001C2C       .text lookBack__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::lookBack() {
    /* Nonmatching */
}

/* 00001C2C-00001CAC       .text chkAttention__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::chkAttention() {
    /* Nonmatching */
}

/* 00001CAC-00001D28       .text setAttention__11daNpc_Yw1_cFb */
void daNpc_Yw1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 00001D28-00001DC4       .text decideType__11daNpc_Yw1_cFi */
void daNpc_Yw1_c::decideType(int) {
    /* Nonmatching */
}

/* 00001DC4-00001E64       .text privateCut__11daNpc_Yw1_cFi */
void daNpc_Yw1_c::privateCut(int) {
    /* Nonmatching */
}

/* 00001E64-00001E88       .text endEvent__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mAnmTag = 0xFF;
}

/* 00001E88-00001EC0       .text isEventEntry__11daNpc_Yw1_cFv */
s32 daNpc_Yw1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 00001EC0-00001F18       .text event_proc__11daNpc_Yw1_cFi */
void daNpc_Yw1_c::event_proc(int i_param) {
    if (!mEventCut.cutProc()) {
        privateCut(i_param);
    }
    lookBack();
}

/* 00001F18-00001FC4       .text set_action__11daNpc_Yw1_cFM11daNpc_Yw1_cFPCvPvPv_iPv */
int daNpc_Yw1_c::set_action(int (daNpc_Yw1_c::*i_action)(void*), void* i_arg) {
    if (mCurrProcFunc != i_action) {
        if (mCurrProcFunc != NULL) {
            m7C7 = 9;
            (this->*mCurrProcFunc)(i_arg);
        }
        mCurrProcFunc = i_action;
        m7C7 = 0;
        (this->*mCurrProcFunc)(i_arg);
    }
    return 1;
}

/* 00001FC4-0000205C       .text setStt__11daNpc_Yw1_cFSc */
void daNpc_Yw1_c::setStt(signed char i_stt) {
    s8 prevStt = mStt;
    mStt = i_stt;
    switch (mStt) {
        case 2:
            mAnmAtr = 0xFF;
            mAnmTag = 0xFF;
            m7C8 = 0;
            m7C3 = prevStt;
            break;
        case 3:
        case 5:
            m77D = 1;
            break;
        case 4:
        case 6:
            break;
        default:
            break;
    }
    setAnm();
    chngTsuboAnm();
}

/* 0000205C-0000212C       .text chngTsuboAnm__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::chngTsuboAnm() {
    /* Nonmatching */
}

/* 0000212C-000022B8       .text chk_areaIN__11daNpc_Yw1_cFffs4cXyz */
void daNpc_Yw1_c::chk_areaIN(float, float, short, cXyz) {
    /* Nonmatching */
}

/* 000022B8-00002360       .text set_pthPoint__11daNpc_Yw1_cFUc */
void daNpc_Yw1_c::set_pthPoint(unsigned char) {
    /* Nonmatching */
}

/* 00002360-00002D94       .text setHairAngle__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::setHairAngle() {
    /* Nonmatching */
}

/* 00002D94-00002DEC       .text chk_brkTsubo__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::chk_brkTsubo() {
    /* Nonmatching */
}

/* 00002DEC-00002E28       .text chk_bm1Odoroki__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::chk_bm1Odoroki() {
    /* Nonmatching */
}

/* 00002E28-00002F90       .text wait_1__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::wait_1() {
    /* Nonmatching */
}

/* 00002F90-0000309C       .text wait_2__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::wait_2() {
    /* Nonmatching */
}

/* 0000309C-00003174       .text wait_3__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::wait_3() {
    /* Nonmatching */
}

/* 00003174-0000347C       .text walk_1__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::walk_1() {
    /* Nonmatching */
}

/* 0000347C-00003594       .text turn_1__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::turn_1() {
    /* Nonmatching */
}

/* 00003594-000036F0       .text talk_1__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::talk_1() {
    /* Nonmatching */
}

/* 000036F0-00003848       .text wait_action1__11daNpc_Yw1_cFPv */
void daNpc_Yw1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00003848-00003904       .text wait_action2__11daNpc_Yw1_cFPv */
void daNpc_Yw1_c::wait_action2(void*) {
    /* Nonmatching */
}

/* 00003904-00003A50       .text demo__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::demo() {
    /* Nonmatching */
}

/* 00003A50-00003B4C       .text shadowDraw__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::shadowDraw() {
    /* Nonmatching */
}

/* 00003B4C-00003C84       .text _draw__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::_draw() {
    /* Nonmatching */
}

/* 00003C84-00003EDC       .text _execute__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::_execute() {
    /* Nonmatching */
}

/* 00003EDC-00003F38       .text _delete__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::_delete() {
    /* Nonmatching */
}

/* 00003F38-0000417C       .text _create__11daNpc_Yw1_cFv */
cPhs_State daNpc_Yw1_c::_create() {
    /* Nonmatching */
}

/* 00004448-0000469C       .text bodyCreateHeap__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::bodyCreateHeap() {
    /* Nonmatching */
}

/* 0000469C-00004930       .text headCreateHeap__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::headCreateHeap() {
    /* Nonmatching */
}

/* 00004930-000049D0       .text CreateHeap__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::CreateHeap() {
    /* Nonmatching */
}

/* 000049D0-000049F0       .text daNpc_Yw1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Yw1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_create();
}

/* 000049F0-00004A10       .text daNpc_Yw1_Delete__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_Delete(daNpc_Yw1_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_delete();
}

/* 00004A10-00004A30       .text daNpc_Yw1_Execute__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_Execute(daNpc_Yw1_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_execute();
}

/* 00004A30-00004A50       .text daNpc_Yw1_Draw__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_Draw(daNpc_Yw1_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_draw();
}

/* 00004A50-00004A58       .text daNpc_Yw1_IsDelete__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_IsDelete(daNpc_Yw1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Yw1_Method = {
    (process_method_func)daNpc_Yw1_Create,
    (process_method_func)daNpc_Yw1_Delete,
    (process_method_func)daNpc_Yw1_Execute,
    (process_method_func)daNpc_Yw1_IsDelete,
    (process_method_func)daNpc_Yw1_Draw,
};

actor_process_profile_definition g_profile_NPC_YW1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_YW1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Yw1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_YW1_e,
    /* Actor SubMtd */ &l_daNpc_Yw1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
