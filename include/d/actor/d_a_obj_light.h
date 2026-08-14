#ifndef D_A_OBJ_LIGHT_H
#define D_A_OBJ_LIGHT_H

#include "f_op/f_op_actor.h"

namespace daObjLight {
    class Act_c : public fopAc_ac_c {
    public:
        bool solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void init_collision();
        void set_collision();
        cPhs_State _create();
        bool _delete();
        void set_fire(int);
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

        static s16 M_S_light_angle;
        static u32 M_S_pre_set_frame_LOD;
        static u32 M_S_pre_set_frame_FRRS;
        static u8 M_S_lod_access;

public:
        /* 0x290 */ u8 field_0x290[0x44C - 0x290];
        /* 0x44C */ u8 field_0x44C[0x450 - 0x44C];  // object w/ vtable (virtual @ +0x20)
        /* 0x450 */ void* mpModel;
        /* 0x454 */ u8 field_0x454[0x464 - 0x454];
        /* 0x464 */ u8 mFireAlpha;
        /* 0x465 */ u8 field_0x465[0x46C - 0x465];
        /* 0x46C */ Mtx mFireMtx;
        /* 0x49C */ s16 mEventId;
        /* 0x49E */ s16 mEventActive;
    };
};

#endif /* D_A_OBJ_LIGHT_H */
