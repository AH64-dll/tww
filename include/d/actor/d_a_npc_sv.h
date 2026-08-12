#ifndef D_A_NPC_SV_H
#define D_A_NPC_SV_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

struct sSvAnmDat {
    /* 0x00 */ u8 mAnmNo;
    /* 0x01 */ u8 mSpeed;
    /* 0x02 */ s8 mRepeat;
}; // Size: 0x03

struct sSvNpcDat {
    /* 0x00 */ s16 mMaxHeadX;
    /* 0x02 */ s16 mMaxHeadY;
    /* 0x04 */ s16 mMaxBackboneX;
    /* 0x06 */ s16 mMaxBackboneY;
    /* 0x08 */ s16 mMinHeadX;
    /* 0x0A */ s16 mMinHeadY;
    /* 0x0C */ s16 mMinBackboneX;
    /* 0x0E */ s16 mMinBackboneY;
    /* 0x10 */ s16 mMaxTurnStep;
    /* 0x12 */ s16 m12;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ s16 m34;
    /* 0x36 */ s16 m36;
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ s16 m40;
    /* 0x42 */ u8 m42;
    /* 0x43 */ u8 m43;
}; // Size: 0x44

class daNpcSv_c : public fopNpc_npc_c {
public:
    u32* getMsgPtn() { return mMsgTbl; }
    u8 getNpcNo() { return mNpcNo; }
    request_of_phase_process_class* getPhaseP() { return &mPhase; }
    void setResFlag(u8 flag) { m73A = flag; }

    daNpcSv_c();
    cPhs_State _create();
    s32 createHeap();
    s32 createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    s32 executeCommon();
    void executeSetMode(u8);
    s32 executeWaitInit();
    void executeWait();
    s32 executeTalkInit();
    void executeTalk();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    bool eventMesSet();
    void eventGetItemInit(int);
    s32 eventGetItem();
    void eventSetAngleInit();
    void eventAttentionInit(int);
    s32 eventAttention();
    void eventTurnOkInit();
    u16 talk2(int, fopAc_ac_c*);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void setMessage(u32);
    void setAnmFromMsgTag();
    u8 getPrmNpcNo();
    void setMtx();
    void chkAttention();
    void lookBack();
    void playAnm();
    void setAnm(u8, int, f32);
    u8 setAnmTbl(sSvAnmDat*);
    void setCollision(dCcD_Cyl*, cXyz, f32, f32);
    u8 getTalkNo();
    bool isTalkOK();

    static const char m_arcname[];

public:
    /* 0x6C4 */ request_of_phase_process_class mPhase;
    /* 0x6CC */ request_of_phase_process_class mPhase2;
    /* 0x6D4 */ u32 mShadowId;
    /* 0x6D8 */ u32 m6D8;
    /* 0x6DC */ u8 m6DC[0x6EC - 0x6DC];
    /* 0x6EC */ f32 m6EC;
    /* 0x6F0 */ f32 m6F0;
    /* 0x6F4 */ f32 m6F4;
    /* 0x6F8 */ u8 m6F8[0x704 - 0x6F8];
    /* 0x704 */ sSvAnmDat* mAnmDat;
    /* 0x708 */ u32* mMsgTbl;
    /* 0x70C */ f32 m70C;
    /* 0x710 */ f32 m710;
    /* 0x714 */ s32 m714;
    /* 0x718 */ s32 m718;
    /* 0x71C */ u8 m71C;
    /* 0x71D */ u8 m71D[0x71E - 0x71D];
    /* 0x71E */ s16 m71E;
    /* 0x720 */ s16 m720;
    /* 0x722 */ s16 m722;
    /* 0x724 */ s16 m724;
    /* 0x726 */ s16 m726;
    /* 0x728 */ s16 m728;
    /* 0x72A */ s16 m72A;
    /* 0x72C */ s16 m72C;
    /* 0x72E */ s16 m72E;
    /* 0x730 */ s16 m730;
    /* 0x732 */ s16 m732;
    /* 0x734 */ u16 m734;
    /* 0x736 */ u8 m736;
    /* 0x737 */ u8 m737;
    /* 0x738 */ u8 m738;
    /* 0x739 */ u8 m739;
    /* 0x73A */ u8 m73A;
    /* 0x73B */ u8 mNpcNo;
    /* 0x73C */ u8 m73C;
    /* 0x73D */ u8 m73D;
    /* 0x73E */ u8 m73E;
    /* 0x73F */ u8 m73F;
    /* 0x740 */ u8 m740;
    /* 0x741 */ u8 m741;
    /* 0x742 */ u8 m742;
    /* 0x743 */ u8 m743;
    /* 0x744 */ u8 m744;
    /* 0x745 */ u8 m745;
    /* 0x746 */ u8 m746;
    /* 0x747 */ u8 m747;
    /* 0x748 */ u8 m748;
    /* 0x749 */ u8 m749;
    /* 0x74A */ u8 m74A;
    /* 0x74B */ u8 m74B;
}; // Size: 0x74C

#endif /* D_A_NPC_SV_H */
