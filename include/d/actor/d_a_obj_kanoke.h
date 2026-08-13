#ifndef D_A_OBJ_KANOKE_H
#define D_A_OBJ_KANOKE_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "d/d_bg_w.h"

class daObjKanoke_c : public fopAc_ac_c {
public:
    enum Prm_e {
        PRM_TYPE_W = 0x1,
        PRM_TYPE_S = 0x0,

        PRM_SEARCH_W = 0x5,
        PRM_SEARCH_S = 0x1,

        PRM_YURE_W = 0x1,
        PRM_YURE_S = 0x6,

        PRM_SWNO_W = 0x8,
        PRM_SWNO_S = 0x8,

        PRM_SWNO2_W = 0x8,
        PRM_SWNO2_S = 0x10,
    };

    daObjKanoke_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    BOOL _delete();
    BOOL _draw();
    BOOL _execute();
    void executeNormal();
    void executeYureYoko();
    void executeOpenYoko();
    void executeEffectYoko();
    void executeYureTate();
    void executeOpenTate();
    void executeEffectTate();
    void executeWait();
    u8 getPrmType();
    u8 getPrmSearch();
    u8 getPrmYure();
    u8 getPrmSwNo();
    u8 getPrmSwNo2();
    void setMtx();
    void setMtxHontai();
    void setMtxHuta(cXyz*);

public:
    /* 0x290 */ request_of_phase_process_class mPhs;
    /* 0x298 */ J3DModel* mpModel;
    /* 0x29C */ J3DModel* mpModel2;
    /* 0x2A0 */ dBgW* m2A0;
    /* 0x2A4 */ dBgW* m2A4;
    /* 0x2A8 */ Mtx mMtx;
    /* 0x2D8 */ Mtx m2D8;
    /* 0x308 */ dCcD_Stts mStts;
    /* 0x344 */ dCcD_Cps mCps0;
    /* 0x47C */ dCcD_Cps mCps[3];
    /* 0x824 */ s32 m824[2];
    /* 0x82C */ dPa_smokeEcallBack mSmokeCb;
    /* 0x84C */ cXyz m84C;
    /* 0x858 */ csXyz m858;
    /* 0x85E */ u8 m85E[0x860 - 0x85E];
    /* 0x860 */ cXyz m860;
    /* 0x86C */ f32 m86C;
    /* 0x870 */ f32 m870;
    /* 0x874 */ f32 m874;
    /* 0x878 */ f32 m878;
    /* 0x87C */ s16 m87C;
    /* 0x87E */ s16 m87E;
    /* 0x880 */ s16 m880;
    /* 0x882 */ s16 m882;
    /* 0x884 */ s16 m884;
    /* 0x886 */ s16 m886;
    /* 0x888 */ s16 m888;
    /* 0x88A */ u8 m88A;
    /* 0x88B */ u8 m88B;
    /* 0x88C */ u8 m88C;
    /* 0x88D */ u8 m88D;
    /* 0x88E */ u8 m88E;
    /* 0x88F */ u8 m88F;
};  // Size: 0x890

#endif /* D_A_OBJ_KANOKE_H */
