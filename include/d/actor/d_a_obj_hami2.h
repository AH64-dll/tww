#ifndef D_A_OBJ_HAMI2_H
#define D_A_OBJ_HAMI2_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor_mng.h"

namespace daObjHami2 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWSAVE_W_e = 8,
            PRM_SWSAVE_S_e = 0,
        };

        void prm_get_swSave() const {}

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHami2_close_stop();
        void daObjHami2_open_demo_wait();
        void daObjHami2_open_demo();
        void daObjHami2_open_stop();
        void daObjHami2_close_demo_wait();
        void daObjHami2_close_demo();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

    public:
        /* 0x2C8 */ s16 mSpinAngle;
        /* 0x2CA */ u8 field_0x2CA[0x2CC - 0x2CA];
        /* 0x2CC */ request_of_phase_process_class mPhs;
        /* 0x2D4 */ J3DModel* mpModel;
        /* 0x2D8 */ dBgW* mpBgW;
        /* 0x2DC */ Mtx mMtx;
        /* 0x30C */ s32 mState;
        /* 0x310 */ s16 mOpenEventIdx;
        /* 0x312 */ s16 mCloseEventIdx;

        static const char M_arcname[];
        static const char M_evname[];
        static Mtx M_tmp_mtx;
    };
};

#endif /* D_A_OBJ_HAMI2_H */
