#ifndef D_A_OBJ_MAGMAROCK_H
#define D_A_OBJ_MAGMAROCK_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_kankyo.h"
#include "d/d_particle.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"

class dBgW;

namespace daObjMagmarock {
    static void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
    static BOOL CheckCreateHeap(fopAc_ac_c*);

    class Act_c : public fopAc_ac_c {
    public:
        virtual bool LiftUpRequest(cXyz&);
        virtual bool BeforeLiftRequest(cXyz&);

        void set_mtx();
        void demo_move();
        void ControlEffect();
        void play_anim();
        void appear_proc_init();
        void appear_proc();
        void wait_proc_init();
        void wait_proc();
        void stay_proc_init();
        void stay_proc();
        void quake_proc_init();
        void quake_proc();
        void vanish_proc_init();
        void vanish_proc();
        BOOL CreateHeap();
        void CreateInit();
        void calc_ground_quat();
        inline bool _execute();

        static const char M_arcname[];
        static const GXColor default_color;

    public:
        /* 0x290 */ /* vtable */
        /* 0x294 */ s32 field_0x294;
        /* 0x298 */ s16 mRideAngle;
        /* 0x29A */ s16 m29A;
        /* 0x29C */ s16 m29C;
        /* 0x29E */ u8 m29E;
        /* 0x29F */ u8 m29F;
        /* 0x2A0 */ JPABaseEmitter* mpLavaSmoke;
        /* 0x2A4 */ JPABaseEmitter* mpLavaBubble;
        /* 0x2A8 */ JPABaseEmitter* mpEffectA;
        /* 0x2AC */ JPABaseEmitter* mpEffectB;
        /* 0x2B0 */ Quaternion mQuat1;
        /* 0x2C0 */ Quaternion mQuat2;
        /* 0x2D0 */ Quaternion mQuat3;
        /* 0x2E0 */ void (Act_c::*mProcFunc)();
        /* 0x2EC */ request_of_phase_process_class mPhs;
        /* 0x2F4 */ J3DModel* mpModel;
        /* 0x2F8 */ J3DAnmTevRegKey* M_brk;
        /* 0x2FC */ mDoExt_brkAnm mBrkAnm;
        /* 0x314 */ J3DAnmTransform* M_bck;
        /* 0x318 */ mDoExt_bckAnm mBckAnm;
        /* 0x328 */ Mtx mMtx;
        /* 0x358 */ dBgW* mpBgW;
        /* 0x35C */ dKy_tevstr_c mTevStr;
        /* 0x40C */ cXyz mCorner[3];
        /* 0x430 */ f32 mQuakeAngle;
        /* 0x434 */ f32 mBckFrame;
        /* 0x438 */ f32 mBrkFrame;
        /* 0x43C */ cXyz mLiftPos;
        /* 0x448 */ s32 mProcTimer;
        /* 0x44C */ s32 mAnmIdx;
        /* 0x450 */ s32 field_0x450;
        /* 0x454 */ s16 mAngle;
        /* 0x456 */ s16 mAngleAdd;
        /* 0x458 */ s16 field_0x458;
        /* 0x45A */ s16 m45A;
        /* 0x45C */ s16 m45C;
        /* 0x45E */ s16 m45E;
    };  // Size: 0x460

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_MAGMAROCK_H */
