#ifndef D_A_BL_H
#define D_A_BL_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_path.h"
#include "c/c_damagereaction.h"
#include "m_Do/m_Do_ext.h"

class bl_class : public fopAc_ac_c {
public:
    /* 0x290 */ u8 m290[0x2AC - 0x290];
    /* 0x2AC */ request_of_phase_process_class mPhs;
    /* 0x2B4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2B8 */ u8 m2B8[0x2BC - 0x2B8];
    /* 0x2BC */ mDoExt_btkAnm* mpBtk2;
    /* 0x2C0 */ mDoExt_btkAnm* mpBtk1;
    /* 0x2C4 */ cXyz m2C4;
    /* 0x2D0 */ u8 m2D0;
    /* 0x2D1 */ u8 m2D1;
    /* 0x2D2 */ u8 m2D2;
    /* 0x2D3 */ u8 m2D3;
    /* 0x2D4 */ u8 m2D4;
    /* 0x2D5 */ u8 m2D5;
    /* 0x2D6 */ u8 m2D6[0x2D8 - 0x2D6];
    /* 0x2D8 */ dPath* mPath;
    /* 0x2DC */ u8 m2DC[0x2E9 - 0x2DC];
    /* 0x2E9 */ u8 m2E9;
    /* 0x2EA */ u8 m2EA;
    /* 0x2EB */ u8 m2EB[0x2EE - 0x2EB];
    /* 0x2EE */ s16 m2EE;
    /* 0x2F0 */ s16 m2F0;
    /* 0x2F2 */ u8 m2F2[0x2F4 - 0x2F2];
    /* 0x2F4 */ s16 m2F4;
    /* 0x2F6 */ s16 m2F6;
    /* 0x2F8 */ s16 m2F8[4];
    /* 0x300 */ s16 m300;
    /* 0x302 */ s16 m302;
    /* 0x304 */ s16 m304;
    /* 0x306 */ s16 m306;
    /* 0x308 */ s32 m308;
    /* 0x30C */ u8 m30C[0x310 - 0x30C];
    /* 0x310 */ f32 m310;
    /* 0x314 */ f32 m314;
    /* 0x318 */ f32 m318;
    /* 0x31C */ f32 m31C;
    /* 0x320 */ f32 m320;
    /* 0x324 */ f32 m324;
    /* 0x328 */ f32 m328;
    /* 0x32C */ dBgS_AcchCir mAcchCir;
    /* 0x36C */ dBgS_ObjAcch mAcch;
    /* 0x530 */ dCcD_Stts mStts;
    /* 0x56C */ dCcD_Sph mSph;
    /* 0x698 */ cXyz m698[3];
    /* 0x6BC */ cXyz m6BC;
    /* 0x6C8 */ dPa_smokeEcallBack mSmokeCB;
    /* 0x6E8 */ dPa_followEcallBack mFollowCB1;
    /* 0x6FC */ dPa_followEcallBack mFollowCB2;
    /* 0x710 */ fopAc_ac_c* m710;
    /* 0x714 */ s16 m714;
    /* 0x716 */ u8 m716;
    /* 0x717 */ u8 m717[0x718 - 0x717];
    /* 0x718 */ f32 m718;
    /* 0x71C */ s16 m71C;
    /* 0x71E */ s16 m71E;
    /* 0x720 */ u8 m720[0x740 - 0x720];
    /* 0x740 */ dCcD_Stts mStts2;
    /* 0x77C */ dCcD_Cyl mCyl;
    /* 0x8AC */ u8 m8AC[0x8C4 - 0x8AC];
    /* 0x8C4 */ dBgS_AcchCir mAcchCir2;
    /* 0x904 */ dBgS_ObjAcch mAcch2;
    /* 0xAC8 */ enemyfire mEnemyFire;
    /* 0xCF0 */ mDoExt_invisibleModel mInvisibleModel;
};

STATIC_ASSERT(sizeof(bl_class) == 0xCF8);

#endif /* D_A_BL_H */
