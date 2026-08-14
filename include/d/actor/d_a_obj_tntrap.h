#ifndef D_A_OBJ_TNTRAP_H
#define D_A_OBJ_TNTRAP_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_com_inf_game.h"
#include "SSystem/SComponent/c_phase.h"

class daObjTnTrap_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0,

        PRM_SWSAVE2_W = 8,
        PRM_SWSAVE2_S = 8,

        PRM_ARG0_W = 1,
        PRM_ARG0_S = 0x10,

        PRM_MAPTYPE_W = 2,
        PRM_MAPTYPE_S = 0x11,
    };

    s32 param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    s32 param_get_swSave2() const { return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }
    s32 param_get_arg0() const { return daObj::PrmAbstract(this, PRM_ARG0_W, PRM_ARG0_S); }
    s32 param_get_mapType() const { return daObj::PrmAbstract(this, PRM_MAPTYPE_W, PRM_MAPTYPE_S); }

    BOOL chk_appear();
    void set_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    BOOL create_heap();
    void particle_set(int, f32);
    void particle_delete(int);
    void set_se();
    void set_tri(int);
    BOOL chk_event_flg();
    void set_em_set_offsetY();
    cPhs_State _create();
    bool _delete();
    BOOL trap_off_wait_act_proc();
    BOOL trap_on_wait_act_proc();
    BOOL demo_regist_wait_act_proc();
    BOOL demo_wait_act_proc();
    BOOL demo_wait2_act_proc();
    BOOL demo_end_wait_act_proc();
    BOOL hide_wait_act_proc();
    void dummy_proc();
    void trap_off_wait_act_init_proc();
    void trap_on_wait_act_init_proc();
    void demo_regist_wait_act_init_proc();
    void demo_wait2_act_init_proc();
    void demo_end_wait_act_init_proc();
    void setup_action(int);
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ s32 mAppear;
    /* 0x29C */ dCcD_Stts mStts;
    /* 0x2D8 */ dCcD_Tri mTri[8];
    /* 0xD58 */ cBgW* mpBgW;
    /* 0xD5C */ Mtx mMtx;
    /* 0xD8C */ JPABaseEmitter* mBallPrt[2][2];
    /* 0xD9C */ JPABaseEmitter* mThunderPrt[2][3];
    /* 0xDB4 */ BOOL (daObjTnTrap_c::*mProcFunc)();
    /* 0xDC0 */ s32 mAction;
    /* 0xDC4 */ u8 mAppearFlg;
    /* 0xDC8 */ s32 mSwSave;
    /* 0xDCC */ s32 mSwSave2;
    /* 0xDD0 */ s32 mArg0;
    /* 0xDD4 */ s32 mMapType;
    /* 0xDD8 */ s16 mEvtIdx;
    /* 0xDE0 */ u8 mPrtSetFlg[2];
    /* 0xDE4 */ f32 mOffsetY[2];
};  // Size: 0xDEC

#endif /* D_A_OBJ_TNTRAP_H */
