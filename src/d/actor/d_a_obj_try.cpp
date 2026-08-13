/**
 * d_a_obj_try.cpp
 * Object - Tower of the Gods - Glowing blue/pink statue/pillar
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_try.h"

#include "d/d_bg_w.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_camera.h"
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
u8 Act_c::solidHeapCB(fopAc_ac_c*) {
    return create_heap();
}

/* 000000B4-0000026C       .text create_heap__Q28daObjTry5Act_cFv */
s32 Act_c::create_heap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, attr().m48);
    if (modelData == NULL) {
        JUT_ASSERT(1009, modelData != NULL);
    }

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020203);
    if (mpModel == NULL) {
        return 0;
    }

    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, attr().m4A);
    if (brk == NULL) {
        JUT_ASSERT(1019, brk != NULL);
    }

    if (mBrkAnm.init(modelData, brk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, TRUE) == 0) {
        return 0;
    }

    if (prm_get_type() == 0) {
        mBrkAnm.getFrameCtrl()->setFrame((f32)mBrkAnm.getFrameCtrl()->getEnd());
    }

    if (mpModel != NULL && mBrkAnm.getFrameCtrl()->getEnd() != 0) {
        return 1;
    }
    return 0;
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
void daObjTry::Act_c::search_sameType(void*, void*) {
    /* Nonmatching */
}

/* 00000428-00000528       .text chk_appear__Q28daObjTry5Act_cCFv */
void daObjTry::Act_c::chk_appear() const {
    /* Nonmatching */
}

/* 00000528-000008D8       .text _create__Q28daObjTry5Act_cFv */
cPhs_State daObjTry::Act_c::_create() {
    /* Nonmatching */
}

/* 00000C88-00000D5C       .text _delete__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::_delete() {
    /* Nonmatching */
}

/* 00000D5C-00000EA8       .text mode_restart_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_restart_init() {
    /* Nonmatching */
}

/* 00000EA8-00000FFC       .text mode_restart__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_restart() {
    /* Nonmatching */
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
}

/* 000012C4-00001344       .text mode_carry_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_carry_init() {
    /* Nonmatching */
}

/* 00001344-000013D4       .text mode_carry__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_carry() {
    /* Nonmatching */
}

/* 000013D4-000014A8       .text mode_drop_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_drop_init() {
    /* Nonmatching */
}

/* 000014A8-00001518       .text mode_drop__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_drop() {
    /* Nonmatching */
}

/* 00001518-000016A0       .text mode_sink_init__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_sink_init() {
    /* Nonmatching */
}

/* 000016A0-0000177C       .text mode_sink__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_sink() {
    /* Nonmatching */
}

/* 0000177C-00001B58       .text mode_proc_call__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::mode_proc_call() {
    /* Nonmatching */
}

/* 00001B58-00001B90       .text cull_set_draw__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::cull_set_draw() {
    /* Nonmatching */
    fopAcM_setCullSizeSphere(this, 25.0f, 1.0f, 25.0f, 1.0f);
}

/* 00001B90-00001BC8       .text cull_set_move__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::cull_set_move() {
    /* Nonmatching */
    fopAcM_setCullSizeSphere(this, 25.0f, 1.0f, 25.0f, 1.0f);
}

/* 00001BC8-00001BE8       .text damaged__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::damaged() {
    fopAcM_cancelCarryNow(this);
}

/* 00001BE8-00001CD8       .text damage_cc_proc__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::damage_cc_proc() {
    /* Nonmatching */
}

/* 00001CD8-00001E98       .text damage_bg_proc__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::damage_bg_proc() {
    /* Nonmatching */
}

/* 00001E98-00001FEC       .text damage_bg_proc_directly__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::damage_bg_proc_directly() {
    /* Nonmatching */
}

/* 00001FEC-00002034       .text chk_sink_water__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::chk_sink_water() {
    /* Nonmatching */
}

/* 00002034-000020AC       .text chk_sinkdown_water__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::chk_sinkdown_water() {
    /* Nonmatching */
}

/* 000020AC-00002218       .text calc_drop_param__Q28daObjTry5Act_cCFPfPfPf */
void daObjTry::Act_c::calc_drop_param(float*, float*, float*) const {
    /* Nonmatching */
}

/* 00002218-000022F4       .text bound__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::bound() {
    /* Nonmatching */
}

/* 000022F4-0000240C       .text se_fall_water__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::se_fall_water() {
    /* Nonmatching */
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
}

/* 00002790-000027BC       .text eff_land_smoke__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::eff_land_smoke() {
    /* Nonmatching */
}

/* 000027BC-0000280C       .text eff_hit_water_splash__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::eff_hit_water_splash() {
    /* Nonmatching */
}

/* 0000280C-00002868       .text make_vib__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::make_vib() {
    /* Nonmatching */
}

/* 00002868-00002960       .text check_circle__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::check_circle() {
    /* Nonmatching */
}

/* 00002960-00002A90       .text get_water_h__Q28daObjTry5Act_cFv */
void daObjTry::Act_c::get_water_h() {
    /* Nonmatching */
}

/* 00002BB4-00002DA8       .text _execute__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::_execute() {
    /* Nonmatching */
}

/* 00002DA8-00002EA4       .text _draw__Q28daObjTry5Act_cFv */
bool daObjTry::Act_c::_draw() {
    /* Nonmatching */
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
