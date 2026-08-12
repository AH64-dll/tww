#ifndef D_A_KLFT_H
#define D_A_KLFT_H

#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

class klft_class : public fopAc_ac_c {
public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ s16 mMoveCounter;
    /* 0x29A */ u8 field_29A[0x29C - 0x29A];
    /* 0x29C */ J3DModel* mModel;
    /* 0x2A0 */ mDoExt_McaMorf* mMorf[2];
    /* 0x2A8 */ cXyz mPath2[2];
    /* 0x2C0 */ s16 mRotY;
    /* 0x2C2 */ u8 mParam;
    /* 0x2C3 */ u8 mShapeParam;
    /* 0x2C4 */ cXyz mSwingPos;
    /* 0x2D0 */ f32 field_2D0;
    /* 0x2D4 */ u8 field_2D4[4];
    /* 0x2D8 */ f32 field_2D8;
    /* 0x2DC */ cXyz field_2DC;
    /* 0x2E8 */ cXyz field_2E8;
    /* 0x2F4 */ f32 field_2F4;
    /* 0x2F8 */ u8 field_2F8[4];
    /* 0x2FC */ f32 field_2FC;
    /* 0x300 */ csXyz field_300;
    /* 0x306 */ u8 field_306[6];
    /* 0x30C */ Mtx mMtx;
    /* 0x33C */ dBgW* pm_bgw;
    /* 0x340 */ mDoExt_3DlineMat1_c mLineMat;
    /* 0x37C */ cXyz mPath0[2];
    /* 0x394 */ cXyz field_394;
    /* 0x3A0 */ cXyz mPos;
    /* 0x3AC */ s16 mAngleX;
    /* 0x3AE */ s16 mAngleZ;
    /* 0x3B0 */ s16 field_3B0;
    /* 0x3B2 */ s16 field_3B2;
    /* 0x3B4 */ f32 field_3B4;
    /* 0x3B8 */ f32 field_3B8;
    /* 0x3BC */ f32 field_3BC;
    /* 0x3C0 */ f32 field_3C0;
    /* 0x3C4 */ f32 field_3C4;
    /* 0x3C8 */ f32 field_3C8;
    /* 0x3CC */ dCcD_Stts mStts;
    /* 0x408 */ dCcD_Sph mSph;
    /* 0x534 */ dCcD_Cyl mCyl[2];
    /* 0x794 */ dCcD_Sph mSph2[2];
    /* 0x9EC */ s16 field_9EC;
};

#endif /* D_A_KLFT_H */
