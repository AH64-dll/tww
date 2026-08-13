#ifndef D_A_OBJ_KANOKE_H
#define D_A_OBJ_KANOKE_H

#include "f_op/f_op_actor.h"

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
    void createHeap();
    void createInit();
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
    /* Place member variables here */
};

#endif /* D_A_OBJ_KANOKE_H */
