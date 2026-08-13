/**
 * d_a_obj_try.cpp
 * Object - Tower of the Gods - Glowing blue/pink statue/pillar
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_try.h"

#include "d/d_bg_s_func.h"
#include "d/d_bg_w.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_pc/f_pc_name.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_particle.h"
#include "d/d_stage.h"
#include "d/d_s_play.h"

namespace daObjTry {
namespace {
    const f32 L_attrBase[3] = {-0.6f, 15.0f, 15.0f};

    typedef void (Act_c::*ModeFunc)();
    static const ModeFunc mode_proc_init[5] = {
        &Act_c::mode_restart,
        &Act_c::mode_wait,
        &Act_c::mode_carry,
        &Act_c::mode_drop,
        &Act_c::mode_sink,
    };
    static ModeFunc mode_proc[5];
    static u8 mode_proc_ready;
}; // namespace

const char Act_c::M_arcname[] = "Hseki";

const dCcD_SrcCyl Act_c::M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 8,
        /* SrcObjAt  Atp     */ 1 << 24,
        /* SrcObjAt  SPrm    */ 0xB,
        /* SrcObjTg  Type    */ 0xFF3DFEFF,
        /* SrcObjTg  SPrm    */ 9,
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
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    }},
};

const Attr_c Act_c::M_attr[13] = {
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x00001240,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 0, /* m73 */ 0,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x00001240,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 0, /* m73 */ 0,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 0,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 0,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 0,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ 8,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x00001BE0,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 1, /* m71 */ 1, /* m72 */ 0, /* m73 */ 1,
        /* m74 */ 1, /* m75 */ 1, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 5, /* m48 */ 9,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x00001BE0,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 1, /* m71 */ 1, /* m72 */ 0, /* m73 */ 1,
        /* m74 */ 1, /* m75 */ 1, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 1,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 1,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 1,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 1,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 1,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
    {
        /* mGravity */ -6.0f, /* m04 */ 70.0f, /* m08 */ 150.0f,
        /* m0C */ 200, /* m0D */ 0, /* m0E */ 0, /* m0F */ 0,
        /* m10 */ 27.0f, /* m14 */ 36.0f, /* m18 */ 0.0f,
        /* m1C */ 0.002f, /* m20 */ 0.0002f, /* m24 */ 4.0f,
        /* m28 */ 0.2f, /* m2C */ 0.02f, /* m30 */ 30.0f,
        /* m34 */ 15, /* m36 */ 15,
        /* m38 */ 0.1f, /* m3C */ 0.02f,
        /* m40 */ 150, /* m41 */ 5, /* m42 */ 100, /* m43 */ 4,
        /* m44 */ 125, /* m45 */ 5, /* m46 */ 4, /* m48 */ -1,
        /* m4A */ 72, /* m4B */ 56, /* m4C */ 150, /* m4D */ 150,
        /* m4E */ 0, /* m4F */ 0,
        /* m50 */ 0x0000692B, /* m54 */ 0x00006929, /* m58 */ 0x00006918,
        /* m5C */ 13, /* m60 */ 0x0000FFFF,
        /* m64 */ 1.0f, /* m68 */ 0.75f, /* m6C */ 1.12f,
        /* m70 */ 0, /* m71 */ 0, /* m72 */ 1, /* m73 */ 1,
        /* m74 */ 0, /* m75 */ 0, /* m76 */ 0, /* m77 */ 0,
    },
};

u8 Act_c::M_bingo;
u8 Act_c::M_restart;

/* 00000078-00000090       .text prm_set_swSave__Q28daObjTry5Act_cFi */
void Act_c::prm_set_swSave(int i_swSave) {
    u32 p = fopAcM_GetParam(this);
    p &= 0xFFFF00FF;
    p |= (u8)i_swSave << 8;
    fopAcM_SetParam(this, p);
}

/* 00000090-000000B4       .text solidHeapCB__Q28daObjTry5Act_cFP10fopAc_ac_c */
BOOL Act_c::solidHeapCB(fopAc_ac_c* i_actor) {
    return (u8)static_cast<Act_c*>(i_actor)->create_heap();
}

/* 000000B4-0000026C       .text create_heap__Q28daObjTry5Act_cFv */
s32 Act_c::create_heap() {
    /* Nonmatching */
    s32 ret = 0;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, attr().m46);
    if (modelData == NULL) {
        JUT_ASSERT(1009, modelData != NULL);
    }

    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    BOOL brkOk = TRUE;
    if (attr().m48 >= 0) {
        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, attr().m48);
        if (brk == NULL) {
            JUT_ASSERT(1019, brk != NULL);
        }
        brkOk = mBrkAnm.init(modelData, brk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE);
    }

    if (daObj::PrmAbstract(this, 1, 0x1f) == 0) {
        mBrkAnm.getFrameCtrl()->setFrame((f32)mBrkAnm.getFrameCtrl()->getEnd());
    }

    if (mpModel != NULL && brkOk) {
        ret = 1;
    }
    return ret;
}

/* 0000026C-0000038C       .text init_cc__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::init_cc() {
    mStts.Init(attr().m0C, 0xFF, this);
    mCyl.Set(M_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.SetR((f32)attr().m4B);
    mCyl.SetH((f32)attr().m4C);
    mCyl.SetAtVec((cXyz&)cXyz::Zero);
    mCyl.SetTgVec((cXyz&)cXyz::Zero);
    mCyl.OnTgShield();
}

/* 0000038C-00000428       .text search_sameType__Q28daObjTry5Act_cFPvPv */
void* daObjTry::Act_c::search_sameType(void* pActor, void* pSelf) {
    /* Nonmatching */
    // static member: pActor = candidate, pSelf = this-actor data from fopAcIt_Judge
    if (pActor != NULL && fopAc_IsActor(pActor) && fopAcM_GetName(pActor) == fpcNm_Obj_Try_e &&
        pActor != pSelf &&
        daObj::PrmAbstract((fopAc_ac_c*)pActor, PRM_TYPE_W, PRM_TYPE_S) ==
            daObj::PrmAbstract((fopAc_ac_c*)pSelf, PRM_TYPE_W, PRM_TYPE_S) &&
        ((Act_c*)pActor)->m650 != 0) {
        return pActor;
    }
    return NULL;
}

/* 00000428-00000528       .text chk_appear__Q28daObjTry5Act_cCFv */
bool daObjTry::Act_c::chk_appear() const {
    bool result = true;

    if (attr().m70 != 0) {
        u8 swFlag = daObj::PrmAbstract(this, PRM_FLAG_W, PRM_FLAG_S) != 0;
        int swSave = prm_get_swSave();
        bool sw = dComIfGs_isSwitch(swSave, home.roomNo) != 0;
        if ((!sw && swFlag) || (sw && !swFlag)) {
            result = false;
        }
    }

    if (attr().m71 != 0 && fopAcIt_Judge(search_sameType, (void*)this) != NULL) {
        result = false;
    }
    return result;
}

/* 00000528-000008D8       .text _create__Q28daObjTry5Act_cFv */
cPhs_State daObjTry::Act_c::_create() {
    fopAcM_SetupActor(this, Act_c);

    mType = prm_get_type();
    m650 = chk_appear();

    cPhs_State phase = cPhs_ERROR_e;
    if (m650 != 0) {
        phase = dComIfG_resLoad(&mPhase, M_arcname);
        if (phase == cPhs_COMPLEATE_e) {
            if (fopAcM_entrySolidHeap(this, solidHeapCB, attr().m60)) {
                mAcchCir.SetWall(30.0f, (f32)attr().m4B);
                mAcch.Set(&current.pos, &old.pos, this, 1, &mAcchCir, &speed, &current.angle,
                          &shape_angle);
                mAcch.ClrWaterNone();
                mAcch.ClrRoofNone();
                mAcch.SetRoofCrrHeight((f32)attr().m4D);
                init_cc();
                cullMtx = mpModel->getBaseTRMtx();
                cull_set_draw();
                gravity = attr().mGravity;
                if (mType == 5 || mType == 6) {
                    fopAcM_OnStatus(this, fopAcStts_UNK2000000_e);
                }
                fopAcM_posMoveF(this, NULL);
                mAcch.CrrPos(*dComIfG_Bgsp());
                mAcch.ClrGroundLanding();
                m634 = 1;
                m632 = 0x14;
                attention_info.flags |= 0x10;
                attention_info.distances[4] = 0x17;
                attention_info.position.x = current.pos.x;
                attention_info.position.y = current.pos.y + attr().m08;
                attention_info.position.z = current.pos.z;
                m635 = 1;
                m636 = 0;
                m638 = 0.0f;
                m630 = 0;
                m64A = 0;
                init_mtx();
                m651 = 0;
                m64C = 0;
                m64D = 0;
                m64E = 1;
                m64F = 0;
                m652 = 0;
                mode_wait_init();
                model = mpModel;
            } else {
                phase = cPhs_ERROR_e;
            }
        }
    }
    return phase;
}

/* 00000C88-00000D5C       .text _delete__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::_delete() {
    /* Nonmatching */
    if (m650 != 0) {
        mFollowCb.remove();
        if (m668 != 0) {
            ((JPABaseEmitter*)m668)->mMaxFrame = -1;
            ((JPABaseEmitter*)m668)->setStatus(JPAEmtrStts_StopEmit);
        }
        if (mType == 5) {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0108);
        } else if (mType == 6) {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0110);
        }
        model = NULL;
        dComIfG_deleteObjectRes(M_arcname);
    }
    return true;
}

/* 00000D5C-00000EA8       .text mode_restart_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_restart_init() {
    /* Nonmatching */
    mCyl.ClrAtSet();
    mCyl.ClrTgSet();
    mCyl.OnCoSetBit();
    mAcch.SetRoofNone();
    mAcch.SetWallNone();
    mAcch.ClrGrndNone();
    mAcch.SetWaterNone();
    mAcch.OffLineCheck();
    speedF = 0.0f;
    m630 = 0x6E;
    current.pos.x = home.pos.x;
    current.pos.y = home.pos.y + (-10.0f - (f32)attr().m4D);
    current.pos.z = home.pos.z;
    shape_angle.x = home.angle.x;
    shape_angle.y = home.angle.y - 0x8000;
    shape_angle.z = home.angle.z;
    current.angle = shape_angle;
    old.pos = current.pos;
    old.angle = current.angle;
    attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
    mMode = 0;
}

/* 00000EA8-00000FFC       .text mode_restart__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_restart() {
    /* Nonmatching */
    m630--;
    if (m630 < 0x50) {
        M_restart = 1;
    }
    m632 = 0x14;
    m634 = 1;
    if (m630 == 0) {
        shape_angle.y = home.angle.y;
        current.angle.y = shape_angle.y;
        current.pos.y = home.pos.y;
        mode_wait_init();
        return;
    }
    if (m630 < 0x32) {
        f32 f4 = 0.5f * (0.0f - jmaCosTable[(u16)(655.36f * m630) >> jmaSinShift]);
        current.pos.y = home.pos.y + f4 * (-10.0f - (f32)attr().m4D);
        shape_angle.y = home.angle.y + (s16)(-32768.0f * f4);
        current.angle.y = shape_angle.y;
    }
}

/* 00000FFC-00001074       .text mode_wait_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_wait_init() {
    mCyl.OffAtSetBit();
    mCyl.OnTgSetBit();
    mCyl.OnCoSetBit();

    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OffLineCheck();

    speedF = 0.0f;
    mMode = 1;
}

/* 00001074-000012C4       .text mode_wait__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_wait() {
    /* Nonmatching */
    int bingo = 0;
    if (attr().m74 != 0 && m64C != 0) {
        bingo = 1;
    }

    if (attr().m73 != 0 && m64D != 0) {
        f32 y = current.pos.y;
        cLib_chasePos(&current.pos, m63C, 10.0f);
        current.pos.y = y;

        cXyz a(m63C.x, 0.0f, m63C.z);
        cXyz b(current.pos.x, 0.0f, current.pos.z);
        if (PSVECSquareDistance(&a, &b) < 25.0f) {
            current.pos.x = m63C.x;
            current.pos.z = m63C.z;
            if (PSVECSquareDistance(&m63C, &current.pos) < 0.0f) {
                M_bingo = 1;
            }
        }

        m64A = (s16)(((u16)(shape_angle.y - m648 + 0x2000) & 0xC000) + m648);
        cLib_addCalcAngleS(&shape_angle.y, m64A, 3, 0x1800, 0x800);
    } else if (bingo == 0) {
        bound();
    }

    bool groundHit = mAcch.ChkGroundHit();
    if (groundHit && bingo == 0) {
        attention_info.flags |= fopAc_Attn_ACTION_CARRY_e;
    } else {
        attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
    }

    if (bingo != 0) {
        m64E = 1;
    }

    int ret = 0;
    if (groundHit && (bingo != 0 || m64D != 0)) {
        ret = 1;
    }

    const cXyz* move;
    if (ret != 0) {
        move = &cXyz::Zero;
    } else {
        move = mStts.GetCCMoveP();
    }

    if (groundHit) {
        this->gravity = attr().mGravity;
        fopAcM_posMoveF(this, move);
    } else {
        f32 spd;
        f32 f1;
        f32 f2;
        calc_drop_param(&spd, &f1, &f2);
        this->gravity = spd;
        daObj::posMoveF_stream(this, move, &cXyz::Zero, f1, f2);
    }
}

/* 000012C4-00001344       .text mode_carry_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_carry_init() {
    mCyl.ClrAtSet();
    mCyl.OnTgSetBit();
    mCyl.ClrCoSet();
    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OffLineCheck();
    attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
    m630 = 8;
    mMode = 2;
}

/* 00001344-000013D4       .text mode_carry__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_carry() {
    /* Nonmatching */
    if (m630 > 0) {
        m630--;
    }
    speed.y = 0.0f;
    if ((actor_status & fopAcStts_UNK40000_e) == 0) {
        if (speedF > 0.0f) {
            mode_drop_init();
            mode_drop();
        } else {
            daObj::SetCurrentRoomNo(this, &mAcch.m_gnd);
            m636 = 2;
            mode_wait_init();
        }
    }
}

/* 000013D4-000014A8       .text mode_drop_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_drop_init() {
    f32 spd = attr().m14 + dComIfGp_getPlayer(0)->speedF * attr().m18;
    mCyl.OnAtSetBit();
    mCyl.OnTgSetBit();
    mCyl.OnCoSetBit();
    mAcch.ClrRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OnLineCheck();
    attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
    speed.y = attr().m10;
    speedF = spd;
    gravity = attr().mGravity;
    mMode = 3;
}

/* 000014A8-00001518       .text mode_drop__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_drop() {
    daObj::SetCurrentRoomNo(this, &mAcch.m_gnd);
    bound();
    f32 spd;
    f32 f1;
    f32 f2;
    calc_drop_param(&spd, &f1, &f2);
    gravity = spd;
    daObj::posMoveF_stream(this, mStts.GetCCMoveP(), &cXyz::Zero, f1, f2);
}

/* 00001518-000016A0       .text mode_sink_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_sink_init() {
    /* Nonmatching */
    mCyl.ClrAtSet();
    mCyl.OnTgSetBit();
    mCyl.OnCoSetBit();
    mAcch.SetRoofNone();
    mAcch.ClrWallNone();
    mAcch.ClrGrndNone();
    mAcch.ClrWaterNone();
    mAcch.OnLineCheck();
    gravity = attr().mGravity + attr().m24;
    f32 spd = speed.y * speed.y + speedF * speedF;
    if (spd > 0.0f) {
        spd = std::sqrtf(spd);
    }
    if (spd > attr().m30) {
        f32 scale = attr().m30 / spd;
        PSVECScale(&speed, &speed, scale);
        speedF *= scale;
    }
    attention_info.flags &= ~fopAc_Attn_ACTION_CARRY_e;
    mMode = 4;
}

/* 000016A0-0000177C       .text mode_sink__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_sink() {
    f32 waterH = get_water_h();
    f32 groundH = mAcch.GetGroundH();
    daObj::SetCurrentRoomNo(this, &mAcch.m_gnd);
    if (speed.y != 0.0f) {
        if (current.pos.y + attr().m04 > waterH) {
            f32 y = waterH - attr().m04;
            if (y > groundH) {
                current.pos.y = y;
            }
        }
    }
    daObj::posMoveF_stream(this, mStts.GetCCMoveP(), &cXyz::Zero, attr().m28, attr().m2C);
}

/* 0000177C-00001B58       .text mode_proc_call__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::mode_proc_call() {
    /* Nonmatching */
}

/* 00001B58-00001B90       .text cull_set_draw__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::cull_set_draw() {
    /* Nonmatching */
    fopAcM_setCullSizeSphere(this, 0.0f, 65.0f, 0.0f, 100.0f);
}

/* 00001B90-00001BC8       .text cull_set_move__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::cull_set_move() {
    /* Nonmatching */
    fopAcM_setCullSizeSphere(this, 0.0f, 65.0f, 0.0f, 300.0f);
}

/* 00001BC8-00001BE8       .text damaged__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::damaged() {
    fopAcM_cancelCarryNow(this);
}

/* 00001BE8-00001CD8       .text damage_cc_proc__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::damage_cc_proc() {
    /* Nonmatching */
    if (mCyl.ChkAtHit()) {
        mCyl.ClrAtHit();
        speedF *= 0.3f;
    } else if (mCyl.ChkTgHit()) {
        mCyl.GetTgHitObj();
        daObj::HitSeStart(&eyePos, current.roomNo, &mCyl, attr().m5C);
        set_senv(attr().m42, attr().m43);
        daObj::HitEff_hibana(this, &mCyl);
        mCyl.ClrTgHit();
    }
    return false;
}

/* 00001CD8-00001E98       .text damage_bg_proc__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::damage_bg_proc() {
    /* Nonmatching */
    s32 homeRoom = home.roomNo;
    s32 stayRoom = dStage_roomControl_c::mStayNo;
    bool groundHit = mAcch.ChkGroundHit();
    bool sink = chk_sink_water();
    bool ret = false;
    bool sinkdown = false;

    if (mMode == 1) {
        if (sink) {
            se_fall_water();
            if (speed.y != 0.0f) {
                eff_hit_water_splash();
                m653 = 1;
            } else {
                m653 = 0;
            }
            mode_sink_init();
        }
    } else if (mMode == 3) {
        if (groundHit) {
            mode_wait_init();
        } else if (sink) {
            se_fall_water();
            eff_hit_water_splash();
            m653 = 1;
            mode_sink_init();
        }
    } else if (mMode == 4) {
        if (chk_sinkdown_water()) {
            sinkdown = true;
            if (m653 == 0) {
                eff_hit_water_splash();
            }
        } else if (!sink) {
            mode_wait_init();
        }
    }

    if (groundHit && dComIfG_Bgsp()->GetGroundCode(mAcch.m_gnd) == 4) {
        sinkdown = true;
    }

    if (sinkdown) {
        if (homeRoom == stayRoom && (attr().m71 != 0 || m64F == 0)) {
            mode_restart_init();
        } else {
            damaged();
            ret = true;
        }
    }
    return ret;
}

/* 00001E98-00001FEC       .text damage_bg_proc_directly__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::damage_bg_proc_directly() {
    /* Nonmatching */
    bool groundHit = mAcch.ChkGroundHit();
    if (mMode == 3 && (mAcch.ChkRoofHit() || chk_sink_water() || groundHit)) {
        cam_lockoff();
    }

    if (m632 > 0) {
        m632--;
        return false;
    }

    if (groundHit && m634 == 0) {
        if (mMode == 1 || mMode == 3) {
            u32 mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd);
            JAIZelBasic::zel_basic->seStart(attr().m54, &eyePos, mtrlSndId,
                                            dComIfGp_getReverb(current.roomNo), 0.0f, 0.0f, -1.0f,
                                            -1.0f, 0);
            if (m62C != 4) {
                eff_land_smoke();
            }
            m634 = 1;
            m632 = 0x14;
            make_vib();
        }
    } else {
        m634 = 0;
    }
    return false;
}

/* 00001FEC-00002034       .text chk_sink_water__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::chk_sink_water() {
    bool ret = false;
    if (mAcch.ChkWaterHit() && mAcch.m_wtr.GetHeight() > current.pos.y + attr().m04) {
        ret = true;
    }
    return ret;
}

/* 00002034-000020AC       .text chk_sinkdown_water__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::chk_sinkdown_water() {
    bool ret = false;
    if (mAcch.ChkWaterHit() && mAcch.m_wtr.GetHeight() > current.pos.y + (f32)attr().m4D + 50.0f) {
        ret = true;
    }
    return ret;
}

/* 000020AC-00002218       .text calc_drop_param__Q28daObjTry5Act_cCFPfPfPf */
void daObjTry::Act_c::calc_drop_param(f32* pGravity, f32* pViscous, f32* pInert) const {
    /* Nonmatching */
    dBgS_ObjAcch& acch = const_cast<dBgS_ObjAcch&>(mAcch);
    if (acch.ChkWaterHit()) {
        f32 f2 = current.pos.y - acch.m_wtr.GetHeight();
        if (f2 <= 0.0f) {
            f2 = 0.0f;
        } else if (f2 <= (f32)(-attr().m4D)) {
            f2 = 0.5f;
        } else {
            f2 = -f2 * (0.5f / (f32)attr().m4D);
        }
        f32 f3 = 0.0f - f2;
        *pViscous = f2 * attr().m28 + f3 * attr().m1C;
        *pInert = f2 * attr().m2C + f3 * attr().m20;
        *pGravity = f2 * attr().m24 + attr().mGravity;
    } else {
        *pViscous = attr().m1C;
        *pInert = attr().m20;
        *pGravity = attr().mGravity;
    }
}

/* 00002218-000022F4       .text bound__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::bound() {
    /* Nonmatching */
    bool ret = mAcch.ChkGroundHit();
    if (mAcch.ChkWallHit()) {
        speedF *= L_attrBase[2];
        current.angle.y = (s16)(mAcchCir.GetWallAngleY() * 2 - (current.angle.y + 0x8000));
    }
    if (mAcch.ChkGroundLanding()) {
        f32 spd = std::fabsf(m638 * L_attrBase[0]);
        if (spd > L_attrBase[1]) {
            if (spd > L_attrBase[2]) {
                speed.y = L_attrBase[2];
            } else {
                speed.y = spd;
            }
            ret = false;
        }
    } else if (mAcch.ChkGroundHit()) {
        cLib_addCalc(&speed.y, 0.0f, 0.5f, 5.0f, 0.0f);
    }
    return ret;
}

/* 000022F4-0000240C       .text se_fall_water__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::se_fall_water() {
    /* Nonmatching */
    cBgS_PolyInfo* temp[2] = {
        &mAcch.m_wtr,
        &mAcch.m_gnd,
    };

    u32 mtrlSndId = 0x13;
    for (int i = 0; i < ARRAY_SIZE(temp); i++) {
        int bg_index = temp[i]->GetBgIndex();
        if (bg_index >= 0 && bg_index < 0x100) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(*temp[i]);
            break;
        }
    }

    JAIZelBasic::zel_basic->seStart(attr().m58, &eyePos, mtrlSndId, dComIfGp_getReverb(current.roomNo),
                                    0.0f, 0.0f, -1.0f, -1.0f, 0);
    set_senv(attr().m44, attr().m45);
}

/* 0000240C-00002460       .text set_senv__Q28daObjTry5Act_cCFii */
void daObjTry::Act_c::set_senv(int i_a, int i_b) const {
    dKy_Sound_set(current.pos, i_a, fopAcM_GetID((void*)this), i_b);
}

/* 00002460-00002498       .text cam_lockoff__Q28daObjTry5Act_cCFv */
void daObjTry::Act_c::cam_lockoff() const {
    dComIfGp_getCamera(0)->mCamera.ForceLockOff(base.base.mBsPcId);
}

/* 00002498-00002504       .text set_mtx__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00002504-00002540       .text init_mtx__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00002540-00002718       .text eff_set_bingo__Q28daObjTry5Act_cFbb */
void daObjTry::Act_c::eff_set_bingo(bool, bool) {
    /* Nonmatching */
}

/* 00002718-00002790       .text eff_clr_bingo__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::eff_clr_bingo() {
    /* Nonmatching */
    if (m651 != 0) {
        mFollowCb.remove();
        if (m668 != 0) {
            ((JPABaseEmitter*)m668)->mMaxFrame = -1;
            ((JPABaseEmitter*)m668)->setStatus(JPAEmtrStts_StopEmit);
            m668 = 0;
        }
        m651 = 0;
    }
}

/* 00002790-000027BC       .text eff_land_smoke__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::eff_land_smoke() {
    /* Nonmatching */
    daObj::make_land_effect(this, &mAcch.m_gnd, 0.0f);
}

/* 000027BC-0000280C       .text eff_hit_water_splash__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::eff_hit_water_splash() {
    /* Nonmatching */
    cXyz pos(current.pos.x, mAcch.m_wtr.GetHeight(), current.pos.z);
    fopKyM_createWpillar(&pos, 0.0f, 0.75f, 0);
}

/* 0000280C-00002868       .text make_vib__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::make_vib() {
    /* Nonmatching */
    int ret = check_circle();
    g_dComIfG_gameInfo.play.mVibration.StartShock(ret + 1, 1, cXyz(0.0f, 0.0f, 0.0f));
}

/* 00002868-00002960       .text check_circle__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::check_circle() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz diff = player->current.pos - current.pos;
    f32 dist = PSVECSquareMag((Vec*)&cXyz(diff.x, 0.0f, diff.z));
    dist = std::sqrtf(dist);
    bool ret = false;
    if (dist <= 190.0f) {
        ret = true;
    }
    return ret;
}

/* 00002960-00002A90       .text get_water_h__Q28daObjTry5Act_cFv */
f32 daObjTry::Act_c::get_water_h() {
    /* Nonmatching */
    dBgS_WtrChk waterChk;
    f32 ret = current.pos.y;
    if (dBgS_SplGrpChk_In_ObjGnd(current.pos, &waterChk, 100.0f)) {
        ret = waterChk.GetHeight();
    }
    return ret;
}

/* 00002BB4-00002DA8       .text _execute__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::_execute() {
    /* Nonmatching */
    cull_set_move();

    if (m635 == 0 && mMode == 1 && mAcch.ChkGroundHit() && !mAcch.ChkGroundLanding() &&
            attr().m75 == 0 && fopAcM_cullingCheck(this) != 0) {
        goto skip;
    }

    m635 = 0;
    bool deleteFlag = true;
    if (!damage_cc_proc()) {
        if (!damage_bg_proc()) {
            if (m636 > 0) {
                m636--;
            }
        }
    }
    m64E = 0;
    if (mode_proc_call()) {
        deleteFlag = false;
        set_mtx();
        mStts.SetRoomId(current.roomNo);
        mCyl.MoveCAtTg(current.pos);
        g_dComIfG_gameInfo.play.mCcS.Set(&mCyl);
        if (mMode == 3 || mMode == 4 || m636 != 0) {
            g_dComIfG_gameInfo.play.mCcS.SetMass(&mCyl, 3);
        }
        attention_info.position.x = current.pos.x;
        attention_info.position.y = current.pos.y + attr().m08;
        attention_info.position.z = current.pos.z;
        eyePos.x = attention_info.position.x;
        eyePos.y = attention_info.position.y;
        eyePos.z = attention_info.position.z;
        m62C = mMode;
    }
    if (deleteFlag) {
        fopAcM_delete(this);
    }

skip:
    if (attr().m74 == 0) {
        m64C = 0;
    }
    m64D = 0;
    cull_set_draw();
    return true;
}

/* 00002DA8-00002EA4       .text _draw__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    if (attr().m48 >= 0) {
        mBrkAnm.entry(mpModel->getModelData(), mBrkAnm.getFrameCtrl()->getFrame());
    }
    mDoExt_modelUpdateDL(mpModel);

    if ((actor_status & fopAcStts_UNK40000_e) == 0) {
        f32 h = (f32)attr().m4A;
        dComIfGd_setSimpleShadow2(&current.pos, mAcch.GetGroundH(), h, mAcch.m_gnd, 0, 0.0f,
                                  &dDlst_shadowControl_c::mSimpleTexObj);
    }
    return true;
}

namespace {
/* 00002EA4-00002EC4       .text Mthd_Create__Q28daObjTry25@unnamed@d_a_obj_try_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjTry::Act_c*)i_this)->_create();
}

/* 00002EC4-00002EE8       .text Mthd_Delete__Q28daObjTry25@unnamed@d_a_obj_try_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjTry::Act_c*)i_this)->_delete();
}

/* 00002EE8-00002F0C       .text Mthd_Execute__Q28daObjTry25@unnamed@d_a_obj_try_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjTry::Act_c*)i_this)->_execute();
}

/* 00002F0C-00002F30       .text Mthd_Draw__Q28daObjTry25@unnamed@d_a_obj_try_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjTry::Act_c*)i_this)->_draw();
}

/* 00002F30-00002F38       .text Mthd_IsDelete__Q28daObjTry25@unnamed@d_a_obj_try_cpp@FPv */
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
}; // namespace daObjTry

actor_process_profile_definition g_profile_Obj_Try = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0008,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Try_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTry::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Try_e,
    /* Actor SubMtd */ &daObjTry::Mthd_Table,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_UNK8000000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLSPHERE_CUSTOM_e,
};
