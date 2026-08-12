/**
 * d_a_npc_mn.cpp
 * NPC - Manny
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_mn.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "m_Do/m_Do_ext.h"

static const char* l_arcname_tbl[] = { "Mn" };
static const u16 l_bmd_ix_tbl[] = { 2 };
static const u16 l_etc_bmd_ix_tbl[] = { 1 };
static const u16 l_bck_ix_tbl[] = { 6, 10, 4, 5, 11, 7, 8, 9 };
static const u16 l_btp_ix_tbl[] = { 3 };

/* 00000078-00000230       .text __ct__9daNpcMn_cFv */
daNpcMn_c::daNpcMn_c() {
    m7B5 = 0;
    m7B4 = 0;
    m77C = 0.0f;
    m798 = 0;
    m780 = -1.0f;
    m7BD = 0;
    m794 = 1;
    m7A0 = home.angle.y;
    m7B8 = 0;
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
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[m7B8]),
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
static s16 daNpcMn_XyCheckCB(void*, int) {
    /* Nonmatching */
}

/* 00000C00-00000F3C       .text createInit__9daNpcMn_cFv */
cPhs_State daNpcMn_c::createInit() {
    /* Nonmatching */
}

/* 00000F3C-00000FE4       .text _delete__9daNpcMn_cFv */
bool daNpcMn_c::_delete() {
    /* Nonmatching */
}

/* 00000FE4-00001154       .text _draw__9daNpcMn_cFv */
bool daNpcMn_c::_draw() {
    /* Nonmatching */
}

/* 00001154-00001344       .text _execute__9daNpcMn_cFv */
bool daNpcMn_c::_execute() {
    /* Nonmatching */
}

/* 00001344-000013B4       .text executeCommon__9daNpcMn_cFv */
void daNpcMn_c::executeCommon() {
    /* Nonmatching */
}

/* 000013B4-0000140C       .text executeSetMode__9daNpcMn_cFUc */
void daNpcMn_c::executeSetMode(unsigned char) {
    /* Nonmatching */
}

/* 0000140C-00001518       .text executeWaitInit__9daNpcMn_cFv */
void daNpcMn_c::executeWaitInit() {
    /* Nonmatching */
}

/* 00001518-000017CC       .text executeWait__9daNpcMn_cFv */
void daNpcMn_c::executeWait() {
    /* Nonmatching */
}

/* 000017CC-000017D4       .text executeTalkInit__9daNpcMn_cFv */
void daNpcMn_c::executeTalkInit() {
    /* Nonmatching */
}

/* 000017D4-0000184C       .text executeTalk__9daNpcMn_cFv */
void daNpcMn_c::executeTalk() {
    /* Nonmatching */
}

/* 0000184C-0000185C       .text executeTalk3Init__9daNpcMn_cFv */
void daNpcMn_c::executeTalk3Init() {
    /* Nonmatching */
}

/* 0000185C-0000191C       .text executeTalk3__9daNpcMn_cFv */
void daNpcMn_c::executeTalk3() {
    /* Nonmatching */
}

/* 0000191C-00001948       .text executeWalkInit__9daNpcMn_cFv */
void daNpcMn_c::executeWalkInit() {
    /* Nonmatching */
}

/* 00001948-00001BD4       .text executeWalk__9daNpcMn_cFv */
void daNpcMn_c::executeWalk() {
    /* Nonmatching */
}

/* 00001BD4-00001D18       .text executeTurnInit__9daNpcMn_cFv */
void daNpcMn_c::executeTurnInit() {
    /* Nonmatching */
}

/* 00001D18-00001DE8       .text executeTurn__9daNpcMn_cFv */
void daNpcMn_c::executeTurn() {
    /* Nonmatching */
}

/* 00001DE8-00001E80       .text checkOrder__9daNpcMn_cFv */
void daNpcMn_c::checkOrder() {
    /* Nonmatching */
}

/* 00001E80-00001F00       .text eventOrder__9daNpcMn_cFv */
void daNpcMn_c::eventOrder() {
    /* Nonmatching */
}

/* 00001F00-00001F74       .text eventMove__9daNpcMn_cFv */
void daNpcMn_c::eventMove() {
    /* Nonmatching */
}

/* 00001F74-00002194       .text privateCut__9daNpcMn_cFv */
void daNpcMn_c::privateCut() {
    /* Nonmatching */
}

/* 00002194-0000226C       .text eventMesSetInit__9daNpcMn_cFi */
void daNpcMn_c::eventMesSetInit(int) {
    /* Nonmatching */
}

/* 0000226C-000022A0       .text eventMesSet__9daNpcMn_cFv */
void daNpcMn_c::eventMesSet() {
    /* Nonmatching */
}

/* 000022A0-000022F8       .text eventGetItemInit__9daNpcMn_cFv */
void daNpcMn_c::eventGetItemInit() {
    /* Nonmatching */
}

/* 000022F8-00002358       .text eventWaitInit__9daNpcMn_cFi */
void daNpcMn_c::eventWaitInit(int) {
    /* Nonmatching */
}

/* 00002358-000023E8       .text eventWait__9daNpcMn_cFi */
void daNpcMn_c::eventWait(int) {
    /* Nonmatching */
}

/* 000023E8-00002448       .text eventSwOnInit__9daNpcMn_cFi */
void daNpcMn_c::eventSwOnInit(int) {
    /* Nonmatching */
}

/* 00002448-000024AC       .text eventSwOn__9daNpcMn_cFv */
void daNpcMn_c::eventSwOn() {
    /* Nonmatching */
}

/* 000024AC-00002540       .text eventHatchInit__9daNpcMn_cFv */
void daNpcMn_c::eventHatchInit() {
    /* Nonmatching */
}

/* 00002540-00002578       .text eventHatch__9daNpcMn_cFv */
void daNpcMn_c::eventHatch() {
    /* Nonmatching */
}

/* 00002578-000025EC       .text eventBikkuriInit__9daNpcMn_cFi */
void daNpcMn_c::eventBikkuriInit(int) {
    /* Nonmatching */
}

/* 000025EC-00002644       .text eventBikkuri__9daNpcMn_cFv */
void daNpcMn_c::eventBikkuri() {
    /* Nonmatching */
}

/* 00002644-0000266C       .text eventTurnInit__9daNpcMn_cFv */
void daNpcMn_c::eventTurnInit() {
    /* Nonmatching */
}

/* 0000266C-000027B4       .text eventTurn__9daNpcMn_cFi */
void daNpcMn_c::eventTurn(int) {
    /* Nonmatching */
}

/* 000027B4-000027DC       .text eventWalkInit__9daNpcMn_cFv */
void daNpcMn_c::eventWalkInit() {
    /* Nonmatching */
}

/* 000027DC-0000293C       .text eventWalk__9daNpcMn_cFv */
void daNpcMn_c::eventWalk() {
    /* Nonmatching */
}

/* 0000293C-00002964       .text eventLookInit__9daNpcMn_cFv */
void daNpcMn_c::eventLookInit() {
    /* Nonmatching */
}

/* 00002964-00002988       .text eventLook__9daNpcMn_cFv */
void daNpcMn_c::eventLook() {
    /* Nonmatching */
}

/* 00002988-00002A90       .text eventJumpInit__9daNpcMn_cFi */
void daNpcMn_c::eventJumpInit(int) {
    /* Nonmatching */
}

/* 00002A90-00002AE8       .text eventJump__9daNpcMn_cFv */
void daNpcMn_c::eventJump() {
    /* Nonmatching */
}

/* 00002AE8-00002C30       .text talk2__9daNpcMn_cFi */
void daNpcMn_c::talk2(int) {
    /* Nonmatching */
}

/* 00002C30-00002D68       .text talk3__9daNpcMn_cFi */
void daNpcMn_c::talk3(int) {
    /* Nonmatching */
}

/* 00002D68-00002DB8       .text next_msgStatus__9daNpcMn_cFPUl */
u16 daNpcMn_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00002DB8-00002F7C       .text getMsg__9daNpcMn_cFv */
u32 daNpcMn_c::getMsg() {
    /* Nonmatching */
}

/* 00002F7C-00002F8C       .text getMsg3__9daNpcMn_cFv */
void daNpcMn_c::getMsg3() {
    /* Nonmatching */
}

/* 00002F8C-00002F90       .text chkMsg__9daNpcMn_cFv */
void daNpcMn_c::chkMsg() {
    /* Nonmatching */
}

/* 00002F90-00002F98       .text setMessage__9daNpcMn_cFUl */
void daNpcMn_c::setMessage(unsigned long) {
    /* Nonmatching */
}

/* 00002F98-0000302C       .text setAnmFromMsgTag__9daNpcMn_cFv */
void daNpcMn_c::setAnmFromMsgTag() {
    /* Nonmatching */
}

/* 0000302C-0000303C       .text getPrmNpcNo__9daNpcMn_cFv */
s8 daNpcMn_c::getPrmNpcNo() {
    /* Nonmatching */
}

/* 0000303C-00003068       .text getPrmRailID__9daNpcMn_cFv */
void daNpcMn_c::getPrmRailID() {
    /* Nonmatching */
}

/* 00003068-00003094       .text getPrmSwitchBit__9daNpcMn_cFv */
s32 daNpcMn_c::getPrmSwitchBit() {
    /* Nonmatching */
}

/* 00003094-000030C0       .text getPrmSwitchBit2__9daNpcMn_cFv */
void daNpcMn_c::getPrmSwitchBit2() {
    /* Nonmatching */
}

/* 000030C0-00003148       .text setMtx__9daNpcMn_cFv */
void daNpcMn_c::setMtx() {
    /* Nonmatching */
}

/* 00003148-00003478       .text chkAttention__9daNpcMn_cFv */
void daNpcMn_c::chkAttention() {
    /* Nonmatching */
}

/* 00003478-000035C4       .text lookBack__9daNpcMn_cFv */
void daNpcMn_c::lookBack() {
    /* Nonmatching */
}

/* 000035C4-000036D0       .text initTexPatternAnm__9daNpcMn_cFb */
BOOL daNpcMn_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 000036D0-0000373C       .text playTexPatternAnm__9daNpcMn_cFv */
void daNpcMn_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 0000373C-000037F8       .text playAnm__9daNpcMn_cFv */
void daNpcMn_c::playAnm() {
    /* Nonmatching */
}

/* 000037F8-000038C8       .text setAnm__9daNpcMn_cFUcif */
void daNpcMn_c::setAnm(unsigned char, int, float) {
    /* Nonmatching */
}

/* 000038C8-00003974       .text setAnmTbl__9daNpcMn_cFP9sMnAnmDat */
void daNpcMn_c::setAnmTbl(sMnAnmDat*) {
    /* Nonmatching */
}

/* 00003974-0000397C       .text XyCheckCB__9daNpcMn_cFi */
void daNpcMn_c::XyCheckCB(int) {
    /* Nonmatching */
}

/* 0000397C-000039E0       .text getRand__9daNpcMn_cFi */
void daNpcMn_c::getRand(int) {
    /* Nonmatching */
}

/* 000039E0-00003A58       .text setCollision__9daNpcMn_cFP8dCcD_Cyl4cXyzff */
void daNpcMn_c::setCollision(dCcD_Cyl*, cXyz, float, float) {
    /* Nonmatching */
}

/* 00003A58-00003AC4       .text chkEndEvent__9daNpcMn_cFv */
void daNpcMn_c::chkEndEvent() {
    /* Nonmatching */
}

/* 00003AC4-00003B38       .text chkPosNo__9daNpcMn_cFv */
s8 daNpcMn_c::chkPosNo() {
    /* Nonmatching */
}

/* 00003B38-00003CD8       .text getPosNo__9daNpcMn_cFv */
u8 daNpcMn_c::getPosNo() {
    /* Nonmatching */
}

/* 00003CD8-00003CE8       .text isChangePos__9daNpcMn_cFUc */
BOOL daNpcMn_c::isChangePos(unsigned char) {
    /* Nonmatching */
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
