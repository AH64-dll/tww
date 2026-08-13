/**
 * d_a_obj_flame.cpp
 * Object - Fire pillar
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_flame.h"
#include "d/actor/d_a_mflft.h"
#include "d/actor/d_a_ykgr.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_particle.h"
#include "d/d_a_obj.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_iter.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "SSystem/SComponent/c_lib.h"

// Minimal local declaration of daObjMagmarock::Act_c so the vtable calls in
// liftup_magmarock generate the original call sequence (vtable at 0x290).
// The real class is a stub; only LiftUpRequest/BeforeLiftRequest are used.
namespace daObjMagmarock {
    class Act_c : public fopAc_ac_c {
    public:
        virtual void LiftUpRequest(cXyz&);
        virtual void BeforeLiftRequest(cXyz&);
    };
}

namespace daObjFlame {
    // Per-access table lookup: keeps the scaled index in a register so mwcc
    // emits indexed loads (lfsx/lbzx) exactly like the original.
    static inline const attr_scl_s* flameAttr(const Act_c* a) {
        return &Act_c::M_attr_scl[a->mType];
    }
    static inline const attr_scl_s* flameAttrIdx(s32 type) {
        return &Act_c::M_attr_scl[type];
    }

    const attr_base_s Act_c::M_attr_base = {
        /* mKiMax */ 6,
        /* mRotAdd */ {400, 400},
        /* mF08 */ 200,
        /* mF0A */ -100,
        /* mF0C */ 1000,
        /* mF0E */ 100,
        /* mF10 */ 270,
        /* mF12 */ 0,
    };

    const dCcD_SrcCps Act_c::M_cps_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ 0,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ 0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCpsS
        {{
            /* Start  */ {0.0f, 0.0f, 0.0f},
            /* End    */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 30.0f,
        }},
    };

    const attr_scl_s Act_c::M_attr_scl[4] = {
        {
            /* mScale */ 1.0f,
            /* mF04 */ 1.0f,
            /* mF08 */ 1.0f,
            /* mF0C */ 1.0f,
            /* mBdlResID */ 6,
            /* mBtkResID */ 13,
            /* mBrkResID */ 9,
            /* mHeapSize */ 0x52E0,
            /* mRate */ 1.0f,
            /* mF24 */ 1.0f,
            /* mEmID */ 0x805C,
            /* mF2C */ 1,
            /* mF2D */ 1,
            /* mF2E */ 0,
            /* mF2F */ 0,
            /* mEm0SclX */ 1.0f,
            /* mEm0SclY */ 1.0f,
            /* mEm1SclX */ 1.0f,
            /* mEm1SclY */ 1.0f,
            /* mEm2Scl */ 1.0f,
            /* mF44 */ 1.0f,
            /* mCull */ {-150, -1, -150, 150, 1500, 150},
            /* mF54 */ 0.7f,
        },
        {
            /* mScale */ 4.3333335f,
            /* mF04 */ 3.3333335f,
            /* mF08 */ 1.0f,
            /* mF0C */ 0.815f,
            /* mBdlResID */ 5,
            /* mBtkResID */ 12,
            /* mBrkResID */ -1,
            /* mHeapSize */ 0x62A0,
            /* mRate */ 1.0f,
            /* mF24 */ 0.5f,
            /* mEmID */ 0x808A,
            /* mF2C */ 0,
            /* mF2D */ 0,
            /* mF2E */ 0,
            /* mF2F */ 0,
            /* mEm0SclX */ 4.3333335f,
            /* mEm0SclY */ 2.7166667f,
            /* mEm1SclX */ 4.3333335f,
            /* mEm1SclY */ 2.7166667f,
            /* mEm2Scl */ 0.8666667f,
            /* mF44 */ 0.54333335f,
            /* mCull */ {-700, -1, -700, 700, 7500, 700},
            /* mF54 */ 0.0f,
        },
        {
            /* mScale */ 7.5f,
            /* mF04 */ 7.5f,
            /* mF08 */ 1.0f,
            /* mF0C */ 1.0f,
            /* mBdlResID */ 5,
            /* mBtkResID */ 12,
            /* mBrkResID */ -1,
            /* mHeapSize */ 0x6760,
            /* mRate */ 1.0f,
            /* mF24 */ 0.5f,
            /* mEmID */ 0x808A,
            /* mF2C */ 0,
            /* mF2D */ 0,
            /* mF2E */ 0,
            /* mF2F */ 0,
            /* mEm0SclX */ 7.5f,
            /* mEm0SclY */ 7.5f,
            /* mEm1SclX */ 7.5f,
            /* mEm1SclY */ 7.5f,
            /* mEm2Scl */ 1.0f,
            /* mF44 */ 1.0f,
            /* mCull */ {-150, -1, -150, 150, 1500, 150},
            /* mF54 */ 0.0f,
        },
        {
            /* mScale */ 0.5f,
            /* mF04 */ 0.5f,
            /* mF08 */ 0.5f,
            /* mF0C */ 0.5f,
            /* mBdlResID */ 6,
            /* mBtkResID */ 13,
            /* mBrkResID */ 9,
            /* mHeapSize */ 0x52E0,
            /* mRate */ 1.0f,
            /* mF24 */ 1.0f,
            /* mEmID */ 0x805C,
            /* mF2C */ 0,
            /* mF2D */ 1,
            /* mF2E */ 0,
            /* mF2F */ 0,
            /* mEm0SclX */ 0.5f,
            /* mEm0SclY */ 0.5f,
            /* mEm1SclX */ 0.5f,
            /* mEm1SclY */ 0.5f,
            /* mEm2Scl */ 0.5f,
            /* mF44 */ 0.5f,
            /* mCull */ {-75, -1, -75, 75, 750, 75},
            /* mF54 */ 0.7f,
        },
    };

    char Act_c::M_arcname[9] = "Yfire_00";
};

/* 00000078-00000110       .text set_switch__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::set_switch() {
    Act_c* a_this = this;
    if (a_this->mType == 1) {
        if (a_this->mModeProc == 3 || a_this->mModeProc == 4) {
            s32 sw = a_this->prm_get_swSave();
            dComIfGs_onSwitch(sw, a_this->home.roomNo);
        } else {
            s32 sw = a_this->prm_get_swSave();
            dComIfGs_offSwitch(sw, a_this->home.roomNo);
        }
    }
}

/* 00000110-00000134       .text solidHeapCB__Q210daObjFlame5Act_cFP10fopAc_ac_c */
int daObjFlame::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return (u8)((Act_c*)i_this)->create_heap();
}

/* 00000134-00000414       .text create_heap__Q210daObjFlame5Act_cFv */
    /* Nonmatching */
int daObjFlame::Act_c::create_heap() {
    BOOL ret = FALSE;
    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, flameAttr(this)->mBdlResID);
    JUT_ASSERT(499, mdl_data != 0);

    mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);

    J3DAnmTextureSRTKey* btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(M_arcname, flameAttr(this)->mBtkResID);
    mpBtkAnm = new mDoExt_btkAnm();
    BOOL btkOk = FALSE;
    JUT_ASSERT(508, btk != 0);

    if (mpBtkAnm != NULL) {
        btkOk = mpBtkAnm->init(mdl_data, btk, 1, 2, flameAttr(this)->mRate, 0, -1, 0, 0);
    }

    BOOL brkOk = FALSE;
    s32 brkResID = flameAttr(this)->mBrkResID;
    if (brkResID >= 0) {
        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, brkResID);
        mpBrkAnm = new mDoExt_brkAnm();
        JUT_ASSERT(530, brk != 0);

        if (mpBrkAnm != NULL) {
            brkOk = mpBrkAnm->init(mdl_data, brk, 1, 2, flameAttr(this)->mRate, 0, -1, 0, 0);
        }
    } else {
        brkOk = TRUE;
    }

    if (mpModel != NULL && btkOk && brkOk) {
        ret = TRUE;
    }
    return ret;
}

/* 0000045C-000007D8       .text create_mode_init__Q210daObjFlame5Act_cFv */
    /* Nonmatching */
void daObjFlame::Act_c::create_mode_init() {
    u8 sch = prm_get_sch();
    u8 schbit = dKy_get_schbit();
    if (sch != 0 && schbit != 0) {
        s32 timer = dKy_get_schbit_timer();
        s32 cycle = dStage_stagInfo_GetSchSec(dComIfGp_getStage().getStagInfo()) * 30;
        u32 mask = sch << 8;
        if (sch >= schbit) {
            mask = sch;
        }
        s32 idx = 0;
        u32 bit = schbit;
        while ((mask & bit) == 0) {
            bit <<= 1;
            idx++;
        }
        f32 f3 = (f32)(timer + cycle * idx) * flameAttr(this)->mF24;
        if (mType != 1) {
            f3 -= 127.0f;
        }

        if (f3 < 0.0f) {
            mModeProc = 1;
            mTimer = 127.0f + f3;
            mHeight = 0.0f;
        } else if (f3 < 23.0f) {
            mModeProc = 2;
            mTimer = 23.0f - f3;
            mHeight = 0.0f;
        } else if (f3 < 45.0f) {
            mModeProc = 3;
            mTimer = 45.0f - f3;
            mHeight = 0.045454547f * (22.0f - mTimer);
        } else if (f3 < 135.0f) {
            mModeProc = 4;
            mTimer = 135.0f - f3;
            mHeight = 1.0f;
        } else if (f3 < 160.0f) {
            mModeProc = 5;
            mTimer = 160.0f - f3;
            mHeight = 0.04f * mTimer;
        } else if (f3 < 180.0f) {
            mModeProc = 6;
            mTimer = 180.0f - f3;
            mHeight = 0.0f;
        } else {
            mModeProc = 0;
            mTimer = 0.0f;
            mHeight = 0.0f;
        }

        f32 f2 = 0.0055555557f * f3;
        if (mModeProc != 0 && mModeProc != 1) {
            if (mpBtkAnm != NULL) {
                mpBtkAnm->getFrameCtrl()->setFrame(1.0f + f2 * mpBtkAnm->getFrameCtrl()->getEnd());
            }
            if (mpBrkAnm != NULL) {
                mpBrkAnm->getFrameCtrl()->setFrame(1.0f + f2 * mpBrkAnm->getFrameCtrl()->getEnd());
            }
        }

        if (mModeProc != 0 && (mModeProc == 1 || mModeProc == 2 || mModeProc == 3 || mModeProc == 4)) {
            mEm0State = 1;
        }
        if (mModeProc == 1 || mModeProc == 2 || mModeProc == 3 || mModeProc == 4 || mModeProc == 5) {
            mEm1State = 1;
            mEm2State = 1;
        }
        if (flameAttr(this)->mF2C == 0) {
            em_manual_set();
        }
        mbEmPosition = 1;
    } else {
        mModeProc = 0;
        if (sch != 0) {
            mTimer = 0.0f;
        } else {
            mTimer = 120.0f;
        }
        mHeight = 0.0f;
    }
}

/* 000007D8-00000930       .text set_mtx__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::YrotM(mRotY);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    const attr_scl_s* attr = &M_attr_scl[mType];
    fopAcM_setCullSizeBox(this, (f32)attr->mCull[0], (f32)attr->mCull[1], (f32)attr->mCull[2],
                          (f32)attr->mCull[3], mHeight * (f32)attr->mCull[4], (f32)attr->mCull[5]);
}

/* 00000930-00000950       .text init_mtx__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::init_mtx() {
    set_mtx();
}

/* 00000950-00000B3C       .text em_position__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_position() {
    if (mbEmPosition != 0) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
        if (flameAttr(this)->mF2C == 0) {
            if (mpEmitter0 != NULL) {
                mDoMtx_stack_c::push();
                mDoMtx_stack_c::transM(0.0f, mScaleY * (1500.0f * mHeight * flameAttr(this)->mF0C) + mScaleY * (-300.0f * flameAttr(this)->mF0C), 0.0f);
                mpEmitter0->setGlobalRTMatrix(mDoMtx_stack_c::get());
                mDoMtx_stack_c::pop();
            }
            if (mpEmitter1 != NULL) {
                mpEmitter1->setGlobalRTMatrix(mDoMtx_stack_c::get());
            }
        }
        mDoMtx_stack_c::transM(0.0f, mScaleX * (1500.0f * mHeight * flameAttr(this)->mF04), 0.0f);
        PSMTXMultVec(mDoMtx_stack_c::now, &cXyz::Zero, &eyePos);

        mbCol = 1500.0f * mHeight - 300.0f > 0.0f;
        if (mbCol) {
            mDoMtx_stack_c::transM(0.0f, mScaleX * (-300.0f * flameAttr(this)->mF04), 0.0f);
            PSMTXMultVec(mDoMtx_stack_c::now, &cXyz::Zero, &mCpsP1);
        }
    }
}

/* 00000B3C-00000CAC       .text em_simple_set__Q210daObjFlame5Act_cFv */
    /* Nonmatching */
void daObjFlame::Act_c::em_simple_set() {
    u8 flag = 0;
    if (flameAttr(this)->mF2D != 0 && mbLiftup == 0) {
        flag = 1;
    }

    if (mEm0State == 1 && flag) {
        Vec pos;
        pos.x = eyePos.x;
        pos.y = eyePos.y + mScaleY * (-300.0f * flameAttr(this)->mF04);
        pos.z = eyePos.z;
        dComIfGp_particle_setSimple(0x805A, (cXyz*)&pos, 0xFF, g_whiteColor, g_whiteColor, 0);
    }

    if (mEm1State == 1) {
        dComIfGp_particle_setSimple(0x805B, &eyePos, 0xFF, g_whiteColor, g_whiteColor, 0);
    }

    if (mEm2State == 1 && flag) {
        dComIfGp_particle_setSimple(flameAttr(this)->mEmID & 0xFFFF, &home.pos, 0xFF, g_whiteColor, g_whiteColor, 0);
    }
}

/* 00000CAC-00000CEC       .text em_simple_inv__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_simple_inv() {
    if (mEm0State == 3) {
        mpEmitter0 = NULL;
    }
    if (mEm1State == 3) {
        mpEmitter1 = NULL;
    }
    if (mEm2State == 3) {
        mpEmitter2 = NULL;
    }
}

/* 00000CEC-00000F04       .text em_manual_set__Q210daObjFlame5Act_cFv */
    /* Nonmatching */
void daObjFlame::Act_c::em_manual_set() {
    u8 flag = 0;
    const attr_scl_s* attr = &M_attr_scl[mType];
    if (attr->mF2D != 0 && mbLiftup == 0) {
        flag = 1;
    }

    if (mEm0State == 1 && flag && mType != 1) {
        cXyz scale(attr->mEm0SclX, mScaleY * attr->mEm0SclY, attr->mEm0SclX);
        mpEmitter0 = dComIfGp_particle_set(0x805A, &home.pos, &home.angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
        mEm0State = 2;
    }

    if (mEm1State == 1) {
        cXyz scale(flameAttr(this)->mEm1SclX, mScaleY * flameAttr(this)->mEm1SclY, flameAttr(this)->mEm1SclX);
        mpEmitter1 = dComIfGp_particle_set(0x805B, &home.pos, &home.angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
        mEm1State = 2;
    }

    if (mEm2State == 1 && flag) {
        cXyz scale(flameAttr(this)->mEm2Scl, flameAttr(this)->mEm2Scl, flameAttr(this)->mEm2Scl);
        mpEmitter2 = dComIfGp_particle_set(flameAttr(this)->mEmID & 0xFFFF, &home.pos, &home.angle, &scale, 0xFF, NULL, -1, NULL, NULL, NULL);
        mEm2State = 2;
    }
}

/* 00000F04-00001010       .text em_manual_inv__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_manual_inv() {
    const attr_scl_s* attr = &M_attr_scl[mType];
    u8 flag = 0;
    if (attr->mF2D != 0 && mbLiftup != 0) {
        flag = 1;
    }

    if (mEm0State == 2 && flag) {
        mEm0State = 3;
    }

    if (mEm2State == 2 && flag) {
        mEm2State = 3;
    }

    if (mEm0State == 3) {
        JPABaseEmitter* emitter = mpEmitter0;
        if (emitter != NULL) {
            emitter->mMaxFrame = -1;
            emitter->setStatus(1);
            mpEmitter0 = NULL;
        }
    }

    if (mEm1State == 3) {
        JPABaseEmitter* emitter = mpEmitter1;
        if (emitter != NULL) {
            emitter->mMaxFrame = -1;
            emitter->setStatus(1);
            mpEmitter1 = NULL;
        }
    }

    if (mEm2State == 3) {
        JPABaseEmitter* emitter = mpEmitter2;
        if (emitter != NULL) {
            emitter->mMaxFrame = -1;
            emitter->setStatus(1);
            mpEmitter2 = NULL;
        }
    }
}

/* 00001010-00001070       .text ki_init__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::ki_init() {
    s32 count = prm_get_kiNum() + 1;
    s32 temp = count - 32;
    s32 mask = temp - temp - (temp == 0);
    if ((count & ~mask) > 0) {
        mKiCount = 0;
        mKiIdx = 0;
        mbKi = 1;
    }
}

/* 00001070-00001194       .text ki_make__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::ki_make() {
    if (mbKi != 0) {
        if (mKiTimer <= 0) {
            s32 count = prm_get_kiNum() + 1;
            s32 idx = mKiIdx;
            if (idx < (count & ~((count - 32) - (count - 32) - ((count - 32) == 0)))) {
                if (--mKiCount <= 0) {
                    mKiCount = M_attr_base.mKiMax - 1;
                    mKiIdx++;
                    csXyz angle(0, (s16)cM_rndFX(32768.0f), 0);
                    fopAcM_create(0xD8, (s16)0x8002, &current.pos, fopAcM_GetRoomNo(this), &angle, NULL, -1);
                }
            } else {
                mbKi = 0;
                mKiTimer = prm_get_prm();
            }
        } else {
            mbKi = 0;
            mKiTimer--;
        }
    }
}

/* 00001194-000011E4       .text eff_hase__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::eff_hase() {
    dComIfGp_particle_setSimple(0xC06B, &home.pos, 0xFF, g_whiteColor, g_whiteColor, 0);
}

/* 000011E4-00001254       .text se_fireblast_omen__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::se_fireblast_omen() {
    s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
    JAIZelBasic::getInterface()->seStart(JA_SE_FIREBLAST_OMEN, &current.pos, 0, reverb,
                                         1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 00001254-00001610       .text liftup_magmarock__Q210daObjFlame5Act_cFPvPv */
    /* Nonmatching */
void* daObjFlame::Act_c::liftup_magmarock(void* i_actor, void* i_this) {
    daObjMagmarock::Act_c* rock = (daObjMagmarock::Act_c*)i_actor;
    Act_c* flame = (Act_c*)i_this;
    if (fopAc_IsActor(rock) && fopAcM_GetName(rock) == 0x2C && !fpcM_IsCreating(fopAcM_GetID(rock))) {
        f32 f31 = 145.0f * flameAttr(flame)->mScale + M_attr_base.mF08;
        f32 y1 = flame->current.pos.y;
        f32 y2 = flame->eyePos.y;
        f32 maxY = y1 > y2 ? y1 : y2;
        f32 f30 = maxY + M_attr_base.mF0A;
        f32 f29 = maxY + M_attr_base.mF0C;

        cXyz a(rock->current.pos.x, 0.0f, rock->current.pos.z);
        cXyz b(flame->eyePos.x, 0.0f, flame->eyePos.z);
        f32 dist = std::sqrtf(PSVECSquareDistance(&a, &b));

        if (dist < f31 && rock->current.pos.y > f30 && rock->current.pos.y < f29 && flame->mType != 1) {
            f32 f3;
            f32 f4;
            if (flame->mHeight < 0.1f) {
                f4 = M_attr_base.mF0E;
                f3 = 10.0f * M_attr_base.mF10 * flame->mHeight;
            } else if (flame->mHeight <= 0.9f) {
                f3 = 1.0f - flame->mHeight;
                f4 = 10.0f * M_attr_base.mF0E * f3;
                f3 = 10.0f * M_attr_base.mF10 * f3;
            } else {
                f4 = M_attr_base.mF0E;
                f3 = M_attr_base.mF10;
            }

            f32 f0 = flame->mScaleX * flameAttr(flame)->mF04;
            cXyz pos(flame->current.pos.x, flame->current.pos.y + f4 * f0 + f3 * f0, flame->current.pos.z);
            if (flame->mModeProc == 1 || flame->mModeProc == 2) {
                rock->BeforeLiftRequest(pos);
            } else {
                rock->LiftUpRequest((cXyz&)pos);
            }
            flame->mbLiftup = 1;
        }
    }
    return 0;
}

/* 00001610-00001884       .text liftup_mflft__Q210daObjFlame5Act_cFPvPv */
    /* Nonmatching */
void* daObjFlame::Act_c::liftup_mflft(void* i_actor, void* i_this) {
    mflft_class* mflft = (mflft_class*)i_actor;
    Act_c* flame = (Act_c*)i_this;
    if (fopAc_IsActor(mflft) && fopAcM_GetName(mflft) == 0x5D) {
        f32 f31 = 1.0f;
        f32 f30;
        f32 f0 = 5000.0f;
        if (mflft->m29A == 0) {
            f30 = 1.0004418f;
        } else {
            f30 = f31;
        }

        f32 f4 = flame->mHeight;
        f32 f3;
        f32 f5;
        if (f4 < 0.1f) {
            f5 = M_attr_base.mF0E;
            f3 = 10.0f * M_attr_base.mF10 * f4;
        } else if (f4 <= 0.9f) {
            f3 = 1.0f - f4;
            f5 = 10.0f * M_attr_base.mF0E * f3;
            f3 = 10.0f * M_attr_base.mF10 * f3;
        } else {
            f5 = M_attr_base.mF0E;
            f3 = M_attr_base.mF10;
        }

        f32 f1 = flame->mScaleX * flameAttr(flame)->mF04;
        cXyz pos(flame->current.pos.x, flame->current.pos.y + f5 * f1 + f3 * f1, flame->current.pos.z);
        f32 clampY = flame->current.pos.y + f0;
        if (pos.y > clampY) {
            pos.y = clampY;
        }

        if (flame->mModeProc != 1 && flame->mModeProc != 2) {
            mflft->setLiftUp((cXyz)pos);
        }
        flame->mbLiftup = 1;
        cLib_addCalc(&flame->mScaleX, f31, 0.3f, 0.1f, 0.01f);
        cLib_addCalc(&flame->mScaleY, f30, 0.3f, 0.1f, 0.01f);
    }
    return 0;
}

/* 00001884-00001988       .text mode_wait__Q210daObjFlame5Act_cFv */
    /* Nonmatching */
void daObjFlame::Act_c::mode_wait() {
    u8 sch = prm_get_sch();
    u8 flag = FALSE;
    if (sch != 0) {
        if ((sch & dKy_get_schbit()) && dKy_get_schbit_timer() == 0) {
            flag = TRUE;
        }
    } else if (mTimer <= 0.0f) {
        flag = TRUE;
    }

    if (flag) {
        if (mType == 1) {
            mpBtkAnm->getFrameCtrl()->setFrame(0.0f);
            if (mpBrkAnm != NULL) {
                mpBrkAnm->getFrameCtrl()->setFrame(0.0f);
            }
            mModeProc = 2;
            mTimer = 23.0f;
            ki_init();
        } else {
            mModeProc = 1;
            mTimer = 127.0f;
        }
        mEm0State = 1;
        mEm1State = 1;
        mEm2State = 1;
        mbEmPosition = 1;
    }
}

/* 00001988-00001A08       .text mode_wait2__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_wait2() {
    se_fireblast_omen();
    if (mTimer <= 0.0f) {
        mpBtkAnm->getFrameCtrl()->setFrame(0.0f);
        if (mpBrkAnm != NULL) {
            mpBrkAnm->getFrameCtrl()->setFrame(0.0f);
        }
        mModeProc = 2;
        mTimer = 23.0f;
        ki_init();
    }
}

/* 00001A08-00001A98       .text mode_l_before__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_l_before() {
    mbEmPosition = 0;
    if (mTimer <= 0.0f) {
        mModeProc = 3;
        mTimer = 22.0f;
        JAIZelBasic::getInterface()->seStart(JA_SE_FIREBLAST_BLOW, &eyePos, 0, mReverb);
        return;
    }
    se_fireblast_omen();
}

/* 00001A98-00001AE8       .text mode_l_u__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_l_u() {
    mHeight = 0.045454547f * (22.0f - mTimer);
    mbEmPosition = 1;
    if (mTimer <= 0.0f) {
        mModeProc = 4;
        mTimer = 90.0f;
    }
}

/* 00001AE8-00001B20       .text mode_u__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_u() {
    if (mTimer <= 0.0f) {
        mModeProc = 5;
        mTimer = 25.0f;
        mEm0State = 3;
    }
}

/* 00001B20-00001B74       .text mode_u_l__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_u_l() {
    mHeight = 0.04f * mTimer;
    mbEmPosition = 1;
    if (mTimer <= 0.0f) {
        mModeProc = 6;
        mTimer = 20.0f;
        mEm1State = 3;
        mEm2State = 3;
    }
}

/* 00001B74-00001BEC       .text mode_l_after__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_l_after() {
    if (mTimer <= 0.0f) {
        mModeProc = 0;
        if ((u8)prm_get_sch() != 0) {
            mTimer = 0.0f;
        } else {
            mTimer = 120.0f;
        }
    }
}

/* 00001BEC-00001EAC       .text mode_proc_call__Q210daObjFlame5Act_cFv */
    /* Nonmatching */
void daObjFlame::Act_c::mode_proc_call() {
    typedef void (daObjFlame::Act_c::*ModeFunc)();
    static const ModeFunc mode_proc[7] = {
        &daObjFlame::Act_c::mode_wait,
        &daObjFlame::Act_c::mode_wait2,
        &daObjFlame::Act_c::mode_l_before,
        &daObjFlame::Act_c::mode_l_u,
        &daObjFlame::Act_c::mode_u,
        &daObjFlame::Act_c::mode_u_l,
        &daObjFlame::Act_c::mode_l_after,
    };

    if (mTimer >= -0.1f) {
        if (mModeProc == 0 || mModeProc == 1) {
            mTimer -= 1.0f;
        } else {
            mTimer -= flameAttr(this)->mF24;
        }
    }

    (this->*mode_proc[mModeProc])();

    if (flameAttr(this)->mF2C != 0) {
        em_position();
        em_simple_set();
        em_simple_inv();
    } else {
        em_manual_set();
        em_manual_inv();
        em_position();
    }

    if (mModeProc != 0 && mModeProc != 1) {
        mpBtkAnm->play();
        if (mpBrkAnm != NULL) {
            mpBrkAnm->play();
        }
        JAIZelBasic::getInterface()->seStart(JA_SE_FIREBLAST_NOISE, &eyePos, 0, mReverb);
    }

    if (mbCol) {
        if (mModeProc == 5 && !(mHeight > flameAttr(this)->mF54)) {
            return;
        }
        mCps.SetStartEnd(mCpsP0, mCpsP1);
        mCps.SetR(mCpsRad);
        dComIfG_Ccsp()->Set(&mCps);
    }
}

/* 00001EAC-00001ECC       .text Create__Q210daObjFlame6MethodFPv */
cPhs_State daObjFlame::Method::Create(void* i_this) {
    return ((Act_c*)i_this)->_create();
}

/* 00001ECC-00002200       .text _create__Q210daObjFlame5Act_cFv */
    /* Nonmatching */
cPhs_State daObjFlame::Act_c::_create() {
    fopAcM_SetupActor(this, daObjFlame::Act_c);

    cPhs_State phase = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase == cPhs_COMPLEATE_e) {
        mType = prm_get_type();
        if (fopAcM_entrySolidHeap(this, solidHeapCB, flameAttr(this)->mHeapSize)) {
            mOrigScale = scale;
            if (mType == 1) {
                mScaleX = 1.0f;
                mScaleY = 1.0004418f;
            } else {
                mScaleX = 1.0f;
                mScaleY = 1.0f;
            }
            scale.x *= flameAttr(this)->mF08;
            scale.y *= mScaleY * flameAttr(this)->mF0C;
            scale.z *= flameAttr(this)->mF08;
            mEm0State = 0;
            mEm1State = 0;
            mEm2State = 0;
            create_mode_init();
            set_switch();
            cullMtx = mpModel->getBaseTRMtx();
            init_mtx();
            mStts.Init(0x64, 0xFF, this);
            mCps.Set(M_cps_src);
            mCps.SetStts(&mStts);
            mCpsP0 = current.pos;
            mCpsP1 = current.pos;
            mCpsRad = 145.0f * flameAttr(this)->mScale;
            mbCol = FALSE;
            em_position();
            mReverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
            mbLiftup = 0;
            mKiTimer = (s32)cM_rndF(prm_get_prm() + 1);
            if (mModeProc != 0 && mKiTimer == 0) {
                mKiTimer = 1;
            }
        } else {
            phase = cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 00002484-000024B4       .text Delete__Q210daObjFlame6MethodFPv */
BOOL daObjFlame::Method::Delete(void* i_this) {
    Act_c* a_this = (Act_c*)i_this;
    dComIfG_resDelete(&a_this->mPhs, daObjFlame::Act_c::M_arcname);
    return TRUE;
}

/* 000024B4-00002638       .text Execute__Q210daObjFlame6MethodFPv */
    /* Nonmatching */
BOOL daObjFlame::Method::Execute(void* i_this) {
    Act_c* a_this = (Act_c*)i_this;
    a_this->scale.x = a_this->mOrigScale.x * flameAttr(a_this)->mF08;
    a_this->scale.y = a_this->mScaleY * (a_this->mOrigScale.y * flameAttr(a_this)->mF0C);
    a_this->scale.z = a_this->mOrigScale.z * flameAttr(a_this)->mF08;
    a_this->mode_proc_call();
    a_this->ki_make();
    if (a_this->prm_get_haze() == 0) {
        a_this->eff_hase();
    }

    if (a_this->mType == 1) {
        a_this->mRotY += Act_c::M_attr_base.mRotAdd[0];
        if (a_this->mHeight > 0.01f) {
            daYkgr_c::m_aim_rate = 1.0f;
        }
    } else {
        a_this->mRotY += Act_c::M_attr_base.mRotAdd[1];
    }

    a_this->mbLiftup = 0;
    if (a_this->mModeProc == 1 || a_this->mModeProc == 2 || a_this->mModeProc == 3 ||
        a_this->mModeProc == 4)
    {
        fopAcIt_Judge(&Act_c::liftup_magmarock, a_this);
        if (a_this->mType == 1) {
            fopAcIt_Judge(&Act_c::liftup_mflft, a_this);
        }
    }
    a_this->set_switch();
    a_this->set_mtx();
    return TRUE;
}

/* 00002638-00002710       .text Draw__Q210daObjFlame6MethodFPv */
    /* Nonmatching */
BOOL daObjFlame::Method::Draw(void* i_this) {
    Act_c* a_this = (Act_c*)i_this;
    dKy_tevstr_c* tevStr = &a_this->tevStr;
    g_env_light.settingTevStruct(0, &a_this->current.pos, tevStr);
    g_env_light.setLightTevColorType(a_this->mpModel, tevStr);

    a_this->mpBtkAnm->entry(a_this->mpModel->getModelData());
    if (a_this->mpBrkAnm != NULL) {
        a_this->mpBrkAnm->entry(a_this->mpModel->getModelData());
    }

    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaListFilter, 0);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaListFilter, 1);
    mDoExt_modelUpdateDL(a_this->mpModel);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpOpaList, 0);
    j3dSys.setDrawBuffer(g_dComIfG_gameInfo.drawlist.mpXluList, 1);
    return TRUE;
}

/* 00002710-000027B0       .text IsDelete__Q210daObjFlame6MethodFPv */
BOOL daObjFlame::Method::IsDelete(void* i_this) {
    Act_c* a_this = (Act_c*)i_this;
    const attr_scl_s* attr = &Act_c::M_attr_scl[a_this->mType];
    if (attr->mF2C == 0) {
        JPABaseEmitter* emitter0 = a_this->mpEmitter0;
        if (emitter0 != NULL) {
            emitter0->mMaxFrame = -1;
            emitter0->setStatus(1);
            a_this->mpEmitter0 = NULL;
        }
        JPABaseEmitter* emitter1 = a_this->mpEmitter1;
        if (emitter1 != NULL) {
            emitter1->mMaxFrame = -1;
            emitter1->setStatus(1);
            a_this->mpEmitter1 = NULL;
        }
        JPABaseEmitter* emitter2 = a_this->mpEmitter2;
        if (emitter2 != NULL) {
            emitter2->mMaxFrame = -1;
            emitter2->setStatus(1);
            a_this->mpEmitter2 = NULL;
        }
    }
    return TRUE;
}

actor_method_class daObjFlame::Method::Table = {
    (process_method_func)daObjFlame::Method::Create,
    (process_method_func)daObjFlame::Method::Delete,
    (process_method_func)daObjFlame::Method::Execute,
    (process_method_func)daObjFlame::Method::IsDelete,
    (process_method_func)daObjFlame::Method::Draw,
};

actor_process_profile_definition g_profile_Obj_Flame = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Flame_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjFlame::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Flame_e,
    /* Actor SubMtd */ &daObjFlame::Method::Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
