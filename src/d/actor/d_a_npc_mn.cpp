/**
 * d_a_npc_mn.cpp
 * NPC - Manny
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_mn.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "d/d_picture_box.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"

static char* l_npc_staff_id[] = {
    "Mn",
};

static const char* l_arcname_tbl[] = { "Mn" };
static const u16 l_bmd_ix_tbl[] = { 2 };
static const u16 l_etc_bmd_ix_tbl[] = { 1 };
static const u16 l_bck_ix_tbl[] = { 6, 10, 4, 5, 11, 7, 8, 9 };
static const u16 l_btp_ix_tbl[] = { 3 };

static sMnAnmDat l_npc_anm_wait[] = {
    {
        0x00,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_wait2[] = {
    {
        0x01,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_talk[] = {
    {
        0x02,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_talk2[] = {
    {
        0x03,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_walk[] = {
    {
        0x04,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_bikkuri[] = {
    {
        0x05,
        0x08,
        0x01,
    },

    {
        0x00,
        0x08,
        0xFF,
    },
};

static sMnAnmDat l_npc_anm_jump1[] = {
    {
        0x06,
        0x08,
        0x01,
    },

    {
        0xFF,
        0x08,
        0x00,
    },
};

static sMnAnmDat l_npc_anm_jump2[] = {
    {
        0x07,
        0x08,
        0xFF,
    },
};

static sMnDat l_npc_dat[] = {
    {
        0x0FA0,
        0x2710,
        0x0000,
        0x1770,
        0xF830,
        0xD8F0,
        0xE890,
        0xF060,
        0x05DC,
        0x0000,
        0x00000000,
        150.0f,
        120.0f,
        250.0f,
        0.0f,
        0x7FFF,
        0x0514,
        0x0190,
        0x0000,
        60.0f,
        0.5f,
        3.0f,
        0x0006,
        0x0400,
        0x003C,
        0x005A,
        0x00C8,
        0x012C,
        0x001E,
        0x01,
        0x01,
    },
    {
        0x0FA0,
        0x2710,
        0x0000,
        0x1770,
        0xF830,
        0xD8F0,
        0xE890,
        0xF060,
        0x05DC,
        0x0000,
        0x00000000,
        150.0f,
        120.0f,
        250.0f,
        0.0f,
        0x7FFF,
        0x0514,
        0x0190,
        0x0000,
        60.0f,
        0.5f,
        1.5f,
        0x0006,
        0x0400,
        0x003C,
        0x005A,
        0x00C8,
        0x012C,
        0x001E,
        0x01,
        0x01,
    },
};

static u32 l_msg_mn_1st_talk[] = {
    0x35E9,
    0x35EA,
    0x35EB,
    0x0000,
};

static u32 l_msg_mn_2nd_talk[] = {
    0x35EC,
    0x35ED,
    0x35EE,
    0x0000,
};

static u32 l_msg_mn_1st_talk_in[] = {
    0x35F1,
    0x0000,
};

static u32 l_msg_mn_2nd_talk_in[] = {
    0x35F2,
    0x0000,
};

static u32 l_msg_mn_3rd_talk_in[] = {
    0x35F0,
    0x0000,
};

static u32 l_msg_mn_comp_1st[] = {
    0x35F3,
    0x35F4,
    0x35F5,
    0x0000,
};

static u32 l_msg_mn_comp_2nd[] = {
    0x35F6,
    0x0000,
};

static u32 l_msg_mn_figure[] = {
    0x35F7,
    0x35F8,
    0x35F9,
    0x35FA,
    0x35FB,
    0x35FC,
    0x35FD,
    0x35FE,
    0x35FF,
    0x3600,
};

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0xFFFFFFFF,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0x15,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 4,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 40.0f,
        /* Height */ 160.0f,
    }},
};

static char* l_room_name[] = {
    "sea",
    "Pfigure",
    "figureA",
    "figureB",
    "figureC",
    "figureD",
    "figureE",
    "figureF",
    "figureG",
    "K_Testb",
};

static const u16 l_figure_comp[] = {
    0x95FF, 0x94FF,
    0x93FF, 0x92FF,
    0x91FF, 0x90FF,
    0x8FFF, 0x8EFF,
    0x8DFF, 0x8CFF,
    0xB1FF, 0x9CFF,
    0x84FF, 0x83FF,
    0x82FF, 0x81FF,
    0x80FF,
};

/* 00000078-00000230       .text __ct__9daNpcMn_cFv */
daNpcMn_c::daNpcMn_c() {
    m7B5 = 0;
    m7B4 = 0;
    m77C = 0.0f;
    mTimer = 0;
    m780 = -1.0f;
    mLookMode = 0;
    m794 = 1;
    m7A0 = home.angle.y;
    mAnmNo = 0;
    m7A4 = 0;
    mPosNo = chkPosNo();
    mNpcNo = getPrmNpcNo();
}

/* 000005E0-000006F8       .text daNpc_Mn_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Mn_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpcMn_c* i_this = (daNpcMn_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();

        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));

        if (jntNo == i_this->m_jnt.getHeadJntNum()) {
            mDoMtx_stack_c::XrotM(i_this->m_jnt.getHead_y());
            mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
        }
        if (jntNo == i_this->m_jnt.getBackboneJntNum()) {
            mDoMtx_stack_c::XrotM(i_this->m_jnt.getBackbone_y());
            mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());
        }

        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        PSMTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 000006F8-00000718       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpcMn_c*>(i_this)->createHeap();
}

/* 00000718-0000085C       .text phase_1__FP9daNpcMn_c */
static cPhs_State phase_1(daNpcMn_c* i_this) {
    fopAcM_SetupActor(i_this, daNpcMn_c);

    if (i_this->mPosNo != 0) {
        u8 reg = dComIfGs_getEventReg(0x870F);
        if (i_this->isChangePos(reg)) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A01)) {
                reg = i_this->getPosNo();
            } else {
                reg = 1;
            }
            dComIfGs_setEventReg(0x870F, reg);
        }
        if (reg != i_this->mPosNo) {
            return cPhs_ERROR_e;
        }
    } else {
        dComIfGs_setEventReg(0x870F, 0);
        if (dComIfGs_isSwitch(i_this->getPrmSwitchBit(), (s8)i_this->home.field_0x13)) {
            return cPhs_ERROR_e;
        }
    }
    i_this->m7B5 = 1;
    return cPhs_NEXT_e;
}

/* 0000085C-000008D4       .text phase_2__FP9daNpcMn_c */
static cPhs_State phase_2(daNpcMn_c* i_this) {
    cPhs_State phase_state = dComIfG_resLoad(&i_this->mPhs, l_arcname_tbl[0]);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0)) {
            return i_this->createInit();
        }
        i_this->mpMorf = NULL;
        return cPhs_ERROR_e;
    }
    return phase_state;
}

/* 000008D4-00000904       .text _create__9daNpcMn_cFv */
cPhs_State daNpcMn_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        NULL,
    };
    return dComLbG_PhaseHandler(&mPhs2, l_method, this);
}

/* 00000904-00000BE0       .text createHeap__9daNpcMn_cFv */
BOOL daNpcMn_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bmd_ix_tbl[0]);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[mAnmNo]),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x15021222
    );

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x3E4, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(0x3E8, m_jnt.getBackboneJntNum() >= 0);

    if (!initTexPatternAnm(false)) {
        return FALSE;
    }

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            modelData->getJointNodePointer(i)->setCallBack(daNpc_Mn_nodeCallBack);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);

    mAcchCir.SetWall(30.0f, 30.0f);
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

    m734 = mDoExt_J3DModel__create((J3DModelData*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_etc_bmd_ix_tbl[0]), 0x80000, 0x11000002);
    if (m734 == NULL) {
        return FALSE;
    }

    m7C2 = modelData->getJointName()->getIndex("shoulderR");
    return TRUE;
}

/* 00000BE0-00000C00       .text daNpcMn_XyCheckCB__FPvi */
static s16 daNpcMn_XyCheckCB(void* i_this, int i_param) {
    return static_cast<daNpcMn_c*>(i_this)->XyCheckCB(i_param);
}

/* 00000C00-00000F3C       .text createInit__9daNpcMn_cFv */
cPhs_State daNpcMn_c::createInit() {
    u8 railID = getPrmRailID();
    u8 ret = 0xFF;
    if (railID != 0xFF) {
        mPathRun.setInf(railID, (s8)current.angle.y, 1);
        if (!mPathRun.isPath()) {
            return cPhs_ERROR_e;
        }
        dPath_GetNextRoomPath(mPathRun.getPath(), -1);
        m794 = 0;
        u8 idx = 0;
        while (idx < mPathRun.maxPoint()) {
            if (mPathRun.pointArg(idx) != 0) {
                idx++;
                continue;
            }
            break;
        }
        if (idx == mPathRun.maxPoint()) {
            idx = 0;
        }
        mPathRun.setIdx(idx);
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        mLookAtX = point.x;
        mLookAtY = point.y;
        mLookAtZ = point.z;
        current.pos.set(point.x, point.y, point.z);
        mPathRun.incIdxLoop();
        mTimer = 1;
        ret = 0xFE;
    }

    gravity = -9.0f;
    setAnmTbl(l_npc_anm_wait);
    mEventIdx = dComIfGp_evmng_getEventIdx("FIGURE_HATCH_OPEN", 0xff);
    eventInfo.mpCheckCB = daNpcMn_XyCheckCB;
    mEventCut.setActorInfo2(l_npc_staff_id[mNpcNo], this);
    mAngAccel = 0;
    mMode = 0;
    mAttnFlag = 0;
    m7C0 = 0;
    cullMtx = mpMorf->getModel()->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, -280.0f, 1.0f, -280.0f, 280.0f, 200.0f, 280.0f);
    m7BE = 0xAA;
    m7BF = 0xAA;
    m790 = 10;
    m_jnt.setParam(
        l_npc_dat[mNpcNo].mMax_backbone_x,
        l_npc_dat[mNpcNo].mMax_backbone_y,
        l_npc_dat[mNpcNo].mMin_backbone_x,
        l_npc_dat[mNpcNo].mMin_backbone_y,
        l_npc_dat[mNpcNo].mMax_head_x,
        l_npc_dat[mNpcNo].mMax_head_y,
        l_npc_dat[mNpcNo].mMin_head_x,
        l_npc_dat[mNpcNo].mMin_head_y,
        l_npc_dat[mNpcNo].mMax_turn_step
    );
    m794 = l_npc_dat[mNpcNo].field_0x4A;
    m7BF = l_npc_dat[mNpcNo].field_0x4B;
    mAttnDist = l_npc_dat[mNpcNo].field_0x20;
    mTurnSpeed = l_npc_dat[mNpcNo].field_0x28;
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    f32 groundY = mObjAcch.GetGroundH();
    if (l_npc_dat[mNpcNo].field_0x18 != groundY) {
        mLookAtY = groundY;
        current.pos.y = groundY;
    }
    setMtx();
    mpMorf->getModel()->getBaseTRMtx();
    mStts.Init(ret, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].field_0x30, 150.0f);
    return cPhs_NEXT_e;
}

/* 00000F3C-00000FE4       .text _delete__9daNpcMn_cFv */
bool daNpcMn_c::_delete() {
    dComIfG_resDelete(&mPhs, l_arcname_tbl[0]);
    if (m794) {
        if (mpMorf != NULL) {
            mpMorf->stopZelAnime();
        }
    }
    if (dComIfGp_getStartStageRoomNo() != 0 && strcmp(dComIfGp_getNextStageName(), "sea") == 0) {
        dComIfGs_setEventReg(0x870F, 0);
    }
    return true;
}

/* 00000FE4-00001154       .text _draw__9daNpcMn_cFv */
bool daNpcMn_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    mBtpAnm.entry(modelData, mTexPatternNo);
    mpMorf->updateDL();
    mBtpAnm.remove(modelData);

    J3DModel* model2 = m734;
    g_env_light.setLightTevColorType(model2, &tevStr);
    mDoMtx_stack_c::copy(model->getAnmMtx(m7C2));
    model2->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoExt_modelUpdateDL(model2);

    cXyz shadowPos(
        current.pos.x,
        current.pos.y + 150.0f,
        current.pos.z
    );
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, model, &shadowPos, 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr
    );
    dSnap_RegistFig(DSNAP_TYPE_UNKA8, this, 1.0f, 1.0f, 1.0f);
    return true;
}

static daNpcMn_c::InitFunc_t l_execute_init[] = {
    &daNpcMn_c::executeWaitInit,
    &daNpcMn_c::executeTalkInit,
    &daNpcMn_c::executeWalkInit,
    &daNpcMn_c::executeTurnInit,
    &daNpcMn_c::executeTalk3Init,
};

static daNpcMn_c::MoveFunc_t moveProc[] = {
    &daNpcMn_c::executeWait,
    &daNpcMn_c::executeTalk,
    &daNpcMn_c::executeWalk,
    &daNpcMn_c::executeTurn,
    &daNpcMn_c::executeTalk3,
};

/* 00001154-00001344       .text _execute__9daNpcMn_cFv */
bool daNpcMn_c::_execute() {
    chkAttention();
    checkOrder();

    if (!dComIfGp_event_runCheck() || eventInfo.checkCommandTalk() || m7C3) {
        (this->*moveProc[m7B4])();
    } else {
        eventMove();
    }

    eventOrder();
    playTexPatternAnm();
    playAnm();

    if (mAnmNo == 4) {
        cLib_chaseF(&m788, m77C, 0.3f);
        f32 speed = m788 * l_npc_dat[mNpcNo].field_0x34;
        if (speed < 0.5f) {
            speed = 0.5f;
        }
        mpMorf->getModel()->setBaseScale(cXyz(speed, speed, speed));
    } else {
        cLib_chaseF(&m788, m77C, 0.1f);
    }

    fopAcM_posMoveF(this, &speed);
    mObjAcch.CrrPos(*dComIfG_Bgsp());

    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].field_0x30, 150.0f);

    attention_info.position.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x18, current.pos.z);
    eyePos.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x1C, current.pos.z);

    lookBack();
    setMtx();
    return false;
}

/* 00001344-000013B4       .text executeCommon__9daNpcMn_cFv */
BOOL daNpcMn_c::executeCommon() {
    if (mAttnFlag) {
        mOrderMode = 1;
    } else {
        mOrderMode = 0;
    }

    if (mMode == 1 && m7B4 != 1) {
        executeSetMode(1);
    }

    return mMode;
}

/* 000013B4-0000140C       .text executeSetMode__9daNpcMn_cFUc */
void daNpcMn_c::executeSetMode(u8 param_1) {
    m77C = 0.0f;
    m788 = 0.0f;
    m7B4 = (this->*l_execute_init[param_1])();
}

/* 0000140C-00001518       .text executeWaitInit__9daNpcMn_cFv */
s32 daNpcMn_c::executeWaitInit() {
    m788 = 1.0f;
    if (m7C4 != 0) {
        setAnmTbl(l_npc_anm_wait2);
        mTimer = (s16)(150.0f + cM_rndF(30.0f));
    } else {
        setAnmTbl(l_npc_anm_wait);
        mTimer = (s16)((f32)l_npc_dat[mNpcNo].field_0x40 + cM_rndF((f32)(l_npc_dat[mNpcNo].field_0x42 - l_npc_dat[mNpcNo].field_0x40)));
    }
    return FALSE;
}

/* 00001518-000017CC       .text executeWait__9daNpcMn_cFv */
void daNpcMn_c::executeWait() {
    executeCommon();
    if (mPosNo == 0) {
        if (dComIfGp_getStartStagePoint() & 0x200000) {
            mAttnDist = (f32)(s16)(2.0f * l_npc_dat[mNpcNo].field_0x20);
        } else {
            mAttnDist = l_npc_dat[mNpcNo].field_0x20;
            m7A4 &= 0xFFFE;
        }
        if (mAttnFlag && dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F08) && (dComIfGp_getStartStagePoint() & 0x200000)) {
            m7BE = 1;
            if (dComIfGp_getMesgAnimeAttrInfo() == 0xB) {
                if (!(m7A4 & 1)) {
                    m7A4 |= 1;
                    executeSetMode(4);
                }
            }
        }
        if (!(mSwFlag & 1) && dComIfGs_isSwitch(getPrmSwitchBit(), (s8)home.roomNo)) {
            dComIfGs_onSwitch(getPrmSwitchBit(), (s8)home.roomNo);
            mSwFlag |= 1;
            m794 = 0;
            m7BF = 0;
            mOrderMode = 3;
        }
    } else if (m7C4 != 0) {
        if (mTimer == 0) {
            m7C4 = 0;
            executeSetMode(3);
            return;
        }
        mTimer--;
        fopAc_ac_c* actor = fopAcM_searchFromName("figureE", 0xFF, m790);
        if (actor != NULL && *((u8*)actor + 0x73E) != 0) {
            mLookAtX = actor->eyePos.x;
            mLookAtY = actor->eyePos.y;
            mLookAtZ = actor->eyePos.z;
            mLookMode = 1;
            m794 = 0;
            m_jnt.setTrn();
        }
    } else if (mPathRun.isPath()) {
        if (mTimer != 0 && mAttnFlag == 0 && m7C0 == 0) {
            mTimer--;
            if (mTimer == 0) {
                m7C4 = 0;
                executeSetMode(3);
            }
        }
    }
}

/* 000017CC-000017D4       .text executeTalkInit__9daNpcMn_cFv */
s32 daNpcMn_c::executeTalkInit() {
    return TRUE;
}

/* 000017D4-0000184C       .text executeTalk__9daNpcMn_cFv */
void daNpcMn_c::executeTalk() {
    executeCommon();
    if (talk2(1) == fopMsgStts_BOX_CLOSED_e) {
        mMode = 0;
        executeSetMode(0);
        dComIfGp_event_reset();
    } else {
        setAnmFromMsgTag();
    }
}

/* 0000184C-0000185C       .text executeTalk3Init__9daNpcMn_cFv */
s32 daNpcMn_c::executeTalk3Init() {
    m7C3 = 0;
    return 4;
}

/* 0000185C-0000191C       .text executeTalk3__9daNpcMn_cFv */
void daNpcMn_c::executeTalk3() {
    if (m7C3 < 2) {
        if (m7C3 < 0) {
            return;
        }
        if (eventInfo.checkCommandDemoAccrpt()) {
            m7C3 = 2;
            return;
        }
        fopAcM_orderPotentialEvent(this, 0xA, 0, 0);
        m7BE |= 2;
        m7C3 = 1;
    } else if (talk3(1) == fopMsgStts_BOX_CLOSED_e) {
        m7C3 = 0;
        executeSetMode(0);
        dComIfGp_event_reset();
    }
}

/* 0000191C-00001948       .text executeWalkInit__9daNpcMn_cFv */
s32 daNpcMn_c::executeWalkInit() {
    setAnmTbl(l_npc_anm_walk);
    return 2;
}

/* 00001948-00001BD4       .text executeWalk__9daNpcMn_cFv */
void daNpcMn_c::executeWalk() {
    executeCommon();
    if (mMode != 0) {
        return;
    }
    u8 turnFlag = 0;
    cXyz myPos = current.pos;
    if (mPathRun.chkPointPass(myPos, mPathRun.getDir() != 0)) {
        m790 = mPathRun.pointArg(mPathRun.getIdx());
        if (m790 != 0xFF) {
            fopAc_ac_c* actor = fopAcM_searchFromName("figureE", 0xFF, m790);
            if (actor != NULL && *((u8*)actor + 0x73E) != 0) {
                m7C5 = getRand(5);
                m7C4 = 1;
                executeSetMode(0);
            }
        }
        if (!mPathRun.nextIdxAuto()) {
            turnFlag = 1;
        }
    }
    if (mAttnFlag || m7C0) {
        m7C4 = 0;
        executeSetMode(0);
        return;
    }
    if (turnFlag == 0) {
        if (m7C4 == 0) {
            cXyz point = mPathRun.getPoint(mPathRun.getIdx());
            s16 angle;
            dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
            m7A0 = angle;
            m7AE = angle;
            m794 = 0;
            m7AA = l_npc_dat[mNpcNo].field_0x2C;
            mLookMode = 2;
            m_jnt.setTrn();
            m77C = l_npc_dat[mNpcNo].field_0x38;
        }
    } else {
        mPathRun.turnDir();
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
        m7A0 = angle;
        mPathRun.setInf(0xFF, (s8)current.angle.y, 1);
        executeSetMode(0);
    }
}

/* 00001BD4-00001D18       .text executeTurnInit__9daNpcMn_cFv */
s32 daNpcMn_c::executeTurnInit() {
    cXyz point = mPathRun.getPoint(mPathRun.getIdx());
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
    if (angle == shape_angle.y) {
        setAnmTbl(l_npc_anm_walk);
        mTimer = (s16)((f32)l_npc_dat[mNpcNo].field_0x44 + cM_rndF((f32)(l_npc_dat[mNpcNo].field_0x46 - l_npc_dat[mNpcNo].field_0x44)));
        return 2;
    }
    return 3;
}

/* 00001D18-00001DE8       .text executeTurn__9daNpcMn_cFv */
void daNpcMn_c::executeTurn() {
    if (executeCommon() == 0) {
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
        m7AE = angle;
        m794 = 0;
        mLookMode = 2;
        m_jnt.setTrn();
        if (shape_angle.y == angle) {
            executeSetMode(2);
        }
    }
}

/* 00001DE8-00001E80       .text checkOrder__9daNpcMn_cFv */
void daNpcMn_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdx) && mOrderMode == 3) {
            mOrderMode = 0;
        }
    } else if (eventInfo.checkCommandTalk() && (mOrderMode == 2 || mOrderMode == 1)) {
        mMode = 1;
        executeSetMode(1);
    }
}

/* 00001E80-00001F00       .text eventOrder__9daNpcMn_cFv */
void daNpcMn_c::eventOrder() {
    if (mOrderMode == 2 || mOrderMode == 1) {
        m7BE |= 1;
        if (mOrderMode == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mOrderMode == 3) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mEventIdx, 0, 0xffff);
    }
}

/* 00001F00-00001F74       .text eventMove__9daNpcMn_cFv */
void daNpcMn_c::eventMove() {
    if (!chkEndEvent()) {
        u8 oldFlag = mEventCut.getAttnFlag();
        if (mEventCut.cutProc()) {
            if (mEventCut.getAttnFlag() == 0) {
                mEventCut.setAttnFlag(oldFlag);
            }
        } else {
            privateCut();
            setAnmFromMsgTag();
        }
    }
}

/* 00001F74-00002194       .text privateCut__9daNpcMn_cFv */
void daNpcMn_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET",
        "GET_ITEM",
        "WAIT",
        "HATCH",
        "BIKKURI",
        "TURN",
        "WALK",
        "LOOK",
        "JUMP",
        "SWON",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId(l_npc_staff_id[mNpcNo]);
    if (staffIdx != -1) {
        mCutActIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, 10, TRUE, 0);
        if (mCutActIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
            return;
        }

        if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch (mCutActIdx) {
                case 0:
                    eventMesSetInit(staffIdx);
                    break;
                case 1:
                    eventGetItemInit();
                    break;
                case 2:
                    eventWaitInit(staffIdx);
                    break;
                case 3:
                    eventHatchInit();
                    break;
                case 4:
                    eventBikkuriInit(staffIdx);
                    break;
                case 5:
                    eventTurnInit();
                    break;
                case 6:
                    eventWalkInit();
                    break;
                case 7:
                    eventLookInit();
                    break;
                case 8:
                    eventJumpInit(staffIdx);
                    break;
                case 9:
                    eventSwOnInit(staffIdx);
                    break;
            }
        }

        s32 cutEnd;
        switch (mCutActIdx) {
            case 0:
                cutEnd = eventMesSet();
                break;
            case 2:
                cutEnd = eventWait(staffIdx);
                break;
            case 3:
                cutEnd = eventHatch();
                break;
            case 4:
                cutEnd = eventBikkuri();
                break;
            case 5:
                cutEnd = eventTurn(staffIdx);
                break;
            case 6:
                cutEnd = eventWalk();
                break;
            case 7:
                cutEnd = eventLook();
                break;
            case 8:
                cutEnd = eventJump();
                break;
            case 9:
                cutEnd = eventSwOn();
                break;
            default:
                cutEnd = 1;
                break;
        }

        if (cutEnd) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
}

/* 00002194-0000226C       .text eventMesSetInit__9daNpcMn_cFi */
void daNpcMn_c::eventMesSetInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if (pData) {
        mpMsgTbl = NULL;

        switch (*pData) {
            case 1:
                break;
            case 0:
                setMessage(getMsg());
                break;
            default:
                setMessage(*pData);
        }

        if (mpMsgTbl != NULL) {
            setMessage(*mpMsgTbl);
        }
    } else {
        mpMsgTbl++;
        setMessage(*mpMsgTbl);
    }
}

/* 0000226C-000022A0       .text eventMesSet__9daNpcMn_cFv */
s32 daNpcMn_c::eventMesSet() {
    return talk2(0) == fopMsgStts_BOX_CLOSED_e;
}

/* 000022A0-000022F8       .text eventGetItemInit__9daNpcMn_cFv */
void daNpcMn_c::eventGetItemInit() {
    fpc_ProcID itemID = fopAcM_createItemForPresentDemo(&current.pos, m794, 0, -1, -1);
    if (itemID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemID);
    }
}

/* 000022F8-00002358       .text eventWaitInit__9daNpcMn_cFi */
void daNpcMn_c::eventWaitInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    mEvTimer = 0;
    if (pData) {
        mEvTimer = *pData;
    }
}

/* 00002358-000023E8       .text eventWait__9daNpcMn_cFi */
s32 daNpcMn_c::eventWait(int staffIdx) {
    if (mEvTimer != 0) {
        mEvTimer--;
        return 0;
    }
    if (dComIfGp_evmng_getMyIntegerP(staffIdx, "SwOn") != NULL) {
        dComIfGs_onSwitch(getPrmSwitchBit2(), (s8)home.roomNo);
    }
    return 1;
}

/* 000023E8-00002448       .text eventSwOnInit__9daNpcMn_cFi */
void daNpcMn_c::eventSwOnInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    mEvTimer = 0;
    if (pData) {
        mEvTimer = *pData;
    }
}

/* 00002448-000024AC       .text eventSwOn__9daNpcMn_cFv */
s32 daNpcMn_c::eventSwOn() {
    if (mEvTimer != 0) {
        mEvTimer--;
        return 0;
    }
    dComIfGs_onSwitch(getPrmSwitchBit2(), (s8)home.roomNo);
    return 1;
}

/* 000024AC-00002540       .text eventHatchInit__9daNpcMn_cFv */
void daNpcMn_c::eventHatchInit() {
    fopAc_ac_c* actor = fopAcM_searchFromName("Ohatch", 0, 0);
    if (actor != NULL) {
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, actor->current.pos, NULL, &angle);
        m7A0 = angle;
    }
}

/* 00002540-00002578       .text eventHatch__9daNpcMn_cFv */
s32 daNpcMn_c::eventHatch() {
    m7AE = m7A0;
    m794 = 0;
    mLookMode = 2;
    m_jnt.setTrn();
    return shape_angle.y == m7A0;
}

/* 00002578-000025EC       .text eventBikkuriInit__9daNpcMn_cFi */
void daNpcMn_c::eventBikkuriInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    mEvTimer = 1;
    if (pData) {
        mEvTimer = *pData;
    }
    if (mEvTimer <= 0) {
        mEvTimer = 1;
    }
}

/* 000025EC-00002644       .text eventBikkuri__9daNpcMn_cFv */
s32 daNpcMn_c::eventBikkuri() {
    if (mEvTimer != 0) {
        mEvTimer--;
        if (mEvTimer == 0) {
            setAnmTbl(l_npc_anm_bikkuri);
        }
        return 0;
    }
    return m7B9 & 1;
}

/* 00002644-0000266C       .text eventTurnInit__9daNpcMn_cFv */
void daNpcMn_c::eventTurnInit() {
    setAnmTbl(l_npc_anm_wait);
}

/* 0000266C-000027B4       .text eventTurn__9daNpcMn_cFi */
s32 daNpcMn_c::eventTurn(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "TurnMode");
    s32 mode = 0;
    if (pData) {
        mode = *pData;
    }
    cXyz point;
    if (mode == 1) {
        fopAc_ac_c* actor = fopAcM_searchFromName("Ohatch", 0, 0);
        if (actor != NULL) {
            point = actor->current.pos;
        } else {
            point = mPathRun.getPoint(mPathRun.getIdx());
        }
    } else {
        point = mPathRun.getPoint(mPathRun.getIdx());
    }
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
    m7AE = angle;
    m794 = 0;
    mLookMode = 2;
    m_jnt.setTrn();
    if (shape_angle.y == angle) {
        return 1;
    }
    return 0;
}

/* 000027B4-000027DC       .text eventWalkInit__9daNpcMn_cFv */
void daNpcMn_c::eventWalkInit() {
    setAnmTbl(l_npc_anm_walk);
}

/* 000027DC-0000293C       .text eventWalk__9daNpcMn_cFv */
s32 daNpcMn_c::eventWalk() {
    u8 turnFlag = 0;
    cXyz myPos = current.pos;
    if (mPathRun.chkPointPass(myPos, mPathRun.getDir() != 0) && !mPathRun.nextIdxAuto()) {
        turnFlag = 1;
    }
    if (turnFlag == 0) {
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
        m7A0 = angle;
        m7AE = angle;
        m794 = 0;
        m7AA = l_npc_dat[mNpcNo].field_0x2C;
        mLookMode = 2;
        m_jnt.setTrn();
        m77C = l_npc_dat[mNpcNo].field_0x38;
        return 0;
    }
    m788 = 0.0f;
    m77C = 0.0f;
    return 1;
}

/* 0000293C-00002964       .text eventLookInit__9daNpcMn_cFv */
void daNpcMn_c::eventLookInit() {
    setAnmTbl(l_npc_anm_jump1);
}

/* 00002964-00002988       .text eventLook__9daNpcMn_cFv */
s32 daNpcMn_c::eventLook() {
    return shape_angle.y == m7A0;
}

/* 00002988-00002A90       .text eventJumpInit__9daNpcMn_cFi */
void daNpcMn_c::eventJumpInit(int staffIdx) {
    f32* pSpeedX = dComIfGp_evmng_getMyFloatP(staffIdx, "SpeedX");
    f32* pSpeedY = dComIfGp_evmng_getMyFloatP(staffIdx, "SpeedY");
    f32* pGravity = dComIfGp_evmng_getMyFloatP(staffIdx, "Gravity");
    if (pSpeedX != NULL) {
        m788 = *pSpeedX;
    } else {
        m788 = 3.0f;
    }
    if (pSpeedY != NULL) {
        gravity = *pSpeedY;
    } else {
        gravity = 200.0f;
    }
    if (pGravity != NULL) {
        maxFallSpeed = *pGravity;
    }
    m77C = 40.0f;
    m788 = 25.0f;
    maxFallSpeed = -1.0f;
}

/* 00002A90-00002AE8       .text eventJump__9daNpcMn_cFv */
s32 daNpcMn_c::eventJump() {
    current.pos.y += m788;
    m788 += maxFallSpeed;
    if (m788 < 0.0f && m7C0 & 0x80) {
        m788 = 0.0f;
        m77C = 0.0f;
        return 1;
    }
    return 0;
}

/* 00002AE8-00002C30       .text talk2__9daNpcMn_cFi */
u16 daNpcMn_c::talk2(int i_param) {
    u16 status = 0xFF;
    if (mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        if (i_param == 1) {
            mCurrMsgNo = getMsg();
        }
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
        mMsgStatus = 0xFFFF;
    } else if (mpCurrMsg) {
        status = mpCurrMsg->mStatus;
        switch (status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                if (mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
                break;

            case fopMsgStts_MSG_TYPING_e:
                if (mMsgStatus == fopMsgStts_MSG_CONTINUES_e) {
                    chkMsg();
                }
                break;

            case fopMsgStts_BOX_CLOSED_e:
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                mCurrMsgBsPcId = -1;
                break;
        }
        mMsgStatus = status;
        anmAtr(status);
    } else {
        mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
    }
    return status;
}

/* 00002C30-00002D68       .text talk3__9daNpcMn_cFi */
u8 daNpcMn_c::talk3(int i_param) {
    u8 status = 0xFF;
    if (mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {
        if (i_param == 1) {
            mCurrMsgNo = getMsg3();
        }
        mCurrMsgBsPcId = fopMsgM_scopeMessageSet(mCurrMsgNo);
        mpCurrMsg = NULL;
        mMsgStatus = 0xFFFF;
    } else if (mpCurrMsg) {
        status = dComIfGp_getScopeMesgStatus();
        switch (status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                if (mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
                break;

            case fopMsgStts_MSG_TYPING_e:
                if (mMsgStatus == fopMsgStts_MSG_CONTINUES_e) {
                    chkMsg();
                }
                break;

            case fopMsgStts_BOX_CLOSED_e:
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                mCurrMsgBsPcId = -1;
                break;
        }
        mMsgStatus = status;
        anmAtr(status);
    } else {
        mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
    }
    return status;
}

/* 00002D68-00002DB8       .text next_msgStatus__9daNpcMn_cFPUl */
u16 daNpcMn_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    if (mpMsgTbl) {
        mpMsgTbl++;
        switch (*mpMsgTbl) {
            case 2:
                dPb_erasePicture();
            case 0:
                mpMsgTbl = NULL;
                status = fopMsgStts_MSG_ENDS_e;
                break;
            case 1:
                *pMsgNo = l_msg_mn_figure[dSnap_GetFigRoomId(dComIfGs_getEventReg(dSv_event_flag_c::UNK_A9FF))];
                break;
            default:
                *pMsgNo = *mpMsgTbl;
                break;
        }
    } else {
        status = fopMsgStts_MSG_ENDS_e;
    }
    return status;
}

/* 00002DB8-00002F7C       .text getMsg__9daNpcMn_cFv */
u32 daNpcMn_c::getMsg() {
    u32 msgNo = 0;
    mpMsgTbl = NULL;

    if (dComIfGp_event_chkTalkXY()) {
        return 0;
    }

    if (mPosNo == 0) {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F08)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F08);
            mpMsgTbl = l_msg_mn_1st_talk;
        } else {
            mpMsgTbl = l_msg_mn_2nd_talk;
        }
    } else if (mPosNo == 1 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D08)) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F04);
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3120)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3120);
            mpMsgTbl = l_msg_mn_comp_1st;
        } else {
            mpMsgTbl = l_msg_mn_comp_2nd;
        }
    } else {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2F04)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2F04);
            mpMsgTbl = l_msg_mn_1st_talk_in;
        } else if (m7C4 != 0) {
            msgNo = l_msg_mn_figure[m7C5];
        } else if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A01)) {
            mpMsgTbl = l_msg_mn_2nd_talk_in;
        } else {
            mpMsgTbl = l_msg_mn_3rd_talk_in;
        }
    }

    if (mpMsgTbl != NULL) {
        msgNo = *mpMsgTbl;
    }
    return msgNo;
}

/* 00002F7C-00002F8C       .text getMsg3__9daNpcMn_cFv */
u32 daNpcMn_c::getMsg3() {
    mpMsgTbl = NULL;
    return 0x35EF;
}

/* 00002F8C-00002F90       .text chkMsg__9daNpcMn_cFv */
void daNpcMn_c::chkMsg() {
    return;
}

/* 00002F90-00002F98       .text setMessage__9daNpcMn_cFUl */
void daNpcMn_c::setMessage(u32 msgNo) {
    mCurrMsgNo = msgNo;
}

/* 00002F98-0000302C       .text setAnmFromMsgTag__9daNpcMn_cFv */
void daNpcMn_c::setAnmFromMsgTag() {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnmTbl(l_npc_anm_wait);
            break;
        case 1:
            setAnmTbl(l_npc_anm_talk);
            break;
        case 2:
            setAnmTbl(l_npc_anm_talk2);
            break;
        case 3:
            setAnmTbl(l_npc_anm_wait2);
            break;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xff);
}

/* 0000302C-0000303C       .text getPrmNpcNo__9daNpcMn_cFv */
s8 daNpcMn_c::getPrmNpcNo() {
    return mPosNo != 0;
}

/* 0000303C-00003068       .text getPrmRailID__9daNpcMn_cFv */
u8 daNpcMn_c::getPrmRailID() {
    return daObj::PrmAbstract<daNpcMn_c::Prm_e>(this, PRM_RAIL_ID_W, PRM_RAIL_ID_S);
}

/* 00003068-00003094       .text getPrmSwitchBit__9daNpcMn_cFv */
u8 daNpcMn_c::getPrmSwitchBit() {
    return daObj::PrmAbstract<daNpcMn_c::Prm_e>(this, PRM_SW_BIT_W, PRM_SW_BIT_S);
}

/* 00003094-000030C0       .text getPrmSwitchBit2__9daNpcMn_cFv */
u8 daNpcMn_c::getPrmSwitchBit2() {
    return daObj::PrmAbstract<daNpcMn_c::Prm_e>(this, PRM_SW_BIT2_W, PRM_SW_BIT2_S);
}

/* 000030C0-00003148       .text setMtx__9daNpcMn_cFv */
void daNpcMn_c::setMtx() {
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00003148-00003478       .text chkAttention__9daNpcMn_cFv */
void daNpcMn_c::chkAttention() {
    m7C0 = 0;
    if (mEventCut.getAttnFlag()) {
        mLookAtX = mEventCut.getAttnPos().x;
        mLookAtY = mEventCut.getAttnPos().y;
        mLookAtZ = mEventCut.getAttnPos().z;
        mLookMode = 1;
        if (m794 != 0) {
            m794 = 0;
            m_jnt.setTrn();
        } else {
            m794 = 1;
        }
        if (mAttnFlag == 0) {
            mAttnFlag = 1;
        }
    } else {
        f32 attnDist = mAttnDist;
        s16 turnSpeed = mTurnSpeed;
        cXyz myPos = current.pos;
        fopAc_ac_c* player = dComIfGp_getLinkPlayer();
        f32 distXZ;
        s16 angle;
        dNpc_calc_DisXZ_AngY(myPos, player->current.pos, &distXZ, &angle);
        if (mAttnFlag) {
            attnDist += 40.0f;
            turnSpeed += 0x71C;
        }
        s16 diffAngle = angle - shape_angle.y;
        if (attnDist > distXZ && turnSpeed > abs(diffAngle)) {
            cXyz eyePos = dNpc_playerEyePos(l_npc_dat[mNpcNo].field_0x14);
            mLookAtX = eyePos.x;
            mLookAtY = eyePos.y;
            mLookAtZ = eyePos.z;
            mLookMode = 1;
            if (m794 != 0) {
                m794 = 0;
            } else {
                m794 = 1;
            }
            if (m7BF == 0) {
                m7AE = m7A0;
                m794 = 0;
                mLookMode = 2;
                m_jnt.setTrn();
            }
            if (mAttnFlag == 0) {
                mAttnFlag = 1;
            }
        } else {
            if (mAttnFlag == 1) {
                mAttnFlag = 0;
                mLookTimer = l_npc_dat[mNpcNo].field_0x48;
            }
            if (l_npc_dat[mNpcNo].field_0x24 > distXZ) {
                cXyz eyePos = dNpc_playerEyePos(l_npc_dat[mNpcNo].field_0x14);
                mLookAtX = eyePos.x;
                mLookAtY = eyePos.y;
                mLookAtZ = eyePos.z;
                mLookMode = 1;
                if (m794 != 0) {
                    m794 = 0;
                } else {
                    m794 = 1;
                }
                if (m7BF == 0) {
                    m7AE = m7A0;
                    m794 = 0;
                    mLookMode = 2;
                    m_jnt.setTrn();
                }
                m7C0 = 1;
            } else {
                mLookMode = 0;
                if (!mPathRun.isPath()) {
                    if (mLookTimer != 0) {
                        mLookTimer--;
                    } else {
                        m7AE = m7A0;
                        m794 = 0;
                        mLookMode = 2;
                        m_jnt.setTrn();
                    }
                }
            }
        }
    }
    m7AA = l_npc_dat[mNpcNo].field_0x2A;
}

/* 00003478-000035C4       .text lookBack__9daNpcMn_cFv */
void daNpcMn_c::lookBack() {
    s16 angAccel = m7AA;
    s16 angle = shape_angle.y;
    cXyz lookAtPos;
    cXyz* pTarget = NULL;
    cXyz eyePos = this->eyePos;
    u8 attnFlag = m794;
    u8 lookMode = mLookMode;
    switch (lookMode) {
        case 1:
            lookAtPos.set(mLookAtX, mLookAtY, mLookAtZ);
            pTarget = &lookAtPos;
            break;
        case 2:
            angle = m7AE;
            break;
    }
    if (mMode && m794) {
        attnFlag = 0;
        m_jnt.setTrn();
    }
    if (m_jnt.trnChk()) {
        if (mEventCut.getTurnSpeed() != 0) {
            angAccel = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&mAngAccel, angAccel, 4, 0x800);
    } else {
        mAngAccel = 0;
    }
    m_jnt.lookAtTarget(&shape_angle.y, pTarget, eyePos, angle, mAngAccel, attnFlag);
    shape_angle = current.angle;
}

/* 000035C4-000036D0       .text initTexPatternAnm__9daNpcMn_cFb */
BOOL daNpcMn_c::initTexPatternAnm(bool param_1) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_btp_ix_tbl[0]);
    if (m_head_tex_pattern == NULL) {
        JUT_ASSERT(0xA19, m_head_tex_pattern != NULL);
        OSPanic("d_a_npc_mn.cpp", 0xA19, "m_head_tex_pattern != 0");
    }
    if (!mBtpAnm.init(modelData, m_head_tex_pattern, 1, 2, 1.0f, 0, -1, param_1, 0)) {
        return FALSE;
    }
    mTexPatternNo = 0;
    mTexTimer = 0;
    return TRUE;
}

/* 000036D0-0000373C       .text playTexPatternAnm__9daNpcMn_cFv */
void daNpcMn_c::playTexPatternAnm() {
    if (cLib_calcTimer<s16>(&mTexTimer) == 0) {
        s16 frameMax = m_head_tex_pattern->getFrameMax();
        if (mTexPatternNo >= frameMax) {
            mTexPatternNo = mTexPatternNo - frameMax;
            mTexTimer = 0x78;
            return;
        }
        mTexPatternNo = mTexPatternNo + 1;
    }
}

/* 0000373C-000037F8       .text playAnm__9daNpcMn_cFv */
void daNpcMn_c::playAnm() {
    if (mpMorf->play(NULL, 0, 0) && mpAnmDat != NULL && mAnmCnt > 0) {
        mAnmCnt--;
        if (mAnmCnt == 0) {
            mpAnmDat = (sMnAnmDat*)&mpAnmDat->mBtpNum + 1;
            if (setAnmTbl(mpAnmDat)) {
                m7B9 |= 1;
            }
        } else {
            setAnm(mpAnmDat->mAnmNum, 0, 0.0f);
        }
    }
}

/* 000037F8-000038C8       .text setAnm__9daNpcMn_cFUcif */
void daNpcMn_c::setAnm(u8 anmNum, int loopMode, f32 morf) {
    f32 morfLocal = morf;
    if (m780 <= 0.0f) {
        morfLocal = m780;
        m780 = -1.0f;
    }
    mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[anmNum]),
        loopMode, morfLocal, 1.0f, 0.0f, -1.0f, NULL
    );
    mAnmNo = anmNum;
}

/* 000038C8-00003974       .text setAnmTbl__9daNpcMn_cFP9sMnAnmDat */
s32 daNpcMn_c::setAnmTbl(sMnAnmDat* pAnmDat) {
    m7B9 &= 0xFE;
    if (pAnmDat->mAnmNum == 0xFF) {
        mpAnmDat = NULL;
        return 1;
    }
    mpAnmDat = pAnmDat;
    mAnmCnt = mpAnmDat->mAnmCnt;
    int loopMode = 2;
    if (mAnmCnt > 0) {
        loopMode = 0;
    }
    if (mAnmNo != pAnmDat->mAnmNum || loopMode == 0) {
        setAnm(pAnmDat->mAnmNum, loopMode, (f32)pAnmDat->mBtpNum);
    }
    return 0;
}

/* 00003974-0000397C       .text XyCheckCB__9daNpcMn_cFi */
s32 daNpcMn_c::XyCheckCB(int) {
    return 0;
}

/* 0000397C-000039E0       .text getRand__9daNpcMn_cFi */
u8 daNpcMn_c::getRand(int i_max) {
    int rand = cM_rndF(i_max);
    if (rand == i_max) {
        return 0;
    }
    return rand;
}

/* 000039E0-00003A58       .text setCollision__9daNpcMn_cFP8dCcD_Cyl4cXyzff */
void daNpcMn_c::setCollision(dCcD_Cyl* pCyl, cXyz pos, f32 radius, f32 height) {
    pCyl->SetC(pos);
    pCyl->SetR(radius);
    pCyl->SetH(height);
    dComIfG_Ccsp()->Set(pCyl);
}

/* 00003A58-00003AC4       .text chkEndEvent__9daNpcMn_cFv */
s32 daNpcMn_c::chkEndEvent() {
    if (dComIfGp_evmng_endCheck(mEventIdx)) {
        dComIfGp_event_reset();
        fopAcM_delete(this);
        return 1;
    }
    return 0;
}

/* 00003AC4-00003B38       .text chkPosNo__9daNpcMn_cFv */
u8 daNpcMn_c::chkPosNo() {
    u8 ret = 0;
    while (ret < 0xA) {
        if (strcmp(dComIfGp_getNextStageName(), l_room_name[ret]) != 0) {
            ret++;
            continue;
        }
        break;
    }
    return ret;
}

/* 00003B38-00003CD8       .text getPosNo__9daNpcMn_cFv */
u8 daNpcMn_c::getPosNo() {
    dSv_event_c* pEvent = dComIfGs_getPEvent();
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D08) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3120)) {
        return 1;
    }
    u8 count[8] = {1, 0, 0, 0, 0, 0, 0, 0};
    for (u16 i = 0; i < 0x86; i++) {
        u8 idx = i / 8;
        if (idx < 0x11) {
            if (dComIfGs_getEventReg(l_figure_comp[i]) & (1 << (i & 7))) {
                s8 roomId = dSnap_GetFigRoomId(i);
                if (roomId != 0xFF && roomId < 8) {
                    count[roomId]++;
                }
            }
        }
    }
    u8 num = 0;
    for (int i = 0; i < 8; i++) {
        if (count[i] != 0) {
            num++;
        }
    }
    u8 rand = getRand(num);
    for (int i = 0; i < 8; i++) {
        if (count[i] != 0) {
            if (rand != 0) {
                rand--;
                continue;
            }
            return i + 1;
        }
    }
    return 1;
}

/* 00003CD8-00003CE8       .text isChangePos__9daNpcMn_cFUc */
BOOL daNpcMn_c::isChangePos(u8 param_1) {
    return param_1 == 0;
}

/* 00003CE8-00003D08       .text daNpc_MnCreate__FPv */
static cPhs_State daNpc_MnCreate(void* i_this) {
    return ((daNpcMn_c*)i_this)->_create();
}

/* 00003D08-00003D2C       .text daNpc_MnDelete__FPv */
static BOOL daNpc_MnDelete(void* i_this) {
    return ((daNpcMn_c*)i_this)->_delete();
}

/* 00003D2C-00003D50       .text daNpc_MnExecute__FPv */
static BOOL daNpc_MnExecute(void* i_this) {
    return ((daNpcMn_c*)i_this)->_execute();
}

/* 00003D50-00003D74       .text daNpc_MnDraw__FPv */
static BOOL daNpc_MnDraw(void* i_this) {
    return ((daNpcMn_c*)i_this)->_draw();
}

/* 00003D74-00003D7C       .text daNpc_MnIsDelete__FPv */
static BOOL daNpc_MnIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_MnMethodTable = {
    (process_method_func)daNpc_MnCreate,
    (process_method_func)daNpc_MnDelete,
    (process_method_func)daNpc_MnExecute,
    (process_method_func)daNpc_MnIsDelete,
    (process_method_func)daNpc_MnDraw,
};

actor_process_profile_definition g_profile_NPC_MN = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_MN_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcMn_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_MN_e,
    /* Actor SubMtd */ &daNpc_MnMethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
