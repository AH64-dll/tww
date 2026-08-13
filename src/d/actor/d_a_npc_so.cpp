/**
 * d_a_npc_so.cpp
 * NPC - Fishman (blue fish)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_so.h"
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_tag_so.h"
#include "m_Do/m_Do_ext.h"
#include "res/Object/So.h"

const s32 daNpc_So_c::m_heapsize = 0x1C00;
const char daNpc_So_c::m_arc_name[] = "So";

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
    field_0x38 = 1.75f;
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

    if (jntNo == field_0x298) {
        cXyz pos(0.0f, 0.0f, 0.0f);
        cXyz off(24.0f, -12.0f, 0.0f);
        mDoMtx_stack_c::multVec(&pos, &field_0xB60);
        mDoMtx_stack_c::YrotM(field_0x292);
        mDoMtx_stack_c::ZrotM(field_0x290);
        mDoMtx_stack_c::multVec(&off, &field_0xB54);
    } else if (jntNo == field_0x299) {
        mDoMtx_stack_c::XrotM(field_0x296);
        mDoMtx_stack_c::ZrotM(field_0x294);
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

    field_0x298 = 0xB;
    JUT_ASSERT(0x215, field_0x298 >= 0);

    field_0x299 = 1;
    JUT_ASSERT(0x217, field_0x299 >= 0);

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
    static Vec cyl_offset_B[] = {
        {15.0f, 0.0f, 0.0f},
        {-15.0f, 0.0f, 0.0f},
    };
    static __jnt_hit_data_c search_data[] = {
        {
            /* mShapeType  */ 4,
            /* mJointIndex */ 0,
            /* mRadius     */ 2.0f,
            /* mpOffsets   */ cyl_offset_B,
        },
        {
            /* mShapeType  */ 8,
            /* mJointIndex */ 0,
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
void daNpc_So_c::checkTgHit() {
    /* Nonmatching */
}

/* 00000C8C-00000CB0       .text offsetZero__10daNpc_So_cFv */
void daNpc_So_c::offsetZero() {
    /* Nonmatching */
}

/* 00000CB0-00000CD4       .text offsetDive__10daNpc_So_cFv */
void daNpc_So_c::offsetDive() {
    /* Nonmatching */
}

/* 00000CD4-00000CF8       .text offsetSwim__10daNpc_So_cFv */
void daNpc_So_c::offsetSwim() {
    /* Nonmatching */
}

/* 00000CF8-00000D1C       .text offsetAppear__10daNpc_So_cFv */
void daNpc_So_c::offsetAppear() {
    /* Nonmatching */
}

/* 00000D1C-00000E40       .text getMsg__10daNpc_So_cFv */
void daNpc_So_c::getMsg() {
    /* Nonmatching */
}

/* 00000E40-00001214       .text next_msgStatus__10daNpc_So_cFPUl */
void daNpc_So_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001214-000013A0       .text lookBack__10daNpc_So_cFv */
void daNpc_So_c::lookBack() {
    /* Nonmatching */
}

/* 000013A0-00001430       .text setAttention__10daNpc_So_cFv */
void daNpc_So_c::setAttention() {
    /* Nonmatching */
}

/* 00001430-00001524       .text setAnm__10daNpc_So_cFScb */
void daNpc_So_c::setAnm(signed char, bool) {
    /* Nonmatching */
}

/* 00001524-00001644       .text setAnmSwimSpeed__10daNpc_So_cFv */
void daNpc_So_c::setAnmSwimSpeed() {
    /* Nonmatching */
}

/* 00001644-000016E8       .text setMtx__10daNpc_So_cFv */
void daNpc_So_c::setMtx() {
    /* Nonmatching */
}

/* 000016E8-00001718       .text modeWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeWaitInit() {
    /* Nonmatching */
}

/* 00001718-0000171C       .text modeWait__10daNpc_So_cFv */
void daNpc_So_c::modeWait() {
    /* Nonmatching */
}

/* 0000171C-0000175C       .text modeHideInit__10daNpc_So_cFv */
void daNpc_So_c::modeHideInit() {
    /* Nonmatching */
}

/* 0000175C-00001778       .text modeHide__10daNpc_So_cFv */
void daNpc_So_c::modeHide() {
    /* Nonmatching */
}

/* 00001778-00001880       .text modeJumpInit__10daNpc_So_cFv */
void daNpc_So_c::modeJumpInit() {
    /* Nonmatching */
}

/* 00001880-000019F0       .text modeJump__10daNpc_So_cFv */
void daNpc_So_c::modeJump() {
    /* Nonmatching */
}

/* 000019F0-00001A6C       .text modeSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeSwimInit() {
    /* Nonmatching */
}

/* 00001A6C-00001DB8       .text modeSwim__10daNpc_So_cFv */
void daNpc_So_c::modeSwim() {
    /* Nonmatching */
}

/* 00001DB8-00001DFC       .text modeNearSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwimInit() {
    /* Nonmatching */
}

/* 00001DFC-00002144       .text modeNearSwim__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwim() {
    /* Nonmatching */
}

/* 00002144-0000217C       .text modeEventFirstWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWaitInit() {
    /* Nonmatching */
}

/* 0000217C-000022D0       .text modeEventFirstWait__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWait() {
    /* Nonmatching */
}

/* 000022D0-00002314       .text modeEventFirstInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstInit() {
    /* Nonmatching */
}

/* 00002314-000023C8       .text modeEventFirst__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirst() {
    /* Nonmatching */
}

/* 000023C8-0000240C       .text modeEventFirstEndInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEndInit() {
    /* Nonmatching */
}

/* 0000240C-000024C0       .text modeEventFirstEnd__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEnd() {
    /* Nonmatching */
}

/* 000024C0-00002504       .text modeEventEsaInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsaInit() {
    /* Nonmatching */
}

/* 00002504-00002594       .text modeEventEsa__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsa() {
    /* Nonmatching */
}

/* 00002594-000025B0       .text modeEventMapopenInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopenInit() {
    /* Nonmatching */
}

/* 000025B0-00002670       .text modeEventMapopen__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopen() {
    /* Nonmatching */
}

/* 00002670-000026B4       .text modeEventBowInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventBowInit() {
    /* Nonmatching */
}

/* 000026B4-000027F8       .text modeEventBow__10daNpc_So_cFv */
void daNpc_So_c::modeEventBow() {
    /* Nonmatching */
}

/* 000027F8-0000283C       .text modeTalkInit__10daNpc_So_cFv */
void daNpc_So_c::modeTalkInit() {
    /* Nonmatching */
}

/* 0000283C-0000289C       .text modeTalk__10daNpc_So_cFv */
void daNpc_So_c::modeTalk() {
    /* Nonmatching */
}

/* 0000289C-0000296C       .text modeDisappearInit__10daNpc_So_cFv */
void daNpc_So_c::modeDisappearInit() {
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 00002B64-00002B68       .text modeGetRupeeInit__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupeeInit() {
    /* Nonmatching */
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
}

/* 00003264-0000330C       .text checkOrder__10daNpc_So_cFv */
void daNpc_So_c::checkOrder() {
    /* Nonmatching */
}

/* 0000330C-000033F4       .text setScale__10daNpc_So_cFv */
void daNpc_So_c::setScale() {
    /* Nonmatching */
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
