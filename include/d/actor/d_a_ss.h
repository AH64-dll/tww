#ifndef D_A_SS_H
#define D_A_SS_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"

class mDoExt_McaMorf;

struct ss_s_s {
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ u8 mSize;
    /* 0x0D */ u8 field_0x0D[3];
};  // size = 0x10

struct ss_s {
    /* 0x00 */ u8 mState;
    /* 0x01 */ u8 field_0x01[3];
    /* 0x04 */ cXyz mPos;
    /* 0x10 */ u8 field_0x10[2];
    /* 0x12 */ s16 mAngleY;
    /* 0x14 */ s16 mAngleZ;
    /* 0x16 */ u8 field_0x16[2];
    /* 0x18 */ cXyz mVel;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ s16 m30;
    /* 0x32 */ s16 m32;
    /* 0x34 */ s16 m34;
    /* 0x36 */ s16 m36;
    /* 0x38 */ s16 m38;
    /* 0x3A */ u8 m3A;
    /* 0x3B */ u8 m3B;
    /* 0x3C */ dCcD_Sph mSph[4];
    /* 0x4EC */ ss_s_s mSss[20];
};  // size = 0x62C

struct ss_class : public fopAc_ac_c {
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ s8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6;
    /* 0x2B7 */ u8 m2B7;
    /* 0x2B8 */ mDoExt_McaMorf* mpMorf;
    /* 0x2BC */ u8 mFlag;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 m2BE;
    /* 0x2BF */ u8 m2BF;
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ s16 m2C2;
    /* 0x2C4 */ s16 m2C4;
    /* 0x2C6 */ s16 m2C6;
    /* 0x2C8 */ s16 m2C8;
    /* 0x2CA */ s16 m2CA;
    /* 0x2CC */ s16 m2CC;
    /* 0x2CE */ s16 m2CE;
    /* 0x2D0 */ s16 m2D0;
    /* 0x2D2 */ s16 m2D2;
    /* 0x2D4 */ s16 m2D4;
    /* 0x2D6 */ s16 m2D6;
    /* 0x2D8 */ s8 m2D8;
    /* 0x2D9 */ u8 m2D9[3];
    /* 0x2DC */ ss_s mHand[10];
    /* 0x4094 */ mDoExt_3DlineMat0_c mLine;
    /* 0x40B0 */ dCcD_Stts mStts;
    /* 0x40EC */ dCcD_Sph mSph;
};  // size = 0x4218

#endif /* D_A_SS_H */
