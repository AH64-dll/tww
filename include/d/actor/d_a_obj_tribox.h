#ifndef D_A_OBJ_TRIBOX_H
#define D_A_OBJ_TRIBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "d/d_bg_s.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/d_com_inf_game.h"

namespace daObjTribox {
    class Act_c;

    struct PP_c {
        /* 0x00 */ u8 mFlag;
        /* 0x04 */ s32 mX;
        /* 0x08 */ s32 mY;
        /* 0x0C */ s32 mZ;
    };  // Size: 0x10

    struct Attr_c {
        /* 0x00 */ f32 m00;
        /* 0x04 */ f32 m04;
        /* 0x08 */ f32 m08;
        /* 0x0C */ s16 m0C;
        /* 0x0E */ s16 m0E;
        /* 0x10 */ f32 m10;
        /* 0x14 */ s16 m14;
        /* 0x16 */ s16 m16;
        /* 0x18 */ s16 m18;
        /* 0x1A */ s16 m1A;
    };  // Size: 0x1C

    struct Hio_c : public JORReflexible {
        Hio_c();
        virtual ~Hio_c() {}
        virtual void genMessage(JORMContext* i_ctx);

        void default_set();

        /* 0x20 */ Attr_c mAttr;
    };  // Size: 0x3C

    class Act_c : public fopAc_ac_c {
    public:
        enum Mode_e {
            MODE_BLOCK_WAIT_e = 0x0,
            MODE_BLOCK_WALK_e = 0x1,
            MODE_BLOCK_SINK_e = 0x2,
            MODE_BLOCK_LOWER_e = 0x3,
            MODE_CORRECT_OFF_e = 0x4,
            MODE_CORRECT_ON_e = 0x5,
            MODE_CORRECT_DEMOREQ_e = 0x6,
            MODE_CORRECT_DEMORUN_e = 0x7,
            MODE_CORRECT_END_e = 0x8,
            MODE_CORRECT_DUMMY_e = 0x9,
        };

        enum Prm_e {
            PRM_TYPE_W = 0x1,
            PRM_TYPE_S = 0x10,
            PRM_SWSAVE_W = 0x8,
            PRM_SWSAVE_S = 0x8,
        };

        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        int prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        bool is_switch() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }
        void on_switch() const { fopAcM_onSwitch(const_cast<Act_c*>(this), prm_get_swSave()); }

        Act_c() : mSmokeCB(1), mSinkSmokeCB(1, 1, 0, 0), mSinkSmokeCB2(1, 1, 0, 0), mSinkSmokeCB3(1, 1, 0, 0) {}

        void set_state();
        static BOOL solidHeapCB(fopAc_ac_c*);
        u8 create_heap();
        void block_init();
        u8 chk_light() const;
        void correct_before_init();
        void correct_after_init();
        void controll_set();
        void controll_clear();
        cPhs_State create_block_before();
        cPhs_State create_block_after();
        cPhs_State create_correct_before();
        cPhs_State create_correct_after();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void init_mtx();
        static fopAc_ac_c* push_pullCB(fopAc_ac_c*, fopAc_ac_c*, s16, dBgW::PushPullLabel);
        bool line_cross(const cXyz*, const cXyz*) const;
        bool chk_wall(int) const;
        bool chk_space() const;
        void eff_flash();
        void eff_smoke_start();
        void eff_smoke_pos();
        void eff_smoke_end();
        void eff_smoke_remove();
        void eff_sink_smoke_init();
        void eff_sink_smoke_start();
        void eff_sink_smoke_end();
        void eff_sink_smoke_remove();
        void vib_sink_init();
        void vib_sink_start();
        void vib_sink_end();
        static fopAc_ac_c* search_block(void*, void*);
        void sound_pos_init();
        void sound_pos_delete();
        int sound_get_mapinfo(const cXyz&);
        void sound_sink_down_block();
        void sound_sink_stop_block();
        void sound_flash_shine();
        void sound_flash_light();
        void mode_block_wait_init();
        void mode_block_wait();
        void mode_block_walk_init();
        void mode_block_walk();
        void mode_block_sink_init();
        void mode_block_sink();
        void mode_block_lower_init();
        void mode_block_lower();
        void mode_correct_off_init();
        void mode_correct_off();
        void mode_correct_on_init();
        void mode_correct_on();
        void mode_correct_demoreq_init();
        void mode_correct_demoreq();
        void mode_correct_demorun_init();
        void mode_correct_demorun();
        void mode_correct_end_init();
        void mode_correct_end();
        void mode_correct_dummy_init();
        void mode_correct_dummy();
        void mode_proc_call();
        void execute_block();
        void execute_correct();
        bool _execute();
        bool _draw();

        static void reset();

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ J3DModel* mpModel2;
        /* 0x2A0 */ mDoExt_brkAnm mBrkAnm;
        /* 0x2B8 */ mDoExt_brkAnm mBrkAnm2;
        /* 0x2D0 */ dBgW* mpBgW;
        /* 0x2D4 */ u8 m2D4[0x304 - 0x2D4];
        /* 0x304 */ s32 mMode;
        /* 0x308 */ s32 m308;
        /* 0x30C */ s16 m30C;
        /* 0x310 */ PP_c mPP[3];
        /* 0x340 */ s16 m340;
        /* 0x344 */ cXyz m344;
        /* 0x350 */ s32 m350;
        /* 0x354 */ s32 m354;
        /* 0x358 */ s16 m358;
        /* 0x35C */ dPa_smokeEcallBack mSmokeCB;
        /* 0x37C */ cXyz mSmokePos;
        /* 0x388 */ csXyz mSmokeAngle;
        /* 0x38E */ u8 m38E;
        /* 0x390 */ f32 m390;
        /* 0x394 */ u8 m394;
        /* 0x395 */ u8 m395;
        /* 0x396 */ s16 m396;
        /* 0x398 */ dPa_smokeEcallBack mSinkSmokeCB;
        /* 0x3B8 */ dPa_smokeEcallBack mSinkSmokeCB2;
        /* 0x3D8 */ dPa_smokeEcallBack mSinkSmokeCB3;
        /* 0x3F8 */ u8 m3F8;
        /* 0x3F9 */ u8 m3F9;
        /* 0x3FA */ s16 m3FA;

        static const char M_arcname[];
        static cXyz M_sound_pos;
        static int M_correct_cnt;
        static bool M_correct_flag;
        static int M_b_cont_cnt;
        static int M_c_cont_cnt;
        static u8 M_sink_start;
        static cXyz M_post[3];
        static dBgS_ObjLinChk M_lin;
    };

    STATIC_ASSERT(sizeof(Act_c) == 0x3FC);
};  // namespace daObjTribox

#endif /* D_A_OBJ_TRIBOX_H */
