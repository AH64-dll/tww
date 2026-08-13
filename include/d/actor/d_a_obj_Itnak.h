#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"

namespace daObjItnak {
    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void param_get_arg0() const {}
        void param_get_swbit() const {}

        virtual ~Act_c() {}  // __dt__Q210daObjItnak5Act_cFv (weak, member dtors)

        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        BOOL set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        bool _execute();
        bool _draw();

    public:
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ J3DModel* mpModel;
        /* 0x2A0 */ Mtx mMtx;
        /* 0x2D0 */ s32 mShadowIdx;
        /* 0x2D4 */ dBgS_ObjGndChk mGndChk;
        /* 0x328 */ f32 mGndHeight;
        /* 0x32C */ dCcD_Stts mStts;
        /* 0x368 */ dCcD_Cyl mCyl;
        /* 0x498 */ dCcD_Stts mStts2;
        /* 0x4D4 */ dCcD_Cyl mCyl2;
        /* 0x604 */ dCcD_Stts mStts3;
        /* 0x640 */ dCcD_Cyl mCyl3;
        /* 0x770 */ int m770;
        /* 0x774 */ int m774;

        static const char M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;
    };  // Size: 0x778
};

#endif /* D_A_OBJ_ITNAK_H */
