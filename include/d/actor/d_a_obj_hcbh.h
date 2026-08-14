#ifndef D_A_OBJ_HCBH_H
#define D_A_OBJ_HCBH_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "SSystem/SComponent/c_phase.h"

class daObjHcbh_c : public fopAc_ac_c {
public:
    enum Param_e {
        PRM_ITEMNO_W = 6,
        PRM_ITEMNO_S = 0,

        PRM_ITEMSAVEBIT_W = 7,
        PRM_ITEMSAVEBIT_S = 6,

        PRM_SWSAVE_W = 8,
        PRM_SWSAVE_S = 13,
    };

    s32 param_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEMNO_W, PRM_ITEMNO_S); }
    s32 param_get_itemSaveBitNo() const { return daObj::PrmAbstract(this, PRM_ITEMSAVEBIT_W, PRM_ITEMSAVEBIT_S); }
    s32 param_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
    void param_on_swSave() { dComIfGs_onSwitch(param_get_swSave(), fopAcM_GetRoomNo((fopAc_ac_c*)this)); }

    BOOL chk_appear();
    void set_mtx();
    void init_mtx();
    static u8 solidHeapCB(fopAc_ac_c*);
    int create_heap();
    void setup_break_condition(fopAc_ac_c*);
    void checkCollision();
    static void co_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*);
    void particle_set();
    void make_item();
    cPhs_State _create();
    bool _delete();
    void wait_act_proc();
    void fall_act_proc();
    bool _execute();
    bool _draw();

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpModel2[4];
    /* 0x2AC */ dBgW* mpBgW;
    /* 0x2B0 */ dBgW* mpBgW2;
    /* 0x2B4 */ dBgS_ObjAcch mAcch;
    /* 0x478 */ dBgS_AcchCir mCir;
    /* 0x4B8 */ dCcD_Stts mStts;
    /* 0x4F4 */ dCcD_Cyl mCyl;
    /* 0x624 */ dCcD_Sph mSph[6];
    /* 0xD2C */ f32 mD2C;
    /* 0xD30 */ f32 mD30;
    /* 0xD34 */ s16 mD34;
    /* 0xD36 */ s16 mD36;
    /* 0xD38 */ cXyz mD38[4];
    /* 0xD68 */ f32 mD68[4];
    /* 0xD78 */ s16 mD78[4];
    /* 0xD80 */ s16 mD80[4];
    /* 0xD88 */ s16 mD88[4];
    /* 0xD90 */ int mD90[4];
    /* 0xDA0 */ s16 mDA0;
    /* 0xDA2 */ s16 mDA2;
    /* 0xDA4 */ int mDA4;
    /* 0xDA8 */ dPa_smokeEcallBack mSmokeCB;
    /* 0xDC8 */ u8 mDC8;
    /* 0xDC9 */ u8 mDC9[3];
    /* 0xDCC */ void (daObjHcbh_c::*mProcFunc)();
};

#endif /* D_A_OBJ_HCBH_H */
