/**
 * d_a_npc_kg1.cpp
 * NPC - Salvatore (Squid-Hunt/"Sploosh Kaboom" Minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kg1.h"
#include "f_op/f_op_camera.h"
#include "d/d_lib.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 40.0f,
        /* Height */ 160.0f,
    }},
};


/* 000000EC-000001E0       .text __ct__15daNpc_Kg1_HIO_cFv */
daNpc_Kg1_HIO_c::daNpc_Kg1_HIO_c() {
    mNo = -1;
    field_0x8 = -1;
    mHio[0].m04 = 0.0f;
    mHio[0].mMaxHeadX = 0x9C4;
    mHio[0].mMaxHeadY = 0x1B58;
    mHio[0].mMaxBackboneX = 0x7D0;
    mHio[0].mMaxBackboneY = 0x1F40;
    mHio[0].mMinHeadX = -0x9C4;
    mHio[0].mMinHeadY = -0x1B58;
    mHio[0].mMinBackboneX = -0x7D0;
    mHio[0].mMinBackboneY = -0x1F40;
    mHio[0].mMaxTurnStep = 0x3E8;
    mHio[0].mMaxHeadTurnVel = 0x7D0;
    mHio[0].mAttnYOffset = 35.0f;
    mHio[0].mMaxAttnAngleY = 0x4000;
    mHio[0].m22 = 0;
    mHio[0].mMaxAttnDistXZ = 400.0f;
    field_0xC = 0;
    field_0x38 = 0;
    field_0x39 = 0;
}

static daNpc_Kg1_HIO_c l_HIO;
const char daNpc_Kg1_c::m_arcname[] = "Kg";
cXyz daNpc_Kg1_c::m_camera_ctr(-200.0f, 140.0f, 85.0f);
cXyz daNpc_Kg1_c::m_camera_eye(-117.0f, 92.0f, 344.0f);
const f32 daNpc_Kg1_c::m_camera_fovy = 40.0f;

/* 000001E0-00000428       .text daNpc_Kg1_nodeCallBack__FP7J3DNodei */
static BOOL daNpc_Kg1_nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000464-00000688       .text lookBack__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::lookBack() {
    /* Nonmatching */
}

/* 00000688-000007D8       .text chkAttention__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::chkAttention() {
    /* Nonmatching */
}

static const int l_btp_ix_tbl[] = {9, 11, 13, 12};

/* 000007D8-000008D8       .text initTexPatternAnm__11daNpc_Kg1_cFib */
BOOL daNpc_Kg1_c::initTexPatternAnm(int param_2, bool param_3) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_eye_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arcname, l_btp_ix_tbl[param_2]);
    JUT_ASSERT(0x1CC, m_eye_tex_pattern != 0);
    BOOL ret = m6F8.init(modelData, m_eye_tex_pattern, 1, 2, 1.0f, 0, -1, param_3, FALSE);
    if (ret == FALSE) {
        return FALSE;
    }
    m720 = 0;
    m72C = 0;
    return TRUE;
}

/* 000008D8-00000944       .text playTexPatternAnm__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::playTexPatternAnm() {
    if (!cLib_calcTimer(&m72C)) {
        if (m720 >= m_eye_tex_pattern->getFrameMax()) {
            m720 -= m_eye_tex_pattern->getFrameMax();
            m72C = 0x78;
        } else {
            m720++;
        }
    }
}

/* 00000944-000009E8       .text set_mtx__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::set_mtx() {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    m6C4->setBaseScale(scale);
}

/* 000009E8-00000A08       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Kg1_c*)i_this)->CreateHeap();
}

/* 00000A08-00000D34       .text CreateHeap__11daNpc_Kg1_cFv */
BOOL daNpc_Kg1_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000D34-00000EF0       .text CreateInit__11daNpc_Kg1_cFv */
cPhs_State daNpc_Kg1_c::CreateInit() {
    /* Nonmatching */
}

/* 00000EF0-00000FE8       .text eventOrder__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::eventOrder() {
    /* Nonmatching */
}

/* 00000FE8-000010C4       .text checkOrder__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::checkOrder() {
    /* Nonmatching */
}

/* 000010C4-00001188       .text kg1_talk_camera__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::kg1_talk_camera() {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (m751 && camera != NULL) {
        camera->mCamera.Stay();
        camera->mCamera.Set(m_camera_ctr, m_camera_eye, m_camera_fovy, 0);
        camera->mCamera.Reset();
        camera->mCamera.SetTrimSize(1);
    }
}

/* 00001188-000011D4       .text wait_action_init__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::wait_action_init() {
    clr_seq_flag();
    mAction = &daNpc_Kg1_c::wait_action;
}

/* 000011D4-00001858       .text wait_action__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::wait_action() {
    /* Nonmatching */
}

/* 00001858-00001878       .text clr_seq_flag__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::clr_seq_flag() {
    m772 = 0;
    m773 = 0;
    m774 = 0;
    m775 = 0;
    m776 = 0;
    m777 = 0;
}

/* 00001878-000019B4       .text getMsg__11daNpc_Kg1_cFv */
u32 daNpc_Kg1_c::getMsg() {
    /* Nonmatching */
}

/* 000019B4-00001C7C       .text next_msgStatus__11daNpc_Kg1_cFPUl */
u16 daNpc_Kg1_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

static const u8 anm_atr[] = { 0x01, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A };

/* 00001C7C-00001CB8       .text anmAtr__11daNpc_Kg1_cFUs */
void daNpc_Kg1_c::anmAtr(u16 i_msgStatus) {
    if (i_msgStatus == 6) {
        u8 anime = dComIfGp_getMesgAnimeAttrInfo();
        if (anime < 9) {
            m74D = anm_atr[anime];
            dComIfGp_clearMesgAnimeAttrInfo();
        }
    }
}

/* 00001CB8-00001E60       .text daNpc_Kg1_bcks_setAnm__FPCcP14mDoExt_McaMorfPScPScPScPCiPC14dLib_anm_prm_c */
void daNpc_Kg1_bcks_setAnm(const char*, mDoExt_McaMorf*, signed char*, signed char*, signed char*, const int*, const dLib_anm_prm_c*) {
    /* Nonmatching */
}

/* 00001E60-00001F8C       .text setAnm__11daNpc_Kg1_cFv */
void daNpc_Kg1_c::setAnm() {
    /* Nonmatching */
}

/* 00001F8C-00001FAC       .text daNpc_Kg1Create__FPv */
static cPhs_State daNpc_Kg1Create(void* i_this) {
    return ((daNpc_Kg1_c*)i_this)->_create();
}

/* 00001FAC-0000203C       .text _create__11daNpc_Kg1_cFv */
cPhs_State daNpc_Kg1_c::_create() {
    fopAcM_ct(this, daNpc_Kg1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, m_arcname);
    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x10000) != 0) {
            return CreateInit();
        }
        state = cPhs_ERROR_e;
    }
    return state;
}

/* 00002480-0000250C       .text daNpc_Kg1Delete__FPv */
static BOOL daNpc_Kg1Delete(void* i_this) {
    daNpc_Kg1_c* self = static_cast<daNpc_Kg1_c*>(i_this);
    dComIfG_resDelete(&self->mPhs, daNpc_Kg1_c::m_arcname);
    if (self->heap != NULL && self->mpMorf != NULL) {
        self->mpMorf->stopZelAnime();
    }
    if (l_HIO.field_0x8 >= 0) {
        l_HIO.field_0x8--;
        if (l_HIO.field_0x8 < 0) {
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return TRUE;
}

/* 0000250C-00002648       .text daNpc_Kg1Execute__FPv */
static BOOL daNpc_Kg1Execute(void*) {
    /* Nonmatching */
}

/* 00002648-000027CC       .text daNpc_Kg1Draw__FPv */
static BOOL daNpc_Kg1Draw(void*) {
    /* Nonmatching */
}

/* 000027CC-000027D4       .text daNpc_Kg1IsDelete__FPv */
static BOOL daNpc_Kg1IsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_Kg1MethodTable = {
    (process_method_func)daNpc_Kg1Create,
    (process_method_func)daNpc_Kg1Delete,
    (process_method_func)daNpc_Kg1Execute,
    (process_method_func)daNpc_Kg1IsDelete,
    (process_method_func)daNpc_Kg1Draw,
};

actor_process_profile_definition g_profile_NPC_KG1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KG1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kg1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KG1_e,
    /* Actor SubMtd */ &daNpc_Kg1MethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
