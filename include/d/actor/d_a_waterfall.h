#ifndef D_A_WATERFALL_H
#define D_A_WATERFALL_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

class J3DModel;
class mDoExt_btkAnm;
class mDoExt_brkAnm;

class daWfall_c : public fopAc_ac_c {
public:
    inline bool _draw();

    bool _delete();
    BOOL CreateHeap();
    void CreateInit();
    cPhs_State _create();
    void set_mtx();
    void set_gate_mtx();
    void set_minamo_mtx();
    bool _execute();
    void mode_proc_call();
    void mode_wtr_on_init();
    void mode_wtr_on();
    void mode_wtr_off_init();
    void mode_wtr_off();
    BOOL setEmitter00Pos();
    BOOL setEmitter01Pos();
    f32 getWaterScaleFromGatePos();
    f32 getWaterHeight();
    void set_se();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel1;
    /* 0x29C */ J3DModel* mpModel2;
    /* 0x2A0 */ J3DModel* mpModel3;
    /* 0x2A4 */ s32 mMode;
    /* 0x2A8 */ void* m2A8;
    /* 0x2AC */ mDoExt_btkAnm mBtk1;
    /* 0x2C0 */ mDoExt_brkAnm mBrk;
    /* 0x2D8 */ mDoExt_btkAnm mBtk2;
    /* 0x2EC */ dPa_followEcallBack mFollow1;
    /* 0x300 */ dPa_followEcallBack mFollow2;
    /* 0x314 */ cXyz m314;
    /* 0x320 */ cXyz m320;
    /* 0x32C */ u8 m32C[0x338 - 0x32C];
    /* 0x338 */ csXyz m338[2];
    /* 0x344 */ cXyz m344;
    /* 0x350 */ s16 m350;
    /* 0x352 */ s16 m352;
    /* 0x354 */ u8 m354;
    /* 0x355 */ u8 m355;
    /* 0x356 */ u8 m356;
    /* 0x357 */ u8 m357;

    static const char m_arcname[6];
    static const s16 m_wait_timer;
    static const s16 m_heapsize[2];
};

#endif /* D_A_WATERFALL_H */
