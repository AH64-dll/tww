/**
 * d_a_gy.cpp
 * Enemy - Gyorg
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_gy.h"
#include "d/actor/d_a_gy_ctrl.h"
#include "d/actor/d_a_ship.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_func.h"
#include "d/d_particle.h"
#include "d/d_s_play.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_printf.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_camera.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "d/actor/d_a_player.h"

static dCcD_SrcSph l_sph_head_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};


static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};


static dCcD_SrcCps l_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};

#include "d/d_jnt_hit.h"

static Vec atama_cyl_offset[] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 150.0f, 0.0f},
};
static Vec ago_cyl_offset[] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 90.0f, 0.0f},
};
static Vec body1_cyl_offset[] = {
    {-10.0f, -20.0f, 0.0f},
    {40.0f, -20.0f, 0.0f},
};
static Vec body2_cyl_offset[] = {
    {-10.0f, -10.0f, 0.0f},
    {40.0f, -10.0f, 0.0f},
};
static Vec sebire1_cyl_offset[] = {
    {-10.0f, 60.0f, 0.0f},
    {150.0f, -100.0f, 0.0f},
};

static __jnt_hit_data_c search_data[] = {
    {0, 2, 30.0f, atama_cyl_offset},
    {0, 3, 30.0f, ago_cyl_offset},
    {0, 4, 60.0f, body1_cyl_offset},
    {0, 5, 20.0f, sebire1_cyl_offset},
    {0, 6, 60.0f, body1_cyl_offset},
    {0, 7, 50.0f, body1_cyl_offset},
    {0, 9, 30.0f, body1_cyl_offset},
    {0, 10, 30.0f, body2_cyl_offset},
};

static daGy_HIO_c l_HIO;

const u32 daGy_c::m_heapsize = 0x3FA0;
static const char m_arc_name[] = "Gy";

static void (daGy_c::*mode_proc[])() = {
    &daGy_c::modeDive,
    &daGy_c::modeCircle,
    &daGy_c::modeAttack,
    &daGy_c::modeAttackPlayer,
    &daGy_c::modeAttackBack,
    &daGy_c::modeWithAttack,
    &daGy_c::modeWithCircle,
    &daGy_c::modeDamage,
    &daGy_c::modeDelete,
    &daGy_c::modeDeleteBomb,
};

/* 000000EC-000003CC       .text __ct__10daGy_HIO_cFv */
daGy_HIO_c::daGy_HIO_c() {
    m0C = 0xC8;
    m04 = 1.0f;
    m08 = 0.9f;
    m10 = 200.0f;
    m14 = 300.0f;
    m18 = 2.0f;
    m1C = 2.0f;
    m24 = 15.0f;
    m20 = 0.0f;
    m28 = -80.0f;
    m2C = -50.0f;
    m30 = -150.0f;
    m34 = -40.0f;
    m38 = -100.0f;
    m3C = -350.0f;
    m48 = 10.0f;
    m4C = 20.0f;
    m50 = 30.0f;
    m54 = 40.0f;
    m58 = 15.0f;
    m5C = 5.0f;
    m60 = 40.0f;
    m64 = 20.0f;
    m68 = 55.0f;
    m6C = 10.0f;
    m70 = 20.0f;
    m198 = 1;
    m40 = 60.0f;
    m44 = 2500.0f;
    m74 = 70.0f;
    m78 = 70.0f;
    m7C = 80.0f;
    m80 = 70.0f;
    m84 = 70.0f;
    m88 = 110.0f;
    m8C = 100.0f;
    m90 = 1.0f;
    m9C = 5000.0f;
    mA4 = 180.0f;
    mA8 = -400.0f;
    m94 = m95 = m96 = m97 = m98 = m99 = 0;
    mA0 = -500.0f;
    mAC = -80.0f;
    mB4 = -25.0f;
    mB0 = 20.0f;
    mB8 = 0.0f;
    mBC = 0.0f;
    mC0 = 0.0f;
    mC4 = 8.0f;
    m178 = 0.5f;
    mC8 = 30.0f;
    mD4 = 80.0f;
    mD8 = 0.0f;
    mDC = 0.0f;
    mE0 = 0.0f;
    mE4 = 0.0f;
    mE8 = 0.0f;
    mEC = 0.0f;
    mF0 = 0.0f;
    mF4 = 120.0f;
    mF8 = 0.0f;
    mFC = 0.0f;
    m100 = 300.0f;
    mCC = 2.0f;
    mD0 = 20.0f;
    m104 = -40.0f;
    m108 = 25.0f;
    m10C = 0x78;
    m10E = 0x3C;
    m110 = 0x78;
    m112 = 0xB4;
    m114 = 0x168;
    m116 = 0x5A;
    m118 = 0xF0;
    m188 = 0.2f;
    m12C = 10.0f;
    m144 = 400.0f;
    m148 = 350.0f;
    m150 = 60.0f;
    m154 = 60.0f;
    m158 = 40.0f;
    for (s32 i = 2; i < 0xB; i++) {
        m11A[i] = 0;
    }
    m130 = 0x64;
    m132 = 0x12C;
    m134 = 45.0f;
    m138 = 45.0f;
    m13C = 30.0f;
    m15C = 45.0f;
    m160 = 10.0f;
    m140 = 0x1500;
    m142 = 0x800;
    m164 = 0x5A;
    m168 = -1000.0f;
    m16C = -100.0f;
    m170 = 50.0f;
    m174 = 0.1f;
    m17C = 0.1f;
    m184 = 4000.0f;
    m180 = 0x2000;
    m18C = 3000.0f;
    m190 = 200.0f;
    m194 = 3000.0f;
}

/* 000004C0-0000159C       .text genMessage__10daGy_HIO_cFP11JORMContext */
void daGy_HIO_c::genMessage(JORMContext*) {
    /* Nonmatching */
}

/* 00000450-0000049C       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daGy_c* i_this = reinterpret_cast<daGy_c*>(model->getUserArea());
        if (i_this) {
            i_this->_nodeControl(node, model);
        }
    }
    return TRUE;
}

/* 00000888-000008A8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daGy_c*>(i_this)->_createHeap();
}

/* 00000FC4-00000FDC       .text modeDiveInit__6daGy_cFv */
void daGy_c::modeDiveInit() {
    m2B0 = 0;
    m508 = 0.0f;
}

/* 00001F20-00001F40       .text modeAttackPlayerInit__6daGy_cFv */
void daGy_c::modeAttackPlayerInit() {
    m2B0 = 3;
    mD15 = 2;
    m928 = 0;
    m924 = 0;
}

/* 000019AC-00001A14       .text modeAttackInit__6daGy_cFv */
void daGy_c::modeAttackInit() {
    m2B0 = 2;
    mD15 = 3;
    m8F8 = dComIfGp_getPlayer(0)->current.pos;
    m914 = l_HIO.m10C;
    m904 = m2BC;
    m928 = 0;
}

/* 00001A14-00001A74       .text modeWithAttackInit__6daGy_cFv */
void daGy_c::modeWithAttackInit() {
    m2B0 = 5;
    m8F8 = dComIfGp_getPlayer(0)->current.pos;
    m914 = l_HIO.m10C;
    m904 = m2BC;
    m928 = 0;
}

/* 000022F8-00002400       .text modeAttackBackInit__6daGy_cFv */
void daGy_c::modeAttackBackInit() {
    /* Nonmatching */
}

/* 00002560-000025F0       .text modeDamageInit__6daGy_cFv */
void daGy_c::modeDamageInit() {
    /* Nonmatching */
}

/* 00002754-000028B8       .text modeDeleteInit__6daGy_cFv */
void daGy_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 00002998-00002A70       .text modeDeleteBombInit__6daGy_cFv */
void daGy_c::modeDeleteBombInit() {
    /* Nonmatching */
}

/* 000012DC-0000141C       .text modeCircleInit__6daGy_cFv */
void daGy_c::modeCircleInit() {
    /* Nonmatching */
}

/* 000016E4-00001788       .text modeWithCircleInit__6daGy_cFv */
void daGy_c::modeWithCircleInit() {
    /* Nonmatching */
}

/* 00000C30-00000C7C       .text setAnm__6daGy_cFv */
void daGy_c::setAnm() {
    /* Nonmatching */
}

/* 00000F3C-00000FC4       .text setAimSpeedF__6daGy_cFv */
void daGy_c::setAimSpeedF() {
    /* Nonmatching */
}

/* 00000FDC-000012DC       .text modeDive__6daGy_cFv */
void daGy_c::modeDive() {
    /* Nonmatching */
}

/* 0000141C-000016E4       .text modeCircle__6daGy_cFv */
void daGy_c::modeCircle() {
    /* Nonmatching */
}

/* 00001788-000019AC       .text modeWithCircle__6daGy_cFv */
void daGy_c::modeWithCircle() {
    /* Nonmatching */
}

/* 00001A74-00001D60       .text modeWithAttack__6daGy_cFv */
void daGy_c::modeWithAttack() {
    /* Nonmatching */
}

/* 00001D60-00001F20       .text modeAttack__6daGy_cFv */
void daGy_c::modeAttack() {
    /* Nonmatching */
}

/* 00001F40-000022F8       .text modeAttackPlayer__6daGy_cFv */
void daGy_c::modeAttackPlayer() {
    /* Nonmatching */
}

/* 00002400-00002560       .text modeAttackBack__6daGy_cFv */
void daGy_c::modeAttackBack() {
    /* Nonmatching */
}

/* 000025F0-00002754       .text modeDamage__6daGy_cFv */
void daGy_c::modeDamage() {
    /* Nonmatching */
}

/* 000028B8-00002998       .text modeDelete__6daGy_cFv */
void daGy_c::modeDelete() {
    /* Nonmatching */
}

/* 00002A70-00002CBC       .text modeDeleteBomb__6daGy_cFv */
void daGy_c::modeDeleteBomb() {
    /* Nonmatching */
}

/* 00002CBC-00002E24       .text modeProcCall__6daGy_cFv */
void daGy_c::modeProcCall() {
    /* Nonmatching */
}

/* 00002E24-00003004       .text createWave__6daGy_cFv */
void daGy_c::createWave() {
    /* Nonmatching */
}

/* 00003004-00003268       .text setWave__6daGy_cFv */
void daGy_c::setWave() {
    /* Nonmatching */
}

/* 00003268-000032E4       .text lineCheck__6daGy_cFP4cXyzP4cXyz */
void daGy_c::lineCheck(cXyz* param_0, cXyz* param_1) {
    /* Nonmatching */
}

/* 000032E4-000038EC       .text checkTgHit__6daGy_cFv */
void daGy_c::checkTgHit() {
    /* Nonmatching */
}

/* 000038EC-000039AC       .text getWaterY__6daGy_cFv */
void daGy_c::getWaterY() {
    /* Nonmatching */
}

/* 000039AC-00004264       .text _execute__6daGy_cFv */
bool daGy_c::_execute() {
    /* Nonmatching */
}

/* 00004264-00004560       .text drawDebug__6daGy_cFv */
void daGy_c::drawDebug() {
    /* Nonmatching */
}

/* 00004560-000046C8       .text _draw__6daGy_cFv */
bool daGy_c::_draw() {
    /* Nonmatching */
}

/* 000046C8-00004920       .text createInit__6daGy_cFv */
void daGy_c::createInit() {
    /* Nonmatching */
}

/* 00004920-00004A80       .text _create__6daGy_cFv */
cPhs_State daGy_c::_create() {
    /* Nonmatching */
}

/* 00004A80-00005A80       .text __ct__6daGy_cFv */
daGy_c::daGy_c() {}

/* 00005A80-00005AD4       .text _delete__6daGy_cFv */
bool daGy_c::_delete() {
    /* Nonmatching */
}

static cPhs_State daGyCreate(void* i_this) {
    return ((daGy_c*)i_this)->_create();
}

static BOOL daGyDelete(void* i_this) {
    return ((daGy_c*)i_this)->_delete();
}

static BOOL daGyExecute(void* i_this) {
    return ((daGy_c*)i_this)->_execute();
}

static BOOL daGyDraw(void* i_this) {
    return ((daGy_c*)i_this)->_draw();
}

static BOOL daGyIsDelete(void*) {
    return TRUE;
}

static actor_method_class daGyMethodTable = {
    (process_method_func)daGyCreate,
    (process_method_func)daGyDelete,
    (process_method_func)daGyExecute,
    (process_method_func)daGyIsDelete,
    (process_method_func)daGyDraw,
};

actor_process_profile_definition g_profile_GY = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ fpcNm_GY_e,
    /* ProcSubMtd   */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daGy_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* LeafSubMtd   */ &g_fopAc_Method.base,
    /* Priority     */ fpcDwPi_GY_e,
    /* ActorSubMtd  */ &daGyMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
