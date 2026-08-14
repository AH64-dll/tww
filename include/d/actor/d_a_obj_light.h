#ifndef D_A_OBJ_LIGHT_H
#define D_A_OBJ_LIGHT_H

#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "d/d_cc_d.h"

class J3DModel;
class dBgW;

namespace daObjLight {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void init_collision();
        void set_collision();
        cPhs_State _create();
        bool _delete();
        BOOL set_fire(int);
        void draw_fire();
        void exe_fire();
        void delete_fire();
        bool now_event(s16);
        bool set_event(s16);
        void exe_event();
        void set_mtx();
        void renew_angle();
        void control_light();
        void control_treasure();
        bool _execute();
        bool _draw();
        
        static bool renew_light_angle();
        static s16 get_light_angle();
        static s16 get_light_dif_angle();
        static BOOL set_light_dif_angle_LOD(s16);
        static BOOL set_light_dif_angle_FRRS(s16);

        static const char M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;

        static s16 M_S_light_angle;
        static u32 M_S_pre_set_frame_LOD;
        static u32 M_S_pre_set_frame_FRRS;
        static u8 M_S_lod_access;

public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel[3];
        /* 0x2A4 */ dBgW* mpBgW;
        /* 0x2A8 */ Mtx mBgWBaseMtx;
        /* 0x2D8 */ s16 mAngle;
        /* 0x2DA */ s16 m2DA;
        /* 0x2DC */ s16 m2DC;
        /* 0x2DE */ s16 m2DE;
        /* 0x2E0 */ dCcD_Stts mStts;
        /* 0x31C */ dCcD_Cyl mCyl;
        /* 0x44C */ dPa_followEcallBack mFireFollowCb;
        /* 0x460 */ s16 mFireAngle;
        /* 0x462 */ s16 mFireAngle2;
        /* 0x464 */ u8 mFireAlpha;
        /* 0x465 */ u8 field_0x465[0x468 - 0x465];
        /* 0x468 */ f32 mFireScale;
        /* 0x46C */ Mtx mFireMtx;
        /* 0x49C */ s16 mEventId;
        /* 0x49E */ s16 mEventActive;
        /* 0x4A0 */ s16 mEventIdx;
    };
};

#endif /* D_A_OBJ_LIGHT_H */
