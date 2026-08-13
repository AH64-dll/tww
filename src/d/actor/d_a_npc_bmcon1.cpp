/**
 * d_a_npc_bmcon1.cpp
 * NPC - Willi & Obli (Flight Control Platform)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bmcon1.h"
#include "d/d_a_obj.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_lib_game.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "res/Object/Bmcon1.h"

const char daNpcBmcon_c::m_arcname[] = "Bmcon1";

static char* l_npc_staff_id[] = {
    "Bmcon1",
    "Bmcon2",
};

static const char* l_arcname_tbl[] = {
    "Bmcon1",
    "Bmcon1",
};

static const int l_bmd_ix_tbl[] = {
    dRes_ID_BMCON1_BDL_BM_e,
    dRes_ID_BMCON1_BDL_BM_e,
};

static const int l_head_bmd_ix_tbl[] = {
    dRes_ID_BMCON1_BDL_BMHEAD10_e,
    dRes_ID_BMCON1_BDL_BMHEAD08_e,
};

static const int l_arm_bmd_ix_tbl[] = {
    dRes_ID_BMCON1_BDL_BMARM_e,
    dRes_ID_BMCON1_BDL_BMARM_e,
};

static const int l_bck_ix_tbl[] = {
    dRes_ID_BMCON1_BCK_BM_WAIT01_e,
    dRes_ID_BMCON1_BCK_BM_WAIT02_e,
    dRes_ID_BMCON1_BCK_BM_TALK01_e,
    dRes_ID_BMCON1_BCK_BM_TALK02_e,
    dRes_ID_BMCON1_BCK_BM_TALK03_e,
    dRes_ID_BMCON1_BCK_BM_WALK_e,
    dRes_ID_BMCON1_BCK_BM_TRICON01_e,
    dRes_ID_BMCON1_BCK_BM_TRICON02_e,
};

static const int l_arm_bck_ix_tbl[] = {
    dRes_ID_BMCON1_BCK_BMARM_WAIT01_e,
    dRes_ID_BMCON1_BCK_BMARM_WAIT02_e,
    dRes_ID_BMCON1_BCK_BMARM_TALK01_e,
    dRes_ID_BMCON1_BCK_BMARM_TALK02_e,
    dRes_ID_BMCON1_BCK_BMARM_TALK03_e,
    dRes_ID_BMCON1_BCK_BMARM_WALK_e,
    dRes_ID_BMCON1_BCK_BMARM_TRICON01_e,
    dRes_ID_BMCON1_BCK_BMARM_TRICON02_e,
};

static const int l_btp_ix_tbl[] = {
    0x00,
};

static cXyz l_bmcon_pos_tbl[2] = {
    cXyz(297080.0f, 1100.0f, -202920.0f),
    cXyz(278900.0f, 1100.0f, -221100.0f),
};

static sBmconAnmDat l_npc_anm_wait[] = {
    {
        0x00,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat l_npc_anm_wait2[] = {
    {
        0x01,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat l_npc_anm_talk[] = {
    {
        0x02,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat l_npc_anm_talk2[] = {
    {
        0x03,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat l_npc_anm_talk3[] = {
    {
        0x04,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat l_npc_anm_walk[] = {
    {
        0x05,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat l_npc_anm_con1[] = {
    {
        0x06,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat l_npc_anm_con2[] = {
    {
        0x07,
        0x08,
        0xFF,
    },
};

static sBmconAnmDat* l_npc_anm_tbl[] = {
    l_npc_anm_wait,
    l_npc_anm_wait2,
    l_npc_anm_talk,
    l_npc_anm_talk2,
    l_npc_anm_talk3,
    l_npc_anm_walk,
    l_npc_anm_con1,
    l_npc_anm_con2,
};

static NpcDatStruct l_npc_dat[] = {
    {
        0x2000,
        0x1B58,
        0,
        0x1E78,
        0xF000,
        0xE4A8,
        0,
        0xE188,
        0x05DC,
        0,
        0.0f,
        220.0f,
        190.0f,
        200.0f,
        0.0f,
        0x4E20,
        0x0514,
        0x0190,
        0,
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
        0x00,
        0x01,
    },

    {
        0x2000,
        0x1B58,
        0,
        0x1E78,
        0xF000,
        0xE4A8,
        0,
        0xE188,
        0x05DC,
        0,
        25.0f,
        220.0f,
        190.0f,
        220.0f,
        0.0f,
        0x7FFF,
        0x0514,
        0x0190,
        0,
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
        0x00,
        0x01,
    },
};

static u32 l_msg_bmcon1_1st_appear[] = {
    0x2A96,
    0x2A97,
    0x2A98,
    0x2A99,
    0x0001,
};

static u32 l_msg_bmcon1_appear[] = {
    0x2A9C,
    0x2A9D,
    0x0003,
};

static u32 l_msg_bmcon1_not_appear[] = {
    0x2A9A,
    0x0000,
};

static u32 l_msg_bmcon1_not_rupee[] = {
    0x2A9B,
    0x0000,
};

static u32 l_msg_bmcon1_2nd[] = {
    0x2AAD,
    0x2A9E,
    0x0002,
};

static u32 l_msg_bmcon1_cleared[] = {
    0x2AAE,
    0x0002,
};

static u32 l_msg_bmcon1_appear2[] = {
    0x2A9F,
    0x0003,
};

static u32 l_msg_bmcon1_not_appear2[] = {
    0x2AA0,
    0x0000,
};

static u32 l_msg_bmcon1_talk[] = {
    0x2A95,
    0x0000,
};

static u32 l_msg_bmcon1_result[] = {
    0x2AA1,
    0x2AA2,
    0x2AA3,
    0x2AA4,
    0x2AA5,
};

static u32 l_msg_bmcon1_1st_goal[] = {
    0x2AA7,
    0x2AA8,
    0x2AA9,
    0x0004,
    0x2AAA,
    0x0000,
};

static u32 l_msg_bmcon1_goal[] = {
    0x2AAB,
    0x2AAC,
    0x0005,
    0x2AAA,
    0x0000,
};

static u32 l_msg_bmcon2_2st_talk[] = {
    0x2AF9,
    0x0000,
};

static u32 l_msg_bmcon2_cleared[] = {
    0x2AFE,
    0x0000,
};

static u32 l_msg_bmcon2_appear[] = {
    0x2AFD,
    0x2AFB,
    0x2AFC,
    0x0000,
};

static u32 l_msg_bmcon2_talk[] = {
    0x2AFA,
    0x0000,
};

/* 000000EC-000002A4       .text __ct__12daNpcBmcon_cFv */
daNpcBmcon_c::daNpcBmcon_c() {
    mNpcNo = getPrmNpcNo();
    mResFlag = 0;
    mMode = 0;
    m780 = 0.0f;
    m796 = 0;
    m784 = -1.0f;
    m7BE = 0;
    m790 = 1;
    m79C = home.angle.y;
    mBckNo = 1;
    m7A0 = 0;
    mFlyState = 1;
    m7C3 = 0;
}

/* 00000690-000007F0       .text daNpc_Bmcon_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Bmcon_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpcBmcon_c* i_this = (daNpcBmcon_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();

        MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

        if(jntNo == i_this->get_nec_jnt_num()) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getHead_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getHead_x());
        }

        if(jntNo == i_this->m_jnt.mBackboneJntNum) {
            cMtx_XrotM(*calc_mtx, (s16)i_this->m_jnt.getBackbone_y());
            cMtx_ZrotM(*calc_mtx, (s16)-i_this->m_jnt.getBackbone_x());
        }

        if(jntNo == i_this->get_arm_L_jnt_num()) {
            MTXCopy(*calc_mtx, i_this->mLeftArmMtx);
        }

        if(jntNo == i_this->get_arm_R_jnt_num()) {
            MTXCopy(*calc_mtx, i_this->mRightArmMtx);
        }

        model->setAnmMtx(jntNo, *calc_mtx);
        MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 000007F0-00000834       .text daNpc_Arm_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Arm_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpcBmcon_c* i_this = (daNpcBmcon_c*)model->getUserArea();
        i_this->nodeArmControl(node, model);
    }
    return TRUE;
}

/* 00000834-000008E4       .text nodeArmControl__12daNpcBmcon_cFP7J3DNodeP8J3DModel */
void daNpcBmcon_c::nodeArmControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = (J3DJoint*)node;
    s32 jntNo = joint->getJntNo();

    MTXCopy(model->getAnmMtx(jntNo), mDoMtx_stack_c::now);

    if(jntNo == m_armL1_jnt_num) {
        MTXCopy(mLeftArmMtx, J3DSys::mCurrentMtx);
        MTXCopy(mLeftArmMtx, model->getAnmMtx(jntNo));
    }

    if(jntNo == m_armR1_jnt_num) {
        MTXCopy(mRightArmMtx, J3DSys::mCurrentMtx);
        MTXCopy(mRightArmMtx, model->getAnmMtx(jntNo));
    }
}

/* 000008E4-00000904       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpcBmcon_c*>(i_this)->createHeap();
}

/* 00000904-00000994       .text phase_1__FP12daNpcBmcon_c */
static cPhs_State phase_1(daNpcBmcon_c* i_this) {
    /* Nonmatching */
    fopAcM_ct(i_this, daNpcBmcon_c);

    fopAc_ac_c* player = dComIfGp_getLinkPlayer();
    if (player == NULL || fpcM_IsCreating(fopAcM_GetID(player))) {
        return cPhs_ERROR_e;
    }

    i_this->setResFlag(1);
    return cPhs_NEXT_e;
}

/* 00000994-00000A14       .text phase_2__FP12daNpcBmcon_c */
static cPhs_State phase_2(daNpcBmcon_c* i_this) {
    cPhs_State phase_state = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[i_this->getNpcNo()]);
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0)) {
            return i_this->createInit();
        } else {
#if VERSION > VERSION_DEMO
            i_this->mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 00000A14-00000A44       .text _create__12daNpcBmcon_cFv */
cPhs_State daNpcBmcon_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)phase_1,
        (cPhs__Handler)phase_2,
        NULL,
    };
    return dComLbG_PhaseHandler(&mPhase, l_method, this);
}

/* 00000A44-0000105C       .text createHeap__12daNpcBmcon_cFv */
BOOL daNpcBmcon_c::createHeap() {
    J3DModelData* modelData = (J3DModelData *)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bmd_ix_tbl[mNpcNo]);
    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[mBckNo]),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11000002
    );

    J3DModelData* armModelData = (J3DModelData *)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_arm_bmd_ix_tbl[mNpcNo]);
    mpArmMorf = new mDoExt_McaMorf(
        armModelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_arm_bck_ix_tbl[mBckNo]),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11000002
    );

    if (mpArmMorf == NULL || mpArmMorf->getModel() == NULL) {
        return FALSE;
    }

    mpHeadModel = mDoExt_J3DModel__create(
        (J3DModelData*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_head_bmd_ix_tbl[mNpcNo]),
        0x8000000, 0x37441422
    );

    if (mpHeadModel == NULL) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(DEMO_SELECT(1006, 1007), m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(1010, 1011), m_jnt.getBackboneJntNum() >= 0);
    m_nec_jnt_num = modelData->getJointName()->getIndex("neck");
    JUT_ASSERT(DEMO_SELECT(1017, 1018), m_nec_jnt_num >= 0);
    m_arm_L_jnt_num = modelData->getJointName()->getIndex("armL");
    JUT_ASSERT(DEMO_SELECT(1021, 1022), m_arm_L_jnt_num >= 0);
    m_arm_R_jnt_num = modelData->getJointName()->getIndex("armR");
    JUT_ASSERT(DEMO_SELECT(1023, 1024), m_arm_R_jnt_num >= 0);

    m_armL1_jnt_num = armModelData->getJointName()->getIndex("armLloc");
    JUT_ASSERT(DEMO_SELECT(1027, 1028), m_armL1_jnt_num >= 0);
    m_armR1_jnt_num = armModelData->getJointName()->getIndex("armRloc");
    JUT_ASSERT(DEMO_SELECT(1029, 1030), m_armR1_jnt_num >= 0);

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum() ||
           i == m_nec_jnt_num || i == m_arm_L_jnt_num || i == m_arm_R_jnt_num)
        {
            modelData->getJointNodePointer(i)->setCallBack(daNpc_Bmcon_nodeCallBack);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);

    for(u16 i = 0; i < armModelData->getJointNum(); i++) {
        if(i == m_armL1_jnt_num || i == m_armR1_jnt_num) {
            armModelData->getJointNodePointer(i)->setCallBack(daNpc_Arm_nodeCallBack);
        }
    }

    mpArmMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    return TRUE;
}

/* 0000105C-0000107C       .text daNpcBmcon_XyCheckCB__FPvi */
static s16 daNpcBmcon_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daNpcBmcon_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 0000107C-00001468       .text createInit__12daNpcBmcon_cFv */
cPhs_State daNpcBmcon_c::createInit() {
    int railID = 0xFF;
    u8 prmRailID = getPrmRailID();
    if (prmRailID != 0xFF) {
        mPathRun.setInf(prmRailID, current.roomNo, 1);
        if (!mPathRun.isPath()) {
            return cPhs_ERROR_e;
        }
        dPath_GetNextRoomPath(mPathRun.getPath(), -1);
        actor_status &= ~0x80;
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        old.pos = point;
        current.pos = old.pos;
        mPathRun.incIdxLoop();
        m796 = 1;
        railID = 0xFE;
    }

    gravity = -9.0f;
    setAnmTbl(l_npc_anm_tbl[mBckNo]);

    switch (getNpcNo()) {
    case 0:
        mEventIdx1 = dComIfGp_evmng_getEventIdx("BMCON_RESULT", 0xff);
        mEventIdx2 = dComIfGp_evmng_getEventIdx("BMCON_GET_ITEM", 0xff);
        if (dComIfGs_isTmpBit(dSv_event_tmp_flag_c::UNK_0210)) {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0210);
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
            fopAcM_orderChangeEventId(player, this, mEventIdx1, 0, 0xffff);
            player->onWaterDrop();
        }
        break;
    case 1:
        mEventIdx1 = dComIfGp_evmng_getEventIdx("BMCON_END", 0xff);
        mEventIdx2 = dComIfGp_evmng_getEventIdx("BMCON_END2", 0xff);
        break;
    }

    eventInfo.mpCheckCB = daNpcBmcon_XyCheckCB;
    mEventCut.setActorInfo2(l_npc_staff_id[getNpcNo()], this);
    m7A8 = 0;
    m7AC = 0;
    m7AD = 0;
    m7C1 = 0;
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -70.0f, 0.0f, -70.0f, 70.0f, 200.0f, 70.0f);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    m_jnt.setParam(
        l_npc_dat[getNpcNo()].mMax_backbone_x,
        l_npc_dat[getNpcNo()].mMax_backbone_y,
        l_npc_dat[getNpcNo()].mMin_backbone_x,
        l_npc_dat[getNpcNo()].mMin_backbone_y,
        l_npc_dat[getNpcNo()].mMax_head_x,
        l_npc_dat[getNpcNo()].mMax_head_y,
        l_npc_dat[getNpcNo()].mMin_head_x,
        l_npc_dat[getNpcNo()].mMin_head_y,
        l_npc_dat[getNpcNo()].mMax_turn_step
    );
    m7BF = l_npc_dat[getNpcNo()].field_0x4A;
    m7C0 = l_npc_dat[getNpcNo()].field_0x4B;
    mAttnDist = l_npc_dat[getNpcNo()].field_0x20;
    mAttnAngle = l_npc_dat[getNpcNo()].field_0x28;
    mObjAcch.CrrPos(*dComIfG_Bgsp());

    if (mObjAcch.GetGroundH() != -G_CM3D_F_INF) {
        f32 groundH = mObjAcch.GetGroundH();
        home.pos.y = groundH;
        current.pos.y = groundH;
    }

    setMtx();
    mpMorf->getModel()->calc();
    mStts.Init(railID, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat[getNpcNo()].field_0x30, 150.0f);
    return cPhs_COMPLEATE_e;
}

/* 00001468-000014D8       .text _delete__12daNpcBmcon_cFv */
bool daNpcBmcon_c::_delete() {
    if (mResFlag) {
        dComIfG_resDelete(&mPhs, l_arcname_tbl[mNpcNo]);
    }
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return true;
}

/* 000014D8-00001694       .text _draw__12daNpcBmcon_cFv */
bool daNpcBmcon_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModel* armModel = mpArmMorf->getModel();
    J3DModel* headModel = mpHeadModel;
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    g_env_light.setLightTevColorType(armModel, &tevStr);
    g_env_light.setLightTevColorType(headModel, &tevStr);
    mpMorf->updateDL();
    mpArmMorf->updateDL();

    MTXCopy(model->getAnmMtx(m_jnt.getHeadJntNum()), headModel->getBaseTRMtx());
    mDoExt_modelUpdateDL(mpHeadModel);

    cXyz shadowPos(
        current.pos.x,
        current.pos.y + 150.0f,
        current.pos.z
    );

    mShadowID = dComIfGd_setShadow(
        mShadowID, 1, mpMorf->getModel(), &shadowPos, 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f,
        &dDlst_shadowControl_c::mSimpleTexObj
    );

    if (mShadowID != 0) {
        dComIfGd_addRealShadow(mShadowID, headModel);
        dComIfGd_addRealShadow(mShadowID, armModel);
    }

    switch (getNpcNo()) {
    case 0:
        dSnap_RegistFig(DSNAP_TYPE_UNK95, this, 1.0f, 1.0f, 1.0f);
        break;
    case 1:
        dSnap_RegistFig(DSNAP_TYPE_UNK94, this, 1.0f, 1.0f, 1.0f);
        break;
    }
    return true;
}

static daNpcBmcon_c::InitFunc_t l_execute_init[] = {
    &daNpcBmcon_c::executeWaitInit,
    &daNpcBmcon_c::executeTalkInit,
    &daNpcBmcon_c::executeWalkInit,
    &daNpcBmcon_c::executeTurnInit,
};

static daNpcBmcon_c::MoveFunc_t moveProc[] = {
    &daNpcBmcon_c::executeWait,
    &daNpcBmcon_c::executeTalk,
    &daNpcBmcon_c::executeWalk,
    &daNpcBmcon_c::executeTurn,
};

/* 00001694-00001878       .text _execute__12daNpcBmcon_cFv */
bool daNpcBmcon_c::_execute() {
    chkAttention();
    checkOrder();

    if (!dComIfGp_event_runCheck() || eventInfo.checkCommandTalk()) {
        (this->*moveProc[mMode])();
    } else {
        eventMove();
    }

    eventOrder();
    playAnm();

    if (mBckNo == 5) {
        cLib_chaseF(&speedF, m780, 0.3f);
        f32 playSpeed = speedF * l_npc_dat[mNpcNo].field_0x34;
        if (playSpeed < 0.5f) {
            playSpeed = 0.5f;
        }
        mpMorf->setPlaySpeed(playSpeed);
        mpArmMorf->setPlaySpeed(playSpeed);
    } else {
        cLib_chaseF(&speedF, m780, 0.1f);
    }

    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    setCollision(&mCyl, current.pos, l_npc_dat[mNpcNo].field_0x30, 150.0f);

    attention_info.position.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x18, current.pos.z);
    eyePos.set(current.pos.x, current.pos.y + l_npc_dat[mNpcNo].field_0x1C, current.pos.z);

    lookBack();
    setMtx();
    return false;
}

/* 00001878-00001BC8       .text executeCommon__12daNpcBmcon_cFv */
u8 daNpcBmcon_c::executeCommon() {
    if (m7AD && m7C3 == 0) {
        m7AE = 1;
    } else {
        m7AE = 0;
    }

    if (m7AC == 1 && mMode != 1) {
        executeSetMode(1);
    }

    switch (getNpcNo()) {
    case 0:
        break;
    case 1:
        if (dComIfGp_getStartStageLayer() == 2 || dComIfGp_getStartStageLayer() == 3) {
            cXyz flyDist = calcFlyDist();

            if (!(mSndFlags & 1)) {
                if (flyDist.x > 10.0f) {
                    mSndFlags |= 1;
                    JAIZelBasic::zel_basic->bgmStart(0x80000050, 0, 0);
                    JAIZelBasic::zel_basic->seStart(0x900, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
                }
            }

            if (mFlyState == 1) {
                if (flyDist.x > 25710.0f && flyDist.z < 1131.0f && flyDist.z > -1131.0f) {
                    mFlyState = 0;
                    dComIfGp_setItemMagicCount(-(s16)dComIfGs_getMaxMagic());
                } else if (flyDist.x < -1948.0f || flyDist.x > 25710.0f || flyDist.z < -3534.0f || flyDist.z > 3534.0f) {
                    mFlyState = 2;
                    dComIfGp_setItemMagicCount(-(s16)dComIfGs_getMaxMagic());
                } else {
                    /* stay in flight */
                }
            }

            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
                mFlyDistNow = (s16)(flyDist.x / 100.0f);
                if (mFlyDistNow < 0) {
                    mFlyState = 3;
                }
                dComIfGs_setTmpReg(dSv_event_tmp_flag_c::UNK_F903, mFlyState);

                if (mFlyState == 0 || mFlyState == 1) {
                    m7AE = 3;
                } else {
                    m7AE = 4;
                }

                setFlyDistNow(mFlyDistNow);
                if (mFlyState != 2) {
                    if (mFlyDistNow > getFlyDistMax()) {
                        setFlyDistMax(mFlyDistNow);
                    }
                }

                old.pos = mPathRun.getPoint(mPathRun.getIdx());
                current.pos = old.pos;
                m79C = -0x6000;
                current.angle.y = -0x6000;

                if (!(mSndFlags & 2)) {
                    mSndFlags |= 2;
                    JAIZelBasic::zel_basic->bgmStop(0x5A, 0);
                }
            }
        }
        break;
    }

    return m7AC;
}

/* 00001BC8-00001C1C       .text executeSetMode__12daNpcBmcon_cFUc */
void daNpcBmcon_c::executeSetMode(u8 param_1) {
    m780 = 0.0f;
    mMode = (this->*l_execute_init[param_1])();
}

/* 00001C1C-00001CC8       .text executeWaitInit__12daNpcBmcon_cFv */
s32 daNpcBmcon_c::executeWaitInit() {
    speedF = 0.0f;
    if (mNpcNo != 0) {
        setAnmTbl(l_npc_anm_wait2);
    } else {
        setAnmTbl(l_npc_anm_wait);
    }
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
    return FALSE;
}

/* 00001CC8-00001D38       .text executeWait__12daNpcBmcon_cFv */
void daNpcBmcon_c::executeWait() {
    if (!executeCommon()) {
        if (getNpcNo() == 1 && m7AD != 0 && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A40)) {
            m7AE = 2;
        }
    }
}

/* 00001D38-00001D48       .text executeTalkInit__12daNpcBmcon_cFv */
s32 daNpcBmcon_c::executeTalkInit() {
    m7BF = 1;
    return TRUE;
}

/* 00001D48-00001E40       .text executeTalk__12daNpcBmcon_cFv */
void daNpcBmcon_c::executeTalk() {
    executeCommon();
    if(talk2(1) == fopMsgStts_BOX_CLOSED_e) {
        m7AC = 0;
        executeSetMode(0);
        m7BF = l_npc_dat[mNpcNo].field_0x4A;
        m7C0 = l_npc_dat[mNpcNo].field_0x4B;
        if(m7C2) {
            m7C3 = 1;
            m7AE = 0;
            dComIfGp_setNextStage("sea", 1, 0xE, 2, 0.0f, 0, 1, 0);
        } else {
            g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
        }
    } else {
        setAnmFromMsgTag();
    }
}

/* 00001E40-00001E6C       .text executeWalkInit__12daNpcBmcon_cFv */
s32 daNpcBmcon_c::executeWalkInit() {
    setAnmTbl(l_npc_anm_walk);
    return 2;
}

/* 00001E6C-00002050       .text executeWalk__12daNpcBmcon_cFv */
void daNpcBmcon_c::executeWalk() {
    if (!executeCommon()) {
        bool passed = false;
        if (mPathRun.chkPointPass(current.pos, (bool)mPathRun.getDir())) {
            if (!mPathRun.nextIdxAuto()) {
                passed = true;
            }
        }

        if (!passed) {
            cXyz point = mPathRun.getPoint(mPathRun.getIdx());
            s16 angle;
            dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
            s16 a = angle;
            m79C = a;
            m7AA = a;
            m790 = 0;
            m7A6 = l_npc_dat[getNpcNo()].field_0x2C;
            m7BE = 2;
            m_jnt.setTrn();
            m780 = l_npc_dat[getNpcNo()].field_0x38;
        } else {
            mPathRun.turnDir();
            cXyz point = mPathRun.getPoint(mPathRun.getIdx());
            s16 angle;
            dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
            m79C = angle;
            mPathRun.setInf(0xFF, current.roomNo, 1);
            executeSetMode(0);
        }
    }
}

/* 00002050-00002194       .text executeTurnInit__12daNpcBmcon_cFv */
s32 daNpcBmcon_c::executeTurnInit() {
    cXyz point = mPathRun.getPoint(mPathRun.getIdx());
    s16 angle;
    dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
    if (angle == current.angle.y) {
        setAnmTbl(l_npc_anm_walk);
        m796 = (s16)(l_npc_dat[mNpcNo].field_0x44 + cM_rndF(l_npc_dat[mNpcNo].field_0x46 - l_npc_dat[mNpcNo].field_0x44));
        return 2;
    }
    return 3;
}

/* 00002194-00002264       .text executeTurn__12daNpcBmcon_cFv */
void daNpcBmcon_c::executeTurn() {
    if (!executeCommon()) {
        cXyz point = mPathRun.getPoint(mPathRun.getIdx());
        s16 angle;
        dNpc_calc_DisXZ_AngY(current.pos, point, NULL, &angle);
        m7AA = angle;
        m790 = 0;
        m7BE = 2;
        m_jnt.setTrn();
        if (current.angle.y == angle) {
            executeSetMode(2);
        }
    }
}

/* 00002264-00002360       .text checkOrder__12daNpcBmcon_cFv */
void daNpcBmcon_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_startCheck(mEventIdx1) && m7AE == 3) {
            m7AE = 0;
        }
        else if(dComIfGp_evmng_startCheck(mEventIdx2) && m7AE == 4) {
            m7AE = 0;
        }
        else if(dComIfGp_evmng_startCheck(mEventIdx2) && m7AE == 6) {
            m7AE = 0;
        }
    }
    else if (eventInfo.checkCommandTalk() && (m7AE == 2 || m7AE == 1)) {
        m7AC = 1;
        executeSetMode(1);
    }
}

/* 00002360-00002444       .text eventOrder__12daNpcBmcon_cFv */
void daNpcBmcon_c::eventOrder() {
    if(m7AE == 2 || m7AE == 1) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if(m7AE == 2) {
            fopAcM_orderSpeakEvent(this);
        }
    }
    else if(m7AE == 3) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mEventIdx1, 0, 0xffff);
    }
    else if(m7AE == 4) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mEventIdx2, 0, 0xffff);
    }
    else if(m7AE == 6) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, mEventIdx2, 0, 0xffff);
    }
}

/* 00002444-000024C8       .text eventMove__12daNpcBmcon_cFv */
void daNpcBmcon_c::eventMove() {
    if(!chkEndEvent()) {
        bool oldFlag = mEventCut.getAttnFlag();
        if(mEventCut.cutProc()) {
            if(!mEventCut.getAttnFlag()) {
                mEventCut.setAttnFlag(oldFlag);
            }
        }
        else {
            privateCut();
            setAnmFromMsgTag();
        }
    }
    else {
        executeSetMode(0);
    }
}

/* 000024C8-000025F8       .text privateCut__12daNpcBmcon_cFv */
void daNpcBmcon_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET",
        "GET_ITEM",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId(l_npc_staff_id[mNpcNo]);
    if(staffIdx != -1) {
        mActIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
        if(mActIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
            return;
        }

        if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch(mActIdx) {
                case 0:
                    eventMesSetInit(staffIdx);
                    break;
                case 1:
                    eventGetItemInit();
                    break;
            }
        }

        bool temp;
        switch(mActIdx) {
            case 0:
                temp = eventMesSet();
                break;
            default:
                temp = true;
        }

        if(temp) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
}

/* 000025F8-00002A48       .text eventMesSetInit__12daNpcBmcon_cFi */
void daNpcBmcon_c::eventMesSetInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if (pData) {
        mpMsgTbl = NULL;

        int msg = *pData;
        switch(msg){
            case 0:
                setMessage(getMsg());
                break;
            case 1:
                switch(mFlyState) {
                    case 0:
                        dComIfGp_setMessageCountNumber(mFlyDistNow);
                        setMessage(0x2AB2);
                        dComIfGp_getVibration().StartShock(8, 1, cXyz(0.0f, 1.0f, 0.0f));
                        dComIfGp_getVibration().StartShock(4, 30, cXyz(0.0f, 1.0f, 0.0f));
                        JAIZelBasic::zel_basic->seStart(0x902, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
                        break;
                    case 1:
                        dComIfGp_setMessageCountNumber(mFlyDistNow);
                        setMessage(0x2AB3);
                        dComIfGp_getVibration().StartShock(8, 1, cXyz(0.0f, 1.0f, 0.0f));
                        dComIfGp_getVibration().StartShock(4, 30, cXyz(0.0f, 1.0f, 0.0f));
                        JAIZelBasic::zel_basic->seStart(0x901, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
                        break;
                    case 2:
                        setMessage(0x2AB0);
                        break;
                    case 3:
                        setMessage(0x2AB5);
                        break;
                }
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2901);
                dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0210);
                break;
            case 2:
                switch(mFlyState) {
                    case 0:
                        setMessage(0x2AB4);
                        break;
                    case 1:
                        dComIfGp_setMessageCountNumber(mFlyDistNow);
                        setMessage(0x2AA6);
                        break;
                    case 2:
                        setMessage(0x2AB0);
                        break;
                    case 3:
                        setMessage(0x2AB5);
                        break;
                }
                break;
            case 0xA:
                switch(dComIfGs_getTmpReg(dSv_event_tmp_flag_c::UNK_F903)) {
                    case 0:
                        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2B40)) {
                            mpMsgTbl = l_msg_bmcon1_goal;
                        } else {
                            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2B40);
                            mpMsgTbl = l_msg_bmcon1_1st_goal;
                        }
                        break;
                    case 1:
                        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2B40)) {
                            setMessage(0x2AAF);
                        } else {
                            int dist = getFlyDistNow() * 6 / 256;
                            if (dist > 4) {
                                dist = 4;
                            }
                            setMessage(l_msg_bmcon1_result[dist]);
                        }
                        break;
                    case 2:
                        setMessage(0x2AB1);
                        break;
                    case 3:
                        setMessage(0x2AB6);
                        break;
                }
                break;
            default:
                setMessage(msg);
        }

        if (mpMsgTbl != NULL) {
            setMessage(*mpMsgTbl);
        }
    }
    else {
        mpMsgTbl++;
        setMessage(*mpMsgTbl);
    }
}

/* 00002A48-00002ADC       .text eventMesSet__12daNpcBmcon_cFv */
bool daNpcBmcon_c::eventMesSet() {
    u16 temp = talk2(0);
    if (temp == fopMsgStts_BOX_CLOSED_e) {
        if(mMsgFlags & 1) {
            mMsgFlags &= ~1;
            mItemNo = 7;
            m7AE = 6;
        }
        else if (mMsgFlags & 2) {
            mMsgFlags &= ~2;
            mItemNo = 5;
            m7AE = 6;
        }
    }
    return temp == fopMsgStts_BOX_CLOSED_e;
}

/* 00002ADC-00002B38       .text eventGetItemInit__12daNpcBmcon_cFv */
void daNpcBmcon_c::eventGetItemInit() {
    fpc_ProcID itemID = fopAcM_createItemForPresentDemo(&current.pos, mItemNo, 0, -1, current.roomNo, NULL, NULL);
    if (itemID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemID);
    }
}

/* 00002B38-00002C8C       .text talk2__12daNpcBmcon_cFi */
u16 daNpcBmcon_c::talk2(int i_param) {
    /* Nonmatching */
    u16 status = 0xFF;
    if(mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e) {

        if(i_param == 1) {
            mCurrMsgNo = getMsg();
        }

        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
        mMsgStatus = -1;
    }
    else if(mpCurrMsg) {
        status = mpCurrMsg->mStatus;
        switch(status) {
            case fopMsgStts_MSG_DISPLAYED_e:
                mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);

                if(mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(mCurrMsgNo);
                }
                break;

            case fopMsgStts_MSG_TYPING_e:
                if (mMsgStatus == fopMsgStts_MSG_CONTINUES_e) {
                    /* nothing */
                } else if (mMsgStatus == fopMsgStts_BOX_OPENING_e) {
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

/* 00002C8C-00002E58       .text next_msgStatus__12daNpcBmcon_cFPUl */
u16 daNpcBmcon_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {
    case 0x2AB4:
        *pMsgNo = 0x2AFF;
        break;
    default:
        if (mpMsgTbl) {
            mpMsgTbl++;
            switch (*mpMsgTbl) {
            case 0:
                mpMsgTbl = NULL;
                status = fopMsgStts_MSG_ENDS_e;
                break;
            case 1:
                if (mpCurrMsg->mSelectNum == 0) {
                    if (dComIfGs_getRupee() < dComIfGp_getMessageRupee()) {
                        mpMsgTbl = l_msg_bmcon1_not_rupee;
                    } else {
                        mpMsgTbl = l_msg_bmcon1_appear;
                        dComIfGp_setItemRupeeCount(-dComIfGp_getMessageRupee());
                    }
                } else {
                    mpMsgTbl = l_msg_bmcon1_not_appear;
                }
                *pMsgNo = *mpMsgTbl;
                break;
            case 2:
                if (mpCurrMsg->mSelectNum == 0) {
                    if (dComIfGs_getRupee() < dComIfGp_getMessageRupee()) {
                        mpMsgTbl = l_msg_bmcon1_not_rupee;
                    } else {
                        mpMsgTbl = l_msg_bmcon1_appear2;
                        dComIfGp_setItemRupeeCount(-dComIfGp_getMessageRupee());
                    }
                } else {
                    mpMsgTbl = l_msg_bmcon1_not_appear2;
                }
                *pMsgNo = *mpMsgTbl;
                break;
            case 3:
                dComIfGp_setItemMagicCount(dComIfGs_getMaxMagic());
                m7C2 = 1;
                mpMsgTbl = NULL;
                status = fopMsgStts_MSG_ENDS_e;
                break;
            case 4:
                mMsgFlags |= 1;
                status = fopMsgStts_MSG_ENDS_e;
                break;
            case 5:
                mMsgFlags |= 2;
                status = fopMsgStts_MSG_ENDS_e;
                break;
            default:
                *pMsgNo = *mpMsgTbl;
                break;
            }
        }
        else {
            status = fopMsgStts_MSG_ENDS_e;
        }
        break;
    }

    return status;
}

/* 00002E58-0000301C       .text getMsg__12daNpcBmcon_cFv */
u32 daNpcBmcon_c::getMsg() {
    u32 msgNo = 0;
    mpMsgTbl = NULL;

    if (dComIfGp_event_chkTalkXY()) {
        /* wait for talk input */
    }
    else {
        switch (getNpcNo()) {
        case 0:
            if (m7C2) {
                mpMsgTbl = l_msg_bmcon1_talk;
            }
            else if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2901)) {
                mpMsgTbl = l_msg_bmcon1_1st_appear;
            }
            else if (isClear()) {
                mpMsgTbl = l_msg_bmcon1_cleared;
                dComIfGp_setMessageCountNumber(getFlyDistMax());
            }
            else {
                dComIfGp_setMessageCountNumber(getFlyDistMax());
                mpMsgTbl = l_msg_bmcon1_2nd;
            }
            break;
        case 1:
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A40)) {
                mpMsgTbl = l_msg_bmcon2_2st_talk;
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2A40);
            }
            else if (isClear()) {
                mpMsgTbl = l_msg_bmcon2_cleared;
            }
            else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2901)) {
                dComIfGp_setMessageCountNumber(getFlyDistMax());
                mpMsgTbl = l_msg_bmcon2_appear;
            }
            else {
                mpMsgTbl = l_msg_bmcon2_talk;
            }
            break;
        }
    }

    if (mpMsgTbl != NULL) {
        msgNo = *mpMsgTbl;
    }

    return msgNo;
}

/* 0000301C-00003098       .text chkMsg__12daNpcBmcon_cFv */
void daNpcBmcon_c::chkMsg() {
    switch ((s32)mCurrMsgNo) {
    case 0x2AB2:
        JAIZelBasic::zel_basic->bgmStart(0x80000051, 0, 0);
        break;
    case 0x2AB3:
        JAIZelBasic::zel_basic->bgmStart(0x80000052, 0, 0);
        break;
    }
}

/* 00003098-000030A0       .text setMessage__12daNpcBmcon_cFUl */
void daNpcBmcon_c::setMessage(u32 msgNo) {
    mCurrMsgNo = msgNo;
}

/* 000030A0-00003158       .text setAnmFromMsgTag__12daNpcBmcon_cFv */
void daNpcBmcon_c::setAnmFromMsgTag() {
    switch(dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnmTbl(l_npc_anm_wait);
            break;
        case 5:
            setAnmTbl(l_npc_anm_wait2);
            break;
        case 6:
            setAnmTbl(l_npc_anm_talk);
            break;
        case 9:
            setAnmTbl(l_npc_anm_talk2);
            break;
        case 14:
            m7C0 = 0;
            setAnmTbl(l_npc_anm_talk3);
            break;
        case 18:
            setAnmTbl(l_npc_anm_con1);
            break;
        case 19:
            setAnmTbl(l_npc_anm_con2);
            break;
    }
    dComIfGp_clearMesgAnimeAttrInfo();
}

/* 00003158-00003178       .text getPrmNpcNo__12daNpcBmcon_cFv */
u8 daNpcBmcon_c::getPrmNpcNo() {
    if(0 <= argument && argument < 2) {
        return argument;
    }
    return 0;
}

/* 00003178-000031A4       .text getPrmRailID__12daNpcBmcon_cFv */
u8 daNpcBmcon_c::getPrmRailID() {
    return daObj::PrmAbstract<daNpcBmcon_c::Prm_e>(this, PRM_RAIL_ID_W, PRM_RAIL_ID_S);
}

/* 000031A4-0000322C       .text setMtx__12daNpcBmcon_cFv */
void daNpcBmcon_c::setMtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 0000322C-0000356C       .text chkAttention__12daNpcBmcon_cFv */
void daNpcBmcon_c::chkAttention() {
    m7C1 = 0;

    if(mEventCut.getAttnFlag()) {
        mLookAtPos = mEventCut.getAttnPos();
        m7BE = 1;
        if(m7BF != 0) {
            m790 = 0;
            m_jnt.setTrn();
        }
        else {
            m790 = 1;
        }

        if(m7AD == 0) {
            m7AD = 1;
        }
    }
    else {
        fopAc_ac_c* player = dComIfGp_getLinkPlayer();

        f32 dist = mAttnDist;
        s32 angle = mAttnAngle;
        f32 tmpDist;
        s16 tmpAngle;

        dNpc_calc_DisXZ_AngY(current.pos, player->current.pos, &tmpDist, &tmpAngle);

        if(m7AD != 0) {
            dist += 40.0f;
            angle += 0x71C;
        }

        tmpAngle -= shape_angle.y;
        if(dist > tmpDist && angle > abs(tmpAngle)) {
            if(player->current.pos.y > current.pos.y - 200.0f) {
                mLookAtPos = dNpc_playerEyePos(l_npc_dat[getNpcNo()].field_0x14);
                m7BE = 1;
                if(m7BF != 0) {
                    m790 = 0;
                }
                else {
                    m790 = 1;
                }

                if(m7C0 == 0) {
                    m7AA = m79C;
                    m790 = 0;
                    m7BE = 2;
                    m_jnt.setTrn();
                }

                if (m7AD == 0) {
                    m7AD = 1;
                }
            }
        }
        else {
            if(m7AD == 1) {
                m7AD = 0;
                m798 = l_npc_dat[getNpcNo()].field_0x48;
            }
            if(l_npc_dat[getNpcNo()].field_0x24 > tmpDist){
                mLookAtPos = dNpc_playerEyePos(l_npc_dat[getNpcNo()].field_0x14);
                m7BE = 1;
                if (m7BF != 0) {
                    m790 = 0;
                } else {
                    m790 = 1;
                }
                if (m7C0 == 0) {
                    m7AA = m79C;
                    m790 = 0;
                    m7BE = 2;
                    m_jnt.setTrn();
                }
                m7C1 = 1;
            } else {
                m7BE = 0;
                if(m798) {
                    m798--;
                }
                else {
                    m7AA = m79C;
                    m790 = 0;
                    m7BE = 2;
                    m_jnt.setTrn();
                }
            }
        }
    }

    m7A6 = l_npc_dat[getNpcNo()].field_0x2A;
}

/* 0000356C-000036B8       .text lookBack__12daNpcBmcon_cFv */
void daNpcBmcon_c::lookBack() {
    short target = m7A6;
    short desiredYRot = current.angle.y;
    cXyz* dstTemp = NULL;
    cXyz temp2;
    cXyz dstPos = eyePos;
    bool headOnlyFollow = m790;

    switch(m7BE) {
        case 1:
            temp2 = mLookAtPos;
            dstTemp = &temp2;
            break;
        case 2:
            desiredYRot = m7AA;
            break;
        case 0:
        default:
            break;
    }

    if (m7AC && m7BF) {
        headOnlyFollow = false;
        m_jnt.setTrn();
    }

    if (m_jnt.trnChk()) {
        if(mEventCut.getTurnSpeed() != 0) {
            target = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&m7A8, target, 4, 0x800);
    } else {
        m7A8 = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstTemp, dstPos, desiredYRot, m7A8, headOnlyFollow);
    shape_angle = current.angle;
}

/* 000036B8-00003794       .text playAnm__12daNpcBmcon_cFv */
void daNpcBmcon_c::playAnm() {
    mAnmFlag &= ~1;
    mpArmMorf->play(0, 0, 0);
    if(mpMorf->play(0, 0, 0)) {
        if(mpAnmDat) {
            if(mAnmTimer > 0) {
                mAnmTimer--;
                if(mAnmTimer == 0) {
                    mpAnmDat++;
                    if(setAnmTbl(mpAnmDat)) {
                        mAnmFlag |= 1;
                    }
                }
                else {
                    setAnm(mpAnmDat->mAnmNo, 0, 0.0f);
                }
            }
        }
    }
}

/* 00003794-000038C0       .text setAnm__12daNpcBmcon_cFUcif */
void daNpcBmcon_c::setAnm(u8 param_1, int param_2, f32 morf) {
    if (m784 >= 0.0f) {
        morf = m784;
        m784 = -1.0f;
    }

    mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_bck_ix_tbl[param_1]),
        param_2, morf, 1.0f, 0.0f, -1.0f, NULL
    );

    mpArmMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[mNpcNo], l_arm_bck_ix_tbl[param_1]),
        param_2, morf, 1.0f, 0.0f, -1.0f, NULL
    );
    mBckNo = param_1;
}

/* 000038C0-00003960       .text setAnmTbl__12daNpcBmcon_cFP12sBmconAnmDat */
bool daNpcBmcon_c::setAnmTbl(sBmconAnmDat* anmDat) {
    if (anmDat->mAnmNo == 0xFF) {
        mpAnmDat = NULL;
        return true;
    }
    else {
        mpAnmDat = anmDat;
        mAnmTimer = mpAnmDat->mCount;

        int loopMode = 2;
        if (mAnmTimer > 0) {
            loopMode = 0;
        }

        if (mBckNo != mpAnmDat->mAnmNo || loopMode == 0) {
            setAnm(mpAnmDat->mAnmNo, loopMode, (f32)mpAnmDat->mMorf);
        }
        return false;
    }
}

/* 00003960-00003968       .text XyCheckCB__12daNpcBmcon_cFi */
s16 daNpcBmcon_c::XyCheckCB(int i_itemBtn) {
    return false;
}

/* 00003968-000039E0       .text setCollision__12daNpcBmcon_cFP8dCcD_Cyl4cXyzff */
void daNpcBmcon_c::setCollision(dCcD_Cyl* cyl, cXyz center, f32 radius, f32 height) {
    cyl->SetC(center);
    cyl->SetR(radius);
    cyl->SetH(height);
    dComIfG_Ccsp()->Set(cyl);
}

/* 000039E0-00003A7C       .text calcFlyDist__12daNpcBmcon_cFv */
cXyz daNpcBmcon_c::calcFlyDist() {
    cXyz pos = dComIfGp_getLinkPlayer()->current.pos;
    PSVECSubtract(&pos, &l_bmcon_pos_tbl[0], &pos);
    mDoMtx_stack_c::YrotS(-0x6000);
    cXyz out;
    mDoMtx_stack_c::multVec(&pos, &out);
    return out;
}

/* 00003A7C-00003AE8       .text getFlyDistMax__12daNpcBmcon_cFv */
s16 daNpcBmcon_c::getFlyDistMax() {
    return dComIfGs_getEventReg(dSv_event_flag_c::UNK_A8FF) + (dComIfGs_getEventReg(dSv_event_flag_c::UNK_A7FF) << 8);
}

/* 00003AE8-00003B6C       .text setFlyDistMax__12daNpcBmcon_cFs */
void daNpcBmcon_c::setFlyDistMax(s16 dist) {
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_A7FF, dist % 256);
    dComIfGs_setEventReg(dSv_event_flag_c::UNK_A8FF, (u8)(dist / 256));
}

/* 00003B6C-00003BD8       .text getFlyDistNow__12daNpcBmcon_cFv */
s16 daNpcBmcon_c::getFlyDistNow() {
    return dComIfGs_getTmpReg(dSv_event_tmp_flag_c::UNK_FAFF) + (dComIfGs_getTmpReg(dSv_event_tmp_flag_c::UNK_FBFF) << 8);
}

/* 00003BD8-00003C5C       .text setFlyDistNow__12daNpcBmcon_cFs */
void daNpcBmcon_c::setFlyDistNow(s16 dist) {
    dComIfGs_setTmpReg(dSv_event_tmp_flag_c::UNK_FBFF, dist % 256);
    dComIfGs_setTmpReg(dSv_event_tmp_flag_c::UNK_FAFF, (u8)(dist / 256));
}

/* 00003C5C-00003DC4       .text chkEndEvent__12daNpcBmcon_cFv */
BOOL daNpcBmcon_c::chkEndEvent() {
    switch (getNpcNo()) {
    case 0:
        if (dComIfGp_evmng_endCheck(mEventIdx1) && dComIfGs_getTmpReg(dSv_event_tmp_flag_c::UNK_F903) != 0) {
            g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
            m7C0 = l_npc_dat[getNpcNo()].field_0x4B;
            return TRUE;
        }
        if (dComIfGp_evmng_endCheck(mEventIdx2)) {
            g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
            m7C0 = l_npc_dat[getNpcNo()].field_0x4B;
            return TRUE;
        }
        break;
    case 1:
        if (dComIfGp_evmng_endCheck(mEventIdx1) || dComIfGp_evmng_endCheck(mEventIdx2)) {
            g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
            m7C0 = l_npc_dat[getNpcNo()].field_0x4B;
            return TRUE;
        }
        break;
    }
    return FALSE;
}

/* 00003DC4-00003DFC       .text isClear__12daNpcBmcon_cFv */
BOOL daNpcBmcon_c::isClear() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_2B40) ? TRUE : FALSE;
}

/* 00003DFC-00003E1C       .text daNpc_BmconCreate__FPv */
static cPhs_State daNpc_BmconCreate(void* i_this) {
    return ((daNpcBmcon_c*)i_this)->_create();
}

/* 00003E1C-00003E40       .text daNpc_BmconDelete__FPv */
static BOOL daNpc_BmconDelete(void* i_this) {
    return ((daNpcBmcon_c*)i_this)->_delete();
}

/* 00003E40-00003E64       .text daNpc_BmconExecute__FPv */
static BOOL daNpc_BmconExecute(void* i_this) {
    return ((daNpcBmcon_c*)i_this)->_execute();
}

/* 00003E64-00003E88       .text daNpc_BmconDraw__FPv */
static BOOL daNpc_BmconDraw(void* i_this) {
    return ((daNpcBmcon_c*)i_this)->_draw();
}

/* 00003E88-00003E90       .text daNpc_BmconIsDelete__FPv */
static BOOL daNpc_BmconIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_BmconMethodTable = {
    (process_method_func)daNpc_BmconCreate,
    (process_method_func)daNpc_BmconDelete,
    (process_method_func)daNpc_BmconExecute,
    (process_method_func)daNpc_BmconIsDelete,
    (process_method_func)daNpc_BmconDraw,
};

actor_process_profile_definition g_profile_NPC_BMCON1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BMCON1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcBmcon_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BMCON1_e,
    /* Actor SubMtd */ &daNpc_BmconMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
