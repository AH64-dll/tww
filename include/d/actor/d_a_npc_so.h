#ifndef D_A_NPC_SO_H
#define D_A_NPC_SO_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_jnt_hit.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;
class dCcD_SrcSph;

class daNpc_So_c : public fopNpc_npc_c {
public:
    enum Proc_e {
        
    };

    int getMiniGameRestArrow() { return 10 - mB78; }
    void isAnm(signed char) {}
    void modeProcInit(int) {}

    fopAc_ac_c* _searchEsa(fopAc_ac_c*);
    void _nodeControl(J3DNode*, J3DModel*);
    fopAc_ac_c* _searchTagSo(fopAc_ac_c*);
    fopAc_ac_c* _searchMinigameTagSo(fopAc_ac_c*);
    s16 XyCheckCB(int);
    s16 XyEventCB(int);
    BOOL _createHeap();
    bool jntHitCreateHeap();
    bool checkTgHit();
    void offsetZero();
    void offsetDive();
    void offsetSwim();
    void offsetAppear();
    u32 getMsg();
    u16 next_msgStatus(u32*);
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
    /* 0x6C4 */ u8 m6C4[0xB70 - 0x6C4];
#else
    /* 0x6C4 */ u8 field_0x6C4[0x6D0 - 0x6C4];
    /* 0x6D0 */ s16 field_0x6D0;
    /* 0x6D2 */ u8 field_0x6D2[0x6D3 - 0x6D2];
    /* 0x6D3 */ s8 field_0x6D3;
    /* 0x6D4 */ u8 field_0x6D4[0x6D8 - 0x6D4];
    /* 0x6D8 */ int field_0x6D8;
    /* 0x6DC */ dCcD_Stts mStts;
    /* 0x718 */ dCcD_Sph mSph;
    /* 0x844 */ u8 field_0x844[0x84C - 0x844];
    /* 0x84C */ mDoExt_McaMorf* mpMorf;
    /* 0x850 */ J3DModel* mpModel;
    /* 0x854 */ mDoExt_btpAnm mBtpAnm;
    /* 0x868 */ u8 field_0x868[0x870 - 0x868];
    /* 0x870 */ dBgS_ObjAcch mObjAcch;
    /* 0xA34 */ dBgS_AcchCir mAcchCir;
    /* 0xA74 */ u8 field_0xA74[0xA79 - 0xA74];
    /* 0xA79 */ u8 field_0xA79;
    /* 0xA7A */ u8 field_0xA7A[0xA7C - 0xA7A];
    /* 0xA7C */ f32 field_0xA7C;
    /* 0xA80 */ cXyz field_0xA80;
    /* 0xA8C */ u8 field_0xA8C[0xAA8 - 0xA8C];
    /* 0xAA8 */ JntHit_c* field_0xAA8;
    /* 0xAAC */ u8 field_0xAAC[0xAE8 - 0xAAC];
    /* 0xAE8 */ dPa_rippleEcallBack mRipple;
    /* 0xAFC */ u8 field_0xAFC[0xB0C - 0xAFC];
    /* 0xB0C */ u8 field_0xB0C;
    /* 0xB0D */ u8 field_0xB0D[0xB38 - 0xB0D];
    /* 0xB38 */ cXyz field_0xB38;
    /* 0xB44 */ cXyz field_0xB44;
    /* 0xB50 */ s16 field_0xB50;
    /* 0xB52 */ u8 field_0xB52[0xB54 - 0xB52];
    /* 0xB54 */ cXyz field_0xB54;
    /* 0xB60 */ cXyz field_0xB60;
    /* 0xB6C */ u8 field_0xB6C[0xB70 - 0xB6C];
    /* 0xB70 */ u8 field_0xB70;
    /* 0xB71 */ u8 field_0xB71[0xB74 - 0xB71];
    /* 0xB74 */ int field_0xB74;
    /* 0xB78 */ int mB78;
    /* 0xB7C */ int field_0xB7C;
    /* 0xB80 */ int field_0xB80;
    /* 0xB84 */ u8 field_0xB84;
    /* 0xB85 */ u8 field_0xB85[0xB88 - 0xB85];
    /* 0xB88 */ f32 field_0xB88;
    /* 0xB8C */ f32 field_0xB8C;
    /* 0xB90 */ cXyz field_0xB90;
    /* 0xB9C */ s16 field_0xB9C;
    /* 0xB9E */ u8 field_0xB9E[0xBAE - 0xB9E];
    /* 0xBAE */ u8 field_0xBAE;
    /* 0xBAF */ u8 field_0xBAF[0xBB0 - 0xBAF];
    /* 0xBB0 */ f32 field_0xBB0;
    /* 0xBB4 */ f32 field_0xBB4;
    /* 0xBB8 */ f32 field_0xBB8;
    /* 0xBBC */ int field_0xBBC;
    /* 0xBC0 */ f32 field_0xBC0;
    /* 0xBC4 */ f32 field_0xBC4;
    /* 0xBC8 */ f32 field_0xBC8;
    /* 0xBCC */ f32 field_0xBCC;
    /* 0xBD0 */ f32 field_0xBD0;
    /* 0xBD4 */ f32 field_0xBD4;
    /* 0xBD8 */ u8 field_0xBD8;
    /* 0xBD9 */ u8 field_0xBD9;
    /* 0xBDA */ bool field_0xBDA;
    /* 0xBDB */ u8 field_0xBDB;
    /* 0xBDC */ s16 field_0xBDC;
    /* 0xBDE */ u8 field_0xBDE;
    /* 0xBDF */ u8 field_0xBDF[0xBE0 - 0xBDF];
    /* 0xBE0 */ int field_0xBE0;
    /* 0xBE4 */ u8 field_0xBE4[0xC00 - 0xBE4];
#endif
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
