#ifndef D_A_ICELIFT_H
#define D_A_ICELIFT_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_path.h"
#include "dolphin/mtx/quat.h"

class daIlift_c : public fopAc_ac_c {
public:
    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    bool _execute();
    void lift_wave();
    void path_move();
    void lift_normal_move();
    void set_next_pnt();
    bool _draw();

    static const int m_bmdidx[2];
    static const int m_dzbidx[2];
    static const u32 m_heapsize[2];
    static const f32 m_down_param;
    static const f32 m_max_speed;
    static const char* m_arcname[2];

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mBgMtx;
    /* 0x2D0 */ dBgS_ObjAcch mAcch;
    /* 0x494 */ dBgS_AcchCir mAcchCir;
    /* 0x4D4 */ u8 mOnRide;
    /* 0x4D5 */ u8 mPrevOnRide;
    /* 0x4D6 */ s16 mTiltAngle;
    /* 0x4D8 */ s16 mTiltAngleTarget;
    /* 0x4DC */ Quaternion mTargetRotation;
    /* 0x4EC */ Quaternion mCurrentRotation;
    /* 0x4FC */ cXyz mDiff;
    /* 0x508 */ f32 m508;
    /* 0x50C */ s32 mTimer;
    /* 0x510 */ s32 m510;
    /* 0x514 */ u8 m514[0x518 - 0x514];
    /* 0x518 */ u8 mType;
    /* 0x51C */ cXyz mNextPnt;
    /* 0x528 */ cXyz mPrevPnt;
    /* 0x534 */ dPath* mPath;
    /* 0x538 */ f32 mSpeed;
    /* 0x53C */ f32 m53C;
    /* 0x540 */ u16 mPointNo;
    /* 0x542 */ u8 mPathNo;
    /* 0x543 */ u8 mPointIdx;
    /* 0x544 */ u8 mPointDir;
    /* 0x545 */ u8 mMoveMode;
    /* 0x546 */ u8 m546[0x54C - 0x546];
    /* 0x54C */ f32 mDist;
    /* 0x550 */ u8 m550[0x554 - 0x550];
    /* 0x554 */ s32 mSwNo;
    /* 0x558 */ cXyz mPlayerPos;
};  // Size: 0x564

namespace daIlift_prm {
    inline u8 getType(daIlift_c* i_this) { return fopAcM_GetParam(i_this) & 0x0F; }
    inline u8 getPathId(daIlift_c* i_this) { return (fopAcM_GetParam(i_this) >> 4) & 0xFF; }
    inline u8 getSwNo(daIlift_c* i_this) { return (fopAcM_GetParam(i_this) >> 12) & 0xFF; }
}

#endif /* D_A_ICELIFT_H */
