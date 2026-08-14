/**
 * d_a_obj_vyasi.cpp
 * Object - Palm tree blowing in the wind (Gale Isle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_vyasi.h"
#include "d/d_a_obj.h"
#include "d/d_kankyo.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_math.h"
#include "m_Do/m_Do_ext.h"

namespace daObjVyasi {
namespace {
/* 00000000-00000084       .rodata L_attr__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@ */
struct Attr_c {
    /* 0x00 */ f32 m00;    // 1.0f
    /* 0x04 */ f32 m04;    // 79.0f
    /* 0x08 */ f32 m08;    // 250.0f
    /* 0x0C */ f32 m0C;    // 0.0f
    /* 0x10 */ f32 m10;    // 0.0f
    /* 0x14 */ f32 m14;    // 0.0f
    /* 0x18 */ f32 m18;    // 0.4f
    /* 0x1C */ f32 m1C;    // 1.5f
    /* 0x20 */ u32 m20;    // 0x00020000
    /* 0x24 */ f32 m24;    // 700.0f
    /* 0x28 */ f32 m28;    // 1700.0f
    /* 0x2C */ f32 m2C;    // 1700.0f
    /* 0x30 */ u8 m30[0x84 - 0x30];
};

static const Attr_c L_attr = {
    1.0f, 79.0f, 250.0f, 0.0f, 0.0f, 0.0f, 0.4f, 1.5f, 0x00020000, 700.0f, 1700.0f, 1700.0f,
    {},
};
} // namespace

/* 00000084-000000C8       .rodata M_cyl_src__10daObjVyasi */
static const dCcD_SrcCyl M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0xFF1DFEFF,
        /* SrcObjTg  SPrm    */ 0xF,
        /* SrcObjCo  SPrm    */ 0x79,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 3,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
        /* Height */ 200.0f,
    }},
};

/* 000000C8-00000114       .rodata M_cps_src__10daObjVyasi */
static const dCcD_SrcCps M_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0xFF1DFEFF,
        /* SrcObjTg  SPrm    */ 0xF,
        /* SrcObjCo  SPrm    */ 0x79,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0x100,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
    }},
};

/* 00000114-00000154       .rodata M_sph_src__10daObjVyasi */
static const dCcD_SrcSph M_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0x79,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0x100,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 100.0f,
    }},
};

/* 00000030-0000003E       .data joint_kind_table__10daObjVyasi */
static u8 joint_kind_table[14] = {2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
} // namespace daObjVyasi

/* 000000EC-0000015C       .text SetStopJointAnimation__Q210daObjVyasi5Act_cFP18J3DAnmTransformKeyff */
BOOL daObjVyasi::Act_c::SetStopJointAnimation(J3DAnmTransformKey* i_bck, float i_morf, float i_speed) {
    if(i_bck != NULL) {
        mpMorf->setAnm(i_bck, 0, i_speed, i_morf, 0.0f, -1.0f, NULL);
        m19C4 = 1;
        return TRUE;
    }
    return FALSE;
}

/* 0000015C-00000194       .text PlayStopJointAnimation__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::PlayStopJointAnimation() {
    return mpMorf->play(NULL, 0, 0) == 0;
}

/* 00000194-0000021C       .text set_first_process__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_first_process() {
    s32 swNo = daObj::PrmAbstract<int>(this, 8, 0);
    process_init(dComIfGs_isSwitch(swNo, home.roomNo) ? 4 : 1);
    mNormalCounter = 0;
    m19D4 = 1.0f;
    shape_angle.y += 0x8000;
}

/* 0000021C-000005B8       .text set_collision__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_collision() {
    if (mCyl.ChkTgHit()) {
        daObj::HitSeStart(&current.pos, current.roomNo, &mCyl, 7);
        daObj::HitEff_kikuzu(this, &mCyl);
        dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
        mCyl.ClrTgHit();
    } else {
        mCyl.SetC(current.pos);
        mCyl.SetR(79.0f);
        mCyl.SetH(250.0f);
        dComIfG_Ccsp()->Set(&mCyl);
    }

    for (int i = 0; i < 5; i++) {
        if (mCps[i].ChkTgHit()) {
            daObj::HitSeStart(&current.pos, current.roomNo, &mCps[i], 7);
            dKy_Sound_set(current.pos, 4, fopAcM_GetID(this), 100);
            mCps[i].ClrTgHit();
        } else {
            mCpsData[i].mStart = m0400[i];
            mCpsData[i].mEnd = m0400[i + 1];
            mCpsData[i].mRadius = 47.4f;
            ((cM3dGCps&)mCps[i]).Set(mCpsData[i]);
            dComIfG_Ccsp()->Set(&mCps[i]);
        }
    }

    for (int i = 0; i < 4; i++) {
        cXyz dir = (m0400[i + 2] - m0400[i + 1]) * 0.33333f;
        cXyz pos = m0400[i + 1] + dir;
        mSph[2 * i].SetC(pos);
        mSph[2 * i].SetR(47.4f);
        dComIfG_Ccsp()->Set(&mSph[2 * i]);

        cXyz pos2 = m0400[i + 1] + dir * 2.0f;
        mSph[2 * i + 1].SetC(pos2);
        mSph[2 * i + 1].SetR(47.4f);
        dComIfG_Ccsp()->Set(&mSph[2 * i + 1]);
    }
}

/* 000005F4-000009B8       .text JointNodeCallBack__10daObjVyasiFP7J3DNodei */
BOOL daObjVyasi::JointNodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 000009F4-000009FC       .text process_none_init__Q210daObjVyasi5Act_cFv */
int daObjVyasi::Act_c::process_none_init() {
    return 1;
}

/* 000009FC-00000A00       .text process_none_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_none_main() {
}

/* 00000A00-00000A64       .text process_sag_init__Q210daObjVyasi5Act_cFv */
int daObjVyasi::Act_c::process_sag_init() {
    if (SetStopJointAnimation(mpBckData, 1.0f, 0.0f)) {
        mpMorf->setPlaySpeed(0.0f);
        return 1;
    }
    return 0;
}

/* 00000A64-00000AD8       .text process_sag_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sag_main() {
    fopAc_ac_c* target = fopAcM_SearchByName(0xA3);
    if (target != NULL) {
        mEkszsPos = target->current.pos;
        mEkszsRotY = target->shape_angle.y;
        process_init(2);
    }
}

/* 00000AD8-00000CC0       .text process_sagWind_init__Q210daObjVyasi5Act_cFv */
int daObjVyasi::Act_c::process_sagWind_init() {
    if (SetStopJointAnimation(mpBckData, 1.0f, 3.0f)) {
        f32 dist = mEkszsPos.getSquareDistance(current.pos);
        if (dist > 0.0f) {
            dist = std::sqrtf(dist);
        }
        f32 f = dist < 2800.0f ? dist : 2800.0f;
        f = f < 1000.0f ? 1000.0f : f;
        m0504 = (f - 2800.0f) / -1800.0f;

        f32 f30 = 5000.0f + 7000.0f * m0504;
        f32 f31 = 0.5f * f30;
        for (int i = 0; i < 14; i++) {
            if (joint_kind_table[i] == 0) {
                if ((i & 1) == 0) {
                    m0524[i] = (s16)(f30 + cM_rndF(2000.0f));
                } else {
                    m0524[i] = (s16)(-(f30 + cM_rndF(2000.0f)));
                }
            } else {
                m0524[i] = (s16)f31;
            }
        }
        mpMorf->setPlaySpeed(0.0f);
        return 1;
    }
    return 0;
}

/* 00000CC0-00000D20       .text process_sagWind_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_sagWind_main() {
    if (is_switch()) {
        process_init(3);
    }
}

/* 00000D20-00000D54       .text process_toNormal_init__Q210daObjVyasi5Act_cFv */
int daObjVyasi::Act_c::process_toNormal_init() {
    return SetStopJointAnimation(mpBckData, 1.0f, 0.0f);
}

/* 00000D54-00000E10       .text process_toNormal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_toNormal_main() {
    if (m19C4 == 0) {
        f32 f = std::fabsf(m19CC);
        if (f <= 0.1f) {
            if (process_init(4)) {
                m19CC = 0.0f;
                m19D4 = 0.0f;
                mNormalCounter = 2;
            }
        }
        m19CC *= 0.85f;
        m19D0 += 0x3000;
    } else {
        m19CC = -1792.0f * m0504;
        m19D0 = 0;
    }
}

/* 00000E10-00000E74       .text process_normal_init__Q210daObjVyasi5Act_cFv */
int daObjVyasi::Act_c::process_normal_init() {
    if (SetStopJointAnimation(mpBckData, -1.0f, 0.0f)) {
        mpMorf->setPlaySpeed(0.0f);
        return 1;
    }
    return 0;
}

/* 00000E74-00000ED0       .text process_normal_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_normal_main() {
    if (mNormalCounter == 0 || mNormalCounter == 1) {
        mNormalCounter++;
    }
    cLib_addCalc(&m19D4, 1.0f, 0.01f, 1.0f, 0.007f);
}

/* 00000ED0-00000FE4       .text process_init__Q210daObjVyasi5Act_cFi */
int daObjVyasi::Act_c::process_init(int i) {
    typedef int (daObjVyasi::Act_c::*init_func)();
    static init_func init_table[5] = {
        &daObjVyasi::Act_c::process_none_init,
        &daObjVyasi::Act_c::process_sag_init,
        &daObjVyasi::Act_c::process_sagWind_init,
        &daObjVyasi::Act_c::process_toNormal_init,
        &daObjVyasi::Act_c::process_normal_init,
    };
    if (i >= 0 && i < 5) {
        if ((this->*init_table[i])()) {
            mState = i;
            return 1;
        }
    }
    return 0;
}

/* 00000FE4-000010C8       .text process_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::process_main() {
    typedef void (daObjVyasi::Act_c::*main_func)();
    static main_func main_table[5] = {
        &daObjVyasi::Act_c::process_none_main,
        &daObjVyasi::Act_c::process_sag_main,
        &daObjVyasi::Act_c::process_sagWind_main,
        &daObjVyasi::Act_c::process_toNormal_main,
        &daObjVyasi::Act_c::process_normal_main,
    };
    if (mState >= 0 && mState < 5) {
        (this->*main_table[mState])();
    }
}

const char daObjVyasi::Act_c::M_arcname[] = "Vyasi";

/* 000010C8-000010EC       .text solidHeapCB__Q210daObjVyasi5Act_cFP10fopAc_ac_c */
BOOL daObjVyasi::Act_c::solidHeapCB(fopAc_ac_c*) {
    return create_heap();
}

/* 000010EC-00001290       .text create_heap__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::create_heap() {
    /* Nonmatching */
}

/* 00001290-000016E0       .text _create__Q210daObjVyasi5Act_cFv */
cPhs_State daObjVyasi::Act_c::_create() {
    /* Nonmatching */
}

/* 00001D8C-00001DBC       .text _delete__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_delete() {
    /* Nonmatching */
}

/* 00001DBC-00001E5C       .text set_mtx__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::set_mtx() {
    /* Nonmatching */
}

/* 00001E5C-000025A8       .text calc_dif_angle__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::calc_dif_angle() {
    /* Nonmatching */
}

/* 000025A8-00002880       .text quaternion_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::quaternion_main() {
    /* Nonmatching */
}

/* 00002880-00002938       .text leaf_scale_main__Q210daObjVyasi5Act_cFv */
void daObjVyasi::Act_c::leaf_scale_main() {
    /* Nonmatching */
}

/* 00002938-000029BC       .text _execute__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_execute() {
    /* Nonmatching */
}

/* 000029BC-00002A6C       .text _draw__Q210daObjVyasi5Act_cFv */
bool daObjVyasi::Act_c::_draw() {
    /* Nonmatching */
}

namespace daObjVyasi {
namespace {
/* 00002A6C-00002A8C       .text Mthd_Create__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_create();
}

/* 00002A8C-00002AB0       .text Mthd_Delete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_delete();
}

/* 00002AB0-00002AD4       .text Mthd_Execute__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_execute();
}

/* 00002AD4-00002AF8       .text Mthd_Draw__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVyasi::Act_c*)i_this)->_draw();
}

/* 00002AF8-00002B00       .text Mthd_IsDelete__Q210daObjVyasi27@unnamed@d_a_obj_vyasi_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVyasi

actor_process_profile_definition g_profile_Obj_Vyasi = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Vyasi_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVyasi::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Vyasi_e,
    /* Actor SubMtd */ &daObjVyasi::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
