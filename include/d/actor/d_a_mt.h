#ifndef D_A_MT_H
#define D_A_MT_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_hostIO.h"

class mDoExt_McaMorf;
class J3DAnmTexPattern;
class J3DTexNoAnm;

class daMt_HIO_c : public mDoHIO_entry_c {
public:
    daMt_HIO_c();
    virtual ~daMt_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

    /* 0x04 */ u8 m04;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ s16 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ s16 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ s16 m30;
    /* 0x32 */ s16 m32;
    /* 0x34 */ f32 m34;
    /* 0x38 */ s16 m38;
    /* 0x3A */ s16 m3A;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ s16 m50;
    /* 0x52 */ s16 m52;
    /* 0x54 */ s16 m54;
    /* 0x58 */ f32 m58;
    /* 0x5C */ f32 m5C;
}; // size = 0x60

class mt_class : public fopEn_enemy_c {
public:
    /* 0x2AC */ request_of_phase_process_class mPhase;
    /* 0x2B4 */ u8 m2B4;
    /* 0x2B5 */ u8 m2B5;
    /* 0x2B6 */ u8 m2B6;
    /* 0x2B7 */ u8 m2B7;
    /* 0x2B8 */ u8 m2B8;
    /* 0x2B9 */ u8 m2B9;
    /* 0x2BA */ u8 m2BA;
    /* 0x2BB */ u8 m2BB;
    /* 0x2BC */ u8 m2BC;
    /* 0x2BD */ u8 m2BD;
    /* 0x2BE */ u8 m2BE;
    /* 0x2C0 */ u32 m2C0;
    /* 0x2C4 */ mDoExt_McaMorf* mpMorf[8];
    /* 0x2E4 */ u8 m2E4;
    /* 0x2E5 */ u8 m2E5[0x2E8 - 0x2E5];
    /* 0x2E8 */ u32 m2E8;
    /* 0x2EC */ u32 m2EC;
    /* 0x2F0 */ u32 m2F0;
    /* 0x2F4 */ u8 m2F4[0x310 - 0x2F4];
    /* 0x310 */ u32 m310;
    /* 0x314 */ u8 m314[0x31C - 0x314];
    /* 0x31C */ u32 m31C;
    /* 0x320 */ f64 m320;
    /* 0x328 */ u8 m328[0x330 - 0x328];
    /* 0x330 */ f64 m330;
    /* 0x338 */ f32 m338;
    /* 0x33C */ J3DAnmTexPattern* m33C;
    /* 0x340 */ J3DTexNoAnm* m340;
    /* 0x344 */ u8 m344;
    /* 0x345 */ u8 m345;
    /* 0x346 */ u8 m346;
    /* 0x347 */ u8 m347;
    /* 0x348 */ u8 m348;
    /* 0x349 */ u8 m349;
    /* 0x34A */ s16 m34A;
    /* 0x34C */ u8 m34C;
    /* 0x34D */ u8 m34D[0x350 - 0x34D];
    /* 0x350 */ cXyz m350[8];
    /* 0x3B0 */ dPa_followEcallBack m3B0[8];
    /* 0x450 */ JPABaseEmitter* m450;
    /* 0x454 */ u8 m454;
    /* 0x455 */ u8 m455;
    /* 0x456 */ s16 m456;
    /* 0x458 */ s16 m458;
    /* 0x45A */ s16 m45A;
    /* 0x45C */ s16 m45C;
    /* 0x45E */ s16 m45E;
    /* 0x460 */ s16 m460;
    /* 0x462 */ s16 m462;
    /* 0x464 */ s16 m464;
    /* 0x466 */ s16 m466;
    /* 0x468 */ s16 m468;
    /* 0x46A */ s16 m46A;
    /* 0x46C */ s16 m46C;
    /* 0x46E */ s16 m46E;
    /* 0x470 */ f32 m470;
    /* 0x474 */ f32 m474;
    /* 0x478 */ f32 m478;
    /* 0x47C */ f32 m47C;
    /* 0x480 */ f32 m480;
    /* 0x484 */ f32 m484;
    /* 0x488 */ s16 m488[0xC];
    /* 0x4A0 */ cXyz m4A0[8];
    /* 0x500 */ cXyz m500[8];
    /* 0x560 */ csXyz m560[8];
    /* 0x590 */ cXyz m590[8];
    /* 0x5F0 */ s16 m5F0[8];
    /* 0x600 */ f32 m600[8];
    /* 0x620 */ f32 m620;
    /* 0x624 */ u8 m624[0x640 - 0x624];
    /* 0x640 */ csXyz m640[30];
    /* 0x6F4 */ cXyz m6F4[64];
    /* 0x9F4 */ csXyz m9F4[64];
    /* 0xB74 */ u8 mB74[0xC08 - 0xB74];
    /* 0xC08 */ dBgS_AcchCir mC08;
    /* 0xC48 */ dBgS_ObjAcch mAcch;
    /* 0xE0C */ dCcD_Stts mStts;
    /* 0xE48 */ dCcD_Sph mE48[8];
    /* 0x17A8 */ dCcD_Sph m17A8;
    /* 0x18D4 */ u8 m18D4;
    /* 0x18D5 */ u8 m18D5[0x18D8 - 0x18D5];
    /* 0x18D8 */ J3DModel* m18D8[6];
    /* 0x18F0 */ f32 m18F0;
    /* 0x18F4 */ f32 m18F4;
    /* 0x18F8 */ u8 m18F8;
    /* 0x18F9 */ u8 m18F9;
    /* 0x18FA */ u8 m18FA;
    /* 0x18FB */ u8 m18FB;
    /* 0x18FC */ s16 m18FC;
    /* 0x18FE */ u8 m18FE[0x1930 - 0x18FE];
    /* 0x1930 */ dCcD_Stts m1930;
    /* 0x196C */ dCcD_Cyl m196C;
    /* 0x1A9C */ u8 m1A9C[0x1AB4 - 0x1A9C];
    /* 0x1AB4 */ dBgS_AcchCir m1AB4;
    /* 0x1AF4 */ dBgS_ObjAcch m1AF4;
    /* 0x1CB8 */ u32 m1CB8;
    /* 0x1CBC */ s8 m1CBC;
    /* 0x1CBD */ u8 m1CBD[0x1CC0 - 0x1CBD];
}; // size = 0x1CC0

#endif /* D_A_MT_H */
