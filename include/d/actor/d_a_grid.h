#ifndef D_A_GRID_H
#define D_A_GRID_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DPacket.h"
#include "d/d_kankyo.h"

class daGrid_c;

class daHo_packet_c : public J3DMatPacket {
public:
    daHo_packet_c() {
        mCount = 0;
        m189C = 0;
        m18A0 = 0;
        m189E = 0;
        mAlpha = 0xFF;
        setShapePacket(&mShapePacket);
    }
    virtual ~daHo_packet_c();
    void setBackNrm();
    void setNrmMtx(cXyz&);
    void setNrmVtx(cXyz*, int, int);
    void setTopNrmVtx(cXyz*);
    virtual void draw();

public:
    /* 0x3C */ J3DShapePacket mShapePacket;
    /* 0x80 */ Mtx mMtx;
    /* 0xB0 */ dKy_tevstr_c* mpTevStr;
    /* 0xB4 */ cXyz mNrm[2][0x55];
    /* 0x8AC */ cXyz mNrm2[2][0x55];
    /* 0x10A4 */ cXyz mPos[2][0x55];
    /* 0x189C */ s16 m189C;
    /* 0x189E */ s16 m189E;
    /* 0x18A0 */ s16 m18A0;
    /* 0x18A2 */ u8 mCount;
    /* 0x18A3 */ u8 mAlpha;
};  // Size: 0x18A4

class daGrid_c : public fopAc_ac_c {
public:
    daGrid_c() : mPacket() {}

    void force_calc_wind_rel_angle(short param_1) {
        m2216 = param_1;
        m2218 = 1;
    }

    cPhs_State _create();
    bool _delete();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhase1;
    /* 0x298 */ request_of_phase_process_class mPhase2;
    /* 0x2A0 */ daHo_packet_c mPacket;
    /* 0x1B44 */ u32 mWindAngle;
    /* 0x1B48 */ u8 mParam;
    /* 0x1B49 */ u8 mPad1B49[1];
    /* 0x1B4A */ s16 mB4A;
    /* 0x1B4C */ s16 mB4C;
    /* 0x1B4E */ s16 mB4E;
    /* 0x1B50 */ u8 mPad1B50[4];
    /* 0x1B54 */ f32 mWind[0x55];
    /* 0x1CA8 */ cXyz mWindPos[0x55];
    /* 0x20A4 */ u8 mPad20A4[0x15C];
    /* 0x2200 */ f32 m2200;
    /* 0x2204 */ f32 m2204;
    /* 0x2208 */ f32 m2208;
    /* 0x220C */ u8 mPad220C[4];
    /* 0x2210 */ s16 m2210;
    /* 0x2212 */ s16 m2212;
    /* 0x2214 */ u8 mPad2214[2];
    /* 0x2216 */ s16 m2216;
    /* 0x2218 */ u8 m2218;
    /* 0x2219 */ u8 mPad2219[3];
};  // Size: 0x221C

STATIC_ASSERT(sizeof(daHo_packet_c) == 0x18A4);
STATIC_ASSERT(sizeof(daGrid_c) == 0x221C);

class daHo_HIO_c {
public:
    daHo_HIO_c() {
        mChildId = -1;
        m05 = 1;
        m07 = 0;
        m14 = 40.0f;
        m06 = 0;
        m08 = 0;
        m18 = 0.5f;
        m1C = 0.1f;
        m0C = 0.1f;
        m20 = 0.4f;
        m24 = 1.0f;
        m28 = 1.0f;
        m2C = 1.0f;
        m30 = 0xFF;
        m31 = 0x32;
        m34 = 900.0f;
        m38 = 0;
        m39 = 0;
        m70 = 1.0f;
        m74 = 0.425f;
        m78 = 0.45f;
        m7C = 0.4f;
        m80 = 0.2f;
        m84 = 0.4f;
        m88 = 0.45f;
        m8C = 0.4f;
        m90 = 0.2f;
        m94 = 0.5f;
        m98 = 0.75f;
        m9C = 1.0f;
        mA0 = 1.0f;
        m3C = 0.05f;
        m40 = 0.125f;
        m44 = 0.175f;
        m48 = 0.15f;
        m4C = 0.0625f;
        m50 = 0.15f;
        m54 = 0.2f;
        m58 = 0.15f;
        m5C = 0.075f;
        m60 = 0.175f;
        m64 = 0.175f;
        m68 = 0.1f;
        m6C = 0.0f;
    }
    virtual ~daHo_HIO_c();

    /* 0x04 */ s8 mChildId;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ u8 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ u8 m10[4];
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ u8 m30;
    /* 0x31 */ u8 m31;
    /* 0x34 */ f32 m34;
    /* 0x38 */ u8 m38;
    /* 0x39 */ u8 m39;
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
    /* 0x94 */ f32 m94;
    /* 0x98 */ f32 m98;
    /* 0x9C */ f32 m9C;
    /* 0xA0 */ f32 mA0;
};  // Size: 0xA4

STATIC_ASSERT(sizeof(daHo_HIO_c) == 0xA4);

#endif /* D_A_GRID_H */
