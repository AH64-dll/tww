#ifndef D_A_OBJ_FIREWALL_H
#define D_A_OBJ_FIREWALL_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_bg_w.h"

class daObjFirewall_c : public fopAc_ac_c {
public:
    void param_get_swSave() const {}

    void init_mtx();
    void solidHeapCB(fopAc_ac_c*);
    void create_heap();
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

public:
    /* 0x290 */ u8 mPad290[0x404 - 0x290];  // TODO: dCcD_Stts + unverified members (retail 0x2B0/0x2D4/0x314/0x31C/0x350)
    /* 0x404 */ J3DModel* mpModel;
    /* 0x408 */ dBgW* mpBgW;
    /* 0x40C */ mDoExt_btkAnm mBtk;
    /* 0x420 */ mDoExt_brkAnm mBrk;
    /* 0x438 */ u8 mPad438[0x106C - 0x438];
    /* 0x106C */ s32 m106C;
    /* 0x1070 */ cXyz m1070;
    /* 0x107C */ s16 m107C;
    /* 0x107E */ u8 mSeState;
    /* 0x107F */ u8 mPad107F;
    /* 0x1080 */ Vec mSePos[8];
    /* 0x10E0 */ u8 m10E0;
    /* 0x10E1 */ u8 m10E1;
    /* 0x10E4 */ u8 mPad10E4[4];
    /* 0x10E8 */ u32 m10E8;
};  // Size: 0x10EC

STATIC_ASSERT(sizeof(daObjFirewall_c) == 0x10EC);

#endif /* D_A_OBJ_FIREWALL_H */
