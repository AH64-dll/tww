#ifndef D_A_SSS_H
#define D_A_SSS_H

#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"

struct sss_s {
    /* 0x00 */ Vec mPos;
    /* 0x0C */ Vec m0C;
    /* 0x18 */ f32 mSize;

    sss_s() {}
    ~sss_s() {}
}; // Size: 0x1C

class sss_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ u8 m2B8;
    /* 0x2B9 */ u8 m2B9;
    /* 0x2BA */ u8 m2BA;
    /* 0x2BC */ s16 m2BC;
    /* 0x2BE */ s16 m2BE;
    /* 0x2C0 */ s16 m2C0;
    /* 0x2C2 */ s16 m2C2[2];
    /* 0x2C6 */ s16 m2C6;
    /* 0x2C8 */ cXyz m2C8;
    /* 0x2D4 */ cXyz m2D4;
    /* 0x2E0 */ s16 m2E0;
    /* 0x2E2 */ s16 m2E2;
    /* 0x2E8 */ f32 m2E8;
    /* 0x2F0 */ f32 m2F0;
    /* 0x2F4 */ f32 m2F4;
    /* 0x2F8 */ f32 m2F8;
    /* 0x2FC */ f32 m2FC;
    /* 0x300 */ mDoExt_3DlineMat1_c m300;
    /* 0x33C */ sss_s m33C[10];
    /* 0x454 */ mDoExt_3DlineMat1_c m454;
    /* 0x490 */ sss_s m490[5];
    /* 0x51C */ dCcD_Stts mStts;
    /* 0x558 */ dCcD_Sph mSph[3];
    /* 0x8DC */ dCcD_Sph m8DC;
    /* 0xA08 */ f32 mA08;
    /* 0xA0C */ s16 mA0C;
    /* 0xA10 */ JPABaseEmitter* mpEmitterA10;
    /* 0xA14 */ JPABaseEmitter* mpEmitterA14;
    /* 0xA18 */ u8 mA18;
}; // Size: 0xA1C

#endif /* D_A_SSS_H */
