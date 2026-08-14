#ifndef D_A_OBJ_YLZOU_H
#define D_A_OBJ_YLZOU_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "d/d_a_obj.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_com_inf_game.h"

class EffSmokeCB : public dPa_smokeEcallBack {
public:
    EffSmokeCB() {}
    virtual ~EffSmokeCB() {}

public:
    /* 0x20 */ cXyz mPos;
    /* 0x2C */ csXyz mAngle;
};  // Size: 0x34

class daObjYLzou_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 0,
    };

    s32 param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

    void set_start_type();
    void set_mtx();
    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void eff_set_slip_smoke_pos();
    void eff_smoke_slip_start();
    void eff_smoke_slip_end();
    void eff_smoke_slip_remove();
    void eff_smoke_proc();
    void vib_proc();
    cPhs_State _create();
    bool _delete();
    void move_ylzou_demo_start_wait_act_proc();
    void demo_regist_wait_act_proc();
    void demo_vib_start_wait_act_proc();
    void demo_vib_act_proc();
    void move_ylzou_demo_move_act_proc();
    void go_up_stairs_demo_move_act_proc();
    void demo_end_wait_act_proc();
    void wait_act_proc();
    void move_ylzou_demo_start_wait_act_init_proc();
    void demo_regist_wait_act_init_proc();
    void move_ylzou_demo_vib_start_wait_act_init_proc();
    void move_ylzou_demo_vib_act_init_proc();
    void move_ylzou_demo_move_act_init_proc();
    void demo_end_wait_act_init_proc();
    void open_wait_act_init_proc();
    void close_wait_act_init_proc();
    void go_up_stairs_demo_move_start_wait_act_init_proc();
    void go_up_stairs_demo_move_act_init_proc();
    void setup_action(int);
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ dBgW* mpBgW;
    /* 0x2A0 */ Mtx mBaseMtx;
    /* 0x2D0 */ void (daObjYLzou_c::*mActionFn)();
    /* 0x2DC */ s32 mAction;
    /* 0x2E0 */ s32 mParam;
    /* 0x2E4 */ s16 mEventId;
    /* 0x2E8 */ s32 mType;
    /* 0x2EC */ s32 mDemoIdx;
    /* 0x2F0 */ EffSmokeCB mSmokeCbs[2];
    /* 0x358 */ s16 mAngle;
    /* 0x35C */ f32 mVibStrength;
    /* 0x360 */ u8 mSmokeState;
    /* 0x361 */ u8 mSmokeNext;
    /* 0x364 */ s32 mVibState;
    /* 0x368 */ s32 mVibNext;
};  // Size: 0x36C

#endif /* D_A_OBJ_YLZOU_H */
