#ifndef D_A_OBJ_TRAP_H
#define D_A_OBJ_TRAP_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_w.h"

class dPath;

class daObjTrap_c : public fopAc_ac_c {
public:
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    void set_co_pos();
    void get_ground();
    void circle_search();
    void set_move_info();
    void check_arrival();
    cXyz check_wall();
    cXyz check_block(cXyz);
    BOOL check_block_target_pos(cXyz*);
    void set_vib_mode();
    void vibrate();
    void bound();
    void set_shine();
    void shine_move();
    bool _execute();
    bool _draw();

    static const f32 M_speed_table[];
    static const s16 M_wait_f_table[];
    static const char M_arcname[];

public:
    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ mDoExt_btkAnm mBtk;
    /* 0x2A8 */ request_of_phase_process_class mPhs;
    /* 0x2B0 */ dCcD_Stts mStts;
    /* 0x2EC */ dCcD_Cyl mCyl;
    /* 0x41C */ dBgS_ObjGndChk mGndChk;
    /* 0x470 */ f32 mGroundY;
    /* 0x474 */ dPath* mpPath;
    /* 0x478 */ cXyz mPathPosA;
    /* 0x484 */ cXyz mPathPosB;
    /* 0x490 */ cXyz mDir;
    /* 0x49C */ cXyz mSpeedVec;
    /* 0x4A8 */ cXyz mTargetPos;
    /* 0x4B4 */ cXyz mCurPos;
    /* 0x4C0 */ cXyz mVibPos;
    /* 0x4CC */ f32 mDist;
    /* 0x4D0 */ s16 mWaitTimer;
    /* 0x4D2 */ s16 mBoundTimer;
    /* 0x4D4 */ f32 mVibF;
    /* 0x4D8 */ s16 mVibTimer;
    /* 0x4DA */ s16 mAngleY;
    /* 0x4DC */ u8 mPathIdx;
    /* 0x4DD */ u8 mParam;
    /* 0x4DE */ u8 mDirValid;
    /* 0x4DF */ u8 mVibMode;
    /* 0x4E0 */ u8 mShineFlag;
    /* 0x4E1 */ u8 mSpeedIdx;
    /* 0x4E4 */ f32 mSpeed;
    /* 0x4E8 */ s16 mWait;
    /* 0x4EC */ dBgW* mpBgW;
}; // Size: 0x4F0

STATIC_ASSERT(sizeof(daObjTrap_c) == 0x4F0);

#endif /* D_A_OBJ_TRAP_H */
