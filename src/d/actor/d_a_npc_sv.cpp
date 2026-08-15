/**
 * d_a_npc_sv.cpp
 * NPC - Salvage Corp group members
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_sv.h"
#include "d/actor/d_a_obj_ikada.h"
#include "d/d_com_lib_game.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "res/Object/Sv.h"

enum NpcNo_e {
    /* 0x00 */ NPC_SV1,
    /* 0x01 */ NPC_SV2,
    /* 0x02 */ NPC_SV3,
    /* 0x03 */ NPC_SV4,
};

static char* l_npc_staff_id[] = {
    "Sv0",
    "Sv1",
    "Sv2",
    "Sv3",
};

static const char* l_arcname_tbl[] = {
    "Sv",
    "Sv",
    "Sv",
    "Sv",
};

const char daNpcSv_c::m_arcname[] = "Sv";

static const int l_bmd_ix_tbl[] = {
    dRes_ID_SV_BDL_SV_e,
    dRes_ID_SV_BDL_SV_e,
    dRes_ID_SV_BDL_SV_e,
    dRes_ID_SV_BDL_SV_e,
};

static const int l_bck_ix_tbl[][6] = {
    {
        dRes_ID_SV_BCK_SV_WAIT01_e,
        dRes_ID_SV_BCK_SV_TALK01_e,
        dRes_ID_SV_BCK_SV_TALK02_e,
        dRes_ID_SV_BCK_SV_TALK03_e,
        dRes_ID_SV_BCK_SV_YA_e,
        dRes_ID_SV_BCK_SV_MAWASI_e,
    },
    {
        dRes_ID_SV_BCK_SV_WAIT02_e,
        dRes_ID_SV_BCK_SV_KYORO_e,
        dRes_ID_SV_BCK_SV_UNAZUKU_e,
        dRes_ID_SV_BCK_SV_HARAU_e,
        dRes_ID_SV_BCK_SV_BYE_e,
        dRes_ID_SV_BCK_SV_SHI_e,
    },
    {
        dRes_ID_SV_BCK_SV_WAIT02_e,
        dRes_ID_SV_BCK_SV_KYORO_e,
        dRes_ID_SV_BCK_SV_UNAZUKU_e,
        dRes_ID_SV_BCK_SV_HARAU_e,
        dRes_ID_SV_BCK_SV_BYE_e,
        dRes_ID_SV_BCK_SV_SHI_e,
    },
    {
        dRes_ID_SV_BCK_SV_WAIT02_e,
        dRes_ID_SV_BCK_SV_KYORO_e,
        dRes_ID_SV_BCK_SV_UNAZUKU_e,
        dRes_ID_SV_BCK_SV_HARAU_e,
        dRes_ID_SV_BCK_SV_BYE_e,
        dRes_ID_SV_BCK_SV_SHI_e,
    },
};

static sSvAnmDat l_npc_anm_wait = { 0x00, 0x08, 0xFF };
static sSvAnmDat l_npc_anm_talk = { 0x01, 0x08, 0xFF };
static sSvAnmDat l_npc_anm_talk2 = { 0x02, 0x08, 0xFF };
static sSvAnmDat l_npc_anm_talk3 = { 0x03, 0x08, 0xFF };
static sSvAnmDat l_npc_anm_ya1[] = {
    { 0x04, 0x08, 0x01 },
    { 0x00, 0x08, 0xFF },
};
static sSvAnmDat l_npc_anm_ya2[] = {
    { 0x04, 0x08, 0x01 },
    { 0x01, 0x08, 0xFF },
};
static sSvAnmDat l_npc_anm_mawasi = { 0x05, 0x00, 0xFF };
static sSvAnmDat l_npc_anm_kyoro = { 0x01, 0x08, 0xFF };
static sSvAnmDat l_npc_anm_unun[] = {
    { 0x02, 0x08, 0x01 },
    { 0xFF, 0x08, 0x00 },
};
static sSvAnmDat l_npc_anm_sisi[] = {
    { 0x03, 0x08, 0x01 },
    { 0xFF, 0x08, 0x00 },
};
static sSvAnmDat l_npc_anm_byebye[] = {
    { 0x04, 0x08, 0x01 },
    { 0xFF, 0x08, 0x00 },
};
static sSvAnmDat l_npc_anm_shi[] = {
    { 0x05, 0x08, 0x01 },
    { 0xFF, 0x08, 0x00 },
};

static sSvAnmDat* l_npc_anm_sv1_tbl[] = {
    &l_npc_anm_wait,
    &l_npc_anm_kyoro,
    &l_npc_anm_unun[0],
    &l_npc_anm_sisi[0],
    &l_npc_anm_byebye[0],
    &l_npc_anm_shi[0],
};

static int l_npc_se_sv1_tbl[] = {
    0x00000000,
    0x00000000,
    0x00004927,
    0x00004929,
    0x00004928,
    0x00000000,
};

static sSvNpcDat l_npc_dat[] = {
    {
        0x0FA0, 0x1770, 0x0000, 0x1F40,
        0x0000, 0xE890, 0xF448, 0xE0C0,
        0x03E8, 0x0000,
        0.0f, -5.0f, 0.0f, 0.0f,
        185.0f, 150.0f, 600.0f, 1503.0f,
        0x7FFF, 0x03E8, 60.0f, 150.0f,
        0x001E, 0x01, 0x01,
    },
    {
        0x1000, 0x0000, 0x0000, 0x0000,
        0xF000, 0x0000, 0x0000, 0x0000,
        0x0800, 0x0000,
        0.0f, 0.0f, 0.0f, 0.0f,
        180.0f, 150.0f, 0.0f, 0.0f,
        0x7FFF, 0x0800, 60.0f, 150.0f,
        0x001E, 0x00, 0x01,
    },
    {
        0x1000, 0x0000, 0x0000, 0x0000,
        0xF000, 0x0000, 0x0000, 0x0000,
        0x0800, 0x0000,
        0.0f, 0.0f, 0.0f, 0.0f,
        180.0f, 150.0f, 0.0f, 0.0f,
        0x7FFF, 0x0800, 60.0f, 150.0f,
        0x001E, 0x00, 0x01,
    },
    {
        0x1000, 0x0000, 0x0000, 0x0000,
        0xF000, 0x0000, 0x0000, 0x0000,
        0x0800, 0x0000,
        0.0f, 0.0f, 0.0f, 0.0f,
        180.0f, 150.0f, 0.0f, 0.0f,
        0x4000, 0x0800, 60.0f, 150.0f,
        0x001E, 0x00, 0x01,
    },
};

static u32 l_msg_sv_p1_1st_talk1[] = {
    0x34BD,
    0x34BE,
    0x34BF,
    0x34C0,
    0x0002,
    0x34C1,
    0x34C2,
    0x34C3,
    0x0001,
    0x34C4,
    0x34E8,
    0x0002,
    0x34C5,
    0x0004,
    0x0000,
};

static u32 l_msg_sv_p1_1st_talk2[] = {
    0x34BD,
    0x34BE,
    0x34BF,
    0x34C0,
    0x0002,
    0x34C1,
    0x34C2,
    0x34C3,
    0x0001,
    0x34C6,
    0x34E9,
    0x0002,
    0x34C7,
    0x0004,
    0x0000,
};

static u32 l_msg_sv_p1_2nd_talk1[] = {
    0x34C8,
    0x34C9,
    0x34EA,
    0x0002,
    0x34CA,
    0x0004,
    0x0000,
};

static u32 l_msg_sv_p1_2nd_talk2[] = {
    0x34C8,
    0x34CB,
    0x0002,
    0x34CC,
    0x0004,
    0x0000,
};

static u32 l_msg_sv_p1_3rd_talk1[] = {
    0x34CD,
    0x34D0,
    0x0002,
    0x34D1,
    0x0003,
    0x0000,
};

static u32 l_msg_sv_p1_3rd_talk2[] = {
    0x34CD,
    0x34CE,
    0x0002,
    0x34CF,
    0x0003,
    0x0000,
};

static u32 l_msg_sv_p2_1st_talk[] = {
    0x34D9,
    0x34DA,
    0x34DB,
    0x0002,
    0x34DC,
    0x0004,
    0x0000,
};

static u32 l_msg_sv_p2_2nd_talk[] = {
    0x34DD,
    0x34DE,
    0x0002,
    0x34DF,
    0x0003,
    0x0000,
};

static u32 l_msg_sv_p3_1st_talk[] = {
    0x34D2,
    0x34D3,
    0x34D4,
    0x0002,
    0x34D5,
    0x0004,
    0x0000,
};

static u32 l_msg_sv_p3_2nd_talk[] = {
    0x34D6,
    0x34D7,
    0x0002,
    0x34D8,
    0x0003,
    0x0000,
};

static u32 l_msg_sv_p4_1st_talk[] = {
    0x34E0,
    0x34E1,
    0x34E2,
    0x34E3,
    0x34E4,
    0x0005,
    0x0000,
};

static u32 l_msg_sv_p4_2nd_talk[] = {
    0x34E5,
    0x34E6,
    0x34E7,
    0x0005,
    0x0000,
};

static u32* l_msg_sv_talk_tbl[] = {
    l_msg_sv_p1_1st_talk1,
    l_msg_sv_p1_1st_talk2,
    l_msg_sv_p1_2nd_talk1,
    l_msg_sv_p1_2nd_talk2,
    l_msg_sv_p1_3rd_talk1,
    l_msg_sv_p1_3rd_talk2,
    l_msg_sv_p2_1st_talk,
    l_msg_sv_p2_2nd_talk,
    l_msg_sv_p3_1st_talk,
    l_msg_sv_p3_2nd_talk,
    l_msg_sv_p4_1st_talk,
    l_msg_sv_p4_2nd_talk,
};

static u16 l_msg_sv_flag_tbl[] = {
    0x0001,
    0x0001,
    0x0002,
    0x0002,
    0x0000,
    0x0000,
    0x0004,
    0x0000,
    0x0008,
    0x0000,
    0x0010,
    0x0000,
};

static u32 l_event_id_tbl[] = {
    0x00000000,
    0x00010001,
    0x00010001,
    0x00010001,
    0x00010001,
    0x00020002,
};

static int l_get_item_no[] = {
    0x00E5,
};

typedef s32(daNpcSv_c::*ExecuteInit_t)();
typedef void (daNpcSv_c::*ExecuteProc_t)();

static ExecuteInit_t l_execute_init[] = {
    &daNpcSv_c::executeWaitInit,
    &daNpcSv_c::executeTalkInit,
};

static ExecuteProc_t moveProc[] = {
    &daNpcSv_c::executeWait,
    &daNpcSv_c::executeTalk,
};

/* 00000078-0000021C       .text __ct__9daNpcSv_cFv */
daNpcSv_c::daNpcSv_c() {
    mNpcNo = getPrmNpcNo();
    m73A = 0;
    m739 = 0;
    m70C = -1.0f;
    m741 = 0;
    m71C = 1;
    m742 = 1;
    m728 = home.angle.y;
    m73D = 0;
    m734 = 0;
    m718 = 0;
    if(dComIfGs_checkGetItem(0xE5)) {
        m734 |= 0x20;
    }
}

/* 00000528-00000640       .text daNpc_People_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_People_nodeCallBack(J3DNode* node, int calcTiming) {
    if(calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        J3DModel* model = j3dSys.getModel();
        daNpcSv_c* i_this = (daNpcSv_c*)model->getUserArea();

        s32 jntNo = joint->getJntNo();
        MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

        if(jntNo == i_this->m_jnt.getHeadJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getHead_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getHead_x());
        }
        if(jntNo == i_this->m_jnt.getBackboneJntNum()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getBackbone_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getBackbone_x());
        }

        model->setAnmMtx(jntNo, *calc_mtx);
        MTXCopy(*calc_mtx, j3dSys.mCurrentMtx);
    }

    return true;
}

/* 00000640-00000660       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpcSv_c*>(i_this)->createHeap();
}

/* 00000660-000006B8       .text phase_1__FP9daNpcSv_c */
static cPhs_State phase_1(daNpcSv_c* i_this) {
    fopAcM_ct(i_this, daNpcSv_c);

    i_this->m73A = 1;
    return cPhs_NEXT_e;
}

/* 000006B8-00000738       .text phase_2__FP9daNpcSv_c */
static cPhs_State phase_2(daNpcSv_c* i_this) {
    cPhs_State rt = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[i_this->getNpcNo()]);
    if(rt == cPhs_COMPLEATE_e) {
        if(fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0x3800)) {
            return i_this->createInit();
        }

        i_this->mpMorf = NULL;
        return cPhs_ERROR_e;
    }

    return rt;
}

/* 00000738-00000768       .text _create__9daNpcSv_cFv */
cPhs_State daNpcSv_c::_create() {
    /* Nonmatching */
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        NULL,
    };

    return dComLbG_PhaseHandler(&mPhase2, l_method, this);
}

/* 00000768-00000A04       .text createHeap__9daNpcSv_cFv */
s32 daNpcSv_c::createHeap() {
    /* Nonmatching */
    J3DModelData* bodyModelData = (J3DModelData*)(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bmd_ix_tbl[mNpcNo]));
    mpMorf = new mDoExt_McaMorf(
        bodyModelData,
        NULL, NULL,
        (J3DAnmTransformKey*)(dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[mNpcNo][m73D])),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0
    );

    if(mpMorf == NULL || mpMorf->getModel() == NULL) {
        return false;
    }

    m_jnt.setHeadJntNum((s8)bodyModelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x3B2, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum((s8)bodyModelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(0x3B6, m_jnt.getBackboneJntNum() >= 0);

    for(int i = 0; i < bodyModelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            bodyModelData->getJointNodePointer(i)->setCallBack(daNpc_People_nodeCallBack);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));

    return true;
}

/* 00000A04-00000C74       .text createInit__9daNpcSv_cFv */
s32 daNpcSv_c::createInit() {
    /* Nonmatching */
    gravity = -9.0f;
    setAnmTbl(&l_npc_anm_wait);
    m71E = dComIfGp_evmng_getEventIdx("SV_TALK_P1_1ST", 0xFF);
    m720 = dComIfGp_evmng_getEventIdx("SV_TALK_P1_2ND", 0xFF);
    m722 = dComIfGp_evmng_getEventIdx("SV_TALK_P4_1ST", 0xFF);
    eventInfo.mEventId = (&m71E)[l_event_id_tbl[getTalkNo()]];
    mEventCut.setActorInfo2(l_npc_staff_id[mNpcNo], this);
    m730 = 0;
    m736 = 0;
    m737 = 0;
    m745 = 0;
    cullMtx = mpMorf->getModel()->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, -70.0f, 0.0f, -70.0f, 70.0f, 200.0f, 70.0f);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xB1;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xB1;
    attention_info.flags = 0xA;
    m_jnt.setParam(l_npc_dat[mNpcNo].mMaxBackboneX, l_npc_dat[mNpcNo].mMaxBackboneY,
                   l_npc_dat[mNpcNo].mMinBackboneX, l_npc_dat[mNpcNo].mMinBackboneY,
                   l_npc_dat[mNpcNo].mMaxHeadX, l_npc_dat[mNpcNo].mMaxHeadY,
                   l_npc_dat[mNpcNo].mMinHeadX, l_npc_dat[mNpcNo].mMinHeadY,
                   l_npc_dat[mNpcNo].mMaxTurnStep);
    m743 = l_npc_dat[mNpcNo].m42;
    m744 = l_npc_dat[mNpcNo].m43;
    m710 = l_npc_dat[mNpcNo].m2C;
    m726 = l_npc_dat[mNpcNo].m34;
    setMtx();
    mpMorf->getModel()->calc();
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].m38, l_npc_dat[mNpcNo].m3C);
    return 4;
}

/* 00000C74-00000CD8       .text _delete__9daNpcSv_cFv */
bool daNpcSv_c::_delete() {
    /* Nonmatching */
    dComIfG_resDelete(&mPhase, l_arcname_tbl[mNpcNo]);
    if(fopAcM_CheckCondition(this, 0x2000)) {
        if(mpMorf != NULL) {
            mpMorf->stopZelAnime();
        }
    }
    return true;
}

/* 00000CD8-00000DAC       .text _draw__9daNpcSv_cFv */
bool daNpcSv_c::_draw() {
    /* Nonmatching */
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    mpMorf->updateDL();

    cXyz shadowPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );

    return true;
}

/* 00000DAC-00000F90       .text _execute__9daNpcSv_cFv */
bool daNpcSv_c::_execute() {
    /* Nonmatching */
    fopAc_ac_c* i_target;
    fopAcM_SearchByID(parentActorID, &i_target);

    chkAttention();
    checkOrder();
    if(!dComIfGp_event_runCheck()) {
        (this->*moveProc[m739])();
    } else {
        eventMove();
    }

    eventOrder();
    if(mNpcNo == 0 && m73D == 5) {
        mpMorf->setFrame((f32)m718);
    } else {
        playAnm();
    }

    if(i_target != NULL) {
        m718 = ((daObj_Ikada_c*)i_target)->m1154;
    }

    mObjAcch.CrrPos(*dComIfG_Bgsp());
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].m38, l_npc_dat[mNpcNo].m3C);
    attention_info.position.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].m24, current.pos.z);
    eyePos.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].m28, current.pos.z);
    lookBack();
    setMtx();

    return 0;
}

/* 00000F90-00000FB8       .text executeCommon__9daNpcSv_cFv */
s32 daNpcSv_c::executeCommon() {
    if(m737 != 0) {
        m738 = 1;
    } else {
        m738 = 0;
    }
    return 0;
}

/* 00000FB8-00001000       .text executeSetMode__9daNpcSv_cFUc */
void daNpcSv_c::executeSetMode(u8 proc) {
    m739 = (this->*l_execute_init[proc])();
}

/* 00001000-00001080       .text executeWaitInit__9daNpcSv_cFv */
s32 daNpcSv_c::executeWaitInit() {
    setAnmTbl(&l_npc_anm_wait);
    m_jnt.setParam(l_npc_dat[mNpcNo].mMaxBackboneX, l_npc_dat[mNpcNo].mMaxBackboneY, l_npc_dat[mNpcNo].mMinBackboneX, l_npc_dat[mNpcNo].mMinBackboneY, l_npc_dat[mNpcNo].mMaxHeadX, l_npc_dat[mNpcNo].mMaxHeadY, l_npc_dat[mNpcNo].mMinHeadX, l_npc_dat[mNpcNo].mMinHeadY, l_npc_dat[mNpcNo].mMaxTurnStep);
    return 0;
}

/* 00001080-0000131C       .text executeWait__9daNpcSv_cFv */
void daNpcSv_c::executeWait() {
    /* Nonmatching */
    fopAc_ac_c* i_target;
    fopAcM_SearchByID(parentActorID, &i_target);
    if(i_target != NULL) {
        if(mNpcNo == 0) {
            if(m745 != 0) {
                m738 = 1;
                if(m745 != m74A) {
                    m749 = 1;
                }
                ((daObj_Ikada_c*)i_target)->m1166 = 1;
            } else {
                m738 = 0;
                m749 = 0;
                ((daObj_Ikada_c*)i_target)->m1166 = 0;
            }
            if(m749 != 0) {
                setAnmTbl(&l_npc_anm_wait);
            } else {
                m732 = i_target->shape_angle.y;
                current.angle.x = i_target->shape_angle.x;
                current.angle.z = i_target->shape_angle.z;
                m741 = 2;
                m71C = 0;
                m_jnt.setTrn();
                setAnmTbl(&l_npc_anm_mawasi);
            }
            m74A = m745;
            return;
        }

        m743 = 1;
        if(((daObj_Ikada_c*)i_target)->mCurMode == 8 || ((daObj_Ikada_c*)i_target)->mCurMode == 9 || ((daObj_Ikada_c*)i_target)->mCurMode == 5) {
            m732 = i_target->shape_angle.y;
            m741 = 2;
            m71C = 0;
            m_jnt.setTrn();
        } else if(((daObj_Ikada_c*)i_target)->mCurMode == 4 || ((daObj_Ikada_c*)i_target)->mCurMode == 6) {
            if(((daObj_Ikada_c*)i_target)->m1168 == 0) {
                m732 = i_target->shape_angle.y + 0x4000;
            } else {
                m732 = i_target->shape_angle.y - 0x4000;
            }
            m741 = 2;
            m71C = 0;
            m_jnt.setTrn();
        } else {
            s16 var_r5;
            if(((daObj_Ikada_c*)i_target)->m1168 == 0) {
                var_r5 = i_target->shape_angle.y + 0x4000;
            } else {
                var_r5 = i_target->shape_angle.y - 0x4000;
            }
            if(current.angle.y == var_r5) {
                cXyz cranePos = ((daObj_Ikada_c*)i_target)->getCranePos();
                m6EC = cranePos.x;
                m6F0 = cranePos.y;
                m6F4 = cranePos.z;
                m741 = 1;
                m71C = 1;
                m743 = 0;
            } else {
                m732 = var_r5;
                m741 = 2;
                m71C = 0;
                m_jnt.setTrn();
            }
        }

        if(((daObj_Ikada_c*)i_target)->mCurMode == 7) {
            if(m748 == 0) {
                m748 = 1;
                setAnmTbl(l_npc_anm_sv1_tbl[1]);
            }
        } else if(m748 == 1) {
            m748 = 0;
            setAnmTbl(l_npc_anm_sv1_tbl[0]);
        }
    }
}

/* 0000131C-00001338       .text executeTalkInit__9daNpcSv_cFv */
s32 daNpcSv_c::executeTalkInit() {
    if(m742 != 0) {
        return 1;
    }
    return m739;
}

/* 00001338-000013B8       .text executeTalk__9daNpcSv_cFv */
void daNpcSv_c::executeTalk() {
    /* Nonmatching */
    executeCommon();
    if(talk2(1, this) == 0x12) {
        m736 = 0;
        m749 = 0;
        executeSetMode(0);
        dComIfGp_event_setItemPartnerId(0);
        return;
    }
    setAnmFromMsgTag();
}

/* 000013B8-000013EC       .text checkOrder__9daNpcSv_cFv */
void daNpcSv_c::checkOrder() {
    if(eventInfo.mCommand == 2) {
        return;
    }
    if(eventInfo.mCommand != 1) {
        return;
    }
    if(m738 == 2 || m738 == 1) {
        m736 = 1;
    }
}

/* 000013EC-00001458       .text eventOrder__9daNpcSv_cFv */
void daNpcSv_c::eventOrder() {
    if((m738 == 2 || m738 == 1) && isTalkOK()) {
        eventInfo.mCondition |= 1;
        if(m738 == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00001458-00001570       .text eventMove__9daNpcSv_cFv */
void daNpcSv_c::eventMove() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck(m71E) || dComIfGp_evmng_endCheck(m720) || dComIfGp_evmng_endCheck(m722)) {
        eventInfo.mEventId = (&m71E)[l_event_id_tbl[getTalkNo()]];
        dComIfGp_event_onEventFlag(8);
        m73C &= ~2;
        m736 = 0;
        m749 = 0;
        executeSetMode(0);
        return;
    }
    u8 attnFlag = mEventCut.getAttnFlag();
    if(mEventCut.cutProc()) {
        if(!mEventCut.getAttnFlag()) {
            mEventCut.setAttnFlag(attnFlag);
        }
    } else {
        privateCut();
        if(mNpcNo == 0) {
            setAnmFromMsgTag();
        }
    }
}

/* 00001570-00001744       .text privateCut__9daNpcSv_cFv */
void daNpcSv_c::privateCut() {
    /* Nonmatching */
    static char* cut_name_tbl[] = {"MES_SET", "GET_ITEM", "SET_ANGLE", "ATTENTION", "TURN_OK"};
    dEvent_manager_c* evtMgr = dComIfGp_getPEvtManager();
    s32 staffIdx = dComIfGp_evmng_getMyStaffId(l_npc_staff_id[mNpcNo], NULL, 0);
    if(staffIdx != -1) {
        m740 = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, 5, 1, 0);
        if((s8)m740 == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch(m740) {
                case 0:
                    eventMesSetInit(staffIdx);
                    break;
                case 1:
                    eventGetItemInit(staffIdx);
                    break;
                case 2:
                    eventSetAngleInit();
                    break;
                case 3:
                    eventAttentionInit(staffIdx);
                    break;
                case 4:
                    eventTurnOkInit();
                    break;
                }
            }
            u8 rt;
            switch(m740) {
            case 0:
                rt = eventMesSet();
                break;
            case 1:
                rt = eventGetItem();
                break;
            case 3:
                rt = eventAttention();
                break;
            default:
            case 2:
                rt = 1;
                break;
            }
            if(rt != 0) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }
    }
    if(m73C & 2) {
        m732 = m72C;
        m741 = 2;
        m71C = 0;
        m_jnt.setTrn();
    }
}

/* 00001744-00001814       .text eventMesSetInit__9daNpcSv_cFi */
void daNpcSv_c::eventMesSetInit(int i_staffIdx) {
    /* Nonmatching */
    int* substance = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "MsgNo");
    if(substance != NULL) {
        mMsgTbl = NULL;
        int msgNo = *substance;
        if(msgNo != 0) {
            setMessage(msgNo);
        } else {
            setMessage(getMsg());
        }
    } else {
        mMsgTbl += 1;
        setMessage(*mMsgTbl);
    }
    dComIfGp_event_setItemPartnerId(dComIfGp_evmng_getMyStaffId(l_npc_staff_id[mNpcNo], this, 0));
}

/* 00001814-0000184C       .text eventMesSet__9daNpcSv_cFv */
bool daNpcSv_c::eventMesSet() {
    return talk2(0, this) == 0x12;
}

/* 0000184C-000018F0       .text eventGetItemInit__9daNpcSv_cFi */
void daNpcSv_c::eventGetItemInit(int i_staffIdx) {
    /* Nonmatching */
    int* substance = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ItemNo");
    int itemNo;
    if(substance != NULL) {
        itemNo = l_get_item_no[*substance];
    } else {
        itemNo = m714;
    }
    int proc = fopAcM_createItemForPresentDemo(&current.pos, itemNo, 0, -1, fopAcM_GetRoomNo(this), NULL, NULL);
    if((u32)(proc + 0x10000) != 0xFFFF) {
        dComIfGp_event_setItemPartnerId(proc);
    }
}

/* 000018F0-000018F8       .text eventGetItem__9daNpcSv_cFv */
s32 daNpcSv_c::eventGetItem() {
    return true;
}

/* 000018F8-000019E0       .text eventSetAngleInit__9daNpcSv_cFv */
void daNpcSv_c::eventSetAngleInit() {
    fopAc_ac_c* i_target;
    fopAcM_SearchByID(parentActorID, &i_target);
    if(i_target != NULL) {
        fopAc_ac_c* link = dComIfGp_getLinkPlayer();
        s16 angle;
        dNpc_calc_DisXZ_AngY(i_target->current.pos, link->current.pos, NULL, &angle);
        angle -= i_target->shape_angle.y;
        if(angle > 0) {
            m72C = i_target->shape_angle.y + 0x4000;
        } else {
            m72C = i_target->shape_angle.y - 0x4000;
        }
        m728 = m72C;
    } else {
        m72C = m728;
    }
    m73C |= 2;
}

/* 000019E0-00001A74       .text eventAttentionInit__9daNpcSv_cFi */
void daNpcSv_c::eventAttentionInit(int i_staffIdx) {
    /* Nonmatching */
    int* substance = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "Timer");
    if(substance != NULL) {
        m72A = *substance;
    } else {
        m72A = 0xC;
    }
    m748 = 0;
    if(mNpcNo == 2) {
        dComIfGp_event_setItemPartnerId(dComIfGp_evmng_getMyStaffId(l_npc_staff_id[mNpcNo], this, 0));
    }
}

/* 00001A74-00001BC8       .text eventAttention__9daNpcSv_cFv */
s32 daNpcSv_c::eventAttention() {
    /* Nonmatching */
    if(m72A != 0) {
        m72A--;
        if(m72A == 0) {
            fopAc_ac_c* target = fopAcM_searchFromName(l_npc_staff_id[mNpcNo], 0, 0);
            if(target != NULL) {
                setAnmTbl(l_npc_anm_sv1_tbl[target->attention_info.distances[fopAc_Attn_TYPE_TALK_e]]);
                if(mNpcNo == 1) {
                    mDoAud_seStart(l_npc_se_sv1_tbl[target->attention_info.distances[fopAc_Attn_TYPE_TALK_e]], NULL, 0, 0);
                }
            } else {
                setAnmTbl(l_npc_anm_sv1_tbl[2]);
                mDoAud_seStart(l_npc_se_sv1_tbl[2], NULL, 0, 0);
            }
        }
    }
    return 0;
}

/* 00001BC8-00001BD4       .text eventTurnOkInit__9daNpcSv_cFv */
void daNpcSv_c::eventTurnOkInit() {
    m743 = 1;
}

/* 00001BD4-00001CF0       .text talk2__9daNpcSv_cFiP10fopAc_ac_c */
u16 daNpcSv_c::talk2(int param_1, fopAc_ac_c* param_2) {
    /* Nonmatching */
    u16 msg_status = 0xFF;
    if(mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        if(param_1 == 1) {
            mCurrMsgNo = getMsg();
        }
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, param_2);
        mpCurrMsg = NULL;
    } else {
        if(mpCurrMsg != NULL) {
            msg_status = mpCurrMsg->mStatus;
            switch(msg_status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                if((u16)mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
                break;
            case fopMsgStts_MSG_TYPING_e:
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                mCurrMsgBsPcId = -1;
                break;
            }
            anmAtr(msg_status);
        } else {
            mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
        }
    }
    return msg_status;
}

/* 00001CF0-00001DC8       .text next_msgStatus__9daNpcSv_cFPUl */
u16 daNpcSv_c::next_msgStatus(u32* pMsgNo) {
    /* Nonmatching */
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    if(*pMsgNo != 0) {
        if(mMsgTbl != NULL) {
            mMsgTbl += 1;
            switch(*mMsgTbl) {
            case 1:
                ret = fopMsgStts_MSG_DISPLAYED_e;
                break;
            case 2:
                m747 = 2;
                ret = fopMsgStts_MSG_DISPLAYED_e;
                break;
            case 3:
                m747 = 3;
                ret = fopMsgStts_MSG_DISPLAYED_e;
                break;
            case 4:
                m747 = 4;
                ret = fopMsgStts_MSG_DISPLAYED_e;
                break;
            case 5:
                m747 = 5;
                ret = fopMsgStts_MSG_DISPLAYED_e;
                break;
            case 0:
                mMsgTbl = NULL;
                ret = fopMsgStts_MSG_DISPLAYED_e;
                break;
            default:
                *pMsgNo = *mMsgTbl;
                break;
            }
        } else {
            ret = fopMsgStts_MSG_DISPLAYED_e;
        }
    } else {
        ret = fopMsgStts_MSG_DISPLAYED_e;
    }
    return ret;
}

/* 00001DC8-00001EB4       .text getMsg__9daNpcSv_cFv */
u32 daNpcSv_c::getMsg() {
    /* Nonmatching */
    u32 msgNo = 0;
    u8 isTalkBtn = 0;
    mMsgTbl = NULL;
    if(g_dComIfG_gameInfo.play.getEvent()->mTalkButton == 1 ||
       g_dComIfG_gameInfo.play.getEvent()->mTalkButton == 2 ||
       g_dComIfG_gameInfo.play.getEvent()->mTalkButton == 3) {
        isTalkBtn = 1;
    }
    if(isTalkBtn == 0) {
        mMsgTbl = l_msg_sv_talk_tbl[m746];
        m734 |= l_msg_sv_flag_tbl[m746];
        if(m734 & 0x10) {
            dComIfGs_onEventBit(0x2F80);
        }
    }
    if(mMsgTbl != NULL) {
        msgNo = *mMsgTbl;
    }
    if(msgNo == 0) {
        setAnmTbl(&l_npc_anm_talk);
    }
    return msgNo;
}

/* 00001EB4-00001EBC       .text setMessage__9daNpcSv_cFUl */
void daNpcSv_c::setMessage(u32 msgNo) {
    mCurrMsgNo = msgNo;
}

/* 00001EBC-00001F74       .text setAnmFromMsgTag__9daNpcSv_cFv */
void daNpcSv_c::setAnmFromMsgTag() {
    switch(dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnmTbl(&l_npc_anm_wait);
            break;
        case 1:
            setAnmTbl(&l_npc_anm_ya1[0]);
            break;
        case 2:
            setAnmTbl(&l_npc_anm_talk);
            break;
        case 3:
            setAnmTbl(&l_npc_anm_talk2);
            break;
        case 4:
            setAnmTbl(&l_npc_anm_talk3);
            break;
        case 5:
            setAnmTbl(&l_npc_anm_ya2[0]);
            break;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xFF);
}

/* 00001F74-00001F94       .text getPrmNpcNo__9daNpcSv_cFv */
u8 daNpcSv_c::getPrmNpcNo() {
    if(0 <= argument && argument < 4) {
        return argument;
    }
    return 0;
}

/* 00001F94-0000209C       .text setMtx__9daNpcSv_cFv */
void daNpcSv_c::setMtx() {
    /* Nonmatching */
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    cXyz offset(l_npc_dat[mNpcNo].m14, l_npc_dat[mNpcNo].m18, l_npc_dat[mNpcNo].m1C);
    mDoMtx_YrotS(mDoMtx_stack_c::now, current.angle.y);
    MtxPosition(&offset, &offset);
    mDoMtx_stack_c::transS(current.pos + offset);
    mDoMtx_XYZrotM(mDoMtx_stack_c::now, current.angle.x, 0, current.angle.z);
    mDoMtx_YrotM(mDoMtx_stack_c::now, current.angle.y);
    PSMTXCopy(mDoMtx_stack_c::now, model->getBaseTRMtx());
}

/* 0000209C-000023D4       .text chkAttention__9daNpcSv_cFv */
void daNpcSv_c::chkAttention() {
    /* Nonmatching */
    m745 = 0;
    f32 distXZ;
    s16 angle;
    if(mEventCut.getAttnFlag()) {
        cXyz pos = mEventCut.getAttnPos();
        m6EC = pos.x;
        m6F0 = pos.y;
        m6F4 = pos.z;
        m741 = 1;
        if(m743 != 0) {
            m71C = 0;
            m_jnt.setTrn();
        } else {
            m71C = 1;
        }
        if(m737 == 0) {
            m737 = 1;
        }
    } else {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        f32 dist = m710;
        s32 limitAngle = m726;
        dNpc_calc_DisXZ_AngY(current.pos, player->current.pos, &distXZ, &angle);
        if(m737 != 0) {
            dist += 100.0f;
            limitAngle += 0x71C;
        }
        angle -= shape_angle.y;
        if(dist > distXZ && limitAngle > abs(angle)) {
            cXyz eyePos2 = dNpc_playerEyePos(l_npc_dat[mNpcNo].m20);
            m6EC = eyePos2.x;
            m6F0 = eyePos2.y;
            m6F4 = eyePos2.z;
            m741 = 1;
            if(m743 != 0) {
                m71C = 0;
            } else {
                m71C = 1;
            }
            if(m744 == 0) {
                m732 = m728;
                m71C = 0;
                m741 = 2;
                m_jnt.setTrn();
            }
            if(m737 == 0) {
                m737 = 1;
            }
            m745 = 1;
        } else {
            if(m737 == 1) {
                m737 = 0;
                m724 = l_npc_dat[mNpcNo].m40;
            }
            if(l_npc_dat[mNpcNo].m30 > distXZ) {
                cXyz eyePos2 = dNpc_playerEyePos(l_npc_dat[mNpcNo].m20);
                m6EC = eyePos2.x;
                m6F0 = eyePos2.y;
                m6F4 = eyePos2.z;
                m741 = 1;
                if(m743 != 0) {
                    m71C = 0;
                } else {
                    m71C = 1;
                }
                if(m744 == 0) {
                    m732 = m728;
                    m71C = 0;
                    m741 = 2;
                    m_jnt.setTrn();
                }
                m745 = 1;
            } else {
                m741 = 0;
                if(m6D8 == 0) {
                    if(m724 != 0) {
                        m724--;
                    } else {
                        m732 = m728;
                        m71C = 0;
                        m741 = 2;
                        m_jnt.setTrn();
                    }
                }
            }
        }
    }
    m72E = l_npc_dat[mNpcNo].m36;
}

/* 000023D4-00002520       .text lookBack__9daNpcSv_cFv */
void daNpcSv_c::lookBack() {
    /* Nonmatching */
    s16 var_r4 = m72E;
    s16 var_r31 = current.angle.y;
    cXyz* lookPos = NULL;
    cXyz srcPos = eyePos;
    u8 var_r29 = m71C;
    switch(m741) {
    case 1: {
        cXyz pos(m6EC, m6F0, m6F4);
        lookPos = &pos;
        break;
    }
    case 2:
        var_r31 = m732;
        break;
    }
    if(m736 != 0 && m743 != 0) {
        var_r29 = 0;
        m_jnt.setTrn();
    }
    if(m_jnt.trnChk()) {
        s16 turnSpeed = mEventCut.getTurnSpeed();
        if(turnSpeed != 0) {
            var_r4 = turnSpeed;
        }
        cLib_addCalcAngleS2(&m730, var_r4, 4, 0x800);
    } else {
        m730 = 0;
    }
    cXyz srcPos2 = srcPos;
    m_jnt.lookAtTarget(&current.angle.y, lookPos, srcPos2, var_r31, m730, var_r29);
    shape_angle.x = current.angle.x;
    shape_angle.y = current.angle.y;
    shape_angle.z = current.angle.z;
}

/* 00002520-000025E8       .text playAnm__9daNpcSv_cFv */
void daNpcSv_c::playAnm() {
    /* Nonmatching */
    m73E &= 0xFE;
    if(mpMorf->play(NULL, 0, 0) != 0 && mAnmDat != NULL && (s8)m73F > 0) {
        m73F--;
        if((s8)m73F == 0) {
            mAnmDat++;
            if(setAnmTbl(mAnmDat) != 0) {
                m73E |= 1;
            }
        } else {
            setAnm(mAnmDat->mAnmNo, 0, 0.0f);
        }
    }
}

/* 000025E8-000026C8       .text setAnm__9daNpcSv_cFUcif */
void daNpcSv_c::setAnm(u8 anmNo, int mode, f32 speed) {
    /* Nonmatching */
    if (m70C >= 0.0f) {
        speed = m70C;
        m70C = -1.0f;
    }
    mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[mNpcNo][anmNo]),
        mode, speed, 1.0f, 0.0f, -1.0f, NULL
    );
    m73D = anmNo;
}

/* 000026C8-00002768       .text setAnmTbl__9daNpcSv_cFP9sSvAnmDat */
u8 daNpcSv_c::setAnmTbl(sSvAnmDat* anmDat) {
    /* Nonmatching */
    if(anmDat->mAnmNo == 0xFF) {
        mAnmDat = NULL;
        return true;
    }
    mAnmDat = anmDat;
    m73F = mAnmDat->mRepeat;
    int mode = 2;
    if((s8)m73F > 0) {
        mode = 0;
    }
    sSvAnmDat* pAnmDat = mAnmDat;
    u8 anmNo = pAnmDat->mAnmNo;
    if(m73D != anmNo || mode == 0) {
        setAnm(anmNo, mode, (f32)pAnmDat->mSpeed);
    }
    return false;
}

/* 00002768-000027E0       .text setCollision__9daNpcSv_cFP8dCcD_Cyl4cXyzff */
void daNpcSv_c::setCollision(dCcD_Cyl* pCyl, cXyz pos, f32 radius, f32 height) {
    pCyl->SetC(pos);
    pCyl->SetR(radius);
    pCyl->SetH(height);
    dComIfG_Ccsp()->Set(pCyl);
}

/* 000027E0-0000293C       .text getTalkNo__9daNpcSv_cFv */
u8 daNpcSv_c::getTalkNo() {
    /* Nonmatching */
    int bHook = dComIfGs_checkGetItem(dItemNo_GRAPPLING_HOOK_e) != 0;
    m746 = 0;
    u16 flags = m734;

    if (!(flags & 0x20)) {
        if (!(flags & 1)) {
            if (bHook) {
                m746 = 1;
            } else {
                m746 = 0;
            }
        } else if (!(flags & 2)) {
            if (bHook) {
                m746 = 3;
            } else {
                m746 = 2;
            }
        } else if (bHook) {
            m746 = 5;
        } else {
            m746 = 4;
        }
    } else if (!bHook) {
        if (flags & 4) {
            m746 = 7;
        } else {
            m746 = 6;
        }
    } else if (!dComIfGs_isCollect(0, 1)) {
        if (m734 & 8) {
            m746 = 9;
        } else {
            m746 = 8;
        }
    } else if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F80)) {
        m746 = 0xA;
    } else {
        m746 = 0xB;
    }
    return m746;
}

/* 0000293C-00002958       .text isTalkOK__9daNpcSv_cFv */
s32 daNpcSv_c::isTalkOK() {
    if (g_dComIfG_gameInfo.play.mPlayerStatus[0][0] & 0x100000) {
        return 0;
    }
    return 1;
}

/* 00002958-00002978       .text daNpc_PeopleCreate__FPv */
static cPhs_State daNpc_PeopleCreate(void* i_this) {
    return ((daNpcSv_c*)i_this)->_create();
}

/* 00002978-0000299C       .text daNpc_PeopleDelete__FPv */
static BOOL daNpc_PeopleDelete(void* i_this) {
    return ((daNpcSv_c*)i_this)->_delete();
}

/* 0000299C-000029C0       .text daNpc_PeopleExecute__FPv */
static BOOL daNpc_PeopleExecute(void* i_this) {
    return ((daNpcSv_c*)i_this)->_execute();
}

/* 000029C0-000029E4       .text daNpc_PeopleDraw__FPv */
static BOOL daNpc_PeopleDraw(void* i_this) {
    return ((daNpcSv_c*)i_this)->_draw();
}

/* 000029E4-000029EC       .text daNpc_PeopleIsDelete__FPv */
static BOOL daNpc_PeopleIsDelete(void* i_this) {
    return true;
}

static actor_method_class daNpc_PeopleMethodTable = {
    (process_method_func)daNpc_PeopleCreate,
    (process_method_func)daNpc_PeopleDelete,
    (process_method_func)daNpc_PeopleExecute,
    (process_method_func)daNpc_PeopleIsDelete,
    (process_method_func)daNpc_PeopleDraw,
};

actor_process_profile_definition g_profile_NPC_SV = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_SV_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcSv_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_SV_e,
    /* Actor SubMtd */ &daNpc_PeopleMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
