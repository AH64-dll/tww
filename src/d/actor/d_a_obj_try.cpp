/**
 * d_a_obj_try.cpp
 * Object - Tower of the Gods - Glowing blue/pink statue/pillar
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_try.h"

#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
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
    fopAcM_SetParam(this, (fopAcM_GetParam(this) & 0xFFFF00FF) | ((i_swSave << 8) & 0xFF00));
}

/* 00000090-000000B4       .text solidHeapCB__Q28daObjTry5Act_cFP10fopAc_ac_c */
s32 Act_c::solidHeapCB(fopAc_ac_c*) {
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
