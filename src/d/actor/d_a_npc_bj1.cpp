/**
 * d_a_npc_bj1.cpp
 * NPC - Generic Koroks
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bj1.h"
#include "d/actor/d_a_jbo.h"
#include "d/d_npc.h"
#include "d/d_kankyo_wether.h"
#include "d/d_com_inf_game.h"
#include "res/Object/Bj.h"

static daNpc_Bj1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

static int a_bck_resID_tbl[] = {0xA, 0x2, 0x7, 0x8, 0x3, 0x6, 0x0, 0x1, 0xB, 0x9, 0x2A};

static daNpc_Bj1_c::anm_prm_c a_anm_prm_tbl[] = {
    {0, 0, 0, 8.0f, 1.0f, 2},
    {1, 0, 0, 8.0f, 1.0f, 0},
    {2, 0, 0, 8.0f, 1.0f, 2},
    {3, 0, 0, 8.0f, 1.0f, 2},
    {4, 0, 0, 8.0f, 1.0f, 2},
    {5, 0, 0, 8.0f, 1.0f, 0},
    {6, 0, 0, 8.0f, 1.0f, 0},
    {7, 0, 0, 8.0f, 1.0f, 0},
    {8, 0, 0, 8.0f, 1.0f, 2},
    {9, 0, 0, 8.0f, 1.0f, 0},
    {0xA, 0, 0, 8.0f, 1.0f, 2},
    {0, 0, 0, 0.0f, 0.0f, 0},
};

static const char* l_evn_tbl[3] = {
    "Mak_Drg", "Get_Blu_Btl", "Calling",
};

struct bj1_prm_tbl_t {
    /* 0x00 */ Vec mScaleHead;
    /* 0x0C */ Vec mScaleArm;
    /* 0x18 */ Vec mScaleBack;
};  // Size: 0x24

static const bj1_prm_tbl_t l_bj1_prm_tbl[9] = {
    { {1.0f, 1.0f, 1.0f}, {1.1f, 1.0f, 1.0f}, {40.0f, 10.0f, 0.0f} },
    { {0.9f, 1.0f, 1.0f}, {0.9f, 1.0f, 1.0f}, {30.0f, 10.0f, 0.0f} },
    { {1.1f, 1.0f, 1.0f}, {1.25f, 1.1f, 1.1f}, {40.0f, 10.0f, 0.0f} },
    { {0.8f, 1.0f, 1.0f}, {0.9f, 1.0f, 1.0f}, {30.0f, 10.0f, 0.0f} },
    { {0.8f, 1.0f, 1.0f}, {0.8f, 1.0f, 1.0f}, {30.0f, 10.0f, 0.0f} },
    { {1.0f, 1.0f, 1.0f}, {1.15f, 1.0f, 1.05f}, {40.0f, 10.0f, 0.0f} },
    { {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {40.0f, 10.0f, 0.0f} },
    { {1.0f, 1.0f, 1.0f}, {1.1f, 1.2f, 1.05f}, {40.0f, 10.0f, 0.0f} },
    { {1.1f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {40.0f, 10.0f, 0.0f} },
};

/* 000000EC-00000108       .text __ct__20daNpc_Bj1_childHIO_cFv */
daNpc_Bj1_childHIO_c::daNpc_Bj1_childHIO_c() {}

/* 00000150-0000020C       .text __ct__15daNpc_Bj1_HIO_cFv */
daNpc_Bj1_HIO_c::daNpc_Bj1_HIO_c() {
    /* Nonmatching */
    static u32 a_prm_tbl[] = {
        0x13881388, 0xE000EC78, 0x00001C70, 0x0000E390, 0x04000400, 0x43020000,
        0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x13881388, 0xFD44EC78, 0x00001C70, 0x0000E390, 0x04000400,
        0x42C80000, 0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x13881388, 0xE000EC78, 0x00001C70, 0x0000E390,
        0x04000400, 0x43160000, 0x00000000, 0x43960000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x13881B58, 0xFF38F830, 0x00000000,
        0x00000000, 0x04000400, 0x42C80000, 0x00000000, 0x43960000, 0x005A0006,
        0x04000000, 0x40800000, 0x40A00000, 0x3E4CCCCD, 0x40800000, 0x3E4CCCCD,
        0x3F800000, 0x232800C8, 0x10001388, 0x437A0000, 0x7FFF0000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x13880BB8, 0x0064F448,
        0x00001388, 0x0000EC78, 0x04000400, 0x42DC0000, 0x00000000, 0x43960000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x13881388,
        0xFF9CEC78, 0x000007D0, 0x0000F830, 0x04000400, 0x43020000, 0x00000000,
        0x43960000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x13881388, 0xE000EC78, 0x00001C70, 0x0000E390, 0x04000400, 0x42FA0000,
        0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000006, 0x04000000, 0x3ECCCCCD, 0x40A00000, 0x3E4CCCCD,
        0x42200000, 0x13880FA0, 0xF830F060, 0x00001C70, 0x0000E390, 0x04000400,
        0x42F00000, 0x00000000, 0x43960000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x13881388, 0xF254EC78, 0x00001C70, 0x0000E390,
        0x04000400, 0x43020000, 0x00000000, 0x43960000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000,
    };
    for (int i = 0; i < 9; i++) {
        mChild[i].mNo = i;
        memcpy(&mChild[i].mPrm, &a_prm_tbl[i * 25], 0x64);
    }
    mNo = -1;
    field_0x8 = -1;
}

/* 00000268-000002EC       .text searchActor_Jb__FPvPv */
static void* searchActor_Jb(void* i_actor, void*) {
    if (l_check_wrk < 20 && fopAc_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_JBO_e &&
        ((jbo_class*)i_actor)->mType != 0) {
        l_check_inf[l_check_wrk] = static_cast<fopAc_ac_c*>(i_actor);
        l_check_wrk++;
    }
    return NULL;
}

/* 000002EC-00000338       .text nodeCallBack_Bj1__FP7J3DNodei */
static BOOL nodeCallBack_Bj1(J3DNode* i_node, int i_param) {
    if (i_param == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Bj1_c*>(j3dSys.getModel()->getUserArea())->nodeBj1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000338-000004C4       .text nodeBj1Control__11daNpc_Bj1_cFP7J3DNodeP8J3DModel */
void daNpc_Bj1_c::nodeBj1Control(J3DNode* i_node, J3DModel* i_model) {
    /* Nonmatching */
}

/* 00000500-0000054C       .text nodeCallBack_Prp__FP7J3DNodei */
static BOOL nodeCallBack_Prp(J3DNode* i_node, int i_param) {
    if (i_param == 0) {
        if (j3dSys.getModel()->getUserArea() != NULL) {
            reinterpret_cast<daNpc_Bj1_c*>(j3dSys.getModel()->getUserArea())->nodePrpControl(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000054C-00000664       .text nodePrpControl__11daNpc_Bj1_cFP7J3DNodeP8J3DModel */
void daNpc_Bj1_c::nodePrpControl(J3DNode* i_node, J3DModel* i_model) {
    /* Nonmatching */
}

/* 00000664-00000710       .text init_BJ4_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJ4_0() {
    bool ret = dComIfGs_isSymbol(2) == 0;
    if (ret) {
        ret = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != 0;
        if (ret) {
            set_action(&daNpc_Bj1_c::wait_action2, NULL);
        }
    }
    return ret;
}

/* 00000710-000007D4       .text init_BJ6_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJ6_0() {
    bool ret = dComIfGs_isSymbol(2) == 0;
    if (ret) {
        ret = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != 0;
        if (ret) {
            actor_status &= ~fopAcStts_NOCULLEXEC_e;
            actor_status |= fopAcStts_UNK4000_e;
            set_action(&daNpc_Bj1_c::wait_action4, NULL);
        }
    }
    return ret;
}

/* 000007D4-00000864       .text init_BJ7_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJ7_0() {
    bool ret = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != 0;
    if (ret) {
        setPrtcl_drugPot_1();
        set_action(&daNpc_Bj1_c::wait_action3, NULL);
    }
    return ret;
}

/* 00000864-00000910       .text init_BJX_0__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJX_0() {
    bool ret = dComIfGs_isSymbol(2) == 0;
    if (ret) {
        ret = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1801) != 0;
        if (ret) {
            set_action(&daNpc_Bj1_c::wait_action1, NULL);
        }
    }
    return ret;
}

/* 00000910-00000998       .text init_BJX_1__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::init_BJX_1() {
    bool ret = dComIfGs_isSymbol(2) != 0;
    if (ret) {
        set_action(&daNpc_Bj1_c::wait_action1, NULL);
    }
    return ret;
}

/* 00000998-00000C90       .text createInit__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::createInit() {
    int i = 0;
    for (; i < 3; i++) {
        mEventIdTable[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }

    attention_info.flags = 10;
    switch (mType) {
    case 4:
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA7;
        attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
        break;
    case 0:
    case 1:
    case 7:
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
        attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;
        break;
    case 2:
    case 3:
    case 5:
    case 8:
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAA;
        attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAA;
        break;
    case 6:
        attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x5A;
        attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x5A;
        break;
    default:
        return FALSE;
    }

    mScaleHead = l_bj1_prm_tbl[mType].mScaleHead;
    mScaleArm = l_bj1_prm_tbl[mType].mScaleArm;
    mScaleBack = l_bj1_prm_tbl[mType].mScaleBack;

    gravity = -4.5f;
    mHomePos = current.pos;

    u8 pathNo = (fopAcM_GetParam(this) >> 16) & 0xFF;
    mPathNo = pathNo;
    if (pathNo != 0xFF) {
        mPathRun.setInf(pathNo, current.roomNo, 1);
        if (mPathRun.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        } else {
            return FALSE;
        }
    }

    static char* a_staff_tbl[0x11] = {"Bj1", "Bj1", "Bj2", "Bj2", "Bj3", "Bj3", "Bj4", "Bj4", "Bj5", "Bj5", "Bj6", "Bj6", "Bj7", "Bj8", "Bj8", "Bj9", "Bj9"};
    mEventCut.setActorInfo2(a_staff_tbl[mSpecificType], this);
    m8AF = 0xB;

    bool result;
    switch (mSpecificType) {
    case 6:
        result = init_BJ4_0();
        break;
    case 10:
        result = init_BJ6_0();
        break;
    case 0:
    case 2:
    case 4:
    case 8:
    case 13:
    case 15:
        result = init_BJX_0();
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
    case 11:
    case 14:
    case 16:
        result = init_BJX_1();
        break;
    case 12:
        result = init_BJ7_0();
        break;
    default:
        result = 0;
        break;
    }
    if (result) {
        shape_angle.x = current.angle.x;
        shape_angle.y = current.angle.y;
        shape_angle.z = current.angle.z;
        goto success;
    }
    return FALSE;
success:
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(TRUE);
    return TRUE;
}

/* 00000C90-00000E00       .text setMtx_anmProc__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setMtx_anmProc() {
    /* Nonmatching */
}

/* 00000E00-00001098       .text setMtx__11daNpc_Bj1_cFb */
void daNpc_Bj1_c::setMtx(bool) {
    /* Nonmatching */
}

/* 00001098-000010AC       .text anmNum_toResID__11daNpc_Bj1_cFi */
int daNpc_Bj1_c::anmNum_toResID(int i_anmNum) {
    return a_bck_resID_tbl[i_anmNum];
}

/* 000010AC-00001188       .text setAnm_anm__11daNpc_Bj1_cFPQ211daNpc_Bj1_c9anm_prm_c */
BOOL daNpc_Bj1_c::setAnm_anm(daNpc_Bj1_c::anm_prm_c* i_anmPrmP) {
    if (m8AF == i_anmPrmP->mAnmNum) {
        return TRUE;
    }
    m8AF = i_anmPrmP->mAnmNum;
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed,
                     anmNum_toResID(m8AF), -1, "Bj");
    if (m8AF == 7) {
        setPrtcl_danceLR();
        m888 = 0;
        m894 = 0x1E;
    } else {
        delPrtcl_danceLR();
    }
    mPrevMorfFrame = 0.0f;
    m83D = 0;
    m83C = 0;
    return TRUE;
}

/* 00001188-000011B8       .text setAnm_NUM__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::setAnm_NUM(int i_anmNum) {
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 000011B8-000011F4       .text setAnm__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::setAnm() {
    setAnm_anm(&a_anm_prm_tbl[mPrevStatus]);
    return true;
}

/* 000011F4-00001378       .text setAnm_prp__11daNpc_Bj1_cFSc */
BOOL daNpc_Bj1_c::setAnm_prp(signed char) {
    /* Nonmatching */
}

/* 00001378-0000137C       .text chg_anmTag__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::chg_anmTag() {
    /* Nonmatching */
}

/* 0000137C-00001380       .text control_anmTag__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::control_anmTag() {
    /* Nonmatching */
}

/* 00001380-000013C0       .text chg_anmAtr__11daNpc_Bj1_cFUc */
void daNpc_Bj1_c::chg_anmAtr(unsigned char i_attr) {
    if (i_attr >= 0xB || i_attr == m8AD) {
        return;
    }
    m8AD = i_attr;
    setAnm_ATR();
}

/* 000013C0-0000143C       .text control_anmAtr__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::control_anmAtr() {
    switch (m8AD) {
    case 10:
        if (m83C != 0) {
            m8AD = 2;
            setAnm_NUM(3);
        }
        break;
    case 6:
    case 7:
        if (m83C != 0) {
            m8AD = 0;
            setAnm_NUM(0);
        }
        break;
    }
}

/* 0000143C-00001470       .text setAnm_ATR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setAnm_ATR() {
    setAnm_anm(&a_anm_prm_tbl[m8AD]);
}

/* 00001470-00001534       .text anmAtr__11daNpc_Bj1_cFUs */
void daNpc_Bj1_c::anmAtr(unsigned short i_attr) {
    switch (i_attr) {
    case 0x6:
        if (m8B7 == 0) {
            m8AD = 0xFF;
            chg_anmAtr(g_dComIfG_gameInfo.play.mMesgAnime);
            m8B7++;
        }
        {
            u8 tagInfo = g_dComIfG_gameInfo.play.mMesgAnimeTagInfo;
            g_dComIfG_gameInfo.play.mMesgAnimeTagInfo = 0xFF;
            if (tagInfo != 0xFF && m8AE != tagInfo) {
                m8AE = tagInfo;
                chg_anmTag();
            }
        }
        break;
    case 0xE:
        m8B7 = 0;
        break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00001534-000015D8       .text eventOrder__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eventOrder() {
    /* Nonmatching */
}

/* 000015D8-00001690       .text checkOrder__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::checkOrder() {
    /* Nonmatching */
}

/* 00001690-0000172C       .text chk_talk__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::chk_talk() {
    bool ret = true;
    m83E = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            m83E = dComIfGp_event_getPreItemNo();
        } else {
            ret = false;
        }
    }
    return ret;
}

/* 0000172C-000017C0       .text chk_drct__11daNpc_Bj1_cFf */
bool daNpc_Bj1_c::chk_drct(f32 i_param_1) {
    s16 target = cLib_targetAngleY(
        &current.pos,
        &dComIfGp_getPlayer(0)->current.pos
    ) - current.angle.y;
    int cmp = abs(target);
    return cmp < cM_deg2s(i_param_1);
}

/* 000017C0-000017F0       .text chk_partsNotMove__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::chk_partsNotMove() {
    bool ret = false;
    if (m822 != m_jnt.getBackbone_y() || m820 != m_jnt.getHead_y()) {
        ret = true;
    }
    return ret;
}

/* 000017F0-000019A0       .text lookBack__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    m820 = m_jnt.getHead_y();
    m822 = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool flag = m856;

    switch (m8B3) {
    case 1:
        dstPos = dNpc_playerEyePos(-20.0f);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
    case 2:
        dstPos.set(mHomePos);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
    case 3:
        desiredYrot = m83A;
        break;
    }
    cLib_addCalcAngleS2(&m838, l_HIO.mChild[mType].mPrm.field_0x12, 4, 0x800);
    if (!m_jnt.trnChk()) {
        m838 = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, m838, flag);
}

/* 000019A0-00001A44       .text getMaskInf__11daNpc_Bj1_cFPUc */
bool daNpc_Bj1_c::getMaskInf(unsigned char* i_mask) {
    bool ret = i_mask != NULL;
    if (ret) {
        switch (mSpecificType) {
        case 0:
            *i_mask = 0x1;
            break;
        case 1:
            *i_mask = 0x2;
            break;
        case 2:
            *i_mask = 0x4;
            break;
        case 3:
            *i_mask = 0x8;
            break;
        case 4:
            *i_mask = 0x10;
            break;
        case 5:
            *i_mask = 0x20;
            break;
        case 6:
            *i_mask = 0x40;
            break;
        case 7:
            *i_mask = 0x80;
            break;
        default:
            ret = false;
            break;
        }
    }
    return ret;
}

/* 00001A44-00001AA8       .text chkReg__11daNpc_Bj1_cFUs */
bool daNpc_Bj1_c::chkReg(unsigned short i_reg) {
    u8 mask;
    if (getMaskInf(&mask)) {
        u8 reg = dComIfGs_getEventReg(i_reg);
        return (reg & mask) != 0;
    }
    return false;
}

/* 00001AA8-00001B14       .text setReg__11daNpc_Bj1_cFUs */
void daNpc_Bj1_c::setReg(unsigned short i_reg) {
    u8 mask;
    if (getMaskInf(&mask)) {
        dComIfGs_setEventReg(i_reg, (u8)(dComIfGs_getEventReg(i_reg) | mask));
    }
}

/* 00001B14-00001E84       .text next_msgStatus__11daNpc_Bj1_cFPUl */
u16 daNpc_Bj1_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001E84-00001F14       .text getMsg_BJ1_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ1_0() {
    if (dComIfGs_isEventBit(0x604) == 0) {
        return 0x140E;
    }
    if (dKyw_get_windsdir() == 1) {
        if (dComIfGs_isEventBit(0xC80)) {
            return 0x1414;
        }
        return 0x1412;
    }
    return dComIfGs_isEventBit(0x904) ? 0x1411 : 0x1410;
}

/* 00001F14-00001F54       .text getMsg_BJ2_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ2_0() {
    if (dComIfGs_isEventBit(0x920)) {
        return 0x13F4;
    }
    return 0x13F2;
}

/* 00001F54-00001FA8       .text getMsg_BJ3_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ3_0() {
    if (m84B != 0) {
        return 0x13FB;
    }
    if (dComIfGs_isEventBit(0xC20)) {
        return 0x13FA;
    }
    return 0x13F8;
}

/* 00001FA8-00001FE8       .text getMsg_BJ4_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ4_0() {
    if (dComIfGs_isEventBit(0xC08)) {
        return 0x13FF;
    }
    return 0x13FD;
}

/* 00001FE8-00002028       .text getMsg_BJ5_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ5_0() {
    if (dComIfGs_isEventBit(0xC04)) {
        return 0x13F7;
    }
    return 0x13F5;
}

/* 00002028-00002068       .text getMsg_BJ6_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ6_0() {
    if (dComIfGs_isEventBit(0xC02)) {
        return 0x1405;
    }
    return 0x1402;
}

/* 00002068-000021C4       .text getMsg_BJ7_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ7_0() {
    if (m842 != 0) {
        m842 = 0;
        return 0x142B;
    }
    if (m843 != 0) {
        m843 = 0;
        return 0x142C;
    }
    if (m83E == 0x46) {
        if (dComIfGs_isEventBit(0x1B80)) {
            return 0x1424;
        }
        return 0x1422;
    }
    if (m83E != 0xFF) {
        return 0x1421;
    }
    if (dComIfGs_isSymbol(2)) {
        if (dComIfGs_isEventBit(0xD08) == 0) {
            return 0x1433;
        }
        if (dComIfGs_isEventBit(0x1C80)) {
            return dComIfGs_isEventBit(0x1B80) ? 0x141E : 0x141F;
        }
        return 0x1431;
    }
    if (dComIfGs_isEventBit(0xD08)) {
        return dComIfGs_isEventBit(0x1B80) ? 0x141E : 0x141F;
    }
    return 0x1416;
}

/* 000021C4-00002254       .text getMsg_BJ8_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ8_0() {
    if (dComIfGs_isEventBit(0xD40) == 0) {
        return 0x1406;
    }
    if (dKyw_get_windsdir() == 7) {
        if (dComIfGs_isEventBit(0xD10)) {
            return 0x140D;
        }
        return 0x140B;
    }
    return dComIfGs_isEventBit(0xD20) ? 0x140A : 0x1409;
}

/* 00002254-00002294       .text getMsg_BJ9_0__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_BJ9_0() {
    if (dComIfGs_isEventBit(0xC10)) {
        return 0x13F0;
    }
    return 0x13ED;
}
/* 00002294-0000242C       .text getMsg_Corog__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg_Corog() {
    if (chkReg(0x9AFF)) {
        if (dComIfGs_isEventBit(0x102)) {
            return chkReg(0x99FF) ? 0x1486 : 0x1485;
        }
        if (chkReg(0x9EFF) == 0) {
            if (chkReg(0x98FF)) {
                return 0x149E;
            }
            return 0x1487;
        }
        if (chkReg(0x96FF)) {
            return 0x1484;
        }
        u8 reg = dComIfGs_getEventReg(0x9EFF);
        s16 count = 0;
        for (int i = 0; i < 8; i++) {
            if (reg & 1) {
                count++;
            }
            reg >>= 1;
        }
        g_dComIfG_gameInfo.play.mMsgCountNumber = 8 - count;
        return 0x1482;
    }
    if (dComIfGs_isEventBit(0x2E10)) {
        if (chkReg(0x97FF)) {
            return 0x1494;
        }
        return 0x1497;
    }
    if (chkReg(0x97FF)) {
        return 0x1494;
    }
    return 0x148A;
}

/* 0000242C-000024EC       .text getMsg__11daNpc_Bj1_cFv */
u32 daNpc_Bj1_c::getMsg() {
    u32 msg = 0;
    switch (mSpecificType) {
    case 0:
        msg = getMsg_BJ1_0();
        break;
    case 2:
        msg = getMsg_BJ2_0();
        break;
    case 4:
        msg = getMsg_BJ3_0();
        break;
    case 6:
        msg = getMsg_BJ4_0();
        break;
    case 8:
        msg = getMsg_BJ5_0();
        break;
    case 10:
        msg = getMsg_BJ6_0();
        break;
    case 12:
        msg = getMsg_BJ7_0();
        break;
    case 13:
        msg = getMsg_BJ8_0();
        break;
    case 15:
        msg = getMsg_BJ9_0();
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
    case 11:
    case 14:
    case 16:
        msg = getMsg_Corog();
        break;
    default:
        break;
    }
    return msg;
}



/* 000024EC-0000256C       .text chkAttention__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::chkAttention() {
    dAttention_c* attention = &g_dComIfG_gameInfo.play.mAttention;
    if (attention->LockonTruth()) {
        return this == attention->LockonTarget(0);
    }
    return this == attention->ActionTarget(0);
}

/* 0000256C-000025D4       .text setAttention__11daNpc_Bj1_cFb */
void daNpc_Bj1_c::setAttention(bool i_flag) {
    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mChild[mType].mPrm.field_0x14, current.pos.z);
    if (m850 == 0 && i_flag == false) {
        return;
    }
    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 000025D4-00002608       .text searchByID__11daNpc_Bj1_cFUi */
fopAc_ac_c* daNpc_Bj1_c::searchByID(fpc_ProcID i_id) {
    fopAc_ac_c* actor = NULL;
    fopAcM_SearchByID(i_id, &actor);
    return actor;
}

/* 00002608-000026B8       .text partner_srch_sub__11daNpc_Bj1_cFPFPvPv_Pv */
bool daNpc_Bj1_c::partner_srch_sub(fpcLyIt_JudgeFunc i_judgeFunc) {
    bool ret = false;
    mPartnerProcID = -1;
    l_check_wrk = 0;
    for (int i = 0; i < 20; i++) {
        l_check_inf[i] = NULL;
    }
    fpcEx_Search(i_judgeFunc, this);
    if (l_check_wrk != 0) {
        fopAc_ac_c* actor = l_check_inf[0];
        if (actor != NULL) {
            mPartnerProcID = fopAcM_GetID(actor);
        }
        ret = true;
    }
    return ret;
}

/* 000026B8-00002724       .text partner_srch__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::partner_srch() {
    fpcLyIt_JudgeFunc judge = NULL;
    if (mActionIndex == 1) {
        if (mSpecificType == 4) {
            if (partner_srch_sub(searchActor_Jb)) {
                mActionIndex++;
            }
        }
    }
}

/* 00002724-000027B0       .text setCollision_SP___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setCollision_SP_() {
    /* Nonmatching */
}

/* 000027B0-00002840       .text set_pthPoint__11daNpc_Bj1_cFUc */
void daNpc_Bj1_c::set_pthPoint(unsigned char) {
    /* Nonmatching */
}

/* 00002840-00002988       .text bj_clcFlySpd__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_clcFlySpd() {
    /* Nonmatching */
}

/* 00002988-00002B80       .text bj_movPass__11daNpc_Bj1_cFb */
void daNpc_Bj1_c::bj_movPass(bool) {
    /* Nonmatching */
}

/* 00002B80-00002EDC       .text bj_flyMove__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_flyMove() {
    /* Nonmatching */
}

/* 00002EDC-00002F5C       .text bj_clcMovSpd__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_clcMovSpd() {
    /* Nonmatching */
}

/* 00002F5C-000030A4       .text bj_nMove__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::bj_nMove() {
    /* Nonmatching */
}

/* 000030A4-000031F4       .text setPrtcl_drugPot_1__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_drugPot_1() {
    /* Nonmatching */
}

/* 000031F4-000032B4       .text setPrtcl_drugPot_2__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_drugPot_2() {
    /* Nonmatching */
}

/* 000032B4-00003330       .text delPrtcl_drugPot__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::delPrtcl_drugPot() {
    /* Nonmatching */
}

/* 00003330-000033F4       .text setPrtcl_danceLR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_danceLR() {
    /* Nonmatching */
}

/* 000033F4-00003484       .text flwPrtcl_danceLR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::flwPrtcl_danceLR() {
    /* Nonmatching */
}

/* 00003484-000034D8       .text delPrtcl_danceLR__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::delPrtcl_danceLR() {
    /* Nonmatching */
}

/* 000034D8-00003594       .text setPrtcl_peraProOpen__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::setPrtcl_peraProOpen() {
    /* Nonmatching */
}

/* 00003594-00003774       .text createSeed__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::createSeed() {
    /* Nonmatching */
}

/* 00003774-000037E4       .text deleteSeed__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::deleteSeed() {
    /* Nonmatching */
}

/* 000037E4-00003998       .text charDecide__11daNpc_Bj1_cFi */
bool daNpc_Bj1_c::charDecide(int) {
    /* Nonmatching */
}

/* 00003998-000039DC       .text eInit_setLocFlag__11daNpc_Bj1_cFPi */
void daNpc_Bj1_c::eInit_setLocFlag(int* i_flag) {
    m856 = 0;
    if (i_flag == NULL) {
        return;
    }
    switch (*i_flag) {
    case 2:
        m_jnt.setTrn();
        break;
    case 1:
        m856 = 1;
        break;
    }
}

/* 000039DC-00003A14       .text eInit_setShapeAngleY__11daNpc_Bj1_cFPis */
void daNpc_Bj1_c::eInit_setShapeAngleY(int* i_flag, s16 i_angle) {
    m846 = 0;
    if (i_flag == NULL) {
        return;
    }
    m846 = *i_flag == 1;
    if (m846) {
        shape_angle.y = i_angle;
    }
}

/* 00003A14-00003A30       .text eInit_setEvTimer__11daNpc_Bj1_cFPi */
void daNpc_Bj1_c::eInit_setEvTimer(int* i_evTimer) {
    m830 = 0;
    if (i_evTimer != NULL) {
        m830 = *i_evTimer;
    }
}

/* 00003A30-00003B10       .text eInit_calcRelativPos__11daNpc_Bj1_cFP4cXyzPi */
void daNpc_Bj1_c::eInit_calcRelativPos(cXyz*, int*) {
    /* Nonmatching */
}

/* 00003B10-00003B20       .text eInit_prmFloat__11daNpc_Bj1_cFPff */
f32 daNpc_Bj1_c::eInit_prmFloat(float* i_prm, float i_default) {
    if (i_prm != NULL) {
        return *i_prm;
    }
    return i_default;
}

/* 00003B20-00003D3C       .text eInit_ATTENTION___11daNpc_Bj1_cFPiPiPiP4cXyzPiPiPi */
void daNpc_Bj1_c::eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*) {
    /* Nonmatching */
}

/* 00003D3C-00003E24       .text eInit_PLYER_MOV_1___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_PLYER_MOV_1_() {
    /* Nonmatching */
}

/* 00003E24-00003F04       .text eInit_MOV___11daNpc_Bj1_cFPfPfPfPi */
void daNpc_Bj1_c::eInit_MOV_(float*, float*, float*, int*) {
    /* Nonmatching */
}

/* 00003F04-00003F74       .text eInit_JMP___11daNpc_Bj1_cFPfPf */
void daNpc_Bj1_c::eInit_JMP_(float*, float*) {
    /* Nonmatching */
}

/* 00003F74-0000406C       .text eInit_CHG_PTH___11daNpc_Bj1_cFPiPi */
void daNpc_Bj1_c::eInit_CHG_PTH_(int*, int*) {
    /* Nonmatching */
}

/* 0000406C-000040BC       .text eInit_END_MOV___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_END_MOV_() {
    /* Nonmatching */
}

/* 000040BC-000040F4       .text eInit_SET_TNE___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_SET_TNE_() {
    setAnm_NUM(9);
    m8B3 = 0;
}

/* 000040F4-00004114       .text eInit_DEL_TNE___11daNpc_Bj1_cFv */
void daNpc_Bj1_c::eInit_DEL_TNE_() {
    deleteSeed();
}

/* 00004114-0000417C       .text eInit_SET_ANM___11daNpc_Bj1_cFPiPf */
void daNpc_Bj1_c::eInit_SET_ANM_(int*, float*) {
    /* Nonmatching */
}

/* 0000417C-000044E4       .text event_actionInit__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::event_actionInit(int) {
    /* Nonmatching */
}

/* 000044E4-00004530       .text eMove_ATTENTION___11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::eMove_ATTENTION_() {
    if (m830 >= 0) {
        return cLib_calcTimer(&m830) == 0;
    }
    return !m_jnt.trnChk();
}

/* 00004530-00004580       .text eMove_MOV___11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::eMove_MOV_() {
    if (m830 >= 0) {
        return cLib_calcTimer(&m830) == 0;
    }
    return (u8)m84A == 1;
}

/* 00004580-00004594       .text eMove_JMP___11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::eMove_JMP_() {
    return m8A9 == 0 ? 1 : 0;
}

/* 00004594-000045F0       .text eMove_SET_TNE___11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::eMove_SET_TNE_() {
    if (mpMorf->checkFrame(1.0f)) {
        createSeed();
    }
    return m83C != 0;
}

/* 000045F0-00004678       .text eMove_PTH_MOV___11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::eMove_PTH_MOV_() {
    bool ret = m8AA == 0;
    if (!ret) {
        if ((u8)m84A != 0) {
            mPathPoint = mPathRun.getPoint(mPathRun.getIdx());

        }
        m84A = 0;
    }
    return ret;
}

/* 00004678-000046E8       .text event_action__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::event_action() {
    /* Nonmatching */
}

/* 000046E8-000047D4       .text privateCut__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::privateCut(int) {
    /* Nonmatching */
}

/* 000047D4-000047F4       .text endEvent__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::endEvent() {
    g_dComIfG_gameInfo.play.mEvtCtrl.mEventFlag |= 8;
    m8AD = 0xFF;
}

/* 000047F4-0000482C       .text isEventEntry__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL, 0);
}

/* 0000482C-00004914       .text event_proc__11daNpc_Bj1_cFi */
void daNpc_Bj1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00004914-000049C0       .text set_action__11daNpc_Bj1_cFM11daNpc_Bj1_cFPCvPvPv_iPv */
BOOL daNpc_Bj1_c::set_action(daNpc_Bj1_c::ProcFunc, void*) {
    /* Nonmatching */
}

/* 000049C0-00004B60       .text setStt__11daNpc_Bj1_cFSc */
void daNpc_Bj1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 00004B60-00004C30       .text wait_1__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::wait_1() {
    /* Nonmatching */
}

/* 00004C30-00004D10       .text wait_2__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::wait_2() {
    /* Nonmatching */
}

/* 00004D10-00004E2C       .text wait_3__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::wait_3() {
    /* Nonmatching */
}

/* 00004E2C-00004F48       .text wait_4__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::wait_4() {
    /* Nonmatching */
}

/* 00004F48-000050CC       .text flyMov__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::flyMov() {
    /* Nonmatching */
}

/* 000050CC-0000514C       .text fall01__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::fall01() {
    /* Nonmatching */
}

/* 0000514C-00005510       .text talk_1__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::talk_1() {
    /* Nonmatching */
}

/* 00005510-000055D8       .text walk_1__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::walk_1() {
    /* Nonmatching */
}

/* 000055D8-00005694       .text wait_action1__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00005694-0000577C       .text wait_action2__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action2(void*) {
    /* Nonmatching */
}

/* 0000577C-00005860       .text wait_action3__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action3(void*) {
    /* Nonmatching */
}

/* 00005860-00005928       .text wait_action4__11daNpc_Bj1_cFPv */
BOOL daNpc_Bj1_c::wait_action4(void*) {
    /* Nonmatching */
}

/* 00005928-000059C4       .text demo__11daNpc_Bj1_cFv */
bool daNpc_Bj1_c::demo() {
    /* Nonmatching */
}

/* 000059C4-00005AC4       .text shadowDraw__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::shadowDraw() {
    /* Nonmatching */
}

/* 00005AC4-00005E38       .text _draw__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::_draw() {
    /* Nonmatching */
}

/* 00005E38-00006128       .text _execute__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::_execute() {
    /* Nonmatching */
}

/* 00006128-000061A4       .text _delete__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Bj");
    if (heap != NULL) {
        if (mpMorf != NULL) {
            mpMorf->stopZelAnime();
        }
        if (mpPrpMorf != NULL) {
            mpPrpMorf->stopZelAnime();
        }
    }
    delPrtcl_drugPot();
    delPrtcl_danceLR();
    return TRUE;
}

/* 000061A4-000061C4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->CreateHeap();
}

/* 000061C4-000062E4       .text _create__11daNpc_Bj1_cFv */
cPhs_State daNpc_Bj1_c::_create() {
    /* Nonmatching */
}

/* 00006734-00006A00       .text create_Anm__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::create_Anm() {
    /* Nonmatching */
}

/* 00006A00-00006C14       .text create_prp_Anm__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::create_prp_Anm() {
    /* Nonmatching */
}

/* 00006C14-00006F54       .text create_itm_Mdl__11daNpc_Bj1_cFv */
void daNpc_Bj1_c::create_itm_Mdl() {
    /* Nonmatching */
}

/* 00006F54-00007114       .text CreateHeap__11daNpc_Bj1_cFv */
BOOL daNpc_Bj1_c::CreateHeap() {
    /* Nonmatching */
}

/* 00007114-00007134       .text daNpc_Bj1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Bj1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_create();
}

/* 00007134-00007154       .text daNpc_Bj1_Delete__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_Delete(daNpc_Bj1_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_delete();
}

/* 00007154-00007174       .text daNpc_Bj1_Execute__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_Execute(daNpc_Bj1_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_execute();
}

/* 00007174-00007194       .text daNpc_Bj1_Draw__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_Draw(daNpc_Bj1_c* i_this) {
    return ((daNpc_Bj1_c*)i_this)->_draw();
}

/* 00007194-0000719C       .text daNpc_Bj1_IsDelete__FP11daNpc_Bj1_c */
static BOOL daNpc_Bj1_IsDelete(daNpc_Bj1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Bj1_Method = {
    (process_method_func)daNpc_Bj1_Create,
    (process_method_func)daNpc_Bj1_Delete,
    (process_method_func)daNpc_Bj1_Execute,
    (process_method_func)daNpc_Bj1_IsDelete,
    (process_method_func)daNpc_Bj1_Draw,
};

actor_process_profile_definition g_profile_NPC_BJ1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ1_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ2_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ3 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ3_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ3_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ4 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ4_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ4_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ5 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ5_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ5_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ6 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ6_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ6_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ7 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ7_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ7_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ8 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ8_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ8_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BJ9 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BJ9_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bj1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BJ9_e,
    /* Actor SubMtd */ &l_daNpc_Bj1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
