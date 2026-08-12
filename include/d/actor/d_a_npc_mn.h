#ifndef D_A_NPC_MN_H
#define D_A_NPC_MN_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

class J3DNode;

struct sMnAnmDat {
    /* 0x00 */ s8 mAnmNum;
    /* 0x01 */ s8 mBtpNum;
    /* 0x02 */ s16 field_0x02;
    /* 0x04 */ f32 mMorf;
    /* 0x08 */ f32 mSpeed;
    /* 0x0C */ int mLoopMode;
};

class daNpcMn_c : public fopNpc_npc_c {
public:
    void getNpcNo() {}
    void getPhaseP() {}
    void getPosFlag() {}
    void setResFlag(unsigned char) {}

    daNpcMn_c();
    cPhs_State _create();
    BOOL createHeap();
    cPhs_State createInit();
    bool _delete();
    bool _draw();
    bool _execute();
    void executeCommon();
    void executeSetMode(unsigned char);
    void executeWaitInit();
    void executeWait();
    void executeTalkInit();
    void executeTalk();
    void executeTalk3Init();
    void executeTalk3();
    void executeWalkInit();
    void executeWalk();
    void executeTurnInit();
    void executeTurn();
    void checkOrder();
    void eventOrder();
    void eventMove();
    void privateCut();
    void eventMesSetInit(int);
    void eventMesSet();
    void eventGetItemInit();
    void eventWaitInit(int);
    void eventWait(int);
    void eventSwOnInit(int);
    void eventSwOn();
    void eventHatchInit();
    void eventHatch();
    void eventBikkuriInit(int);
    void eventBikkuri();
    void eventTurnInit();
    void eventTurn(int);
    void eventWalkInit();
    void eventWalk();
    void eventLookInit();
    void eventLook();
    void eventJumpInit(int);
    void eventJump();
    void talk2(int);
    void talk3(int);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void getMsg3();
    void chkMsg();
    void setMessage(unsigned long);
    void setAnmFromMsgTag();
    s8 getPrmNpcNo();
    void getPrmRailID();
    s32 getPrmSwitchBit();
    void getPrmSwitchBit2();
    void setMtx();
    void chkAttention();
    void lookBack();
    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void playAnm();
    void setAnm(unsigned char, int, float);
    void setAnmTbl(sMnAnmDat*);
    void XyCheckCB(int);
    void getRand(int);
    void setCollision(dCcD_Cyl*, cXyz, float, float);
    void chkEndEvent();
    s8 chkPosNo();
    u8 getPosNo();
    BOOL isChangePos(unsigned char);

public:
    /* 0x6C4 */ u8 field_0x6C4[0x724 - 0x6C4];
    /* 0x724 */ request_of_phase_process_class mPhs;
    /* 0x72C */ request_of_phase_process_class mPhs2;
    /* 0x734 */ void* m734;
    /* 0x738 */ void* m738;
    /* 0x73C */ mDoExt_btpAnm mBtpAnm;
    /* 0x74C */ u8 field_0x74C[0x750 - 0x74C];
    /* 0x750 */ void* m750;
    /* 0x754 */ void* m754;
    /* 0x758 */ u8 field_0x758[0x759 - 0x758];
    /* 0x759 */ u8 m759;
    /* 0x75A */ u8 field_0x75A[0x768 - 0x75A];
    /* 0x768 */ f32 m768;
    /* 0x76C */ u8 field_0x76C[0x770 - 0x76C];
    /* 0x770 */ f32 m770;
    /* 0x774 */ void* m774;
    /* 0x778 */ void* m778;
    /* 0x77C */ f32 m77C;
    /* 0x780 */ f32 m780;
    /* 0x784 */ f32 m784;
    /* 0x788 */ f32 m788;
    /* 0x78C */ u8 field_0x78C[0x790 - 0x78C];
    /* 0x790 */ void* m790;
    /* 0x794 */ u8 m794;
    /* 0x795 */ u8 field_0x795[0x796 - 0x795];
    /* 0x796 */ s16 m796;
    /* 0x798 */ s16 m798;
    /* 0x79A */ u8 field_0x79A[0x7A0 - 0x79A];
    /* 0x7A0 */ s16 m7A0;
    /* 0x7A2 */ u8 field_0x7A2[0x7A4 - 0x7A2];
    /* 0x7A4 */ s16 m7A4;
    /* 0x7A6 */ u8 field_0x7A6[0x7B4 - 0x7A6];
    /* 0x7B4 */ u8 m7B4;
    /* 0x7B5 */ u8 m7B5;
    /* 0x7B6 */ u8 mNpcNo;
    /* 0x7B7 */ u8 field_0x7B7[0x7B8 - 0x7B7];
    /* 0x7B8 */ u8 m7B8;
    /* 0x7B9 */ u8 field_0x7B9[0x7BD - 0x7B9];
    /* 0x7BD */ u8 m7BD;
    /* 0x7BE */ u8 field_0x7BE[0x7C1 - 0x7BE];
    /* 0x7C1 */ u8 mPosNo;
    /* 0x7C2 */ u8 m7C2;
    /* 0x7C3 */ u8 m7C3;
    /* 0x7C4 */ u8 m7C4;
};  // Size: 0x7C8

#endif /* D_A_NPC_MN_H */
