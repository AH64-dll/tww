#ifndef D_A_GY_H
#define D_A_GY_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_acch.h"
#include "d/d_particle.h"

class daGy_Ctrl_c;

class daGy_c : public fopEn_enemy_c {
public:
    void _nodeControl(J3DNode*, J3DModel*);
    BOOL _createHeap();
    void setMtx();
    void setAnm();
    void setAtCollision();
    void setCollision();
    void setAimSpeedF();
    void modeDiveInit();
    void modeDive();
    void modeCircleInit();
    void modeCircle();
    void modeWithCircleInit();
    void modeWithCircle();
    void modeAttackInit();
    void modeWithAttackInit();
    void modeWithAttack();
    void modeAttack();
    void modeAttackPlayerInit();
    void modeAttackPlayer();
    void modeAttackBackInit();
    void modeAttackBack();
    void modeDamageInit();
    void modeDamage();
    void modeDeleteInit();
    void modeDelete();
    void modeDeleteBombInit();
    void modeDeleteBomb();
    void modeProcCall();
    void createWave();
    void setWave();
    void lineCheck(cXyz*, cXyz*);
    void checkTgHit();
    void getWaterY();
    bool _execute();
    void drawDebug();
    bool _draw();
    void createInit();
    cPhs_State _create();
    bool _delete();

public:
    /* 0x2AC */ s32 m2AC;
    /* 0x2B0 */ s32 m2B0;
    /* 0x2B4 */ f32 m2B4;
    /* 0x2B8 */ daGy_Ctrl_c* mpCtrl;
    /* 0x2BC */ cXyz m2BC;
    /* 0x2C8 */ request_of_phase_process_class mPhs;
    /* 0x2D0 */ u8 m2D0[0x2D4 - 0x2D0];
    /* 0x2D4 */ mDoExt_McaMorf* mpMorf;
    /* 0x2D8 */ mDoExt_invisibleModel m2D8;
    /* 0x2E0 */ dBgS_Acch mAcch;
    /* 0x4A4 */ dBgS_AcchCir mAcchCir;
    /* 0x4E4 */ f32 m4E4;
    /* 0x4E8 */ f32 m4E8;
    /* 0x4EC */ f32 m4EC;
    /* 0x4F0 */ f32 m4F0;
    /* 0x4F4 */ u8 m4F4[0x4F8 - 0x4F4];
    /* 0x4F8 */ s32 m4F8;
    /* 0x4FC */ s32 m4FC;
    /* 0x500 */ s32 m500;
    /* 0x504 */ f32 m504;
    /* 0x508 */ f32 m508;
    /* 0x50C */ dCcD_GObjInf m50C;
    /* 0x604 */ u8 m604[0x624 - 0x604];
    /* 0x624 */ cM3dGSph m624;
    /* 0x638 */ u8 m638[0x8C4 - 0x638];
    /* 0x8C4 */ dCcD_GStts mGStts;
    /* 0x8E4 */ u32 m8E4;
    /* 0x8E8 */ u8 m8E8[0x8F8 - 0x8E8];
    /* 0x8F8 */ cXyz m8F8;
    /* 0x904 */ cXyz m904;
    /* 0x910 */ u8 m910[0x914 - 0x910];
    /* 0x914 */ s32 m914;
    /* 0x918 */ s32 m918;
    /* 0x91C */ u8 m91C[0x920 - 0x91C];
    /* 0x920 */ s32 m920;
    /* 0x924 */ s32 m924;
    /* 0x928 */ s32 m928;
    /* 0x92C */ u8 m92C[0x978 - 0x92C];
    /* 0x978 */ dCcD_GStts m978;
    /* 0x998 */ dCcD_GObjInf m998;
    /* 0xA90 */ u8 mA90[0xAE0 - 0xA90];
    /* 0xAE0 */ dBgS_AcchCir mAE0;
    /* 0xB20 */ dBgS_Acch mB20;
    /* 0xCE4 */ u8 mCE4[0xD08 - 0xCE4];
    /* 0xD08 */ cXyz mD08;
    /* 0xD14 */ u8 mD14[0xD15 - 0xD14];
    /* 0xD15 */ u8 mD15;
    /* 0xD16 */ u8 mD16[0xD18 - 0xD16];
    /* 0xD18 */ dPa_waveEcallBack mD18;
    /* 0xD7C */ dPa_waveEcallBack mD7C;
    /* 0xDE0 */ dPa_splashEcallBack mDE0;
    /* 0xDFC */ u8 mDFC[0xE14 - 0xDFC];
    /* 0xE14 */ cBgS_LinChk mE14;
    /* 0xE6C */ u8 mE6C[0xE90 - 0xE6C];
};

class daGy_HIO_c {
public:
    daGy_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_GY_H */
