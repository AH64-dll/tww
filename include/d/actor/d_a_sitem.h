#ifndef D_A_SITEM_H
#define D_A_SITEM_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

struct sitem_s {
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
};  // Size: 0x1C

STATIC_ASSERT(sizeof(sitem_s) == 0x1C);

class sitem_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ J3DModel* mpModel;
    /* 0x2B8 */ u8 mType;
    /* 0x2B9 */ u8 m2B9;
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB;
    /* 0x2BC */ s16 m2BC;
    /* 0x2BE */ u8 field_0x2BE[2];
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ s16 m2C2[2];
    /* 0x2C6 */ s16 m2C6;
    /* 0x2C8 */ cXyz mHomePos;
    /* 0x2D4 */ cXyz mSpeed;
    /* 0x2E0 */ cXyz m2E0;
    /* 0x2EC */ csXyz m2EC;
    /* 0x2F4 */ f32 m2F4;
    /* 0x2F8 */ f32 m2F8;
    /* 0x2FC */ f32 m2FC;
    /* 0x300 */ cXyz mHandPos;
    /* 0x30C */ mDoExt_3DlineMat0_c mLineMat1;
    /* 0x328 */ sitem_s mSitem1[10];
    /* 0x440 */ mDoExt_3DlineMat0_c mLineMat2;
    /* 0x45C */ sitem_s mSitem2[5];
    /* 0x4E8 */ dCcD_Stts mStts;
    /* 0x524 */ dCcD_Sph mSph[4];
    /* 0x9D4 */ dCcD_Sph mBmSph;
    /* 0xB00 */ cXyz mB00;
    /* 0xB0C */ f32 mB0C;
    /* 0xB10 */ s16 mB10;
    /* 0xB14 */ dBgS_AcchCir mAcchCir;
    /* 0xB54 */ dBgS_Acch mAcch;
    /* 0xD18 */ dPa_followEcallBack mFollow[2];
    /* 0xD40 */ csXyz mCSxyz[2];
    /* 0xD4C */ s8 mD4C;
};  // Size: 0xD50

STATIC_ASSERT(sizeof(sitem_class) == 0xD50);

#endif /* D_A_SITEM_H */
