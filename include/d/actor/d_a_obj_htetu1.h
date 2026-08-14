#ifndef D_A_OBJ_HTETU1_H
#define D_A_OBJ_HTETU1_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "SSystem/SComponent/c_phase.h"

class daObjHtetu1Splash_c : public dPa_followEcallBack {
public:
    void create_s(unsigned short, cXyz*, csXyz*, dKy_tevstr_c*);
    bool chk_stop() { return mStop != 0; }
    void delete_s() {
        if (mpEmitter != NULL) {
            remove();
            mStop = 0;
        }
    }
    s16 get_timer() { return mTimer; }
    void set_pos_y(f32 y) { mPos.y = y; }
    void stop_particle() {
        if (mpEmitter != NULL) {
            mpEmitter->stopCreateParticle();
            mStop = 0;
        }
    }
    void play_particle() {
        if (mpEmitter != NULL) {
            mpEmitter->playCreateParticle();
            mStop = 1;
        }
    }
    void sub_timer() { mTimer--; }
    void timer_play_particle(s16 timer) {
        if (mpEmitter != NULL) {
            mpEmitter->playCreateParticle();
            mStop = 1;
            mTimer = timer;
        }
    }

    /* 0x14 */ cXyz mPos;
    /* 0x20 */ csXyz mAngle;
    /* 0x26 */ s16 mTimer;
    /* 0x28 */ u8 mStop;
};  // Size = 0x2C

STATIC_ASSERT(0x2C == sizeof(daObjHtetu1Splash_c));

class daObjHtetu1_c : public fopAc_ac_c {
public:
    inline BOOL check_sw();

    static u8 solidHeapCB(fopAc_ac_c*);
    int create_heap();
    cPhs_State _create();
    bool _delete();
    void init_mtx();
    void unlock();
    f32 get_water_h();
    void splash_manager();
    bool _execute();
    bool _draw();

public:
    static const char M_arcname[7];

    /* 0x290 */ J3DModel* mpModel;
    /* 0x294 */ request_of_phase_process_class mPhs;
    /* 0x29C */ u32 mSwSave;
    /* 0x2A0 */ cXyz mPos;
    /* 0x2AC */ cXyz mDir;
    /* 0x2B8 */ f32 mWaterLevel;
    /* 0x2BC */ f32 mSpeed;
    /* 0x2C0 */ u16 mAngle;
    /* 0x2C2 */ u8 mStatus;
    /* 0x2C3 */ u8 mPad;
    /* 0x2C4 */ s16 mEvtIdx;
    /* 0x2C6 */ u8 mMode;
    /* 0x2C7 */ u8 mPad2;
    /* 0x2C8 */ s16 mQuakeTimer;
    /* 0x2CA */ u8 mPad3[2];
    /* 0x2CC */ dBgW* mpBgW;
    /* 0x2D0 */ daObjHtetu1Splash_c mSplash[2];
};  // Size = 0x328

STATIC_ASSERT(0x328 == sizeof(daObjHtetu1_c));

#endif /* D_A_OBJ_HTETU1_H */
