#ifndef D_A_OBJ_BALANCELIFT_H
#define D_A_OBJ_BALANCELIFT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"
#include "d/d_path.h"
#include "d/d_chain.h"
#include "dolphin/mtx/quat.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class daBalancelift_c : public fopAc_ac_c {
public:
    inline bool _execute();

    void calc_quat();
    void set_mtx();
    void calc_weight();
    BOOL CreateHeap();
    cPhs_State CreateInit();

    static const char M_arcname[];

    /* 0x290 */ cXyz mLeftPos;
    /* 0x29C */ cXyz mRightPos;
    /* 0x2A8 */ cXyz mSpringPos;
    /* 0x2B4 */ cXyz mTarget;
    /* 0x2C0 */ cXyz mChainPos;
    /* 0x2CC */ Quaternion mQuatL;
    /* 0x2DC */ Quaternion mQuatR;
    /* 0x2EC */ cXyz mOldPos;
    /* 0x2F8 */ cXyz mOffset;
    /* 0x304 */ cXyz mPos;
    /* 0x310 */ f32 mCurrentY;
    /* 0x314 */ s16 mLeftWeight;
    /* 0x316 */ s16 field_0x316;
    /* 0x318 */ s16* mWeightPtr;
    /* 0x31C */ s16 mDir;
    /* 0x31E */ s16 mRightWeight;
    /* 0x320 */ s16* mWeightPtr2;
    /* 0x324 */ request_of_phase_process_class mPhase;
    /* 0x32C */ J3DModel* M_mdl;
    /* 0x330 */ Mtx mBgMtx;
    /* 0x360 */ dPath* mPath;
    /* 0x364 */ dBgW* pm_bgw;
    /* 0x368 */ f32 mVelocity;
    /* 0x36C */ cXyz mLine[4];
    /* 0x39C */ mDoExt_3DlineMat0_c m3Dline;
    /* 0x3B8 */ dChain_packet_c* m_chain;
    /* 0x3BC */ dCcD_Stts mStts;
    /* 0x3F8 */ dCcD_Cyl mCyl;
};  // Size: 0x528

class daBalancelift_HIO_c : public JORReflexible {
public:
    daBalancelift_HIO_c();
    virtual ~daBalancelift_HIO_c() {}

    /* 0x04 */ s8 mChildIdx;
    /* 0x08 */ f32 mFloat0x08;
    /* 0x0C */ f32 mFloat0x0C;
    /* 0x10 */ f32 mFloat0x10;
    /* 0x14 */ f32 mFloat0x14;
    /* 0x18 */ f32 mFloat0x18;
    /* 0x1C */ f32 mFloat0x1C;
    /* 0x20 */ f32 mFloat0x20;
    /* 0x24 */ f32 mFloat0x24;
    /* 0x28 */ f32 mFloat0x28;
    /* 0x2C */ f32 mFloat0x2C;
    /* 0x30 */ f32 mFloat0x30;
    /* 0x34 */ f32 mFloat0x34;
};  // Size: 0x38

#endif /* D_A_OBJ_BALANCELIFT_H */
