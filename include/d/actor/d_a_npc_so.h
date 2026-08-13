#ifndef D_A_NPC_SO_H
#define D_A_NPC_SO_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_jnt_hit.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;
class dCcD_SrcSph;

class daNpc_So_c : public fopAc_ac_c {
public:
    enum Proc_e {
        
    };

    int getMiniGameRestArrow() { return 10 - mB78; }
    void isAnm(signed char) {}
    void modeProcInit(int) {}

    fopAc_ac_c* _searchEsa(fopAc_ac_c*);
    void _nodeControl(J3DNode*, J3DModel*);
    void _searchTagSo(fopAc_ac_c*);
    void _searchMinigameTagSo(fopAc_ac_c*);
    void XyCheckCB(int);
    void XyEventCB(int);
    void _createHeap();
    void jntHitCreateHeap();
    void checkTgHit();
    void offsetZero();
    void offsetDive();
    void offsetSwim();
    void offsetAppear();
    void getMsg();
    void next_msgStatus(unsigned long*);
    void lookBack();
    void setAttention();
    void setAnm(signed char, bool);
    void setAnmSwimSpeed();
    void setMtx();
    void modeWaitInit();
    void modeWait();
    void modeHideInit();
    void modeHide();
    void modeJumpInit();
    void modeJump();
    void modeSwimInit();
    void modeSwim();
    void modeNearSwimInit();
    void modeNearSwim();
    void modeEventFirstWaitInit();
    void modeEventFirstWait();
    void modeEventFirstInit();
    void modeEventFirst();
    void modeEventFirstEndInit();
    void modeEventFirstEnd();
    void modeEventEsaInit();
    void modeEventEsa();
    void modeEventMapopenInit();
    void modeEventMapopen();
    void modeEventBowInit();
    void modeEventBow();
    void modeTalkInit();
    void modeTalk();
    void modeDisappearInit();
    void modeDisappear();
    void modeDebugInit();
    void modeDebug();
    void modeGetRupeeInit();
    void modeGetRupee();
    void modeEventTriForceInit();
    void modeEventTriForce();
    void modeProc(Proc_e, int);
    void eventOrder();
    void checkOrder();
    void setScale();
    bool _execute();
    void debugDraw();
    void hudeDraw();
    bool _draw();
    void createInit();
    void getArg();
    cPhs_State _create();
    bool _delete();

    void cutAppearProc();
    void cutAppearStart();
    void cutDisappearProc();
    void cutDisappearStart();
    void cutDiveProc();
    void cutDiveStart();
    void cutEatesaFirstProc();
    void cutEatesaFirstStart();
    void cutEatesaProc();
    void cutEatesaStart();
    void cutEffectProc();
    void cutEffectStart();
    void cutEquipProc();
    void cutEquipStart();
    void cutJumpMapopenProc();
    void cutJumpMapopenStart();
    void cutJumpProc();
    void cutJumpStart();
    void cutMiniGameEndProc();
    void cutMiniGameEndStart();
    void cutMiniGamePlTurnProc();
    void cutMiniGamePlTurnStart();
    void cutMiniGamePlUpProc();
    void cutMiniGamePlUpStart();
    void cutMiniGameProc();
    void cutMiniGameReturnProc();
    void cutMiniGameReturnStart();
    void cutMiniGameStart();
    void cutMiniGameWaitProc();
    void cutMiniGameWaitStart();
    void cutMiniGameWarpProc();
    void cutMiniGameWarpStart();
    void cutPartnerShipProc();
    void cutPartnerShipStart();
    void cutProc();
    void cutSetAnmProc();
    void cutSetAnmStart();
    void cutSwimProc();
    void cutSwimStart();
    void cutTurnProc();
    void cutTurnStart();
    void cutUnequipProc();
    void cutUnequipStart();
    void initCam();
    void moveCam();

    static const s32 m_heapsize;
    static const char m_arc_name[];
    static const dCcD_SrcSph m_sph_src;

public:
    /* Place member variables here */
#if VERSION == VERSION_DEMO
    /* 0x290 */ u8 m290[0xB70 - 0x290];
#else
    /* 0x290 */ s16 field_0x290;
    /* 0x292 */ s16 field_0x292;
    /* 0x294 */ s16 field_0x294;
    /* 0x296 */ s16 field_0x296;
    /* 0x298 */ s8 field_0x298;
    /* 0x299 */ s8 field_0x299;
    /* 0x29A */ u8 field_0x29A[0x2A0 - 0x29A];
    /* 0x2A0 */ u8 field_0x2A0[0xB54 - 0x2A0];
    /* 0xB54 */ cXyz field_0xB54;
    /* 0xB60 */ cXyz field_0xB60;
    /* 0xB6C */ u8 field_0xB6C[0xB78 - 0xB6C];
#endif
    /* 0xB78 */ int mB78;
};

class daNpc_So_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_So_HIO_c();

public:
    /* 0x04 */ dNpc_HIO_c mNpc;
    /* 0x2C */ u8 field_0x2C[6];
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ s16 field_0x64;
    /* 0x66 */ s16 field_0x66;
    /* 0x68 */ s16 field_0x68;
    /* 0x6A */ s16 field_0x6A;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ s16 field_0x7C;
    /* 0x7E */ u8 field_0x7E[0x80 - 0x7E];
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ u8 field_0x94;
    /* 0x95 */ u8 field_0x95[0x98 - 0x95];
    /* 0x98 */ JntHit_HIO_c mJntHit;
};  // Size: 0xC4

#endif /* D_A_NPC_SO_H */
