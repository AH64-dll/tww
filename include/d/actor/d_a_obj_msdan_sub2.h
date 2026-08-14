#ifndef D_A_OBJ_MSDAN_SUB2_H
#define D_A_OBJ_MSDAN_SUB2_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjMsdanSub2 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x0,
            PRM_SWSAVE2_W = 0x8,
            PRM_SWSAVE2_S = 0x8,
        };

        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_swSave2() const { return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ s32 mCounter;
        /* 0x2D8 */ f32 mOffset;
        /* 0x2DC */ f32 mTimer;

        static const char M_arcname[];
        static Mtx M_tmp_mtx;
    };  // Size: 0x2E0
};

#endif /* D_A_OBJ_MSDAN_SUB2_H */
