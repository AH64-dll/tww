#ifndef D_A_TAG_KF1_H
#define D_A_TAG_KF1_H

#include "d/d_lib.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daTag_Kf1_c : public fopNpc_npc_c {
public:
    typedef int (daTag_Kf1_c::*ProcFunc)(void*);

    s32 createInit();
    void setStt(signed char);
    u16 next_msgStatus(unsigned long*);
    void eventOrder();
    void checkOrder();
    s32 chkAttention(cXyz);
    s32 partner_srch();
    s16 checkPartner();
    void goto_nextStage();
    void event_talkInit(int);
    s32 event_mesSet();
    s32 event_mesEnd();
    void bensyoInit();
    s32 event_bensyo();
    void event_cntTsubo();
    void privateCut();
    void event_proc();
    int set_action(ProcFunc, void*);
    int wait01();
    int wait02();
    int wait_action1(void*);
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();

    static BOOL createHeapCB(fopAc_ac_c*);

public:
    /* 0x6C4 */ ProcFunc mActionFunc;
    /* 0x6D0 */ dNpc_EventCut_c mEventCut;
    /* 0x73C */ u8 m73C;
    /* 0x73D */ u8 m73D;
    /* 0x73E */ s16 m73E;
    /* 0x740 */ u8 m740[0x742 - 0x740];
    /* 0x742 */ u16 m742;
    /* 0x744 */ s32 mPartnerID[8];
    /* 0x764 */ s16 mPartnerNum;
    /* 0x766 */ s8 m766;
    /* 0x767 */ s8 m767;
    /* 0x768 */ s8 m768;
    /* 0x769 */ u8 m769;
    /* 0x76A */ s8 m76A;
    /* 0x76B */ u8 m76B;
};  // Size: 0x76C

class daTag_Kf1_HIO_c : public JORReflexible {
public:
    daTag_Kf1_HIO_c();
    virtual ~daTag_Kf1_HIO_c() {}
    virtual void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05[0x08 - 0x05];
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ u8 m10;
    /* 0x11 */ u8 m11[0x14 - 0x11];
};  // Size: 0x14

#endif /* D_A_TAG_KF1_H */
