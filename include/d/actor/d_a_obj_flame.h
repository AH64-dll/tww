#ifndef D_A_OBJ_FLAME_H
#define D_A_OBJ_FLAME_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "SSystem/SComponent/c_phase.h"

class JPABaseEmitter;
class mDoExt_btkAnm;
class mDoExt_brkAnm;

namespace daObjFlame {
    struct attr_base_s {
        /* 0x00 */ s32 mKiMax;
        /* 0x04 */ s16 mRotAdd[2];
        /* 0x08 */ s16 mF08;
        /* 0x0A */ s16 mF0A;
        /* 0x0C */ s16 mF0C;
        /* 0x0E */ s16 mF0E;
        /* 0x10 */ s16 mF10;
        /* 0x12 */ s16 mF12;
    };  // Size: 0x14

    struct attr_scl_s {
        /* 0x00 */ f32 mScale;
        /* 0x04 */ f32 mF04;
        /* 0x08 */ f32 mF08;
        /* 0x0C */ f32 mF0C;
        /* 0x10 */ s32 mBdlResID;
        /* 0x14 */ s32 mBtkResID;
        /* 0x18 */ s32 mBrkResID;
        /* 0x1C */ u32 mHeapSize;
        /* 0x20 */ f32 mRate;
        /* 0x24 */ f32 mF24;
        /* 0x28 */ u32 mEmID;
        /* 0x2C */ u8 mF2C;
        /* 0x2D */ u8 mF2D;
        /* 0x2E */ u8 mF2E;
        /* 0x2F */ u8 mF2F;
        /* 0x30 */ f32 mEm0SclX;
        /* 0x34 */ f32 mEm0SclY;
        /* 0x38 */ f32 mEm1SclX;
        /* 0x3C */ f32 mEm1SclY;
        /* 0x40 */ f32 mEm2Scl;
        /* 0x44 */ f32 mF44;
        /* 0x48 */ s16 mCull[6];
        /* 0x54 */ f32 mF54;
    };  // Size: 0x58

    class Act_c : public fopAc_ac_c {
    public:
        static char M_arcname[9];
        static const attr_base_s M_attr_base;
        static const dCcD_SrcCps M_cps_src;
        static const attr_scl_s M_attr_scl[4];

        enum Prm_e {
            PRM_SCH_W = 8,
            PRM_SCH_S = 0,

            PRM_KINUM_W = 5,
            PRM_KINUM_S = 8,

            PRM_PRM_W = 2,
            PRM_PRM_S = 13,

            PRM_TYPE_W = 2,
            PRM_TYPE_S = 28,

            PRM_HAZE_W = 1,
            PRM_HAZE_S = 31,

            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 16,
        };

        s32 prm_get_sch() const { return daObj::PrmAbstract(this, PRM_SCH_W, PRM_SCH_S); }
        s32 prm_get_kiNum() const { return daObj::PrmAbstract(this, PRM_KINUM_W, PRM_KINUM_S); }
        s32 prm_get_prm() const { return daObj::PrmAbstract(this, PRM_PRM_W, PRM_PRM_S); }
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        s32 prm_get_haze() const { return daObj::PrmAbstract(this, PRM_HAZE_W, PRM_HAZE_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

        void set_switch();
        static int solidHeapCB(fopAc_ac_c*);
        int create_heap();
        void create_mode_init();
        void set_mtx();
        void init_mtx();
        void em_position();
        void em_simple_set();
        void em_simple_inv();
        void em_manual_set();
        void em_manual_inv();
        void ki_init();
        void ki_make();
        void eff_hase();
        void se_fireblast_omen();
        static void* liftup_magmarock(void*, void*);
        static void* liftup_mflft(void*, void*);
        void mode_wait();
        void mode_wait2();
        void mode_l_before();
        void mode_l_u();
        void mode_u();
        void mode_u_l();
        void mode_l_after();
        void mode_proc_call();
        cPhs_State _create();

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_btkAnm* mpBtkAnm;
        /* 0x2A0 */ mDoExt_brkAnm* mpBrkAnm;
        /* 0x2A4 */ dCcD_Stts mStts;
        /* 0x2E0 */ dCcD_Cps mCps;
        /* 0x418 */ cXyz mCpsP0;
        /* 0x424 */ cXyz mCpsP1;
        /* 0x430 */ f32 mCpsRad;
        /* 0x434 */ bool mbCol;
        /* 0x435 */ u8 m435[0x438 - 0x435];
        /* 0x438 */ int mType;
        /* 0x43C */ int mModeProc;
        /* 0x440 */ f32 mTimer;
        /* 0x444 */ f32 mHeight;
        /* 0x448 */ JPABaseEmitter* mpEmitter0;
        /* 0x44C */ JPABaseEmitter* mpEmitter1;
        /* 0x450 */ JPABaseEmitter* mpEmitter2;
        /* 0x454 */ s8 mEm0State;
        /* 0x455 */ s8 mEm1State;
        /* 0x456 */ s8 mEm2State;
        /* 0x457 */ s8 mbEmPosition;
        /* 0x458 */ u8 mReverb;
        /* 0x459 */ u8 mbLiftup;
        /* 0x45A */ u8 mbKi;
        /* 0x45B */ u8 m45B;
        /* 0x45C */ int mKiTimer;
        /* 0x460 */ int mKiCount;
        /* 0x464 */ int mKiIdx;
        /* 0x468 */ s16 mRotY;
        /* 0x46A */ u8 m46A[0x46C - 0x46A];
        /* 0x46C */ f32 mScaleX;
        /* 0x470 */ f32 mScaleY;
        /* 0x474 */ cXyz mOrigScale;
    };

    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_FLAME_H */
