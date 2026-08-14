#ifndef D_A_OBJ_VDS_H
#define D_A_OBJ_VDS_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_bg_w.h"
#include "d/d_kankyo.h"
#include "d/d_a_obj.h"
#include "f_op/f_op_actor_mng.h"

class J3DAnmTransformKey;
class J3DAnmTevRegKey;

namespace daObjVds {
    static void* ds_search_switchCB(void*, void*);

    class Act_c : public fopAc_ac_c {
    public:
        virtual ~Act_c() {}

        s32 SetLoopJointAnimation(J3DAnmTransformKey*, J3DAnmTransformKey*, f32, f32);
        s32 PlayLoopJointAnimation();
        void set_first_process();
        static BOOL solidHeapCB(fopAc_ac_c*);
        void* search_switchCB(fopAc_ac_c*);
        s32 process_off_init();
        void process_off_main();
        s32 process_on_init();
        void process_on_main();
        s32 process_init(int);
        void process_main();
        void process_common();
        void create_point_light(int, cXyz*);
        void execute_point_light();
        void delete_point_light();
        void Event_init();
        void Event_exe();
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();

        static const char M_arcname[];

    public:
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ Mtx mMtx;
        /* 0x2CC */ mDoExt_McaMorf* M_anm0;
        /* 0x2D0 */ J3DAnmTransformKey* M_bck_data0;
        /* 0x2D4 */ mDoExt_brkAnm mBrk0;
        /* 0x2EC */ J3DAnmTevRegKey* M_brk_data0;
        /* 0x2F0 */ mDoExt_McaMorf* M_anm1;
        /* 0x2F4 */ J3DAnmTransformKey* M_bck_data1;
        /* 0x2F8 */ mDoExt_brkAnm mBrk1;
        /* 0x310 */ J3DAnmTevRegKey* M_brk_data1;
        /* 0x314 */ dBgW* mBgW;
        /* 0x318 */ s32 m318;
        /* 0x31C */ s32 mProcIdx;
        /* 0x320 */ s32 mProcState;
        /* 0x324 */ fpc_ProcID mTargetIds[2];
        /* 0x32C */ f32 mPowers[2];
        /* 0x334 */ s16 mEvtIdx;
        /* 0x336 */ s16 mEvtState;
        /* 0x338 */ s16 mEvtIdx2;
        /* 0x33C */ LIGHT_INFLUENCE mLights[2];
        /* 0x37C */ cXyz mBurnPos[2];
    };  // Size: 0x3A4
};

#endif /* D_A_OBJ_VDS_H */
