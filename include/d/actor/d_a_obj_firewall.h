#ifndef D_A_OBJ_FIREWALL_H
#define D_A_OBJ_FIREWALL_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_kankyo.h"

class daObjFirewall_c : public fopAc_ac_c {
public:
    void init_mtx();
    static BOOL solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void registCollisionTable();
    void setPointLight();
    void particle_set();
    void particle_delete();
    void seStart(unsigned long);
    void set_se(bool);
    void seDelete();
    void set_pl_se();
    void setup_burn_up();
    void setup_put_the_fire_out();
    cPhs_State _create();
    bool _delete();
    void wait_act_proc();
    void wait2_act_proc();
    void wait3_act_proc();
    void appear_act_proc();
    void demo_end_wait_act_proc();
    void burn_wait_act_proc();
    void retire_act_proc();
    bool _execute();
    bool _draw();

    typedef void (daObjFirewall_c::*ProcFunc)();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ dCcD_Stts mStts;
    /* 0x2D4 */ dCcD_Cyl mCyl;
    /* 0x404 */ J3DModel* mpModel;
    /* 0x408 */ dBgW* mpBgW;
    /* 0x40C */ mDoExt_btkAnm mBtk;
    /* 0x420 */ mDoExt_brkAnm mBrk;
    /* 0x438 */ JPABaseEmitter* mParticles[6];
    /* 0x450 */ JPABaseEmitter* mParticles2[5];
    /* 0x464 */ JPABaseEmitter* mParticle3;
    /* 0x468 */ s32 mParam;
    /* 0x46C */ LIGHT_INFLUENCE mLights[0x40];
    /* 0xC6C */ cXyz mBurnPos[0x40];
    /* 0xF6C */ u8 mPadF6C[0x106C - 0xF6C];
    /* 0x106C */ f32 m106C;
    /* 0x1070 */ ProcFunc mProc;
    /* 0x107C */ s16 mEventIdx;
    /* 0x107E */ u8 mSeState;
    /* 0x107F */ u8 mPad107F;
    /* 0x1080 */ cXyz mSePos[8];
    /* 0x10E0 */ u8 m10E0;
    /* 0x10E1 */ u8 m10E1;
    /* 0x10E2 */ u8 mPad10E2[2];
    /* 0x10E4 */ u32 m10E4;
    /* 0x10E8 */ u32 m10E8;
};  // Size: 0x10EC

STATIC_ASSERT(sizeof(daObjFirewall_c) == 0x10EC);

#endif /* D_A_OBJ_FIREWALL_H */
