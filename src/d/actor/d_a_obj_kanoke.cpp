/**
 * d_a_obj_kanoke.cpp
 * Object - Earth Temple - Coffin
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_kanoke.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"

static dCcD_SrcCps l_cps_src_body = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 50.0f, -100.0f},
        /* End    */ {0.0f, 50.0f, 100.0f},
        /* Radius */ 100.0f,
    }},
};


static dCcD_SrcCps l_cps_src_huta = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
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
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 50.0f, -100.0f},
        /* End    */ {0.0f, 50.0f, 100.0f},
        /* Radius */ 25.0f,
    }},
};


/* 000000EC-000002F4       .text __ct__13daObjKanoke_cFv */
daObjKanoke_c::daObjKanoke_c() {
    m88A = getPrmType();
    m88C = getPrmSearch();
    m88D = getPrmSwNo();
    m88E = getPrmSwNo2();
    if (m88A == 0) {
        m86C = 0.0f;
        m870 = 0.0f;
        m874 = 0.0f;
    } else {
        current.pos.y = 200.0f + home.pos.y;
        shape_angle.x = 0x4000;
        m86C = 0.0f;
        m870 = 35.0f;
        m874 = 200.0f;
    }
    m860 = 0.0f;
    m864 = 75.0f;
    m868 = 0.0f;
    m87C = 0;
    m87E = 0;
    m880 = 0;
    m882 = 0;
    for (int i = 0; i < 2; i++) {
        m824[i] = 0;
    }
    mSmokeCb.setRateOff(0);
    m88B = 0;
    m88F = 0;
    m888 = 0;
    setMtxHontai();
    PSMTXCopy(mDoMtx_stack_c::get(), mMtx);
    setMtxHuta(&current.pos);
    PSMTXCopy(mDoMtx_stack_c::get(), m2D8);
}

/* 00000644-00000664       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daObjKanoke_c*)i_this)->createHeap();
}

/* 00000664-00000700       .text _create__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::_create() {
    if (!(actor_condition & 8)) {
        if (this != NULL) {
            new (this) daObjKanoke_c();
        }
        actor_condition |= 8;
    }
    cPhs_State phs = dComIfG_resLoad(&mPhs, "Mkanoke");
    if (phs == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2400)) {
            createInit();
        } else {
            m2A4 = 0;
            m2A0 = 0;
            return cPhs_ERROR_e;
        }
    }
    return phs;
}

/* 00000700-000008BC       .text createHeap__13daObjKanoke_cFv */
BOOL daObjKanoke_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Mkanoke", 4);
    if (modelData == NULL) {
        return FALSE;
    }
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModel == NULL) {
        return FALSE;
    }
    m2A0 = new dBgW();
    if (m2A0 == NULL) {
        return FALSE;
    }
    if (m2A0->Set((cBgD_t*)dComIfG_getObjectRes("Mkanoke", 8), 1, &mMtx) == 1) {
        return FALSE;
    }
    J3DModelData* modelData2 = (J3DModelData*)dComIfG_getObjectRes("Mkanoke", 5);
    if (modelData2 == NULL) {
        return FALSE;
    }
    mpModel2 = mDoExt_J3DModel__create(modelData2, 0, 0x11020203);
    if (mpModel2 == NULL) {
        return FALSE;
    }
    m2A4 = new dBgW();
    if (m2A4 == NULL) {
        return FALSE;
    }
    if (m2A4->Set((cBgD_t*)dComIfG_getObjectRes("Mkanoke", 9), 1, &m2D8) == 1) {
        return FALSE;
    }
    return TRUE;
}

/* 000008BC-00000B28       .text createInit__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::createInit() {
    if (dComIfG_Bgsp()->Regist(m2A0, this)) {
        return cPhs_ERROR_e;
    }
    if (m88D != 0xFF) {
        if (dComIfGs_isSwitch(m88D, home.roomNo)) {
            m88B = 7;
            if (m88A == 0) {
                if (dComIfG_Bgsp()->Regist(m2A4, this)) {
                    return cPhs_ERROR_e;
                }
                m860 = 148.0f;
                m864 = 75.0f;
                m868 = 0.0f;
                m86C = 200.0f;
                m870 = 0.0f;
                m874 = 0.0f;
                m880 = -0x15E0;
            } else {
                m88F |= 2;
            }
        } else {
            if (dComIfG_Bgsp()->Regist(m2A4, this)) {
                return cPhs_ERROR_e;
            }
        }
    } else {
        if (dComIfG_Bgsp()->Regist(m2A4, this)) {
            return cPhs_ERROR_e;
        }
    }

    mStts.Init(0xFF, 0xFF, this);
    mCps0.Set(l_cps_src_body);
    mCps0.SetStts(&mStts);
    *mCps0.GetStartP() = current.pos;
    *mCps0.GetEndP() = current.pos;
    for (int i = 0; i < 3; i++) {
        mCps[i].Set(l_cps_src_huta);
        mCps[i].SetStts(&mStts);
        *mCps[i].GetStartP() = current.pos;
        *mCps[i].GetEndP() = current.pos;
    }
    cullMtx = mpModel->getBaseTRMtx();
    setMtx();
    if (m88A == 0) {
        fopAcM_setCullSizeBox(this, 120.0f, 0.0f, 210.0f, -48.0f, -110.0f, -210.0f);
    } else {
        fopAcM_setCullSizeBox(this, 120.0f, 0.0f, 210.0f, 310.0f, 520.0f, -210.0f);
    }
    return cPhs_COMPLEATE_e;
}

/* 00000B28-00000C0C       .text _delete__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_delete() {
    /* Nonmatching */
}

/* 00000C0C-00000CE0       .text _draw__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_draw() {
    /* Nonmatching */
}

/* 00000CE0-00000E7C       .text _execute__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_execute() {
    /* Nonmatching */
}

/* 00000E7C-0000122C       .text executeNormal__13daObjKanoke_cFv */
void daObjKanoke_c::executeNormal() {
    /* Nonmatching */
}

/* 0000122C-00001358       .text executeYureYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureYoko() {
    /* Nonmatching */
}

/* 00001358-00001544       .text executeOpenYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenYoko() {
    /* Nonmatching */
}

/* 00001544-000015F8       .text executeEffectYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeEffectYoko() {
    /* Nonmatching */
}

/* 000015F8-00001764       .text executeYureTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureTate() {
    /* Nonmatching */
}

/* 00001764-00001A6C       .text executeOpenTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenTate() {
    /* Nonmatching */
}

/* 00001A6C-00001B24       .text executeEffectTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeEffectTate() {
    /* Nonmatching */
}

/* 00001B24-00001B28       .text executeWait__13daObjKanoke_cFv */
void daObjKanoke_c::executeWait() {
    /* Nonmatching */
}

/* 00000000-00000000       .text getPrmType__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmType() {
    return daObj::PrmAbstract(this, 0x1, 0x0);
}

/* 00000000-00000000       .text getPrmSearch__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSearch() {
    return daObj::PrmAbstract(this, 0x5, 0x1);
}

/* 00000000-00000000       .text getPrmYure__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmYure() {
    return daObj::PrmAbstract(this, 0x1, 0x6);
}

/* 00000000-00000000       .text getPrmSwNo__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo() {
    return daObj::PrmAbstract(this, 0x8, 0x8);
}

/* 00000000-00000000       .text getPrmSwNo2__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo2() {
    return daObj::PrmAbstract(this, 0x8, 0x10);
}

/* 00001C04-00001C9C       .text setMtx__13daObjKanoke_cFv */
void daObjKanoke_c::setMtx() {
    if (!(m88F & 1)) {
        setMtxHontai();
        PSMTXCopy(mDoMtx_stack_c::get(), mpModel->getBaseTRMtx());
        PSMTXCopy(mDoMtx_stack_c::get(), mMtx);
    }
    if (!(m88F & 2)) {
        setMtxHuta(&current.pos);
        PSMTXCopy(mDoMtx_stack_c::get(), mpModel2->getBaseTRMtx());
        PSMTXCopy(mDoMtx_stack_c::get(), m2D8);
    }
}

/* 00001C9C-00001D38       .text setMtxHontai__13daObjKanoke_cFv */
void daObjKanoke_c::setMtxHontai() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(m86C, m870, m874);
    mDoMtx_stack_c::YrotM(m87E);
    mDoMtx_stack_c::transM(-m86C, -m870, -m874);
}

/* 00001D38-00001E4C       .text setMtxHuta__13daObjKanoke_cFP4cXyz */
void daObjKanoke_c::setMtxHuta(cXyz* param_0) {
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    cXyz sp08;
    PSMTXMultVec(mDoMtx_stack_c::get(), (Vec*)&m860, (Vec*)&sp08);
    mDoMtx_stack_c::transS(param_0->x + sp08.x, param_0->y + sp08.y, param_0->z + sp08.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(m86C, m870, m874);
    mDoMtx_stack_c::XrotM(m87C);
    mDoMtx_stack_c::YrotM(m87E);
    mDoMtx_stack_c::ZrotM(m880);
    mDoMtx_stack_c::transM(-m86C, -m870, -m874);
}

/* 00001E4C-00001E6C       .text daObjKanokeCreate__FPv */
static cPhs_State daObjKanokeCreate(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_create();
}

/* 00001E6C-00001E8C       .text daObjKanokeDelete__FPv */
static BOOL daObjKanokeDelete(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_delete();
}

/* 00001E8C-00001EAC       .text daObjKanokeExecute__FPv */
static BOOL daObjKanokeExecute(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_execute();
}

/* 00001EAC-00001ECC       .text daObjKanokeDraw__FPv */
static BOOL daObjKanokeDraw(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_draw();
}

/* 00001ECC-00001ED4       .text daObjKanokeIsDelete__FPv */
static BOOL daObjKanokeIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObjKanokeMethodTable = {
    (process_method_func)daObjKanokeCreate,
    (process_method_func)daObjKanokeDelete,
    (process_method_func)daObjKanokeExecute,
    (process_method_func)daObjKanokeIsDelete,
    (process_method_func)daObjKanokeDraw,
};

actor_process_profile_definition g_profile_Obj_Kanoke = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Kanoke_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjKanoke_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Kanoke_e,
    /* Actor SubMtd */ &daObjKanokeMethodTable,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
