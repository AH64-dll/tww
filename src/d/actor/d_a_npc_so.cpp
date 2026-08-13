/**
 * d_a_npc_so.cpp
 * NPC - Fishman (blue fish)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_so.h"
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_tag_so.h"
#include "d/actor/d_a_ship.h"
#include "d/d_s_play.h"
#include "f_op/f_op_camera.h"
#include "d/d_lib.h"
#include "f_op/f_op_kankyo_mng.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/So.h"

const s32 daNpc_So_c::m_heapsize = 0x1C00;
const char daNpc_So_c::m_arc_name[] = "So";

static daNpc_So_HIO_c l_HIO;

const dCcD_SrcSph daNpc_So_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_UNK8 & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};




/* 000000EC-000002A4       .text __ct__14daNpc_So_HIO_cFv */
daNpc_So_HIO_c::daNpc_So_HIO_c() {
    field_0x2C[0] = 0;
    field_0x2C[1] = 0;
    field_0x2C[2] = 0;
    field_0x2C[3] = 0;
    field_0x2C[4] = 0;
    field_0x2C[5] = 0;
    field_0x34 = 3.0f;
    field_0x38 = 0.9f;
    field_0x3C = 100.0f;
    field_0x40 = 2000.0f;
    field_0x54 = 20000.0f;
    field_0x5C = 30.0f;
    field_0x44 = 0.7f;
    field_0x48 = 2000.0f;
    field_0x4C = 2.0f;
    field_0x50 = 150.0f;
    field_0x64 = 0x1F40;
    field_0x66 = 0x0FA0;
    field_0x68 = -0x1F40;
    field_0x6A = -0x0FA0;
    field_0x6C = 10.0f;
    mNpc.m04 = -33.0f;
    mNpc.mMaxHeadX = 0x1FFE;
    mNpc.mMaxHeadY = 0x1000;
    mNpc.mMaxBackboneX = 0x1000;
    mNpc.mMaxBackboneY = 0x2000;
    mNpc.mMinHeadX = -0xBB8;
    mNpc.mMinHeadY = -0x1000;
    mNpc.mMinBackboneX = -0x1000;
    mNpc.mMinBackboneY = -0x2000;
    mNpc.mMaxTurnStep = 0x250;
    mNpc.mMaxHeadTurnVel = 0x150;
    mNpc.mAttnYOffset = 50.0f;
    mNpc.mMaxAttnAngleY = 0x7FFF;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0f;
    field_0x58 = 250.0f;
    field_0x60 = 700.0f;
    field_0x70 = 600.0f;
    field_0x74 = 300.0f;
    field_0x78 = 100.0f;
    field_0x7C = 5;
    field_0x80 = -1.4f;
    field_0x84 = 18.0f;
    field_0x88 = 120.0f;
    field_0x8C = 300.0f;
    field_0x90 = 15.0f;
    field_0x94 = 0;
}

/* 000002A4-000002D0       .text searchEsa_CB__FPvPv */
static void* searchEsa_CB(void* param_1, void* i_this) {
    return static_cast<daNpc_So_c*>(i_this)->_searchEsa((fopAc_ac_c*)param_1);
}

/* 000002D0-000002F8       .text _searchEsa__10daNpc_So_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_So_c::_searchEsa(fopAc_ac_c* pActor) {
    if (fopAcM_GetName(pActor) == fpcNm_ESA_e) {
        esa_class* pBait = static_cast<esa_class*>(pActor);
        if (pBait->field_0x298 == 0) {
            return pActor;
        }
    }
    return NULL;
}

/* 000002F8-00000344       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == 0) {
        daNpc_So_c* i_this = (daNpc_So_c*)j3dSys.getModel()->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeControl(i_nodeP, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000344-00000474       .text _nodeControl__10daNpc_So_cFP7J3DNodeP8J3DModel */
void daNpc_So_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    /* Nonmatching */
    J3DJoint* joint = static_cast<J3DJoint*>(i_nodeP);
    int jntNo = joint->getJntNo();

    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jntNo));

    if (jntNo == m_jnt.getHeadJntNum()) {
        cXyz pos(0.0f, 0.0f, 0.0f);
        cXyz off(24.0f, -12.0f, 0.0f);
        mDoMtx_stack_c::multVec(&pos, &field_0xB60);
        mDoMtx_stack_c::YrotM(m_jnt.mAngles[0][1]);
        mDoMtx_stack_c::ZrotM(m_jnt.mAngles[0][0]);
        mDoMtx_stack_c::multVec(&off, &field_0xB54);
    } else if (jntNo == m_jnt.getBackboneJntNum()) {
        mDoMtx_stack_c::XrotM(m_jnt.mAngles[1][1]);
        mDoMtx_stack_c::ZrotM(m_jnt.mAngles[1][0]);
    }

    mDoMtx_copy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
    mDoMtx_copy(mDoMtx_stack_c::now, i_modelP->getAnmMtx(jntNo));
}

/* 000004B0-000004DC       .text searchTagSo_CB__FPvPv */
static void* searchTagSo_CB(void* param_1, void* i_this) {
    return static_cast<daNpc_So_c*>(i_this)->_searchTagSo((fopAc_ac_c*)param_1);
}

/* 000004DC-0000054C       .text _searchTagSo__10daNpc_So_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_So_c::_searchTagSo(fopAc_ac_c* pActor) {
    if (fopAcM_GetName(pActor) == fpcNm_TAG_SO_e) {
        daTag_So_c* pTag = static_cast<daTag_So_c*>(pActor);
        if (field_0xA79 == pTag->m290 && pTag->m298 != 1) {
            field_0xA7C = pTag->mRadius;
            field_0xA80 = pTag->current.pos;
            current.pos = field_0xA80;
            return pActor;
        }
    }
    return NULL;
}

/* 0000054C-00000578       .text searchMinigameTagSo_CB__FPvPv */
static void* searchMinigameTagSo_CB(void* param_1, void* i_this) {
    return static_cast<daNpc_So_c*>(i_this)->_searchMinigameTagSo((fopAc_ac_c*)param_1);
}

/* 00000578-000005C8       .text _searchMinigameTagSo__10daNpc_So_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_So_c::_searchMinigameTagSo(fopAc_ac_c* pActor) {
    if (fopAcM_GetName(pActor) == fpcNm_TAG_SO_e) {
        daTag_So_c* pTag = static_cast<daTag_So_c*>(pActor);
        if (pTag->m298 == 1) {
            field_0xB90 = pTag->current.pos;
            field_0xB9C = pTag->shape_angle.y;
            field_0xBAE = 1;
            return pActor;
        }
    }
    return NULL;
}

/* 000005C8-000005E8       .text daNpc_So_XyCheckCB__FPvi */
static s16 daNpc_So_XyCheckCB(void* i_this, int i_itemBtn) {
    return static_cast<daNpc_So_c*>(i_this)->XyCheckCB(i_itemBtn);
}

/* 000005E8-00000680       .text XyCheckCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyCheckCB(int i_itemBtn) {
    if (fopAcIt_Judge(searchEsa_CB, this)) {
        return 0;
    }
    if (field_0x6D3 != 2) {
        return 0;
    }
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && dComIfGp_getSelectItem(i_itemBtn) == 0x82) {
        return 1;
    }
    return 0;
}

/* 00000680-000006A0       .text daNpc_So_XyEventCB__FPvi */
static s16 daNpc_So_XyEventCB(void* i_this, int i_itemBtn) {
    return static_cast<daNpc_So_c*>(i_this)->XyEventCB(i_itemBtn);
}

/* 000006A0-000006EC       .text XyEventCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyEventCB(int i_itemBtn) {
    field_0xBDC = dComIfGp_evmng_getEventIdx("NpcSo", 0xFF);
    return field_0xBDC;
}

/* 000006EC-0000070C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daNpc_So_c*>(i_this)->_createHeap();
}

/* 0000070C-00000A20       .text _createHeap__10daNpc_So_cFv */
BOOL daNpc_So_c::_createHeap() {
    /* Nonmatching */
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_SO_BDL_SO_e));
    JUT_ASSERT(0x1FD, modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL, NULL,
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL,
        0x00080000, 0x11020022
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return false;
    }

    mpMorf->getModel()->setUserArea((u32)this);

    J3DAnmTexPattern* btpData = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_SO_BTP_SO_e));
    JUT_ASSERT(0x210, btpData != NULL);

    if (!mBtpAnm.init(modelData, btpData, 1, 0, 1.0f, 0, -1, 0)) {
        return false;
    }

    m_jnt.setHeadJntNum(0xB);
    JUT_ASSERT(0x215, m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(1);
    JUT_ASSERT(0x217, m_jnt.getBackboneJntNum() >= 0);

    modelData->getJointNodePointer(0xB)->setCallBack(nodeControl_CB);
    modelData->getJointNodePointer(1)->setCallBack(nodeControl_CB);

    J3DModelData* fudeData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name, dRes_INDEX_SO_BDL_SO_FUDE_e));
    JUT_ASSERT(0x221, fudeData != NULL);

    mpModel = mDoExt_J3DModel__create(fudeData, 0x00080000, 0x11000022);
    if (mpModel == NULL) {
        return false;
    }

    return jntHitCreateHeap() ? TRUE : FALSE;
}

/* 00000A20-00000A84       .text jntHitCreateHeap__10daNpc_So_cFv */
bool daNpc_So_c::jntHitCreateHeap() {
    /* Nonmatching */
    static Vec cyl_offset_B[] = {
        {15.0f, 0.0f, 0.0f},
        {-15.0f, 0.0f, 0.0f},
    };
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 4,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ cyl_offset_B,
        },
        {
            /* mShapeType  */ JntHitType_CYL_e,
            /* mJointIndex */ 8,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ cyl_offset_B,
        },
    };

    field_0xAA8 = JntHit_create(mpMorf->getModel(), search_data, ARRAY_SIZE(search_data));
    if (field_0xAA8 != NULL) {
        jntHit = field_0xAA8;
    } else {
        return FALSE;
    }
    return TRUE;
}

/* 00000A84-00000C8C       .text checkTgHit__10daNpc_So_cFv */
bool daNpc_So_c::checkTgHit() {
    /* Nonmatching */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    mStts.Move();

    if (cLib_calcTimer(&field_0x6D8) == 0 && mSph.ChkTgHit()) {
        cXyz* hitPos = mSph.GetTgHitPosP();
        cCcD_Obj* hitObj = mSph.GetTgHitObj();
        field_0x6D8 = l_HIO.field_0x7C;

        if (hitObj == NULL) {
            return false;
        }

        switch (hitObj->GetAtType()) {
        case 0x4000:
            fopAcM_seStart(this, 0x2879, 0x20);
            fopAcM_monsSeStart(this, 0x4991, 0);
            dComIfGp_particle_set(0x10, hitPos);
            cXyz scale(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(0xf, hitPos, &player->shape_angle, &scale);
            fopAcM_seStart(this, 0x2828, 0);
            return true;
        }
    }
    return false;
}

/* 00000C8C-00000CB0       .text offsetZero__10daNpc_So_cFv */
void daNpc_So_c::offsetZero() {
    /* Nonmatching */
    field_0xB38.z = 0.1f;
    field_0xB38.y = 20.0f;
    field_0xB38.x = -1.0f;
}

/* 00000CB0-00000CD4       .text offsetDive__10daNpc_So_cFv */
void daNpc_So_c::offsetDive() {
    /* Nonmatching */
    field_0xB38.z = 0.3f;
    field_0xB38.y = 10.0f;
    field_0xB38.x = -150.0f;
}

/* 00000CD4-00000CF8       .text offsetSwim__10daNpc_So_cFv */
void daNpc_So_c::offsetSwim() {
    /* Nonmatching */
    field_0xB38.z = 0.3f;
    field_0xB38.y = 10.0f;
    field_0xB38.x = -40.0f;
}

/* 00000CF8-00000D1C       .text offsetAppear__10daNpc_So_cFv */
void daNpc_So_c::offsetAppear() {
    /* Nonmatching */
    field_0xB38.z = 0.4f;
    field_0xB38.y = 22.0f;
    field_0xB38.x = 110.0f;
}

/* 00000D1C-00000E40       .text getMsg__10daNpc_So_cFv */
u32 daNpc_So_c::getMsg() {
    /* Nonmatching */
    if (field_0xB0C != 0) {
        if (l_HIO.field_0x2C[2] != 0 || field_0xB7C >= 0xA) {
            if (field_0xBD9) {
                return 0x32E2;
            }
            return 0x32DD;
        }
        if (field_0xB7C == 0) {
            return 0x32E1;
        }
        if (field_0xB7C == 1) {
            return 0x32E0;
        }
        dComIfGp_setMessageCountNumber(field_0xB7C);
        return 0x32DF;
    }
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0901) &&
        strcmp(dComIfGp_getStartStageName(), "sea") == 0 && current.roomNo == 0xD) {
        return field_0xBD8 ? field_0x6D0 : 0x32CA;
    }
    return field_0xBD8 ? field_0x6D0 : 0x32D0;
}

/* 00000E40-00001214       .text next_msgStatus__10daNpc_So_cFPUl */
u16 daNpc_So_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00001214-000013A0       .text lookBack__10daNpc_So_cFv */
void daNpc_So_c::lookBack() {
    /* Nonmatching */
    if (dComIfGp_event_getMode() != 0) {
        if (mEventCut.getAttnFlag()) {
            if (field_0x6D3 == 4) {
                m_jnt.mbTrn = false;
            } else {
                m_jnt.mbTrn = true;
                field_0xB44 = mEventCut.getAttnPos();
            }
        } else {
            field_0xB44 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        }
    } else {
        m_jnt.mbTrn = false;
        field_0xB44 = dNpc_playerEyePos(l_HIO.mNpc.m04);
    }

    if (m_jnt.mbTrn) {
        s16 speed = l_HIO.mNpc.mMaxHeadTurnVel;
        if (mEventCut.getTurnSpeed() != 0) {
            speed = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&field_0xB50, speed, 4, 0x800);
    } else {
        field_0xB50 = 0;
    }

    cXyz pos = field_0xB54;
    pos.y += 12.0f;
    m_jnt.lookAtTarget(&shape_angle.y, &field_0xB44, pos, shape_angle.y, field_0xB50, field_0xBDA);
}

/* 000013A0-00001430       .text setAttention__10daNpc_So_cFv */
void daNpc_So_c::setAttention() {
    attention_info.position = field_0xB60;
    attention_info.position.y += l_HIO.mNpc.mAttnYOffset;
    f32 waterY = dLib_getWaterY(attention_info.position, mObjAcch);
    if (attention_info.position.y <= waterY) {
        attention_info.position.y = waterY;
    }
    eyePos = field_0xB54;
}

/* 00001430-00001524       .text setAnm__10daNpc_So_cFScb */
void daNpc_So_c::setAnm(s8 i_anmIdx, bool i_loopFlag) {
    /* Nonmatching */
    static const int a_anm_bcks_tbl[] = {
        9, 6, 7, 5, 8,
    };
    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {0x00, 0xFF, 0x00, 8.0f, 1.0f, 2},
        {0x00, 0xFF, 0x00, 8.0f, 1.0f, 2},
        {0x01, 0xFF, 0x00, 8.0f, 1.0f, 2},
        {0x02, 0xFF, 0x00, 8.0f, 1.0f, 2},
        {0x03, 0xFF, 0x00, 8.0f, 1.0f, 2},
        {0x04, 0xFF, 0x00, 8.0f, 1.0f, 2},
    };

    if (i_anmIdx != 6) {
        field_0x6D3 = i_anmIdx;
    }

    if (mpMorf->getFrame() >= mpMorf->getEndFrame() - 1.0f) {
        if (cM_rndF(100.0f) < l_HIO.field_0x5C) {
            if (field_0x6D3 == 5) {
                field_0x6D3 = 3;
            } else if (field_0x6D3 == 3) {
                field_0x6D3 = 5;
            }
        }
    }

    dLib_bcks_setAnm(m_arc_name, mpMorf, &field_0x6D2, &field_0x6D3, &field_0x6D4, a_anm_bcks_tbl,
                     a_anm_prm_tbl, i_loopFlag);
}

/* 00001524-00001644       .text setAnmSwimSpeed__10daNpc_So_cFv */
void daNpc_So_c::setAnmSwimSpeed() {
    if (field_0x6D3 == 2) {
    /* Nonmatching */
        const cXyz& delta = current.pos - old.pos;
        f32 dist = std::sqrtf(PSVECSquareMag(&delta));
        dist = dist / 10.0f;
        if (dist <= 0.0f) {
            dist = 0.0f;
        } else if (dist >= 1.0f) {
            dist = 1.0f;
        }
        f32 speed = l_HIO.field_0x38;
        if (dist * l_HIO.field_0x34 >= l_HIO.field_0x38) {
            speed = dist * l_HIO.field_0x34;
        }
        mpMorf->setPlaySpeed(speed);
    }
}

/* 00001644-000016E8       .text setMtx__10daNpc_So_cFv */
void daNpc_So_c::setMtx() {
    /* Nonmatching */
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::transM(1.0f, field_0xB34, 1.0f);
    mDoMtx_copy(mDoMtx_stack_c::now, model->getBaseTRMtx());
}

/* 000016E8-00001718       .text modeWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeWaitInit() {
    speedF = 0.0f;
    field_0xAFC = 0.0f;
    offsetAppear();
}

/* 00001718-0000171C       .text modeWait__10daNpc_So_cFv */
void daNpc_So_c::modeWait() {
}

/* 0000171C-0000175C       .text modeHideInit__10daNpc_So_cFv */
void daNpc_So_c::modeHideInit() {
    field_0xBDB = 1;
    offsetDive();
    field_0xA7C = 0.0f;
}

/* 0000175C-00001778       .text modeHide__10daNpc_So_cFv */
void daNpc_So_c::modeHide() {
    current.pos = field_0xA80;
}

/* 00001778-00001880       .text modeJumpInit__10daNpc_So_cFv */
void daNpc_So_c::modeJumpInit() {
    /* Nonmatching */
    field_0xAFC = field_0xB08 * (5.0f + cM_rndF(5.0f));
    speedF = field_0xAFC;
    speed.y = 30.0f * field_0xB08 + 4.0f * speedF;
    if (speed.y > l_HIO.field_0x50) {
        speed.y = l_HIO.field_0x50;
    }
    field_0xB00 = speed.y;
    shape_angle.x = l_HIO.field_0x68;
    setAnm(4, 0);
    m_jnt.onBackBoneLock();
    fopAcM_seStart(this, 0x5938, 0);
}

/* 00001880-000019F0       .text modeJump__10daNpc_So_cFv */
void daNpc_So_c::modeJump() {
    if (current.pos.y < dLib_getWaterY(current.pos, mObjAcch)) {
    /* Nonmatching */
        fopAcM_seStart(this, 0x5939, 0);
        fopKyM_createWpillar(&current.pos, 45.0f * scale.x, 45.0f, 0);

        cXyz diff = field_0xA80 - current.pos;
        cXyz flat;
        flat.x = diff.x;
        flat.y = 0.0f;
        flat.z = diff.z;
        f32 dist = std::sqrtf(PSVECSquareMag(&flat));
        if (dist > field_0xA7C) {
            current.pos = field_0xA80;
        }
        modeProc(PROC_INIT_e, 3);
    }
}

/* 000019F0-00001A6C       .text modeSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeSwimInit() {
    /* Nonmatching */
    attention_info.flags = fopAc_Attn_TALKFLAG_NOTALK_e | fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    field_0xA90 = (int)(30.0f + cM_rndF(90.0f));
    setAnm(2, 0);
    m_jnt.onBackBoneLock();
    offsetDive();
}

/* 00001A6C-00001DB8       .text modeSwim__10daNpc_So_cFv */
void daNpc_So_c::modeSwim() {
    /* Nonmatching */
}

/* 00001DB8-00001DFC       .text modeNearSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwimInit() {
    setAnm(2, 0);
    offsetDive();
    m_jnt.onBackBoneLock();
}

/* 00001DFC-00002144       .text modeNearSwim__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwim() {
    /* Nonmatching */
}

/* 00002144-0000217C       .text modeEventFirstWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWaitInit() {
    field_0xA90 = 0x96;
    field_0xAFC = 0.0f;
    speedF = 0.0f;
    offsetDive();
}

/* 0000217C-000022D0       .text modeEventFirstWait__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWait() {
    /* Nonmatching */
    daShip_c* player = dComIfGp_getShipActor();
    if (player != NULL) {
        current.pos = player->current.pos;
        cXyz diff = player->current.pos - field_0xAAC;
        cXyz flat;
        flat.x = diff.x;
        flat.y = 0.0f;
        flat.z = diff.z;
        f32 dist = std::sqrtf(PSVECSquareMag(&flat));
        if (dist >= l_HIO.field_0x54 && dComIfGs_checkGetItem(0x78) && dComIfGs_isStageBossEnemy(3) &&
            dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
            modeProc(PROC_INIT_e, 6);
        }
    }
}

/* 000022D0-00002314       .text modeEventFirstInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstInit() {
    offsetSwim();
    field_0xAFC = 0.0f;
    speedF = 0.0f;
    m_jnt.offBackBoneLock();
}

/* 00002314-000023C8       .text modeEventFirst__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirst() {
    if (eventInfo.getCommand() == 2) {
        if (!mEventCut.cutProc()) {
    /* Nonmatching */
            cutProc();
        }
        if (dComIfGp_evmng_endCheck("SO_1ST_MEET")) {
            dComIfGp_event_onEventFlag(8);
            field_0xB70 = 1;
            modeProc(PROC_INIT_e, 0xB);
            attention_info.flags = fopAc_Attn_TALKFLAG_NOTALK_e | fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;        }
    } else {
        field_0xB70 = 3;
    }
}

/* 000023C8-0000240C       .text modeEventFirstEndInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEndInit() {
    offsetAppear();
    field_0xAFC = 0.0f;
    speedF = 0.0f;
    m_jnt.offBackBoneLock();
}

/* 0000240C-000024C0       .text modeEventFirstEnd__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEnd() {
    if (eventInfo.getCommand() == 2) {
        if (!mEventCut.cutProc()) {
    /* Nonmatching */
            cutProc();
        }
        if (dComIfGp_evmng_endCheck("SO_1ST_MEET_END")) {
            dComIfGp_event_onEventFlag(8);
            modeProc(PROC_INIT_e, 0xC);
        }
    } else {
        if (talk(1) == 0x12) {
            field_0xB70 = 4;
        }
    }
}

/* 000024C0-00002504       .text modeEventEsaInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsaInit() {
    offsetSwim();
    field_0xAFC = 0.0f;
    speedF = 0.0f;
    m_jnt.offBackBoneLock();
}

/* 00002504-00002594       .text modeEventEsa__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsa() {
    /* Nonmatching */
}

/* 00002594-000025B0       .text modeEventMapopenInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopenInit() {
    field_0xAFC = 0.0f;
    speedF = 0.0f;
    m_jnt.offBackBoneLock();
}

/* 000025B0-00002670       .text modeEventMapopen__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopen() {
    if (eventInfo.getCommand() == 2) {
        if (!mEventCut.cutProc()) {
    /* Nonmatching */
            cutProc();
        }
        if (dComIfGp_evmng_endCheck("SO_MAPOPEN")) {
            dComIfGp_event_onEventFlag(8);
            field_0xB70 = 1;
            field_0xBD8 = 1;
            modeProc(PROC_INIT_e, 0xB);
        }
    } else {
        if (talk(1) == 0x12) {
            field_0xB70 = 5;
        }
    }
}

/* 00002670-000026B4       .text modeEventBowInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventBowInit() {
    offsetSwim();
    field_0xAFC = 0.0f;
    speedF = 0.0f;
    m_jnt.offBackBoneLock();
}

/* 000026B4-000027F8       .text modeEventBow__10daNpc_So_cFv */
void daNpc_So_c::modeEventBow() {
    if (eventInfo.getCommand() == 2) {
        if (!mEventCut.cutProc()) {
    /* Nonmatching */
            cutProc();
        }
        if (dComIfGp_evmng_endCheck("SO_BOW")) {
            field_0xB0C = 1;
            dComIfGp_event_onEventFlag(8);
            field_0xBDB = 0;
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3A10);
            camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
            cam->mCamera.Reset(field_0xBCC, field_0xBC0);
            cam->mCamera.Start();
            field_0xB70 = 1;
            modeProc(PROC_INIT_e, 0xB);
        }
    } else {
        if (talk(1) == 0x12) {
            field_0xB70 = 6;
        }
    }
}

/* 000027F8-0000283C       .text modeTalkInit__10daNpc_So_cFv */
void daNpc_So_c::modeTalkInit() {
    offsetAppear();
    setAnm(3, 0);
    m_jnt.offBackBoneLock();
}

/* 0000283C-0000289C       .text modeTalk__10daNpc_So_cFv */
void daNpc_So_c::modeTalk() {
    /* Nonmatching */
}

/* 0000289C-0000296C       .text modeDisappearInit__10daNpc_So_cFv */
void daNpc_So_c::modeDisappearInit() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0901)) {
    /* Nonmatching */
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0901);
    }
    offsetDive();
    fopAcM_seStart(this, 0x593B, 0);
    fopKyM_createWpillar(&current.pos, 1.2f * scale.x, 45.0f, 0);
    m_jnt.offBackBoneLock();
}

/* 0000296C-00002A90       .text modeDisappear__10daNpc_So_cFv */
void daNpc_So_c::modeDisappear() {
    /* Nonmatching */
}

/* 00002A90-00002B60       .text modeDebugInit__10daNpc_So_cFv */
void daNpc_So_c::modeDebugInit() {
    /* Nonmatching */
}

/* 00002B60-00002B64       .text modeDebug__10daNpc_So_cFv */
void daNpc_So_c::modeDebug() {
    
}

/* 00002B64-00002B68       .text modeGetRupeeInit__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupeeInit() {
}

/* 00002B68-00002C6C       .text modeGetRupee__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupee() {
    /* Nonmatching */
}

/* 00002C6C-00002CC0       .text modeEventTriForceInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForceInit() {
    /* Nonmatching */
}

/* 00002CC0-00002D80       .text modeEventTriForce__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForce() {
    /* Nonmatching */
}

/* 00002D80-00003110       .text modeProc__10daNpc_So_cFQ210daNpc_So_c6Proc_ei */
void daNpc_So_c::modeProc(daNpc_So_c::Proc_e, int) {
    /* Nonmatching */
}

/* 00003110-00003264       .text eventOrder__10daNpc_So_cFv */
void daNpc_So_c::eventOrder() {
    /* Nonmatching */
    static char* a_demo_name_tbl[] = {
        "SO_1ST_MEET",
        "SO_1ST_MEET_END",
        "SO_MAPOPEN",
        "SO_BOW",
        "SO_GET_RUPEE",
        "SO_TRIFORCE_CHECK",
    };

    if (field_0xB70 == 1 || field_0xB70 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (field_0xB70 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (field_0xB70 == 5 || field_0xB70 == 4 || field_0xB70 == 6) {
        fopAcM_orderChangeEvent(this, a_demo_name_tbl[field_0xB70 - 3], 0, 0xFFFF);
    } else if (field_0xB70 == 7) {
        if (REG12_S(9) == 0) {
            fopAcM_orderChangeEvent(this, a_demo_name_tbl[field_0xB70 - 3], 0, 0xFFFF);
            eventInfo.onCondition(8);
        } else {
            fopAcM_orderOtherEvent2(this, a_demo_name_tbl[field_0xB70 - 3], 1, 0xFFFF);
        }
    } else if (field_0xB70 >= 3) {
        fopAcM_orderOtherEvent2(this, a_demo_name_tbl[field_0xB70 - 3], 1, 0xFFFF);
    }
}

/* 00003264-0000330C       .text checkOrder__10daNpc_So_cFv */
void daNpc_So_c::checkOrder() {
    if (eventInfo.getCommand() == 2) {
    /* Nonmatching */
        field_0xB70 = 0;
    } else if (eventInfo.getCommand() == 1) {
        if (field_0xB70 == 1 || field_0xB70 == 2) {
            u8 flag = 0;
            u8 talkBtn = dComIfGp_event_getTalkXYBtn();
            if (talkBtn == 1 || talkBtn == 2 || talkBtn == 3) {
                flag = 1;
            }
            if (flag != 0) {
                modeProc(PROC_INIT_e, 8);
            }
        }
        field_0xB70 = 0;
    }
}

/* 0000330C-000033F4       .text setScale__10daNpc_So_cFv */
void daNpc_So_c::setScale() {
    /* Nonmatching */
    f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
    if (dist > l_HIO.field_0x48) {
        field_0xB08 = 1.0f + (dist - l_HIO.field_0x48) / ((100000.0f - l_HIO.field_0x48) / l_HIO.field_0x4C);
        if (field_0xB08 > l_HIO.field_0x4C) {
            field_0xB08 = l_HIO.field_0x4C;
        }
    } else {
        field_0xB08 = l_HIO.field_0x44;
    }
    if (field_0x6CC == 0xF) {
        field_0xB08 = 1.0f;
        scale.set(field_0xB08, field_0xB08, field_0xB08);
    }
    cXyz target(field_0xB08, field_0xB08, field_0xB08);
    cLib_addCalcPos2(&scale, target, 0.1f, 0.5f);
}

/* 000033F4-00003844       .text _execute__10daNpc_So_cFv */
bool daNpc_So_c::_execute() {
    /* Nonmatching */
}

/* 00003844-000038E0       .text debugDraw__10daNpc_So_cFv */
void daNpc_So_c::debugDraw() {
    /* Nonmatching */
}

/* 000038E0-00003954       .text hudeDraw__10daNpc_So_cFv */
void daNpc_So_c::hudeDraw() {
    /* Nonmatching */
}

/* 00003954-00003B00       .text _draw__10daNpc_So_cFv */
bool daNpc_So_c::_draw() {
    /* Nonmatching */
}

/* 00003B00-00003DF8       .text createInit__10daNpc_So_cFv */
void daNpc_So_c::createInit() {
    /* Nonmatching */
}

/* 00003DF8-00003E24       .text getArg__10daNpc_So_cFv */
void daNpc_So_c::getArg() {
    /* Nonmatching */
}

/* 00003E24-00003F38       .text _create__10daNpc_So_cFv */
cPhs_State daNpc_So_c::_create() {
    /* Nonmatching */
}

/* 000046E4-00004754       .text _delete__10daNpc_So_cFv */
bool daNpc_So_c::_delete() {
    /* Nonmatching */
}

/* 00004754-00004774       .text daNpc_SoCreate__FPv */
static cPhs_State daNpc_SoCreate(void* i_this) {
    return ((daNpc_So_c*)i_this)->_create();
}

/* 00004774-00004798       .text daNpc_SoDelete__FPv */
static BOOL daNpc_SoDelete(void* i_this) {
    return ((daNpc_So_c*)i_this)->_delete();
}

/* 00004798-000047BC       .text daNpc_SoExecute__FPv */
static BOOL daNpc_SoExecute(void* i_this) {
    return ((daNpc_So_c*)i_this)->_execute();
}

/* 000047BC-000047E0       .text daNpc_SoDraw__FPv */
static BOOL daNpc_SoDraw(void* i_this) {
    return ((daNpc_So_c*)i_this)->_draw();
}

/* 000047E0-000047E8       .text daNpc_SoIsDelete__FPv */
static BOOL daNpc_SoIsDelete(void*) {
    return TRUE;
}

#include "d/actor/d_a_npc_so_cut.inc"
#include "d/d_cc_d.h"

static actor_method_class daNpc_SoMethodTable = {
    (process_method_func)daNpc_SoCreate,
    (process_method_func)daNpc_SoDelete,
    (process_method_func)daNpc_SoExecute,
    (process_method_func)daNpc_SoIsDelete,
    (process_method_func)daNpc_SoDraw,
};

actor_process_profile_definition g_profile_NPC_SO = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_SO_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_So_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_SO_e,
    /* Actor SubMtd */ &daNpc_SoMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
