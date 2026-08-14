/**
 * d_a_npc_ko1.cpp
 * NPC - Joel & Zill (Outset Island)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ko1.h"
#include "d/d_a_obj.h"
#include "d/d_com_lib_game.h"
#include "d/d_demo.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_executor.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_counter.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "m_Do/m_Do_mtx.h"

/* 000000EC-00000108       .text __ct__20daNpc_Ko1_childHIO_cFv */
daNpc_Ko1_childHIO_c::daNpc_Ko1_childHIO_c() {}

/* 00000150-0000020C       .text __ct__15daNpc_Ko1_HIO_cFv */
daNpc_Ko1_HIO_c::daNpc_Ko1_HIO_c() { /* Nonmatching */
    static u8 a_prm_tbl[0xB0] = {
        0x40, 0x1F, 0x00, 0x20, 0xC0, 0xE0, 0xC0, 0xE0, 0x40, 0x1F, 0x00, 0x00, 0xC0, 0xE0, 0x00, 0x00,
        0x40, 0x06, 0xD0, 0x07, 0x00, 0x00, 0xB4, 0x42, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
        0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xA8, 0x41,
        0xCD, 0xCC, 0xCC, 0x3D, 0x00, 0x00, 0x20, 0x41, 0x9A, 0x99, 0x99, 0x3E, 0x00, 0x00, 0x20, 0x42,
        0x00, 0x00, 0xA0, 0x42, 0x00, 0x00, 0x48, 0x43, 0x00, 0x00, 0x96, 0x43, 0x00, 0x00, 0x16, 0x43,
        0x00, 0x80, 0x89, 0x44, 0x00, 0x80, 0xBB, 0x44, 0x40, 0x1F, 0x00, 0x20, 0xC0, 0xE0, 0xC0, 0xE0,
        0x40, 0x1F, 0x00, 0x00, 0xC0, 0xE0, 0x00, 0x00, 0x40, 0x06, 0xD0, 0x07, 0x00, 0x00, 0xB4, 0x42,
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x9A, 0x99, 0x99, 0x3E, 0x00, 0x00, 0xC0, 0x40,
        0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0xA8, 0x41, 0xCD, 0xCC, 0xCC, 0x3D, 0x00, 0x00, 0x40, 0x41,
        0x00, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0xC8, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAF, 0x43,
        0x00, 0x00, 0xFA, 0x43, 0x00, 0x00, 0x16, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    for (int i = 0; i < 2; i++) {
        mChild[i].mIdx = i;
        memcpy(mChild[i].mPrm, &a_prm_tbl[i * 0x58], 0x58);
    }
    mNo = -1;
    field_0x8 = -1;
}

static daNpc_Ko1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 00000268-000002E0       .text searchActor_Ko_Hna__FPvPv */
static void* searchActor_Ko_Hna(void* i_actor, void*) {
    if (l_check_wrk < 0x14 && fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == 0x141) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 000002E0-00000358       .text searchActor_Ko_Bou__FPvPv */
static void* searchActor_Ko_Bou(void* i_actor, void*) {
    if (l_check_wrk < 0x14 && fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == 0x142) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 00000358-000003D0       .text searchActor_Ob__FPvPv */
static void* searchActor_Ob(void* i_actor, void*) {
    if (l_check_wrk < 0x14 && fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == 0x14D) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 000003D0-0000041C       .text nodeCallBack_Hed__FP7J3DNodei */
static BOOL nodeCallBack_Hed(J3DNode* i_node, int i_judge) {
    if (i_judge == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ko1_c*>(j3dSys.getModel()->getUserArea())->nodeHedControl(
                i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000041C-00000488       .text nodeHedControl__11daNpc_Ko1_cFP7J3DNodeP8J3DModel */
void daNpc_Ko1_c::nodeHedControl(J3DNode* i_node, J3DModel* i_model) {
    s32 jointIdx = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    if (jointIdx == mHedJntNo) {
        PSMTXCopy(mDoMtx_stack_c::get(), mMtx);
    }
}

/* 00000488-000004D4       .text nodeCallBack_Bln__FP7J3DNodei */
static BOOL nodeCallBack_Bln(J3DNode* i_node, int i_judge) {
    if (i_judge == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ko1_c*>(j3dSys.getModel()->getUserArea())->nodeBlnControl(
                i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000004D4-00000554       .text nodeBlnControl__11daNpc_Ko1_cFP7J3DNodeP8J3DModel */
void daNpc_Ko1_c::nodeBlnControl(J3DNode* i_node, J3DModel* i_model) {
    s32 jointIdx = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    if (jointIdx == mBlnJntNo) {
        PSMTXCopy(mMtx, j3dSys.mCurrentMtx);
        PSMTXCopy(mMtx, i_model->getAnmMtx(jointIdx));
    }
}

/* 00000554-000005A0       .text nodeCallBack_Ko1__FP7J3DNodei */
static BOOL nodeCallBack_Ko1(J3DNode* i_node, int i_judge) {
    if (i_judge == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Ko1_c*>(j3dSys.getModel()->getUserArea())->nodeKo1Control(
                i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000005A0-000006E8       .text nodeKo1Control__11daNpc_Ko1_cFP7J3DNodeP8J3DModel */
void daNpc_Ko1_c::nodeKo1Control(J3DNode* i_node, J3DModel* i_model) { /* Nonmatching */
    static cXyz a_eye_pos_off(0.0f, 0.0f, 0.0f);

    s32 jointIdx = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jointIdx));
    if (jointIdx == mJntNo1) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &m7DC);
    }
    if (jointIdx == mJntNo2) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::YrotM(m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
}

/* 00000724-000007CC       .text init_HNA_0__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_HNA_0() { /* Nonmatching */
    return FALSE;
}

/* 000007CC-00000860       .text init_HNA_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_HNA_1() { /* Nonmatching */
    return FALSE;
}

/* 00000860-000008E8       .text init_HNA_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_HNA_2() { /* Nonmatching */
    return FALSE;
}

/* 000008E8-00000994       .text init_HNA_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_HNA_3() { /* Nonmatching */
    return FALSE;
}

/* 00000994-00000A20       .text init_HNA_4__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_HNA_4() { /* Nonmatching */
    return FALSE;
}

/* 00000A20-00000AAC       .text init_BOU_0__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_BOU_0() { /* Nonmatching */
    return FALSE;
}

/* 00000AAC-00000B38       .text init_BOU_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_BOU_1() { /* Nonmatching */
    return FALSE;
}

/* 00000B38-00000BE4       .text init_BOU_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_BOU_2() { /* Nonmatching */
    return FALSE;
}

/* 00000BE4-00000C78       .text init_BOU_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::init_BOU_3() { /* Nonmatching */
    return FALSE;
}

/* 00000C78-00000F14       .text createInit__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::createInit() { /* Nonmatching */
    return FALSE;
}

/* 00000F14-000011C4       .text setMtx__11daNpc_Ko1_cFb */
void daNpc_Ko1_c::setMtx(bool) { /* Nonmatching */
}

/* 000011C4-000011D8       .text anmNum_toResID__11daNpc_Ko1_cFi */
int daNpc_Ko1_c::anmNum_toResID(int i_anmNum) { /* Nonmatching */
    static const int a_bck_resID_tbl[] = {0x16, 0x0F, 0x18, 0x15, 0x14, 0x0D, 0x17, 0x10, 0x11, 0x12, 0x13, 0x0E, 0x0C, 0x26};
    return a_bck_resID_tbl[i_anmNum];
}

/* 000011D8-00001200       .text headAnmNum_toResID__11daNpc_Ko1_cFi */
int daNpc_Ko1_c::headAnmNum_toResID(int i_anmNum) { /* Nonmatching */
    static const int a_bck_resID_tbl[] = {0x0A, 0x05, 0x0B, 0x09, 0x08, 0x03, 0x0A, 0x0A, 0x0A, 0x06, 0x07, 0x04, 0x02, 0x0A};
    if ((s32)mCharNo == 1) {
        return 0x25;
    }
    return a_bck_resID_tbl[i_anmNum];
}

/* 00001200-00001214       .text balloon_anmNum_toResID__11daNpc_Ko1_cFi */
int daNpc_Ko1_c::balloon_anmNum_toResID(int i_anmNum) { /* Nonmatching */
    static const int a_bck_resID_tbl[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    return a_bck_resID_tbl[i_anmNum];
}

/* 00001214-0000129C       .text btpNum_toResID__11daNpc_Ko1_cFi */
int daNpc_Ko1_c::btpNum_toResID(int i_btpNum) { /* Nonmatching */
    static const int a_btp_resID_tbl[] = {0x1F, 0x22, 0x20, 0x21};
    int resID = a_btp_resID_tbl[i_btpNum];
    switch (resID) {
    case 0x1F: {
        int ch = (s8)mCharNo;
        if (ch != 1) {
            if (ch > 1) {
                return (int)this;
            }
            if (ch < 0) {
                return (int)this;
            }
            return 0x1F;
        }
        return 0x23;
    }
    case 0x20: {
        int ch = (s8)mCharNo;
        if (ch != 1) {
            if (ch > 1) {
                return (int)this;
            }
            if (ch < 0) {
                return (int)this;
            }
            return 0x20;
        }
        return 0x24;
    }
    }
    return resID;
}

/* 0000129C-000013AC       .text setBtp__11daNpc_Ko1_cFbi */
void daNpc_Ko1_c::setBtp(bool, int) { /* Nonmatching */
}

/* 000013AC-000013D4       .text iniTexPttrnAnm__11daNpc_Ko1_cFb */
void daNpc_Ko1_c::iniTexPttrnAnm(bool) { /* Nonmatching */
}

/* 000013D4-00001480       .text plyTexPttrnAnm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::plyTexPttrnAnm() { /* Nonmatching */
}

/* 00001480-000014BC       .text setAnm_tex__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::setAnm_tex(signed char) { /* Nonmatching */
}

/* 000014BC-000015B4       .text setAnm_anm__11daNpc_Ko1_cFPQ211daNpc_Ko1_c9anm_prm_c */
void daNpc_Ko1_c::setAnm_anm(daNpc_Ko1_c::anm_prm_c*) { /* Nonmatching */
}

/* 000015B4-00001674       .text set_balloonAnm_anm__11daNpc_Ko1_cFPQ211daNpc_Ko1_c9anm_prm_c */
void daNpc_Ko1_c::set_balloonAnm_anm(daNpc_Ko1_c::anm_prm_c*) { /* Nonmatching */
}

/* 00001674-000016A4       .text set_balloonAnm_NUM__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::set_balloonAnm_NUM(int) { /* Nonmatching */
}

/* 000016A4-00001710       .text setAnm_NUM__11daNpc_Ko1_cFii */
void daNpc_Ko1_c::setAnm_NUM(int, int) { /* Nonmatching */
}

/* 00001710-00001790       .text setAnm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::setAnm() { /* Nonmatching */
}

/* 00001790-000017A4       .text setPlaySpd__11daNpc_Ko1_cFf */
void daNpc_Ko1_c::setPlaySpd(float) { /* Nonmatching */
}

/* 000017A4-000017DC       .text chg_anmTag__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::chg_anmTag() { /* Nonmatching */
}

/* 000017DC-00001824       .text control_anmTag__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::control_anmTag() { /* Nonmatching */
}

/* 00001824-000018D8       .text chg_anmAtr__11daNpc_Ko1_cFUc */
void daNpc_Ko1_c::chg_anmAtr(unsigned char) { /* Nonmatching */
}

/* 000018D8-0000192C       .text control_anmAtr__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::control_anmAtr() { /* Nonmatching */
}

/* 0000192C-00001994       .text setAnm_ATR__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::setAnm_ATR(int) { /* Nonmatching */
}

/* 00001994-00001A9C       .text anmAtr__11daNpc_Ko1_cFUs */
void daNpc_Ko1_c::anmAtr(unsigned short) { /* Nonmatching */
}

/* 00001A9C-00001AEC       .text eventOrder__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::eventOrder() { /* Nonmatching */
}

/* 00001AEC-00001B2C       .text checkOrder__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::checkOrder() { /* Nonmatching */
}

/* 00001B2C-00001BCC       .text chk_talk__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::chk_talk() { /* Nonmatching */
    return FALSE;
}

/* 00001BCC-00001E0C       .text chk_manzai_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::chk_manzai_1() { /* Nonmatching */
    return FALSE;
}

/* 00001E0C-00001E4C       .text chk_partsNotMove__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::chk_partsNotMove() { /* Nonmatching */
    return FALSE;
}

/* 00001E4C-00001FFC       .text lookBack__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::lookBack() { /* Nonmatching */
}

/* 00001FFC-00002204       .text next_msgStatus__11daNpc_Ko1_cFPUl */
u16 daNpc_Ko1_c::next_msgStatus(unsigned long*) { /* Nonmatching */
    return 0;
}

/* 00002204-00002240       .text getMsg_HNA_0__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg_HNA_0() { /* Nonmatching */
    return 0;
}

/* 00002240-0000227C       .text getMsg_HNA_1__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg_HNA_1() { /* Nonmatching */
    return 0;
}

/* 0000227C-000022B8       .text getMsg_HNA_2__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg_HNA_2() { /* Nonmatching */
    return 0;
}

/* 000022B8-00002318       .text getMsg_HNA_3__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg_HNA_3() { /* Nonmatching */
    return 0;
}

/* 00002318-0000237C       .text getMsg_BOU_0__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg_BOU_0() { /* Nonmatching */
    return 0;
}

/* 0000237C-000023B8       .text getMsg_BOU_1__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg_BOU_1() { /* Nonmatching */
    return 0;
}

/* 000023B8-000023E8       .text bitCount__11daNpc_Ko1_cFUc */
u8 daNpc_Ko1_c::bitCount(unsigned char) { /* Nonmatching */
    return 0;
}

/* 000023E8-0000248C       .text getMsg_BOU_2__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg_BOU_2() { /* Nonmatching */
    return 0;
}

/* 0000248C-00002528       .text getMsg__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg() { /* Nonmatching */
    return 0;
}

/* 00002528-000025A8       .text chkAttention__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::chkAttention() { /* Nonmatching */
    return FALSE;
}

/* 000025A8-00002610       .text setAttention__11daNpc_Ko1_cFb */
void daNpc_Ko1_c::setAttention(bool) { /* Nonmatching */
}

/* 00002610-00002644       .text searchByID__11daNpc_Ko1_cFUi */
fopAc_ac_c* daNpc_Ko1_c::searchByID(unsigned int i_id) {
    fopAc_ac_c* actor = NULL;
    fopAcM_SearchByID(i_id, &actor);
    return actor;
}

/* 00002644-000026DC       .text partner_srch_sub__11daNpc_Ko1_cFPFPvPv_Pv */
void* daNpc_Ko1_c::partner_srch_sub(void* (*)(void*, void*)) { /* Nonmatching */
    return NULL;
}

/* 000026DC-000027CC       .text partner_srch__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::partner_srch() { /* Nonmatching */
}

/* 000027CC-00002900       .text check_landOn__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::check_landOn() { /* Nonmatching */
    return FALSE;
}

/* 00002900-0000299C       .text ko_setPthPos__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_setPthPos() { /* Nonmatching */
}

/* 0000299C-00002AA4       .text set_tgtPos__11daNpc_Ko1_cF4cXyz */
void daNpc_Ko1_c::set_tgtPos(cXyz) { /* Nonmatching */
}

/* 00002AA4-00002C14       .text ko_movPass__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::ko_movPass() { /* Nonmatching */
    return FALSE;
}

/* 00002C14-00002D50       .text ko_clcMovSpd__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::ko_clcMovSpd() { /* Nonmatching */
    return FALSE;
}

/* 00002D50-00002E3C       .text ko_clcSwmSpd__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::ko_clcSwmSpd() { /* Nonmatching */
    return FALSE;
}

/* 00002E3C-00003028       .text ko_nMove__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_nMove() { /* Nonmatching */
}

/* 00003028-000030E8       .text chk_routeAngle__11daNpc_Ko1_cFR4cXyzPs */
BOOL daNpc_Ko1_c::chk_routeAngle(cXyz&, short*) { /* Nonmatching */
    return FALSE;
}

/* 000030E8-0000334C       .text routeWallCheck__11daNpc_Ko1_cFR4cXyzR4cXyzPs */
BOOL daNpc_Ko1_c::routeWallCheck(cXyz&, cXyz&, short*) { /* Nonmatching */
    return FALSE;
}

/* 00003784-00003A04       .text chk_ForwardGroundY__11daNpc_Ko1_cFs */
BOOL daNpc_Ko1_c::chk_ForwardGroundY(short) { /* Nonmatching */
    return FALSE;
}

/* 00003B9C-00003C54       .text chk_wallJump__11daNpc_Ko1_cFs */
BOOL daNpc_Ko1_c::chk_wallJump(short) { /* Nonmatching */
    return FALSE;
}

/* 00003C54-00003D34       .text routeCheck__11daNpc_Ko1_cFfPs */
BOOL daNpc_Ko1_c::routeCheck(float, short*) { /* Nonmatching */
    return FALSE;
}

/* 00003D34-00003DE8       .text chk_start_swim__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::chk_start_swim() { /* Nonmatching */
    return FALSE;
}

/* 00003DE8-00003E64       .text get_crsActorID__11daNpc_Ko1_cFv */
fopAc_ac_c* daNpc_Ko1_c::get_crsActorID() { /* Nonmatching */
    return NULL;
}

/* 00003E64-00003F50       .text chk_areaIn__11daNpc_Ko1_cFf4cXyz */
BOOL daNpc_Ko1_c::chk_areaIn(float, cXyz) { /* Nonmatching */
    return FALSE;
}

/* 00003F50-00003FF0       .text setPrtcl_Hamon__11daNpc_Ko1_cFff */
void daNpc_Ko1_c::setPrtcl_Hamon(float, float) { /* Nonmatching */
}

/* 00003FF0-000040F8       .text setPrtcl_HanaPachi__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::setPrtcl_HanaPachi() { /* Nonmatching */
}

/* 000040F8-0000420C       .text charDecide__11daNpc_Ko1_cFi */
BOOL daNpc_Ko1_c::charDecide(int) { /* Nonmatching */
    return FALSE;
}

/* 0000420C-00004264       .text event_actionInit__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::event_actionInit(int) { /* Nonmatching */
}

/* 00004264-00004274       .text event_action__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::event_action() { /* Nonmatching */
}

/* 00004274-00004360       .text privateCut__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::privateCut(int) { /* Nonmatching */
}

/* 00004360-00004384       .text endEvent__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::endEvent() { /* Nonmatching */
}

/* 00004384-000043BC       .text isEventEntry__11daNpc_Ko1_cFv */
int daNpc_Ko1_c::isEventEntry() { /* Nonmatching */
    return 0;
}

/* 000043BC-00004414       .text event_proc__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::event_proc(int) { /* Nonmatching */
}

/* 00004414-000044C0       .text set_action__11daNpc_Ko1_cFM11daNpc_Ko1_cFPCvPvPv_iPv */
BOOL daNpc_Ko1_c::set_action(int (daNpc_Ko1_c::*)(void*), void*) { /* Nonmatching */
    return FALSE;
}

/* 000044C0-000044E8       .text clrSpd__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::clrSpd() { /* Nonmatching */
}

/* 000044E8-00004B18       .text setStt__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::setStt(signed char i_stt) {
    /* Nonmatching */
    fopAc_ac_c* actor = searchByID(m7B4[0]);
    u8 oldStt = m8A3;
    m84E = 0;
    m8A3 = i_stt;
    s8 stt = m8A3;

    switch (stt) {
    case 1:
    case 2:
    case 0xC:
    case 0x16:
    case 0x1D:
        switch (stt) {
        case 1:
            m852 = (s16)(90.0f + cM_rndF(90.0f));
            break;
        case 2:
            m854 = (g_Counter.mCounter0 & 3) + 1;
            break;
        }
        if ((s8)oldStt != 3) {
            m8A5 = 3;
            m858 = m7D2;
            m_jnt.mbTrn = 1;
            m876 = 0;
        }
        m8A2 = 0;
        m898 = 0;
        clrSpd();
        break;
    case 3:
        m8A5 = 1;
        m_jnt.mbTrn = 1;
        m876 = 0;
        m8A2 = 0;
        m898 = 0;
        clrSpd();
        m89C = 0xFF;
        m89D = 0xFF;
        m8A4 = oldStt;
        break;
    case 4:
    case 0xB:
        switch (stt) {
        case 4:
            m852 = (s16)(180.0f + cM_rndF(180.0f));
            break;
        case 0xB:
            if (m744 != 0) {
                mPath.setInfDrct((dPath*)m744);
                mPath.setNearPathIndx(&current.pos, 0.0f);
                m744 = 0;
            }
            break;
        }
        m7F4 = mPath.getPoint(mPath.getIdx());
        m8A5 = 0;
        m876 = 1;
        m8A2 = 0;
        m898 = 1;
        m86B = 0;
        goto tail_04908;
    case 5:
        m8A5 = 0;
        m876 = 0;
        m8A2 = 0;
        m898 = 0;
        clrSpd();
        break;
    case 6:
    case 0xD:
    case 0x17:
        switch (stt) {
        case 6:
            if (mPath.getPath() != NULL) {
                m744 = (u32)mPath.getPath();
                mPath.setInfDrct(NULL);
            }
            break;
        }
        m7F4 = g_dComIfG_gameInfo.play.getPlayerPtr(0)->current.pos;
        m8A5 = 1;
        m876 = 1;
        m8A2 = 0;
        m898 = 2;
        m86B = 0;
        goto tail_049FC;
    case 7:
        if (mPath.getPath() != NULL) {
            m744 = (u32)mPath.getPath();
            mPath.setInfDrct(NULL);
        }
        m7F4 = g_dComIfG_gameInfo.play.getPlayerPtr(0)->current.pos;
        m8A5 = 1;
        m876 = 1;
        goto tail_04808;
    case 8:
        if (m744 != 0) {
            mPath.setInfDrct((dPath*)m744);
            mPath.setNearPathIndx(&current.pos, 0.0f);
            m744 = 0;
        }
        m7F4 = mPath.getPoint(mPath.getIdx());
        m8A5 = 0;
        m876 = 1;
    tail_04808:
        m8A2 = 0;
        m898 = 3;
        m86B = 0;
        m830 = -4.0f;
        speed.y = m830;
        speedF = 0.0f;
        m834 = 0.0f;
        m82C = 0.0f;
        gravity = 0.0f;
        m83C = *(f32*)&l_HIO.mChild[mCharNo].mPrm[0x40];
        break;
    case 9:
    case 0x10:
    case 0x12:
    case 0x19:
        m8A5 = 0;
        m876 = 0;
        m8A2 = 0;
        m899 = m898;
        m898 = 4;
        m86C = 1;
        speed.y = 10.0f;
        speedF = -3.0f;
        gravity = -1.6f;
        m834 = 0.1f;
        break;
    case 0xA:
    case 0xE:
    case 0x1A:
        m8A5 = 1;
        m876 = 0;
        m8A2 = 0;
        m898 = 0;
        clrSpd();
        break;
    case 0xF:
    case 0x18:
        m7F4 = m7C4;
        m8A5 = 0;
        m876 = 1;
        m8A2 = 0;
        m898 = 1;
        m86B = 0;
    tail_04908:
        gravity = -4.5f;
        {
            daNpc_Ko1_HIO_c* hio = &l_HIO;
            m82C = *(f32*)&hio->mChild[mCharNo].mPrm[0x24];
            m834 = *(f32*)&hio->mChild[mCharNo].mPrm[0x28];
            m83C = *(f32*)&hio->mChild[mCharNo].mPrm[0x2C];
        }
        break;
    case 0x11:
        JUT_ASSERT(0xa73, 0 != actor);
        m7F4 = actor->current.pos;
        m8A5 = 2;
        m7E8 = m7F4;
        m7E8.y = actor->eyePos.y;
        m876 = 1;
        m8A2 = 0;
        m898 = 2;
        m86B = 0;
    tail_049FC:
        gravity = -4.5f;
        m82C = *(f32*)&l_HIO.mChild[mCharNo].mPrm[0x34];
        m834 = *(f32*)&l_HIO.mChild[mCharNo].mPrm[0x38];
        m83C = *(f32*)&l_HIO.mChild[mCharNo].mPrm[0x3C];
        break;
    case 0x13:
        if (actor != NULL) {
            m8A5 = 2;
            m7E8 = actor->current.pos;
            m7E8.y = actor->eyePos.y;
        } else {
            m8A5 = 0;
        }
        m876 = 0;
        m8A2 = 0;
        m898 = 0;
        clrSpd();
        break;
    case 0x14:
        m89C = 0xFF;
        m89D = 0xFF;
        m8A4 = oldStt;
        break;
    case 0x1B:
    case 0x1C:
        m852 = (s16)(180.0f + cM_rndF(180.0f));
        m854 = cLib_getRndValue(3, 10);
        m865 = 0;
        break;
    }

    setAnm();
}

/* 00004B18-00004C70       .text wait_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_1() { /* Nonmatching */
    return FALSE;
}

/* 00004C70-00004CE8       .text wait_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_2() { /* Nonmatching */
    return FALSE;
}

/* 00004CE8-00004D1C       .text wait_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_3() { /* Nonmatching */
    return FALSE;
}

/* 00004D1C-00004E64       .text wait_4__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_4() { /* Nonmatching */
    return FALSE;
}

/* 00004E64-00004F30       .text wait_5__11daNpc_Ko1_cFSc */
BOOL daNpc_Ko1_c::wait_5(signed char) { /* Nonmatching */
    return FALSE;
}

/* 00004F30-00005088       .text wait_6__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_6() { /* Nonmatching */
    return FALSE;
}

/* 00005088-000052D4       .text wait_7__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_7() { /* Nonmatching */
    return FALSE;
}

/* 000052D4-000053F8       .text wait_9__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_9() { /* Nonmatching */
    return FALSE;
}

/* 000053F8-00005524       .text wait_a__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_a() { /* Nonmatching */
    return FALSE;
}

/* 00005524-000055F8       .text walk_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::walk_1() { /* Nonmatching */
    return FALSE;
}

/* 000055F8-000056D4       .text walk_2__11daNpc_Ko1_cFScSc */
BOOL daNpc_Ko1_c::walk_2(signed char, signed char) { /* Nonmatching */
    return FALSE;
}

/* 000056D4-000057B8       .text walk_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::walk_3() { /* Nonmatching */
    return FALSE;
}

/* 000057B8-000058EC       .text swim_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::swim_1() { /* Nonmatching */
    return FALSE;
}

/* 000058EC-000059D4       .text swim_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::swim_2() { /* Nonmatching */
    return FALSE;
}

/* 000059D4-00005AA4       .text attk_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::attk_1() { /* Nonmatching */
    return FALSE;
}

/* 00005AA4-00005B80       .text attk_2__11daNpc_Ko1_cFScSc */
BOOL daNpc_Ko1_c::attk_2(signed char, signed char) { /* Nonmatching */
    return FALSE;
}

/* 00005B80-00005C88       .text attk_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::attk_3() { /* Nonmatching */
    return FALSE;
}

/* 00005C88-00005CD0       .text down_1__11daNpc_Ko1_cFSc */
BOOL daNpc_Ko1_c::down_1(signed char) { /* Nonmatching */
    return FALSE;
}

/* 00005CD0-0000609C       .text talk_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::talk_1() { /* Nonmatching */
    return FALSE;
}

/* 0000609C-00006184       .text talk_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::talk_2() { /* Nonmatching */
    return FALSE;
}

/* 00006184-000062D0       .text manzai__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::manzai() { /* Nonmatching */
    return FALSE;
}

/* 000062D0-00006348       .text neru_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::neru_1() { /* Nonmatching */
    return FALSE;
}

/* 00006348-000064D0       .text neru_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::neru_2() { /* Nonmatching */
    return FALSE;
}

/* 000064D0-000065A0       .text hana_action1__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::hana_action1(void*) { /* Nonmatching */
    return FALSE;
}

/* 000065A0-00006654       .text hana_action2__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::hana_action2(void*) { /* Nonmatching */
    return FALSE;
}

/* 00006654-0000670C       .text hana_action3__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::hana_action3(void*) { /* Nonmatching */
    return FALSE;
}

/* 0000670C-000067B8       .text hana_action4__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::hana_action4(void*) { /* Nonmatching */
    return FALSE;
}

/* 000067B8-00006828       .text hana_action5__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::hana_action5(void*) { /* Nonmatching */
    return FALSE;
}

/* 00006828-000068E0       .text wait_action1__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::wait_action1(void*) { /* Nonmatching */
    return FALSE;
}

/* 000068E0-0000699C       .text wait_action2__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::wait_action2(void*) { /* Nonmatching */
    return FALSE;
}

/* 0000699C-00006A48       .text wait_action3__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::wait_action3(void*) { /* Nonmatching */
    return FALSE;
}

/* 00006A48-00006AF4       .text wait_action4__11daNpc_Ko1_cFPv */
BOOL daNpc_Ko1_c::wait_action4(void*) { /* Nonmatching */
    return FALSE;
}

/* 00006AF4-00006C00       .text demo__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::demo() { /* Nonmatching */
    return FALSE;
}

/* 00006C00-00006CC4       .text shadowDraw__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::shadowDraw() { /* Nonmatching */
}

/* 00006CC4-0000723C       .text _draw__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_draw() { /* Nonmatching */
    return FALSE;
}

/* 0000723C-0000756C       .text _execute__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_execute() { /* Nonmatching */
    return FALSE;
}

/* 0000756C-000075F0       .text _delete__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_delete() { /* Nonmatching */
    return FALSE;
}

/* 000075F0-00007610       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ko1_c*>(i_this)->CreateHeap();
}

/* 00007610-00007730       .text _create__11daNpc_Ko1_cFv */
cPhs_State daNpc_Ko1_c::_create() { /* Nonmatching */
    return cPhs_ERROR_e;
}

/* 00007730-00007848       .text __ct__11daNpc_Ko1_cFv */
/* compiler-generated default ctor */

/* 00007848-00007B2C       .text create_Anm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_Anm() { /* Nonmatching */
}

/* 00007B2C-00007D10       .text create_hed_Anm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_hed_Anm() { /* Nonmatching */
}

/* 00007D10-00007F10       .text create_bln_Anm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_bln_Anm() { /* Nonmatching */
}

/* 00007F10-00007FB8       .text create_itm_Mdl__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_itm_Mdl() { /* Nonmatching */
}

/* 00007FB8-00008318       .text CreateHeap__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::CreateHeap() { /* Nonmatching */
    return FALSE;
}

/* 00008318-00008340       .text daNpc_Ko1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ko1_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ko1_c*>(i_this)->_create();
}

/* 00008340-00008368       .text daNpc_Ko1_Delete__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_Delete(daNpc_Ko1_c* i_this) {
    return i_this->_delete();
}

/* 00008368-00008390       .text daNpc_Ko1_Execute__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_Execute(daNpc_Ko1_c* i_this) {
    return i_this->_execute();
}

/* 00008390-000083B8       .text daNpc_Ko1_Draw__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_Draw(daNpc_Ko1_c* i_this) {
    return i_this->_draw();
}

/* 000083B8-000083C0       .text daNpc_Ko1_IsDelete__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_IsDelete(daNpc_Ko1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ko1_Method = {
    (process_method_func)daNpc_Ko1_Create,
    (process_method_func)daNpc_Ko1_Delete,
    (process_method_func)daNpc_Ko1_Execute,
    (process_method_func)daNpc_Ko1_IsDelete,
    (process_method_func)daNpc_Ko1_Draw,
};

actor_process_profile_definition g_profile_NPC_KO1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KO1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ko1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KO1_e,
    /* Actor SubMtd */ &l_daNpc_Ko1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_KO2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KO2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ko1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KO2_e,
    /* Actor SubMtd */ &l_daNpc_Ko1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
