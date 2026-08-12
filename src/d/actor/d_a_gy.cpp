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
#include "f_pc/f_pc_name.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_camera.h"
#include "f_pc/f_pc_draw_priority.h"
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
#include "d/d_bg_s_acch.h"

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

static const cXyz atama_cyl_offset(0.0f, 150.0f, 0.0f);
static const cXyz ago_cyl_offset(0.0f, 90.0f, 0.0f);
static const cXyz body1_cyl_offset(-10.0f, -20.0f, 0.0f);
static const cXyz body2_cyl_offset(-10.0f, -10.0f, 0.0f);
static const cXyz sebire1_cyl_offset(-10.0f, 60.0f, 0.0f);

static const __jnt_hit_data_c search_data[] = {
    {2, 30.0f, &atama_cyl_offset},
    {3, 30.0f, &ago_cyl_offset},
    {4, 60.0f, &body1_cyl_offset},
    {5, 20.0f, &sebire1_cyl_offset},
    {6, 60.0f, &body1_cyl_offset},
    {7, 50.0f, &body1_cyl_offset},
    {9, 30.0f, &body1_cyl_offset},
    {10, 30.0f, &body2_cyl_offset},
};

class daGy_HIO_c : public mDoHIO_entry_c {
public:
    daGy_HIO_c();
    virtual ~daGy_HIO_c() {}

public:
    /* 0x04 */ f32 m04;
    /* 0x08 */ f32 m08;
    /* 0x0C */ s16 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ f32 m54;
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
    /* 0x60 */ f32 m60;
    /* 0x64 */ f32 m64;
    /* 0x68 */ f32 m68;
    /* 0x6C */ f32 m6C;
    /* 0x70 */ f32 m70;
    /* 0x74 */ f32 m74;
    /* 0x78 */ f32 m78;
    /* 0x7C */ f32 m7C;
    /* 0x80 */ f32 m80;
    /* 0x84 */ f32 m84;
    /* 0x88 */ f32 m88;
    /* 0x8C */ f32 m8C;
    /* 0x90 */ f32 m90;
    /* 0x94 */ u8 m94;
    /* 0x95 */ u8 m95;
    /* 0x96 */ u8 m96;
    /* 0x97 */ u8 m97;
    /* 0x98 */ u8 m98;
    /* 0x99 */ u8 m99;
    /* 0x9A */ s16 m9A;
    /* 0x9C */ f32 m9C;
    /* 0xA0 */ f32 mA0;
    /* 0xA4 */ f32 mA4;
    /* 0xA8 */ f32 mA8;
    /* 0xAC */ f32 mAC;
    /* 0xB0 */ f32 mB0;
    /* 0xB4 */ f32 mB4;
    /* 0xB8 */ f32 mB8;
    /* 0xBC */ f32 mBC;
    /* 0xC0 */ f32 mC0;
    /* 0xC4 */ f32 mC4;
    /* 0xC8 */ f32 mC8;
    /* 0xCC */ f32 mCC;
    /* 0xD0 */ f32 mD0;
    /* 0xD4 */ f32 mD4;
    /* 0xD8 */ f32 mD8;
    /* 0xDC */ f32 mDC;
    /* 0xE0 */ f32 mE0;
    /* 0xE4 */ f32 mE4;
    /* 0xE8 */ f32 mE8;
    /* 0xEC */ f32 mEC;
    /* 0xF0 */ f32 mF0;
    /* 0xF4 */ f32 mF4;
    /* 0xF8 */ f32 mF8;
    /* 0xFC */ f32 mFC;
    /* 0x100 */ f32 m100;
    /* 0x104 */ f32 m104;
    /* 0x108 */ f32 m108;
    /* 0x10C */ s16 m10C;
    /* 0x10E */ s16 m10E;
    /* 0x110 */ s16 m110;
    /* 0x112 */ s16 m112;
    /* 0x114 */ s16 m114;
    /* 0x116 */ s16 m116;
    /* 0x118 */ s16 m118;
    /* 0x11A */ u8 m11A[9];
    /* 0x123 */ u8 m123[9];
    /* 0x12C */ f32 m12C;
    /* 0x130 */ s16 m130;
    /* 0x132 */ s16 m132;
    /* 0x134 */ f32 m134;
    /* 0x138 */ f32 m138;
    /* 0x13C */ f32 m13C;
    /* 0x140 */ s16 m140;
    /* 0x142 */ s16 m142;
    /* 0x144 */ f32 m144;
    /* 0x148 */ f32 m148;
    /* 0x14C */ f32 m14C;
    /* 0x150 */ f32 m150;
    /* 0x154 */ f32 m154;
    /* 0x158 */ f32 m158;
    /* 0x15C */ f32 m15C;
    /* 0x160 */ f32 m160;
    /* 0x164 */ s16 m164;
    /* 0x168 */ f32 m168;
    /* 0x16C */ f32 m16C;
    /* 0x170 */ f32 m170;
    /* 0x174 */ f32 m174;
    /* 0x178 */ f32 m178;
    /* 0x17C */ f32 m17C;
    /* 0x180 */ s16 m180;
    /* 0x182 */ s16 m182;
    /* 0x184 */ f32 m184;
    /* 0x188 */ f32 m188;
    /* 0x18C */ f32 m18C;
    /* 0x190 */ f32 m190;
    /* 0x194 */ f32 m194;
    /* 0x198 */ s16 m198;
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
    m8F8 = dComIfGp_getPlayer()->current.pos;
    m914 = l_HIO.m10C;
    m904 = m2BC;
    m928 = 0;
}

/* 00001A14-00001A74       .text modeWithAttackInit__6daGy_cFv */
void daGy_c::modeWithAttackInit() {
    m2B0 = 5;
    m8F8 = dComIfGp_getPlayer()->current.pos;
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
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
